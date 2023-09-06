#include <iostream>
#include <stack>
#include <string.h>
#include <vector>
#include <map>
#include <queue>
#define endl '\n'
const int N = 1e5;
int ne[N];
char s[N], t[N]; // 匹配串和模式串
int n, m; // 匹配串和模式串的长度
void get_next(int* T, char* t){
    m = strlen(t + 1);

    int j = 0;
    T[1] = 0;
    for(int i = 2; i <= m; i++){
        while(j && t[i] != t[j + 1])j = ne[j];
        if(t[i] == t[j + 1])j++;
        ne[i] = j;
    }
}
std::vector<int> KMP(char *s, char *t){
    n = strlen(s + 1);
    std::vector<int> ans;
    get_next(ne, t);
    int j = 0;
    for(int i = 1; i <= n + 1; i++){
        while(j && s[i] != t[j + 1])j = ne[j];
        if(s[i] == t[j + 1])j++;
        if(j == m){ans.push_back(i - m + 1); j = ne[j];}
    }
    return ans; 
}
int main(){
    scanf("%s%s", s + 1, t + 1);
    std::vector <int > ans = KMP(s , t);
    if(ans.empty()) std::cout << "匹配失败" << endl;
    else{
        for(int v : ans) std::cout << "pos : " << v << endl;
    }
    system("pause");
    return 0;
}
