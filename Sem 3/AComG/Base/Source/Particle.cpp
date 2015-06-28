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

Particle::Particle(Vector3 pos, Vector3 vel, float scale, bool active, Material material, float mass)
{
	this->pos = pos;
	this->defaultPos = pos;
	this->vel = vel;
	this->scale = scale;
	this->defaultScale = scale;
	this->active = active;
	this->material = material;
	this->mass = mass;
	ParticleType = PARTICLE_TYPE::GO_BALL;
}


Particle::~Particle()
{
}

void Particle::CreateRain()
{
	view.Set(0, 0, 1);
	pos.x = Math::RandFloatMinMax(-1000, 1000);
	pos.y = 500;
	pos.z = Math::RandFloatMinMax(-1000, 1000);
	defaultPos = pos;
	vel.y = Math::RandFloatMinMax(-50, -150);
	defaultScale = scale = 3;
	mass = scale * scale  * scale;
	ParticleType = PARTICLE_TYPE::GO_RAIN;
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
	ParticleType = PARTICLE_TYPE::GO_BALL;
}

void Particle::CreateStaticOBJ(Vector3 pos)
{
	active = true;
	this->pos = pos;
	vel.SetZero();
	scale = 10;
	ParticleType = PARTICLE_TYPE::GO_STATICOBJ;
}

void Particle::update(double dt, Vector3 CameraPos)
{
	pos += vel * (100 / mass) * dt;

	if (ParticleType == PARTICLE_TYPE::GO_BALL)
	{
		scale -= dt * 10;

		if (scale < 0)
			scale = defaultScale;

		if (pos.y < 0 || pos.y > 1000 || pos.z < -1000 || pos.z > 1000 || pos.x < -1000 || pos.x > 1000)
			CreateBall();
	}
	else if (ParticleType == PARTICLE_TYPE::GO_RAIN)
	{
		if (pos.y < 0)
		{
			CreateRain();
		}

		Vector3 diff;
		diff.x = CameraPos.x - pos.x;
		diff.z = CameraPos.z - pos.z;

		angle = Math::RadianToDegree(acos(view.Dot(diff) / (view.Length() * diff.Length())));
		if (view.Cross(diff).y > 1)
			angle *= 1;
		else
			angle *= -1;
	}
}
