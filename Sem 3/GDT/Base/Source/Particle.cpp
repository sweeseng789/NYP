#include "Particle.h"
#include "Application.h"
#include <iostream>



Particle::Particle()
{
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
}


Particle::~Particle()
{
}

void Particle::update(double dt)
{
	pos += (vel * (1/mass) * dt);
	scale -= dt * 10;


	if (scale < 0)
		scale = defaultScale;

	if (pos.y < 0 || pos.y > 1000)
		pos.y = defaultPos.y;
	if (pos.z < -1000 || pos.z > 1000)
		pos.z = defaultPos.z;
	if (pos.x < -1000 || pos.x > 1000)
		pos.x = defaultPos.x;
}
