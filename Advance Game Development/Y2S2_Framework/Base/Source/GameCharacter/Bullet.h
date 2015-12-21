#pragma once

#include "GameObject.h"

class CBullet : public CGameObject
{
public:
	CBullet();
	~CBullet();

	void Update(const double& dt,const float &WORLDSIZE);

	//Setter
	void setTimeLimit(double timeLimit);
	void setDisplayBullet(bool displayBullet);

	//Getter
	bool getDisplayBullet();

	float damage;
	Vector3 startPos;
private:
	static const float bulletSpeed;
	static const double displaybulletLimit;
	double timeLimit;
	bool displayBullet;
	double displayBulletTimeLimit;
};

