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
    void sever(std::string& str, std::string& hstr); // 将脱去外层括号的非空串str分割成两部分：hstr为第一个','之前的子串，str为之后的子串
    void PreorderTraversal(); // T15
    void InorderTraversal(); // T17
    void PostorderTraversal(); // T18
    void PreorderInput();
    void PreInorderInput(const int, const int, const int, const int, const std::string&, const std::string&); // 由先序输入和中序输入共同确定二叉树
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
    // 如果输入的字符串长度为1，那么一定没有子节点了
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

// 先序输入
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

// 得到叶子数目
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


// 先序遍历
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

// 中序遍历
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

// 后序遍历
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
    int k = 0, i = -1; // k记尚未配对的左括号个数
    char ch;
    int n = str.size(); // n为串str的长度
    std::string temp;

    do // 搜索最外层(k=0时)的第1个逗号
    {
        i++;
        ch = str[i]; // ch为串str的第i+1个字符 
        if (ch == '(') { // 尚未配对的左括号个数+1
            ++k;
        }
        else if (ch == ')') { // 尚未配对的左括号个数-1 
            --k;
        }
    } while (i < n && ch != ',' || k != 1); // i小于串长且ch不是最外层的','
    
    if (i < n) // 串str中存在最外层的','，它是第i个字符
    {
        hstr = str.substr(1, i - 1); // hstr返回串str','前的字符
        temp = str.substr(i  + 1, n - i - 2); // str返回串str','后的字符
        str = temp;
    }
    else // 串str中不存在','
    {
        hstr = str; // 串hstr就是串str
        str = ""; // ','后面是空串
    }
}

// 由先序输入和中序输入共同确定二叉树
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
            // 取的inStr与preStr长度相同
            leftSon.PreInorderInput(preLeft + 1, preLeft + 1 + i - inLeft, inLeft, i, preStr, inStr);
            this->root->leftChild = leftSon.root;
            // 取的inStr与preStr长度相同
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
    bool PreorderInput(); // 先序输入
    void InorderTraversal(T, T); // 中序输出
    void Insert(T); // 二叉排序树的节点插入
    void Delete(T); // 二叉排序树的节点删除
    void Merge(BinarySortTree<T>& BST_2); // 二叉排序树的合并
private:
    BinaryTreeNode<T>* root;
    void DeleteNode(); // 二叉排序树的节点删除
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

// 先序输入
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
        
        // 判断父节点与两个子节点是否满足排序二叉树的结构
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

// 中序遍历
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
    // 若二叉排序树是空树，则 key 成为二叉排序树的根
    if (this->root == nullptr) {
        BinaryTreeNode<T>* p = new BinaryTreeNode<T>(key);
        this->root = p;
        return;
    }
    // 若二叉排序树非空，则将 key 与二叉排序树的根进行比较
    else {
        // a. 如果 key 的值等于根节点的值，则停止插入
        if (this->root->data == key) {
            return;
        }
        // b. 如果 key 的值小于根节点的值，则将 key 插入左子树
        else if (this->root->data > key) {
            BinarySortTree<T> leftSon(this->root->leftChild);
            leftSon.Insert(key);
            this->root->leftChild = leftSon.root;
        }
        // c. 如果 key 的值大于根节点的值，则将 key 插入右子树
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
    // 设 p 为要删除的节点，f为 p 的父节点 
    // 1. p 为叶节点，则可直接将其删除
    if (this->root->rightChild == nullptr && this->root->leftChild == nullptr) {
        delete this->root;
        root = nullptr;
    }
    // 2. p 只有左子树或右子树
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
    // 3. p 既有左子树，又有右子树
    else {
        BinaryTreeNode<T>* q;
        BinaryTreeNode<T>* s;
        // 转左，然后向右走到尽头
        s = this->root->leftChild;
        q = s;
        while (s->rightChild != nullptr) {
            q = s;
            s = s->rightChild;
        }
        //用s节点中的值代替p节点中的值，删除 s 节点，将原 s 节点的左子树改为 s 的双亲节点 q 的右子树
        this->root->data = s->data;
        q->rightChild = s->leftChild;
        delete s;
    }
}

template <class T>
void BinarySortTree<T>::Merge(BinarySortTree<T>& BST_2)
{
    // 递归合并
    if (BST_2.root != nullptr) {
        BinarySortTree<T> leftSon(BST_2.root->leftChild);
        this->Merge(leftSon);

        this->Insert(BST_2.root->data);

        BinarySortTree<T> rightSon(BST_2.root->rightChild);
        this->Merge(rightSon);
    }
}

#endif // !_BINARYTREE_HPP_