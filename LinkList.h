#pragma once
#include <iostream>
#include "Node.h"

using namespace std;

class CLinkList
{
private:
		CNode *head, *tail, *current, *newNode, *prev;
public:
	CLinkList(void);
	~CLinkList(void);

	void InsertForward(int newValue);
	void InsertBackward(int newValue);
	void CheckNumber(int newValue);


	bool Delete(int toDelete);

	void PrintAll(void);
};

