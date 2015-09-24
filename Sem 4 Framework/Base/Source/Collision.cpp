#include "Collision.h"



Collision::Collision()
{
}


Collision::~Collision()
{
}

void Collision::setpos(Vector3 pos)
{
	this->pos = pos;
}

Vector3 Collision::getPos() const
{
	return pos;
}

bool Collision::checkCollision(Collision &CB1, Collision &CB2, float &range)
{
	Collision Type1 = CB1;
	Collision Type2 = CB2;

	if (Type1.type < Type2.type)
	{
		Type1 = CB2;
		Type2 = CB1;
	}

	if (Type1.type == AABB)
	{
		if (Type2.type == AABB)//AABB to AABB
		{
			return AABB_AABB(Type1, Type2);
		}
		else if (Type2.type == SPHERE)//AABB to Sphere
		{
			return AABB_SPHERE(Type1, Type2);
		}
		else if (Type2.type == POINT)//AABB to Point
		{
			return AABB_POINT(Type1, Type2);
		}
		else if (Type2.type == RAY)//AABB to Point
		{
			return AABB_RAY(Type1, Type2);
		}
		else if (Type2.type == PLANE)//AABB to Plane
		{
			return AABB_PLANE(Type1, Type2);
		}
	}
	else if (Type1.type == SPHERE)
	{
		if (Type2.type == SPHERE)//Sphere to Sphere
		{
			return SPHERE_SPHERE(Type1, Type2);
		}
		else if (Type2.type == POINT)//Sphere to Point
		{
			return SPHERE_POINT(Type1, Type2);
		}
		else if (Type2.type == RAY)//Sphere to Ray
		{
			return SPHERE_RAY(Type1, Type2);
		}
		else if (Type2.type == PLANE)//Sphere to Plane
		{
			return SPHERE_PLANE(Type1, Type2);
		}
	}
	else if (Type1.type == POINT)
	{
		if (Type2.type == POINT)//Point to Point
		{
			return POINT_POINT(Type1, Type2, range);
		}
		else if (Type2.type == RAY)//Point to Ray
		{
			return POINT_RAY(Type1, Type2);
		}
		else if (Type2.type == PLANE)//Point to Plane
		{
			return POINT_PLANE(Type1, Type2);
		}
	}
	else if (Type1.type == RAY)
	{
		if (Type2.type == RAY)//Ray to Ray
		{
			return RAY_RAY(Type1, Type2);
		}
		else if (Type2.type == PLANE)//Ray to Plane
		{
			return RAY_PLANE(Type1, Type2);
		}
	}
	else if (Type1.type == PLANE)
	{
		if (Type2.type == PLANE)//Plane to Plane
		{
			return PLANE_PLANE(Type1, Type2);
		}
	}

	return false;
}

//AABB Collision
bool Collision::AABB_AABB(Collision &CB1, Collision &CB2)
{
	Vector3 topLeft = CB1.pos + CB1.CollisionBox + CB2.CollisionBox;
	Vector3 bottomRight = CB1.pos - CB1.CollisionBox - CB2.CollisionBox;

	if (SSDLC::intersect(topLeft, bottomRight, CB2.pos))
	{
		return true;
	}

	return false;
}

bool Collision::AABB_SPHERE(Collision &CB1, Collision &CB2)
{
	float radius = CB2.radius;
	Vector3 topRight = CB1.pos + CB1.CollisionBox + CB1.CollisionOffset;
	Vector3 bottomLeft = CB1.pos - CB1.CollisionBox + CB1.CollisionOffset;
	float distanceDiff = 0.f;
	float temp;

	//X Axis
	if (CB2.pos.x < bottomLeft.x)
	{
		temp = CB2.pos.x - bottomLeft.x;
		distanceDiff += temp * temp;
	}
	else if (CB2.pos.x > topRight.x)
	{
		temp = CB2.pos.x - topRight.x;
		distanceDiff += temp * temp;
	}

	//Z Axis
	if (CB2.pos.z < bottomLeft.z)
	{
		temp = CB2.pos.z - bottomLeft.z;
		distanceDiff += temp * temp;
	}
	else if (CB2.pos.z > topRight.z)
	{
		temp = CB2.pos.z - topRight.z;
		distanceDiff += temp * temp;
	}


	//Y Axis
	if (CB2.pos.y < bottomLeft.y)
	{
		temp = CB2.pos.y - bottomLeft.y;
		distanceDiff += temp * temp;
	}
	else if (CB2.pos.y > topRight.y)
	{
		temp = CB2.pos.y - topRight.y;
		distanceDiff += temp * temp;
	}



	return distanceDiff <= (radius * radius);
}

bool Collision::AABB_POINT(Collision &CB1, Collision &CB2)
{
	return (SSDLC::intersect((CB1.pos + CB1.CollisionBox + CB1.CollisionOffset), (CB1.pos - CB1.CollisionBox + CB1.CollisionOffset), CB2.pos));
}

bool Collision::AABB_RAY(Collision &CB1, Collision &CB2)
{
	Vector3 topRight = CB1.pos + CB1.CollisionBox + CB1.CollisionOffset;
	Vector3 bottomLeft = CB1.pos - CB1.CollisionBox + CB1.CollisionOffset;
	Vector3 min, max;

	//X Axis
	if (CB2.direction.x >= 0)
	{
		min.x = (bottomLeft.x - CB2.pos.x) / CB2.direction.x;
		max.x = (topRight.x - CB2.pos.x) / CB2.direction.x;
	}
	else
	{
		min.x = (topRight.x - CB2.pos.x) / CB2.direction.x;
		max.x = (bottomLeft.x - CB2.pos.x) / CB2.direction.x;
	}

	//Y Axis
	if (CB2.direction.y >= 0)
	{
		min.y = (bottomLeft.y - CB2.pos.y) / CB2.direction.y;
		max.y = (topRight.y - CB2.pos.y) / CB2.direction.y;
	}
	else
	{
		min.y = (topRight.y - CB2.pos.y) / CB2.direction.y;
		max.y = (bottomLeft.y - CB2.pos.y) / CB2.direction.y;
	}

	if (min.x > max.y || min.y > max.x)
		return false;

	if (min.y > min.x)
	{
		min.x = min.y;
	}

	if (max.y < max.x)
	{
		max.x = max.y;
	}

	//Z Axis
	if (CB2.direction.z > 0)
	{
		min.z = (bottomLeft.z - CB2.pos.z) / CB2.direction.z;
		max.z = (topRight.z - CB2.pos.z) / CB2.direction.z;
	}
	else
	{
		min.z = (topRight.z - CB2.pos.z) / CB2.direction.z;
		max.z = (bottomLeft.z - CB2.pos.z) / CB2.direction.z;
	}

	if (min.x > max.z || min.z > max.z)
		return false;

	if (min.z > min.z)
	{
		min.x = min.z;
	}
	if (max.z < max.x)
	{
		max.x = max.z;
	}

	return ((min.x < CB2.interval_Min) && (max.x > CB2.interval_Max));
}

bool Collision::AABB_PLANE(Collision &CB1, Collision &CB2)
{
	Vector3 topRight = CB1.pos + CB1.CollisionBox + CB1.CollisionOffset;
	Vector3 bottomLeft = CB1.pos - CB1.CollisionBox + CB1.CollisionOffset;
	Vector3 v1 = (topRight - bottomLeft) * 0.5f;

	float rad = abs(CB2.planeNormal.x * v1.x) + abs(CB2.planeNormal.y * v1.y) + abs(CB2.planeNormal.z * v1.z);

	CB1.radius = rad;

	return SPHERE_PLANE(CB1, CB2);
}

//Sphere Collision
bool Collision::SPHERE_SPHERE(Collision &CB1, Collision &CB2)
{
	float radius1 = CB1.radius;
	float radius2 = CB2.radius;

	//Difference between their center
	Vector3 diff;
	diff.x = pow(CB1.pos.x - CB2.pos.x, 2);
	diff.y = pow(CB1.pos.y - CB2.pos.y, 2);
	diff.z = pow(CB1.pos.z - CB2.pos.z, 2);

	float d = diff.x + diff.y + diff.z;

	//Combined radius of the 2 sphere
	float CR = pow(radius1 + radius2, 2);

	if (d <= CR)
		return true;

	return false;
}

bool Collision::SPHERE_POINT(Collision &CB1, Collision &CB2)
{
	float radius1 = CB1.radius;

	//Difference between their center
	Vector3 diff;
	diff.x = pow(CB1.pos.x - CB2.pos.x, 2);
	diff.y = pow(CB1.pos.y - CB2.pos.y, 2);
	diff.z = pow(CB1.pos.z - CB2.pos.z, 2);

	float d = diff.x + diff.y + diff.z;

	//Combined radius of 2 sphere
	float CR = pow(radius1, 2);

	if (d <= CR)
		return true;

	return false;
}

bool Collision::SPHERE_RAY(Collision &CB1, Collision &CB2)
{
	return false;
}

bool Collision::SPHERE_PLANE(Collision &CB1, Collision &CB2)
{
	float dot = CB2.planeNormal.Dot(CB1.pos);

	if (dot > CB1.radius)
		return false;
	else if (dot < -CB1.radius)
		return false;

	return true;
}


//Point Collision
bool Collision::POINT_POINT(Collision &CB1, Collision &CB2, float &range)
{
	Vector3 pos1 = CB1.pos;
	Vector3 pos2 = CB2.pos;

	if ((pos1 - pos2).Length() < range)
		return true;
	return false;
}

bool Collision::POINT_RAY(Collision &CB1, Collision &CB2)
{
	return false;
}

bool Collision::POINT_PLANE(Collision &CB1, Collision &CB2)
{
	Vector3 pointOnPlane = CB2.pos + CB2.CollisionBox;
	float d = SSDLC::minDistance(CB1.pos, CB2.pos, pointOnPlane);

	if (d <= 0)
		return true;
	return false;
}

//Ray Collision
bool Collision::RAY_RAY(Collision &CB1, Collision &CB2)
{
	return false;
}

bool Collision::RAY_PLANE(Collision &CB1, Collision &CB2)
{
	Vector3 ray = CB1.pos - CB1.end;

	if (ray.LengthSquared() == 0)
		return false;

	float dot1 = CB2.planeNormal.Dot(CB1.pos);
	float dot2 = CB2.planeNormal.Dot(ray);

	if(dot1 == 0 || dot2 == 0)
		return false;

	Vector3 intersection = CB1.end + (((CB2.offset - dot1) / dot2) * ray);

	if (intersection.LengthSquared() == 0)
		return false;

	return true;
}

//Plane Collision
bool Collision::PLANE_PLANE(Collision &CB1, Collision &CB2)
{
	return false;
}