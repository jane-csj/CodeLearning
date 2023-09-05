#include <iostream>
#include <stack>
#include <string.h>
#include <vector>
#include <map>
#include <queue>
using namespace std;
const int INF = 0x3f3f3f3f;
const int MAX_V = 1e2; // 最大顶点数
int V, E;
const int MAX_E = 1e5;
int e[MAX_E], h[MAX_E], ne[MAX_E], w[MAX_E];
int idx = 0;
int dis[MAX_V];
bool vis[MAX_V];
typedef pair<int, int>PII;
priority_queue<PII, vector<PII>, greater<PII>> q;
void add(int u, int v, int cost){
    e[idx] = v, w[idx] = cost, ne[idx] = h[u], h[u] = idx++;
}
int prim2(){
    memset(dis, INF, sizeof dis);
    memset(vis, 0, sizeof vis);
    
    int cnt = 0, sum = 0;
    dis[1] = 0;
    q.push(PII(0, 1));
    while (cnt < V && !q.empty())
    {
        PII p = q.top();
        q.pop();
        int distance = p.first, ver = p.second;
        if(vis[ver])continue;
        vis[ver] = true;
        cnt++;
        sum += distance;
        for(int i = h[ver]; i != -1; i = ne[i]){
            int j = e[i];
            if(w[j] < dis[j]){
                dis[j] = w[j];
                q.push(PII(dis[j], j));
            }
        }

    }
    return sum;
}
int main(){
    memset(h, -1, sizeof h);
    int a, b, c;
    for(int i = 0; i < E; i++){
        cin >> a >> b >> c;
        add(a, b, c);
        add(b, a, c);
    }
    cout << prim2() << endl;
    system("pause");
    return 0;
}
