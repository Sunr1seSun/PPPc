#include "std_lib_facilities.h"
int main()
{
    int i = 97;
    char c = 'a';
    while(i < 123){
        cout << c << " " << i << endl;
        ++i;
        ++c;
    }
    for(int i=122; i>=97; --i){
        --c;
        cout << c << " " << i << endl;
    }
}