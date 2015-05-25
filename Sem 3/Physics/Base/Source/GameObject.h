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
		GO_BOMB,
		GO_EXPLOSION,
		GO_ENEMY,
		GO_ENEMY_LASER,
		GO_HEART,
		GO_BULLET,
		GO_MISSILE,
		GO_POWERUP_Ironman,
		GO_BOSS,
		GO_BOSS_SHIELD,
		GO_TOTAL, //must be last
	};
	GAMEOBJECT_TYPE type;
	Vector3 pos;
	Vector3 vel;
	Vector3 scale;
	double health;
	double damage;
	bool active;
	float mass;
	float angle;
	double bombTime;
	double ScaleSize;
	float bombDuration;
	const unsigned bulletSpeed;
	int number;
	float m_shieldTime;

	GameObject(GAMEOBJECT_TYPE typeValue = GO_BALL);
	~GameObject();

	void setAngle(float angle);
};

#endif