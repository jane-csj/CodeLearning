#include <iostream>
#include <cmath>
#include <vector>


#define endl '\n'
using namespace std;
struct OLNode{
    int i, j, e;
    OLNode *right, *down;
};
struct CrossList{
    OLNode **cHead, **rHead; // 列 行链表首地址
    int row, col, n;
};
bool createSMatrix_OL(CrossList &M){
    cin >> M.row >> M.col >> M.n;
    if(!(M.rHead = new OLNode*[M.row]))exit(OVERFLOW);
    if(!(M.cHead = new OLNode*[M.col]))exit(OVERFLOW);
    OLNode *p{};
    int i, j, e;
    while((cin >> i >> j >> e) && i !=0){
        p -> i = i, p -> j = j, p -> e = e;
        if(M.rHead[i] == nullptr || M.rHead[i] -> j > j){ // 行插入
            p -> right = M.rHead[i];
            M.rHead[i] = p;
        }else{
            for(auto q = M.rHead[i]; q->right && q->right->j > j; q++){
                p->right = q->right;
                q->right = p;
            }
        }
//        列插入
        if(M.cHead[j] == nullptr || M.cHead[j]->i > i) {p->down = M.cHead[j];M.cHead[j] = p;}
        else{
            for(OLNode *q = M.cHead[j]; q->down && q->down->i < i; q++){
                p->down = q->down;
                q->down = p;
            }
        }
    }
    return true;
}
int main() {

    return 0;
}
