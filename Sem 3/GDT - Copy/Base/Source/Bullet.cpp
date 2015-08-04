#include "Bullet.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;


CBullet::CBullet() : active(true), time(3.f), scale(1)
{
}

void CBullet::setActive()
{
	active = true;
	time = 3.f;
	scale = 1;
}


CBullet::~CBullet()
{
}

void CBullet::update(double dt)
{
	time -= dt;

	if (inverted)
		pos -= 100 * dt;
	else
		pos += 100 * dt;

	if (time <= 0)
	{
		//active = false;
	}
}

void CBullet::setData(Vector3 pos, bool inverted)
{
	this->pos = pos;
	this->inverted = inverted;
}

Vector3 CBullet::getPos()
{
	return pos;
}

bool CBullet::getActive()
{
	return active;
}

float CBullet::getScale()
{
	return scale;
}
