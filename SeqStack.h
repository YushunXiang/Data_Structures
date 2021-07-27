#pragma once

#include "main.h"

const int SeqStackMax = 1e5;

#ifndef _SeqStack_h_
#define _SeqStack_h_

class SeqStack
{
private:
	ElementType* Array;
	int TopOfStack;/*’ª∂•÷∏’Î*/
public:
	SeqStack();
	~SeqStack();
	void Push(ElementType X);
	void Pop();
	ElementType GetTop();
	bool IsEmpty();
};
#endif
