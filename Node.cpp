#include "Node.h"
#include <iostream>


CNode::CNode(void)
{
	data = -1;
	next = NULL;
}

CNode:: CNode(int newValue)
{
	data = newValue;
	next = NULL;
}

CNode::~CNode(void)
{
}
