#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <iostream>

using namespace std;

template <typename T>
class LockingPtr {
public:
    LockingPtr(volatile T& obj, std::mutex& mtx)
        : pObj_{const_cast<T*>(&obj) }
        , pMtx_{&mtx}
    {
        mtx.lock();
    }
    ~LockingPtr()
    {
        pMtx_->unlock();
    }
    T& operator*()
    {
        return *pObj_;
    }
    T* operator->()
    {
        return pObj_;
    }
    LockingPtr(const LockingPtr&) = delete;
    LockingPtr& operator=(const LockingPtr&) = delete;
private:
    T* pObj_;
    std::mutex* pMtx_;
};

class SyncInt
{
private:
    volatile int data_;
    std::mutex mtx_;
public:
    SyncInt(int i) : data_{i} {}
    SyncInt& operator++()
    {
        LockingPtr<int> lpInt(data_, mtx_);
        ++(*lpInt);
        return *this;
    }
    bool operator< (int rhs)
    {
        LockingPtr<int> lpInt(data_, mtx_);
        return *lpInt < rhs;
    }
    void stream_to(ostream& os)
    {
        LockingPtr<int> lpInt(data_, mtx_);
        os << *lpInt;
    }
    friend ostream& operator<<(ostream& os, const SyncInt& obj);
};

inline ostream& operator<<(ostream& os, SyncInt& obj)
{
    obj.stream_to(os);
    return os;
}

void increment(SyncInt& val)
{
    while (++val < 10)
    {
        cout << std::this_thread::get_id() << ": " << val << endl;
    }
}

int main()
{
    SyncInt val {0};
    std::thread t1(increment, std::ref(val));
    std::thread t2(increment, std::ref(val));

    t1.join();
    t2.join();
}

