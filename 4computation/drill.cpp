#include "std_lib_facilities.h"
int main()
{
    int first;
    int second;
    while(1){
        cin >> first >> second;
        if(first > second){
            swap(first, second);
        }else if(first == second){
            cout << "equal" << endl;
            continue; 
        }
        cout << "the smaller value is:" << first << endl;
        cout << "the smaller value is:" << second << endl;
    }
}