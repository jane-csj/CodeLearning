#include <iostream>
#include <vector>
#include <stack>
using namespace std;
/// <summary>
/// ��������ʵ��
/// ���Ϊ0�Ķ��㼴Ϊû��ǰ���Ķ���ɾ�������Լ�����Ϊβ
/// �Ļ��Ĳ�������ɻ��Ի�ͷ�������ȼ�1��ʵ�֡�
/// ���Ӷ�ΪO(n + e) n Ϊ��������eΪ��������
/*
12 16
1 2 1
1 4 1
1 3 1
1 12 1
2 3 1
3 5 1
3 7 1
3 8 1
4 5 1
5 7 1
6 8 1
9 10 1
9 11 1
9 12 1
10 12 1
11 6 1
���
9 11 6 10 1 12 4 2 3 8 5 7*/
/// </summary>

const int MAX_VEXTER_NUM = 50;
struct Graph
{
	int vexnum, arcnum;
	vector<int>indegree;
	vector<int>G[MAX_VEXTER_NUM];
	int weight[MAX_VEXTER_NUM][MAX_VEXTER_NUM]; // ����ߵ�Ȩֵ
	Graph() : vexnum(0), arcnum(0){ for (int i = 0; i <= MAX_VEXTER_NUM; i++) indegree.emplace_back(0); }
};

// ��ʼ�����ж�������
void FindInDegree(Graph& G) {
	for (int i = 1; i <= G.vexnum; i++) {
		for (int v : G.G[i]) {
			G.indegree[v]++;
		}
	}
}

bool TopologicalSort(Graph& G) {
	FindInDegree(G);
	stack<int> st;
	for (int i = 1; i <= G.vexnum; i++) {
		if (!G.indegree[i])st.push(i);
	}
	int count = 0;
	while (!st.empty())
	{
		int u = st.top();
		cout << u << ' ';
		count++;
		st.pop();
		for (int v : G.G[u]) {
			if (!(--G.indegree[v]))st.push(v);
		}
	}
	cout << endl;
	if (count < G.vexnum)return false;
	return true;
}

int main() {
	Graph G;
	cin >> G.vexnum >> G.arcnum;
	for (int i = 1; i <= G.arcnum; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		G.G[u].emplace_back(v);
		G.weight[u][v] = w;
	}
	TopologicalSort(G);
	return 0;
}
