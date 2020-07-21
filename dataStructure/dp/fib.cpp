#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

#define LAST_TIME(begin, end) (end-begin) / CLOCKS_PER_SEC * 1000

int fib(int n){
    if(n == 1 || n == 2)
        return 1;
    else
        return fib(n-1) + fib(n-2);
}

int fib2(int n){
    if(n ==1 || n == 2)
        return 1;
    vector<int> dp(n+1);
    dp[1] = 1;
    dp[2] = 1;
    for(int i = 3; i <= n; ++i){
        dp[i] = dp[i-1] + dp[i-2];
    }
    return dp[n];
}

int main()
{
    int start,end;
    start = clock();
    cout << fib(42) << endl;
    end = clock();
    cout << "fib:"<< LAST_TIME(start, end) << "ms" << endl;
    
    start = clock();
    cout << fib2(42) << endl;
    end = clock();
    cout << "fib2:"<< LAST_TIME(start, end) << "ms" << endl;
}
