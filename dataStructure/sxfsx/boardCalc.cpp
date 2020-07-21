#include <stdio.h>
#include <string.h>
#include <vector>
#include <queue>
#include <iostream>
using namespace std;

enum color {
    NONE, WHITE, BLACK,         //棋子颜色，NONE表示未落子
};
struct weiqi {
    enum color board[19][19];   //棋盘上每个位置的落子
};

// 计算(x,y)所在块区域
int calc(struct weiqi *wq, int x, int y)
{
    vector<vector<bool>> visited(19, vector<bool>(19));
    queue<pair<int, int>> q;
    q.push(pair<int, int>(y, x));
    enum color curColor = wq->board[y][x]; 
    while(!q.empty()){
        pair<int, int> cur = q.front();
        cout << "cur:" << cur.first << "," << cur.second << wq->board[cur.first][cur.second] <<endl;
        q.pop();
        visited[cur.first][cur.second] = true;
        if(cur.first> 0 && !visited[cur.first-1][cur.second] && wq->board[cur.first-1][cur.second] == curColor){
            q.push(pair<int, int>(cur.first-1, cur.second));
        }
        if(cur.first< 18 && !visited[cur.first+1][cur.second] && wq->board[cur.first+1][cur.second] == curColor){
            q.push(pair<int, int>(cur.first+1, cur.second));
        }
        if(cur.second>0 && !visited[cur.first][cur.second-1] && wq->board[cur.first][cur.second-1] == curColor){
            q.push(pair<int, int>(cur.first, cur.second-1));
        }
        if(cur.first< 18 && !visited[cur.first][cur.second+1] && wq->board[cur.first][cur.second+1] == curColor){
            q.push(pair<int, int>(cur.first, cur.second+1));
        }
    }
    int res = 0;
    for(auto x1: visited)
        for(auto x2: x1)
            if(x2)
                res += 1;
    return res;
}
int input(struct weiqi *wq, int *x, int *y)
{
    int row, col;
    int ret;
    char buf[80];
    
    for (row = 0; row < 19; ++row) {
        if (fgets(buf, sizeof(buf), stdin) == NULL)
            return -1;
        if (strlen(buf) < 19)
            return -1;
        for (col = 0; col < 19; ++col) {
            switch (buf[col]) {
            case '0':
                wq->board[row][col] = NONE;
                break;
            case '1':
                wq->board[row][col] = WHITE;
                break;
            case '2':
                wq->board[row][col] = BLACK;
                break;
            default:
                return -1;
            }
        }
    }
    ret = fscanf(stdin, "%d,%d\n", x, y);
    if (ret != 2)
        return -1;
    for (row = 0 ; row < 19; ++row) {
        for (col = 0; col < 19; ++col) {
            fprintf(stderr, "%d ", wq->board[row][col]);
        }
        fprintf(stderr, "\n");
    }
    fprintf(stderr, "x = %d, y = %d\n", *x, *y);
    return 0;
}

int main()
{
    struct weiqi wq;
    int x = 0, y = 0;
    int cnt;

    memset(&wq, 0, sizeof(wq));
    if (input(&wq, &x, &y) < 0) {
        fprintf(stderr, "error!\n");
        return 1;
    }
    cnt = calc(&wq, x, y);

    printf("%d\n", cnt);
    return 0;
}