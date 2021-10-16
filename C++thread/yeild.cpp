#include <thread>
#include <iostream>
#include <chrono>


void testThread(const char *p)
{
    int i = 0;

    for(; i < 10; ++i){

        std::cout << "thread:" << p << i <<std::endl;
        if(i == 5){
            std::this_thread ::yield();
            //std::chrono ::milliseconds durl(2000); 
            //std::this_thread :: sleep_for(durl);
        }
    }

}

int main()
{
    std::thread myThread(testThread, "bbb");
    std::thread myThread2(testThread, "aaa");

    myThread.join();
    myThread2.join();
    return 0;
}