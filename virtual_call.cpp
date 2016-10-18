#include <iostream>
using namespace std;
class A
{
public:

    virtual void foo() = 0;
    A()
    {
        foo();
    }
    ~A()
    {
        cout << "~A()" << endl;
    }
};

class B : public A
{
public:

    virtual void foo() { cout << "B::foo()" << endl;}
    B()
    {
        foo();
    }
};

main()
{
   A* pa = new A;
   delete pa;
}
