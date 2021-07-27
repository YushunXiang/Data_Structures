#pragma once
#include "main.h"

#ifndef _DoubleLinkedList_h_
#define _DoubleLinkedList_h_


/*Ë«Ñ­»·Á´±í*/
class DoubleLinkNode
{
public:
	ElementType Element;
	DoubleLinkNode* Prev;
	DoubleLinkNode* Next;
	DoubleLinkNode();
};

class DoubleLinkedList
{
public:
	DoubleLinkedList();
	~DoubleLinkedList();
	// DoubleLinkNode* CreateLink();
	DoubleLinkNode* GetHead();
	int GetLength();
	void PushBack(ElementType X); // Î²²å·¨
	void PopBack(); //Î²É¾·¨
	void PushFront(ElementType X);
	void PopFront();
	void PopKth(DoubleLinkNode* P);
	DoubleLinkNode* Find(ElementType X);
	void ClearList();
	void Print();
	bool IsEmpty();
private:
	DoubleLinkNode* Head;
	int len;
};

#endif // !_DoubleLinkedList_h_

void BigInteger_Change_Symbol(DoubleLinkedList L, bool Positive);

DoubleLinkedList BigInteger_Add(DoubleLinkedList a, DoubleLinkedList b);

