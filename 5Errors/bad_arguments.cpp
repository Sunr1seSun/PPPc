#include "std_lib_facilities.h"
class Base
{
public:
    int m_x;
    Base(int val = 0):m_x(val){}
    Base(const Base& oth):m_x(oth.m_x){}

};

class Derived:public Base
{
public:
    int m_y;
    Derived(int val):Base(val),m_y(val){}
    Derived(const Derived& oth):m_y(oth.m_y){}

};

int main()
{
    Derived d1(10);
    Derived d2(d1);
    cout << d2.m_x << endl;
    cout << d2.m_y<<endl;
}