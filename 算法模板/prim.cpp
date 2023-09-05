#include <iostream>
#include <stack>
#include <string.h>
#include <vector>
#include <map>
#include <queue>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAX_V = 1e2; // 最大顶点数
int cost[MAX_V][MAX_V]; //cost[u][v] 表示边e(u, v)的权值， 不存在的情况下设为INF
int mincost[MAX_V]; // 从集合X出发到每个顶点的最小权值
bool used[MAX_V]; // 顶点i是否包含在集合X中
int V, E; // 顶点数
int prim()
{
    memset(mincost, INF, sizeof mincost);
    memset(used, 0, sizeof used);
    mincost[0] = 0;
    int res = 0;
    while (true)
    {
        int v = -1;
        for(int u = 0; u < V; u++){
            if(!used[u] && (v == -1 || mincost[u] < mincost[v])) v = u;
        }
        if(v == -1)break;
        used[v] = true;
        res += mincost[v];
        for(int u = 0; u < V; u++)mincost[u] = min(mincost[u], cost[u][v]);
    }
    return res;
}

int main(){
    
    system("pause");
    return 0;
}
