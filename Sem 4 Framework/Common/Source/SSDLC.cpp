#include "SSDLC.h"



SSDLC::SSDLC()
{
}


SSDLC::~SSDLC()
{
}

bool SSDLC::intersect(const Vector3 & TopLeft, const Vector3 & BottomRight, const Vector3 & pos)
{
	if (pos.x <= TopLeft.x && pos.x >= BottomRight.x)
	{
		if (pos.y <= TopLeft.y && pos.y >= BottomRight.y)
		{
			if (pos.z <= TopLeft.z && pos.z >= BottomRight.z)
			{
				return true;
			}
		}
	}

	return false;
}

bool SSDLC::intersect2D(const Vector3 & TopLeft, const Vector3 & BottomRight, const Vector3 & pos)
{
	if (pos.x <= TopLeft.x && pos.x >= BottomRight.x)
	{
		if (pos.y <= TopLeft.y && pos.y >= BottomRight.y)
		{
			return true;
		}
	}

	return false;
}

float SSDLC::minDistance(const Vector3 &point, const Vector3 &pointPlane1, const Vector3 &pointPlane2)
{
	return point.Dot(pointPlane1.Cross(pointPlane2));
}