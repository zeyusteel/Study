#include <thread>
#include <iostream>

void func()
{
    for(int i = 0; i < 100; i++){
        std::cout << i << "thread func " << std::endl;
    }
}

int main()
{
    std::thread threadObj(func);
    for(int i = 0; i < 100; i++){
        std::cout << i << "main func " << std::endl;
    }
    threadObj.join();

    std::cout << "exit" << std::endl;
    return 0;
}