#include "order.h"


void eatline()
{
	while (cin.get() != '\n')continue;
}
order::order(string name)
{
	this->name = name;

}

void order::welcome()
{
	printf("**********");
	cout << this->name;
	printf(" Welcome to order system!");
	printf("**********\n");
}

int order::morder(int num)
{
	
	char one[] = "1->menu";
	char two[] = "2->myorder";
	char three[] = "3->return";
	printf("%20s", one);
	printf("%20s\n", two);
	printf("%20s\n", three);
	
	printf("please chose what you want to do:");
	cin >> num;
	switch (num)
	
	{
		//Õ¹Ê¾²Ëµ¥
	case 1:
		showmenu();
		orderfood();
		break;
	case 2:
		showmorder();
	case 3:
		return num;
	default:
		cout << "please input the correct number\n\n\n";
		break;
	}
}

void order::writemenu()
{
	fstream out(this->file, ios_base::in | ios_base::out|ios_base::app);
	printf("please input the name of food£º");
	cin >> fl.fname;
	while (fl.fname[0] != '-')
	{
		ct++;
		printf("please inout the price of the food: ");
		cin >> fl.price;
		out.write((char*)&fl, sizeof fl);
		printf("this is new menu:\n");
		printf("id:%6d",ct);
		cout << setw(20) << fl.fname;
		printf("%6.2lf\n", fl.price);
		printf("please input the name of food: ");
		cin >> fl.fname;
	}
	out.clear();
	out.close();
}

void order::orderfood()
{
	fstream re(this->file,ios_base::in|ios_base::out);
	int rec;
	cout << "please chose your food what you want to eat: ";
	cin >> rec;
	streampos place = rec * sizeof(fl);
	re.seekp(place);
	re.read((char*)&fl, sizeof fl);
	u.foodname = fl.fname;
	u.price = fl.price;
	u.total += fl.price;
	re.close();
	fstream wr(this->ofile, ios_base::in | ios_base::out | ios_base::app);
	printf("please input your dress: ");
	string dress;
	cin >> dress;
	printf("please input your phone: ");
	string phone;
	cin >> phone;
	u.phone = phone;
	u.dress = dress;
	u.name = this->name;
	wr.write((char*)&u, sizeof u);
	cout << "order success\n";
	wr.close();
}

void order::showmorder()
{
	fstream re(ofile, ios_base::in|ios_base::out);
	while (re.read((char*)&u, sizeof u))
	{
		if (u.name == name)
		{
			cout << setw(20) << u.name;
			cout <<setw(10)<< u.phone;
			cout << setw(20) << u.dress<<endl;
			cout << setw(20) << u.foodname;
			printf("%6.2lf\n", u.price);
			break;
		}
	}
}

string order::password()
{
	printf("please input your password : ");
	string s;
	cin >> s;
	return s;
}

bool order::istrue(string s)
{
	if(strcmp(s.c_str(),mPassword.c_str())==0)
	{
		return true;
	}
	printf("password error!please input again or return\n");
	return false;
}

bool order::chose()
{

	int a;
	string chose1 = "1->input again\n";
	string chose2 = "2->return\n";
	while (1)
	{
		cout << chose1;
		cout << chose2;
		printf("input your chosed  opreation: ");
		cin >> a;
		if (a == 2)return false;
		else if (a == 1)return true;
		else printf("number is error\n");
     }
	return false;
}



void order::showmenu()
{
	
	ifstream in(file, ios_base::in | ios_base::out);
	while (in.read((char*)&this->fl, sizeof this->fl))
	{
		cout << setw(5) << ct++;
		cout << setw(20) << fl.fname;
		printf("%6.2lf\n", fl.price);
	}
	if (in.eof())
	{
		in.clear();
		in.close();
	}
	return;
}

