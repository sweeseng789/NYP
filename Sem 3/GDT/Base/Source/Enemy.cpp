#include "Enemy.h"
#include "Application.h"


CEnemy::CEnemy(void): active(true), scale(2.2)
{
	vel.x = 3;
}
CEnemy::~CEnemy(void)
{

}

void CEnemy::setPos(Vector3 pos)
{
	this->pos = pos;
}

Vector3 CEnemy::getEnemyPos()
{
	return pos;
}

bool CEnemy::getActive()
{
	return active;
}

float CEnemy::getScale()
{
	return scale;
}

void CEnemy::update(float dt)
{
	if (Application::IsKeyPressed('8'))
	{
		pos.x += 100 * dt;
	}
}