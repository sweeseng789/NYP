#include "Bullet.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;


CBullet::CBullet()
{
}

CBullet::CBullet(Vector3 pos, bool inverted) : active(true), time(3.f)
{
	this->pos = pos;
	this->inverted = inverted;
}


CBullet::~CBullet()
{
}

void CBullet::update(double dt)
{
	time -= dt;

	if (inverted)
		pos -= 600 * dt;
	else
		pos += 600 * dt;

	if (time <= 0)
	{
		active = false;
		cout << "h" << endl;
	}
}

Vector3 CBullet::getPos()
{
	return pos;
}

bool CBullet::getActive()
{
	return active;
}
