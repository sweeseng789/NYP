#pragma once
#ifndef COLLISION_H
#define COLLISION_H

#include <iostream>
#include <string>
#include "Vector3.h"

using std::cin;
using std::cout;
using std::endl;
using std::to_string;

class Collision
{
public:
	Collision();
	~Collision();

	static bool PointDistance(Vector3 pos1, Vector3 pos2, float range);
	static bool PointDistanceSqrt(Vector3 pos1, Vector3 pos2, float range);
	static bool SphereToSphere(Vector3 pos1, Vector3 pos2, float scale1, float scale2);
};

#endif