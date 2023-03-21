#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
using namespace std;
//string fileName = "menu.txt";
//void showmenu()
//{
//	cout << "the lastly menu is :\n";
//	char ch;
//	ifstream in(fileName.c_str());
//	int count = 0;
//	while (in.get(ch))
//	{
//		cout << ch;
//		if (ch == '\n')count++;
//	}
//	cout << endl;
//	cout << "the menu have " << count<<" " << "food";
//	in.clear();
//	in.close();
//}
//void initmenu()
//{
//	ifstream in(fileName.c_str());
//	if (in.is_open())
//	{
//		char ch;
//		cout << "now,the menu have these :\n";
//		while (in.get(ch))
//		{
//			cout << ch;
//		}
//	}
//	in.close();
//}
//int main()
//{
//
//	//for (int i = 0; i < 20; i++)
//	//{
//	//	//设置字段宽度
//	//	cout.width(6);
//	//	cout << i;
//	//}
//	//设置数字精度
//	//设置末尾的零
//	//cout.setf(ios_base::showpoint);
//	//cout.precision(3);
//	//double c = 0.35;
//	//cout << c<<endl;
//	////设置数字精度
//	//cout << setprecision(4)<< (double)1 / 3; 
//	//读写文件
//	
//	ifstream in(fileName.c_str());
//	char ch;
//	//展示之前的菜单
//	initmenu();
//	ofstream out(fileName.c_str(),ios::out|ios::app);
//	string name;
//	//添加菜名
//	cout << "please input your love name:\n";
//	while (getline(cin, name) && name.size() > 0)
//	{
//		out << name << endl;
//	}
//	out.close();
//	//展示菜单
//	showmenu();
//	
//	return 0;
//}
const string file = "test.txt";
struct plane {
	char name[20];
	double time;
}pl;
inline void eatline()
{
	while (cin.get() != '\n')continue;
}
//int main()
//{
//
//	ofstream fio;
//	fio.open(file.c_str(), ios::out|ios::app|ios_base::binary);
//	cout << "input the plane name(if you want to pause input ,please input'-'): ";
//	cin.get( pl.name, 20);
//	eatline();
//	double bb;
//	cin >> pl.ptime;
//	cout << pl.ptime;
//	fio.write((char*)&pl, sizeof pl);
//	fio.close();
//}

void chage(int maxx,fstream &in)
{
	cout << "input numble of plane you want to chage:";
	long rec;
	cin >> rec;
	eatline();
	//输出选择的星球的参数
	if (rec > maxx || rec < 0)return;
	streampos place = rec * sizeof pl;
	in.seekp(place);
	cout << "you selexct :\n";
	in.read((char*)&pl, sizeof pl);
	cout << rec << setw(20) << pl.name<< setw(10) << pl.time<<endl;
	if (in.eof())in.clear();
	cout << "enter plane name:\n";
	cin.get(pl.name,20);
	cout << "enter the time:\n";
	cin >> pl.time;
	in.seekp(place);
	in.write((char*)&pl, sizeof pl) << flush;

}

void showfile(int ct,fstream &in)
{
	ct = 0;
	in.seekg(0);
	cout << "here are the new cotents of the " << file << endl;
	while (in.read((char*)&pl, sizeof pl))
	{
		cout << ct++ << setw(20) << pl.name << setw(10)<< pl.time << endl;
	}
	in.close();
}

int main()
{
	fstream fio;
	fio.open(file, ios_base::out | ios::in);

	int ct = 0;
	if (fio.is_open())
	{
		fio.seekg(0);
		cout << "Here are the content of the plane\n";
		while (fio.read((char*)&pl, sizeof pl))
		{
			cout << ct++ << setw(20) << pl.name << setw(10)<<pl.time << endl;
		}
		if (fio.eof())
		{
			fio.clear();
		}
		else 
		{
			cout << "read is error" << endl;
		}
	}
	else
	{
		cout << file << " could not open." << endl;
	}
	//改变行星的参数
	chage(ct,fio);
	showfile(ct,fio);
}