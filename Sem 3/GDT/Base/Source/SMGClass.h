#ifndef SMG_CLASS_H
#define SMG_CLASS_H
#include "Ammo.h"
#include "Vector3.h"

class SMGClass : public CAmmo
{
public:
	SMGClass(void);
	SMGClass(Vector3 bulletPosition, Vector3 bulletDirection, Vector3 bulletSpeed);
	~SMGClass(void);

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

#endif