#pragma once
#include<iostream>
#include<algorithm>
#include<fstream>
#include<string>
#include<iomanip>
using namespace std;
class order
{
public:
	order(string name);
	void welcome();
	//选餐
	int morder(int num);
	//展示菜单
	void showmenu();
	void writemenu();
	//点菜（暂时只能一道菜）
	void orderfood();
	//展示顾客的菜单
	void showmorder();
	//输入密码
	string password();
	//检查密码
	bool istrue(string s);
	bool chose();
private:
	string name;
	string dress;
	struct food
	{
		string fname;
		double price;
	}fl;
	struct user
	{
		string name;
		string dress;
		string foodname;
		double price;
		string phone;
		double total=0;
	}u;
	string file = "menu.text";
	string ofile = "order.txt";
	string mPassword = "6464334";
	int ct = 0;
};