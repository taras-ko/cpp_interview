#include <iostream>

using namespace std;

class SmartGMainLoop
{
    static int m_cnt;
public:
    SmartGMainLoop() = default;
    SmartGMainLoop(SmartGMainLoop& loop)
    {
        cout << "SmartGmainLoop&(): cnt++" << endl;
    }

    SmartGMainLoop& operator=(SmartGMainLoop&)
    {
        m_cnt++;
        return *this;
    }
    void unref()
    {
        cout << "cnt--()" << endl;
        m_cnt--;
    }
    void print() const
    {
        cout << "cnt: " << m_cnt << endl;
    }
};

int SmartGMainLoop::m_cnt {0};

void foo(SmartGMainLoop& loop)
{
    SmartGMainLoop local_loop;

    local_loop = loop;

    local_loop.print();
}

int main()
{
    SmartGMainLoop loop;

    foo(loop);
}
