#include <string>
#include <iostream>

class HasPtr {
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0) { }
    HasPtr(const HasPtr &hp) : ps(new std::string(*hp.ps)), i(hp.i) { }
    HasPtr& operator=(const HasPtr &hp) {
        auto new_p = new std::string(*hp.ps);
        delete ps;
        ps = new_p;
        i = hp.i;
        return *this;
    }
    ~HasPtr() {
        delete ps;
    } 

    inline void swap(HasPtr &ptr) noexcept {
        using std::swap;
        swap(ps, ptr.ps);
        swap(i, ptr.i);
    }
    
    void show() { std::cout << *ps << std::endl; }
private:
    std::string *ps;
    int i;
};

namespace std {
    template<>
    void swap<HasPtr>(HasPtr &ptrA, HasPtr &ptrB) {
        std::cout << "----std::swap----" << std::endl;
        ptrA.swap(ptrB);
    }
}

void swap(HasPtr& lhs, HasPtr& rhs) {
    lhs.swap(rhs);
    std::cout << "----test::swap----" << std::endl;
}

int main() {
    HasPtr a("aaa");
    HasPtr b("bbb");
    using std::swap;
    swap(a, b);
}
