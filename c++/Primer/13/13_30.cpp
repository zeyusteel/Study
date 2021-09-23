#include <string>
#include <iostream>

class HasPtr {
public:
    friend void swap(HasPtr&, HasPtr&);
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) { }
    HasPtr(const HasPtr &hp) : ps(new std::string(*hp.ps)), i(hp.i) { 
        std::cout << "copy from" << *hp.ps << std::endl;
    }
    HasPtr& operator=(const HasPtr &hp) {
        std::cout << *ps << " = " << *hp.ps << std::endl;
        auto new_p = new std::string(*hp.ps);
        delete ps;
        ps = new_p;
        i = hp.i;
        return *this;
    }
    ~HasPtr() {
        delete ps;
    } 
    
    void show() { std::cout << *ps << std::endl; }
private:
    std::string *ps;
    int i;
};

inline
void swap(HasPtr& lhs, HasPtr& rhs)
{
    using std::swap;
    swap(lhs.ps, rhs.ps);
    swap(lhs.i, rhs.i);
    std::cout << "call swap(HasPtr& lhs, HasPtr& rhs)" << std::endl;
}

int main(int argc, char const *argv[])
{
    HasPtr ptr1("aaa"), ptr2("bbb"); 
    std::swap(ptr1, ptr2);
    swap(ptr1, ptr2);
    return 0;
}
