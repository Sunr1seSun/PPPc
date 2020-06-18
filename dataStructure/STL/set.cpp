#include <iostream>
#include <set>

using namespace std;

void print(multiset<int> l){
    for(int x: l){
        cout << x << " ";
    }
    cout << endl;
}

int main()
{
    multiset<int> s {1,2,3,4,5,5,5,5,5,5};
    print(s);
    print(s);
    auto x = s.equal_range(5);
    s.erase(x.first, x.second);
    print(s);
}
