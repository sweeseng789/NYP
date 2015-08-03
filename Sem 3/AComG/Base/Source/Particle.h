#pragma once
#include <vector>
#include "Vector3.h"
#include "Material.h"
#include "LoadHmap.h"

using std::vector;
class Particle
{
public:
	enum PARTICLE_TYPE
	{
		GO_NONE = 0,
		GO_BALL,
		GO_RAIN,
		GO_STATICOBJ,
		GO_STATICOBJ2,
		GO_STATICOBJ3,
		GO_ROCK,
		GO_MOON,
		GO_TOTAL, //must be last
	};

	Particle();
	~Particle();

	//Create Particle
	void CreateRain();
	void CreateRain2(Vector3 cameraPos, Vector3 CameraTarget);
	void CreateBall();
	void CreateStaticOBJ(Vector3 pos);
	void update(double dt, Vector3 CameraPos, Vector3 CameraTarget);
	void setTerrainYPos(float tempY);

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
	float tempY;

	float rotateX;
	float rotateY;
	float rotateZ;
private:
};

