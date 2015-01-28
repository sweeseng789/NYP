#pragma once
#include <iostream>
#include "Node.h"
#include "Monster.h"

using namespace std;

class CDatabase
{
private:
		CNode *head, *tail, *current, *newNode, *prev;
		
public:
	CDatabase(void);
	~CDatabase(void);
	void Insert(int newValue);
	
	CMonster monsterStuff;

	int count;

	bool Delete(int toDelete);

	void PrintAll(void);
	void PrintD();
};

