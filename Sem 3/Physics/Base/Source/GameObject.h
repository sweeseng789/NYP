#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"

struct GameObject
{
	enum GAMEOBJECT_TYPE
	{
		GO_NONE = 0,
		GO_BALL,
		GO_CUBE,
		GO_ASTEROID_SMALL,
		GO_ASTEROID_BIG,
		GO_SHIP,
		GO_SHIP_THURSTER,
		GO_ENEMY,
		GO_BULLET,
		GO_MISSILE,
		GO_TOTAL, //must be last
	};
	GAMEOBJECT_TYPE type;
	Vector3 pos;
	Vector3 view;
	Vector3 target;
	Vector3 vel;
	Vector3 up;
	Vector3 scale;
	Vector3 EnemyDiff;
	bool active;
	float mass;
	float angle;
	double bulletSpeed;
	float testing;

	GameObject(GAMEOBJECT_TYPE typeValue = GO_BALL);
	~GameObject();

	void setAngle(float angle);
	void SetData(Vector3 pos, Vector3 target, Vector3 up);
	void Update(float dt);
	void angleUpdate(float dt, GameObject* m_ship);
};

#endif