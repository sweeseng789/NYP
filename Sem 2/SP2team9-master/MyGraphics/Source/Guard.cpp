/******************************************************************************/
/*!
\file	Guard.cpp
\author Princeton Chew
\par	email: 141991A@mymail.nyp.edu.sg
\brief
Guard Class
*/
/******************************************************************************/
#include "Guard.h"

/******************************************************************************/
/*!
\brief
Default constructor for class
*/
/******************************************************************************/
CGuard::CGuard(void)
{
	guardPos.SetZero();
	guardTarget.SetZero();
	guardView.SetZero();
	guardDifference.SetZero();
	initialPos.SetZero();

	derivedAngle = 0.f;
	state = 0;
	CatchPlayerState = false;
}

/******************************************************************************/
/*!
\brief
Default destructor for class
*/
/******************************************************************************/
CGuard::~CGuard(void)
{
}

/******************************************************************************/
/*!
\brief
Set guard's position and target

\param pos - Vector3 position of guard
\param targ - Vector3 target of guard
*/
/******************************************************************************/
void CGuard::SetData(Vector3 pos, Vector3 targ)
{
	guardPos = pos;
	initialPos = pos;
	guardTarget = targ;
	guardView = (guardTarget - guardPos).Normalized();
}
/******************************************************************************/
/*!
\brief
Updates the guard based on delta time and camera's position

\param dt - delta time
\param camerapos - Vector3 position of camera
*/
/******************************************************************************/
void CGuard::guardUpdate(float dt, Vector3 camerapos)
{
	//==================================GUARD=====================//
	//Rotation following player
	derivedAngle = Math::RadianToDegree(acos(guardView.Dot(guardDifference) / (guardView.Length() * guardDifference.Length())));
	if(guardView.Cross(guardDifference).y > 1)
	{
		derivedAngle *= 1;
	}
	else
	{
		derivedAngle *= -1;
	}
	//std::cout << derivedAngle << std::endl;

	if(state == S_ALERT)
	{
		//Movement of guard to player
		if ((guardPos - camerapos).Length() > 6)
		{
			guardPos += (guardDifference.Normalized()) * 25 * dt;
			CatchPlayerState = false;
		}
		else
		{
			CatchPlayerState = true;
		}
	}
	if(state == S_IDLE)
	{
		guardPos = initialPos;
	}


	//=====================RESET=================//
	if (Application::IsKeyPressed('R') && CatchPlayerState == true)
	{
		derivedAngle = 0.f;
		state = 0;
		CatchPlayerState = false;
	}
}
/******************************************************************************/
/*!
\brief
Get the difference between guard and camera

\param camerapos - Vector3 position of camera
*/
/******************************************************************************/
void CGuard::getDifference(Vector3 camerapos)
{
	guardDifference = camerapos - guardPos;
}
/******************************************************************************/
/*!
\brief
Get the guard's position

\return Vector3 position of guard
*/
/******************************************************************************/
Vector3 CGuard::getGuardPosition()
{
	return guardPos;
}

/******************************************************************************/
/*!
\brief
Get the derived angle of guard and player

\return Float of derived angle
*/
/******************************************************************************/
float CGuard::getDerivedAngle()
{
	return derivedAngle;
}

/******************************************************************************/
/*!
\brief
Get the state of guard

\return Int of guard's state
*/
/******************************************************************************/
int CGuard::getState()
{
	return state;
}

/******************************************************************************/
/*!
\brief
Set the state of guard

\param a - int of state
*/
/******************************************************************************/
void CGuard::setState(int a)
{
	state = a;
}
/******************************************************************************/
/*!
\brief
Returns the player state (Caught or not)

\param bool of state
*/
/******************************************************************************/
bool CGuard::getCatchPlayerState()
{
	return CatchPlayerState;
}