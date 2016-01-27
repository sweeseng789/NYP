#include "GameObject.h"
#include <hge.h>
#include <hgeSprite.h>
#include <hgeFont.h>
#include <math.h>
#include <iostream>

//===== CONSTRUCTOR & DESTRUCTOR =====//
CGameObject::CGameObject()
:	pos(0)
,	angular_velocity(0)
,	vel(0)
,	id(0)
,	collidetimer(0)
,	serverPos(0)
,	clientPos(0)
,	serverVel(0)
,	ratio(1)
{

	/*std::cout << "Creating Ship " << type << " " << locx_ << " " << locy_ << std::endl;
#ifdef INTERPOLATEMOVEMENT
	pos.x = serverPos.x = clientPos.x = locx_;
	pos.y = serverPos.y = clientPos.y = locy_;
#else
	x_ = locx_;
	y_ = locy_;
#endif

	HGE* hge = hgeCreate(HGE_VERSION);

	switch( type )
	{
		case 2:
			textureID = hge->Texture_Load(SHIPTYPE2);
			type = 2;
			break;
		case 3:
			textureID = hge->Texture_Load(SHIPTYPE3);
			type = 3;
			break;
		case 4:
			textureID = hge->Texture_Load(SHIPTYPE4);
			type = 4;
			break;
		default:
			textureID = hge->Texture_Load(SHIPTYPE1);
			type = 1;
			break;
	}

	hge->Release();
	sprite.reset(new hgeSprite(textureID, 0, 0, 64, 64));

	font.reset(new hgeFont("font1.fnt"));
	font->SetScale( 0.5 );
	sprite->SetHotSpot(32,32);*/
}

CGameObject::~CGameObject()
{
	HGE* hge = hgeCreate(HGE_VERSION);
	hge->Texture_Free(textureID);
	hge->Release();
}

//===== SETTER =====//
void CGameObject::Update(float timedelta)
{
	HGE* hge = hgeCreate(HGE_VERSION);
	float pi = 3.141592654f*2;
	float screenwidth = static_cast<float>(hge->System_GetState(HGE_SCREENWIDTH));
	float screenheight = static_cast<float>(hge->System_GetState(HGE_SCREENHEIGHT));
	float spritewidth = sprite->GetWidth();
	float spriteheight = sprite->GetHeight();

	//Server Pos Update
	serverPos.w += angular_velocity * timedelta;
	if (serverPos.w > pi)
		serverPos.w -= pi;

	if (serverPos.w < 0.0f)
		serverPos.w += pi;

	//Client Pos Update
	clientPos.w += angular_velocity * timedelta;
	if (clientPos.w > pi)
		clientPos.w -= pi;

	if (clientPos.w < 0.0f)
		clientPos.w += pi;

	//Angular Pos Update
	pos.w = ratio * serverPos.w + (1 - ratio) * clientPos.w;
	if (pos.w > pi)
		pos.w -= pi;

	if (pos.w < 0.0f)
		pos.w += pi;

	// store old coords
	oldPos = pos;

	// Lab 7 Task 2 : In order to change to interpolation-based, comment these out
#ifndef INTERPOLATEMOVEMENT
	x_ += velocity_x_ * timedelta;
	y_ += velocity_y_ * timedelta;
#endif

	// Lab 7 Task 2 : Add new motion changes for Interpolation
#ifdef INTERPOLATEMOVEMENT
	//Server Wraparound Update
	serverPos.x += serverVel.x * timedelta;
	serverPos.y += serverVel.y * timedelta;

	if (serverPos.x < -spritewidth / 2)
	{
		serverPos.x += screenwidth + spritewidth;
	}
	else if (serverPos.x > screenwidth + spritewidth / 2)
	{
		serverPos.x -= screenwidth + spritewidth;
	}

	if (serverPos.y < -spriteheight / 2)
	{
		serverPos.y += screenheight + spriteheight;
	}
	else if (serverPos.y > screenheight + spriteheight / 2)
	{
		serverPos.y -= screenheight + spriteheight;
	}
	
	//Clent Wraparound Update
	clientPos.x += vel.x * timedelta;
	clientPos.y += vel.y * timedelta;

	if (clientPos.x < -spritewidth / 2)
	{
		clientPos.x += screenwidth + spritewidth;
	}
	else if (clientPos.x > screenwidth + spritewidth / 2)
	{
		clientPos.x -= screenwidth + spritewidth;
	}

	if (clientPos.y < -spriteheight / 2)
	{
		clientPos.y += screenheight + spriteheight;
	}
	else if (clientPos.y > screenheight + spriteheight / 2)
	{
		clientPos.y -= screenheight + spriteheight;
	}

	if ( (serverPos.x < -spritewidth/2 && clientPos.x > screenwidth + spritewidth/2) || (serverPos.x > screenwidth + spritewidth/2 && clientPos.x < -spritewidth/2 ) )
	{
		pos.x = serverPos.x;
	}
	else
	{
		pos.x = ratio * serverPos.x + (1 - ratio) * clientPos.x;
	}

	if ( (serverPos.y < -spriteheight/2 && clientPos.y > screenheight + spriteheight/2) || (serverPos.y > screenheight + spriteheight/2 && clientPos.y < -spriteheight/2 ) )
	{
		pos.y = serverPos.y;
	}
	else
	{
		pos.y = ratio * serverPos.y + (1 - ratio) * clientPos.y;
	}

	if (ratio < 1)
	{
		// interpolating ratio step
		ratio += timedelta *4;
		if (ratio > 1)
			ratio = 1;
	}
#endif

	if (pos.x < -spritewidth / 2)
	{
		pos.x += screenwidth + spritewidth;
	}
	else if (pos.x > screenwidth + spritewidth / 2)
	{
		pos.x -= screenwidth + spritewidth;
	}

	if (pos.y < -spriteheight / 2)
	{
		pos.y += screenheight + spriteheight;
	}
	else if (pos.y > screenheight + spriteheight / 2)
	{
		pos.y -= screenheight + spriteheight;
	}
}

void CGameObject::Accelerate(float acceleration, float timedelta)
{
	// Lab 7 Task 2 : Changes for interpolation
#ifdef INTERPOLATEMOVEMENT
	serverVel.x += acceleration * cosf(pos.w) * timedelta;
	serverVel.y += acceleration * sinf(pos.w) * timedelta;
#else
	velocity_x_ += acceleration * cosf(w_) * timedelta;
	velocity_y_ += acceleration * sinf(w_) * timedelta;
#endif
}

void CGameObject::DoInterpolateUpdate()
{
#ifdef INTERPOLATEMOVEMENT
	clientPos = pos;
	vel.x = serverVel.x;
	vel.y = serverVel.y;
	ratio = 0;
#else
	std::cout "DoInterpolateUpdate() is not working" << std::endl;
#endif
}

void CGameObject::SetName(const char * text)
{
	this->text.clear();
	this->text = text;
}

void CGameObject::SetAngularVelocity(float angular_velocity)
{
	this->angular_velocity = angular_velocity;
}

void CGameObject::SetPreviousLocation()
{
	pos.x = oldPos.x;
	pos.y = oldPos.y;
}

void CGameObject::setID(int id)
{
	this->id = id;
}

void CGameObject::setLocation(float x, float y, float w)
{
	pos.x = x;
	pos.y = y;
	pos.w = w;
}

void CGameObject::setPosX(float x)
{
	pos.x = x;
}

void CGameObject::setPosY(float y)
{
	pos.y = y;
}

void CGameObject::SetVelocityX(float velocity)
{
	vel.x = velocity;
}

void CGameObject::SetVelocityY(float velocity)
{
	vel.y = velocity;
}

void CGameObject::SetServerVelocityX(float velocity)
{
#ifdef INTERPOLATEMOVEMENT
	serverVel.x = velocity;
#else
	std::cout << "SetServerVelocityX is not working" << std::endl;
#endif
}

void CGameObject::SetServerVelocityY(float velocity)
{
#ifdef INTERPOLATEMOVEMENT
	serverVel.y = velocity;
#else
	std::cout << "SetServerVelocityY is not working" << std::endl;
#endif
}

void CGameObject::SetServerLocation(float x, float y, float w)
{
#ifdef INTERPOLATEMOVEMENT
	serverPos.x = x;
	serverPos.y = y;
	serverPos.w = w;
#else
	std::cout << "SetServerLocation is not working" << std::endl;
#endif
}


//===== GETTER =====//
void CGameObject::Render()
{
	sprite->RenderEx(pos.x, pos.y, pos.w);

	font->printf(pos.x+5, pos.y+5, HGETEXT_LEFT, "%s", text.c_str());
}

hgeRect* CGameObject::GetBoundingBox()
{
	sprite->GetBoundingBox(pos.x, pos.y, &collidebox);

	return &collidebox;
}

int CGameObject::GetID()
{
	return id;
}

int CGameObject::GetType()
{
	return type;
}

float CGameObject::GetAngularVelocity()
{
	return angular_velocity;
}

bool CGameObject::CanCollide(unsigned int timer)
{
	if (timer - collidetimer > 2000)
	{
		collidetimer = timer;

		return true;
	}

	return false;
}

bool CGameObject::HasCollided(CGameObject *go )
{
	sprite->GetBoundingBox( pos.x, pos.y, &collidebox);

	return collidebox.Intersect( go->GetBoundingBox() );
}

Vector3 CGameObject::getPos()
{
	return pos;
}

Vector3 CGameObject::getVel()
{
	return vel;
}

Vector3 CGameObject::getClientPos()
{
	return clientPos;
}

Vector3 CGameObject::getServerPos()
{
	return serverPos;
}

Vector3 CGameObject::getServerVel()
{
#ifdef INTERPOLATEMOVEMENT
	return serverVel;
#else
	std::cout "getServerVel() is not working" << std::endl;
	return Vector3(0, 0, 0);
#endif
}
