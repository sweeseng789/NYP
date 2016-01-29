#include "Projectile.h"
#include "ship.h"
#include <hge.h>
#include <hgeSprite.h>
#include <math.h>

CProjectile::CProjectile()
{
	ownerid = 0;
	angular_velocity = 0;
	text = NULL;
	sprite.reset();
	pos.SetZero();
	oldPos.SetZero();
	vel.SetZero();
	active = false;
}


CProjectile::~CProjectile()
{
	HGE* hge = hgeCreate(HGE_VERSION);
	hge->Texture_Free(text);
	hge->Release();

}

bool CProjectile::Update(std::vector<Ship*> &shipList, float dt)
{
	HGE* hge = hgeCreate(HGE_VERSION);
	float pi = 3.141592654f * 2;
	float screenwidth = static_cast<float>(hge->System_GetState(HGE_SCREENWIDTH));
	float screenheight = static_cast<float>(hge->System_GetState(HGE_SCREENHEIGHT));
	float spritewidth = sprite->GetWidth();
	float spriteheight = sprite->GetHeight();

	pos.w += angular_velocity * dt;
	if (pos.w > pi)
		pos.w -= pi;

	if (pos.w < 0.f)
		pos.w += pi;

	oldPos.x = pos.x;
	oldPos.y = pos.y;
	pos.x += vel.x * dt;
	pos.y += vel.y * dt;

	for (std::vector<Ship*>::iterator it = shipList.begin(); it != shipList.end(); ++it)
	{
		Ship* ship = static_cast<Ship*>(*it);

		if (ownerid != ship->GetID())
		{
			if (hasCollided(ship))
			{
				return true;
			}
		}
	}

	if (pos.x < -spritewidth * 0.5)
	{
		//pos.x += screenwidth + spritewidth;
		active = false;
	}
	else if (pos.x > screenwidth + spritewidth * 0.5)
	{
		//pos.x -= screenwidth + spritewidth;
		active = false;
	}

	if (pos.y < -spriteheight * 0.5)
	{
		//pos.y += screenheight + spriteheight;
		active = false;
	}
	else if (pos.y > screenheight + spriteheight * 0.5)
	{
		//pos.y -= screenheight + spriteheight;
		active = false;
	}

	return false;
}

void CProjectile::Render()
{
	sprite->RenderEx(pos.x, pos.y, pos.w);
}

bool CProjectile::hasCollided(Ship* ship)
{
	sprite->GetBoundingBox(pos.x, pos.y, &collidebox);

	return collidebox.Intersect(ship->GetBoundingBox());
}
void CProjectile::UpdateLoc(float x, float y, float w)
{
	pos.x = x;
	pos.y = y;
	pos.w = w;
}

int CProjectile::getOwnerID()
{
	return ownerid;
}

Vector3 CProjectile::getPos() const
{
	return pos;
}

Vector3 CProjectile::getVel() const
{
	return vel;
}

void CProjectile::setVelocityX(float velocity)
{
	vel.x = velocity;
}

void CProjectile::setVelocityY(float velocity)
{
	vel.y = velocity;
}

void CProjectile::setActive(bool active)
{
	this->active = active;
}

bool CProjectile::getActive()
{
	return active;
}