#pragma once
#include <iostream>
#include <Windows.h>
#include "Application.h"
#include "timer.h"
#include <ctime>

using std::cin;
using std::cout;
using std::endl;
using std::time_t;

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

	bool returnReloading();

	float returnReloadTime_Pistol();
	float returnReloadTime_Sniper();
	float returnReloadTime_SMG();

	bool returnReadyToShootPistol();
	bool returnReadyToShootSniper();
	bool returnReadyToShootSMG();

private:
	int damage;
	unsigned int ammos, rounds;
	StopWatch timer;
	time_t timer2;
	float dt;
	long long unsigned int TimeOfPress;
	float reloadTime_Pistol, reloadTime_Sniper,	reloadTime_SMG;
	bool reloadedGun;
	bool reloading;
	bool pressingMouse, pressingR;
	bool readyToShoot_Pistol, readyToShoot_Sniper, readyToShoot_SMG;
};

