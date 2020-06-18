#include <iostream>
#include <list>
#include <algorithm>
#include <numeric>
using namespace std;

void print(list<int> l){
    for(int x: l){
        cout << x << " ";
    }
    cout << endl;
}

int main()
{
    list<int> l {5,1,2,3,4,5,6,7};
    print(l);
    l.sort(greater<int>());
    print(l);
    l.reverse();
    print(l);
    int sum = accumulate(l.begin(), l.end(), 1);
    cout << sum << endl;

    print(list<int>(3, 4));
}
