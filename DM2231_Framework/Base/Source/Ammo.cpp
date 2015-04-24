#include "Ammo.h"


CAmmo::CAmmo(void)
{
	damage = ammos = rounds = NULL;
}


CAmmo::~CAmmo(void)
{
}

void CAmmo::setBulletandRounds(const int newAmmos, const int newRounds)
{
	ammos = newAmmos;
	rounds = newRounds;
}

unsigned int CAmmo::returnAmmos()
{
	return ammos;
}
unsigned int CAmmo::returnRounds()
{
	return rounds;
}

void CAmmo::update(float dt, bool usingSword, bool usingPistol, bool usingSniper, bool usingSMG)
{
	bool pressingMouse = false;
	bool pressingR = false;

	//=============Pressing Left Mouse=============//
	if (Application::IsKeyPressed(VK_LBUTTON))
		pressingMouse = true;
	else
		pressingMouse = false;
	
	//=============Pressing R=============//
	if (Application::IsKeyPressed('R'))
		pressingR = true;
	else
		pressingR = false;

	//=========Shooting Bullet=========//
	if (pressingMouse == true)
	{
		if (ammos > 0)
		{
			ammos -= 0.1 * dt;
		}
	}


	//=============PISTOL=============//
	if (usingSword == false && usingPistol == true && usingSniper == false && usingSMG == false)
	{
		if (ammos >= 0)
		{
			if (rounds > 0)
			{
				if (pressingR == true)
				{
					rounds -= 1;
					ammos = 15;
				}
			}
		}
	}
	//=============SNIPER=============//
	else if (usingSword == false && usingPistol == false && usingSniper == true && usingSMG == false)
	{
		if (ammos >= 0)
		{
			if (rounds > 0)
			{
				if (pressingR == true)
				{
					rounds -= 1;
					ammos = 8;
				}
			}
		}
	}
	//=============SMG=============//
	else if (usingSword == false && usingPistol == false && usingSniper == false && usingSMG == true)
	{
		
		if (ammos >= 0)
		{
			if (rounds > 0)
			{
				if (pressingR == true)
				{
					rounds -= 1;
					ammos = 30;
				}
			}
		}
	}

	//=======Setting Limit for ammos and rounds=======//
	if (ammos < 0)
		ammos = 0;
	if (rounds < 0)
		rounds = 0;
}
