#include <iostream>

using namespace std;

class A
{
public:
    virtual void log()
    {
        cout << "A" << endl;
    }
};

class B : public A
{
public:
    virtual void log() override
    {
        cout << "B" << endl;
    }
};

int main()
{
    B b;
    A a = b;
    a.log();
    return 0;
}