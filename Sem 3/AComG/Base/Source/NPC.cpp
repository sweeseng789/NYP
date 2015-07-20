#include "NPC.h"



CNPC::CNPC(): active(true), pos(NULL), vel(NULL), angle(0)
{
}


CNPC::~CNPC()
{
}

void CNPC::reactivate(Vector3 pos)
{
	active = true;
	this->pos = pos;
	vel.x = Math::RandFloatMinMax(10, 20);
	angle = 0;
}

bool CNPC::getActive()
{
	return active;
}

Vector3 CNPC::getPos()
{
	return pos;
}

float CNPC::getAngle()
{
	return angle;
}

void CNPC::setPos(Vector3 pos)
{
	this->pos = pos;
}

void CNPC::update(double dt, float pos_y)
{
	if (active)
	{
		//pos.y = pos_y;
		float diff = pos_y - pos.y;
		pos.y += diff * 10 * dt;

		pos.x += cos(Math::DegreeToRadian(angle)) * vel.x * (float)dt;


		if (pos.x > 1000 || pos.x < -1000 || pos.z > 1000 || pos.z < -1000)
		{
			std::cout << "Dead" << std::endl;
			active = false;
		}
	}
}