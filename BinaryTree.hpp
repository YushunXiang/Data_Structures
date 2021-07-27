#ifndef _BINARYTREE_HPP_
#define _BINARYTREE_HPP_
#include <iostream>
#include <string>



template <class T>
class BinaryTreeNode {
public:
    BinaryTreeNode(T);
    BinaryTreeNode(T, BinaryTreeNode<T>, BinaryTreeNode<T>);
public:
    T data;
    BinaryTreeNode<T>* leftChild;
    BinaryTreeNode<T>* rightChild;
};

template <class T>
BinaryTreeNode<T>::BinaryTreeNode(T newData)
    : data(newData)
    , leftChild(nullptr)
    , rightChild(nullptr)
{
}

template <class T>
BinaryTreeNode<T>::BinaryTreeNode(T newData, BinaryTreeNode<T> newLeftChild, BinaryTreeNode<T> newRightChild)
    : data(newData)
    , leftChild(newLeftChild)
    , rightChild(newRightChild)
{
}

template <class T>
class BinaryTree {
private:
    BinaryTreeNode<T>* root;

public:
    BinaryTree(std::string); // T15
    BinaryTree(); //T16
    BinaryTree(BinaryTreeNode<T>* changeRoot);
    void sever(std::string& str, std::string& hstr); // ����ȥ������ŵķǿմ�str�ָ�������֣�hstrΪ��һ��','֮ǰ���Ӵ���strΪ֮����Ӵ�
    void PreorderTraversal(); // T15
    void InorderTraversal(); // T17
    void PostorderTraversal(); // T18
    void PreorderInput();
    void PreInorderInput(const int, const int, const int, const int, const std::string&, const std::string&); // ������������������빲ͬȷ��������
    int GetLeafNumber() const; //T16
};

template <class T>
BinaryTree<T>::BinaryTree() : root(nullptr) { }

template <class T>
BinaryTree<T>::BinaryTree(BinaryTreeNode<T>* changeRoot) : root(changeRoot) { }

template <class T>
BinaryTree<T>::BinaryTree(std::string strIn)
{
    std::string sub, hsub;
    // ���������ַ�������Ϊ1����ôһ��û���ӽڵ���
    if (strIn.size() == 1) {
        this->root = new BinaryTreeNode<T>;
        if (this->root != nullptr) {
            this->root->data = strIn[0];
            this->root->leftChild = nullptr;
            this->root->rightChild = nullptr;
        }
        else {
            std::cerr << "Malloc Error!" << std::endl;
            exit(0);
        }
    }
    else {
        this->root = new BinaryTreeNode<T>;
        if (this->root != nullptr) {
            this->root->data = strIn[0];
        }
        else {
            std::cerr << "Malloc Error!" << std::endl;
            exit(0);
        }
        
        sub = strIn.substr(1, strIn.size() - 1);
        this->sever(sub, hsub);
        BinaryTree<T> leftSon(hsub);
        BinaryTree<T> rightSon(sub);
        this->root->leftChild = leftSon.root;
        this->root->rightChild = rightSon.root;
    }
}

// ��������
template <class T>
void BinaryTree<T>::PreorderInput()
{
    char ch;
    std::cin.get(ch);
    if (ch != '\n') {
        if (ch == '#') {
            this->root = nullptr;
        }
        else {
            this->root = new BinaryTreeNode<T>;
            if (this->root != nullptr) {
                this->root->data = ch;asqw
                this->root->leftChild = nullptr;
                this->root->rightChild = nullptr;
            }
            else {
                std::cerr << "Malloc Error!" << std::endl;
                exit(0);
            }
            BinaryTree<T> leftSon;
            BinaryTree<T> rightSon;
            leftSon.PreorderInput();
            this->root->leftChild = leftSon.root;
            rightSon.PreorderInput();
            this->root->rightChild = rightSon.root;
        }
    }
}

// �õ�Ҷ����Ŀ
template <class T>
int BinaryTree<T>::GetLeafNumber() const
{
    if (this->root->rightChild == nullptr && this->root->leftChild == nullptr) {
        return 1;
    }
    else {
        int leftLeafNumber = 0, rightLeafNumber = 0;
        if (this->root->leftChild != nullptr) {
            BinaryTree<T> leftSon(this->root->leftChild);
            leftLeafNumber = leftSon.GetLeafNumber();
        }
        if (this->root->rightChild != nullptr) {
            BinaryTree<T> rithtSon(this->root->rightChild);
            rightLeafNumber = rithtSon.GetLeafNumber();
        }
        return leftLeafNumber + rightLeafNumber;
    }
}


// �������
template <class T>
void BinaryTree<T>::PreorderTraversal()
{
    if (this->root != nullptr) {
        std::cout << this->root->data;
        BinaryTree<T> leftSon(this->root->leftChild);
        BinaryTree<T> rightSon(this->root->rightChild);
        leftSon.PreorderTraversal();
        rightSon.PreorderTraversal();
        this->root->leftChild = nullptr;
        this->root->rightChild = nullptr;
        delete root;
        root = nullptr;
    }
}

// �������
template <class T>
void BinaryTree<T>::InorderTraversal()
{
    if (this->root != nullptr) {
        BinaryTree<T> leftSon(this->root->leftChild);
        BinaryTree<T> rightSon(this->root->rightChild);

        leftSon.InorderTraversal();
        std::cout << this->root->data;

        rightSon.InorderTraversal();



        this->root->leftChild = nullptr;
        this->root->rightChild = nullptr;
        delete root;
        root = nullptr;
    }
}

// �������
template <class T>
void BinaryTree<T>::PostorderTraversal()
{
    if (this->root != nullptr) {
        BinaryTree<T> leftSon(this->root->leftChild);
        BinaryTree<T> rightSon(this->root->rightChild);
        leftSon.PostorderTraversal();
        rightSon.PostorderTraversal();
        
        std::cout << this->root->data;

        this->root->leftChild = nullptr;
        this->root->rightChild = nullptr;
        delete root;
        root = nullptr;
    }
}

/// <summary>
/// 
/// example:
/// (B(#,D),C(E(#,F),#)) --> B(#,D)  &  C(E(#,F),#)
/// 
/// </summary>
/// <typeparam name="T"></typeparam>
/// <param name="str"></param>
/// <param name="hstr"></param>
template <class T>
void BinaryTree<T>::sever(std::string& str, std::string& hstr)
{
    int k = 0, i = -1; // k����δ��Ե������Ÿ���
    char ch;
    int n = str.size(); // nΪ��str�ĳ���
    std::string temp;

    do // ���������(k=0ʱ)�ĵ�1������
    {
        i++;
        ch = str[i]; // chΪ��str�ĵ�i+1���ַ� 
        if (ch == '(') { // ��δ��Ե������Ÿ���+1
            ++k;
        }
        else if (ch == ')') { // ��δ��Ե������Ÿ���-1 
            --k;
        }
    } while (i < n && ch != ',' || k != 1); // iС�ڴ�����ch����������','
    
    if (i < n) // ��str�д���������','�����ǵ�i���ַ�
    {
        hstr = str.substr(1, i - 1); // hstr���ش�str','ǰ���ַ�
        temp = str.substr(i  + 1, n - i - 2); // str���ش�str','����ַ�
        str = temp;
    }
    else // ��str�в�����','
    {
        hstr = str; // ��hstr���Ǵ�str
        str = ""; // ','�����ǿմ�
    }
}

// ������������������빲ͬȷ��������
template <class T>
void BinaryTree<T>::PreInorderInput(
    const int preLeft, const int preRight, 
    const int inLeft, const int inRight, 
    const std::string& preStr, const std::string& inStr)
{
    if (preLeft >= preRight) { return; }
    for (int i = inLeft; i < inRight; i++) {
        if (inStr[i] == preStr[preLeft]) {
            this->root = new BinaryTreeNode<T>;
            if (this->root != nullptr) {
                this->root->data = preStr[preLeft];
                this->root->leftChild = nullptr;
                this->root->rightChild = nullptr;
            }
            else {
                std::cerr << "Malloc Error!" << std::endl;
                exit(0);
            }

            BinaryTree<T> leftSon;
            BinaryTree<T> rightSon;
            // ȡ��inStr��preStr������ͬ
            leftSon.PreInorderInput(preLeft + 1, preLeft + 1 + i - inLeft, inLeft, i, preStr, inStr);
            this->root->leftChild = leftSon.root;
            // ȡ��inStr��preStr������ͬ
            rightSon.PreInorderInput(preRight - inRight + i + 1, preRight, i + 1, inRight, preStr, inStr);
            this->root->rightChild = rightSon.root;
            break;
        }
    }
}

/*********************************************************************************************************/

template <class T>
class BinarySortTree
{
public:
    BinarySortTree();
    BinarySortTree(BinaryTreeNode<T>*);
    ~BinarySortTree();
    void Destroy();
    bool PreorderInput(); // ��������
    void InorderTraversal(T, T); // �������
    void Insert(T); // �����������Ľڵ����
    void Delete(T); // �����������Ľڵ�ɾ��
    void Merge(BinarySortTree<T>& BST_2); // �����������ĺϲ�
private:
    BinaryTreeNode<T>* root;
    void DeleteNode(); // �����������Ľڵ�ɾ��
    //void MergeNode();
};

template <class T>
BinarySortTree<T>::BinarySortTree()
    : root(nullptr)
{
}

template <class T>
BinarySortTree<T>::BinarySortTree(BinaryTreeNode<T>* changeRoot)
    : root(changeRoot)
{
}

template <class T>
BinarySortTree<T>::~BinarySortTree()
{
}

// ��������
template <class T>
bool BinarySortTree<T>::PreorderInput()
{
    T ch;
    std::cin >> ch;
    if (ch == -1) {
        this->root = nullptr;
    }
    else {
        this->root = new BinaryTreeNode<T>(ch);
        BinarySortTree<T> leftSon;
        BinarySortTree<T> rightSon;
        if (leftSon.PreorderInput() == false) {
            return false;
        }
        else {
            this->root->leftChild = leftSon.root;
        }
        if (rightSon.PreorderInput() == false) {
            return false;
        }
        else {
            this->root->rightChild = rightSon.root;
        }
        
        // �жϸ��ڵ��������ӽڵ��Ƿ���������������Ľṹ
        if (this->root->leftChild != nullptr) {
            if (this->root->data <= this->root->leftChild->data) {
                return false;
            }
        }
        if (this->root->rightChild != nullptr) {
            if (this->root->data >= this->root->rightChild->data) {
                return false;
            }
        }
    }
    return true;
}

template <class T>
void BinarySortTree<T>::Destroy()
{
    if (this->root != nullptr) {
        BinarySortTree<T> leftSon(this->root->leftChild);
        BinarySortTree<T> rightSon(this->root->rightChild);
        leftSon.Destroy();
        rightSon.Destroy();
        this->root->leftChild = nullptr;
        this->root->rightChild = nullptr;
        delete root;
        root = nullptr;
    }
}

// �������
template <class T>
void BinarySortTree<T>::InorderTraversal(T low, T high)
{
    if (this->root != nullptr) {
        BinarySortTree<T> leftSon(this->root->leftChild);
        BinarySortTree<T> rightSon(this->root->rightChild);

        leftSon.InorderTraversal(low, high);
        if (this->root->data > low && this->root->data < high) {
            std::cout << this->root->data << " ";
        }
        rightSon.InorderTraversal(low, high);

        //this->root->leftChild = nullptr;
        //this->root->rightChild = nullptr;
        //delete root;
        //root = nullptr;
    }
}


template <class T>
void BinarySortTree<T>::Insert(T key)
{   
    // �������������ǿ������� key ��Ϊ�����������ĸ�
    if (this->root == nullptr) {
        BinaryTreeNode<T>* p = new BinaryTreeNode<T>(key);
        this->root = p;
        return;
    }
    // �������������ǿգ��� key ������������ĸ����бȽ�
    else {
        // a. ��� key ��ֵ���ڸ��ڵ��ֵ����ֹͣ����
        if (this->root->data == key) {
            return;
        }
        // b. ��� key ��ֵС�ڸ��ڵ��ֵ���� key ����������
        else if (this->root->data > key) {
            BinarySortTree<T> leftSon(this->root->leftChild);
            leftSon.Insert(key);
            this->root->leftChild = leftSon.root;
        }
        // c. ��� key ��ֵ���ڸ��ڵ��ֵ���� key ����������
        else {
            BinarySortTree<T> rightSon(this->root->rightChild);
            rightSon.Insert(key);
            this->root->rightChild = rightSon.root;
        }
    }
}

template <class T>
void BinarySortTree<T>::Delete(T key)
{
    if (key == this->root->data) {
        this->DeleteNode();
    }
    else if (key < this->root->data) {
        BinarySortTree<T> leftSon(this->root->leftChild);
        leftSon.Delete(key);
        this->root->leftChild = leftSon.root;
    }
    else {
        BinarySortTree<T> rightSon(this->root->rightChild);
        rightSon.Delete(key);
        this->root->rightChild = rightSon.root;
    }
}

template <class T>
void BinarySortTree<T>::DeleteNode()
{
    // �� p ΪҪɾ���Ľڵ㣬fΪ p �ĸ��ڵ� 
    // 1. p ΪҶ�ڵ㣬���ֱ�ӽ���ɾ��
    if (this->root->rightChild == nullptr && this->root->leftChild == nullptr) {
        delete this->root;
        root = nullptr;
    }
    // 2. p ֻ����������������
    else if (this->root->rightChild == nullptr) {
        BinaryTreeNode<T>* p;
        p = this->root;
        this->root = this->root->leftChild;
        delete p;
    }
    else if (this->root->leftChild == nullptr) {
        BinaryTreeNode<T>* p;
        p = this->root;
        this->root = this->root->rightChild;
        delete p;
    }
    // 3. p ����������������������
    else {
        BinaryTreeNode<T>* q;
        BinaryTreeNode<T>* s;
        // ת��Ȼ�������ߵ���ͷ
        s = this->root->leftChild;
        q = s;
        while (s->rightChild != nullptr) {
            q = s;
            s = s->rightChild;
        }
        //��s�ڵ��е�ֵ����p�ڵ��е�ֵ��ɾ�� s �ڵ㣬��ԭ s �ڵ����������Ϊ s ��˫�׽ڵ� q ��������
        this->root->data = s->data;
        q->rightChild = s->leftChild;
        delete s;
    }
}

template <class T>
void BinarySortTree<T>::Merge(BinarySortTree<T>& BST_2)
{
    // �ݹ�ϲ�
    if (BST_2.root != nullptr) {
        BinarySortTree<T> leftSon(BST_2.root->leftChild);
        this->Merge(leftSon);

        this->Insert(BST_2.root->data);

        BinarySortTree<T> rightSon(BST_2.root->rightChild);
        this->Merge(rightSon);
    }
}

#endif // !_BINARYTREE_HPP_