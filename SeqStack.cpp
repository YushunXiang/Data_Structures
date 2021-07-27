#include "SeqStack.h"

SeqStack::SeqStack()
{
	Array = new ElementType[SeqStackMax];
	TopOfStack = -1;
}

SeqStack::~SeqStack()
{
	delete[] Array;
}

void SeqStack::Push(ElementType X)
{
	TopOfStack++;
	Array[TopOfStack] = X;
}

void SeqStack::Pop()
{
	TopOfStack--;
}

ElementType SeqStack::GetTop()
{
	return Array[TopOfStack];
}

//return true if stack is empty
bool SeqStack::IsEmpty()
{
	if (TopOfStack <= -1) {
		return true;
	}
	else {
		return false;
	}
}