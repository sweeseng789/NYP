#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Vector3.h"

struct GameObject
{
	enum GAMEOBJECT_TYPE
	{
		GO_NONE = 0,
		GO_BALL,
		GO_BALL2,
		GO_BALL3,
		GO_BALL4,
		GO_BALL5,
		GO_BALL6,
		GO_BALL7,
		GO_BALL8,
		GO_BALL9,
		GO_BALL10,
		GO_BALL11,
		GO_BALL12,
		GO_BALL13,
		GO_BALL14,
		GO_BALL15,
		GO_CUBE,
		GO_WALL,
		GO_WALL2,
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
	Vector3 normal;
	Vector3 tempPos;

	GameObject(GAMEOBJECT_TYPE typeValue = GO_BALL);
	~GameObject();

	void setAngle(float angle);
};

#endif