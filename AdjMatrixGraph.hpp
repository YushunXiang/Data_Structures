#ifndef _ADJMATRIXGRAPH_HPP_
#define _ADJMATRIXGRAPH_HPP_
#include <iostream>
#include <cstring>

const int ADJMATRIXGRAPH_MAX = 100;
const int EDGEDISTANCE_MAX = 10000;

// ���ڽӾ���Ϊ�洢�ṹ������ͼ
class AdjMatrixGraph
{
public:
	AdjMatrixGraph(int n); // ���캯��
	~AdjMatrixGraph(); // ��������
	void Dijkstra(int firstPoint, int* distanceList, int* path) const; // Dijkstra�㷨
	void Floyd(int** distance, int** path) const; // Floyd�㷨
private:
	int** m_adjMatrix; // �ڽ׾���
	int m_vexNum; // ��ĸ���
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
	// ��άָ�������
	for (int i = 0; i < this->m_vexNum; i++) {
		delete[] this->m_adjMatrix[i];
		this->m_adjMatrix[i] = nullptr;
	}
	delete[] this->m_adjMatrix;
	this->m_adjMatrix = nullptr;
}

void AdjMatrixGraph::Dijkstra(int firstPoint, int* distance, int* path) const
{
	int tempPoint; // ��ʱ�ĵ㣬��¼��һ�������ĵ�
	int min, i, j;
	bool* book = new bool[this->m_vexNum]; // һ���㼯�����ڴ���Ѿ�ȷ�����·���ĵ�
	
	// ��ʼ��������
	for (int i = 0; i < this->m_vexNum; i++) {
		book[i] = false; // ��ʱ��δ�����κ�һ����
		distance[i] = EDGEDISTANCE_MAX;
	}

	/*  �ѱ���Դ�㣬��Դ�㵽Դ��ľ���Ϊ0 */
	book[firstPoint] = true; // �������뼯��
	distance[firstPoint] = 0; // ��㵽�Լ��ľ���Ϊ0 //
	path[firstPoint] = -1;

	// �Դ�ԭ������ı߽���ͳ��
	for (i = 0; i < this->m_vexNum; i++) {
		if (i != firstPoint) {
			distance[i] = this->m_adjMatrix[firstPoint][i];
			if (distance[i] < EDGEDISTANCE_MAX) {
				path[i] = firstPoint; //������firstPoint����i֮����ڱߣ���i����һ�������� firstPoint
			}
			else {
				path[i] = -1; //������ firstPoint ���� i ֮�䲻���ڱߣ���path[i]��ֵ -1
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
					tempPoint = j; // ��¼��̻����յ�
				}
			}



			book[tempPoint] = true; //����̻����յ�/��ͷ���뼯��

			for (j = 0; j < this->m_vexNum; j++) {
				if (book[j] == false) { //�������j�ڼ���Book��
					// �����p�㵽j���л�,�Ҵ���㵽j�������·�����ȴ��ڴ���㾭p����ת�ٵ�j���·������
					if (distance[j] > distance[tempPoint] + this->m_adjMatrix[tempPoint][j]) {
						// ������ɳ�(̰�ĵ�����)
						distance[j] = distance[tempPoint] + this->m_adjMatrix[tempPoint][j];
						path[j] = tempPoint; // ����path�� ʹ j ǰһ���ڵ�Ϊ tempPoint
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