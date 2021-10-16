#include <iostream>
#include <thread>
#include <future>
#include <chrono>
#include <mutex>
#include <condition_variable>
#include <exception>

std::mutex io_mutex;
std::mutex mutex;
std::condition_variable cond;

void testThread(int *p)
{

    std::lock_guard<std::mutex> guard(mutex);
    *p = 9;

    io_mutex.lock();
    std::cout << "thread test" << *p << std::endl;
    io_mutex.unlock();

    cond.notify_one();
}

void testOldFunc()
{
    int a = 7;
    std::thread myThread(testThread, &a);

    std::unique_lock<std::mutex> lock(mutex);
    cond.wait(lock);

    io_mutex.lock();
    std::cout << "main test" << a << std::endl;
    io_mutex.unlock();

    if(myThread.joinable()){
        myThread.join();
    }
}

void initiazer(std::promise<int> * promObj)
{
    std::cout<<"Inside Thread"<<std::endl;     
    promObj->set_value(35);


    try{
        promObj->set_value(36); //再次传递会抛出异常
    } catch(std::exception &e){
        std::cout << e.what() << std::endl;
    }


}

int main()
{
   //testOldFunc(); 
#if 1 
    std::promise<int> promiseObj;
    std::future<int> futureObj = promiseObj.get_future();
    std::thread th(initiazer, &promiseObj);
    std::cout<<futureObj.get()<<std::endl; //但是如果线程2还没有对该值进行设置，那么这个调用将会阻塞，直到线程2在promise对象中对该值进行设置
    th.join();
    //如果std::promise对象在赋值之前被销毁，那么管理的std::future对象上的get()调用将会抛出异常。 
    //除此之外，如果想要线程在不同时间点返回多个值，只需要在线程中传输多个std::promise对象，并从相关的多个std::futur对象中获取多个返回值。
#endif
    return 0;
}