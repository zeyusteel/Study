//假定numbered 定义了一个拷贝构造函数，能生成一个新的序列号。这会改变上一题中调用的输出结果吗？
//如果会改变，为什么？新的输出结果是什么？
#include <iostream>

class numbered {
public:
    numbered() {
        mysn = unique++;
    }
	numbered(const numbered& n)
	{
		mysn = unique++;
	}

    int mysn;
    static int unique;
};

int numbered::unique = 10;

void f(numbered s) {
    std::cout << s.mysn << std::endl;
}

int main()
{
    numbered a, b = a, c = b;
    f(a);
    f(b);
    f(c);
}

