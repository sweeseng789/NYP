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

bool SSDLC::intersect(const Vector3 &TopLeft, const Vector3 &bottomRight, const Vector3 &pos)
{
	if (pos.x <= TopLeft.x && pos.x >= bottomRight.x)
	{
		if (pos.y <= TopLeft.y && pos.y >= bottomRight.y)
		{
			if (pos.z <= TopLeft.z && pos.z >= bottomRight.z)
			{
				return true;
			}
		}
	}
	return false;
}

bool SSDLC::intersect2D(const Vector3 &TopLeft, const Vector3 &bottomRight, const Vector3 &pos)
{
	if (pos.x <= TopLeft.x && pos.x >= bottomRight.x)
	{
		if (pos.y <= TopLeft.y && pos.y >= bottomRight.y)
		{
			return true;
		}
	}
	return false;
}