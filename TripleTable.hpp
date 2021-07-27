#ifndef _TRIPLETABLE_HPP_
#define _TRIPLETABLE_HPP_
#include <algorithm>
#include <iostream>
#include <cstring>

const int g_col_max = 20 + 1;
const int g_row_max = 20 + 1;

// 这是一个三元组表
template <class T>
struct TripleTable {
public:
    // 这是记录了单个元素的行，列，值
    int row;
    int col;
    T element;

public:
    bool operator<(const TripleTable<T>& obj) const;
};

// 类中使用class 或 struct的对象时，想用std::sort()需先重载运算符
// 遵循先行比较，再列比较的原则，对strcut TripleTable 重载 "<" 运算符
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
    // 矩阵的行数和列数
    int m_row;
    int m_col;
    // 三元组表数列
    TripleTable<T>* m_table;
    // 稀疏矩阵的元素个数
    int m_length;

public:
    TripleTable_Matrix(int row, int col, int length); // 构造函数
    TripleTable_Matrix(const TripleTable_Matrix<T>&); // 拷贝构造函数
    ~TripleTable_Matrix(); // 析构函数
    void Init(); // 初始化函数（对类的对象进行赋值操作）
    void Transfer(); // 转置函数（含sort函数，时间复杂度O(n*logn)）
    void FastTransfer(const TripleTable_Matrix<T>&); // 快速转置函数，时间复杂度O(n)
    void Add(const TripleTable_Matrix<T>&, const TripleTable_Matrix<T>&); // 三元组表相加函数
    void Multiply(const TripleTable_Matrix<T>&, const TripleTable_Matrix<T>&); // 稀疏矩阵乘法函数
    void Print(); //以三元组表的形式打印
    int GetLength() const; // 得到三元组表的长度（即稀疏矩阵非零元素个数）
};

// 构造函数
template <class T>
TripleTable_Matrix<T>::TripleTable_Matrix(int row, int col, int length):
    m_row(row),
    m_col(col),
    m_length(length)
{
    this->m_table = new TripleTable<T>[this->m_length + 2];
}

// 拷贝构造函数
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

// 析构函数，回收内存
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

// 初始化函数， 输入至 0 0 0 停止
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

// 三元组表转置函数
// 直接将行列对调（但是不考虑行列的顺序）
template <class T>
void TripleTable_Matrix<T>::Transfer()
{
    for (int i = 1; i <= this->m_length; i++) {
        std::swap(this->m_table[i].col, this->m_table[i].row);
    }

    // 利用strcut TripleTable 重载 "<" 运算符与std::sort()函数对this->m_table进行排序
    // 以达到一行一行顺序的输出结果
    std::sort(this->m_table + 1, this->m_table + m_length + 1);
}

// 三元组表转置函数
// 直接将行列对调（考虑行列的顺序）
template <class T>
void TripleTable_Matrix<T>::FastTransfer(const TripleTable_Matrix<T>& table)
{
    int col, p, q, t;
    
    int num[g_col_max];
    int cpos[g_col_max];

    // 如果该矩阵存在非0元
    if (this->m_length > 0) {
        // NUM数组全置为0
        std::memset(num, 0, sizeof(num));
        // 根据矩阵 table，对num数组进行初始化
        for (t = 1; t <= table.m_length; t++) {
            num[table.m_table[t].col]++;
        }
        // 初始化cpos数组
        cpos[1] = 1;
        for (col = 2; col <= table.m_col; col++) {
            cpos[col] = cpos[col - 1] + num[col - 1];
        }
        // 结束num和cpot，对矩阵 a 进行转置
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

// 三元组表相加
// 将table1 和 table2 相加至 this->m_table 中
template <class T>
void TripleTable_Matrix<T>::Add(const TripleTable_Matrix<T>& table1, const TripleTable_Matrix<T>& table2)
{
    int i = 1, j = 1, k = 1;
    while (i <= table1.m_length && j <= table2.m_length) {
        // 遵循先行比较，再列比较的原则
        if (table1.m_table[i].row == table2.m_table[j].row) {
            if (table1.m_table[i].col == table2.m_table[j].col) {
                // 如果两三元组相加为0，则删除该三元表
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
    // 更新该类成员的长度
    this->m_length = k - 1;
}

// 三元组表相乘
// 将table1 和 table2 相乘至 this->m_table 中
template <class T>
void TripleTable_Matrix<T>::Multiply(const TripleTable_Matrix<T>& table1, const TripleTable_Matrix<T>& table2)
{
    int arow, brow, p, q, ccol, ctemp[g_row_max] = { 0 }, t, tp;
    // 稀疏矩阵三元组的各行起始坐标
    int table1_rpos[g_row_max] = { 0 };
    int table1_num[g_row_max] = { 0 };
    int table2_rpos[g_row_max] = { 0 };
    int table2_num[g_row_max] = { 0 };
    int table3_rpos[g_row_max] = { 0 };
    
    // 求每行非零元素个数
    for (int j = 1; j <= table1.m_length; j++) {
        ++table1_num[table1.m_table[j].row]; 
    }

    // 初始化稀疏矩阵三元组的各行起始坐标
    table1_rpos[1] = 1;
    for (int i = 2; i <= table1.m_length; i++) {
        table1_rpos[i] = table1_rpos[i - 1] + table1_num[i - 1];
    }

    // 求每行非零元素个数
    for (int j = 1; j <= table2.m_length; j++) {
        ++table2_num[table2.m_table[j].row];
    }

    // 初始化稀疏矩阵三元组的各行起始坐标
    table2_rpos[1] = 1;
    for (int i = 2; i <= table2.m_length; i++) {
        table2_rpos[i] = table2_rpos[i - 1] + table2_num[i - 1];
    }

    // 如果第一个矩阵的列不等于第二个矩阵的行，则报错并退出。
    if (table1.m_col != table2.m_row) {
        std::cerr << "Error! The columns of the first matrix are not equal to the rows of the second matrix." << std::endl;
        exit(0);
    }
    // 如果两矩阵中有一个为空矩阵
    if (table1.m_length * table2.m_length == 0) {
        this->m_length = 0;
        return;
    }
    // 新矩阵初始化
    this->m_row = table1.m_row;
    this->m_col = table2.m_col;
    this->m_length = 0;
    
    // 从table1的第一行开始到最后一行，arow是table1的当前行
    for (arow = 1; arow <= table1.m_row; arow++) {
        //元素累加清零
        std::memset(ctemp, 0, sizeof(ctemp));
        table3_rpos[arow] = this->m_length + 1;
        // tp 为该行元素的rpos的上限
        if (arow < table1.m_row) {
            tp = table1_rpos[arow + 1];
        }
        else {
            tp = table1.m_length + 1;
        }

        //求Q中第arow行的非零元
        for (p = table1_rpos[arow]; p < tp; p++) {
            brow = table1.m_table[p].col;
            //找到N中该行移动次数上限
            if (brow < table2.m_row) {
                t = table2_rpos[brow + 1];
            }
            else {
                t = table2.m_length + 1;
            }
            for (q = table2_rpos[brow]; q < t; q++) {
                ccol = table2.m_table[q].col;//成绩元素在N中列号
                ctemp[ccol] += table1.m_table[p].element * table2.m_table[q].element;
            }
        }
        for (ccol = 1; ccol <= this->m_col; ccol++) {//存储非零元
            // 若ctemp值不为0，则储存进三元组
            if (ctemp[ccol] != 0) {
                this->m_length++;
                this->m_table[this->m_length].row = arow;
                this->m_table[this->m_length].col = ccol;
                this->m_table[this->m_length].element = ctemp[ccol];
            }
        }
    }
}


// 打印函数
template <class T>
void TripleTable_Matrix<T>::Print()
{
    for (int i = 1; i <= this->m_length; i++) {
        std::cout << this->m_table[i].row << " " << this->m_table[i].col << " " << this->m_table[i].element << std::endl;
    }
}

#endif // !_TRIPLETABLE_HPP_