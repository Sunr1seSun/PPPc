#include <iostream>
#include <algorithm>

using namespace std;
void work(char c)
{
    cout << c << endl;
}

int main()
{
    string s = "sunrise";
    for_each(s.begin(), s.end(), work);
    cout << s.at(3) << endl;
    s.append(1,'a');
    s += 'a';
    cout << s.find('b') << endl;
    s.erase(3,1);
    cout << s << endl;
}
