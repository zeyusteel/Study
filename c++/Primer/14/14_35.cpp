#include <iostream>
#include <string>
#include <vector>

class GetInput
{
public:
	GetInput(std::istream &i = std::cin) : is(i) {}
	std::string operator()() const
	{
		std::string str;
		std::getline(is, str);
		return is ? str : std::string();
	}

private:
	std::istream &is;
};


class IsEqual
{
	int value;
public:
	IsEqual(int v) : value(v) {}
	bool operator()(int elem)
	{
        std::cout << "abc" << std::endl;
		return elem == value;
	}
};

int main()
{
#if 0
	GetInput getInput;
	std::cout << getInput() << std::endl;
#endif

    std::vector<int> vec = { 3, 2, 1, 4, 3, 7, 8, 6 };
	std::replace_if(vec.begin(), vec.end(), IsEqual(3), 5);
	for (int i : vec) std::cout << i << " ";
	std::cout << std::endl;
    IsEqual(5);
}