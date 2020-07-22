#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

void backTrack(vector<int> &cur, int n, int level){
    if(level == n){
        string res;
        for(int c: cur){
            res += to_string(c) + " ";
        }
        res.pop_back();
        //cout << res << endl;
        return;
    }
    for(int i = 1; i <= n; ++i){
        if(level > 0){
            int prev = *(cur.end()-1);
            if(find(cur.begin(),cur.end(),i) != cur.end() || abs(prev - i) <= 1)
                continue;
        }
        cur.push_back(i);
        backTrack(cur, n, level+1);
        cur.pop_back();
    }
}

void func(int n){
    vector<int> temp;
    backTrack(temp, n, 0);
}

int main()
{
    int start = clock();
    func(10);
    int end = clock();
    cout << "test:"<< (end-start) / CLOCKS_PER_SEC * 1000 << "ms" << endl;
}
