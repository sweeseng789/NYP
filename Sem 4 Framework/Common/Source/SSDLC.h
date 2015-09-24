#ifndef SSDLC_H
#define SSDLC_H

#include "Vector3.h"
class SSDLC
{
public:
	SSDLC();
	~SSDLC();
	
	static bool intersect(const Vector3 &TopLeft, const Vector3 &BottomRight, const Vector3 &pos);
	static bool intersect2D(const Vector3 &TopLeft, const Vector3 &BottomRight, const Vector3 &pos);
	static float minDistance(const Vector3 &point, const Vector3 &pointPlane1, const Vector3 &pointPlane2);
};

#endif