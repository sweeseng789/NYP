#include "SniperClass.h"


SniperClass::SniperClass(void)
{
}

SniperClass::SniperClass(Vector3 bulletPosition, Vector3 bulletDirection, Vector3 bulletSpeed) :	HeadDamage	(100),
																									TorsoDamage (10),
																									ArmDamage	(2)
{
	this->bulletPosition = Vector3(bulletPosition.x, bulletPosition.y, bulletPosition.z);
	this->bulletDirection = Vector3(bulletDirection.x, bulletDirection.y, bulletDirection.z);
	this->bulletSpeed = bulletSpeed;
	//Normalize bullet direction
	this->bulletDirection.Normalize();
}


SniperClass::~SniperClass(void)
{
}

unsigned SniperClass::returnHeadDamage()
{
	return this->HeadDamage;
}
unsigned SniperClass::returnArmDamage()
{
	return this->ArmDamage;
}
unsigned SniperClass::returnTorsoDamage()
{
	return this->TorsoDamage;
}
void SniperClass::bulletUpdate(float dt)
{
	this->bulletPosition.x += (this->bulletDirection.x * this->bulletSpeed.x * dt);
	this->bulletPosition.y += (this->bulletDirection.y * this->bulletSpeed.y * dt);
	this->bulletPosition.z += (this->bulletDirection.z * this->bulletSpeed.z * dt);
}