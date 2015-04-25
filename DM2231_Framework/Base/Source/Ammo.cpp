#include "Ammo.h"


CAmmo::CAmmo(void)
{
	this->damage = this->ammos = this->rounds = NULL;
	this->dt = 0.0f;

	this->reloadTime_Pistol = 3.0f;
	this->reloadTime_Sniper = 5.0f;
	this->reloadTime_SMG = 4.0f;

	this->reloadedGun = false;

	this->pressingMouse = false;
	this->pressingR = false;

	this->reloading = false;

	this->readyToShoot_Pistol = this->readyToShoot_Sniper = this->readyToShoot_SMG = false;
}


CAmmo::~CAmmo(void)
{
}
void CAmmo::setBulletandRounds(const int newAmmos, const int newRounds)
{
	this->ammos = newAmmos;
	this->rounds = newRounds;
}
unsigned int CAmmo::returnAmmos()
{
	return ammos;
}
unsigned int CAmmo::returnRounds()
{
	return rounds;
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

void CAmmo::update(float dt, bool usingSword, bool usingPistol, bool usingSniper, bool usingSMG)
{
	//=============Pressing Left Mouse=============//
	if (GetKeyState(VK_LBUTTON) < 0 && this->reloading == false)
		this->pressingMouse = true;
	else
		this->pressingMouse = false;

	//=============Pressing R=============//
	if (Application::IsKeyPressed('R'))
		this->pressingR = true;

	//=========Shooting Bullet=========//
	static float elapsedTime1 = 0.0f;
	static float shoot_Pistol = 0.0f;
	static float shoot_Sniper = 0.0f;
	static float shoot_SMG = 0.0f;

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

	//=============PISTOL=============//
	if (usingSword == false && usingPistol == true && usingSniper == false && usingSMG == false)
	{
		if (this->ammos >= 0)
		{
			if (this->rounds > 0)
			{
				if (this->pressingR == true)
				{
					this->reloadTime_Pistol -= dt;
					this->reloading = true;

					if (this->reloadTime_Pistol <= 0.0f)
					{
						this->rounds -= 1; //minus 1 round
						this->ammos = 15; // reload ammo which is 8
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

		if (this->pressingMouse == true && shoot_Pistol >= 0.5f)
		{
			if (this->ammos > 0)
			{
				this->ammos -= 1;
			}
			shoot_Pistol -= 0.5f;
		}

		if (this->reloading == false)
		{
			this->reloadTime_Pistol = 3.0f;// reset reload time
		}
	}
	//=============SNIPER=============//
	if (usingSword == false && usingPistol == false && usingSniper == true && usingSMG == false)
	{
		if (this->ammos >= 0)
		{
			if (this->rounds > 0)
			{
				if (this->pressingR == true)
				{
					this->reloadTime_Sniper -= dt;
					this->reloading = true;

					if (this->reloadTime_Sniper <= 0.0f)
					{
						this->rounds -= 1; //minus 1 round
						this->ammos = 8; // reload ammo which is 8
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
			if (this->ammos > 0)
			{
				this->ammos -= 1;
			}
			shoot_Sniper -= 1.2f;
		}

		if (this->reloading == false)
		{
			this->reloadTime_Sniper = 5.0f;// reset reload time
		}
	}
	//=============SMG=============//
	if (usingSword == false && usingPistol == false && usingSniper == false && usingSMG == true)
	{

		if (this->ammos >= 0)
		{
			if (this->rounds > 0)
			{
				if (this->pressingR == true)
				{
					this->reloadTime_SMG -= dt;
					this->reloading = true;

					if (this->reloadTime_SMG <= 0.0f)
					{
						this->rounds -= 1; //minus 1 round
						this->ammos = 30; // reload ammo which is 30
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
			if (this->ammos > 0)
			{
				this->ammos -= 1;
			}
			shoot_SMG -= 0.2f;
		}
		if (this->reloading == false)
		{
			this->reloadTime_SMG = 5.0f;// reset reload time
		}
	}

	//=======Setting Limit for ammos and rounds=======//
	if (this->ammos < 0)
		this->ammos = 0;
	if (this->rounds < 0)
		this->rounds = 0;

	cout << reloadTime_Pistol << endl;
}