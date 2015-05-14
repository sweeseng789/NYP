#ifndef WEAPON_H
#define WEAPON_H

#include <iostream>
#include <Windows.h>
#include <string>
#include "SMGClass.h"
#include "SniperClass.h"
#include "SwordClass.h"
#include "PistolClass.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

class CWeapon : public PistolClass
{
public:
	CWeapon();
	~CWeapon();

	void update(float dt);
	void setWeapon(unsigned int newWeapon, string newType);
	bool returnSwordConfirmation();
	bool returnPistolConfirmation();
	bool returnSniperConfirmation();
	bool returnSMGConfirmation();
	bool returnAmmos();
	bool returnRounds();

	string returnWeaponType();

	unsigned int returnSwordNumber();
	unsigned int returnPistolNumber();
	unsigned int returnSniperNumber();
	unsigned int returnSMGNumber();

	CAmmo ammo1, ammo2, ammo3, ammo4;
private:
	unsigned int swordNumber, pistolNumber, sniperNumber, SMGnumber, bullet, rounds;
	bool usingSword, usingPistol, usingSniper, usingSMG;
	string type;
};

#endif