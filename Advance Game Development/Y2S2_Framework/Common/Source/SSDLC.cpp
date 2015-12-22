#include "SSDLC.h"
#include <algorithm>
using std::max;
using std::min;

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
	Vector3 max, min;

	min.x = (bottomRight.x - projectilePos.x) / projectileDir.x;
	max.x = (topLeft.x - projectilePos.x) / projectileDir.x;

	if (min.x > max.x)
		std::swap(min.x, max.x);

	min.y = (bottomRight.y - projectilePos.y) / projectileDir.y;
	max.y = (topLeft.y - projectilePos.y) / projectileDir.y;

	if (min.y > max.y)
		std::swap(min.y, max.y);

	if (min.x > max.y || min.y > max.x)
		return false;

	if (min.y > min.x)
		min.x = min.y;

	if (max.y < max.x)
		max.x = max.y;

	min.z = (bottomRight.z - projectilePos.z) / projectileDir.z;
	max.z = (topLeft.z - projectilePos.z) / projectileDir.z;

	if (min.z > max.z)
		std::swap(min.z, max.z);

	if (min.x > max.z || min.z > max.x)
		return false;

	if (min.z > min.x)
		min.x = min.z;

	if (max.z < max.x)
		max.x = max.z;

	return true;
}