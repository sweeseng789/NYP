#ifndef WEAPON_H
#define WEAPON_H

#include <iostream>
#include <Windows.h>
#include <string>
#include "Application.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

class CWeapon
{
public:
	CWeapon();
	~CWeapon();

	void update();
	void weaponConfirm_Sword();
	void weaponConfirm_Pistol();
	void weaponConfirm_Sniper();
	void weaponConfirm_SMG();

	//Getter
	bool returnSwordConfirmation();
	bool returnPistolConfirmation();
	bool returnSniperConfirmation();
	bool returnSMGConfirmation();

private:
	bool usingSword, usingPistol, usingSniper, usingSMG;
};

#endif