//编写行为类似标准库 find 算法的模版。函数需要两个模版类型参数，
//一个表示函数的迭代器参数，另一个表示值的类型。使用你的函数在一个 vector<int> 和一个list<string>中查找给定值。
#include <vector>
#include <iostream>
namespace abc {
template<typename Iterator, typename Value>
Iterator find(Iterator first, Iterator last, const Value& value)
{
	for ( ; first != last && *first != value; ++first);
	return first;
}
}

int main(int argc, char const *argv[])
{
    std::vector<int> vec{1,3,5,7};
    auto itor = abc::find(vec.begin(), vec.end(), 5);
    std::cout << *itor << std::endl;

    return 0;
}


