#include "GameObject.h"

float CGameObject::velSpeed = 30.f;

CGameObject::CGameObject() :
	rotateAngle(0),
	pos(0),
	vel(0),
	target(0),
	direction(0),
	animation(NULL),
	m_cSceneGraph(NULL),
	type(STATIC_OBJ),
	nodeList(NULL)
{
}

CGameObject::CharAnimation::CharAnimation():
	vel_LeftArm(0.f),
	vel_LeftLeg(0.f),
	vel_RightArm(0.f),
	vel_RightLeg(0.f),
	invertWalkingDirection(false)
{
}


CGameObject::~CGameObject()
{
	if (m_cSceneGraph)
	{
		delete m_cSceneGraph;
		m_cSceneGraph = NULL;
	}

	if (animation)
	{
		delete animation;
		animation = NULL;
	}
}

CGameObject::CharAnimation::~CharAnimation()
{
}

void CGameObject::CharAnimation::Update(const double &dt, float vel)
{
	if (invertWalkingDirection == false)
	{
		if (vel > 0)
		{
			vel_LeftLeg += dt * vel;
		}
		else
		{
			vel_LeftLeg -= dt * vel;
		}

		if (vel_LeftLeg > 30)
			invertWalkingDirection = true;
	}
	else
	{
		if (vel > 0)
		{
			vel_LeftLeg -= dt * vel;
		}
		else
		{
			vel_LeftLeg += dt * vel;
		}

		if (vel_LeftLeg < -30)
			invertWalkingDirection = false;
	}

	//Friction
	if (vel < 0.5 && vel > -0.5)
	{
		vel_LeftLeg += (0 - vel_LeftLeg) * dt * 5.f;
	}

	vel_RightLeg = -vel_LeftLeg;

	vel_LeftArm = vel_RightLeg;
	vel_RightArm = vel_LeftLeg;
}

void CGameObject::CharAnimation::setZero()
{
	invertWalkingDirection = false;
	vel_LeftArm = vel_LeftLeg = vel_RightArm = vel_RightLeg = 0.f;
}

void CGameObject::setPos(Vector3 pos)
{
	this->pos = pos;
}

void CGameObject::setPos_x(float pos_x)
{
	pos.x = pos_x;
}

void CGameObject::setPos_y(float pos_y)
{
	pos.y = pos_y;
}

void CGameObject::setPos_z(float pos_z)
{
	pos.z = pos_z;
}

void CGameObject::setVel(Vector3 vel)
{
	this->vel = vel;
}

void CGameObject::setScale(Vector3 scale)
{
	this->scale = scale;
}

void CGameObject::setDirection(Vector3 direction)
{
	this->direction = direction;
}

void CGameObject::setActive(bool active)
{
	this->active = active;
}

void CGameObject::setType_PlayerBullet()
{
	this->type = PLAYERBULLET;
}

void CGameObject::setType_EnemyBullet()
{
	this->type = ENEMYBULLET;
}

bool CGameObject::isPlayer()
{
	if (type == PLAYER)
		return true;
	return false;
}

bool CGameObject::isEnemy()
{
	if (type == ENEMY)
		return true;
	return false;
}

bool CGameObject::isStaticOBJ()
{
	if (type == STATIC_OBJ)
		return true;
	return false;
}

bool CGameObject::isMovableObj()
{
	if (type == MOVABLE_OBJ)
		return true;
	return false;
}

bool CGameObject::isPlayerBullet()
{
	if (type == PLAYERBULLET)
		return true;
	return false;
}

bool CGameObject::isEnemyBullet()
{
	if (type == ENEMYBULLET)
		return true;
	return false;
}

bool CGameObject::getActive()
{
	return active;
}

Vector3 CGameObject::getPos()
{
	return pos;
}

Vector3& CGameObject::getVel()
{
	return vel;
}

Vector3 CGameObject::getScale()
{
	return scale;
}

Vector3 CGameObject::getTarget()
{
	return target;
}

Vector3 CGameObject::getDirection()
{
	return direction;
}

CSceneNode* CGameObject::getNode()
{
	return m_cSceneGraph;
}

CGameObject::GO_TYPE CGameObject::getType()
{
	return type;
}

std::unordered_map<int, std::string> CGameObject::getNodeList()
{
	return nodeList;
}

CSceneNode* CGameObject::getSceneGraph()
{
	return m_cSceneGraph;
}