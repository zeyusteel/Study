//指出下列哪些输出语句是合法的（如果有的话）：
#include <iostream>

int main(){
    std::cout << "/*";
    std::cout << "*/";
    std::cout << /* "*/" */;   //不合法要改成 std::cout << /* "*/" */";
    std::cout << /* "*/" /* "/*" */;
}