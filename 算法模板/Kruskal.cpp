#include <iostream>
#include <algorithm>
#include <stack>
#include <string.h>
#include <vector>
#include <map>
#include <queue>
#define endl '\n'
const int N = 1e5;
int r[N], par[N];
// 并查集
void init(int n){
    for(int i = 1; i <= n; i++){
        par[i] = i;
        r[i] = 0;
    }
}
int find(int x){
    if(par[x] == x)return x;
    return par[x] = find(par[x]);
}
void unit(int x, int y){
    x = find(x);
    y = find(y);
    if(r[x] < r[y])par[x] = y;
    else{
        par[y] = x;
        if(r[x] == r[y])r[x]++;
    }
}
bool same(int x, int y){
    return find(x) == find(y);
}
//  Kruskal
struct edge
{
    int u, v, cost;
    bool operator <(const edge e){
        return cost < e.cost;
    }
}es[N];
int V, E;
int kruskal(){
    init(V);
    std::sort(es, es + E);
    int res = 0;
    for(int i = 0; i < E; i++){
        edge e = es[i];
        if(!same(e.u, e.v)){
            unit(e.u, e.v);
            res += e.cost;
        }
    }
    return res;
}
int main(){
    std::cin >> V >> E;
    for(int i = 0; i < E; i++){
        int u, v, w;
        std::cin >> u >> v >> w;
        es[i].u = u, es[i].v = v, es[i].cost  = w;
    }
    std::cout << kruskal();
    system("pause");
    return 0;
}
