//定义一个 Employee 类，它包含雇员的姓名和唯一的雇员证号。为这个类定义默认构造函数，以及接受一个表示雇员姓名的 string 的构造函数。每个构造函数应该通过递增一个 static 数据成员来生成一个唯一的证号。
#include <string>
#include <iostream>
using std::string;

class Employee
{
public:
	Employee();
	Employee(const string& name);
    Employee(const Employee&) = delete;
    Employee& operator=(const Employee &) = delete;

	const int id() const { return id_; }

private:
	string name_;
	int id_;
	static int s_increment;
};

int Employee::s_increment = 0;

Employee::Employee()
{
	id_ = s_increment++;
}

Employee::Employee(const string& name)
{
	id_ = s_increment++;
	name_ = name;
}

int main() 
{
    Employee yee;
    return 0;
}



