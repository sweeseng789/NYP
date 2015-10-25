#include "Particle.h"



Particle::Particle()
{
	active = true;
	pos.SetZero();
	vel.SetZero();
	scale = 0;
	mass = 0;
}


Particle::~Particle()
{
}

void Particle::restartParticles(Vector3 pos, Vector3 vel, double timeLimit)
{
	active = true;
	this->pos = pos;
	this->vel = vel;
	this->timeLimit = timeLimit;

	scale = Math::RandFloatMinMax(0.1, 0.2);
	mass = scale * scale * scale;
}

bool Particle::getActive()
{
	return active;
}

Vector3 Particle::getPos()
{
	return pos;
}

Vector3 Particle::getVel()
{
	return vel;
}

float Particle::getScale()
{
	return scale;
}

void Particle::update(const double & dt)
{
	if (active)
	{
		timeLimit -= dt;

		pos += vel * (0.15 / mass) * dt;

		if (timeLimit <= 0.0)
		{
			active = false;
		}
	}
}
