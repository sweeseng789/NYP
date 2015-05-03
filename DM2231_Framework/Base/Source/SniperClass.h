#pragma once
#include "Ammo.h"
#include "Vector3.h"

class SniperClass : public CAmmo
{
public:
	SniperClass(void);
	SniperClass(Vector3 bulletPosition, Vector3 bulletDirection, Vector3 bulletSpeed);
	~SniperClass(void);

	unsigned GetDamage();

	//Vector3
	Vector3 bulletPosition;
	Vector3 bulletDirection;
	Vector3 bulletSpeed;

	void bulletUpdate(float dt);
	unsigned returnHeadDamage();
	unsigned returnTorsoDamage();
	unsigned returnArmDamage();
private:
	unsigned HeadDamage;
	unsigned TorsoDamage;
	unsigned ArmDamage;
};

