#pragma once
#include "GameObject.h"

class Ship : public CGameObject
{
public:
	Ship(int type, float x, float y);
	~Ship();
};

