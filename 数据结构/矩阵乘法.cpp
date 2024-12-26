#include <iostream>
#include <stack>
#include <string.h>
#include <vector>
#include <map>
using namespace std;


#define endl '\n'
const int MAXSIZE = 12500;
struct Triple
{
    int i, j;
    int e; // 元的值
    Triple(){}
    Triple(int i, int j, int e): i(i), j(j), e(e){}
};
struct TSMatrix
{
    Triple data[MAXSIZE + 1]; // data[0]不用
    int col, row, tu; // 列数 行数 非零个数
    TSMatrix(int col, int row, int tu):col(col), row(row), tu(tu){}
    TSMatrix(){}
};
// 转置矩阵
TSMatrix TransposeSMatrix(TSMatrix M){
    TSMatrix T(M.row, M.col, M.tu);
    int q = 1;
    for(int i = 1; i <= M.col; i++){
        for(int j = 1; j <= M.tu; j++){
            if(M.data[j].j == i){
                T.data[q].i = M.data[j].j;
                T.data[q].j = M.data[j].i;
                T.data[q].e = M.data[j].e;
                ++q;
            }
        }
    }
    return T;
}
TSMatrix FastTransposeSMatrix(TSMatrix M){
    int cpos[MAXSIZE + 1], num[MAXSIZE + 1];
    memset(num, 0, sizeof num);
    for(int i = 1; i <= M.tu; i++)num[M.data[i].j]++; // 记录每列的非零元的数量
    cpos[1] = 1;
    for(int i = 2; i <= M.col; i++)cpos[i] = cpos[i - 1] + num[i - 1]; // 记录每列第一个非零元的在倒置矩阵的位置
    TSMatrix T(M.row, M.col, M.tu);
    for(int i = 1; i <= M.tu; i++){
        int col = M.data[i].j, q = cpos[col];
        T.data[q].i = col, T.data[q].j = M.data[i].i, T.data[q].e = M.data[i].e;
        ++cpos[col];
    } 
    return T;
}

struct TSMatrix2
{
    Triple data[MAXSIZE + 1];
    int row, col, sum;
    int rpos[MAXSIZE + 1]; // 每行首个非零元的位置
    TSMatrix2(){}
    TSMatrix2(int _row, int _col, int _sum) : row(_row), col(_col), sum(_sum){}
};
void initRpos(TSMatrix2 &M){
    vector<int>num(M.row + 1);
    // int num[10 + 1];
    fill(num.begin(), num.end(), 0);
    for(int i = 1; i <= M.sum; i++)num[M.data[i].i]++;
    M.rpos[1] = 1;
    for(int i = 2; i <= M.row; i++)M.rpos[i] = M.rpos[i - 1] + num[i - 1];
}
// 两个稀疏矩阵的乘法 M x N
TSMatrix2 MultSMatrix(TSMatrix2 &M, TSMatrix2 &N){
    if(M.col != N.row) throw "这两个矩阵不能相乘";
    initRpos(M);
    initRpos(N);
    TSMatrix2 Q(M.row, N.col, 0);
    vector<int>ctemp(N.col + 1);
    for(int row = 1; row <= M.row; row++){
        fill(ctemp.begin(), ctemp.end(), 0); // 计数器清零
        Q.rpos[row] = Q.sum + 1;
        int tp = 0;
        if(row < M.row) tp = M.rpos[row + 1];
        else tp = M.sum + 1;
        for(int p = M.rpos[row]; p < tp; p++){
            int brow = M.data[p].j; // 找到对应N中的行
            int t = 0;
            if(brow < N.row) t = N.rpos[brow + 1];
            else t = N.sum + 1;
            for(int q = N.rpos[brow]; q < t; q ++){
                int bcol = N.data[q].j;
                ctemp[bcol] += M.data[p].e * N.data[q].e;
            }
        }
        for(int col = 1; col <= Q.col; col++){
            if(ctemp[col] == 0) continue;
            if(++Q.sum > MAXSIZE) throw "超出最大的非零数量";
            Q.data[Q.sum] = Triple(row, col, ctemp[col]);
        }
    }

    return Q;
}





int main(){
    TSMatrix2 M(3, 4, 4);
    M.data[1] = Triple(1, 1, 3);
    M.data[2] = Triple(1, 4, 5);
    M.data[3] = Triple(2, 2, -1);
    M.data[4] = Triple(3, 1, 2);


    TSMatrix2 N(4, 2, 4);
    N.data[1] = Triple(1, 2, 2);
    N.data[2] = Triple(2, 1, 1);
    N.data[3] = Triple(3, 1, -2);
    N.data[4] = Triple(3, 2, 4);
    TSMatrix2 Q;
    try
    {
        Q = MultSMatrix(M, N);
    }
    catch(const char* error)
    {
        std::cerr << error << '\n';
        return 0;
    }
    
    for(int i = 1; i <= Q.sum; i++){
        Triple tr = Q.data[i];
        cout << tr.i << ' ' << tr.j << ' ' << tr.e << endl;
    }
    
    return 0;
}
