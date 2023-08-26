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
int main(){
    Triple t[8];
    t[0].i = 1, t[0].j = 2, t[0].e = 12;
    t[1].i = 1, t[1].j = 3, t[1].e = 9;
    t[2].i = 3, t[2].j = 1, t[2].e = -3;
    t[3].i = 3, t[3].j = 6, t[3].e = 14;
    t[4].i = 4, t[4].j = 3, t[4].e = 24;
    t[5].i = 5, t[5].j = 2, t[5].e = 18;
    t[6].i = 6, t[6].j = 1, t[6].e = 15;
    t[7].i = 6, t[7].j = 4, t[7].e = -7;
    TSMatrix M(6, 6, 8);
    for(int i = 0; i < 8; i++){
        M.data[i + 1] = t[i];
    }
    TSMatrix T = FastTransposeSMatrix(M);
    for(int i = 1; i <= T.tu; i++){
        Triple tr = T.data[i];
        cout << tr.i << ' ' << tr.j << ' ' << tr.e << endl;
    }
    system("pause");
    return 0;
}
// 转置后的结果
/*1 3 -3
1 6 15
2 1 12
2 5 18
3 1 9
3 4 24
4 6 -7
6 3 14*/
