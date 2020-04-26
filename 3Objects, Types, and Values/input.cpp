#include "std_lib_facilities.h"

int main()
{
    cout << "please enter your first name and age(followed by 'enter'):\n";
    string first_name;
    double age;
    cin >> first_name >> age;
    cout << "Hello, " << first_name << " (age " << age*12 << " months)\n";
}