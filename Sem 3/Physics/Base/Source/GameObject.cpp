
#include "GameObject.h"

GameObject::GameObject(GAMEOBJECT_TYPE typeValue) 
	: type(typeValue),
	scale(1, 1, 1),
	active(false),
	mass(1.f),
	angle(0),
	bulletSpeed(100)
{
}

GameObject::~GameObject()
{
}

void GameObject::setAngle(float angle)
{
	this->angle = angle;
}