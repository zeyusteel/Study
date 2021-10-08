#include <iostream>
#include <string>

template<typename T>
void test(T &t) {
    --t;
    std::cout << t << std::endl;
}


int main(int argc, char const *argv[])
{
    int a = 5;
    test(a);
    std::cout << a << std::endl;
    return 0;
}
