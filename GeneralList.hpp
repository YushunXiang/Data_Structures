#ifndef _GENERALLIST_HPP_
#define _GENERALLIST_HPP_
#include <iostream>
#include <string>

typedef char AtomType;
enum ElemTag { ATOM, LIST }; // ö������

template <class T>
class GeneralListNode
{
public:
	ElemTag tag; // ��־λtag��������ԭ�ӽڵ�ͱ�ڵ�
	union
	{
		// data��ԭ�ӽڵ��ֵ��
		T data;
		
		// ptr�Ǳ����ָ����prt.hp��ptr.tp�ֱ�ָ���ͷ�ͱ�β(��ͷ֮�������Ԫ��)
		struct
		{
			GeneralListNode<T>* hp, * tp;
		}ptr; 
	};
};

template <class T>
class GeneralList
{
public:
	GeneralList(std::string str);
	GeneralList(GeneralListNode<T>* changeHead);
	GeneralList(const GeneralList<T>& obj);
	//~GeneralList();
	void Destroy();
	int GetLength() const; // ���ع����ĳ���
	int GetDepth() const; // ���ع��������
	void sever(std::string& str, std::string& hstr); // ����ȥ������ŵķǿմ�str�ָ�������֣�hstrΪ��һ��','֮ǰ���Ӵ���strΪ֮����Ӵ�
public:
	GeneralListNode<T>* Head;
};

// ��ָ���ı�ͷ�����µ�������Դﵽ�ݹ��Ŀ��
// �о������Ĵ�����ʵ��̫��
template <class T>
GeneralList<T>::GeneralList(GeneralListNode<T>* changeHead)
{
	this->Head = changeHead;
}


template <class T>
GeneralList<T>::GeneralList(const GeneralList<T>& obj) : this->Head(obj.Head) { }

/*
��������Ҫͨ���ݹ鴴�� 
��ȡ��һ���ַ��������ж�
s='('ʱ�������ӱ�
s='�ַ�'ʱ������ԭ�ӽڵ�
s=')'ʱ����GL->tail=NULL��ͬʱ�˳�����ݹ�
s=','ʱ�������̱�
*/
template <class T>
GeneralList<T>::GeneralList(std::string strIn)
{
	// ����ͷβ����洢�ṹ���ɹ�������д��ʽ��S���������L����emp="()"
	std::string sub, hsub, empty;
	GeneralListNode<T>* p, * q;
	empty = "()";
	// if strIn == "()"
	if (empty == strIn || strIn == "") {
		this->Head = NULL; // �����ձ�
	}
	else { // strIn ���ǿմ�
		GeneralListNode<T>* node = new GeneralListNode<T>;
		if (node != NULL) {
			this->Head = node;
		}
		else {
			std::cerr << "Malloc Error!" << std::endl;
			exit(0);
		}

		if (strIn.size() == 1) { // strInΪ��ԭ�ӣ��������ֻ������ڵݹ������
			this->Head->tag = ATOM; // ������ԭ�ӹ����
			this->Head->data = strIn[0]; // ��ԭ�ӵ�ֵΪ�ַ���
		}
		else { // SΪ��
			this->Head->tag = LIST;
			p = this->Head;
			// ���������(ȥ����1���ַ�(������)�����1���ַ�(������))����sub
			sub = strIn.substr(1, strIn.size() - 2); // �����ִ�
			do { // �ظ���n���ӱ�
				this->sever(sub, hsub); // ��sub�з������ͷ����hsub�����ಿ��(��β)��sub
				
				// �ݹ鴴����ͷ����ʾ��4�ӱ�
				GeneralList<T> subTable(hsub);
				p->ptr.hp = subTable.Head;
				q = p; // qָ��p��ָ���
				if (sub.size() != 0) // ��β����
				{
					p = new GeneralListNode<T>; // ��p��������

					p->tag = LIST; // p���ӱ�
					q->ptr.tp = p; // p��ָ������q��ָ���֮���γ�q����һ�����
				}
			} while (sub.size() != 0);
			q->ptr.tp = NULL; // �������һ����βָ��Ϊ��
		}
		
	}
}

template <class T>
void GeneralList<T>::Destroy() 
{
	if (this->Head != NULL) {
		if (this->Head->tag == LIST) {
			GeneralList<T> tmp1(this->Head->ptr.hp);
			GeneralList<T> tmp2(this->Head->ptr.tp);
			tmp1.Destroy();
			tmp2.Destroy();
			delete this->Head;
			this->Head = NULL;
		}
	}
}

template <class T>
int GeneralList<T>::GetLength() const
{
	int len = 0;
	GeneralListNode<T>* p = Head;
	// δ����β
	while (p != NULL) {
		p = p->ptr.tp; // Headָ��������������һ��Ԫ��
		len++;
	}

	return len;
}


template <class T>
int GeneralList<T>::GetDepth() const
{
	int dep, max = 0;
	GeneralListNode<T>* p;
	if (Head == NULL) { // �����HeadΪ��
		return 1; // �ձ����Ϊ1
	}
	
	if (Head->tag == ATOM) {// ��ԭ�ӽ��
		return 0; // ԭ�����Ϊ0��ֻ������ڵݹ������
	}	
	
	for (p = Head; p; p = p->ptr.tp) {// �ӱ���ĵ�1��Ԫ�ص����һ��Ԫ��
		GeneralList<T> tmpList(p->ptr.hp);
		dep = tmpList.GetDepth(); // �ݹ�����p->ptr.hpΪͷָ����ӱ����
		if (dep > max) {
			max = dep; // max�汾���ӱ���ȵ����ֵ
		}
	}
	
	return max + 1; // �ǿձ������Ǹ�Ԫ�ص���ȵ����ֵ��1
}


// ����ȥ������ŵķǿմ�str�ָ�������֣�hstrΪ��һ��','֮ǰ���Ӵ���strΪ֮����Ӵ�
template <class T>
void GeneralList<T>::sever(std::string& str, std::string& hstr)
{
	int k = 0, i = -1; // k����δ��Ե������Ÿ���
	char ch;
	int n = str.size(); // nΪ��str�ĳ���
	std::string sub, temp;

	do // ���������(k=0ʱ)�ĵ�1������
	{
		i++;
		ch = str[i]; // chΪ��str�ĵ�i+1���ַ� 
		if (ch == '(') { // ��δ��Ե������Ÿ���+1
			++k;
		}
		else if (ch == ')') { // ��δ��Ե������Ÿ���-1 
			--k;
		}
	} while ((i < n && ch != ',' )|| k != 0); // iС�ڴ�����ch����������','
	if (i < n) // ��str�д���������','�����ǵ�i���ַ�
	{
		hstr = str.substr(0, i); // hstr���ش�str','ǰ���ַ�
		temp = str.substr(i + 1, n - i - 1); // str���ش�str','����ַ�
		str = temp;
	}
	else // ��str�в�����','
	{
		hstr = str; // ��hstr���Ǵ�str
		str = ""; // ','�����ǿմ�
	}
}

#endif // !_GENERALLIST_HPP_