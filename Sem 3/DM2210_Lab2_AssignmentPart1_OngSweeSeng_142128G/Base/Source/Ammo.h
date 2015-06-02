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

using std::cin;
using std::cout;
using std::endl;
using std::vector;

class CAmmo
{
public:
	CAmmo(void);
	virtual ~CAmmo(void);

	//======================GETTER=====================//
	//Int
	unsigned returnBullet_Pistol();
	unsigned returnBullet_Sniper();
	unsigned returnBullet_SMG();
	unsigned returnRounds_Pistol();
	unsigned returnRounds_Sniper();
	unsigned returnRounds_SMG();
	unsigned int returnSwordNumber();
	unsigned int returnPistolNumber();
	unsigned int returnSniperNumber();
	unsigned int returnSMGNumber();

	//Bool
	bool returnReloading();
	bool returnReadyToShootPistol();
	bool returnReadyToShootSniper();
	bool returnReadyToShootSMG();
	bool returnPressingMouse();
	bool returnSwordConfirmation();
	bool returnPistolConfirmation();
	bool returnSniperConfirmation();
	bool returnSMGConfirmation();
	bool returnPistolFired();
	bool returnSniperFired();
	bool returnSMGFired();
	bool returnCreateBullet_Pistol();
	bool returnCreateBullet_Sniper();
	bool returnCreateBullet_SMG();

	//Float
	float returnReloadTime_Pistol();
	float returnReloadTime_Sniper();
	float returnReloadTime_SMG();
	float returnShootingGap_Pistol();

	//Vector3
	Vector3 returnBulletPosition();

	//===============SETTER==================//
	void setPistolFired(bool newValue);
	void SetBulletandRounds_Pistol(const unsigned newAmmos_Pistol, const unsigned newRounds_Pistol);
	void SetBulletandRounds_Sniper(const unsigned newAmmos_Sniper, const unsigned newRounds_Sniper);
	void SetBulletandRounds_SMG(const unsigned newAmmos_SMG, const unsigned newRounds_SMG);
	void ChooseWeaponUpdate();
	void DeleteBullet_Pistol();
	void ShootingTimeGap();
	void ButtonInput();
	void ShootFunction_Pistol();
	void ShootFunction_Sniper();
	void ShootFunction_SMG();
	void BulletAndRoundLimit();
	void SetterForPolymorphism();


	//Update
	virtual void bulletUpdate(float dt);
	void update(float dt);

	//Vector3
	Vector3 bulletPosition;
	Vector3 bulletDirection;
	Vector3 bulletSpeed;

private:
	//Int
	unsigned ammos;
	unsigned swordNumber; 
	unsigned pistolNumber; 
	unsigned sniperNumber; 
	unsigned SMGnumber; 
	unsigned bullet; 
	unsigned rounds;
	unsigned PistolBullet;
	unsigned PistolDamage;
	unsigned PistolRound;
	unsigned SniperBullet;
	unsigned SniperDamage;
	unsigned SniperRound;
	unsigned SMGBullet;
	unsigned SMGDamage;
	unsigned SMGRound;

	//Float
	float reloadTime_Pistol; 
	float reloadTime_Sniper;
	float reloadTime_SMG;
	float dt;
	float elapsedTime1;
	float shoot_Pistol;
	float shoot_Sniper;
	float shoot_SMG;

	//bool
	bool reloadedGun;
	bool reloading;
	bool pressingMouse, pressingR;
	bool readyToShoot_Pistol;
	bool readyToShoot_Sniper; 
	bool readyToShoot_SMG;
	bool pistolFired; 
	bool SniperFired; 
	bool SMGFired;
	bool usingSword;
	bool usingPistol;
	bool usingSniper; 
	bool usingSMG;
	bool testing;
	bool CreateBullet_Pistol;
	bool CreateBullet_Sniper;
	bool CreateBullet_SMG;

	//Timer
	StopWatch timer;

	//String
	std::string type;
};

#endif