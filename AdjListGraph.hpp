#ifndef _ADJLISTGRAPH_HPP_
#define _ADJLISTGTAPH_HPP_
#include <iostream>
#include <cstring>
#include <queue>
#define INF 0x3f3f3f3f
/// <summary>
/// 邻接表 表示图
/// </summary>

const int MAXNUM = 1e5;

enum GraphKinds
{
	DG, //有向图
	DN, //有向网
	UDG, //无向图
	UDN //无向网
};

template <class T>
class ArcNode
{
public:
	T adjvex; // 该弧指向顶点的位置
	int weight; // 权值
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
	VertexNode<T>* m_vertex; // 存放顶点的数组
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

// 深度优先搜索策略
template <class T>
bool AdjList<T>::DepthFirstSearch(T firstVex, T secondVex) const
{
	// 记录已经搜索过的点
	visited[this->FindVex(firstVex)] = true;
	// 如果进入改函数时首顶点等于尾顶点，结束搜索
	if (firstVex == secondVex) { 
		return false;
	}
	// 定义一个指针 p 指向firstVex顶点所对应的第一条边
	ArcNode<T>* p = this->m_vertex[this->FindVex(firstVex)].head;
	
	while (p != NULL) { // 若 p 不为空，则继续遍历
		// 如果 p 这条边指向f的点 等于 secondVex，结束搜索，且返回true
		if (p->adjvex == secondVex) {
			return true;
		}
		// 如果p->adjvex没有被搜索过，那么就搜索这个点所由连接的边
		if (visited[this->FindVex(p->adjvex)] == false) {
			return (DepthFirstSearch(p->adjvex, secondVex));
		}
		// 遍历下一个点
		p = p->next;
	}
	// 一无所获，那必定返回false
	return false;
}

template <class T>
bool AdjList<T>::BreadthFirstSearch(T firstVex, T secondVex) const
{
	// 记录已经搜索过的点
	visited[this->FindVex(firstVex)] = true;
	// 初始化空队列
	std::queue<T> Q;
	Q.push(firstVex);
	while (Q.empty() == false) {
		int vexPos = this->FindVex(Q.front()); // 队头元素出队
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
	bool* book = new bool[this->m_vexNum]; // 记录该点是否已被确定最短路径
	std::pair<int, int> pa [100];
	pa[0].second = 0;
	//int* distance = new int[this->m_vexNum]; // 原点到该点的最短路径
	for (int i = 1; i < this->m_vexNum; i++) {
		book[i] = false;
		// distance[i] = INF;
		pa[i].first = INF;
		pa[i].second = i;
	}
	book[0] = true; // 将起点加入集合
	pa[0].first = 0; //起点到自己距离为0
	ArcNode<T>* q = this->m_vertex[0].head;
	min = INF;
	while (q != NULL) {
		pa[this->FindVex(q->adjvex)].first = q->weight;
		q = q->next;
	}
	// book[k] = true;

	for (i = 1; i < this->m_vexNum; i++) {//处理剩下的点
		min = INF;//记录当前情况下权值最小的弧
		for (j = 0; j < this->m_vexNum; j++) {
			if (book[j] == false && pa[j].first < min) {
				min = pa[j].first;
				p = j;//记录最短弧的终点/弧头
			}
		}

		book[p] = true;//将最短弧的终点/弧头加入集合
		for (j = 0; j < this->m_vexNum; j++)
		{
			if (book[j] == false)//如果顶点j在集合B中
			{
				q = this->m_vertex[p].head;
				while (q != NULL) {
					if (this->FindVex(q->adjvex) == j) {
						if (pa[j].first > pa[p].first + q->weight) { // 如果从p点到j点有弧,且从起点到j点的已有路径长度大于从起点经p点中转再到j点的路径长度
							pa[j].first = pa[p].first + q->weight; // 则进行松弛(贪心的体现)
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