#pragma once
#include "MyMath.h"
#include <iostream>

class CharAnimation
{
public:
	CharAnimation();
	~CharAnimation();

	bool invertWalkingDirection;

	float vel_LeftArm;

	float vel_RightArm;

	float vel_LeftLeg;

	float vel_RightLeg;

	void Update(const double &dt, float vel);
};

