#include <iostream>
#include <chrono>
using namespace std;
using namespace std::chrono;

#define endl '\n'
#define mfor(m) for(int i = 0; i < m; i++)
int main(){
    auto now = chrono::system_clock::now(); // 获取当前系统时间
    auto t_now = chrono::system_clock::to_time_t(now); // 将系统时间转化为 time_t 类型
    tm *t = localtime(&t_now); // 将 time_t 类型转化为 tm 结构
    char ch[200];
    strftime(ch,sizeof ch,"%Y-%m-%d %H:%M:%S",t); // 格式化输出tm结构
    cout << ch << endl;



    int cnt = 0;
    auto start = chrono::steady_clock::now(); // 单调时钟  计时器
    mfor(5e8-1){
        if(1)cnt++;
    }
    auto end = chrono::steady_clock::now();
    cout << duration_cast<milliseconds>(end - start).count() << endl; // 以毫秒输出
//    system("pause");
   return 0;
}
