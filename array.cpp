#include <iostream>
using namespace std;

#define endl '\n'
#define mfor(m) for(int i = 0; i < m; i++)
int main(){
    // 数组是一段连续的内存
    char b[20];
    int *pb = (int *)b; // 将 char 类型(1字节)  当成 int 类型(4字节)使用  注意越界
    mfor(5){
        pb[i] = i + 1;
        cout << pb[i] << ' ';
    }
    cout << endl;


    // 理解数组名的含义 和 指针对数组的使用 
    int a[10];
    cout << "数组 a 的地址: " << a << endl;
    cout << "a[0] 的地址: " << &a[0] << endl; // 地址与上面代码一致 表明数组名可以表示数组首元素的地址
    mfor(10){
        a[i] = i;
    }
    mfor(10){
        cout << a[i] << ' '; // 数组名[下标] 解释为 *(数组首地址 + 下标)
    }
    cout << endl;
    int *p = a; // 注意不是 int *p = &a;
    mfor(10){
        cout << p[i] << ' '; //地址[下标] 解释为 *(地址 + 下标)
    }
    cout << endl;

    p = &a[2]; // p 指向第三个元素
    cout << p[0] << ' ' << p[1] << endl; // 输出第三个和第四个元素 2 和 3
    // system("pause");
    return 0;
}
