#pragma once
#include "Vector3.h"

class SSDLC
{
public:
	SSDLC();
	~SSDLC();

	static float findAngleFromPos(Vector3 target, Vector3 pos, bool XZ = true);

	static bool intersect(const Vector3 &topLeft, const Vector3 &bottomRight, const Vector3 &pos);
	static bool intersect2D(const Vector3 &topLeft, const Vector3 &bottomRight, const Vector3 &pos);
	static bool intersect_LineAABB(Vector3 &projectilePos, Vector3 &projectileDir, Vector3 &topLeft, Vector3 &bottomRight);
};

