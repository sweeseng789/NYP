#pragma once
#include "Vector3.h"
#include "Material.h"

class Particle
{
	enum PARTICLE_TYPE
	{
		GO_NONE = 0,
		GO_BALL,
		GO_CUBE,
		GO_TOTAL, //must be last
	};
	PARTICLE_TYPE type;

public:
	Particle();
	Particle(Vector3 pos, Vector3 vel, float scale, bool active, Material material, float mass);
	~Particle();

	void update(double dt);

	Vector3 pos;
	Vector3 defaultPos;
	Vector3 vel;
	float scale;
	float mass;
	float defaultScale;
	bool active;
	Material material;
};

