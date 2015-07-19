#pragma once

#include "Vector3.h"
class CBullet
{
public:
	CBullet();
	CBullet(Vector3 pos, bool inverted);
	~CBullet();

	void update(double dt);
	void setData(Vector3 pos, bool inverted);
	void setActive();

	bool getActive();
	Vector3 getPos();
	float getScale();

	bool active;
private:
	Vector3 pos;
	bool inverted;
	float scale;

	double time;
};

