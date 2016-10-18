#include <iostream>
#include <map>
#include <memory>

using namespace std;

class X {};

map<int, unique_ptr<X>> m
{
};

int main()
{
    m.emplace(0, unique_ptr<X>(new X));

//    m.insert(std::make_pair(0, std::unique_ptr<X>(new X())));
}
