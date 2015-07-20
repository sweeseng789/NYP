#include "Particle.h"
#include "Application.h"
#include <iostream>



Particle::Particle(): active(true)
{
	material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	material.kShininess = 10.f;
}


Particle::~Particle()
{
}


void Particle::CreateRain()
{
	//view.Set(0, 0, 1);
	pos.x = Math::RandFloatMinMax(-1000, 1000);
	pos.y = 500;
	pos.z = Math::RandFloatMinMax(-1000, 1000);
	defaultPos = pos;
	vel.x = Math::RandFloatMinMax(-10, 10);
	vel.z = Math::RandFloatMinMax(-10, 10);
	vel.y = Math::RandFloatMinMax(-50, -150);
	defaultScale = scale = 3;
	mass = scale * scale  * scale;
	ParticleType = GO_RAIN;
}

void Particle::CreateRain2(Vector3 cameraPos, Vector3 cameraTarget)
{
	/*pos.x = Math::RandFloatMinMax(cameraPos.x - 400, cameraPos.x + 400);
	pos.y = 500;
	pos.z = Math::RandFloatMinMax(cameraPos.z - 400, cameraPos.z + 400);*/

	//This would give give the rain particle the position that is always infront of the camera
	float directionOffSet = 8;
	pos.x = cameraPos.x + Math::RandFloatMinMax(cameraTarget.x - directionOffSet, cameraTarget.x + directionOffSet) * Math::RandFloatMinMax(50, 100);
	pos.y = 500;
	pos.z = cameraPos.z + Math::RandFloatMinMax(cameraTarget.z - directionOffSet, cameraTarget.z + directionOffSet) * Math::RandFloatMinMax(50, 100);
	defaultPos = pos;
	vel.x = Math::RandFloatMinMax(-10, 10);
	vel.z = Math::RandFloatMinMax(-10, 10);
	vel.y = Math::RandFloatMinMax(-70, -170);
	defaultScale = scale = 3;
	mass = scale * scale  * scale;
	ParticleType = GO_RAIN;
}


void Particle::CreateBall()
{
	pos.x = Math::RandFloatMinMax(-1000, 1000);
	pos.y = Math::RandFloatMinMax(0, 1000);
	pos.z = Math::RandFloatMinMax(-1000, 1000);
	defaultPos = pos;
	vel.x = Math::RandFloatMinMax(-10, 10);
	vel.y = Math::RandFloatMinMax(-10, 10);
	vel.z = Math::RandFloatMinMax(-10, 10);
	defaultScale = scale = Math::RandFloatMinMax(0, 10);
	mass = scale * scale * scale;
	ParticleType = GO_BALL;
}

void Particle::CreateStaticOBJ(Vector3 pos)
{
	active = true;
	this->pos = pos;
	vel.SetZero();
}

void Particle::update(double dt, Vector3 CameraPos, Vector3 CameraTarget)
{
	pos += vel * (100 / mass) * (float)dt;

	/*if (ParticleType == GO_BALL)
	{
		scale -= (float)dt * 10;

		if (scale < 0)
			scale = defaultScale;

		if (pos.y < 0 || pos.y > 1000 || pos.z < -1000 || pos.z > 1000 || pos.x < -1000 || pos.x > 1000)
			CreateBall();
	}*/
	if (ParticleType == GO_RAIN)
	{
		if (pos.y < 0)
		{
			CreateRain2(CameraPos, CameraTarget);
		}

		//atan2(difference about x axis, difference about z axis) == angle
		Vector3 diff;
		diff.x = CameraPos.x - pos.x;
		diff.z = CameraPos.z - pos.z;
		angle = Math::RadianToDegree(atan2(diff.x, diff.z));
	}
}
