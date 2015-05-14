#include "Ammo.h"


CAmmo::CAmmo(void):
//Int
ammos				(0),
swordNumber			(0),
pistolNumber		(0), 
sniperNumber		(0),
SMGnumber			(0),
bullet				(0),
rounds				(0),
PistolBullet		(0),
PistolDamage		(0),
PistolRound			(0),
SniperBullet		(0),
SniperDamage		(0),
SniperRound			(0),
SMGBullet			(0),
SMGDamage			(0),
SMGRound			(0),
//Float
dt					(0.f),
reloadTime_Pistol	(3.f),
reloadTime_Sniper	(5.f),
reloadTime_SMG		(4.0f),
elapsedTime1		(0.f),
shoot_Pistol		(0.f),
shoot_Sniper		(0.f),
shoot_SMG			(0.f),
//Bool
reloadedGun			(false),
pressingMouse		(false),
pressingR			(false),
reloading			(false),
readyToShoot_Pistol (false),
readyToShoot_Sniper (false),
readyToShoot_SMG	(false),	
pistolFired			(false),
SniperFired			(false),
SMGFired			(false),
usingPistol			(false),
usingSniper			(false),
usingSMG			(false),
usingSword			(true),
CreateBullet_Pistol	(false),
CreateBullet_Sniper (false),
CreateBullet_SMG	(false),
//Vector3
bulletDirection		( Vector3(0.0f, 0.0f, 0.0f)),
bulletPosition		( Vector3(0.0f, 0.0f, 0.0f)),
bulletSpeed			( Vector3(5.f, 5.f, 5.f))
{
	cout << "Ammo Created" << endl;
}

CAmmo::~CAmmo(void)
{
	cout << "Ammo Deleted" << endl;
}
void CAmmo::SetBulletandRounds_Pistol(const unsigned newAmmos_Pistol, const unsigned newRounds_Pistol)
{
	this->PistolBullet = newAmmos_Pistol;
	this->PistolRound = newRounds_Pistol;
}
void CAmmo::SetBulletandRounds_Sniper(const unsigned newAmmos_Sniper, const unsigned newRounds_Sniper)
{
	this->SniperBullet = newAmmos_Sniper;
	this->SniperRound = newRounds_Sniper;
}
void CAmmo::SetBulletandRounds_SMG(const unsigned newAmmos_SMG, const unsigned newRounds_SMG)
{
	this->SMGBullet = newAmmos_SMG;
	this->SMGRound = newRounds_SMG;
}
unsigned CAmmo::returnBullet_Pistol()
{
	return this->PistolBullet;
}
unsigned CAmmo::returnBullet_SMG()
{
	return this->SMGBullet;
}
unsigned CAmmo::returnBullet_Sniper()
{
	return this->SniperBullet;
}
unsigned CAmmo::returnRounds_Pistol()
{
	return this->PistolRound;
}
unsigned CAmmo::returnRounds_Sniper()
{
	return this->SniperRound;
}
unsigned CAmmo::returnRounds_SMG()
{
	return this->SMGRound;
}
bool CAmmo::returnReloading()
{
	return this->reloading;
}
float CAmmo::returnReloadTime_Pistol()
{
	return this->reloadTime_Pistol;
}
float CAmmo::returnReloadTime_Sniper()
{
	return this->reloadTime_Sniper;
}
float CAmmo::returnReloadTime_SMG()
{
	return this->reloadTime_SMG;
}
bool CAmmo::returnReadyToShootPistol()
{
	return this->readyToShoot_Pistol;
}
bool CAmmo::returnReadyToShootSniper()
{
	return this->readyToShoot_Sniper;
}
bool CAmmo::returnReadyToShootSMG()
{
	return this->readyToShoot_SMG;
}
bool CAmmo::returnPressingMouse()
{
	return this->pressingMouse;
}
Vector3 CAmmo::returnBulletPosition()
{
	return this->bulletPosition;
}
bool CAmmo::returnPistolFired()
{
	return this->pistolFired;
}
bool CAmmo::returnSniperFired()
{
	return this->SniperFired;
}
bool CAmmo::returnSMGFired()
{
	return this->SMGFired;
}
void CAmmo::setPistolFired(bool newValue)
{
	this->pistolFired = newValue;
}
bool CAmmo::returnSwordConfirmation()
{
	if (this->usingSword == true && this->usingPistol == false && this->usingSniper == false && this->usingSMG == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool CAmmo::returnPistolConfirmation()
{
	if (this->usingSword == false && this->usingPistol == true && this->usingSniper == false && this->usingSMG == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool CAmmo::returnSniperConfirmation()
{
	if (this->usingSword == false && this->usingPistol == false && this->usingSniper == true && this->usingSMG == false)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool CAmmo::returnSMGConfirmation()
{
	if (this->usingSword == false && this->usingPistol == false && this->usingSniper == false && this->usingSMG == true)
	{
		return true;
	}
	else
	{
		return false;
	}
}
unsigned int CAmmo::returnSwordNumber()
{
	return this->swordNumber;
}
unsigned int CAmmo::returnPistolNumber()
{
	return this->pistolNumber;
}
unsigned int CAmmo::returnSniperNumber()
{
	return this->sniperNumber;
}
unsigned int CAmmo::returnSMGNumber()
{
	return this->SMGnumber;
}
void CAmmo::ShootingTimeGap()
{
	//=========Shooting Bullet=========//
	elapsedTime1 = (float)fmod(timer.getElapsedTime(), 1);

	//=============PISTOL Shooting Gap=============//
	if (shoot_Pistol < 0.5f)
	{
		shoot_Pistol += elapsedTime1;
		this->readyToShoot_Pistol = false;
	}
	else if (shoot_Pistol >= 0.5f)
	{
		shoot_Pistol = 0.5f;
		this->readyToShoot_Pistol = true;
	}
	//=============SNIPER Shooting Gap=============//
	if (shoot_Sniper < 1.2f)
	{
		shoot_Sniper += elapsedTime1;
		this->readyToShoot_Sniper = false;
	}
	else if (shoot_Sniper >= 1.2f)
	{
		shoot_Sniper = 1.2f;
		this->readyToShoot_Sniper = true;
	}
	//=============SMG Shooting Gap=============//
	if (shoot_SMG < 0.2f)
	{
		shoot_SMG += elapsedTime1;
		this->readyToShoot_SMG = false;
	}
	else if (shoot_SMG >= 0.2f)
	{
		shoot_SMG = 0.2f;
		this->readyToShoot_SMG = true;
	}
}
void CAmmo::ButtonInput()
{
	//=============Pressing Left Mouse=============//
	if (GetKeyState(VK_LBUTTON) < 0 && this->reloading == false)
		this->pressingMouse = true;
	else
		this->pressingMouse = false;

	//=============Pressing R=============//
	if (Application::IsKeyPressed('R'))
		this->pressingR = true;
}
void CAmmo::bulletUpdate(float dt)
{
	cout << "hi" << endl;
}

void CAmmo::ShootFunction_Pistol()
{
	//=============PISTOL=============//
	if (this->returnPistolConfirmation() == true)
	{
		if (this->PistolBullet >= 0 && this->PistolRound > 0)
		{
			if (this->pressingR == true)
			{
				this->reloadTime_Pistol -= dt;
				this->reloading = true;

				if (this->reloadTime_Pistol <= 0.0f)
				{
					this->PistolRound -= 1; //minus 1 round
					this->PistolBullet = 15; // reload ammo which is 8
					this->pressingR = false; // reset button
					this->reloading = false;
				}

				//Player switching weapon when reloading
				if (Application::IsKeyPressed('1') && this->reloading == true ||
					Application::IsKeyPressed('3') && this->reloading == true||
					Application::IsKeyPressed('4') && this->reloading == true)
				{
					this->reloading = false;
				}
			}
		}
	}

	if (this->pressingMouse == true && shoot_Pistol >= 0.5f)
	{
		if (this->PistolBullet > 0)
		{
			this->PistolBullet -= 1;
			this->pistolFired = true;
			CreateBullet_Pistol = true;
		}
		else
		{
			CreateBullet_Pistol = false;
		}
		shoot_Pistol -= 0.5f;
	}
	else
	{
		CreateBullet_Pistol = false;
	}

	if (this->reloading == false)
	{
		this->reloadTime_Pistol = 3.0f;// reset reload time
	}
}
void CAmmo::ShootFunction_Sniper()
{
	//=============SNIPER=============//
	if (this->returnSniperConfirmation() == true)
	{
		if (this->SniperBullet >= 0 && this->SniperRound > 0)
		{
			if (this->pressingR == true)
			{
				this->reloadTime_Sniper -= dt;
				this->reloading = true;

				if (this->reloadTime_Sniper <= 0.0f)
				{
					this->SniperRound -= 1; //minus 1 round
					this->SniperBullet = 8; // reload ammo which is 8
					this->pressingR = false; // reset button
					this->reloading = false;
				}

				//Player switching weapon when reloading
				if (Application::IsKeyPressed('1') && this->reloading == true ||
					Application::IsKeyPressed('2') && this->reloading == true||
					Application::IsKeyPressed('4') && this->reloading == true)
				{
					this->reloading = false;
				}
			}
		}
	}

	if (this->pressingMouse == true && shoot_Sniper >= 1.2f)
	{
		if (this->SniperBullet > 0)
		{
			this->SniperBullet -= 1;
			this->SniperFired = true;
			CreateBullet_Sniper = true;
		}
		else
		{
			CreateBullet_Sniper = false;
		}
		shoot_Sniper -= 1.2f;
	}
	else
	{
		CreateBullet_Sniper = false;
	}

	if (this->reloading == false)
	{
		this->reloadTime_Sniper = 5.f;// reset reload time
	}
}
void CAmmo::ShootFunction_SMG()
{
	//=============SMG=============//
	if (this->returnSMGConfirmation() == true)
	{

		if (this->SMGBullet >= 0)
		{
			if (this->SMGRound > 0)
			{
				if (this->pressingR == true)
				{
					this->reloadTime_SMG -= dt;
					this->reloading = true;

					if (this->reloadTime_SMG <= 0.0f)
					{
						this->SMGRound -= 1; //minus 1 round
						this->SMGBullet = 30; // reload ammo which is 30
						this->pressingR = false; // reset button
						this->reloading = false;
					}

					//Player switching weapon when reloading
					if (Application::IsKeyPressed('1') && this->reloading == true ||
						Application::IsKeyPressed('2') && this->reloading == true ||
						Application::IsKeyPressed('3') && this->reloading == true)
					{
						this->reloading = false;
					}
				}
			}
		}
		if (this->pressingMouse == true && shoot_SMG >= 0.2f)
		{
			if (this->SMGBullet > 0)
			{
				this->SMGBullet -= 1;
				CreateBullet_SMG = true;
			}
			else
				CreateBullet_SMG = false;
			shoot_SMG -= 0.2f;
		}
		else
			CreateBullet_SMG = false;

		if (this->reloading == false)
		{
			this->reloadTime_SMG = 5.0f;// reset reload time
		}
	}
}
void CAmmo::BulletAndRoundLimit()
{
	//=======Setting Limit for ammos and rounds=======//
	if (this->PistolBullet < 0)
		this->PistolBullet = 0;
	if (this->PistolRound < 0)
		this->PistolRound = 0;

	if (this->SniperBullet < 0)
		this->SniperBullet = 0;
	if (this->SniperRound < 0)
		this->SniperRound = 0;

	if (this->SMGBullet < 0)
		this->SMGBullet = 0;
	if (this->SMGRound < 0)
		this->SMGRound = 0;
}
void CAmmo::DeleteBullet_Pistol()
{
	this->pistolFired = false;
}
bool CAmmo::returnCreateBullet_Pistol()
{
	return this->CreateBullet_Pistol;
}
bool CAmmo::returnCreateBullet_Sniper()
{
	return this->CreateBullet_Sniper;
}
bool CAmmo::returnCreateBullet_SMG()
{
	return this->CreateBullet_SMG;
}

void CAmmo::update(float dt)
{
	this->dt = dt;
	ButtonInput();

	ShootingTimeGap();

	ShootFunction_Pistol();

	ShootFunction_Sniper();

	ShootFunction_SMG();
	
	BulletAndRoundLimit();
}
void CAmmo::ChooseWeaponUpdate()
{
	//===================CHOOSING WEAPON==================//
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
}