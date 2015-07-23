#include "NPC.h"
#include "Application.h"



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
	vel.z = Math::RandFloatMinMax(10, 20);
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

		//pos.x += cos(Math::DegreeToRadian(angle)) * vel.x * (float)dt;

		//if (angle == 0 || angle == 360)
		{
			pos.x += cos(Math::DegreeToRadian(angle)) * vel.x * (float)dt;
			pos.z += sin(Math::DegreeToRadian(angle)) * vel.z * (float)dt;
		}
		/*else if (angle == 90)
		{
			pos.z += sin(Math::DegreeToRadian(angle)) * vel.z * (float)dt;
		}
		else if (angle == 180)
		{
			pos.x += cos(Math::DegreeToRadian(angle)) * vel.x * (float)dt;
		}
		else if (angle == 270)
		{
			pos.z -= sin(Math::DegreeToRadian(angle)) * vel.x * (float)dt;
		}
		else if (angle > 0 && angle < 90)
		{
			pos.x += cos(Math::DegreeToRadian(angle)) * vel.x * (float)dt;
			pos.z += sin(Math::DegreeToRadian(angle)) * vel.z * (float)dt;
		}
		else if (angle > 90 && angle < 180)
		{
			pos.x -= cos(Math::DegreeToRadian(angle)) * vel.x * (float)dt;
			pos.z += sin(Math::DegreeToRadian(angle)) * vel.z * (float)dt;
		}
		else if (angle > 180 && angle < 270)
		{
			pos.x -= cos(Math::DegreeToRadian(angle)) * vel.x * (float)dt;
			pos.z -= sin(Math::DegreeToRadian(angle)) * vel.z * (float)dt;
		}
		else if (angle > 270 && angle < 360)
		{
			pos.x += cos(Math::DegreeToRadian(angle)) * vel.x * (float)dt;
			pos.z -= sin(Math::DegreeToRadian(angle)) * vel.z * (float)dt;
		}*/


		if (pos.x > 1000 || pos.x < -1000 || pos.z > 1000 || pos.z < -1000)
		{
			std::cout << "Dead" << std::endl;
			active = false;
		}

		if (angle > 360)
		{
			angle = 0;
		}
		else if (angle < 0)
		{
			angle = 360;
		}
	}
}