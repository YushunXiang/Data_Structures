#include "DoubleLinkList.h"

DoubleLinkNode::DoubleLinkNode()
{
    Next = NULL;
    Prev = NULL;
}

DoubleLinkedList::DoubleLinkedList()
{
    Head = new DoubleLinkNode;
    Head->Prev = Head;
    Head->Next = Head;
}

DoubleLinkedList::~DoubleLinkedList()
{
    ClearList();
    delete Head;
    Head = NULL;
}

//返回链表的头指针
DoubleLinkNode* DoubleLinkedList::GetHead()
{
    return Head;
}

// 返回双向链表的长度
int DoubleLinkedList::GetLength()
{
    return len;
}

// 判断链表是否为空
bool DoubleLinkedList::IsEmpty()
{
    if (len == 0) {
        return true;
    }
    else {
        return false;
    }
}


 
// 尾插法
void DoubleLinkedList::PushBack(ElementType X)
{
    DoubleLinkNode* Node = new DoubleLinkNode;
    DoubleLinkNode* tmp = Head->Prev;
    Node->Element = X;
    Head->Prev = Node;
    Node->Next = Head;
    Node->Prev = tmp;
    tmp->Next = Node;
    len++;
}

// 尾删法
void DoubleLinkedList::PopBack()
{
    if (Head == NULL) {
        return;
    }
    if (Head->Next == Head) {
        return;
    }
    DoubleLinkNode* tmp = Head->Prev->Prev;
    delete Head->Prev;
    tmp->Next = Head;
    Head->Prev = tmp;
    len--;
}


//头插法
void DoubleLinkedList::PushFront(ElementType X)
{
    DoubleLinkNode* Node = new DoubleLinkNode;
    DoubleLinkNode* tmp = Head->Next;
    Node->Element = X;
    Head->Next = Node;
    Node->Prev = Head;
    Node->Next = tmp;
    tmp->Prev = Node;
    len++;
}

// 头删法
void DoubleLinkedList::PopFront()
{
    if (Head == NULL) {
        return;
    }
    if (Head->Next == Head) {
        return;
    }
    DoubleLinkNode* tmp = Head->Next;
    Head->Next = tmp->Next;
    tmp->Prev = Head;
    delete tmp;
    len--;
}

// 删除第K个元素
void DoubleLinkedList::PopKth(DoubleLinkNode* P)
{
    if (Head == P) {
        return;
    }
    DoubleLinkNode* _prev = P->Prev;
    DoubleLinkNode* _next = P->Next;
    _prev->Next = _next;
    _next->Prev = _prev;
    delete P;
    len--;
}

// 按值查找
DoubleLinkNode* DoubleLinkedList::Find(ElementType X)
{
    DoubleLinkNode* P = Head->Next;
    while (P->Element != X) {
        P = P->Next;
    }
    return P;
}

// 打印整个双向循环链表
void DoubleLinkedList::Print()
{
    DoubleLinkNode* P = Head->Next;
    while (P != Head) {
        std::cout << P->Element << " ";
        P = P->Next;
    }
}

// 清空链表
void DoubleLinkedList::ClearList()
{
    DoubleLinkNode* p = Head->Next, * q;
    while (p != Head) {
        q = p->Next;
        delete p;
        p = q;
    }
    Head->Next = Head;
    Head->Prev = Head;
    len = 0;
}

// 设定或者改变大数的符号
void BigInteger_Change_Symbol(DoubleLinkedList L, bool Positive) 
{
    if (Positive) {
        L.GetHead()->Element = 1; // 表示正数
    }
    else {
        L.GetHead()->Element = 0; // 表示负数
    }
}

//DoubleLinkedList BigInteger_Add(DoubleLinkedList a, DoubleLinkedList b)
//{
//    if (a.GetHead()->Element == 0 && b.GetHead()->Element != 0) {
//        BigInteger_Change_Symbol(b, false);
//    }
//}