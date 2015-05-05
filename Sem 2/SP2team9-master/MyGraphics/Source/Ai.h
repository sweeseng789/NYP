/******************************************************************************/
/*!
\file	Ai.h
\author Ong Swee Seng
\par	email: 142128G@mymail.nyp.edu.sg
\brief
Ai Class
*/
/******************************************************************************/
#ifndef AI_H
#define AI_H

#include "Camera.h"
#include <iostream>
#include <vector>
#include "Vector3.h"
#include "timer.h"
/******************************************************************************/
/*!
	Class Ai
\brief
Defines the variables and functions required for the AI

*/
/******************************************************************************/
class Ai : public Camera
{
public:
	Ai();
	~Ai();

	void passInPositionAndTarget(Vector3, Vector3);
	void update(float, Vector3);
	void FindPlayerDistanceDifference(Vector3);
	void FindPlayerDistanceDifferencePasserby(Vector3);

	void SetPasserby(Vector3);

	float getDerivedAngle();
	float getPasserbyAngle();
	float getPasserbyAngle2();
	float getPasserbyAngle3();
	Vector3 getGuardPosition();
	Vector3 getPasserbyPosition();
	Vector3 getPasserby2Position();
	Vector3 getPasserby3Position();
	bool getAlertState();

private:
	Vector3 guardPos;
	Vector3 guardTarget;
	Vector3 guardView;
	Vector3 guardDifference;

	Vector3 PasserbyPos;
	Vector3 PasserbyPos2;
	Vector3 PasserbyPos3;
	Vector3 PasserbyDifference;

	float derivedAngle;
	float PasserbyAngle;
	float PasserbyAngle2;
	float PasserbyAngle3;
	bool guardAlertState;

	bool Passerby1Phase1, Passerby1Phase2, Passerby1Phase3, Passerby1Phase4;

	StopWatch Timer;
};

#endif