#include <utility>

template <template <typename> class T, template<typename...> class P, typename... Args>
void foo()
{
    T<P<Args...> > t;
}

int main()
{

//    newDevice<InputDevice, PeriodicPoller<100>>
}
