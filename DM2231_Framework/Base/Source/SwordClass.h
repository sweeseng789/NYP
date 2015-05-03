#pragma once
class SwordClass
{
public:
	SwordClass(void);
	~SwordClass(void);
	void setParametersForPistol(int newRounds, int newBullets, int newDamage);
private:
	int rounds, bullet, damage;
};

