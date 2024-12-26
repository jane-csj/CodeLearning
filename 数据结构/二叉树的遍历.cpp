#include <iostream>
#include <stack>

constexpr auto endl = '\n';
constexpr auto MAX_TREE_SIZE = 100;
using std::cout;

struct BiTNode
{
    char data;
    BiTNode *l_child, *r_child;
};

class binaryTree{
    private:
        char SqBiTree[MAX_TREE_SIZE];
        
        bool visit(char e);
    public:
        binaryTree(){}
        void CreateBiTree(BiTNode* &T);
        bool PreOrderTraverse(BiTNode* T);      // 前序遍历
        bool InorderTraverse(BiTNode* T);       // 中序遍历
        bool PostOrderTraverse(BiTNode* T);     // 后序遍历
        bool LevelOrderTraverse(BiTNode* T);
        
};

void binaryTree::CreateBiTree(BiTNode* &T)
{
    char e;
    // std::cin >> e ;
    scanf("%c", &e);
    if(e == ' '){T = nullptr; return ;}
    // T = (BiTNode *)malloc(sizeof(BiTNode));
    T = new BiTNode;
    T->data = e;
    CreateBiTree(T->l_child);
    CreateBiTree(T->r_child);
    return;
}

bool binaryTree::visit(char e)
{
    std::cout << e << endl;
    return true;
}
bool binaryTree::PreOrderTraverse(BiTNode* T)
{
    if(T != nullptr){
        visit(T->data);
        PreOrderTraverse(T->l_child); // 遍历左节点
        PreOrderTraverse(T->r_child); // 遍历右节点
    }else return false;
    return true;
}
bool binaryTree::InorderTraverse(BiTNode* T)
{
    // 中序遍历二叉树的非递归算法
    std::stack<BiTNode*> s; auto p = T;
    while (p || !s.empty())
    {
        if(p){s.push(p); p = p->l_child;} // 遍历左子树
        else{                             // 遍历右子数
            p = s.top();
            visit(p->data);
            s.pop();
            p = p->r_child;
        }
    }
    
    return true;
}
bool binaryTree::PostOrderTraverse(BiTNode* T)
{
    if(T){
        PostOrderTraverse(T->l_child);
        PostOrderTraverse(T->r_child);
        visit(T->data);
    }else return false;
    return true;
}
int main(){
    binaryTree bt;
    BiTNode *Tch; 
    bt.CreateBiTree(Tch);
    // bt.InorderTraverse(Tch);     //结果:   C B E G D F A
    // bt.PreOrderTraverse(Tch);    //结果:   A B C D E G F
    // bt.PostOrderTraverse(Tch);   //结果:   C G E F D B A
    // system("pause");
    return 0;
}
