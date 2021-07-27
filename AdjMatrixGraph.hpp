#ifndef _ADJMATRIXGRAPH_HPP_
#define _ADJMATRIXGRAPH_HPP_
#include <iostream>
#include <cstring>

const int ADJMATRIXGRAPH_MAX = 100;
const int EDGEDISTANCE_MAX = 10000;

// 以邻接矩阵为存储结构的无向图
class AdjMatrixGraph
{
public:
	AdjMatrixGraph(int n); // 构造函数
	~AdjMatrixGraph(); // 析构函数
	void Dijkstra(int firstPoint, int* distanceList, int* path) const; // Dijkstra算法
	void Floyd(int** distance, int** path) const; // Floyd算法
private:
	int** m_adjMatrix; // 邻阶矩阵
	int m_vexNum; // 点的个数
};

AdjMatrixGraph::AdjMatrixGraph(int n) :m_vexNum(n)
{
	this->m_adjMatrix = new int* [n];
	for (int i = 0; i < n; i++) {
		this->m_adjMatrix[i] = new int[n];
	}
	//std::cout << "Please enter the adjacent matrix of the graph" << std::endl;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			std::cin >> this->m_adjMatrix[i][j];
		}
	}
}

AdjMatrixGraph::~AdjMatrixGraph()
{
	// 二维指针的析构
	for (int i = 0; i < this->m_vexNum; i++) {
		delete[] this->m_adjMatrix[i];
		this->m_adjMatrix[i] = nullptr;
	}
	delete[] this->m_adjMatrix;
	this->m_adjMatrix = nullptr;
}

void AdjMatrixGraph::Dijkstra(int firstPoint, int* distance, int* path) const
{
	int tempPoint; // 临时的点，记录上一个遍历的点
	int min, i, j;
	bool* book = new bool[this->m_vexNum]; // 一个点集，用于存放已经确定最短路径的点
	
	// 初始化各数组
	for (int i = 0; i < this->m_vexNum; i++) {
		book[i] = false; // 这时还未遍历任何一个点
		distance[i] = EDGEDISTANCE_MAX;
	}

	/*  已遍历源点，且源点到源点的距离为0 */
	book[firstPoint] = true; // 将起点加入集合
	distance[firstPoint] = 0; // 起点到自己的距离为0 //
	path[firstPoint] = -1;

	// 对从原点出发的边进行统计
	for (i = 0; i < this->m_vexNum; i++) {
		if (i != firstPoint) {
			distance[i] = this->m_adjMatrix[firstPoint][i];
			if (distance[i] < EDGEDISTANCE_MAX) {
				path[i] = firstPoint; //如果起点firstPoint与结点i之间存在边，则i的上一个结点就是 firstPoint
			}
			else {
				path[i] = -1; //如果起点 firstPoint 与结点 i 之间不存在边，给path[i]赋值 -1
			}
		}
	}

	for (i = 0; i < this->m_vexNum; i++) {
		if (i != firstPoint) {
			min = EDGEDISTANCE_MAX;
			tempPoint = 0;
			for (j = 0; j < this->m_vexNum; j++) {
				if (book[j] == false && distance[j] < min) {
					min = distance[j];
					tempPoint = j; // 记录最短弧的终点
				}
			}



			book[tempPoint] = true; //将最短弧的终点/弧头加入集合

			for (j = 0; j < this->m_vexNum; j++) {
				if (book[j] == false) { //如果顶点j在集合Book中
					// 如果从p点到j点有弧,且从起点到j点的已有路径长度大于从起点经p点中转再到j点的路径长度
					if (distance[j] > distance[tempPoint] + this->m_adjMatrix[tempPoint][j]) {
						// 则进行松弛(贪心的体现)
						distance[j] = distance[tempPoint] + this->m_adjMatrix[tempPoint][j];
						path[j] = tempPoint; // 跟新path， 使 j 前一个节点为 tempPoint
					}
				}
			}
		}
	}

	delete[] book;
	book = nullptr;
}

void AdjMatrixGraph::Floyd(int** distance, int** path) const
{
	for (int i = 0; i < this->m_vexNum; i++) {
		for (int j = 0; j < this->m_vexNum; j++) {
			distance[i][j] = this->m_adjMatrix[i][j];
		}
	}

	for (int i = 0; i < this->m_vexNum; i++) {
		for (int j = 0; j < this->m_vexNum; j++) {
			path[i][j] = -1;
		}
	}

	for (int i = 0; i < this->m_vexNum; i++) {
		for (int j = 0; j < this->m_vexNum; j++) {
			for (int k = 0; k < this->m_vexNum; k++) {
				if (distance[j][k] > distance[j][i] + distance[i][k]) {
					distance[j][k] = distance[j][i] + distance[i][k];
					path[j][k] = i;
				}
			}
		}
	}
}

#endif // !_ADJMATRIXGRAPH_HPP_