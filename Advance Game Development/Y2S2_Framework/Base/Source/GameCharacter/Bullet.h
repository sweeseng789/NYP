#pragma once

#include "GameObject.h"

class CBullet : public CGameObject
{
public:
	CBullet();
	~CBullet();

	void Update(const double& dt);

	//Setter
	void setTimeLimit(double timeLimit);
	void setDisplayBullet(bool displayBullet);

	//Getter
	bool getDisplayBullet();
private:
	static const float bulletSpeed;
	static const double displaybulletLimit;
	double timeLimit;
	bool displayBullet;
	double displayBulletTimeLimit;
};

