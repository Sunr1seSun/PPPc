#include <iostream>
#include <deque>

using namespace std;

int main()
{
    deque<int> q {1,2,3,4,5};
    auto it = q.begin();
    q.push_front(2);
    cout << q[0] << endl;
    cout << *it;
}
