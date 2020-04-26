#include "std_lib_facilities.h"
constexpr double pi = 3.14;
int main()
{
    //const:获得一个编译时无法计算结果的静态值。
    //constexpr:编译时可以算出结果的静态值
    constexpr int max = 20;
    cout << max << endl;
    int i = 5;
    const int *j = &i;
    cout << *j << endl;
    i = 10;
    cout << *j << endl;
    cout << pi << endl;
    // char{value} prevents narrowing
    // char(value) not
    cout << char('a' +2.5) << endl;
}