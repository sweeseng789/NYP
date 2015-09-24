#ifndef COLLISION_H
#define COLLISION_H

#include "Vector3.h"
#include "SSDLC.h"

class Collision
{
public:
	enum COLLISION_TYPE
	{
		AABB,
		SPHERE,
		POINT,
		RAY,
		PLANE
	};

	Collision();
	~Collision();

	//AABB
	Vector3 CollisionBox;
	Vector3 CollisionOffset;

	//Sphere
	float radius;

	//Ray
	Vector3 direction;
	Vector3 end;
	float interval_Min, interval_Max;

	//Plane
	Vector3 planeNormal;
	float offset;

	COLLISION_TYPE type;
	Vector3 pos;
	static bool checkCollision(Collision &CB1, Collision &CB2, float &range);
	void setpos(Vector3 pos);
	Vector3 getPos() const;

private:
	//AABB Colliison
	static bool AABB_AABB(Collision &CB1, Collision &CB2);
	static bool AABB_SPHERE(Collision &CB1, Collision &CB2);
	static bool AABB_POINT(Collision &CB1, Collision &CB2);
	static bool AABB_RAY(Collision &CB1, Collision &CB2);
	static bool AABB_PLANE(Collision &CB1, Collision &CB2);

	//Sphere Colliison
	static bool SPHERE_SPHERE(Collision &CB1, Collision &CB2);
	static bool SPHERE_POINT(Collision &CB1, Collision &CB2);
	static bool SPHERE_RAY(Collision &CB1, Collision &CB2);
	static bool SPHERE_PLANE(Collision &CB1, Collision &CB2);

	//Point Colliison
	static bool POINT_POINT(Collision &CB1, Collision &CB2, float &range);
	static bool POINT_RAY(Collision &CB1, Collision &CB2);
	static bool POINT_PLANE(Collision &CB1, Collision &CB2);

	//Ray Colliison
	static bool RAY_RAY(Collision &CB1, Collision &CB2);
	static bool RAY_PLANE(Collision &CB1, Collision &CB2);

	//Plane Colliison
	static bool PLANE_PLANE(Collision &CB1, Collision &CB2);
};

#endif