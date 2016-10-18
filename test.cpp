#include <utility>
#include <string>
#include <iostream>

using namespace std;

class Base {
public:
  Base(int n) {cout << n << endl;}
  Base(string s) {cout << s << endl;}
};

class Specific: public Base {
public:
    template<typename... Args>
    Specific(Args&&... args)
        : Base(std::forward<Args>(args)...)
    {}
};

Specific s(5);
Specific s2("sldfkj");

//void printOut(Specific const& b);
//void printOut(std::string const& s);

int main()
{
}
