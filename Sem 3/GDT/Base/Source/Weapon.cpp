#include "Weapon.h"

#include <irrKlang.h>

#pragma comment (lib, "irrKlang.lib")
using namespace irrklang;

ISoundEngine *sound3 = createIrrKlangDevice(ESOD_AUTO_DETECT, ESEO_MULTI_THREADED | ESEO_LOAD_PLUGINS | ESEO_USE_3D_BUFFERS);

CWeapon::CWeapon():
	usingSword	(false),
	usingPistol	(true),
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

void CWeapon::update(double dt)
{
	static double elapsedTime = 0.f;
	elapsedTime += dt;

	if (elapsedTime >= 0.3)
	{
		elapsedTime = 0.3;


		if (Application::IsKeyPressed('1'))
		{
			//weaponConfirm_Sword();
			weaponConfirm_Pistol();
			elapsedTime = 0;
			sound3->play3D("../irrKlang/media/Change.mp3", vec3df(0, 0, 0), false);
		}
		else if (Application::IsKeyPressed('2'))
		{
			sound3->play3D("../irrKlang/media/Change.mp3", vec3df(0, 0, 0), false);
			elapsedTime = 0;
			weaponConfirm_Sniper();
		}
		else if (Application::IsKeyPressed('3'))
		{
			sound3->play3D("../irrKlang/media/Change.mp3", vec3df(0, 0, 0), false);
			elapsedTime = 0;
			weaponConfirm_SMG();
		}
		else if (Application::IsKeyPressed('4'))
		{
			sound3->play3D("../irrKlang/media/Change.mp3", vec3df(0, 0, 0), false);
			elapsedTime = 0;
			weaponConfirm_SMG();
		}
	}
}