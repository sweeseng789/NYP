#pragma once
#include "Vector3.h"

class Particle
{
public:
	Particle();
	~Particle();

	void restartParticles(Vector3 pos, Vector3 vel, double timeLimit);
	void update(const double &dt);

	bool getActive();
	Vector3 getPos();
	Vector3 getVel();
	float getScale();

private:
	bool active;
	double timeLimit;
	Vector3 pos;
	Vector3 vel;
	float scale;
	float mass;
};

