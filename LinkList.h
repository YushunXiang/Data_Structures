#pragma once
#include "main.h"

#ifndef _LinkNode_h

class LinkNode {

public:
    ElementType Element;
    LinkNode* Next;

    LinkNode();
};

class LinkList {
private:
    LinkNode* Head; //头表
    int len; //整个链表的长度

public:
    LinkNode* GetHead();
    LinkList();
    void CleanList();
    int GetLength();
    void CreateList(int n);
    bool IsEmpty();
    bool IsLast(LinkNode* P);
    LinkNode* Find(ElementType X);
    void Insert(ElementType X, LinkNode* P);
    LinkNode* FindPrevious(ElementType X);
    void Delete(ElementType X);
    ElementType FindKth(int i); // 返回链表第 i 个元素的值
    void Reverse();
};

void DuplicateRemoval_Link(LinkList link1, LinkList link2, LinkList link3);

#endif // !_LinkNode_h