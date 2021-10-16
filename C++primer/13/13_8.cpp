#include <string>
#include <iostream>

class HasPtr {
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) { 
        std::cout << "construct" << std::endl;
    }
    HasPtr(const HasPtr &hp) : ps(new std::string(*hp.ps)), i(hp.i) { 
        std::cout << "copy" << std::endl;
    }
    HasPtr& operator=(const HasPtr &hp) {
        std::cout << "operator = " << std::endl;
        std::string *new_ps = new std::string(*hp.ps);
        delete ps;
        ps = new_ps;
        i = hp.i;
        return *this;
    }
    ~HasPtr() {
        delete ps;
    }
private:
    std::string *ps;
    int i;
};

int main(int argc, char const *argv[])
{
    HasPtr ptr;
    HasPtr ptr2 = ptr;


    return 0;
}
