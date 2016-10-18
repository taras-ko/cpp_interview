struct Foo
{
    Foo(int newId)
        : id(newId)
    {}
    int id;
};

struct Bar
{
    Bar(const Foo &newFoo)
        : foo(newFoo)
        , fooId(foo.id)
    {}

    const int fooId;
    const Foo& foo;
};

int main(int argc, char **argv)
{
    Foo foo(303);
    Bar bar(foo);
    return 0;
}
