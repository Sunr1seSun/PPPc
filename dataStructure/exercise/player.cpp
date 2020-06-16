#include <iostream>
#include <vector>

using namespace std;

void dfs(vector<pair<int, int>> &order, int x, int y, bool& flag, int i){
    if(x == 18 && y == 18 && i == order.size()){
        flag = 1;
        return;
    }
    if(i >= order.size())
        return;
    if(x > 18 || y > 18 || x < 0 || y < 0)
        return;
    if(order[i].first == 1){
        if(order[i].second != 0)
            dfs(order, x+order[i].second, y, flag, i+1);
        else{
            for(int j = 1; j <= 18; ++j){
                dfs(order, x+j, y, flag, i+1);
            }
        }
    }
    if(order[i].first == -1){
        if(order[i].second != 0)
            dfs(order, x-order[i].second, y, flag, i+1);
        else{
            for(int j = 1; j <= 18; ++j){
                dfs(order, x-j, y, flag, i+1);
            }
        }
    }
    if(order[i].first == 2){
        if(order[i].second != 0)
            dfs(order, x, y+order[i].second, flag, i+1);
        else{
            for(int j = 1; j <= 18; ++j){
                dfs(order, x, y+j, flag, i+1);
            }
        }
    }
    if(order[i].first == -2){
        if(order[i].second != 0)
            dfs(order, x, y-order[i].second, flag, i+1);
        else{
            for(int j = 1; j <= 18; ++j){
                dfs(order, x, y-j, flag, i+1);
            }
        }
    }
    
}

int main()
{
    int n = 0;
    cin >> n;
    vector<pair<int, int>> order;
    int ins1, ins2;
    for(int i = 0; i < n; ++i){
        cin >> ins1 >> ins2;
        order.push_back(pair<int, int>(ins1, ins2));
    }
    int x=0, y=0;
    bool flag = 0;
    dfs(order, x, y, flag, 0);
    if(flag) cout << "Yes";
    else cout << "No";
    for(auto x: order){
            cout << x.first << " " << x.second;
        cout << endl;
    }

}
