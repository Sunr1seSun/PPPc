#include "std_lib_facilities.h"
int main()
{
    cout << "What's your name?" << endl;
    string first_name;
    cin >> first_name;
    cout << "Hello, " << first_name;
    string friend_name {"yangqing"};
    cout << "Have you seen " << friend_name << " lately?" << endl;
    char friend_sex {0};
    cout << "m == male, f = female" << endl;
    while(cin >> friend_sex){
        if(friend_sex == 'f'){
            cout << "she" << endl;
            break;
        }else if(friend_sex == 'm'){
            cout << "he" << endl;
            break;
        }else{
            cout << "wrong!" << endl;
        }
    }
    cout << "How old?" << endl;
    int age;
    cin >> age;
    if(age > 110 || age < 0)
        simple_error("you're kidding!");
    else if(age < 12)
        cout << "Next year you will be " << age+1 << endl;
    else if(age == 17)
        cout << "Next year you will be able to vote." << endl;
    
}