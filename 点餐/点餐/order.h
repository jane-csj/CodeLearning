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
	//ѡ��
	int morder(int num);
	//չʾ�˵�
	void showmenu();
	void writemenu();
	//��ˣ���ʱֻ��һ���ˣ�
	void orderfood();
	//չʾ�˿͵Ĳ˵�
	void showmorder();
	//��������
	string password();
	//�������
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