#ifndef AMMO_H
#define AMMO_H

#include <iostream>
#include <vector>
#include <Windows.h>
#include <ctime>
#include <string.h>
#include "Application.h"
#include "timer.h"
#include "Vector3.h"
#include "Camera3.h"
#include "Enemy.h"
#include "Weapon.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

enum WEAPON
{
	BULLET_SWORD = 1,
	BULLET_PISTOL,
	BULLET_SNIPER,
	BULLET_SMG,
	BULLET_TOTAL
};

class CAmmo
{
public:
	CAmmo(void);
	CAmmo(const Vector3 bulletPosition, const Vector3 bulletDirection, const Vector3 bulletSpeed, WEAPON dataType);
	~CAmmo(void);

	//======================GETTER=====================//
	//Int
	unsigned getBullet();
	unsigned getRounds();

	//Bool
	bool getReadyToShoot();
	bool getReloading();
	bool getCreateBullet();

	//Float
	float getReloadTime();

	//===============SETTER==================//
	void setBulletAndRounds(const unsigned bullet, const unsigned rounds, const float shootTimeLimit, const float reloadTime);
	void setDirection(const Vector3 bulletPosition, const Vector3 bulletDirection, const Vector3 bulletSpeed, const unsigned damage, bool active, const float lifeTime, WEAPON dataType);

	//Update
	virtual void bulletUpdate(float dt);
	void update(float dt, CWeapon weapon);

	//Bullet Variables
	bool active;
	unsigned damage;
	float lifeTime;
	WEAPON dataType;
	Vector3 bulletPosition;
	Vector3 bulletDirection;
	Vector3 bulletSpeed;
private:
	//Int
	unsigned ammos;
	unsigned bullet;
	unsigned defaultBullet;
	unsigned rounds;
	unsigned defaultRounds;

	//Float
	float elapsedTime1;
	float defaultReloadTime;
	float reloadTime;
	float shootTimeGap;
	float shootTimeLimit;

	//bool

	bool pressingR;
	bool readyToShoot;

	
	
	
	bool pressingMouse;
	bool reloading;
	bool createBullet;
};

#endif