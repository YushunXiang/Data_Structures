#ifndef _HASHTABLE_HPP_
#define _HASHTABLE_HPP_
#include <iostream>

class HashTableNode {
public:
	friend class HashTable;
	HashTableNode();
	HashTableNode(int data, int flag);
private:
	int m_data;
	int m_flag;
};

HashTableNode::HashTableNode()
	: m_data(0)
	, m_flag(0)
{
}

HashTableNode::HashTableNode(int data, int flag)
	: m_data(data)
	, m_flag(flag)
{
}

class HashTable {
public:
	HashTable();
	~HashTable();
	void GetHashTable(); //¹¹Ôì¹þÏ£±í
	int putOutAverageSearchLength();
private:
	HashTableNode* T[11];
	int dataList[8] = { 22, 41, 53, 46, 30, 13, 01, 67 };
};

HashTable::HashTable()
{
	for (int i = 0; i < 11; i++) {
		this->T[i] = nullptr;
	}
}

HashTable::~HashTable()
{
	for (int i = 0; i < 11; i++) {
		if (this->T[i] != nullptr) {
			delete T[i];
			T[i] = nullptr;
		}
	}
}

void HashTable::GetHashTable()
{
	int pos, flag;
	for (int i = 0; i < 8; i++) {
		flag = 1;
		pos = (3 * dataList[i]) % 11;
		while (T[pos] != nullptr) {
			if (pos >= 11) {
				exit(0);
			}
			pos++;
			flag++;
		}
		T[pos] = new HashTableNode(dataList[i], flag);
	}
}

int HashTable::putOutAverageSearchLength()
{
	int sum = 0;
	for (int i = 0; i < 11; i++) {
		if (T[i] != nullptr) {
			sum += T[i]->m_flag;
		}
		
	}
	return sum / 8;
}





#endif // !_HASHTABLE_HPP_