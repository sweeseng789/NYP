#pragma once
class CNode
{
public:
	CNode(void);
	CNode(int newValue);
	~CNode(void);

	int data;
	CNode* next;
	CNode* previous;
};

