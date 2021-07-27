#include "SeqQueue.h"
// 构造函数
SeqQueue::SeqQueue(int length) :front(0), rear(0) 
{
	this->maxQueueLength = length;
	this->element = new ElementType[maxQueueLength];
}

// 拷贝构造函数
SeqQueue::SeqQueue(const SeqQueue& q)
{
	this->maxQueueLength = q.maxQueueLength;
	this->element = q.element;
	this->front = q.front;
	this->rear = q.rear;
}

SeqQueue::~SeqQueue()
{
	delete[] element;
}

// 删除队列最前面的数据
// 即 front 指向的数据向后移1位
void SeqQueue::Pop()
{
	front = (front + 1) % maxQueueLength;
}

// 输入元素到队列
void SeqQueue::Push(ElementType X)
{
	element[rear] = X;
	rear = (rear + 1) % maxQueueLength;
}

// 返回队列头的元素
ElementType SeqQueue::Front() const
{
	return element[front];
}

// 判断队列是否为空
// 如果为空，则返回true
bool SeqQueue::Empty() const
{
	return front == rear;
}

bool SeqQueue::Full() const
{
	return front == rear;
}