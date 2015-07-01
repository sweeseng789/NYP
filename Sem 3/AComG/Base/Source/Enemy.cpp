#include "Enemy.h"
#include "Application.h"


CEnemy::CEnemy(void)
{
	EnemyPosition.Set(0.f, 0.f, 0.f);
	active = true;
	test = false;
	rotateAngle = 0;
	count = -1;
}
CEnemy::~CEnemy(void)
{

}

void CEnemy::setAngle(float rotateAngle)
{
	this->rotateAngle = rotateAngle;
}
void CEnemy::setSpriteAnimation(SpriteAnimation *sa)
{
	this->sa = sa;
}


Vector3 CEnemy::getEnemyPos()
{
	return EnemyPosition;
}

void CEnemy::findDiff(Vector3 pos)
{
	EnemyDiff = pos - EnemyPosition;
}

void CEnemy::setPos(Vector3 pos, Vector3 target)
{
	EnemyPosition = pos;
	EnemyTarget = target;
	EnemyView = (EnemyTarget - EnemyPosition).Normalized();
}

float CEnemy::getRotateAngle()
{
	return rotateAngle;
}

void CEnemy::update(float dt, Vector3 pos)
{
	/*Vector3 diff;
	diff.x = pos.x - EnemyPosition.x;
	diff.z = pos.z - EnemyPosition.z;
	float angle = Math::RadianToDegree(atan2(diff.x, diff.z)) + rotateAngle;

	if (angle < 0 || angle > 180)
		test = false;
	else
		test = true;*/

	Vector3 temp;
	float hyp = 0;
	temp.x = pos.x - EnemyPosition.x;
	temp.z = pos.z - EnemyPosition.z;
	hyp = sqrt(temp.x * temp.x + temp.z * temp.z);
	temp.x /= hyp;
	temp.z /= hyp;

	EnemyPosition += temp * 1 * dt;

	Vector3 diff;
	diff.x = pos.x - EnemyPosition.x;
	diff.z = pos.z - EnemyPosition.z;
	rotateAngle = Math::RadianToDegree(atan2(diff.x, diff.z));
}