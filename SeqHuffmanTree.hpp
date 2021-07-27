#ifndef _SEQHUFFMANTREE_HPP_
#define _SEQHUFFMANTREE_HPP_
#include <cstdio>
#include <iostream>
#include <string>
#define MAXVALUE 10000 // Ҷ����Ȩֵ���ֵ
#define MAXBIT 100 // ������λ��

class HuffmanTreeNode {
public:
    friend class HuffmanTree;
    HuffmanTreeNode(); // constructor
private :
    int m_weight; // Ȩ��
    char m_char; // �ַ����� m_char == 0�����ʾ�˴����ַ�
    int m_parent, m_leftChild, m_rightChild; // �ýڵ�� ���ڵ� �� �����ӽڵ�
};

HuffmanTreeNode::HuffmanTreeNode()
    : m_weight(0)
    , m_char(0)
    , m_parent(-1) // -1��ʾ parent û��ָ��
    , m_leftChild(-1)
    , m_rightChild(-1)
{
}

class HuffmanCode {
public:
    friend class HuffmanTree;
private:
    int weight; // ����Ȩֵ
    char sign;
    char bit[MAXBIT]; // ��ű������е�����
    int start; // �������ʼ�±�
}; // ��̬��������洢����������

class HuffmanTree {
public:
    HuffmanTree(unsigned int charNumber); // constructor
    void HuffmanTreeing(const int* weight, const char* ch); // �����������
    void select(int i, int& x1, int& x2) const; // ���ع�������this->m_root��ǰi�������Ȩֵ��С��Ȩֵ��С�����ĸ�������
    void HuffmanCoding(HuffmanCode* HC); // ��n���ַ�(Ҷ�ӽ��)�Ĺ���������HC
    std::string StringToCodes(HuffmanCode* HC, const std::string& Str);
    std::string CodesToString(const std::string& Coding);
private:
    HuffmanTreeNode* m_root; // ���ڶ�̬����huffman tree������
    unsigned int m_charNumber; // �ַ���
};


HuffmanTree::HuffmanTree(unsigned int charNumber)
    : m_charNumber(charNumber)
{
    if (charNumber == 0) {
        std::cerr << "char number equal 0, will lead malloc error!" << std::endl;
        exit(1);
    }
    else { // ������������Ĵ洢�ռ�
        this->m_root = new HuffmanTreeNode[2 * charNumber - 1];
    }
}

void HuffmanTree::select(int i, int& x1, int& x2) const
{ // ���ع�������this->m_root��ǰi�������Ȩֵ��С��Ȩֵ��С�����ĸ�������
    // x1Ϊ�������(Ȩֵ)��С��, x2Ϊ�������(Ȩֵ)��С��
    int m1, m2;
    m1 = m2 = MAXVALUE; // ��ֵΪȨֵ���ֵ
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
{ // w�д��n��Ȩֵ,����n��Ҷ�ӽ��Ĺ�������this->m_root
    unsigned int i;
    int s1, s2;
    
    for (i = 0; i < this->m_charNumber; i++) // �����ʼ��
    {
            this->m_root[i].m_weight = weight[i];
            this->m_root[i].m_char = ch[i];
    }

    for (i = this->m_charNumber; i < 2 * this->m_charNumber - 1; i++) // �������������n-1����Ҷ�ӽ��
    {
        this->select(i, s1, s2); // ѡ���������Ȩֵ��С�ʹ�С�����ö�����
            // �¶��������������ĵ�i��������,��Ȩֵ��s1��s2��Ȩֵ֮��
        this->m_root[i].m_weight = this->m_root[s1].m_weight + this->m_root[s2].m_weight;
        this->m_root[i].m_leftChild = s1; //�¶����������Һ��ӷֱ���s1��s2
        this->m_root[i].m_rightChild = s2;
        this->m_root[s1].m_parent = this->m_root[s2].m_parent = i; // ����ĵ�i��������s1��s2��˫��
    }

} // HuffmanTreeing

void HuffmanTree::HuffmanCoding(HuffmanCode* HC)
{ // ��n���ַ�(Ҷ�ӽ��)�Ĺ���������HC
    unsigned int i, j;
    int child, parent;
    HuffmanCode cd; // ��ʱ��ű���
    for (i = 0; i < this->m_charNumber; i++) // ��n��Ҷ�ӵĹ���������
    {
        HC[i].sign = this->m_root[i].m_char;
        cd.start = MAXBIT - 1; // ���ȳ���������һλΪMAXBIT-1
        cd.weight = this->m_root[i].m_weight; // ȡ�ñ����Ӧ��Ȩֵ
        child = i; // �ӵ�i��Ҷ��㿪ʼ
        parent = this->m_root[child].m_parent; // parentָ��child˫�׽��
        while (parent != -1) {
            if (this->m_root[parent].m_leftChild == child) // child����˫�׵�����
                cd.bit[cd.start] = '0'; // ���֦��ֵΪ'0'
            else // child����˫�׵��Һ���
                cd.bit[cd.start] = '1'; // ���֦��ֵΪ'1'
            cd.start--; // ��ʼλ����ǰ��һλ
            child = parent; // childָ����˫��
            parent = this->m_root[child].m_parent; // parentָ��child˫�׽��
        }

        for (j = cd.start + 1; j < MAXBIT; j++) {
            HC[i].bit[j] = cd.bit[j]; // ����ÿ��Ҷ�ӵı���
        }
        HC[i].start = cd.start + 1; // ����Ҷ���������ʼλ
        HC[i].weight = cd.weight; // ��������Ӧ��Ȩֵ
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

