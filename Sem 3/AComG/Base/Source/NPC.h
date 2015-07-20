#pragma once
#include "Vector3.h"
#include "MyMath.h"

class CNPC
{
public:
	CNPC();
	~CNPC();

	bool getActive();
	Vector3 getPos();
	float getAngle();

	void update(double dt, float pos_y);
	void setPos(Vector3 pos);
	void reactivate(Vector3 pos);
private:
	bool active;
	Vector3 pos;
	Vector3 vel;
	float angle;
};

