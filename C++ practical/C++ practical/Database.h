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
	CMonster * Try;
	void Insert(int newValue, int newLevel, int newHealth, string newName);
	void EditRecord(int newValue, int newLevel, int newHealth, string newName);
	void EditMonsterName(int newValue, string newName);
	void EditMonsterHealth(int newValue, int newHealth);
	void EditMonsterLevel(int newValue, int newLevel);
	bool RecordValidation(int newValue);

	CMonster monsterStuff;

	int count;

	bool Delete(int toDelete);

	void PrintAll(void);
	void PrintD();
};

