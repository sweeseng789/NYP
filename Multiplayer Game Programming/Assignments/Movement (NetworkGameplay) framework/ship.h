#ifndef _SHIP_H_
#define _SHIP_H_

#include <hge.h>
#include <hgerect.h>
#include <memory>
#include <string>
#include "Vector3.h"

class hgeSprite;
class hgeFont;

#define INTERPOLATEMOVEMENT 

/**
* The Ship class represents a single spaceship floating in space. It obeys
* 2D physics in terms of displacement, velocity and acceleration, as well
* as angular position and displacement. The size of the current art is
* 128*128 pixels
*/

class Ship
{
public:
	//===== CONSTRUCTOR & DESTRUCTOR =====//
	Ship(int type, float x, float y);
	~Ship();

	//===== SETTER =====//
	void Update(float timedelta);
	void Accelerate(float acceleration, float timedelta);
	void DoInterpolateUpdate();
	void SetName(const char * text);
	void SetAngularVelocity(float av); // { angular_velocity = av; }
	void SetPreviousLocation();
	void setID(int newid);// { id = newid; }

	void setLocation(float x, float y, float w);
	void setPosX(float x);
	void setPosY(float y);
	void SetVelocityX(float velocity);
	void SetVelocityY(float velocity);
	void SetServerVelocityX(float velocity);
	void SetServerVelocityY(float velocity);
	void SetServerLocation(float x, float y, float w);

	//===== GETTER =====//
	void Render();
	hgeRect* GetBoundingBox();
	int GetID();
	int GetType();
	float GetAngularVelocity();
	bool CanCollide(unsigned int timer);
	bool HasCollided(Ship *ship);
	Vector3 getPos();
	Vector3 getVel();
	Vector3 getClientPos();
	Vector3 getServerPos();
	Vector3 getServerVel();

	// Lab Task 2 : add new member functions here

protected:
	//Int
	int id;
	int type;
	int collidetimer;

	//Float
	float angular_velocity;
	float ratio;

	//String
	std::string text;

	//Class Variables 
	HTEXTURE textureID; //Handle to the sprite's texture
	std::auto_ptr<hgeSprite> sprite; //!< The sprite used to display the ship
	std::auto_ptr<hgeFont> font;
	hgeRect collidebox;
	Vector3 pos; //x & y = pos of ship, w = angular position of ship
	Vector3 vel; //The resolved velocity of the ship
	Vector3 oldPos; // for reset back to previous location if collision detected
	Vector3 serverPos;
	Vector3 serverVel;
	Vector3 clientPos;

	// Lab Task 2 : add for interpolation
};

#endif