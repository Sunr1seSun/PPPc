#include "std_lib_facilities.h"
int main()
{
    int a = 0x21;
    char b = a;
    int c = b;
    cout << hex << "a == " << a <<endl;
    cout << hex << "b == " << b <<endl;
    cout << hex << "c == " << c <<endl;
}