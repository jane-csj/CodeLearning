#include<iostream>
#include<fstream>
#include"order.h"
using namespace std;

order *p=NULL;

void ad();
void customer();
void isad();
void customer()
{
	p->welcome();
	int num = 0;
	while (num != 3)
	{
		num=p->morder(num);
		
	}

}
void isad()
{
	char yes[] = "1->YES";
	char no[] = "2->NO";
	//进入系统
	string name;
	cout << "please input your name: ";
	cin >> name;
	p = new order(name);
	cout << "Are you ad?\n";
	printf("%6s%6s\n", yes, no);
	int m;
	cin >> m;
	if (m == 1)ad();
	else if (m == 2)customer();

}
void ad()
{
	while (!p->istrue(p->password()))
	{
		if (!p->chose())isad();
	}
	p->welcome();
	p->showmenu();
	p->writemenu();
}
int main()
 {
	cout << left;
	isad();
	return 0;
}