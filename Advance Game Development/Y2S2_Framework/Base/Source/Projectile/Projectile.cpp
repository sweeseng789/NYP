#include "Projectile.h"

double CProjectile::DEAFULT_BULLET_TIME = 5;

/********************************************************************************
 Constructor
 ********************************************************************************/
CProjectile::CProjectile(void)
: m_bActive(false)
, thePosition(0, 0, 0)
, theDirection(0, 0, 0)
, speed(0.0f)
, length(0.f)
, type(PROJ_TYPE_DISCRETE)
, timing(DEAFULT_BULLET_TIME)
{
}

/********************************************************************************
 Destructor
 ********************************************************************************/
CProjectile::~CProjectile(void)
{
}

/********************************************************************************
 Update the status of this projectile
 ********************************************************************************/
void CProjectile::Update(const double dt)
{
	if (m_bActive == false)
		return;

	// Update Position
	/*thePosition.Set(	thePosition.x + theDirection.x * speed * dt, 
						thePosition.y + theDirection.y * speed * dt, 
						thePosition.z + theDirection.z * speed * dt);*/

	thePosition += theDirection * speed * dt;
	timing -= dt;
	if (timing <= 0)
	{
		m_bActive = false;
	}
}

/********************************************************************************
 Activate the projectile. true == active, false == inactive
 ********************************************************************************/
void CProjectile::SetActivate(bool m_bActivate)
{
	/*if (m_bActivate == true)
		m_bActive = true;
	else
		m_bActive = false;*/
	this->m_bActive = m_bActivate;
}

/********************************************************************************
 get status of the projectile. true == active, false == inactive
 ********************************************************************************/
bool CProjectile::GetStatus(void)
{
	return m_bActive;
}

/********************************************************************************
 Get the position of the projectile
 ********************************************************************************/
Vector3 CProjectile::GetPosition(void)
{
	return thePosition;
}

/********************************************************************************
 Get the direction of the projectile
 ********************************************************************************/
Vector3 CProjectile::GetDirection(void)
{
	return theDirection;
}

/********************************************************************************
 Set the position of the projectile
 ********************************************************************************/
void CProjectile::SetPosition(Vector3 theNewPosition)
{
	thePosition.Set( theNewPosition.x, theNewPosition.y, theNewPosition.z);
}

/********************************************************************************
 Set the direction of the projectile
 ********************************************************************************/
void CProjectile::SetDirection(Vector3 theNewDirection)
{
	theDirection.Set( theNewDirection.x, theNewDirection.y, theNewDirection.z);
}

/********************************************************************************
 Set speed
 ********************************************************************************/
void CProjectile::SetSpeed(const float speed)
{
	this->speed = speed;
}

/********************************************************************************
Get length of ray projectile
********************************************************************************/
float CProjectile::getLength()
{
	return length;
}

/********************************************************************************
set length of ray projectile
********************************************************************************/
void CProjectile::setLength(const float length)
{
	this->length = length;
}

/********************************************************************************
Get projectile type
********************************************************************************/
int CProjectile::getType()
{
	return type;
}

/********************************************************************************
Get the projectile type
********************************************************************************/
void CProjectile::setType(const int type)
{
	this->type = type;
}

void CProjectile::resetTimer()
{
	this->timing = DEAFULT_BULLET_TIME;
}
