#include"std_lib_facilities.h"

class Base
{
protected:
    int m_a;
public:
    Base(int a):m_a(a){}
};
class Derived:public Base
{
protected:
    int m_b;
    int m_c;
public:
    Derived(int a, int c):m_c(c), Base(a), m_b(m_a+m_c){}
};
int main()
{
    Derived a1(1,10);
}

