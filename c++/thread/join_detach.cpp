#include <iostream>
#include <thread>
#include <vector>
#include <algorithm>

class MyWorkThread
{
public:
    void operator()(){
        std::cout<< "worker thread" << std::this_thread::get_id() << "running!" << std::endl;
    }
};

void abc(){}
/*
多次join 与 detach  或不掉用 会导致程序终止
*/
void test(){
    std::thread mythread(abc);
    
    if(mythread.joinable()){
        mythread.join();
    }
    if(mythread.joinable()){
        mythread.join();
    }
}

int main()
{
    test();
    std::vector<std::thread *> threadList;
    std::vector<std::string> vectest;

    for(int i = 0; i < 10; i++){
        std::thread *a = new std::thread(MyWorkThread()); 

        threadList.push_back(a);
    }

    std::for_each(threadList.begin(), threadList.end(), std::mem_fn(&std::thread::join));
    return 0;
}
