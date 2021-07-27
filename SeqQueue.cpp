#include "SeqQueue.h"
// ���캯��
SeqQueue::SeqQueue(int length) :front(0), rear(0) 
{
	this->maxQueueLength = length;
	this->element = new ElementType[maxQueueLength];
}

// �������캯��
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

// ɾ��������ǰ�������
// �� front ָ������������1λ
void SeqQueue::Pop()
{
	front = (front + 1) % maxQueueLength;
}

// ����Ԫ�ص�����
void SeqQueue::Push(ElementType X)
{
	element[rear] = X;
	rear = (rear + 1) % maxQueueLength;
}

// ���ض���ͷ��Ԫ��
ElementType SeqQueue::Front() const
{
	return element[front];
}

// �ж϶����Ƿ�Ϊ��
// ���Ϊ�գ��򷵻�true
bool SeqQueue::Empty() const
{
	return front == rear;
}

bool SeqQueue::Full() const
{
	return front == rear;
}