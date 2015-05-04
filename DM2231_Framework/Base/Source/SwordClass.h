#ifndef SWORD_CLASS_H
#define SWORD_CLASS_H
class SwordClass
{
public:
	SwordClass(void);
	~SwordClass(void);
	void setParametersForPistol(int newRounds, int newBullets, int newDamage);
private:
	int rounds, bullet, damage;
};

#endif