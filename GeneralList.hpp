#ifndef _GENERALLIST_HPP_
#define _GENERALLIST_HPP_
#include <iostream>
#include <string>

typedef char AtomType;
enum ElemTag { ATOM, LIST }; // 枚举类型

template <class T>
class GeneralListNode
{
public:
	ElemTag tag; // 标志位tag用来区别原子节点和表节点
	union
	{
		// data是原子节点的值域
		T data;
		
		// ptr是表结点的指针域，prt.hp和ptr.tp分别指向表头和表尾(表头之外的其余元素)
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
	int GetLength() const; // 返回广义表的长度
	int GetDepth() const; // 返回广义表的深度
	void sever(std::string& str, std::string& hstr); // 将脱去外层括号的非空串str分割成两部分：hstr为第一个','之前的子串，str为之后的子串
public:
	GeneralListNode<T>* Head;
};

// 将指定的表头赋给新的类对象，以达到递归的目的
// 感觉这样的处理其实不太好
template <class T>
GeneralList<T>::GeneralList(GeneralListNode<T>* changeHead)
{
	this->Head = changeHead;
}


template <class T>
GeneralList<T>::GeneralList(const GeneralList<T>& obj) : this->Head(obj.Head) { }

/*
创造广义表要通过递归创建 
读取下一个字符，进行判断
s='('时，则构造子表
s='字符'时，则构造原子节点
s=')'时，令GL->tail=NULL，同时退出本层递归
s=','时，构造后继表
*/
template <class T>
GeneralList<T>::GeneralList(std::string strIn)
{
	// 采用头尾链表存储结构，由广义表的书写形式串S创建广义表L。设emp="()"
	std::string sub, hsub, empty;
	GeneralListNode<T>* p, * q;
	empty = "()";
	// if strIn == "()"
	if (empty == strIn || strIn == "") {
		this->Head = NULL; // 创建空表
	}
	else { // strIn 不是空串
		GeneralListNode<T>* node = new GeneralListNode<T>;
		if (node != NULL) {
			this->Head = node;
		}
		else {
			std::cerr << "Malloc Error!" << std::endl;
			exit(0);
		}

		if (strIn.size() == 1) { // strIn为单原子，这种情况只会出现在递归调用中
			this->Head->tag = ATOM; // 创建单原子广义表
			this->Head->data = strIn[0]; // 单原子的值为字符型
		}
		else { // S为表
			this->Head->tag = LIST;
			p = this->Head;
			// 脱外层括号(去掉第1个字符(左括号)和最后1个字符(右括号))给串sub
			sub = strIn.substr(1, strIn.size() - 2); // 返回字串
			do { // 重复建n个子表
				this->sever(sub, hsub); // 从sub中分离出表头串给hsub，其余部分(表尾)给sub
				
				// 递归创建表头串表示的4子表
				GeneralList<T> subTable(hsub);
				p->ptr.hp = subTable.Head;
				q = p; // q指向p所指结点
				if (sub.size() != 0) // 表尾不空
				{
					p = new GeneralListNode<T>; // 由p创建表结点

					p->tag = LIST; // p是子表
					q->ptr.tp = p; // p所指结点接在q所指结点之后，形成q的下一个结点
				}
			} while (sub.size() != 0);
			q->ptr.tp = NULL; // 设置最后一个表尾指针为空
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
	// 未到表尾
	while (p != NULL) {
		p = p->ptr.tp; // Head指向广义表最外层的下一个元素
		len++;
	}

	return len;
}


template <class T>
int GeneralList<T>::GetDepth() const
{
	int dep, max = 0;
	GeneralListNode<T>* p;
	if (Head == NULL) { // 广义表Head为空
		return 1; // 空表深度为1
	}
	
	if (Head->tag == ATOM) {// 是原子结点
		return 0; // 原子深度为0，只会出现在递归调用中
	}	
	
	for (p = Head; p; p = p->ptr.tp) {// 从本层的第1个元素到最后一个元素
		GeneralList<T> tmpList(p->ptr.hp);
		dep = tmpList.GetDepth(); // 递归求以p->ptr.hp为头指针的子表深度
		if (dep > max) {
			max = dep; // max存本层子表深度的最大值
		}
	}
	
	return max + 1; // 非空表的深度是各元素的深度的最大值加1
}


// 将脱去外层括号的非空串str分割成两部分：hstr为第一个','之前的子串，str为之后的子串
template <class T>
void GeneralList<T>::sever(std::string& str, std::string& hstr)
{
	int k = 0, i = -1; // k记尚未配对的左括号个数
	char ch;
	int n = str.size(); // n为串str的长度
	std::string sub, temp;

	do // 搜索最外层(k=0时)的第1个逗号
	{
		i++;
		ch = str[i]; // ch为串str的第i+1个字符 
		if (ch == '(') { // 尚未配对的左括号个数+1
			++k;
		}
		else if (ch == ')') { // 尚未配对的左括号个数-1 
			--k;
		}
	} while ((i < n && ch != ',' )|| k != 0); // i小于串长且ch不是最外层的','
	if (i < n) // 串str中存在最外层的','，它是第i个字符
	{
		hstr = str.substr(0, i); // hstr返回串str','前的字符
		temp = str.substr(i + 1, n - i - 1); // str返回串str','后的字符
		str = temp;
	}
	else // 串str中不存在','
	{
		hstr = str; // 串hstr就是串str
		str = ""; // ','后面是空串
	}
}

#endif // !_GENERALLIST_HPP_