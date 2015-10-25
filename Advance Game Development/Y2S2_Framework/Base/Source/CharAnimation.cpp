#include "CharAnimation.h"



CharAnimation::CharAnimation() :
	vel_LeftArm(0.f),
	vel_LeftLeg(0.f),
	vel_RightArm(0.f),
	vel_RightLeg(0.f)
{
	invertWalkingDirection = false;
}


CharAnimation::~CharAnimation()
{
}

void CharAnimation::Update(const double &dt, float vel)
{
	if (invertWalkingDirection == false)
	{
		if (vel > 0)
		{
			vel_LeftLeg += dt * vel;
		}
		else
		{
			vel_LeftLeg -= dt * vel;
		}

		if (vel_LeftLeg > 30)
			invertWalkingDirection = true;
	}
	else
	{
		if (vel > 0)
		{
			vel_LeftLeg -= dt * vel;
		}
		else
		{
			vel_LeftLeg += dt * vel;
		}

		if (vel_LeftLeg < -30)
			invertWalkingDirection = false;
	}

	//Friction
	if (vel < 0.5 && vel > -0.5)
	{
			vel_LeftLeg += (0 - vel_LeftLeg) * dt * 5.f;
	}

	vel_RightLeg = -vel_LeftLeg;

	vel_LeftArm = vel_RightLeg;
	vel_RightArm = vel_LeftLeg;
}