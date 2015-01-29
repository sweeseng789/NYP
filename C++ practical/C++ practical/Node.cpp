#include "Node.h"
#include <iostream>


CNode::CNode(void)
{
	data = -1;
	next = NULL;
	back = NULL;
	parameters = new CMonster();
}

CNode:: CNode(int newValue)
{
	data = newValue;
	next = NULL;
	back = NULL;
	parameters = new CMonster();
}

CNode::~CNode(void)
{
}
