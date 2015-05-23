
#include "GameObject.h"
#include "Application.h"
#include "Mtx44.h"
#include <Windows.h>

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

void GameObject::SetData(Vector3 pos, Vector3 target, Vector3 up)
{
	this->pos = pos;
	this->target = target;
	Vector3 view = (target - pos).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = right.Cross(view).Normalized();
}

void GameObject::Update(float dt)
{

}

void GameObject::angleUpdate(float dt, GameObject* m_ship)
{
	/*this->EnemyDiff = m_ship->pos - this->pos;
	std::cout << target << std::endl;

	/*angle = Math::RadianToDegree(acos(view.Dot(EnemyDiff) / (view.Length() * EnemyDiff.Length())));
	if(view.Cross(EnemyDiff).y > 1)
	{
		angle *= 1;
	}
	else
	{
		angle *= -1;
	}*/
}