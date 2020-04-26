#include "std_lib_facilities.h"

class Base
{
public:
    virtual void display() const
    {cout << "I am Base class !" << endl;}
    virtual ~Base(){}
};
class Derive: public Base
{
public:
    virtual void display()
    {cout << "I am Derive class !" << endl;}
    virtual ~Derive(){}
};

class cAAA
{
public:
    cAAA(){};
    virtual ~cAAA(){};
private:
    static int m1;
    int m2;
    char m3[10];
};

int myFunc()
{
    static int i;
    ++i;
    cout << i << endl;
}
int main()
{
    for(int i=0; i <10; ++i){
        myFunc();
    }
}