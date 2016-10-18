#include <iostream>

using namespace std;

template <class T>
class move_ptr
{
private:
    T* ptr;
public:
    explicit move_ptr(T* p = 0) : ptr(p) {}

    ~move_ptr() { delete ptr; }

    move_ptr(move_ptr&& p)
        : ptr(p.ptr)
    {
        p.ptr = 0;
    }

    move_ptr& operator=(move_ptr&& p)
    {
        std::swap(ptr, p.ptr);
        return *this;
    }

    T& operator*() const { return *ptr; }
    T* operator->() const { return ptr; }
    T* operator&() const { return ptr; }
};

int main()
{
    int* pi { new int(10) };
    cout << pi << endl;

    //move_ptr<int>& lv_mp = move_ptr<int>(new int(20));
    move_ptr<int>&& rv_mp = move_ptr<int>(new int(20));

    move_ptr<int> mp1 { pi };
    move_ptr<int> mp2 { std::move(mp1) };
    move_ptr<int> mp3;
    move_ptr<int> mp4;

    mp4 = std::move(move_ptr<int>(new int(30)));

    mp3 = std::move(mp2);

    cout << &mp1 << endl;
    cout << &mp2 << endl;
    cout << &mp3 << endl;
    cout << &mp4 << endl;
}
