#include <iostream>
template<typename Printable>
std::ostream& print(std::ostream& os, Printable const& printable)
{
    return os << printable;
}
// recursion
template<typename Printable, typename... Args>
std::ostream& print(std::ostream& os, Printable const& printable, Args const&... rest)
{
    return print(os << printable << ", ", rest...);
}


int main(int argc, char const *argv[])
{
    return 0;
}
