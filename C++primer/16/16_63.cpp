#include <iostream>

template<typename T>
void test(const T& t) {
    std::cout << t << std::endl;
}

template<>
void test(const char* const &t){
    std::cout << t << "special" << std::endl;
}

template<size_t N>
void test(const char (&a)[N]) {
    std::cout << a << "[]" << std::endl;
}

int main(int argc, char const *argv[])
{
    char aa[256] = "hhh";
    const char *p = "abc";   
    test(p);

    return 0;
}
