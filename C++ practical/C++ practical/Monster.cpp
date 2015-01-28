#include "Monster.h"


CMonster::CMonster(void)
{
	level = health = 0;
}


CMonster::~CMonster(void)
{
}

void CMonster::set(const string newname, const int newlevel, const int newhealth)
{
	name = newname;
	level = newlevel;
	health = newhealth;
}

void CMonster::setHealth(int newHealth)
{
	health = newHealth;
}

void CMonster::setLevel(int newLevel)
{
	level = newLevel;
}

void CMonster::setName(string newName)
{
	name = newName;
}

int CMonster::getHealth()
{
	return health;
}

int CMonster::getLevel()
{
	return level;
}

string CMonster::getName()
{
	return name;
}

void CMonster::printAll()
{
	cout << "Monster's name: " << name << endl;
	cout << "Monster's level: " << level << endl;
	cout << "Monster's health: " << health << endl;
}