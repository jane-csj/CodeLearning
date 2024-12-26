#include <iostream>
#include <vector>
#include <string.h>
#include <stack>
using namespace std;
const int MAX_VEXTER_NUM = 50;
struct Graph
{
	int vexnum, arcnum;
	vector<int>indegree;
	vector<int>G[MAX_VEXTER_NUM];
	int weight[MAX_VEXTER_NUM][MAX_VEXTER_NUM]; // 储存边的权值
	Graph() : vexnum(0), arcnum(0) { for (int i = 0; i <= MAX_VEXTER_NUM; i++) indegree.emplace_back(0); }
};
int vl[MAX_VEXTER_NUM], ve[MAX_VEXTER_NUM];
// 初始化所有顶点的入度
void FindInDegree(Graph& G) {
	for (int i = 1; i <= G.vexnum; i++) {
		for (int v : G.G[i]) {
			G.indegree[v]++;
		}
	}
}

bool TopologicalSort(Graph& G, stack<int> &T) {
	FindInDegree(G);
	memset(ve, 0, sizeof ve);
	stack<int> st;
	for (int i = 1; i <= G.vexnum; i++) {
		if (!G.indegree[i])st.push(i);
	}
	int count = 0;
	while (!st.empty())
	{
		int u = st.top();
		T.push(u);
		count++;
		st.pop();
		for (int v : G.G[u]) {
			if (!(--G.indegree[v]))st.push(v);
			int dist = G.weight[u][v];
			if (ve[u] + dist > ve[v])ve[v] = ve[u] + dist;

		}
	}
	if (count < G.vexnum)return false;
	return true;
}

bool CriticalPath(Graph& G) {
	stack<int> st;
	if (!TopologicalSort(G, st))return false;
	for (int i = 1; i <= G.vexnum; i++) {
		vl[i] = ve[G.vexnum];
	}
	
	while (!st.empty())
	{
		int u = st.top();
		st.pop();
		for (int p : G.G[u]) {
			int dut = G.weight[u][p];
			if (vl[p] - dut < vl[u]) vl[u] = vl[p] - dut;
		}
	}
	for (int j = 1; j <= G.vexnum; j++) {
		for (int k : G.G[j]) {
			int dut = G.weight[j][k];
			int ee = ve[j], el = vl[k] - dut;
			char tag = (ee == el) ? '*' : ' ';
			printf("%d, %d, %d, %d, %d, %c\n", j, k, dut, ee, el, tag);
		}
	}
}
/*
6 8 
1 2 3
1 3 2
2 5 3
2 4 2
3 4 4
3 6 3
4 6 2
5 6 1
*/
int main() {
	Graph G;
	cin >> G.vexnum >> G.arcnum;
	for (int i = 1; i <= G.arcnum; i++) {
			int u, v, w;
			cin >> u >> v >> w;
			G.G[u].emplace_back(v);
			G.weight[u][v] = w;
		}
	CriticalPath(G);
}