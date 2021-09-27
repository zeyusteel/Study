#include <iostream>
#include <functional>
//g++ test.cpp -std=c++11

class MyClass
{
public:
	MyClass(){}
	static int test(int iType){
		std::cout << "test" << iType << std::endl;
		return 0;
	}
	int _test(int iType){
		std::cout << "_test" << iType << std::endl;
		return 0;
	}

};

typedef int (MyClass::*func)(int);
typedef int (*_func)(int);
using fun_c11 = int(*)(int);
typedef decltype(MyClass::test) *decf; //decltype 不会保存将函数转换成函数指针
typedef std::function<int(int)> funct;

int main(int argc, char *argv[])
{
	MyClass myclass;
	MyClass *pClass = new MyClass();

	func f = &MyClass::_test;

	(myclass.*f)(15);
	(pClass->*f)(15);

	_func ff = MyClass::test;
	ff(30);

	fun_c11 f11 = MyClass::test;
	f11(45);

	decf fdec = MyClass::test;
	fdec(60);

	funct ft = std::bind(&MyClass::_test, &myclass, std::placeholders::_1);
	ft(75);

	return 0;
}
