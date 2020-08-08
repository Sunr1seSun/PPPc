#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
int func(vector<int> &a){
    sort(a.begin(), a.end());
    reverse(a.begin(), a.end());
    int one = 0, two = 0;
    int res = 0;
    for(int i = 0; i < a.size(); ++i){
        res += a[i];
        cout << res << endl;
        if(one <= two){
            one += a[i];
        }else if(one > two){
            two += a[i];
        }
        if(one == two){
            res = 0;
        }
    }
    return res;
}

int main()
{
    int t = 0;
    cin >> t;
    for(int i = 0; i < t; ++i){
        int n = 0;
        cin >> n;
        vector<int> a(n);
        for(int j = 0; j < n; ++j){
            cin >> a[j];
        }
        cout << func(a);
        
    }
}