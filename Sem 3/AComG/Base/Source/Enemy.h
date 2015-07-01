#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <vector>
#include "Camera3.h"
#include "MyMath.h"
#include "Vector3.h"
#include "SpriteAnimation.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

class CEnemy
{
public:
	CEnemy(void);
	~CEnemy(void);

	//Getter
	float getRotateAngle();
	Vector3 getEnemyPos();

	//Setter
	void update(float dt, Vector3 pos);
	void findDiff(Vector3 pos);
	void setPos(Vector3 pos, Vector3 target);
	void setAngle(float rotateAngle);
	void setSpriteAnimation(SpriteAnimation *sa);

	//Variable
	bool active;
	float defaultAngle;
	float defaultAngle2;
	bool test;
	Vector3 EnemyPosition;

	SpriteAnimation *sa;
private:
	//Float
	float rotateAngle;

	int count;

	//Vector3
	
	Vector3 EnemyTarget;
	Vector3 EnemyView;
	Vector3 EnemyDiff;
};

#endif