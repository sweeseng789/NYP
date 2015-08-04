#include "Collision.h"


Collision::Collision()
{
}

Collision::~Collision()
{
}

bool Collision::PointDistance(Vector3 pos1, Vector3 pos2, float range)
{
	if ((pos1 - pos2).Length() < range)
		return true;
	else
		return false;
}

bool Collision::PointDistanceSqrt(Vector3 pos1, Vector3 pos2, float range)
{
	if ((pos1 - pos2).LengthSquared() < range)
		return true;
	else
		return false;
}

bool Collision::SphereToSphere(Vector3 pos1, Vector3 pos2, float scale1, float scale2)
{
	float dist = Vector3((pos1 - pos2)).LengthSquared();
	if (dist <= (scale1 + scale2) * (scale1 + scale2))
		return true;
	else
		return false;
}

bool Collision::AABB(Vector3 pos1, Vector3 pos2, float offSet_x, float offSet_y)
{
	/*if (pos1.x > pos2.x - offSet_x && pos1.x < pos2.x + offSet_x)
	{
		if (pos1.y > pos2.y - offSet_y && pos1.y < pos2.y + offSet_y)
			return false;
		else
			return true;
	}*/

	if (pos1.x > pos2.x - offSet_x && pos1.x < pos2.x + offSet_x)
	{
		if (pos1.y > pos2.y - offSet_y && pos1.y < pos2.y + offSet_y)
			return true;
		else
			return false;
	}

}