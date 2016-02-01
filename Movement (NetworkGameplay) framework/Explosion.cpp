#include "Explosion.h"
#include <hge.h>
#include <hgeSprite.h>
#include <hgeFont.h>
#include <math.h>
#include "ship.h"
#include "Laser.h"
#include <iostream>

#define SHIPTYPE1 "ship1.png"
#define SHIPTYPE2 "ship2.png"
#define SHIPTYPE3 "ship3.png"
#define SHIPTYPE4 "ship4.png"

/**
* Ship Constructor
*
* It will load the file specified into a sprite and intialise its
* hotspot to the center. Assumes a sprite size of 64*64 and a
* screen size of 800*600
*
* @param filename Name of the graphics file used to represent the ship
*/

Explode::Explode(std::string type, float locx_, float locy_, float w)
	: w_(0)
	, angular_velocity(0)
	, velocity_x_(0)
	, velocity_y_(0)
	, id(0)
	, collidetimer(0)
#ifdef INTERPOLATEMOVEMENT
	, server_w_(0)
	, client_w_(0)
	, server_velx_(0)
	, server_vely_(0)
	, ratio_(1)
#endif
{

	std::cout << "Creating Ship " << type << " " << locx_ << " " << locy_ << std::endl;
#ifdef INTERPOLATEMOVEMENT
	x_ = server_x_ = client_x_ = locx_;
	y_ = server_y_ = client_y_ = locy_;
	angular_velocity = w / 100;
#else
	x_ = locx_;
	y_ = locy_;
#endif

	HGE* hge = hgeCreate(HGE_VERSION);

	tex_ = hge->Texture_Load("Explosion.png");
	hge->Release();
	sprite_.reset(new hgeSprite(tex_, 0, 0, 100, 100));

	font_.reset(new hgeFont("font1.fnt"));
	font_->SetScale(0.5);
	sprite_->SetHotSpot(10, 10);
	active = true;
	explodeTime = 8.0f;
}


/**
* Ship Destructor
*
* Frees the internal texture used by the sprite
*/
Explode::~Explode()
{
	HGE* hge = hgeCreate(HGE_VERSION);
	hge->Texture_Free(tex_);
	hge->Release();
}


/**
* Update cycle
*
* Increments the angular and x,y position of the ship based on how
* much time that has passed since the last frame. It also wraps the
* ship around the screen so it never goes out of screen.
*
* @param timedelta The time that has passed since the last frame in milliseconds
*/

void Explode::Update(float timedelta)
{
	if (explodeTime > 0.f)
	{
		explodeTime -= timedelta;
	}
}


/**
* Render Cycle
*
* Renders the ship to the screen. Must be called between a
* Gfx_BeginScene an Gfx_EndScene, otherwise bad things will
* happen.
*/

void Explode::Render()
{

	sprite_->RenderEx(x_, y_, w_);

	font_->printf(x_ + 5, y_ + 5, HGETEXT_LEFT, "%s",
		mytext_.c_str());
}

/**
* Accelerates a ship by the given acceleration (i.e. increases
* the ships velocity in the direction it is pointing in)
*
* @param acceleration How much to accelerate by in px/s^2
* @param timedelta Time passed since last frame
*/

void Explode::Accelerate(float acceleration, float timedelta)
{
	// Lab 7 Task 2 : Changes for interpolation
#ifdef INTERPOLATEMOVEMENT
	server_velx_ += acceleration * cosf(w_) * timedelta;
	server_vely_ += acceleration * sinf(w_) * timedelta;
#else
	velocity_x_ += acceleration * cosf(w_) * timedelta;
	velocity_y_ += acceleration * sinf(w_) * timedelta;
#endif
}

void Explode::SetName(const char * text)
{
	mytext_.clear();
	mytext_ = text;
}

hgeRect* Explode::GetBoundingBox()
{
	sprite_->GetBoundingBox(x_, y_, &collidebox);

	return &collidebox;
}


bool Explode::HasCollided(Ship *ship)
{
	sprite_->GetBoundingBox(x_, y_, &collidebox);

	return collidebox.Intersect(ship->GetBoundingBox());
}

bool Explode::hasCollided(Laser* laser)
{
	sprite_->GetBoundingBox(x_, y_, &collidebox);
	return collidebox.Intersect(laser->GetBoundingBox());
}

bool Explode::Update_Laser(std::vector<Laser*> &laserList)
{
	for (std::vector<Laser*>::iterator it = laserList.begin(); it != laserList.end(); ++it)
	{
		Laser* laser = static_cast<Laser*>(*it);
		if (hasCollided(laser))
		{
			delete *it;
			laserList.erase(it);
			return true;
			break;
		}
	}
	return false;
}