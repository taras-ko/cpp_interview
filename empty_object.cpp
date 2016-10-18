#include <iostream>
#include <memory>
#include <cstring>

using namespace std;

class MyString
{
    shared_ptr<char> _ptr;

public:
    MyString() = default;

    MyString(const char *str)
        : _ptr {new char[strlen(str) + 1], [](char *str){ cout << "deleting memory"; delete[] str; }}
    {

        ::strncpy(_ptr.get(), str, strlen(str) + 1);
    }

    MyString(const MyString& obj)
    {
        cout << "Copy constructor\n";
        _ptr = obj._ptr;
    }

    MyString& operator=(const MyString& obj)
    {
        cout << "operator=()\n";
        _ptr = obj._ptr;
    }

    ~MyString()
    {
        _ptr.reset();
    }

    friend std::ostream& operator<<(std::ostream& os, const MyString& my_string);
};

std::ostream& operator<<(std::ostream& os, const MyString& my_string)
{
    return os << my_string._ptr;
}

int main()
{
    MyString str1 {"one"};
    MyString str2 {str1};
    MyString str3 = str1;
    MyString str4;

    {
        MyString str5 = str3;
        cout << str5 << endl;
    }

    str4 = str4;

        cout << str1 << endl;
        cout << str2 << endl;
        cout << str3 << endl;
        cout << str4 << endl;
}
