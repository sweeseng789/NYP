#pragma once
#include "Vector3.h"
#include "Material.h"
#include "LoadHmap.h"

class Particle
{
public:
	enum PARTICLE_TYPE
	{
		GO_NONE = 0,
		GO_BALL,
		GO_RAIN,
		GO_STATICOBJ,
		GO_TOTAL, //must be last
	};

	Particle();
	Particle(Vector3 pos, Vector3 vel, float scale, bool active, Material material, float mass);
	~Particle();

	//Create Particle
	void CreateRain();
	void CreateBall();
	void CreateStaticOBJ(Vector3 pos);

	void update(double dt, Vector3 CameraPos);

	Vector3 pos;
	Vector3 defaultPos;
	Vector3 vel;
	Vector3 view;
	float scale;
	float mass;
	float defaultScale;
	bool active;
	Material material;
	int ParticleType;
	float angle;
};

