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
    //int m_c;
    int m_b;
    int m_c;
public:
    Derived(int a, int c):Base(a), m_b(a+c), m_c(c){
        cout << m_a << endl;
        cout << m_b << endl;
        cout << m_c << endl;
    }
};


int main()
{
    Derived a1(1,10);
}

