#include "Particle.h"

Particle::Particle()
{
	active = false;
	pos.SetZero();
	vel.SetZero();
	scale.Set(0.5, 0.5, 0.5);
	mass = 0;
	color = e_YELLOW;

	meshList[e_YELLOW] = MeshBuilder::GenerateSphere("Particle", Color(1, 1, 0), 18, 36);
	meshList[e_BLUE] = MeshBuilder::GenerateSphere("Particle", Color(0.43921568627, 0.74117647058, 0.81960784313), 18, 36, 2);
}


Particle::~Particle()
{
}

void Particle::restartParticles(Vector3 pos, Vector3 vel, double timeLimit, COLORS color)
{
	active = true;
	this->pos = pos;
	this->vel = vel;
	this->timeLimit = timeLimit;
	this->color = color;
}

Mesh* Particle::getParticle()
{
	return meshList[color];
}

void Particle::update(const double & dt)
{
	timeLimit -= dt;

	vel += Vector3(0, -9.82 * 25, 0) * dt;
	pos += vel * dt;

	if (timeLimit <= 0.0)
	{
		active = false;
	}
}

void Particle::setTimeLimit(double timeLimit)
{
	this->timeLimit = timeLimit;
}
