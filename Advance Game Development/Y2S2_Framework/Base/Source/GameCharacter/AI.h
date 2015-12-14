#pragma once
#include "GameObject.h"

class AI : public CGameObject
{
public:
	AI();
	AI(Vector3 pos);
	~AI();

	void Update(double dt, Vector3 playerPos, const float& terrainY);
};

