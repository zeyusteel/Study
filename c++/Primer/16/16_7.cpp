//编写一个 constexpr 模版，返回给定数组的大小。

#include <iostream>
template<typename T, unsigned N> constexpr
unsigned size(const T (&arr)[N])
{
	return N;
}

template<typename T1>
unsigned _size(const T1 &tt)
{
    std::cout << tt[3] << std::endl;
    return sizeof(tt);
}

int main(int argc, char const *argv[])
{
    int a[5] = {0,1,2,3,4};
    std::cout << size(a) << std::endl;
    std::cout << _size(a) << std::endl;
    return 0;
}
