#include <iostream>
#include <vector>
#include <string.h> // memcpy strlen
using namespace std;

class HuffmanTree {

public:
	HuffmanTree(){}
	HuffmanTree(vector<int> _w) : w(_w){}
	~HuffmanTree();
	void HuffmanCoding();
	void print();

private:
	void Select(int n, int& t1, int& t2);
	struct HTNode
	{
		unsigned int weight;
		int parent, lchild, rchild;
	};
	HTNode* HT;
	typedef char** HuffmanCode;
	HuffmanCode HC;
	vector<int> w;
};

HuffmanTree::~HuffmanTree()
{
	delete[] HT;
	HT = nullptr;
	delete[] HC;
	HC = nullptr;
	
}

void HuffmanTree::HuffmanCoding()
{
	int n = w.size() - 1;
	if (n <= 1)return;
	int m = 2 * n - 1;
	HT = new HTNode[m + 1];
	for (int i = 1; i <= n; i++) {
		HT[i] = { (unsigned)w[i], 0, 0 , 0 };
	}
	for (int i = n + 1; i <= m; i++) { HT[i] = { 0, 0 ,0, 0 }; }
	int s1 = 0, s2 = 0;
	for (int i = n + 1; i <= m; i++) {
		Select(i, s1, s2);
		
		HT[s1].parent = i, HT[s2].parent = i;
		HT[i].lchild = s1, HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	//	±àÂë¹ý³Ì
	HC = new char* [n + 1];
	char* cd = new char[n];
	cd[n - 1] = '\0';
	for (int i = 1; i <= n; i++) {
		int start = n - 1;
		for (int c = i, f = HT[i].parent; f != 0; c = f, f = HT[f].parent) {
			if (HT[f].lchild == c) cd[--start] = '0';
			else cd[--start] = '1';
		}
		HC[i] = new char[n - start];
		strcpy(HC[i], &cd[start]);
	}
	delete[] cd;
}

void HuffmanTree::print()
{
	for (int i = 1; i <= w.size() - 1; i++) {
		cout << i << ": " << HC[i] << endl;
	}
}

void HuffmanTree::Select(int n, int& t1, int& t2)
{
	t1 = -1, t2 = -1;
	for (int i = 1; i < n; i++) {
		if ((t1 == -1 || HT[i].weight < HT[t1].weight) && HT[i].parent == 0) {
			t2 = t1;
			t1 = i;
			continue;
		}
		if ((t2 == -1||HT[i].weight < HT[t2].weight) && HT[i].parent == 0) {
			t2 = i;
		}
	}
}

int main() {
	vector<int> w{ 0, 5, 29, 7, 8, 14, 23, 3, 11 };
	HuffmanTree HT(w);
	HT.HuffmanCoding();
	HT.print();
	return 0;
}