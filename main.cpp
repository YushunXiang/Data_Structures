#include <iostream>
#include "GeneralList.hpp"
#include <string>

int main()
{
	std::string inStr;
	std::cin >> inStr;
	GeneralList<char> GL(inStr);

	std::cout << GL.GetDepth() << std::endl;
	return 0;
}

















//#include <iostream>
//#include "AdjMatrixGraph.hpp"
//
//
//int main()
//{
//	int n;
//	std::cin >> n;
//	int** distance, ** path;
//	// distance 的内存申请（二维指针的内存申请）
//	distance = new int* [n];
//	for (int i = 0; i < n; i++) {
//		distance[i] = new int[n];
//	}
//	// path 的内存申请
//	path = new int* [n];
//	for (int i = 0; i < n; i++) {
//		path[i] = new int[n];
//	}
//
//
//	AdjMatrixGraph graph(n);
//	graph.Floyd(distance, path);
//
//	int outNum;
//	std::cin >> outNum;
//	int firstPos, secondPos;
//	//while (outNum--) {
//	//	std::cin >> firstPos >> secondPos;
//	//	std::cout << distance[firstPos][secondPos] << std::endl;
//	//}
//
//	int count, tempPoint;
//	int* outputPoint = new int[n];
//	while (outNum--) {
//		std::cin >> firstPos >> secondPos;
//		count = 1;
//		outputPoint[0] = secondPos;
//		tempPoint = secondPos;
//		while (true) {
//			tempPoint = path[firstPos][tempPoint];
//			
//			if (tempPoint == firstPos || tempPoint == -1) {
//				outputPoint[count] = firstPos;
//				break;
//			}
//			outputPoint[count] = tempPoint;
//			count++;
//		}
//
//		while (count > -1) {
//			std::cout << outputPoint[count] << std::endl;
//			count--;
//		}
//	}
//	// distance 的内存释放（二维指针的析构）
//	for (int i = 0; i < n; i++) {
//		delete[] distance[i];
//		distance[i] = nullptr;
//	}
//
//	delete[] distance;
//	distance = nullptr;
//	// path 的内存释放
//	for (int i = 0; i < n; i++) {
//		delete[] path[i];
//		path[i] = nullptr;
//	}
//
//	delete[] path;
//	path = nullptr;
//	// outPoint 的内存释放
//	delete[] outputPoint;
//	outputPoint = nullptr;
//}

/*
5 a b c d e 12 40 15 8 25
bbbaddeccbbb

12 8 4 -1 -1 10 -1 -1 16 13 -1 -1 18 -1 -1
17 6 2 -1 -1 9 -1 -1 24 19 -1 -1 26 -1 -1

10 17
6
12


*/
/*
4
0 2 10 10000
2 0 7 3
10 7 0 6
10000 3 6 0
2
0 2
*/