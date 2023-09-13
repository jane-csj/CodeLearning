#include <iostream>

using namespace std;

class myException : public exception{ // 从 exception 类派生出自己的异常类
private:
    const string message;
public:
    myException(string msg) : message(msg){} 
    const char* what() const noexcept override{ // 重写父类 what 方法
        return message.c_str();
    }
};
double divi(double a, double b){
    if( b == 0){
        throw myException("division by zero"); // 抛出自定义异常
    }
    return a/b;
}
int main(){
  try{
    divi(10,0);
  }catch(myException &e) { // 捕获异常
    cout << e.what() << endl;
  }
   return 0;
}
