#pragma once
#include "GameCharacter\GameObject.h"

class Particle : public CGameObject
{
public:
	enum COLORS
	{
		e_YELLOW,
		e_BLUE,
		TOTAL
	};

	Particle();
	~Particle();

	void restartParticles(Vector3 pos, Vector3 vel, double timeLimit, COLORS color);
	//Getter
	Mesh* getParticle();

	//Setter
	void update(const double &dt);
	void setTimeLimit(double timeLimit);

private:
	double timeLimit;
	float mass;
	COLORS color;
	Mesh* meshList[TOTAL];
};

