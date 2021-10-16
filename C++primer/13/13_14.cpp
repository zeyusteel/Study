#include <iostream>
/*
假定 numbered 是一个类，它有一个默认构造函数，能为每个对象生成一个唯一的序号，保存在名为 mysn 的数据成员中。假定 numbered 使用合成的拷贝控制成员，并给定如下函数：
void f (numbered s) { cout << s.mysn < endl; }
则下面代码输出什么内容？
numbered a, b = a, c = b;
f(a); f(b); f(c);
*/

class numbered
{
public:
	numbered()
	{
		mysn = unique++;
	}

	int mysn;
	static int unique;
};

int numbered::unique = 10;

void f(numbered s)
{
	std::cout << s.mysn << std::endl;
}

int main()
{
	numbered a, b = a, c = b;
	f(a);
	f(b);
	f(c);
}