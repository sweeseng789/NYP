#pragma once
#include "Vector3.h"

class SSDLC
{
public:
	SSDLC();
	~SSDLC();

	static float findAngleFromPos(Vector3 target, Vector3 pos, bool XZ = true);
};

