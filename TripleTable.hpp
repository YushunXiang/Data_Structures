#ifndef _TRIPLETABLE_HPP_
#define _TRIPLETABLE_HPP_
#include <algorithm>
#include <iostream>
#include <cstring>

const int g_col_max = 20 + 1;
const int g_row_max = 20 + 1;

// ����һ����Ԫ���
template <class T>
struct TripleTable {
public:
    // ���Ǽ�¼�˵���Ԫ�ص��У��У�ֵ
    int row;
    int col;
    T element;

public:
    bool operator<(const TripleTable<T>& obj) const;
};

// ����ʹ��class �� struct�Ķ���ʱ������std::sort()�������������
// ��ѭ���бȽϣ����бȽϵ�ԭ�򣬶�strcut TripleTable ���� "<" �����
template <class T>
bool TripleTable<T>::operator<(const TripleTable<T>& obj) const
{
    if (this->row < obj.row) {
        return true;
    }
    else if (this->row == obj.row) {
        if (this->col < obj.col) {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

template <class T>
class TripleTable_Matrix {
private:
    // ���������������
    int m_row;
    int m_col;
    // ��Ԫ�������
    TripleTable<T>* m_table;
    // ϡ������Ԫ�ظ���
    int m_length;

public:
    TripleTable_Matrix(int row, int col, int length); // ���캯��
    TripleTable_Matrix(const TripleTable_Matrix<T>&); // �������캯��
    ~TripleTable_Matrix(); // ��������
    void Init(); // ��ʼ������������Ķ�����и�ֵ������
    void Transfer(); // ת�ú�������sort������ʱ�临�Ӷ�O(n*logn)��
    void FastTransfer(const TripleTable_Matrix<T>&); // ����ת�ú�����ʱ�临�Ӷ�O(n)
    void Add(const TripleTable_Matrix<T>&, const TripleTable_Matrix<T>&); // ��Ԫ�����Ӻ���
    void Multiply(const TripleTable_Matrix<T>&, const TripleTable_Matrix<T>&); // ϡ�����˷�����
    void Print(); //����Ԫ������ʽ��ӡ
    int GetLength() const; // �õ���Ԫ���ĳ��ȣ���ϡ��������Ԫ�ظ�����
};

// ���캯��
template <class T>
TripleTable_Matrix<T>::TripleTable_Matrix(int row, int col, int length):
    m_row(row),
    m_col(col),
    m_length(length)
{
    this->m_table = new TripleTable<T>[this->m_length + 2];
}

// �������캯��
template <class T>
TripleTable_Matrix<T>::TripleTable_Matrix(const TripleTable_Matrix<T>& obj)
    : m_row(obj.m_row)
    , m_col(obj.m_col)
    , m_length(obj.m_length)
{
    for (int i = 0; i < this->m_length; i++) {
        this->m_table[i] = obj.m_table[i];
    }
}

// ���������������ڴ�
template <class T>
TripleTable_Matrix<T>::~TripleTable_Matrix()
{
    delete[] this->m_table;
    this->m_table = NULL;
}

template <class T>
int TripleTable_Matrix<T>::GetLength() const
{
    return this->m_length;
}

// ��ʼ�������� ������ 0 0 0 ֹͣ
template <class T>
void TripleTable_Matrix<T>::Init()
{
    for (int i = 1; i <= this->m_length; i++) {
        std::cin >> this->m_table[i].row >> this->m_table[i].col >> this->m_table[i].element;
        if (this->m_table[i].row > this->m_row || this->m_table[i].col > this->m_col) {
            std::cerr << "Input error! Exceeds number of rows or columns!" << std::endl;
        }
        if (this->m_table[i].row == 0 && this->m_table[i].col == 0 && this->m_table[i].element == 0) {
            this->m_length = i - 1;
            break;
        }
    }
}

// ��Ԫ���ת�ú���
// ֱ�ӽ����жԵ������ǲ��������е�˳��
template <class T>
void TripleTable_Matrix<T>::Transfer()
{
    for (int i = 1; i <= this->m_length; i++) {
        std::swap(this->m_table[i].col, this->m_table[i].row);
    }

    // ����strcut TripleTable ���� "<" �������std::sort()������this->m_table��������
    // �Դﵽһ��һ��˳���������
    std::sort(this->m_table + 1, this->m_table + m_length + 1);
}

// ��Ԫ���ת�ú���
// ֱ�ӽ����жԵ����������е�˳��
template <class T>
void TripleTable_Matrix<T>::FastTransfer(const TripleTable_Matrix<T>& table)
{
    int col, p, q, t;
    
    int num[g_col_max];
    int cpos[g_col_max];

    // ����þ�����ڷ�0Ԫ
    if (this->m_length > 0) {
        // NUM����ȫ��Ϊ0
        std::memset(num, 0, sizeof(num));
        // ���ݾ��� table����num������г�ʼ��
        for (t = 1; t <= table.m_length; t++) {
            num[table.m_table[t].col]++;
        }
        // ��ʼ��cpos����
        cpos[1] = 1;
        for (col = 2; col <= table.m_col; col++) {
            cpos[col] = cpos[col - 1] + num[col - 1];
        }
        // ����num��cpot���Ծ��� a ����ת��
        for (p = 1; p <= table.m_length; p++) {
            col = table.m_table[p].col;
            q = cpos[col];
            this->m_table[q].row = table.m_table[p].col;
            this->m_table[q].col = table.m_table[p].row;
            this->m_table[q].element = table.m_table[p].element;
            cpos[col]++;
        }
    }
}

// ��Ԫ������
// ��table1 �� table2 ����� this->m_table ��
template <class T>
void TripleTable_Matrix<T>::Add(const TripleTable_Matrix<T>& table1, const TripleTable_Matrix<T>& table2)
{
    int i = 1, j = 1, k = 1;
    while (i <= table1.m_length && j <= table2.m_length) {
        // ��ѭ���бȽϣ����бȽϵ�ԭ��
        if (table1.m_table[i].row == table2.m_table[j].row) {
            if (table1.m_table[i].col == table2.m_table[j].col) {
                // �������Ԫ�����Ϊ0����ɾ������Ԫ��
                if (table1.m_table[i].element + table2.m_table[j].element == 0) {
                    i++;
                    j++;
                    continue;
                }
                this->m_table[k].row = table1.m_table[i].row;
                this->m_table[k].col = table1.m_table[i].col;
                this->m_table[k].element = table1.m_table[i].element + table2.m_table[j].element;
                i++;
                j++;
                k++;
            }
            else if (table1.m_table[i].col < table2.m_table[j].col) {
                this->m_table[k].row = table1.m_table[i].row;
                this->m_table[k].col = table1.m_table[i].col;
                this->m_table[k].element = table1.m_table[i].element;
                i++;
                k++;
            }
            else {
                this->m_table[k].row = table2.m_table[j].row;
                this->m_table[k].col = table2.m_table[j].col;
                this->m_table[k].element = table2.m_table[j].element;
                j++;
                k++;
            }
        }
        else if (table1.m_table[i].row < table2.m_table[j].row) {
            this->m_table[k].row = table1.m_table[i].row;
            this->m_table[k].col = table1.m_table[i].col;
            this->m_table[k].element = table1.m_table[i].element;
            i++;
            k++;
        }
        else {
            this->m_table[k].row = table2.m_table[j].row;
            this->m_table[k].col = table2.m_table[j].col;
            this->m_table[k].element = table2.m_table[j].element;
            j++;
            k++;
        }
    }
    while (i <= table1.m_length) {
        this->m_table[k].row = table1.m_table[i].row;
        this->m_table[k].col = table1.m_table[i].col;
        this->m_table[k].element = table1.m_table[i].element;
        i++;
        k++;
    }
    while (j <= table2.m_length) {
        this->m_table[k].row = table2.m_table[j].row;
        this->m_table[k].col = table2.m_table[j].col;
        this->m_table[k].element = table2.m_table[j].element;
        j++;
        k++;
    }
    // ���¸����Ա�ĳ���
    this->m_length = k - 1;
}

// ��Ԫ������
// ��table1 �� table2 ����� this->m_table ��
template <class T>
void TripleTable_Matrix<T>::Multiply(const TripleTable_Matrix<T>& table1, const TripleTable_Matrix<T>& table2)
{
    int arow, brow, p, q, ccol, ctemp[g_row_max] = { 0 }, t, tp;
    // ϡ�������Ԫ��ĸ�����ʼ����
    int table1_rpos[g_row_max] = { 0 };
    int table1_num[g_row_max] = { 0 };
    int table2_rpos[g_row_max] = { 0 };
    int table2_num[g_row_max] = { 0 };
    int table3_rpos[g_row_max] = { 0 };
    
    // ��ÿ�з���Ԫ�ظ���
    for (int j = 1; j <= table1.m_length; j++) {
        ++table1_num[table1.m_table[j].row]; 
    }

    // ��ʼ��ϡ�������Ԫ��ĸ�����ʼ����
    table1_rpos[1] = 1;
    for (int i = 2; i <= table1.m_length; i++) {
        table1_rpos[i] = table1_rpos[i - 1] + table1_num[i - 1];
    }

    // ��ÿ�з���Ԫ�ظ���
    for (int j = 1; j <= table2.m_length; j++) {
        ++table2_num[table2.m_table[j].row];
    }

    // ��ʼ��ϡ�������Ԫ��ĸ�����ʼ����
    table2_rpos[1] = 1;
    for (int i = 2; i <= table2.m_length; i++) {
        table2_rpos[i] = table2_rpos[i - 1] + table2_num[i - 1];
    }

    // �����һ��������в����ڵڶ���������У��򱨴��˳���
    if (table1.m_col != table2.m_row) {
        std::cerr << "Error! The columns of the first matrix are not equal to the rows of the second matrix." << std::endl;
        exit(0);
    }
    // �������������һ��Ϊ�վ���
    if (table1.m_length * table2.m_length == 0) {
        this->m_length = 0;
        return;
    }
    // �¾����ʼ��
    this->m_row = table1.m_row;
    this->m_col = table2.m_col;
    this->m_length = 0;
    
    // ��table1�ĵ�һ�п�ʼ�����һ�У�arow��table1�ĵ�ǰ��
    for (arow = 1; arow <= table1.m_row; arow++) {
        //Ԫ���ۼ�����
        std::memset(ctemp, 0, sizeof(ctemp));
        table3_rpos[arow] = this->m_length + 1;
        // tp Ϊ����Ԫ�ص�rpos������
        if (arow < table1.m_row) {
            tp = table1_rpos[arow + 1];
        }
        else {
            tp = table1.m_length + 1;
        }

        //��Q�е�arow�еķ���Ԫ
        for (p = table1_rpos[arow]; p < tp; p++) {
            brow = table1.m_table[p].col;
            //�ҵ�N�и����ƶ���������
            if (brow < table2.m_row) {
                t = table2_rpos[brow + 1];
            }
            else {
                t = table2.m_length + 1;
            }
            for (q = table2_rpos[brow]; q < t; q++) {
                ccol = table2.m_table[q].col;//�ɼ�Ԫ����N���к�
                ctemp[ccol] += table1.m_table[p].element * table2.m_table[q].element;
            }
        }
        for (ccol = 1; ccol <= this->m_col; ccol++) {//�洢����Ԫ
            // ��ctempֵ��Ϊ0���򴢴����Ԫ��
            if (ctemp[ccol] != 0) {
                this->m_length++;
                this->m_table[this->m_length].row = arow;
                this->m_table[this->m_length].col = ccol;
                this->m_table[this->m_length].element = ctemp[ccol];
            }
        }
    }
}


// ��ӡ����
template <class T>
void TripleTable_Matrix<T>::Print()
{
    for (int i = 1; i <= this->m_length; i++) {
        std::cout << this->m_table[i].row << " " << this->m_table[i].col << " " << this->m_table[i].element << std::endl;
    }
}

#endif // !_TRIPLETABLE_HPP_