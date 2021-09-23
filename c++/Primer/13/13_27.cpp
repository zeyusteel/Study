#include <string>
//定义你自己的使用引用计数版本的 HasPtr。
/*
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
private:
    std::string *ps;
    int i;
};
*/

class HasPtr {
public:
    HasPtr(const std::string &s = std::string()) : ps(new std::string(s)), i(0), use(new size_t(1)) { }
    HasPtr(const HasPtr &hp) : ps(hp.ps), i(hp.i), use(hp.use) { ++*use; }
    HasPtr& operator=(const HasPtr &rhs) {
        ++*rhs.use;
        if (--*use == 0) {
            delete ps;
            delete use;
        }
        ps = rhs.ps;
        i = rhs.i;
        use = rhs.use;
        return *this;
    }
    ~HasPtr() {
        if (--*use == 0) {
            delete ps;
            delete use;
        }
    } 
private:
    std::string *ps;
    int i;
    size_t *use;
};
