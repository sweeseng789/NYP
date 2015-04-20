/******************************************************************************/
/*!
\file	Guard.h
\author Princeton Chew
\par	email: 141991A@mymail.nyp.edu.sg
\brief
Guard Class
*/
/******************************************************************************/
#pragma once
#include "Character.h"
#include "timer.h"
#include "Application.h"
#include "Mtx44.h"

/******************************************************************************/
/*!
	Class CGuard
\brief
Defines the variables and functions required for the guard

*/
/******************************************************************************/
class CGuard : public CCharacter
{
public:
	CGuard(void);	//Constructor
	~CGuard(void);	//Destructor
	void SetData(Vector3 pos, Vector3 targ); //Sets guard position and target
	Vector3 getGuardPosition(); //Get guard position
	void getDifference(Vector3 camerapos);	//Get guard difference from player
	float getDerivedAngle();	//Get angle for guard to look at player
	int getState();	//Get state
	void guardUpdate(float dt,Vector3 camerapos);	//Update guard
	void setState(int a);	//Set guard's state
	bool getCatchPlayerState();

private:
	Vector3 guardPos;
	Vector3 guardTarget;
	Vector3 guardView;
	Vector3 guardDifference;
	Vector3 initialPos;

	float derivedAngle;
	int state;
	bool CatchPlayerState;
 //! States.
/*! Defines States of guard */
	enum States
	{
		S_IDLE,
		S_ALERT,
		S_MAX,
	};

	StopWatch Timer;
};

