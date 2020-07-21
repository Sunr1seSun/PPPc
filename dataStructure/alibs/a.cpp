#include <iostream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

bool isPrime(int n){
    for(int i = 2; i < sqrt(n); ++i){
        if(n % i == 0){
            return false;
        }
    }
    return true;
}

void helper(unsigned long long n, unsigned long long k){
    unsigned long long a = 1, b = 2, c = n/k;
    unsigned long long low = k, mid = b*k, high = c*k;
    for(a; a*k < n; ++a){
        if(!isPrime(a))
            continue;
        while(b < c){
            //cout << a << b << c << endl;
            if(!isPrime(b)){
                ++b;
                continue;
            }
            if(!isPrime(c)){
                --c;
                continue;
            }
            unsigned long long cur = a*k + b*k + c*k;
            if(cur == n){
                cout << a*k << " " << b*k << " " << c*k << endl;
                return;
            }
            else if(cur < n)
                ++b;
            else
                --c;
        }
    }
    cout << "-1" << endl;
    return;
}

int main()
{
    int t;
    cin >> t;
    vector<vector<int>> vec(t, vector<int>(2));
    //0:n 1:k
    //for(int i =0; i < t; ++i){
    //    cin >> vec[i][0] >> vec[i][1];
    //}
    /*
    int i = 0;
    while(cin >> vec[i][0] >> vec[i][1]){
        ++i;
    }
    for(auto cur: vec){
        int n = cur[0];
        int k = cur[1];
        helper(n, k);
        
    }*/
    int count = 0;
    unsigned long long n, k;
    for(int i = 0;i < t; ++i){
        cin >> n >> k;
        helper(n, k);
    }
    for(auto x: vec){
        cout <<"n = " << x[0] << " k = " << x[1] << endl;
    }
    return 0;
}
