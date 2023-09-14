#ifndef LIST_H
#define LIST_H
#include <iostream>
const int LIST_INIT_SIZE = 100;
const int LISTINCREMENT = 10;
template<class elemType>
class List {
private:
	struct SqList {
		elemType* elem;
		int length, listsize;
	}L;
private:
	void visit(elemType e);
	bool compare(elemType a, elemType b);
	void init();
	void allocate();
public:
	List() { init(); }
	~List() {destroy();}
	void destroy();
	void clear(); // 清空链表
	bool empty();
	int length();
	elemType GetElem(int i); // 获取链表中第i个数据元素的值
	int LocateElem(elemType e); // 返回数据e在链表中的位序
	void priorElem(elemType cur_e, elemType& pre_e); /// 若cur_e 是链表中的元素, 用pre_e返回它的前驱
	void NextElem(elemType cur_e, elemType& next_e); // 同上返回后继
	void insert(int i, elemType e);
	void deleted(int i, elemType &e);
	void Traverse();
	void unionList(List<elemType>& list);
	void push(elemType e);

};

template<class elemType>
inline void List<elemType>::visit(elemType e)
{
	std::cout << e << std::endl;
}

template<class elemType>
inline bool List<elemType>::compare(elemType a, elemType b)
{
	return a == b;
}

template<class elemType>
void List<elemType>::init()
{
	L.elem = new elemType[LIST_INIT_SIZE];
	if (!L.elem) exit(OVERFLOW);
	L.length = 0;
	L.listsize = LIST_INIT_SIZE;
}
template<class elemType>
void List<elemType>::insert(int i, elemType e)
{
	if (i == 1 && L.length == 0) {
		*L.elem = e;
		++L.length;
		return;
	}
	if (i < 1 || i > L.length + 1) throw "out ranege";
	if (L.length >= L.listsize) allocate();
	auto q = &(L.elem[i - 1]);
	for (auto p = &(L.elem[L.length - 1]); p >= q; p--) *(p + 1) = *p;
	*q = e;
	++L.length;
}
template<class elemType>
void List<elemType>::deleted(int i, elemType& e)
{
	if (i < 1 || i > L.length)exit(1);
	auto p = &(L.elem[i - 1]);
	e = *p;
	auto q = L.elem + L.length - 1;
	for (++p; p <= q; ++p)*(p - 1) = *p;
	--L.length;
}
template<class elemType>
inline void List<elemType>::Traverse()
{
	for (int i = 0; i < L.length; i++) visit(*(L.elem + i));
}
template<class elemType>
void List<elemType>::unionList(List<elemType>& list)
{
	int cnt = 1;
	while (cnt <= list.length())push(list.GetElem(cnt++));
}
template<class elemType>
inline void List<elemType>::push(elemType e)
{
	if (L.length >= L.listsize)allocate();
	*(L.elem + L.length) = e;
	L.length++;
}
template<class elemType>
void List<elemType>::allocate()
{
	auto newbase = new elemType[L.listsize + LISTINCREMENT];
	std::copy(L.elem, L.elem + L.length, newbase);
	delete []L.elem;
	L.elem = newbase;
	L.listsize += LISTINCREMENT;
}
template<class elemType>
inline void List<elemType>::destroy()
{
	delete []L.elem;
}
template<class elemType>
inline void List<elemType>::clear()
{
	destroy();
	init();
}
template<class elemType>
inline bool List<elemType>::empty()
{
	return (L.length ? 1 : 0);
}
template<class elemType>
inline int List<elemType>::length()
{
	return L.length;
}
template<class elemType>
elemType List<elemType>::GetElem(int i)
{
	if (L.length == 0 || i > L.length || i <= 0)exit(1);
	return L.elem[i - 1];
}
template<class elemType>
int List<elemType>::LocateElem(elemType e)
{
	int pos = 1;
	auto p = L.elem;
	while (pos <= L.length && !compare(*p++, e))++pos;
	if (pos <= L.length) return pos;
	return 0;
}
template<class elemType>
void List<elemType>::priorElem(elemType cur_e, elemType& pre_e)
{
	int pos = LocateElem(cur_e);
	if (pos == 0)return;
	pre_e = *(L.elem + (pos - 2));
}
template<class elemType>
void List<elemType>::NextElem(elemType cur_e, elemType& next_e)
{
	int pos = LocateElem(cur_e);
	if (pos == L.length || pos == 0)return;
	next_e = *(L.elem + pos);
}
#endif// !LIST_H
