#include "Weapon.h"

CWeapon::CWeapon()
{
	this->swordNumber = this->pistolNumber = this->sniperNumber = this->SMGnumber = 0;
	this->usingPistol = this->usingSniper = this->usingSMG = false;
	this->usingSword = true;
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
		this->swordNumber = newWeapon;
	}
	else if (newWeapon == 30)
	{
		this->pistolNumber = newWeapon;
		this->ammo[1].setBulletandRounds(15, 5);
		
	}
	else if (newWeapon == 31)
	{
		this->sniperNumber = newWeapon;
		this->ammo[2].setBulletandRounds(8, 2);
	}
	else
	{
		this->SMGnumber = newWeapon;
		this->ammo[3].setBulletandRounds(30, 3);
	}

	this->type = newType;
}

bool CWeapon::returnSwordConfirmation()
{
	return this->usingSword;
}
bool CWeapon::returnPistolConfirmation()
{
	return this->usingPistol;
}
bool CWeapon::returnSniperConfirmation()
{
	return this->usingSniper;
}
bool CWeapon::returnSMGConfirmation()
{
	return this->usingSMG;
}
unsigned int CWeapon::returnSwordNumber()
{
	return this->swordNumber;
}
unsigned int CWeapon::returnPistolNumber()
{
	return this->pistolNumber;
}
unsigned int CWeapon::returnSniperNumber()
{
	return this->sniperNumber;
}
unsigned int CWeapon::returnSMGNumber()
{
	return this->SMGnumber;
}
string CWeapon::returnWeaponType()
{
	return this->type;
}

void CWeapon::update(float dt)
{
	if (GetKeyState('1') < 0)
	{
		this->usingSword = true;
		this->usingPistol = this->usingSniper = this->usingSMG = false;
	}
	else if (GetKeyState('2') < 0)
	{
		this->usingPistol = true;
		this->usingSword = this->usingSniper = this->usingSMG = false;
	}
	else if(GetKeyState('3') < 0)
	{
		this->usingSniper = true;
		this->usingSword = this->usingPistol = this->usingSMG = false;
	}
	else if (GetKeyState('4') < 0)
	{
		this->usingSMG = true;
		this->usingSword = this->usingPistol = this->usingSniper = false;
	}

	//============Ammo Update===========//
	//=============PISTOL=============//
	if (this->usingSword == false && this->usingPistol == true && this->usingSniper == false && this->usingSMG == false)
	{
		this->ammo[1].update(dt, this->usingSword, this->usingPistol, this->usingSniper, this->usingSMG);
	}
	//=============SNIPER=============//
	else if (this->usingSword == false && this->usingPistol == false && this->usingSniper == true && this->usingSMG == false)
	{
		this->ammo[2].update(dt, this->usingSword, this->usingPistol, this->usingSniper, this->usingSMG);
	}
	//=============SMG=============//
	else if (this->usingSword == false && this->usingPistol == false && this->usingSniper == false && this->usingSMG == true)
	{
		this->ammo[3].update(dt, this->usingSword, this->usingPistol, this->usingSniper, this->usingSMG);
	}
}