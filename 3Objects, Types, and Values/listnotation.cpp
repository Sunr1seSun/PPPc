#include "std_lib_facilities.h"
int main()
{
    // 使用列表初始化可以提示类型转换warning
    int a {0x21};
    char b {0x22};
    int c = b;
    cout << hex << "a == " << a <<endl;
    cout << hex << "b == " << b <<endl;
    cout << hex << "c == " << c <<endl;
}