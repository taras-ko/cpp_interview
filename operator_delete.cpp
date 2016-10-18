#include <iostream>

using namespace std;

class A
{
public:
    A()
    {
        cout << "A()\n";
    }
    ~A()
    {
        cout << "~A()\n";
    }
};

class B : public A
{
public:
    B()
    {
        throw 1;
    }

    ~B()
    {
    }
};

int main()
{
    try
    {
    B b;
    }
    catch (...)
    {
    }
    return 0;
}
