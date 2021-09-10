#include <iostream>
#include <thread>
#include <string>

//g++ send_ref.cpp -std=c++11 -lpthread

void test(int a, std::string str)
{
    std::cout << a << "--" << str << std::endl;
}

void test_pointerThread(int *p){
    std::cout << "test" << *p << std::endl;

    std::chrono::milliseconds last(3000);
    std::this_thread::sleep_for(last);

    *p = 10;
    std::cout << "test" << *p << std::endl;
}
// 指针指为空也没有发现问题
void test_pointer(){
    int *a = new int();
    *a = 5;
    std::cout << "main" << *a << std::endl;
    std::thread abc(test_pointerThread, a);
    abc.detach();
    std::cout << "delete a" << std::endl;
    delete a;
    a = NULL;
}
//如果不用std::ref 这里参数必须用const int & 不然编译不过
void test_refThread(const int &i)
{
    int &p = const_cast<int &>(i);
    p++;
    std::cout << "test_refThread" << p << std::endl;
}

void test_ref()
{
    int a = 7;
    std::thread abc(test_refThread, a);   
    abc.join();
    std::cout << a << std::endl;

    std::thread def(test_refThread,std::ref(a));
    def.join();

    std::cout << a << std::endl;
}


class MyClass{
    public:
    MyClass(){}
    MyClass(const MyClass &obj){}
    void test(int a){
        std::cout << "MyClass" << a << std::endl;
    }
};

void test_class(){
    MyClass myClass;
    std::thread myThread(&MyClass::test, &myClass,7);
    myThread.join();
}

 int main(int argc, char const *argv[])
 {
    //test_pointer();
    //test_ref();
    test_class();

    std::chrono::milliseconds last(5000);
    std::this_thread::sleep_for(last);

    return 0;
 }
 