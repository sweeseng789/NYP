#pragma once

#include "Vector3.h"
class CBullet
{
public:
	CBullet();
	CBullet(Vector3 pos, bool inverted);
	~CBullet();

	void update(double dt);

	bool getActive();
	Vector3 getPos();

private:
	Vector3 pos;
	bool inverted;
	bool active;
	double time;
};

