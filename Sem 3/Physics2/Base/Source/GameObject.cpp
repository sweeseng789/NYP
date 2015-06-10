
#include "GameObject.h"

GameObject::GameObject(GAMEOBJECT_TYPE typeValue) 
	: type(typeValue),
	scale(1, 1, 1),
	active(false),
	mass(1.f),
	angle(0),
	bulletSpeed(500),
	bombTime(0),
	ScaleSize(0.0),
	bombDuration(0.f),
	number(0),
	m_shieldTime(0)
{
}

GameObject::~GameObject()
{
}

void GameObject::setAngle(float angle)
{
	this->angle = angle;
}