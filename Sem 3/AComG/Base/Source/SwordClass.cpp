#include "SwordClass.h"


SwordClass::SwordClass(void)
{
	this->bullet = this->damage = this->rounds = 0;
}


SwordClass::~SwordClass(void)
{
}

void SwordClass::setParametersForPistol(int newRounds, int newBullets, int newDamage)
{
	this->rounds = newRounds;
	this->damage = newDamage;
	this->bullet = newBullets;
}