#pragma once
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

	Vector3 returnEnemyPosition();
	Vector3 returnEnemyHeadPosition();
	Vector3 returnEnemyTorsoPosition();
	Vector3 returnEnemyLeftHandPosition();
	Vector3 returnEnemyRightHandPosition();
	Vector3 returnEnemyLeftLegPosition();
	Vector3 returnEnemyRightLegPosition();

	Vector3 returnEnemyHeadHitboxMax();
	Vector3 returnEnemyHeadHitboxMin();

	Vector3 returnEnemyTorsoHitboxMax();
	Vector3 returnEnemyTorsoHitboxMin();

	Vector3 returnEnemyLeftHandHitboxMax();
	Vector3 returnEnemyLeftHandHitboxMin();

	Vector3 returnEnemyRightHandHitboxMax();
	Vector3 returnEnemyRightHandHitboxMin();

	Vector3 returnEnemyLeftLegHitboxMax();
	Vector3 returnEnemyLeftLegHitboxMin();

	Vector3 returnEnemyRightLegHitboxMax();
	Vector3 returnEnemyRightLegHitboxMin();

	bool returnAliveState();
	int returnEnemyHealth();
	void MinusEnemyHeadHealth(int valueToMinus);
	void MinusEnemyTorsoHealth(int valueToMinus);
	void MinusEnemyLeftArmHealth(int valueToMinus);
	void MinusEnemyRightArmHealth(int valueToMinus);
	void KillEnemy();
	void update(float dt);
	bool returnRenderHead();
	bool returnRenderLeftArm();
	bool returnRenderRightArm();
private:
	bool Alive;
	bool renderHead;
	bool renderLeftArm;
	bool renderRightArm;
	int EnemyHealth;
	int HeadHealth;
	int TorsoHealth;
	int LeftArmHealth;
	int RightArmHealth;
	
	Vector3 EnemyPosition;
	Vector3 EnemyHeadPosition;
	Vector3 EnemyTorsoPosition;
	Vector3 EnemyLeftHandPosition;
	Vector3 EnemyRightHandPosition;
	Vector3 EnemyLeftLegPosition;
	Vector3 EnemyRightLegPosition;

	Vector3 HeadHitBoxMax;
	Vector3 HeadHitBoxMin;

	Vector3 TorsoHitBoxMax;
	Vector3 TorsoHitBoxMin;

	Vector3 LeftHandHitBoxMax;
	Vector3 LeftHandHitBoxMin;

	Vector3 RightHandHitBoxMax;
	Vector3 RightHandHitBoxMin;

	Vector3 LeftLegHitBoxMax;
	Vector3 LeftLegHitBoxMin;

	Vector3 RightLegHitBoxMax;
	Vector3 RightLegHitBoxMin;
};

