#include "OBJ.h"

COBJ::COBJ(Vector3 pos, float speed, int type)
{
	this->pos = pos;
	defaultY = pos.y;
	this->speed = speed;
	this->type = type;
	tempY = 0;
} 

COBJ::~COBJ()
{
}

Vector3 COBJ::getPos()
{
	return pos;
}

void COBJ::update(double dt)
{
	if(type == 1)
	{
		if(pos.y > tempY)
		{
			pos.y -= speed * dt;
		}
		else
		{
			pos.y = defaultY;
			pos.x = Math::RandFloatMinMax(-1000, 1000);
			pos.z = Math::RandFloatMinMax(-1000, 1000);
			speed = Math::RandFloatMinMax(50, 150);
		}
	}
}

void COBJ::update2(double dt, vector<unsigned char> m_heightMap)
{
	if (type == 1)
	{
		//float Y = 350.f * ReadHeightMap(m_heightMap, pos.x / 2000.f, pos.z / 2000.f);
		std::cout << "hi" << std::endl;
		if (pos.y > 0)
		{
			pos.y -= speed * dt;
		}
		else
		{
			pos.y = defaultY;
			pos.x = Math::RandFloatMinMax(-1000, 1000);
			pos.z = Math::RandFloatMinMax(-1000, 1000);
			speed = Math::RandFloatMinMax(50, 150);
		}
	}
}