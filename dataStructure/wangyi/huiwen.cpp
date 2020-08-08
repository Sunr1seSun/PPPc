#include <string>
#include <iostream>
#include <algorithm>
using namespace std;
bool isHuiwen(const string &s) {
    int l = 0;
    int r = s.size()-1;
    while(l < r){
        if(s[l++] != s[r--]){
            return false;
        }
    }
    return true;
}
int main()
{
    string s;
    cin >> s;
    int n = s.size();
    
    for(int i = 0; i < n; ++i){
        if(isHuiwen(s.substr(i, n-i))){
            cout << i << endl;
            string temp = s.substr(0, i);
            reverse(temp.begin(), temp.end());
            s += temp;
            break;
        }
    }
    cout << s << endl;
}