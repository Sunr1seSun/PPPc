#include "std_lib_facilities.h"
int square(int n);


int main()
{
    for(int i=1; i<100; ++i){
        cout << i << " " << square(i) << endl;
    }
}

int square(int n)
{
    int res = 0;
    for(int i=1; i <= n; ++i){
        res += n;
    }
    return res;
}