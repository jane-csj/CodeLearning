#include <iostream>
#include <stack>
#include <string.h>
#include <vector>
using namespace std;


#define endl '\n'
#define mfor(m) for(int i = 0; i < m; i++)
const int INIT_STACK_SIZE = 100;
template<class T>struct cStack
{
    T *base, *top;
    int stackSize;
};
template<class T>class Stack{
private:
    cStack<T> S;
public:
    Stack();
    void push(T val); //入栈
    T top(); // 获取栈顶
    bool pop(); // 出栈
    int size(){return S.top - S.base;};
    bool empty(){return !(S.top - S.base);};
};
template<class T>Stack<T>::Stack(){
    S.base = new T[INIT_STACK_SIZE];
    S.top = S.base;
    S.stackSize = INIT_STACK_SIZE;
}
template<class T>void Stack<T>::push(T val){
   if(S.top - S.base >= S.stackSize - 1){
       T *tmp = new T[(INIT_STACK_SIZE + S.stackSize)]; // 开辟更大的内存
        copy(S.base, S.base + S.stackSize, tmp);  // 复制原有内存
        delete []S.base; // 释放原来的内存
        S.base = tmp;
        S.top = S.base + S.stackSize - 1;
        S.stackSize += INIT_STACK_SIZE;
   }
   *(++S.top) = val;
}
template<class T>T Stack<T>::top(){
    try
    {
        if(S.base == S.top) throw "该栈为空"; // 空栈的情况
    }
    catch(const char *error)
    {
       cout << error << endl;
    }
    return *S.top;
}
template<class T>bool Stack<T>::pop(){
    if(S.base == S.top) return false;
    --S.top;
    return true;
}
void t_to_e(int x){
    Stack<int>s;
    while(x){
        s.push(x%8);
        x /= 8;
    }
    while(!s.empty()){
        cout  << s.top();
        s.pop();
    }
    cout << endl;
}
bool compare(string s){
    Stack<char> st;
    for(char c : s){
        if(c == '(' || c == '[')st.push(c);
        if(c == ')'){
            if(st.top() != '(')return false;
            else st.pop();
        }
        if(c == ']'){
            if(st.top() != '[')return false;
            else st.pop();
        }
    }
    if(!st.empty()) return false;
    return true;
}
int main(){
    t_to_e(1348);// 十进制转化为八进制
    string s;
    cin >> s;
    cout << (compare(s) ? "true" : "false") << endl; // 括号的匹配
    // system("pause");
    return 0;
}
