#include "SSDLC.h"



SSDLC::SSDLC()
{
}


SSDLC::~SSDLC()
{
}

float SSDLC::findAngleFromPos(Vector3 target, Vector3 pos, bool XZ)
{
	if (XZ)
	{
		return Math::RadianToDegree(atan2(target.x - pos.x, target.z - pos.z));
	}
	else
	{
		float y_direction = target.y - pos.y;

		target.y = pos.y = 0;

		float angle = (target - pos).Length();

		return (atan(y_direction / angle) * 180 / Math::PI);
	}
}

bool SSDLC::intersect(const Vector3 &topLeft, const Vector3 &bottomRight, const Vector3 &pos)
{
	if (pos.x <= topLeft.x && pos.x >= bottomRight.x)
	{
		if (pos.y <= topLeft.y && pos.y >= bottomRight.y)
		{
			if (pos.z <= topLeft.z && pos.z >= bottomRight.z)
			{
				return true;
			}
		}
	}
	return false;
}

bool SSDLC::intersect2D(const Vector3 &topLeft, const Vector3 &bottomRight, const Vector3 &pos)
{
	if (pos.x <= topLeft.x && pos.x >= bottomRight.x)
	{
		if (pos.y <= topLeft.y && pos.y >= bottomRight.y)
		{
			return true;
		}
	}
	return false;
}

bool SSDLC::intersect_LineAABB(Vector3 &projectilePos, Vector3 &projectileDir, Vector3 &topLeft, Vector3 &bottomRight)
{
	//Vector3 min, max;

	////X Axis
	//if (projectileDir.x >= 0)
	//{
	//	min.x = (bottomRight.x - projectilePos.x) / projectileDir.x;
	//	max.x = (topLeft.x - projectilePos.x) / projectileDir.x;
	//}
	//else
	//{
	//	min.x = (topLeft.x - projectilePos.x) / projectileDir.x;
	//	max.x = (bottomRight.x - projectilePos.x) / projectileDir.x;
	//}

	////Y Axis
	//if (projectileDir.y >= 0)
	//{
	//	min.y = (bottomRight.y - projectilePos.y) / projectileDir.y;
	//	max.y = (topLeft.y - projectilePos.y) / projectileDir.y;
	//}
	//else
	//{
	//	min.y = (topLeft.y - projectilePos.y) / projectileDir.y;
	//	max.y = (bottomRight.y - projectilePos.y) / projectileDir.y;
	//}

	//if (min.x > max.y || min.y > max.x)
	//	return false;
	//if (min.y > min.x)
	//	min.x = min.y;
	//if (max.y < max.x)
	//	max.x = max.y;

	////Z Axis
	//if (projectileDir.z >= 0)
	//{
	//	min.z = (bottomRight.z - projectilePos.z) / projectileDir.z;
	//	max.z = (topLeft.z - projectilePos.z) / projectileDir.z;
	//}
	//else
	//{
	//	min.z = (topLeft.z - projectilePos.z) / projectileDir.z;
	//	max.z = (bottomRight.z - projectilePos.z) / projectileDir.z;
	//}

	//if (min.x > max.z || min.z > max.z)
	//	return false;
	//if (min.z > min.x)
	//	min.x = min.z;
	//if (max.z < max.x)
	//	max.x = max.z;

	//if (min.x < 0 && max.x > 1)
	//	return true;
	//return false;

	float tmin = (bottomRight.x - projectilePos.x) / projectileDir.x;
	float tmax = (topLeft.x - projectilePos.x) / projectileDir.x;

	if (tmin > tmax)
		std::swap(tmin, tmax);

	float tymin = (bottomRight.y - projectilePos.y) / projectileDir.y;
	float tymax = (topLeft.y - projectilePos.y) / projectileDir.y;

	if (tymin > tymax)
		std::swap(tymin, tymax);

	if (tmin > tymax || tymin > tmax)
		return false;

	if (tymin > tmin)
		tmin = tymin;

	if (tymax < tmax)
		tmax = tymax;

	float tzmin = (bottomRight.z - projectilePos.z) / projectileDir.z;
	float tzmax = (topLeft.z - projectilePos.z) / projectileDir.z;

	if (tzmin > tzmax)
		std::swap(tzmin, tzmax);

	if (tmin > tzmax || tzmin > tmax)
		return false;

	if (tzmin > tmin)
		tmin = tzmin;

	if (tzmax < tmax)
		tmax = tzmax;

	return true;
}