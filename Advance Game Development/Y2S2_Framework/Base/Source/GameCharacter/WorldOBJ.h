#pragma once
#include "GameObject.h"

class CWorldOBJ : public CGameObject
{
public:
	CWorldOBJ();
	CWorldOBJ(Vector3 pos, float scale);
	~CWorldOBJ();


	void update(const double& dt, float& tempY);

	float health;
	float newHealth;
};

