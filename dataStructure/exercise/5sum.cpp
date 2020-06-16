#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool sum(vector<vector<long long>> &nums){
    vector<vector<long long>::iterator> curNum;
    for(int i = 0; i < 5; ++i){
        curNum.push_back(nums[i].begin());
    }
    long long curSum = 0;
    while(curSum< 2018){
        curSum = 0;
        for(int i = 0; i < 5; ++i){
            curSum += *(curNum[i]);
        }
        cout << curSum << endl;
        int stop;
        cin >> stop;
        vector<long long>::iterator curMin = curNum[0];
        int index = 0;
        for(int i = 0; i < 5; ++i){
            if(curNum[i] == nums[i].end())
                continue;
            if(*(curNum[i]) - *(curNum[i]-1)  < *curMin - *(curMin-1)){
                curMin = curNum[i];
                index = i;
            }
        }
        curNum[index] += 1;
    }
    if(curSum == 2018)
        return true;
    else
    {
        return false;
    }
    

}

int main()
{
    int t = 0;
    cin >> t;
    for(int i = 0; i < t; ++i){
        int n = 0;
        cin >> n;
        vector<vector<long long>> nums(5, vector<long long>(n));
        for(int j = 0; j < 5; ++j){
            long long cur = 0;
            for(int k = 0; k < n; ++k){

                cin >> cur;
                nums[j][k] = cur;
            }
            sort(nums[j].begin(), nums[j].end());
        }
        if(sum(nums)) cout << "Yes" << endl;
        else cout << "No" << endl;

        cout << "debug:" <<endl;
        for(auto x: nums){
            for(auto y: x){
                cout << y << " ";
            }
            cout << endl;
        }
        cout << "---------" << endl;
            
    }
}
