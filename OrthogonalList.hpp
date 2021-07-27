#pragma once

#ifndef _ORTHOGONALLIST_HPP_
#define _ORTHOGONALLIST_HPP_
#include <cstring>
#include <iostream>

template <class T>
struct OrthogonalNode {
    int row;
    int col;
    T element;
    // 非0元素所在行标、列表的后继链域
    OrthogonalNode* down;
    OrthogonalNode* right;
};

template <class T>
class OrthogonalList {
private:
    // 行、列链表的头指针向量
    OrthogonalNode<T>** m_rowHead;
    OrthogonalNode<T>** m_colHead;
    // 稀疏矩阵的行数、列数、非零元素的个数
    int m_rowLength, m_colLength, m_length;

public:
    OrthogonalList(int rowLength, int colLength, int length);
    OrthogonalList(const OrthogonalList<T>& obj);
    ~OrthogonalList();
    void Init();
    void Add(const OrthogonalList<T>& obj);
    void Insert(int row, int col, T value);
    void Delete(int row, int col);
    void ChangeElement(int row, int col, T value);
    void Print();
};

template <class T>
OrthogonalList<T>::OrthogonalList(int rowLength, int colLength, int length)
    : m_rowLength(rowLength)
    , m_colLength(colLength)
    , m_length(length)
{
    this->m_rowHead = new OrthogonalNode<T>*[m_rowLength + 1];
    this->m_colHead = new OrthogonalNode<T>*[m_colLength + 1];
    std::memset(this->m_rowHead, 0, sizeof(OrthogonalNode<T>*) * (this->m_rowLength + 1));
    std::memset(this->m_colHead, 0, sizeof(OrthogonalNode<T>*) * (this->m_colLength + 1));
}

template <class T>
OrthogonalList<T>::OrthogonalList(const OrthogonalList<T>& obj)
    : m_rowLength(obj.m_rowLength)
    , m_colLength(obj.m_colLength)
    , m_length(obj.m_length)
{
    this->m_rowHead = new OrthogonalNode<T>*[m_rowLength + 1];
    this->m_colHead = new OrthogonalNode<T>*[m_colLength + 1];
    for (int i = 0; i <= m_rowLength; i++) {
        this->m_rowHead[i] = obj.m_rowHead[i];
    }
    for (int i = 0; i <= m_colLength; i++) {
        this->m_colHead[i] = obj.m_colHead[i];
    }
}

template <class T>
OrthogonalList<T>::~OrthogonalList()
{
    for (int i = 0; i <= this->m_rowLength; i++) {
        if (this->m_rowHead[i] != NULL) {
            OrthogonalNode<T>* p = this->m_rowHead[i];
            while (p != NULL) {
                OrthogonalNode<T>* q = p->right;
                delete p;
                p = q;
                q = NULL;
            }
            p = NULL;
        }
    }
    delete[] m_rowHead;
    this->m_rowHead = NULL;
    delete[] m_colHead;
    this->m_colHead = NULL;
}

template <class T>
void OrthogonalList<T>::Init()
{
    int m, n;
    T value;
    for (int i = 0; i < this->m_length; i++) {
        std::cin >> m >> n >> value;
        OrthogonalNode<T>* p = new OrthogonalNode<T>; // 生成节点
        p->row = m;
        p->col = n;
        p->element = value;
        if (this->m_rowHead[m] == NULL) {
            this->m_rowHead[m] = p;
            p->right = NULL;
        }
        else { // 寻找行表中的插入位置
            OrthogonalNode<T>* q;
            q = this->m_rowHead[m];
            while (q->right != NULL && q->right->col < n) {
                q = q->right;
            }
            p->right = q->right;
            q->right = p; // 完成插入
        }

        if (this->m_colHead[n] == NULL) {
            this->m_colHead[n] = p;
            p->down = NULL;
        }
        else { // 寻找行表中的插入位置
            OrthogonalNode<T>* q;
            q = this->m_colHead[n];
            while (q->down != NULL && q->down->row < m) {
                q = q->down;
            }
            p->down = q->down;
            q->down = p; // 完成插入
        }
    }
}

// 将list2 加到 list1 中
template <class T>
void OrthogonalList<T>::Add(const OrthogonalList<T>& list)
{
    int i = 0, k = 0;
    OrthogonalNode<T>* p1, * p2, * tmp;
    while (i <= this->m_rowLength) {
        if (this->m_rowHead[i] != NULL && list.m_rowHead[i] != NULL) {
            p1 = this->m_rowHead[i];
            p2 = list.m_rowHead[i];
            while (p1 != NULL && p2 != NULL) {
                if (p1->col == p2->col) {
                    int sum = p1->element + p2->element;
                    tmp = p1->right;
                    // 如果sum!=0，那么就调用“ChangeElement”函数来改变row行，col列的值
                    if (sum != 0) {
                        this->ChangeElement(p1->row, p1->col, sum);
                    }
                    // 如果sum==0，那么就调用“Delete”函数来删除row行，col列处的结点
                    else {
                        this->Delete(p1->row, p1->col);
                    }
                    p1 = tmp;
                    p2 = p2->right;
                }
                
                else if (p1->col < p2->col) {
                    p1 = p1->right;
                }
                // 如果是list有，this->list没有的，则将list的相应地方的节点复制并插入到this->list中的row行col列中去
                else {
                    this->Insert(p2->row, p2->col, p2->element);
                    p2 = p2->right;
                }
            }
            // 额外的处理
            if (p2 != NULL) {
                do {
                    this->Insert(p2->row, p2->col, p2->element);
                    p2 = p2->right;
                } while (p2 != NULL);
            }

        }
        else if (this->m_rowHead[i] == NULL && list.m_rowHead[i] == NULL) {

        }
        else if (this->m_rowHead[i] != NULL) {

        }
        else {
            p2 = list.m_rowHead[i];
            do {
                this->Insert(p2->row, p2->col, p2->element);
                p2 = p2->right;
            } while (p2 != NULL);
        }
        i++;
    }
}

template <class T>
void OrthogonalList<T>::Delete(int row, int col)
{
    OrthogonalNode<T>* p;
    OrthogonalNode<T>* q;

    if (this->m_rowHead[row] == NULL) {
        std::cout << "Delete Error!" << std::endl;
    }
    else {
        p = this->m_rowHead[row];
        if (p->col == col) {
            this->m_rowHead[row] = p->right;

        }
        else {
            while (p->right->col != col) {
                p = p->right;
            }
            q = p->right;
            p->right = q->right;
        }
    }

    if (this->m_colHead[col] == NULL) {
        std::cout << "Delete Error!" << std::endl;
    }
    else {
        p = this->m_colHead[col];
        if (p->row == row) {
            q = p;
            this->m_colHead[col] = p->down;
            delete q;
            q = NULL;
        }
        else {
            while (p->down->row != row) {
                p = p->down;
            }
            q = p->down;
            p->down = q->down;
            delete q;
            q = NULL;
        }
    }
}

template <class T>
void OrthogonalList<T>::ChangeElement(int row, int col, T value)
{
    OrthogonalNode<T>* p;
    p = this->m_rowHead[row];
    while (p->col != col) {
        p = p->right;
    }
    p->element = value;
}

template <class T>
void OrthogonalList<T>::Insert(int row, int col, T value)
{
    OrthogonalNode<T>* p = new OrthogonalNode<T>; // 生成节点
    p->row = row;
    p->col = col;
    p->element = value;
    if (this->m_rowHead[row] == NULL) {
        this->m_rowHead[row] = p;
        p->right = NULL;
    }
    else { // 寻找行表中的插入位置
        OrthogonalNode<T>* q;
        q = this->m_rowHead[row];
        // 如果第一个就为 p 的话就插入
        if (p->col < q->col) {
            p->right = q;
            this->m_rowHead[row] = p;
        }
        else {
            while (q->right != NULL && q->right->col < col) {
                q = q->right;
            }

            p->right = q->right;
            q->right = p; // 完成插入
        }
    }

    if (this->m_colHead[col] == NULL) {
        this->m_colHead[col] = p;
        p->down = NULL;
    }
    else { // 寻找行表中的插入位置
        OrthogonalNode<T>* q;
        q = this->m_colHead[col];
        if (p->row < q->row) {
            p->down = q;
            this->m_colHead[col] = p;
        }
        else {
            while (q->down != NULL && q->down->row < row) {
                q = q->down;
            }
            p->down = q->down;
            q->down = p; // 完成插入
        }
    }

    this->m_length++;
}

template <class T>
void OrthogonalList<T>::Print()
{
    for (int i = 0; i <= this->m_rowLength; i++) {
        if (this->m_rowHead[i] != NULL) {
            OrthogonalNode<T>* p = this->m_rowHead[i];
            while (p != NULL) {
                std::cout << p->row << " " << p->col << " " << p->element << std::endl;
                p = p->right;
            }
            p = NULL;
        }
    }
}

#endif // !_ORTHOGONALLIST_HPP_