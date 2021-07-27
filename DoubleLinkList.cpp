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

//���������ͷָ��
DoubleLinkNode* DoubleLinkedList::GetHead()
{
    return Head;
}

// ����˫������ĳ���
int DoubleLinkedList::GetLength()
{
    return len;
}

// �ж������Ƿ�Ϊ��
bool DoubleLinkedList::IsEmpty()
{
    if (len == 0) {
        return true;
    }
    else {
        return false;
    }
}


 
// β�巨
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

// βɾ��
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


//ͷ�巨
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

// ͷɾ��
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

// ɾ����K��Ԫ��
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

// ��ֵ����
DoubleLinkNode* DoubleLinkedList::Find(ElementType X)
{
    DoubleLinkNode* P = Head->Next;
    while (P->Element != X) {
        P = P->Next;
    }
    return P;
}

// ��ӡ����˫��ѭ������
void DoubleLinkedList::Print()
{
    DoubleLinkNode* P = Head->Next;
    while (P != Head) {
        std::cout << P->Element << " ";
        P = P->Next;
    }
}

// �������
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

// �趨���߸ı�����ķ���
void BigInteger_Change_Symbol(DoubleLinkedList L, bool Positive) 
{
    if (Positive) {
        L.GetHead()->Element = 1; // ��ʾ����
    }
    else {
        L.GetHead()->Element = 0; // ��ʾ����
    }
}

//DoubleLinkedList BigInteger_Add(DoubleLinkedList a, DoubleLinkedList b)
//{
//    if (a.GetHead()->Element == 0 && b.GetHead()->Element != 0) {
//        BigInteger_Change_Symbol(b, false);
//    }
//}