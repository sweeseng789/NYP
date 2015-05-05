#include "Enemy.h"


CEnemy::CEnemy(void) :	EnemyPosition			(Vector3(0.0f, 0.0f, 0.0f)),
						EnemyHeadPosition		(Vector3(0.0f, -3.76f, 0.0f)),
						EnemyTorsoPosition		(Vector3(0.0f, 0.0f, 0.0f)),
						EnemyLeftHandPosition	(Vector3 (-0.8f, 0.75f, 0.f)),
						EnemyRightHandPosition	(Vector3 (0.8f, 0.75f, 0.f)),
						EnemyLeftLegPosition	(Vector3 (-0.34f, -1.5f, 0.f)),
						EnemyHealth				(0),
						HeadHealth				(20),
						TorsoHealth				(50),
						LeftArmHealth			(15),
						RightArmHealth			(15),
						renderHead				(true),
						renderLeftArm			(true),
						renderRightArm			(true),
						Alive					(true)
{
	//Head
	HeadHitBoxMin.x = -0.6f;
	HeadHitBoxMax.x = 0.6f;

	HeadHitBoxMax.y = 1.f;
	HeadHitBoxMin.y = 0.2f;

	HeadHitBoxMax.z = 0.6f;
	HeadHitBoxMin.z = -0.5f;

	//Torso
	TorsoHitBoxMax.x = 0.6f;
	TorsoHitBoxMin.x = -0.63f;

	TorsoHitBoxMax.y = 1.0f;
	TorsoHitBoxMin.y = -2.0f;

	TorsoHitBoxMax.z = 0.6f;
	TorsoHitBoxMin.z = -0.46f;

	//Left Arm
	LeftHandHitBoxMax.x = 0.96f;
	LeftHandHitBoxMin.x = 0.44f;

	LeftHandHitBoxMax.y = 0.14f;
	LeftHandHitBoxMin.y = -1.3f;

	LeftHandHitBoxMax.z = 0.42f;
	LeftHandHitBoxMin.z = -0.3f;

	//Right Arm
	RightHandHitBoxMax.x = -0.54f;
	RightHandHitBoxMin.x = -1.05f;

	RightHandHitBoxMax.y = 0.14f;
	RightHandHitBoxMin.y = -1.3f;

	RightHandHitBoxMax.z = 0.42f;
	RightHandHitBoxMin.z = -0.3f;

	//Left Leg
	LeftLegHitBoxMax.x = 0.1f;
	LeftLegHitBoxMin.x = 0.6f;

	LeftLegHitBoxMax.y = 5.0f;
	LeftLegHitBoxMin.y = -5.0f;

	LeftLegHitBoxMax.z = 10.0f;
	LeftLegHitBoxMin.z = -10.0f;
}
CEnemy::~CEnemy(void)
{
	//cout << "Enemy Deleted" << endl;
}
Vector3 CEnemy::returnEnemyPosition()
{
	return EnemyPosition;
}
Vector3 CEnemy::returnEnemyHeadPosition()
{
	return this->EnemyHeadPosition;
}
Vector3 CEnemy::returnEnemyTorsoPosition()
{
	return this->EnemyTorsoPosition;
}
Vector3 CEnemy::returnEnemyLeftHandPosition()
{
	return this->EnemyLeftHandPosition;
}
Vector3 CEnemy::returnEnemyRightHandPosition()
{
	return this->EnemyRightHandPosition;
}
Vector3 CEnemy::returnEnemyLeftLegPosition()
{
	return this->EnemyLeftLegPosition;
}
Vector3 CEnemy::returnEnemyRightLegPosition()
{
	return this->EnemyRightLegPosition;
}
Vector3 CEnemy::returnEnemyHeadHitboxMax()
{
	return this->HeadHitBoxMax;
}
Vector3 CEnemy::returnEnemyHeadHitboxMin()
{
	return this->HeadHitBoxMin;
}
Vector3 CEnemy::returnEnemyTorsoHitboxMax()
{
	return this->TorsoHitBoxMax;
}
Vector3 CEnemy::returnEnemyTorsoHitboxMin()
{
	return this->TorsoHitBoxMin;
}
Vector3 CEnemy::returnEnemyLeftHandHitboxMax()
{
	return this->LeftHandHitBoxMax;
}
Vector3 CEnemy::returnEnemyLeftHandHitboxMin()
{
	return this->LeftHandHitBoxMin;
}
Vector3 CEnemy::returnEnemyRightHandHitboxMax()
{
	return this->RightHandHitBoxMax;
}
Vector3 CEnemy::returnEnemyRightHandHitboxMin()
{
	return this->RightHandHitBoxMin;
}
Vector3 CEnemy::returnEnemyLeftLegHitboxMax()
{
	return this->LeftLegHitBoxMax;
}
Vector3 CEnemy::returnEnemyLeftLegHitboxMin()
{
	return this->LeftLegHitBoxMin;
}
Vector3 CEnemy::returnEnemyRightLegHitboxMax()
{
	return this->RightLegHitBoxMax;
}
Vector3 CEnemy::returnEnemyRightLegHitboxMin()
{
	return this->RightLegHitBoxMin;
}
bool CEnemy::returnAliveState()
{
	return this->Alive;
}
bool CEnemy::returnRenderHead()
{
	return renderHead;
}
bool CEnemy::returnRenderLeftArm()
{
	return renderLeftArm;
}
bool CEnemy::returnRenderRightArm()
{
	return renderRightArm;
}
int CEnemy::returnEnemyHealth()
{
	return this->EnemyHealth;
}
void CEnemy::MinusEnemyHeadHealth(int valueToMinus)
{
	this->HeadHealth -= valueToMinus;
}
void CEnemy::MinusEnemyTorsoHealth(int valueToMinus)
{
	this->TorsoHealth -= valueToMinus;
}
void CEnemy::MinusEnemyLeftArmHealth(int valueToMinus)
{
	this->LeftArmHealth -= valueToMinus;
}
void CEnemy::MinusEnemyRightArmHealth(int valueToMinus)
{
	this->RightArmHealth -= valueToMinus;
}
void CEnemy::KillEnemy()
{
	this->Alive = false;
}

void CEnemy::update(float dt)
{
	EnemyHealth = HeadHealth + TorsoHealth + LeftArmHealth + RightArmHealth;

	if (HeadHealth <= 0)
		this->renderHead = false;
	if (LeftArmHealth <= 0)
		this->renderLeftArm = false;
	if (RightArmHealth <= 0)
		this->renderRightArm = false;
	if (EnemyHealth <= 0)
		KillEnemy();
}