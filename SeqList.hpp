#ifndef _SEQLIST_HPP_
#define _SEQLIST_HPP_
#include <iostream>


template <class T>
class SeqList {
private:
    T* List;
    int MaxSize;
    int Last;

public:
    SeqList();
    ~SeqList();
    int Find(T X);
    void InsertElement(T X, int i);
    void DeleteElement(int i);
    T FindKth(int K) const;
    int Length() const;
    int Upper_BoundFind(T X);
    void Reverse();
};

template <class T>
void DuplicateRemoval_Seq(SeqList<T>&, SeqList<T>&, SeqList<T>&);

template <class T>
SeqList<T>::SeqList()
{
    MaxSize = (int)1e5;
    Last = -1;
    List = new T[MaxSize];
}

template <class T>
SeqList<T>::~SeqList()
{
    delete[] List;
    List = NULL;
}

// 按值查找
// 返回 X 第一次出现的下标
template <class T>
int SeqList<T>::Find(T X)
{
    int i = 0;
    while (i <= Last && *(List + i) != X) {
        i++;
    }
    if (i > Last) { //如果没找到，返回 -1
        return -1;
    }
    else { // 找到后返回下标
        return i;
    }
}

// 插入（向前插入）
template <class T>
void SeqList<T>::InsertElement(T X, int i) //i 表示插入元素的位置
{
    int j;
    if (Last == MaxSize - 1) { //位置已满
        printf("表满");
        return;
    }
    if (i < 0 || i > Last + 1) { //位置越界，如果将数插入 L->Data[L->Last+1]，下面都不用腾位置了
        printf("位置不合法");
        return;
    }
    for (j = Last; j >= i; j--) { // 从后往前依次向后挪一个，给 a[i]腾出位置
        *(List + j + 1) = *(List + j);
    }
    *(List + i) = X; //新元素插入
    Last++; // Last仍然指向最后元素
    return;
}

// 删除
// 删除 i 位置的元素，并将后面的元素填补删除元素的空缺
template <class T>
void SeqList<T>::DeleteElement(int i)
{
    int j;
    if (i < 0 || i > Last) { //位置越界，而删除最多到 L->Data[L->Last]
        printf("L->Data[%d]不存在元素", i);
        return;
    }
    for (j = i; j <= Last; j++) { // 从前往后依次向前挪一个，将 a[i] 覆盖了
        List[j - 1] = List[j];
    }
    Last--; // Last仍然指向最后元素
    return;
}

// 按序查找
// 想要在顺序表中找到下标为 K 的数
template <class T>
T SeqList<T>::FindKth(int K) const
{
    // 严谨的，我们要先判断下标是不是越界了
    if (K < 0 || Last < K) {
        printf("L->Data[%d]不存在元素", K);
        return 0;
    }
    return List[K];
}

//表长
template <class T>
int SeqList<T>::Length() const
{
    return Last + 1;
}

// 严书习题2.11
// 适用于单调递增的顺序表，按要求找到插入的位置
template <class T>
int SeqList<T>::Upper_BoundFind(T X)
{
    int i;
    for (i = 0; i <= Last; i++) {
        if (X < List[i]) {
            break;
        }
    }
    return i;
}

// 严书 习题 2.21
// 顺序表的逆置
template <class T>
void SeqList<T>::Reverse()
{
    if (Last == 0) {
        return;
    }

    int i = 0, j = Last;
    while (i < j) {
        std::swap(List[i], List[j]);
        i++;
        j--;
    }
}

template <class T>
void DuplicateRemoval_Seq(SeqList<T>& Seq_1, SeqList<T>& Seq_2, SeqList<T>& Seq_3)
{
    int i = 0, j = 0, k = 0;
    while (i < Seq_1.Length() && j < Seq_2.Length() && k < Seq_3.Length()) {
        if (Seq_2.FindKth(j) == Seq_3.FindKth(k)) {
            if (Seq_1.FindKth(i) == Seq_2.FindKth(j)) {
                i++;
                j++;
                k++;
            }
            else if (Seq_1.FindKth(i) < Seq_2.FindKth(j)) {
                std::cout << Seq_1.FindKth(i) << " ";
                i++;
            }
            else {
                j++;
                k++;
            }
        }
        else if (Seq_2.FindKth(j) < Seq_3.FindKth(k)) {
            j++;
        }
        else {
            k++;
        }
    }
    while (i < Seq_1.Length()) {
        std::cout << Seq_1.FindKth(i) << " ";
        i++;
    }
}

















#endif // !_SEQLIST_HPP_




