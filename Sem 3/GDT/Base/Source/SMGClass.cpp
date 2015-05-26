#include "SMGClass.h"


SMGClass::SMGClass(void)
{
}

SMGClass::SMGClass(Vector3 bulletPosition, Vector3 bulletDirection, Vector3 bulletSpeed) :	HeadDamage(10),
																							TorsoDamage(5),
																							ArmDamage(2)
{
	this->bulletPosition = Vector3(bulletPosition.x, bulletPosition.y, bulletPosition.z);
	this->bulletDirection = Vector3(bulletDirection.x, bulletDirection.y, bulletDirection.z);
	this->bulletSpeed = bulletSpeed;
	//Normalize bullet direction
	this->bulletDirection.Normalize();
}


SMGClass::~SMGClass(void)
{
}

unsigned SMGClass::returnArmDamage()
{
	return this->ArmDamage;
}

unsigned SMGClass::returnHeadDamage()
{
	return this->HeadDamage;
}

unsigned SMGClass::returnTorsoDamage()
{
	return this->TorsoDamage;
}


void SMGClass::bulletUpdate(float dt)
{
	this->bulletPosition.x += (this->bulletDirection.x * this->bulletSpeed.x * dt);
	this->bulletPosition.y += (this->bulletDirection.y * this->bulletSpeed.y * dt);
	this->bulletPosition.z += (this->bulletDirection.z * this->bulletSpeed.z * dt);
}