#include <iostream>
#include <vector>
#include <algorithm>

struct A
{
    template<typename Ret, typename... Args, typename... UArgs>
    void call(Ret (A::*func)(Args...), UArgs&&... args)
    {
        (this->*func)(std::forward<UArgs>(args)...);
#if 0
        for (auto obj : _observers)
        {
            (obj->*func)(std::forward<UArgs>(args)...);
        }
#endif
    }
    //std::vector<Class*> _observers;

    void func(const std::string& s)
    {
        std::cout << this << ": " << s << std::endl;
    }
    void func(const double d)
    {
        std::cout << this << ": " << d << std::endl;
    }
};

struct foo
{
};

int main()
{
    A l;

    //l._observers = { &f1, &f2 };

#if 0
    l.call(&foo::func, "hello");
    l.call(&foo::func, 0.5);
#endif

    l.call<void, const std::string&>(&A::func, "hello");
    l.call<void, double            >(&foo::func, 0.5);

    return 0;
}
