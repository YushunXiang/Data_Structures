#include "LinkList.h"

LinkNode::LinkNode()
{
    Next = NULL;
}


LinkList::LinkList()
{
    Head = new LinkNode;
}

void LinkList::CleanList()
{
    LinkNode* p;
    while (Head != NULL)
    {
        p = Head;
        Head = Head->Next;
        delete p;
        p = NULL;
    }
}

//返回头指针的位置
LinkNode* LinkList::GetHead()
{
    return Head;
}

//返回链表的长度
int LinkList::GetLength()
{
    return len;
}

//创建一个长度为 n 的链表（带头表的链表）
void LinkList::CreateList(int n)
{
    int i, Length, Data;
    len = n;
    LinkNode* pnew = NULL;
    LinkNode* tail = NULL;
    Head->Element = 0;
    Head->Next = NULL;
    tail = Head;
    for (i = 0; i < len; i++) {
        pnew = new LinkNode();
        std::cin >> pnew->Element;
        pnew->Next = NULL;
        tail->Next = pnew;
        tail = pnew;
    }
}

/*Return true if L is empty  测试一个链表是否为空表的函数*/
bool LinkList::IsEmpty()
{
    return Head->Next == NULL;
}

bool LinkList::IsLast(LinkNode* P)
{
    return P->Next == NULL;
}

LinkNode* LinkList::Find(ElementType X)
{
    LinkNode* P;

    P = Head->Next;
    while (P != NULL && P->Element != X) {
        P = P->Next;
    }
    return P;
}

void LinkList::Insert(ElementType X, LinkNode* P)
{
    LinkNode* TmpCell = new LinkNode();
    if (TmpCell == NULL) {
        std::cout << "Out of space!!!" << std::endl;
    }
    else {
        TmpCell->Element = X;
        TmpCell->Next = P->Next;
        P->Next = TmpCell;
    }
}

LinkNode* LinkList::FindPrevious(ElementType X)
{
    LinkNode* P;
    P = Head;

    while (P->Next != NULL && P->Next->Element != X) {
        P = P->Next;
    }
    return P;
}

void LinkList::Delete(ElementType X)
{
    LinkNode* P, * TmpCell;
    P = FindPrevious(X);
    if (IsLast(P) == 0) { //如果没到最后一个元素，则继续
        TmpCell = P->Next;
        P->Next = TmpCell->Next;
        delete TmpCell;
    }
}

// 返回链表第 i 个元素的值
ElementType LinkList::FindKth(int i)
{
    LinkNode* TmpCell;
    TmpCell = Head->Next;
    int j;

    for (j = 0; j < i; j++) {
        TmpCell = TmpCell->Next;
    }

    return TmpCell->Element;
}

// 链表的逆置
void LinkList::Reverse()
{
    LinkNode* p, * q;
    p = Head->Next;
    Head->Next = NULL;
    while (p) {
        q = p;
        p = p->Next;
        q->Next = Head->Next;
        Head->Next = q;
    }
}

void DuplicateRemoval_Link(LinkList link1, LinkList link2, LinkList link3)
{
    int i = 0, j = 0, k = 0;
    while (i < link1.GetLength() && j < link2.GetLength() && k < link3.GetLength()) {
        if (link2.FindKth(j) == link3.FindKth(k)) {
            if (link1.FindKth(i) == link2.FindKth(j)) {
                i++;
            }
            else if (link1.FindKth(i) < link2.FindKth(j)) {
                std::cout << link1.FindKth(i) << " ";
                i++;
            }
            else {
                j++;
                k++;
            }
        }
        else if (link2.FindKth(j) < link3.FindKth(k)) {
            j++;
        }
        else {
            k++;
        }
    }
    while (i < link1.GetLength()) {
        std::cout << link1.FindKth(i) << " ";
        i++;
    }
}