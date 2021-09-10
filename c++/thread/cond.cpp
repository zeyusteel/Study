#include <iostream>
#include <thread>
#include <functional>
#include <mutex>
#include <condition_variable>

using namespace std::placeholders;
class Application
{
    std::mutex m_mutex;
    std::condition_variable m_condVar;
    bool m_bDataLoaded;
public:
    Application()
    {
        m_bDataLoaded = false;
    }
    void loadData()
    {
        // Make This Thread sleep for 1 Second
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        std::cout<<"Loading Data from XML"<<std::endl;
        // Lock The Data structure
        std::lock_guard<std::mutex> guard(m_mutex);
        // Set the flag to true, means data is loaded
        m_bDataLoaded = true;
        // Notify the condition variable
        m_condVar.notify_one();
    }
    bool isDataLoaded()
    {
        return m_bDataLoaded;
    }
    void mainTask()
    {
        std::cout<<"Do Some Handshaking"<<std::endl;
        // Acquire the lock
        std::unique_lock<std::mutex> mlock(m_mutex);
        /*
        wait()
        它使得当前线程阻塞，直到条件变量得到信号或发生虚假唤醒； 
        它原子性地释放附加的mutex，阻塞当前线程，并将其添加到等待当前条件变量对象的线程列表中，当某线程在同样的条件变量上调用notify_one() 或者 notify_all()，线程将被解除阻塞； 
        这种行为也可能是虚假的，因此，解除阻塞后，需要再次检查条件； 
        一个回调函数会传给该函数，调用它来检查其是否是虚假调用，还是确实满足了真实条件； 
        当线程解除阻塞后，wait()函数获取mutex锁，并检查条件是否满足，如果条件不满足，则再次原子性地释放附加的mutex，阻塞当前线程，并将其添加到等待当前条件变量对象的线程列表中。
        */
        m_condVar.wait(mlock, std::bind(&Application::isDataLoaded, this));
        std::cout<<"Do Processing On loaded Data"<<std::endl;
    }
};
int main()
{
    Application app;
    std::thread thread_1(&Application::mainTask, &app);
    std::thread thread_2(&Application::loadData, &app);
    thread_2.join();
    thread_1.join();
    return 0;
}