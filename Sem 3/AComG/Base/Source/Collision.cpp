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