#pragma once

#include <hge.h>
#include <hgerect.h>
#include <memory>
#include <vector>
#include "Vector3.h"

class hgeSprite;
class hgeRect;
class Ship;

class CProjectile
{
public:
	//===== CONSTRUCTOR & DESTRUCTOR =====//
	CProjectile();
	virtual ~CProjectile();

	//===== GETTER =====//
	bool hasCollided(Ship* ship);
	int getOwnerID();
	bool getActive();
	Vector3 getPos() const;
	Vector3 getVel() const;

	//===== SETTER =====//
	void Render();
	bool Update(std::vector<Ship*> &shipList, float dt);
	void UpdateLoc(float x, float y, float w);
	void setVelocityX(float velocity);
	void setVelocityY(float velocity);
	void setActive(bool active);

protected:
	//Int
	int ownerid;

	//Bool
	bool active;

	//Float
	float angular_velocity;

	//Class Or Vector Variables
	HTEXTURE text;
	std::auto_ptr<hgeSprite> sprite;
	hgeRect collidebox;
	Vector3 pos;
	Vector3 oldPos;
	Vector3 vel;
};

