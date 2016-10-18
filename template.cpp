#include <iostream>
#include <string>
#include <map>

using namespace std;

int main()
{
    std::map<std::string, int> m {
        {"Hello", 1},
        {"World", 2}
    };

    cout << m.find("Hello")->second << endl;
}

