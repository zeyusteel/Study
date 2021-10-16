//编写一段程序，使用范围for语句将字符串内所有字符用X代替。
#include <iostream>
#include <string>

int main(int argc, char const *argv[])
{
    std::string str = "hhhh aaa";

    for(auto &ch : str){
        ch = 'X';
    }

    std::cout << str << std::endl;
    return 0;
}


