#ifndef WEAPON_H
#define WEAPON_H

#include <iostream>

using std::cin;
using std::cout;
using std::endl;

class CWeapon
{
public:
	CWeapon();
	~CWeapon();

	void update(float dt);
	void setWeapon(unsigned int newWeapon);
	bool returnSwordConfirmation();
	bool returnPistolConfirmation();
	bool returnSniperConfirmation();
	bool returnSMGConfirmation();
private:
	unsigned int swordNumber, pistolNumber, sniperNumber, SMGnumber;
	bool usingSword, usingPistol, usingSniper, usingSMG;
};

#endif