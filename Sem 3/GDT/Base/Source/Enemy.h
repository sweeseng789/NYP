#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <vector>
#include "Camera3.h"
#include "MyMath.h"
#include "Vector3.h"

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
	int getEnemyHealth();
	bool returnRenderHead();
	bool returnRenderLeftArm();
	bool returnRenderRightArm();
	float getRotateAngle();
	Vector3 getEnemyPos();

	//Setter
	void update(float dt, Vector3 pos);
	void findDiff(Vector3 pos);
	void setPos(Vector3 pos, Vector3 target);
	void minusHealth(int valueToMinus);

	//Variable
	bool active;
private:
	//Int
	int EnemyHealth;

	//Float
	float rotateAngle;

	//Bool
	bool renderHead;
	bool renderLeftArm;
	bool renderRightArm;

	//Vector3
	Vector3 EnemyPosition;
	Vector3 EnemyTarget;
	Vector3 EnemyView;
	Vector3 EnemyDiff;
};

#endif