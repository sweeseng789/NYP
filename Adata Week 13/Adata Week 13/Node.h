#pragma once
class CNode
{
public:
	CNode();
	~CNode();

	void setData(int data);
	int getData();

	CNode *left;
	CNode *right;
private:
	int data;
};

