#include <utility>
#include <string>
#include <iostream>

using namespace std;

class Base {
public:
  Base(int n) {cout << n << endl;}
  Base(string s) {cout << s << endl;}
};

class Base2 {
public:
  Base2(float f) {cout << f << endl;}
};

template <class T>
class Specific: public T {
public:
    template<typename... Args>
    Specific<T>(Args&&... args)
        : T(std::forward<Args>(args)...)
    {}
};

template <class T>
class Specific2 : public Specific<T> {
public:
    template<typename... Args>
    Specific2(Args&&... args)
        : Specific<T>(std::forward<Args>(args)...)
    {}
};

Specific<Base> s(5);
Specific<Base> s2("sldfkj");

Specific<Base2> s3(5.6);

Specific2<Base2> s4{6.7};

//void printOut(Specific const& b);
//void printOut(std::string const& s);

int main()
{
}
