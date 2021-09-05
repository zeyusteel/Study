#include <thread>
#include <iostream>

void func()
{
    std::cout << "get id = " << std::this_thread::get_id() << std::endl;
}
int main()
{
    std::thread th_a(func);
    std::thread th_b(func);

    if(th_a.get_id() != th_b.get_id()){
        std::cout << "different id" << std::endl;
    }

    std::cout << "thread a :" << th_a.get_id() << std::endl;
    std::cout << "thread b :" << th_b.get_id() << std::endl;


    th_a.join();
    th_b.join();

    return 0;
}