#include<iostream>
using namespace std;
#define null NULL
const string exist = "the List isn't exist!";
class Node 
{
public:
	int val;
	Node* next;
	Node(int num) { val = num; next= NULL; }
};
class List 
{
public :
	Node* head, * tail;
	List() { head = tail = NULL; }
		//增加
	void insert(int num);
	void insert(int num[],int length);
	void print();
	//根据位置查询
	int getpos(int value);
	//删除数据
	void deletedByVal(int value);
	void deletedByPos(int pos);
};
void List::print()
{
	Node* p = head;
	if (p == NULL)cout << "the List is empty!" << endl;
	else
	{
		while (p != NULL)
		{
			cout << p->val << " ";
			p = p->next;
		}
		cout << endl;
	}
}
void List::insert(int num)
{
	Node * p;
	Node* q = new Node(num);
	p = head;
	if (p == NULL) 
	{
		head = q;
		head->next = NULL;
		tail = head;
	}
	else
	{
		tail->next = q;
		tail = q;
	}
}
void List::insert(int num[],int length)
{
	for (int i = 0; i < length; i++)
	{
		insert(num[i]);
	}
}
int List::getpos(int value)
{
	int pos = 0;
	Node* p;
	p = head;
	if (p == NULL)
	{
		cout << "the List isn't exist!\n";
	}
	while ( p!= NULL)
	{
		++pos;
		if (p->val == value)
		{
			cout <<" you search number "<< p->val << " in NO." << pos << endl;
			return pos;
		}
		p = p->next;
	}
	cout << "the List don't have this number";
	return -1;
}
void List::deletedByVal(int value)
{
	Node* p=NULL,*q=null;
	p = head;
	if (p == NULL)
	{
		cout << exist;
		return;
	}
	else
	{
		int flag = 0;
		while (p->next != null)
		{
		
			if (p->val == value)
			{
				flag = 1;
				break;
			}
			q = p;
			p=p->next;
		}
		//删除最后一个
		if (p->next==null&&p->val == value)
		{
			q->next = null;
			tail = q;
			return;
		}
		if (flag ==1)
		{
			q->next = p->next;
			p->next = null;
			return;
		}
		cout << "the List don't exist the number\n";
	}
}
void List::deletedByPos(int pos)
{
	if (pos < 1)
	{
		cout << "the number is error ";
		return;
	}
	//删除第一个
	if (pos == 1)
	{
		head = head->next;
		return;
	}
	Node* p = NULL, * q = null;
	p = head;
	if (p == NULL)
	{
		cout << exist;
		return;
	}
	else
	{
		int cnt = 0;
		while (p->next != null)
		{
			++cnt;
			if (cnt == pos)break;
			q = p;
			p = p->next;
		}
		
		if (p->next == null && pos>cnt+1)
		{
			cout << "the number is error ";
			return;
		}
		q->next = p->next;
		p->next = null;
		tail = q;
		cout << "deleted operation is succeed ";
	} 
}
int main()
{
	List* p = new List();
	int num[] = { 2,1,6,4 };
	p->insert(num,4);
	p->print();
	p->getpos(2);
	p->deletedByPos(1);
	p->print();
	p->getpos(2);
	//p->getpos(3);
	return 0;
}