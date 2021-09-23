#include <string>
#include <iostream>
#include <vector>
#include <algorithm>

class HasPtr 
{
public:
    friend void swap(HasPtr&, HasPtr&);
    friend bool operator<(const HasPtr &lhs, const HasPtr &rhs);

    HasPtr(const std::string &s = std::string()) 
        : ps(new std::string(s)), i(0) 
    { std::cout << "construct" << std::endl;}

    HasPtr(const HasPtr &hp) 
        : ps(new std::string(*hp.ps)), i(hp.i) 
    { 
        std::cout << "copy" << *hp.ps << std::endl;
    }

    HasPtr& operator=(HasPtr tmp) 
    {
        std::cout << " == " << std::endl;
        this->swap(tmp);
        return *this;
    }

    ~HasPtr() 
    {
        delete ps;
    }

    void swap(HasPtr &rhs) 
    {
        using std::swap;
        swap(ps, rhs.ps);
        swap(i, rhs.i);
        std::cout << "call swap(HasPtr &rhs)" << std::endl;
    }

    void show() const
    { 
        std::cout << *ps << std::endl; 
    }
private:
    std::string *ps;
    int i;
};

void swap(HasPtr& lhs, HasPtr& rhs)
{
    std::cout << "test" << std::endl;
    lhs.swap(rhs);
}

bool operator<(const HasPtr &lhs, const HasPtr &rhs)
{
    return *lhs.ps < *rhs.ps;
}

int main(int argc, char const *argv[])
{
    std::vector<HasPtr> vec;    
    HasPtr ptr1("aaa"), ptr2("bbb"), ptr3("ccc") ,ptr4("ddd");
    vec.push_back(ptr4);
    vec.push_back(ptr3);
    vec.push_back(ptr2);
    vec.push_back(ptr1);

    std::sort(vec.begin(), vec.end());
    return 0;
}
