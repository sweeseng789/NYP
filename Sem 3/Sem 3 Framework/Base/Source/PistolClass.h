#ifndef PISTOL_CLASS_H
#define PISTOL_CLASS_H

#include <iostream>
#include "Vector3.h"
#include "Ammo.h"

using std::cin;
using std::cout;
using std::endl;

class PistolClass : public CAmmo
{
public:
	PistolClass(void);
	PistolClass(Vector3 bulletPosition, Vector3 bulletDirection, Vector3 bulletSpeed);
	~PistolClass(void);

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


#endif
