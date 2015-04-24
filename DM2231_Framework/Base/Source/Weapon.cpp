#include "Weapon.h"

CWeapon::CWeapon()
{
	swordNumber = pistolNumber = sniperNumber = SMGnumber = 0;
	usingPistol = usingSniper = usingSMG = false;
	usingSword = true;
}

CWeapon::~CWeapon()
{
}

void CWeapon::setWeapon(unsigned int newWeapon, string newType)
{
	//sword is 29
	//pistol is 30
	//sniper is 31
	//smg is 32
	if (newWeapon == 29)
	{
		swordNumber = newWeapon;
		bullet = rounds = 0;
	}
	else if (newWeapon == 30)
	{
		pistolNumber = newWeapon;
		ammo[1].setBulletandRounds(15, 5);
	}
	else if (newWeapon == 31)
	{
		sniperNumber = newWeapon;
		ammo[2].setBulletandRounds(8, 3);
	}
	else
	{
		SMGnumber = newWeapon;
		ammo[3].setBulletandRounds(30, 3);
	}

	type = newType;
}

bool CWeapon::returnSwordConfirmation()
{
	return usingSword;
}
bool CWeapon::returnPistolConfirmation()
{
	return usingPistol;
}
bool CWeapon::returnSniperConfirmation()
{
	return usingSniper;
}
bool CWeapon::returnSMGConfirmation()
{
	return usingSMG;
}
unsigned int CWeapon::returnSwordNumber()
{
	return swordNumber;
}
unsigned int CWeapon::returnPistolNumber()
{
	return pistolNumber;
}
unsigned int CWeapon::returnSniperNumber()
{
	return sniperNumber;
}
unsigned int CWeapon::returnSMGNumber()
{
	return SMGnumber;
}
string CWeapon::returnWeaponType()
{
	return type;
}

void CWeapon::update(float dt)
{
	if (GetKeyState('1') < 0)
	{
		usingSword = true;
		usingPistol = usingSniper = usingSMG = false;
	}
	else if (GetKeyState('2') < 0)
	{
		usingPistol = true;
		usingSword = usingSniper = usingSMG = false;
	}
	else if(GetKeyState('3') < 0)
	{
		usingSniper = true;
		usingSword = usingPistol = usingSMG = false;
	}
	else if (GetKeyState('4') < 0)
	{
		usingSMG = true;
		usingSword = usingPistol = usingSniper = false;
	}

	//============Ammo Update===========//
	//=============PISTOL=============//
	if (usingSword == false && usingPistol == true && usingSniper == false && usingSMG == false)
	{
		ammo[1].update(dt, usingSword, usingPistol, usingSniper, usingSMG);
	}
	//=============SNIPER=============//
	else if (usingSword == false && usingPistol == false && usingSniper == true && usingSMG == false)
	{
		ammo[2].update(dt, usingSword, usingPistol, usingSniper, usingSMG);
	}
	//=============SMG=============//
	else if (usingSword == false && usingPistol == false && usingSniper == false && usingSMG == true)
	{
		ammo[3].update(dt, usingSword, usingPistol, usingSniper, usingSMG);
	}
}