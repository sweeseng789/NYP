#pragma once

#include "Vector3.h"
#include <stdio.h>

class CProjectile
{
public:
	CProjectile(void);
	~CProjectile(void);

	enum PROJECTILE_TYPE
	{
		PROJ_TYPE_DISCRETE,
		PROJ_TYPE_RAY,
		NUM_PROJ_TYPE,
	};

	static double DEAFULT_BULLET_TIME;

	// Update the status of this projectile
	void Update(const double dt);
	// Activate the projectile. true == active, false == inactive
	void SetActivate(bool m_bActivate);
	// get status of the projectile. true == active, false == inactive
	bool GetStatus(void);
	// Get the position of the projectile
	Vector3 GetPosition();
	// Get the direction of the projectile
	Vector3 GetDirection(void);
	//Get the length of the projectile
	float getLength();
	//Get the projectile type
	int getType();
	// Set the position of the projectile
	void SetPosition(Vector3 theNewPosition);
	// Set the direction of the projectile
	void SetDirection(Vector3 theNewDirection);
	// Set speed
	void SetSpeed(const float speed);
	//Set length of ray projectile
	void setLength(const float length);
	//Projectile TYpe
	void setType(const int type);

	void resetTimer();
private:
	// Boolean flag to indicate if this projectile is active. If not active, then do not compute/update
	bool m_bActive;
	// The position of the projectile
	Vector3 thePosition;
	// The direction of the projectile
	Vector3 theDirection;
	// Speed
	float speed;
	//Time
	double timing;
	//Length of ray projectile
	float length;
	//Type
	int type;
};
