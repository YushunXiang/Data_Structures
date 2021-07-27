#pragma once

#include "main.h"

#ifndef _SeqQueue_h_
#define _SeqQueue_h_

class SeqQueue
{
public:
	SeqQueue(int length);
	SeqQueue(const SeqQueue&);
	~SeqQueue();
	void Push(ElementType X);
	void Pop();
	ElementType Front() const;
	bool Empty() const;
	bool Full() const;
private:
	int maxQueueLength;
	ElementType* element;
	int front;
	int rear;
};

#endif

