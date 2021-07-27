#ifndef _ADJLISTGRAPH_HPP_
#define _ADJLISTGTAPH_HPP_
#include <iostream>
#include <cstring>
#include <queue>
#define INF 0x3f3f3f3f
/// <summary>
/// �ڽӱ� ��ʾͼ
/// </summary>

const int MAXNUM = 1e5;

enum GraphKinds
{
	DG, //����ͼ
	DN, //������
	UDG, //����ͼ
	UDN //������
};

template <class T>
class ArcNode
{
public:
	T adjvex; // �û�ָ�򶥵��λ��
	int weight; // Ȩֵ
	ArcNode<T>* next;

public:
	ArcNode() { }
	ArcNode(T adjvex_, ArcNode<T>* next_): adjvex(adjvex_), next(next_) { }
	ArcNode(T adjvex_, int weight_, ArcNode<T>* next_): adjvex(adjvex_), weight(weight_), next(next_) {	}
};



template <class T>
struct VertexNode
{
	T data;
	ArcNode<T>* head;
};


template <class T>
class AdjList
{
public:
	AdjList(int,int,GraphKinds);
	AdjList(const AdjList<T>&);
	~AdjList();
	bool Creat(bool, bool);
	bool DepthFirstSearch(T, T) const;
	bool BreadthFirstSearch(T, T) const;
	void Dijkstra() const;
private:
	VertexNode<T>* m_vertex; // ��Ŷ��������
	bool* visited;
	const int m_vexNum, m_arcNum;
	GraphKinds m_kind;

	int FindVex(T) const;
	bool CreatVexNode(bool);
	bool CreatArcNode(bool);
};

template <class T>
AdjList<T>::AdjList(int vexNum, int arcNum, GraphKinds kind)
	: m_vexNum(vexNum)
	, m_arcNum(arcNum)
	, m_kind(kind)
{
	this->visited = new bool[vexNum];
	std::memset(visited, 0, sizeof(visited));
	this->m_vertex = new VertexNode<T>[vexNum];
	if (this->m_vertex == NULL) {
		std::cerr << "Malloc Error!!" << std::endl;
		exit(1);
	}
}

template<class T>
AdjList<T>::AdjList(const AdjList<T>& obj)
	: m_arcNum(m_arcNum)
	, m_vexNum(m_vexNum)
	, m_kind(m_kind)
{
	for (int i = 0; i < m_vexNum; i++) {
		this->m_vertex[i] = m_vertex[i];
	}
	for (int i = 0; i < MAXNUM; i++) {
		this->visited[i] = visited[i];
	}
}


template <class T>
AdjList<T>::~AdjList()
{
	delete[] this->m_vertex;
	this->m_vertex = NULL;
	delete[] this->visited;
	this->visited = NULL;
}

template <class T>
int AdjList<T>::FindVex(T vex) const
{
	for (int i = 0; i < this->m_vexNum; i++) {
		if (this->m_vertex[i].data == vex) {
			return i;
		}
	}
	std::cerr << "Can not find vertex" << std::endl;
	return -1;
}

template <class T>
bool AdjList<T>::CreatVexNode(bool isCreatVexNode)
{
	if (isCreatVexNode) {
		for (int i = 0; i < this->m_vexNum; i++) {
			std::cin >> this->m_vertex[i].data;
			m_vertex[i].head = NULL;
		}
		return true;
	}
	else {
		for (int i = 0; i < this->m_vexNum; i++) {
			this->m_vertex[i].data = i + 1;
			m_vertex[i].head = NULL;
		}
	}
}

template <class T>
bool AdjList<T>::CreatArcNode(bool isCreatArcNode)
{
	int firstVex, nextVex, weight;
	int firstPos;
	for (int i = 0; i < this->m_arcNum; i++) {
		std::cin >> firstVex >> nextVex >> weight;
		firstPos = this->FindVex(firstVex);
		ArcNode<T>* p = new ArcNode<T>(nextVex, weight, NULL);
		if (p == NULL) {
			return false;
		}
		ArcNode<T>* q;
		if (this->m_vertex[firstPos].head == NULL) {
			this->m_vertex[firstPos].head = p;
		}
		else {
			q = this->m_vertex[firstPos].head;
			while (q->next != NULL) {
				q = q->next;
			}
			q->next = p;
		}
	}
	return true;
}

template <class T>
bool AdjList<T>::Creat(bool isCreatVexNode,bool isCreatArcNode)
{
	if (this->CreatVexNode(isCreatVexNode) == false) {
		std::cerr << "Creat Vertex Node Error!!" << std::endl;
		exit(1);
	}
	if (this->CreatArcNode(isCreatArcNode) == false) {
		std::cerr << "Creat Arc Node Error!!" << std::endl;
		exit(1);
	}
	return true;
}

// ���������������
template <class T>
bool AdjList<T>::DepthFirstSearch(T firstVex, T secondVex) const
{
	// ��¼�Ѿ��������ĵ�
	visited[this->FindVex(firstVex)] = true;
	// �������ĺ���ʱ�׶������β���㣬��������
	if (firstVex == secondVex) { 
		return false;
	}
	// ����һ��ָ�� p ָ��firstVex��������Ӧ�ĵ�һ����
	ArcNode<T>* p = this->m_vertex[this->FindVex(firstVex)].head;
	
	while (p != NULL) { // �� p ��Ϊ�գ����������
		// ��� p ������ָ��f�ĵ� ���� secondVex�������������ҷ���true
		if (p->adjvex == secondVex) {
			return true;
		}
		// ���p->adjvexû�б�����������ô������������������ӵı�
		if (visited[this->FindVex(p->adjvex)] == false) {
			return (DepthFirstSearch(p->adjvex, secondVex));
		}
		// ������һ����
		p = p->next;
	}
	// һ�������Ǳض�����false
	return false;
}

template <class T>
bool AdjList<T>::BreadthFirstSearch(T firstVex, T secondVex) const
{
	// ��¼�Ѿ��������ĵ�
	visited[this->FindVex(firstVex)] = true;
	// ��ʼ���ն���
	std::queue<T> Q;
	Q.push(firstVex);
	while (Q.empty() == false) {
		int vexPos = this->FindVex(Q.front()); // ��ͷԪ�س���
		Q.pop();
		ArcNode<T>* p = this->m_vertex[vexPos].head;
		while (p != NULL) {
			if (visited[this->FindVex(p->adjvex)] == false) {
				visited[this->FindVex(p->adjvex)] == true;
				Q.push(p->adjvex);
				if(p->adjvex == secondVex) {
					return true;
				}
			}
			p = p->next;
		}
	}
	return false;
}

template <class T>
void AdjList<T>::Dijkstra() const
{
	int i, j, k, min, p;
	bool* book = new bool[this->m_vexNum]; // ��¼�õ��Ƿ��ѱ�ȷ�����·��
	std::pair<int, int> pa [100];
	pa[0].second = 0;
	//int* distance = new int[this->m_vexNum]; // ԭ�㵽�õ�����·��
	for (int i = 1; i < this->m_vexNum; i++) {
		book[i] = false;
		// distance[i] = INF;
		pa[i].first = INF;
		pa[i].second = i;
	}
	book[0] = true; // �������뼯��
	pa[0].first = 0; //��㵽�Լ�����Ϊ0
	ArcNode<T>* q = this->m_vertex[0].head;
	min = INF;
	while (q != NULL) {
		pa[this->FindVex(q->adjvex)].first = q->weight;
		q = q->next;
	}
	// book[k] = true;

	for (i = 1; i < this->m_vexNum; i++) {//����ʣ�µĵ�
		min = INF;//��¼��ǰ�����Ȩֵ��С�Ļ�
		for (j = 0; j < this->m_vexNum; j++) {
			if (book[j] == false && pa[j].first < min) {
				min = pa[j].first;
				p = j;//��¼��̻����յ�/��ͷ
			}
		}

		book[p] = true;//����̻����յ�/��ͷ���뼯��
		for (j = 0; j < this->m_vexNum; j++)
		{
			if (book[j] == false)//�������j�ڼ���B��
			{
				q = this->m_vertex[p].head;
				while (q != NULL) {
					if (this->FindVex(q->adjvex) == j) {
						if (pa[j].first > pa[p].first + q->weight) { // �����p�㵽j���л�,�Ҵ���㵽j�������·�����ȴ��ڴ���㾭p����ת�ٵ�j���·������
							pa[j].first = pa[p].first + q->weight; // ������ɳ�(̰�ĵ�����)
						}
						break;
					}
					q = q->next;
				}
			}
		}
	}

	std::sort(pa, pa + this->m_vexNum);

	for (i = 1; i < this->m_vexNum; i++) {
		if (pa[i].first == INF) {
			std::cout << "1 " << pa[i].second + 1 << " " << "-1" << std::endl;
		}
		else {
			std::cout << "1 " << pa[i].second + 1 << " " << pa[i].first << std::endl;
		}
	}
	delete[] book;
	book = nullptr;
}

#endif // !_ADJLISTGRAPH_HPP_