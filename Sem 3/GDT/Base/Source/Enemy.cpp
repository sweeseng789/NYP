#include "Enemy.h"
#include "Application.h"


CEnemy::CEnemy(void)
{
	EnemyPosition.Set(0.f, 0.f, 0.f);
	EnemyHealth = 100;
	renderHead = false;
	renderLeftArm = true;
	renderRightArm = true;
	active = true;
	rotateAngle = 0;
}
CEnemy::~CEnemy(void)
{

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

int CEnemy::getEnemyHealth()
{
	return this->EnemyHealth;
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

void CEnemy::minusHealth(int value)
{
	EnemyHealth -= value;
}

void CEnemy::update(float dt, Vector3 pos)
{
	Vector3 temp;
	float hyp = 0;
	temp.x = pos.x - EnemyPosition.x;
	temp.z = pos.z - EnemyPosition.z;
	hyp = sqrt(temp.x * temp.x + temp.z * temp.z);
	temp.x /= hyp;
	temp.z /= hyp;

	//EnemyPosition += temp * 10 * dt;

	findDiff(pos);

	rotateAngle = Math::RadianToDegree(acos(EnemyView.Dot(EnemyDiff) / (EnemyView.Length() * EnemyDiff.Length())));
	if (EnemyView.Cross(EnemyDiff).y > 1)
		rotateAngle *= 1;
	else
		rotateAngle *= -1;
}