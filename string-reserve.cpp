#include <iostream>
#include <queue>

using namespace std;

int main()
{
    queue<int> buf;

    cout << "Enter: ";
    char c;

    for(int i = 0; i<5; i++)
    {
        buf.push(i);
    }

    cout << "Buffer(" << buf.size() << "):";
    while (!buf.empty())
    {
        cout << " " << buf.front();
        buf.pop();
    }
    cout << endl;
}
