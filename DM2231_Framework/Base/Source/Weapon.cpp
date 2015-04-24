#include "Weapon.h"

CWeapon::CWeapon()
{
	swordNumber = pistolNumber = sniperNumber = SMGnumber = 0;
	usingSword = usingPistol = usingSniper = usingSMG = NULL;
}

CWeapon::~CWeapon()
{
}

void CWeapon::setWeapon(unsigned int newWeapon)
{
	//sword is 29
	//pistol is 30
	//sniper is 31
	//smg is 32
	if (newWeapon == 29)
		swordNumber = newWeapon;
	else if (newWeapon == 30)
		pistolNumber = newWeapon;
	else if (newWeapon == 31)
		sniperNumber = newWeapon;
	else
		SMGnumber = newWeapon;
}