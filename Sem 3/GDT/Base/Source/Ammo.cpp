#include "Ammo.h"


CAmmo::CAmmo(void):
//Int
ammos				(0),
bullet				(0),
rounds				(0),

//Float
elapsedTime1		(0.f),
shootTimeGap		(0.f),
shootTimeLimit		(0.f),
defaultReloadTime	(0.f),
reloadTime			(0.f),

//Bool
readyToShoot		(false),
pressingMouse		(false),
pressingR			(false),
reloading			(false),
active				(false),
createBullet		(false),

//Vector3
bulletDirection		( Vector3(0.0f, 0.0f, 0.0f)),
bulletPosition		( Vector3(0.0f, 0.0f, 0.0f)),
bulletSpeed			( Vector3(5.f, 5.f, 5.f))
{
	elapsedTime = 0;
	elapsedTime2 = 0;
}

CAmmo::~CAmmo(void)
{

}

void CAmmo::setBulletAndRounds(const unsigned bullet, const unsigned rounds, const float shootTimeLimit, const float reloadTime)
{
	this->bullet = defaultBullet = bullet;
	this->rounds = defaultRounds = rounds;
	this->shootTimeLimit = shootTimeLimit;
	this->reloadTime = defaultReloadTime = reloadTime;
}

void CAmmo::setDirection(const Vector3 bulletPosition, const Vector3 bulletDirection, const Vector3 bulletSpeed, const unsigned damage, bool active, const float lifeTime, WEAPON dataType)
{
	this->dataType = dataType;
	this->lifeTime = lifeTime;
	this->damage = damage;
	this->active = active;
	this->bulletPosition = Vector3(bulletPosition.x, bulletPosition.y, bulletPosition.z);
	this->bulletDirection = Vector3(bulletDirection.x, bulletDirection.y, bulletDirection.z);
	this->bulletSpeed = bulletSpeed;
	//Normalize bullet direction
	this->bulletDirection.Normalize();
}

void CAmmo::bulletUpdate(float td)
{
	cout << "hi" << endl;
}

unsigned CAmmo::getBullet()
{
	return bullet;
}

unsigned CAmmo::getRounds()
{
	return rounds;
}

float CAmmo::getReloadTime()
{
	return reloadTime;
}

bool CAmmo::getReadyToShoot()
{
	return readyToShoot;
}

bool CAmmo::getReloading()
{
	return reloading;
}

bool CAmmo::getCreateBullet()
{
	return createBullet;
}

void CAmmo::reload(float dt)
{

	elapsedTime += dt;
	elapsedTime2 += dt;

	if(elapsedTime > 0.5)
	{
		this->bullet += 1;
		elapsedTime = 0;
	}

	if(elapsedTime2 > 1.5)
	{
		this->rounds += 1;
		elapsedTime2 = 0;
	}

	if(bullet >= defaultBullet)
	{
		bullet = defaultBullet;
	}

	if(rounds >= defaultRounds)
	{
		rounds = defaultRounds;
	}
}

void CAmmo::update(float dt, CWeapon weapon, bool restocking)
{
	//=============Pressing Left Mouse=============//
	if (GetKeyState(VK_LBUTTON) < 0 && this->reloading == false && restocking == false)
		this->pressingMouse = true;
	else
		this->pressingMouse = false;

	//=============Pressing R=============//
	if (Application::IsKeyPressed('R'))
		this->pressingR = true;


	//=========Bullet Timegap=========//
	elapsedTime1 = (float)fmod(dt, 1);

	if (shootTimeGap < shootTimeLimit)
	{
		shootTimeGap += elapsedTime1;
		readyToShoot = false;
	}
	else
	{
		shootTimeGap = shootTimeLimit;
		readyToShoot = true;
	}

	//=========Shooting Bullet=========//
	if (this->pressingMouse == true && shootTimeGap >= shootTimeLimit)
	{
		if (bullet > 0)
		{
			bullet -= 1;
			
			createBullet = true;
		}
		else
		{
			createBullet = false;
		}
		
		shootTimeGap = 0;
	}
	else
	{
		createBullet = false;
	}

	//=========Reloading=========//
	if (this->reloading == false)
	{
		reloadTime = defaultReloadTime;// reset reload time
	}

	if (bullet >= 0 && rounds > 0)
	{
		if (pressingR == true)
		{
			reloadTime -= dt;
			reloading = true;

			if (reloadTime <= 0.0f)
			{
				rounds -= 1; //minus 1 round
				bullet = defaultBullet; // reload ammo which is 30
				pressingR = false; // reset button
				reloading = false;
				reloadTime = defaultReloadTime;
			}

			//Player switching weapon when reloading
			if (reloading == true)
			{
				if (weapon.returnPistolConfirmation() == true)
				{
					if (Application::IsKeyPressed('1') || Application::IsKeyPressed('3') || Application::IsKeyPressed('4'))
					{
						reloading = false;
					}
				}
				else if (weapon.returnSniperConfirmation() == true)
				{
					if (Application::IsKeyPressed('1') || Application::IsKeyPressed('2') || Application::IsKeyPressed('4'))
					{
						reloading = false;
					}
				}
				else if (weapon.returnSMGConfirmation() == true)
				{
					if (Application::IsKeyPressed('1') || Application::IsKeyPressed('2') || Application::IsKeyPressed('3'))
					{
						reloading = false;
					}
				}
			}
		}
	}

	//=======Setting Limit for ammos and rounds=======//
	if (bullet < 0)
		bullet = 0;
	if (rounds < 0)
		rounds = 0;
}