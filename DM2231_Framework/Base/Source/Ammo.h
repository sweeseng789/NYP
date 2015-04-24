#pragma once
#include <iostream>
#include <Windows.h>
#include "Application.h"

using std::cin;
using std::cout;
using std::endl;

class CAmmo
{
public:
	CAmmo(void);
	~CAmmo(void);

	void update(float dt, bool usingSword, bool usingPistol, bool usingSniper, bool usingSMG);

	void setBulletandRounds(const int newAmmos, const int newRounds);

	unsigned int returnAmmos();
	unsigned int returnRounds();
	int returnDamage();

private:
	int damage;
	unsigned int ammos, rounds;
};

