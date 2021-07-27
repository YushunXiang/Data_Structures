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

// ��ֵ����
// ���� X ��һ�γ��ֵ��±�
template <class T>
int SeqList<T>::Find(T X)
{
    int i = 0;
    while (i <= Last && *(List + i) != X) {
        i++;
    }
    if (i > Last) { //���û�ҵ������� -1
        return -1;
    }
    else { // �ҵ��󷵻��±�
        return i;
    }
}

// ���루��ǰ���룩
template <class T>
void SeqList<T>::InsertElement(T X, int i) //i ��ʾ����Ԫ�ص�λ��
{
    int j;
    if (Last == MaxSize - 1) { //λ������
        printf("����");
        return;
    }
    if (i < 0 || i > Last + 1) { //λ��Խ�磬����������� L->Data[L->Last+1]�����涼������λ����
        printf("λ�ò��Ϸ�");
        return;
    }
    for (j = Last; j >= i; j--) { // �Ӻ���ǰ�������Ųһ������ a[i]�ڳ�λ��
        *(List + j + 1) = *(List + j);
    }
    *(List + i) = X; //��Ԫ�ز���
    Last++; // Last��Ȼָ�����Ԫ��
    return;
}

// ɾ��
// ɾ�� i λ�õ�Ԫ�أ����������Ԫ���ɾ��Ԫ�صĿ�ȱ
template <class T>
void SeqList<T>::DeleteElement(int i)
{
    int j;
    if (i < 0 || i > Last) { //λ��Խ�磬��ɾ����ൽ L->Data[L->Last]
        printf("L->Data[%d]������Ԫ��", i);
        return;
    }
    for (j = i; j <= Last; j++) { // ��ǰ����������ǰŲһ������ a[i] ������
        List[j - 1] = List[j];
    }
    Last--; // Last��Ȼָ�����Ԫ��
    return;
}

// �������
// ��Ҫ��˳������ҵ��±�Ϊ K ����
template <class T>
T SeqList<T>::FindKth(int K) const
{
    // �Ͻ��ģ�����Ҫ���ж��±��ǲ���Խ����
    if (K < 0 || Last < K) {
        printf("L->Data[%d]������Ԫ��", K);
        return 0;
    }
    return List[K];
}

//��
template <class T>
int SeqList<T>::Length() const
{
    return Last + 1;
}

// ����ϰ��2.11
// �����ڵ���������˳�����Ҫ���ҵ������λ��
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

// ���� ϰ�� 2.21
// ˳��������
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




