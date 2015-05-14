#include "PistolClass.h"


PistolClass::PistolClass(void)
{
}

PistolClass::PistolClass(Vector3 bulletPosition, Vector3 bulletDirection, Vector3 bulletSpeed) :	HeadDamage	(12),
																									TorsoDamage (10),
																									ArmDamage	(5)
{
	this->bulletPosition = Vector3(bulletPosition.x, bulletPosition.y, bulletPosition.z);
	this->bulletDirection = Vector3(bulletDirection.x, bulletDirection.y, bulletDirection.z);
	this->bulletSpeed = bulletSpeed;
	//Normalize bullet direction
	this->bulletDirection.Normalize();
}


PistolClass::~PistolClass(void)
{
}

unsigned PistolClass::returnHeadDamage()
{
	return this->HeadDamage;
}
unsigned PistolClass::returnArmDamage()
{
	return this->ArmDamage;
}
unsigned PistolClass::returnTorsoDamage()
{
	return this->TorsoDamage;
}
void PistolClass::bulletUpdate(float dt)
{
	this->bulletPosition.x += (this->bulletDirection.x * this->bulletSpeed.x * dt);
	this->bulletPosition.y += (this->bulletDirection.y * this->bulletSpeed.y * dt);
	this->bulletPosition.z += (this->bulletDirection.z * this->bulletSpeed.z * dt);
}