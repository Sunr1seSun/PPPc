#include <iostream>
#include <set>
using namespace std;

int main()
{
    set<int> s1 = {1,2,3,4,5,6,7,8,9};
    set<int> s2 = {1,2,3,4,5,6,7,8,8};
    cout << (s1 == s2) << endl;
}
