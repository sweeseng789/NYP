#pragma once

#include<iostream>
#include <string>
using std::string;
using std::cin;
using std::cout;
using std::endl;

class CMonster
{
private:
	string name;
	int level;
	int health;
		
public:
	CMonster(void);
	~CMonster(void);

	void set(const string newname, const int newlevel, const int newhealth);

	void setName(string newName);
	string getName();

	void setLevel(int newLevel);
	int getLevel();

	void setHealth(int newHealth);
	int getHealth();


	void printAll();
};

