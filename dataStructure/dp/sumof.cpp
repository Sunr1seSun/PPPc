#include <iostream>
#include <vector>

using namespace std;

int func(int n){
    if(n <= 2) return 1;
    vector<int> dp(n+1);
    dp[0] = dp[1] = dp[2] = 1;
    dp[3] = 2;
    for(int i = 4; i <= n; ++i){
        dp[i] = dp[i-1] + dp[i-3] + dp[i-4];
    }
    return dp[n];
}


int main()
{
    cout << func(1000);

    return 0;
}
