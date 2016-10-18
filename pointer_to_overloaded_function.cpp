#include <iostream>
#include <boost/bind.hpp>

using namespace std;

struct A
{
  void foo (int i) {} // choice
  void foo (double i) {}
  void exec (void (A::*fun_ptr)(int)) {
      (this->*fun_ptr)(1);
  }
  void exec_foo1() {
      exec(A::foo);
  }
};

template<typename ObjT>
void ReceiveFuncPtr (ObjT& o, void (ObjT::*fun_ptr)(int))
{
 (o.*fun_ptr)(1);
}

int main ()
{
  A obj;
  ReceiveFuncPtr(obj, &A::foo); // don't want typecast here
}
