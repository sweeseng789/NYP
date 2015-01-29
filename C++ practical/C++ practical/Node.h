#pragma once
#include "Monster.h"
class CNode
{
public:
	CNode(void);
	CNode(int newValue);
	~CNode(void);

	int data;
	CNode* next;
	CNode* back;
	CMonster* parameters;
};

