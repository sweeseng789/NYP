#include "Weapon.h"

CWeapon::CWeapon():
	usingSword	(true),
	usingPistol	(false),
	usingSniper	(false),
	usingSMG	(false)
{
}

CWeapon::~CWeapon()
{
}

bool CWeapon::returnSwordConfirmation()
{
	if (usingSword == true && usingPistol == false && usingSniper == false && usingSMG == false)
		return true;
	else
		return false;
}

bool CWeapon::returnPistolConfirmation()
{
	if (usingSword == false && usingPistol == true && usingSniper == false && usingSMG == false)
		return true;
	else
		return false;
}

bool CWeapon::returnSniperConfirmation()
{
	if (usingSword == false && usingPistol == false && usingSniper == true && usingSMG == false)
		return true;
	else
		return false;
}

bool CWeapon::returnSMGConfirmation()
{
	if (usingSword == false && usingPistol == false && usingSniper == false && usingSMG == true)
		return true;
	else
		return false;
}

void CWeapon::weaponConfirm_Sword()
{
	this->usingSword = true;
	this->usingPistol = this->usingSniper = this->usingSMG = false;
}

void CWeapon::weaponConfirm_Pistol()
{
	this->usingPistol = true;
	this->usingSword = this->usingSniper = this->usingSMG = false;
}

void CWeapon::weaponConfirm_Sniper()
{
	this->usingSniper = true;
	this->usingSword = this->usingPistol = this->usingSMG = false;
}

void CWeapon::weaponConfirm_SMG()
{
	this->usingSMG = true;
	this->usingSword = this->usingPistol = this->usingSniper = false;
}

void CWeapon::update()
{
	if (Application::IsKeyPressed('1'))
	{
		weaponConfirm_Sword();
	}
	else if (Application::IsKeyPressed('2'))
	{
		weaponConfirm_Pistol();
	}
	else if(Application::IsKeyPressed('3'))
	{
		weaponConfirm_Sniper();
	}
	else if (Application::IsKeyPressed('4'))
	{
		weaponConfirm_SMG();
	}
}