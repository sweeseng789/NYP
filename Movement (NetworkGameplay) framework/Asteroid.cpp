#include "Asteroid.h"
#include <hge.h>
#include <hgeSprite.h>
#include <math.h>
#include "ship.h"
#include"Laser.h"

CAsteroid::CAsteroid()
{
}

CAsteroid::CAsteroid(float x, float y, float w, bool smallAsteroid)
{
	HGE* hge = hgeCreate(HGE_VERSION);
	if (smallAsteroid)
	{
		tex_ = hge->Texture_Load("Asteroid_Small.png");
		sprite_.reset(new hgeSprite(tex_, 0, 0, 20, 20));
		sprite_->SetHotSpot(10, 10);
		type = s_SMALL;
	}
	else
	{
		tex_ = hge->Texture_Load("Asteroid_Big.png");
		sprite_.reset(new hgeSprite(tex_, 0, 0, 50, 50));
		sprite_->SetHotSpot(25, 25);
		type = s_BIG;
	}
	hge->Release();

	x_ = x;
	y_ = y;
	w_ = w;

	active = true;

	velocity_x_ = 20.0f * cosf(w_);
	velocity_y_ = 20.0f * sinf(w_);

	
}


CAsteroid::~CAsteroid()
{
}

void CAsteroid::Update(float dt)
{
	HGE* hge = hgeCreate(HGE_VERSION);
	float pi = 3.141592654f * 2;
	float oldx, oldy;

	w_ += dt;
	if (w_ > pi)
		w_ -= pi;

	if (w_ < 0.0f)
		w_ += pi;

	oldx = x_;
	oldy = y_;
	x_ += velocity_x_ * dt;
	y_ += velocity_y_ * dt;

	float screenwidth = static_cast<float>(hge->System_GetState(HGE_SCREENWIDTH));
	float screenheight = static_cast<float>(hge->System_GetState(HGE_SCREENHEIGHT));
	float spritewidth = sprite_->GetWidth();
	float spriteheight = sprite_->GetHeight();

	if (x_ < -spritewidth / 2)
	{
		x_ = screenwidth + spritewidth / 2;
	}
	else if (x_ > screenwidth + spritewidth / 2)
	{
		x_ = 0 - spritewidth / 2;
	}

	if (y_ < -spriteheight / 2)
	{
		y_ = screenheight + spriteheight / 2;
	}
	else if (y_ > screenheight + spriteheight / 2)
	{
		y_ = 0 - spriteheight / 2;
	}
}

bool CAsteroid::UpdateShip(std::vector<Ship*> &shipList, float dt)
{
	for (std::vector<Ship*>::iterator it = shipList.begin(); it != shipList.end(); ++it)
	{
		Ship* ship = static_cast<Ship*>(*it);
		if (hasCollided(ship))
		{
			ship->Restart();
			return true;
		}
	}
	return false;
}

bool CAsteroid::UpdateLaser(std::vector<Laser*> &laserList)
{
	for (std::vector<Laser*>::iterator it = laserList.begin(); it != laserList.end(); ++it)
	{
		Laser* laser = static_cast<Laser*>(*it);
		if (hasCollided(laser))
		{
			delete *it;
			laserList.erase(it);
			return true;
		}
	}
	return false;
}

bool CAsteroid::hasCollided(Ship* ship)
{
	sprite_->GetBoundingBox(x_, y_, &collidebox);

	return collidebox.Intersect(ship->GetBoundingBox());
}

bool CAsteroid::hasCollided(Laser* laser)
{

	sprite_->GetBoundingBox(x_, y_, &collidebox);
	return collidebox.Intersect(laser->GetBoundingBox());
}

void CAsteroid::Render()
{
	sprite_->RenderEx(x_, y_, w_);
}