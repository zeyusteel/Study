//编写程序，从cin读取一组数，输出其和。
#include <iostream>

int main(int argc, char const *argv[])
{
    int sum = 0;
    for (int value = 0; std::cin >> value; ) //ctrl + d 停止
        sum += value;
    std::cout << sum << std::endl;
    return 0;
}

