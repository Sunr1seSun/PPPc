#include <iostream>

using namespace std;

int main()
{
    long long i = 0;
    cin >> i;
    while(true){
        if(i % 7 == 0)
            i /= 7;
        else if(i % 5 == 0)
            i /= 5;
        else if(i % 2 == 0)
            i /= 2;
        else
            break;
    }
    if(i == 1) cout << "1";
    else cout << "0";
}
