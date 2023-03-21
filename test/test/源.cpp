#include <iostream>
#include<algorithm>
#include<string.h>
using namespace std;
int ans = 0;
bool used[105][105];
int mapp[105][105];
int dx[] = { 1,0,-1,0 }, dy[] = { 0,1,0,-1 };
int n, m;
void dfs(int x, int y, int cnt) {
    ans = max(ans, cnt);
    used[x][y] = 1;
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i], ny = dy[i] + y;
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && mapp[nx][ny] < mapp[x][y] && !used[nx][ny])dfs(nx, ny, cnt + 1);
    }
    used[x][y] = 0;
   /* cout << x << '+' << y << endl;
    cout << "-----------------------------------"<<cnt;
    cout << endl;*/
    return;
}
int main()
{
    // 请在此输入您的代码
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> mapp[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            dfs(i, j, 1);
           
        }
    }
    cout << ans;
    return 0;
}