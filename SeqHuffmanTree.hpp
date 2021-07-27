#ifndef _SEQHUFFMANTREE_HPP_
#define _SEQHUFFMANTREE_HPP_
#include <cstdio>
#include <iostream>
#include <string>
#define MAXVALUE 10000 // 叶结点的权值最大值
#define MAXBIT 100 // 最大编码位数

class HuffmanTreeNode {
public:
    friend class HuffmanTree;
    HuffmanTreeNode(); // constructor
private :
    int m_weight; // 权重
    char m_char; // 字符，若 m_char == 0，则表示此处无字符
    int m_parent, m_leftChild, m_rightChild; // 该节点的 父节点 和 左右子节点
};

HuffmanTreeNode::HuffmanTreeNode()
    : m_weight(0)
    , m_char(0)
    , m_parent(-1) // -1表示 parent 没有指向
    , m_leftChild(-1)
    , m_rightChild(-1)
{
}

class HuffmanCode {
public:
    friend class HuffmanTree;
private:
    int weight; // 结点的权值
    char sign;
    char bit[MAXBIT]; // 存放编码序列的数组
    int start; // 编码的起始下标
}; // 动态分配数组存储哈夫曼编码

class HuffmanTree {
public:
    HuffmanTree(unsigned int charNumber); // constructor
    void HuffmanTreeing(const int* weight, const char* ch); // 构造哈夫曼树
    void select(int i, int& x1, int& x2) const; // 返回哈夫曼树this->m_root的前i个结点中权值最小和权值次小的树的根结点序号
    void HuffmanCoding(HuffmanCode* HC); // 求n个字符(叶子结点)的哈夫曼编码HC
    std::string StringToCodes(HuffmanCode* HC, const std::string& Str);
    std::string CodesToString(const std::string& Coding);
private:
    HuffmanTreeNode* m_root; // 用于动态申请huffman tree的数组
    unsigned int m_charNumber; // 字符数
};


HuffmanTree::HuffmanTree(unsigned int charNumber)
    : m_charNumber(charNumber)
{
    if (charNumber == 0) {
        std::cerr << "char number equal 0, will lead malloc error!" << std::endl;
        exit(1);
    }
    else { // 分配哈夫曼树的存储空间
        this->m_root = new HuffmanTreeNode[2 * charNumber - 1];
    }
}

void HuffmanTree::select(int i, int& x1, int& x2) const
{ // 返回哈夫曼树this->m_root的前i个结点中权值最小和权值次小的树的根结点序号
    // x1为其中序号(权值)较小的, x2为其中序号(权值)次小的
    int m1, m2;
    m1 = m2 = MAXVALUE; // 初值为权值最大值
    x1 = x2 = 0;
    for (int j = 0; j < i; j++) {
        if (this->m_root[j].m_weight < m1 && this->m_root[j].m_parent == -1) {
            m2 = m1;
            x2 = x1;
            m1 = this->m_root[j].m_weight;
            x1 = j;
        }
        else if (this->m_root[j].m_weight < m2 && this->m_root[j].m_parent == -1) {
            m2 = this->m_root[j].m_weight;
            x2 = j;
        }
    }
} // select

void HuffmanTree::HuffmanTreeing(const int* weight, const char* ch)
{ // w中存放n个权值,构造n个叶子结点的哈夫曼树this->m_root
    unsigned int i;
    int s1, s2;
    
    for (i = 0; i < this->m_charNumber; i++) // 数组初始化
    {
            this->m_root[i].m_weight = weight[i];
            this->m_root[i].m_char = ch[i];
    }

    for (i = this->m_charNumber; i < 2 * this->m_charNumber - 1; i++) // 构造哈夫曼树的n-1个非叶子结点
    {
        this->select(i, s1, s2); // 选择两根结点权值最小和次小的两棵二叉树
            // 新二叉树存放在数组的第i个分量中,其权值是s1和s2的权值之和
        this->m_root[i].m_weight = this->m_root[s1].m_weight + this->m_root[s2].m_weight;
        this->m_root[i].m_leftChild = s1; //新二叉树的左右孩子分别是s1和s2
        this->m_root[i].m_rightChild = s2;
        this->m_root[s1].m_parent = this->m_root[s2].m_parent = i; // 数组的第i个分量是s1和s2的双亲
    }

} // HuffmanTreeing

void HuffmanTree::HuffmanCoding(HuffmanCode* HC)
{ // 求n个字符(叶子结点)的哈夫曼编码HC
    unsigned int i, j;
    int child, parent;
    HuffmanCode cd; // 临时存放编码
    for (i = 0; i < this->m_charNumber; i++) // 求n个叶子的哈夫曼编码
    {
        HC[i].sign = this->m_root[i].m_char;
        cd.start = MAXBIT - 1; // 不等长编码的最后一位为MAXBIT-1
        cd.weight = this->m_root[i].m_weight; // 取得编码对应的权值
        child = i; // 从第i个叶结点开始
        parent = this->m_root[child].m_parent; // parent指向child双亲结点
        while (parent != -1) {
            if (this->m_root[parent].m_leftChild == child) // child是其双亲的左孩子
                cd.bit[cd.start] = '0'; // 其分枝赋值为'0'
            else // child是其双亲的右孩子
                cd.bit[cd.start] = '1'; // 其分枝赋值为'1'
            cd.start--; // 起始位置向前进一位
            child = parent; // child指向其双亲
            parent = this->m_root[child].m_parent; // parent指向child双亲结点
        }

        for (j = cd.start + 1; j < MAXBIT; j++) {
            HC[i].bit[j] = cd.bit[j]; // 保存每个叶子的编码
        }
        HC[i].start = cd.start + 1; // 保存叶结点编码的起始位
        HC[i].weight = cd.weight; // 保存编码对应的权值
    }
} // HuffmanCoding

std::string HuffmanTree::StringToCodes(HuffmanCode* HC, const std::string& Str)
{
    std::string OutCodes;
    for (unsigned int i = 0; i < Str.size(); i++) {
        for (unsigned int j = 0; j < this->m_charNumber; j++) {
            if (Str[i] == HC[j].sign) {
                for (int k = HC[j].start; k < MAXBIT; k++) {
                    OutCodes += HC[j].bit[k];
                }
            }
        }
    }
    return OutCodes;
}


std::string HuffmanTree::CodesToString(const std::string& Coding)
{
    std::string OutStr;
    unsigned int count = 0;
    int parent = 2 * this->m_charNumber - 2;
    while (count < Coding.size()) {
        while (this->m_root[parent].m_char == 0) {
            if (Coding[count] == '0') {
                parent = this->m_root[parent].m_leftChild;
            }
            else {
                parent = this->m_root[parent].m_rightChild;
            }
            count++;
        }
        OutStr += this->m_root[parent].m_char;
        parent = 2 * this->m_charNumber - 2;
    }
    return OutStr;
}



#endif // !_SeqHuffmanTree_HPP_

