#include "Ai.h"
#include "Application.h"
#include "Mtx44.h"
/******************************************************************************/
/*!
\file	Character.cpp
\author Princeton Chew
\par	email: 141991A@mymail.nyp.edu.sg
\brief
Character Class
*/
/******************************************************************************/

/******************************************************************************/
/*!
\brief
Default constructor for AI
*/
/******************************************************************************/
Ai::Ai()
{
	derivedAngle = 0;
	guardAlertState = false;
	PasserbyAngle = 180;
	PasserbyAngle2 = 0;
	PasserbyAngle3 = 90;
	Passerby1Phase1 = Passerby1Phase2 = Passerby1Phase3 = Passerby1Phase4 = false;
}
/******************************************************************************/
/*!
\brief
Default destructor for class
*/
/******************************************************************************/
Ai::~Ai()
{
}
/******************************************************************************/
/*!
\brief
Sets AI Position and target

\param pos - Vector3 position of AI
\param targ - Vector3 target of AI
*/
/******************************************************************************/
void Ai::passInPositionAndTarget(Vector3 pos, Vector3 target)
{
	guardPos = pos;
	guardTarget = target;
	guardView = (guardTarget - guardPos).Normalized();
}
/******************************************************************************/
/*!
\brief
 Sets the update status for the ai. Telling it what to do every frame

 \param derivedAngle = angle difference between player and ai
*/
/******************************************************************************/
void Ai::update(float dt, Vector3 camera)
{
	//==================================GUARD=====================//
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
	
	static float elapsedTime1 = 0, elapsedTime2 = 0;
	elapsedTime1 = fmod(Timer.getElapsedTime(), 1);
	if (elapsedTime2 <= 1)
	{
		elapsedTime2 += elapsedTime1;
	}
	else
	{
		elapsedTime2 += 0;
	}

	if (Application::IsKeyPressed('0') && elapsedTime2 >= 1)
	{
		if (guardAlertState == false)
		{
			guardAlertState = true;
		}
		else if (guardAlertState == true)
		{
			guardAlertState = false;
		}
		elapsedTime2 -= 1;
	}

	if (guardAlertState == true)
	{
		//moves guard to player
		if (Application::IsKeyPressed('8'))
		{
			guardPos += (guardDifference.Normalized()) * 10 * dt;
		}
	}


	//========================PASSERBY 1==========================//
	if (PasserbyDifference.Length() > 6)
	{
		if (PasserbyPos.z < 31.5 && PasserbyPos.x == 0 && PasserbyAngle ==180)
		{
			PasserbyPos.z += 10 * dt;
			if (PasserbyPos.z >= 31.5)
			{
				PasserbyPos.z = 31.5;
			}

		}
		if (PasserbyPos.z == 31.5 && PasserbyAngle < 270 && PasserbyPos.x == 0)
		{
			PasserbyAngle += 100 * dt;
			if (PasserbyAngle >= 270)
			{
				PasserbyAngle = 270;
			}
		}

		if (PasserbyAngle == 270 && PasserbyPos.z == 31.5 && PasserbyPos.x < 48.5)
		{
			PasserbyPos.x += 10 * dt;
			if (PasserbyPos.x >= 48.5)
			{
				PasserbyPos.x = 48.5;
			}
		}

		if (PasserbyPos.x == 48.5 && PasserbyPos.z == 31.5 && PasserbyAngle > 180)
		{
			PasserbyAngle -= 100 * dt;
			if (PasserbyAngle < 180)
			{
				PasserbyAngle = 180;
			}
		}
	
		if (PasserbyAngle == 180 && PasserbyPos.z  < 55 && PasserbyPos.x == 48.5)
		{
			PasserbyPos.z += 10 * dt;
			if (PasserbyPos.z > 55)
			{
				PasserbyPos.z = 55;
			}
		}

		if (PasserbyAngle > 90 && PasserbyPos.z == 55 && PasserbyPos.x == 48.5)
		{
			PasserbyAngle -= 100 * dt;
			if (PasserbyAngle <= 90)
			{
				PasserbyAngle = 90;
			}
		}

		if (PasserbyAngle == 90 && PasserbyPos.x > -33 && PasserbyPos.z == 55)
		{
			PasserbyPos.x -= 10 * dt;
			if (PasserbyPos.x < -33)
			{
				PasserbyPos.x = -33;
			}
		}

		if (PasserbyAngle < 360 && PasserbyPos.x == -33 && PasserbyPos.z == 55)
		{
			PasserbyAngle += 100 * dt;
			if (PasserbyAngle > 360)
			{
				PasserbyAngle = 360;
			}
		}

		if (PasserbyAngle == 360 && PasserbyPos.x == -33 && PasserbyPos.z > 31.5)
		{
			PasserbyPos.z -= 10 * dt;
			if (PasserbyPos.z < 31.5)
			{
				PasserbyPos.z = 31.5;
			}
		}

		if (PasserbyAngle > 270 && PasserbyPos.x == -33 && PasserbyPos.z == 31.5)
		{
			PasserbyAngle -= 100 * dt;
			if (PasserbyAngle < 270)
			{
				PasserbyAngle = 270;
			}
		}
	}

	//========================PASSERBY 2==========================//
	if (PasserbyPos2.z > -33 && PasserbyPos2.x == 0 && PasserbyAngle2 == 0)
	{
		PasserbyPos2.z -+ 10 * dt;
		if (PasserbyPos2.z <= 33)
		{
			PasserbyPos2.z = -33;
		}
	}

	if (PasserbyPos2.z == -33 && PasserbyPos2.x == 0 && PasserbyAngle2 > -90)
	{
		PasserbyAngle2 -= 100 * dt;
		if (PasserbyAngle2 <= -90)
		{
			PasserbyAngle2 = -90;
		}
	}

	if (PasserbyPos2.z == -33 && PasserbyPos2.x < 48.5 && PasserbyAngle2 == -90)
	{
		PasserbyPos2.x += 10 * dt;
		if (PasserbyPos2.x >= 48.5)
		{
			PasserbyPos2.x = 48.5;
		}
	}

	if (PasserbyPos2.z == -33 && PasserbyPos2.x == 48.5 && PasserbyAngle2 < 0)
	{
		PasserbyAngle2 += 100 * dt;
		if (PasserbyAngle2 >= 0)
		{
			PasserbyAngle2 = 0;
		}
	}

	if (PasserbyPos2.z > -88 && PasserbyPos2.x == 48.5 && PasserbyAngle2 == 0)
	{
		PasserbyPos2.z -= 10 * dt;
		if (PasserbyPos2.z <= -88)
		{
			PasserbyPos2.z = -88;
		}
	}

	if (PasserbyPos2.z == -88 && PasserbyPos2.x == 48.5 && PasserbyAngle2 < 90)
	{
		PasserbyAngle2 += 100 * dt;
		if (PasserbyAngle2 >= 90)
		{
			PasserbyAngle2 = 90;
		}
	}
	
	if (PasserbyPos2.z == -88 && PasserbyPos2.x > -35 && PasserbyAngle2 == 90)
	{
		PasserbyPos2.x -= 10 * dt;
		if (PasserbyPos2.x <= -35)
		{
			PasserbyPos2.x = -35;
		}
	}

	if (PasserbyPos2.z == -88 && PasserbyPos2.x == -35 && PasserbyAngle2 < 180)
	{
		PasserbyAngle2 += 100 * dt;
		if (PasserbyAngle2 >= 180)
		{
			PasserbyAngle2 = 180;
		}
	}

	if (PasserbyPos2.z < -33 && PasserbyPos2.x == -35 && PasserbyAngle2 == 180)
	{
		PasserbyPos2.z += 10 * dt;
		if (PasserbyPos2.z >= -33)
		{
			PasserbyPos2.z = -33;
		}
	}

	if (PasserbyPos2.z == -33 && PasserbyPos2.x == -35 && PasserbyAngle2 > -90)
	{
		PasserbyAngle2 -= 100 * dt;
		if (PasserbyAngle2 <= -90)
		{
			PasserbyAngle2 = -90;
		}
	}

	//========================PASSERBY 3==========================//
	if (PasserbyPos3.x > -34 && PasserbyPos3.z == 31 && PasserbyPos3.y == 0 && PasserbyAngle3 == 90)
	{
		PasserbyPos3.x -= 10 * dt;
		if (PasserbyPos3.x <= -34)
		{
			PasserbyPos3.x = -34;
		}
	}

	if (PasserbyPos3.x == -34 && PasserbyPos3.z == 31 && PasserbyPos3.y == 0 && PasserbyAngle3 < 180)
	{
		PasserbyAngle3 += 100 * dt;
		if (PasserbyAngle3 >= 180)
		{
			PasserbyAngle3 = 180;
		}
	}

	if (PasserbyPos3.x == -34 && PasserbyPos3.z < 70.7 && PasserbyPos3.y == 0 && PasserbyAngle3 == 180)
	{
		PasserbyPos3.z += 10 * dt;
		if (PasserbyPos3.z >= 70.5)
		{
			PasserbyPos3.z = 70.5;
		}
	}

	if (PasserbyPos3.x == -34 && PasserbyPos3.z == 70.5 && PasserbyPos3.y == 0 && PasserbyAngle3 < 270)
	{
		PasserbyAngle3 += 100 * dt;
		if (PasserbyAngle3 >= 270)
		{
			PasserbyAngle3 = 270;
		}
	}

	if (PasserbyPos3.x < -31 && PasserbyPos3.z == 70.5 && PasserbyPos3.y == 0 && PasserbyAngle3 == 270)
	{
		PasserbyPos3.x += 10 * dt;
		if (PasserbyPos3.x >= -31)
		{
			PasserbyPos3.x = -31;
		}
	}


	Vector3 direction = Vector3(32,20.5,0) - Vector3(-31,0,0);
	//std::cout << direction << std::endl;
	direction.Normalized();
	if (PasserbyPos3.x < 32 && PasserbyPos3.z == 70.5 && PasserbyPos3.y < 20.5 && PasserbyAngle3 == 270)
	{
		PasserbyPos3 += direction * (0.5 * dt);
	}

	if (PasserbyPos3.x > 27 && PasserbyPos3.z == 70.5 && PasserbyPos3.y > 20.5 && PasserbyAngle3 < 360) //Setting values
	{
		PasserbyAngle3 += 100 * dt;
		if (PasserbyAngle3 >= 360)
		{
			PasserbyAngle3 = 360;
		}
	}

	if (PasserbyPos3.x > 28 && PasserbyPos3.z > -93 && PasserbyPos3.y > 20.5 && PasserbyAngle3 ==360) //Setting values
	{
		PasserbyPos3.z -= 10 * dt;
		if (PasserbyPos3.z <= -93)
		{
			PasserbyPos3.z = -93;
		}
	}

	if (PasserbyPos3.x > 28 && PasserbyPos3.z == -93 && PasserbyPos3.y > 20.5 && PasserbyAngle3 < 450)
	{
		PasserbyAngle3 += 100 * dt;
		if (PasserbyAngle3 >= 450)
		{
			PasserbyAngle3 = 450;
		}
	}

	if (PasserbyPos3.x > 20 && PasserbyPos3.z == -93 && PasserbyPos3.y > 20.5 && PasserbyAngle3 == 450)
	{
		PasserbyPos3.x -= 10 * dt;
		if (PasserbyPos3.x <= 20)
		{
			PasserbyPos3.x = 20;
		}
	}

	if (PasserbyPos3.x == 20 && PasserbyPos3.z == -93 && PasserbyPos3.y > 20.5 && PasserbyAngle3 < 540)
	{
		PasserbyAngle3 += 100 * dt;
		if (PasserbyAngle3 >= 540)
		{
			PasserbyAngle3 = 540;
		}
	}

	if (PasserbyPos3.x == 20 && PasserbyPos3.z < 57 && PasserbyPos3.y > 20.5 && PasserbyAngle3 == 540)
	{
		PasserbyPos3.z += 10 * dt;
		if (PasserbyPos3.z >= 57)
		{
			PasserbyPos3.z = 57;
		}
	}

	if (PasserbyPos3.x == 20 && PasserbyPos3.z == 57 && PasserbyPos3.y > 20.5 && PasserbyAngle3 < 630)
	{
		PasserbyAngle3 += 100 * dt;
		if (PasserbyAngle3 >= 630)
		{
			PasserbyAngle3 = 630;
		}
	}

	if (PasserbyPos3.x < 40 && PasserbyPos3.z == 57 && PasserbyPos3.y > 20.5 && PasserbyAngle3 == 630)
	{
		PasserbyPos3.x += 10 * dt;
		if (PasserbyPos3.x >= 40)
		{
			PasserbyPos3.x = 40;
		}
	}

	if (PasserbyPos3.x == 40 && PasserbyPos3.z == 57 && PasserbyPos3.y > 20.5 && PasserbyAngle3 > 540)
	{
		PasserbyAngle3 -= 100 * dt;
		if (PasserbyAngle3 <= 540)
		{
			PasserbyAngle3 = 180;
		}
	}

	if (PasserbyPos3.x == 40 && PasserbyPos3.z < 84 && PasserbyPos3.y > 20.5 && PasserbyAngle3 == 180)
	{
		PasserbyPos3.z += 10 * dt;
		if (PasserbyPos3.z >= 84)
		{
			PasserbyPos3.z = 84;
		}
	}

	if (PasserbyPos3.x == 40 && PasserbyPos3.z == 84 && PasserbyPos3.y > 20.5 && PasserbyAngle3 > 90)
	{
		PasserbyAngle3 -= 100 * dt;
		if (PasserbyAngle3 <= 90)
		{
			PasserbyAngle3 = 90;
		}
	}

	if (PasserbyPos3.x > 26 && PasserbyPos3.z == 84 && PasserbyPos3.y > 20.5 && PasserbyAngle3 == 90)
	{
		PasserbyPos3.x -= 10 * dt;
		if (PasserbyPos3.x <= 26)
		{
			PasserbyPos3.x = 26;
			Passerby1Phase1 = true;
		}
	}

	if (PasserbyPos3.x > -31 && Passerby1Phase1 == true && PasserbyPos3.z == 84 && PasserbyPos3.y > 0 && PasserbyAngle3 == 90)
	{
		PasserbyPos3 -= direction * (0.5 * dt);
	}

	if (PasserbyPos3.x < -31 && Passerby1Phase1 == true && PasserbyPos3.z == 84 && PasserbyPos3.y > 0 && PasserbyAngle3 == 90)
	{
		PasserbyPos3.x = -31;
		PasserbyPos3.y = 0;
		Passerby1Phase1 = false;
	}

	if (PasserbyPos3.x > -40 && PasserbyPos3.z == 84 && PasserbyPos3.y == 0 && PasserbyAngle3 == 90)
	{
		PasserbyPos3.x -= 10 * dt;
		if (PasserbyPos3.x <= -40)
		{
			PasserbyPos3.x =  -40;
		}
	}

	if (PasserbyPos3.x == -40 && PasserbyPos3.z == 84 && PasserbyPos3.y == 0 && PasserbyAngle3 > 0)
	{
		PasserbyAngle3 -= 100 * dt;
		if (PasserbyAngle3 <= 0)
		{
			PasserbyAngle3 = 0;
		}
	}

	if (PasserbyPos3.x == -40 && PasserbyPos3.z > 37.5 && PasserbyPos3.y == 0 && PasserbyAngle3 == 0)
	{
		PasserbyPos3.z -= 10 * dt;
		if (PasserbyPos3.z <= 37.5)
		{
			PasserbyPos3.z = 37.5;
		}
	}

	if (PasserbyPos3.x == -40 && PasserbyPos3.z == 37.5 && PasserbyPos3.y == 0 && PasserbyAngle3 > -90)
	{
		PasserbyAngle3 -= 100 * dt;
		if (PasserbyAngle3 <= -90)
		{
			PasserbyAngle3 = -90;
		}
	}

	if (PasserbyPos3.x < 20.5 && PasserbyPos3.z == 37.5 && PasserbyPos3.y == 0 && PasserbyAngle3 == -90)
	{
		PasserbyPos3.x += 10 * dt;
		if (PasserbyAngle3 >= 20.5)
		{
			PasserbyAngle3 = 20.5;
		}
	}

	if (PasserbyPos3.x > 20.5 && PasserbyPos3.z == 37.5 && PasserbyPos3.y == 0 && PasserbyAngle3 < 0)
	{
		PasserbyAngle3 += 100 * dt;
		if (PasserbyAngle3 >= 0)
		{
			PasserbyAngle3 = 0;
			PasserbyPos3.x = 20.5;
		}
	}

	if (PasserbyPos3.x == 20.5 && PasserbyPos3.z > 31 && PasserbyPos3.y == 0 && PasserbyAngle3 == 0)
	{
		PasserbyPos3.z -= 10 * dt;
		if (PasserbyPos3.z <= 31)
		{
			PasserbyPos3.z = 31;
		}
	}

	if (PasserbyPos3.x == 20.5 && PasserbyPos3.z == 31 && PasserbyPos3.y == 0 && PasserbyAngle3 < 90)
	{
		PasserbyAngle3 += 100 * dt;
		if (PasserbyAngle3 >= 90)
		{
			PasserbyAngle3 = 90;
		}
	}
}
 /******************************************************************************/
/*!
\brief
Finds the distance between player and Guard
*/
/******************************************************************************/
void Ai::FindPlayerDistanceDifference(Vector3 cameraPosition)
{
	guardDifference = cameraPosition - guardPos;
}
/******************************************************************************/
/*!
\brief
Finds the distance between ai and customer
*/
/******************************************************************************/
void Ai::FindPlayerDistanceDifferencePasserby(Vector3 cameraPosition)
{
	PasserbyDifference = cameraPosition - PasserbyPos;
}
/******************************************************************************/
/*!
\brief
Default constructor for passerbys
*/
/******************************************************************************/
void Ai::SetPasserby(Vector3 PasserbyPassIn)
{
	PasserbyPos = PasserbyPassIn;
	PasserbyPos2 = PasserbyPassIn;
	PasserbyPos3 = PasserbyPassIn;
}
/******************************************************************************/
/*!
\brief
returns ai (float) angle
*/
/******************************************************************************/
float Ai::getDerivedAngle()
{
	return derivedAngle;
}
/******************************************************************************/
/*!
\brief
Returns guard position
*/
/******************************************************************************/
Vector3 Ai::getGuardPosition()
{
	return guardPos;
}
/******************************************************************************/
/*!
\brief
Returns passerby's angle(float)
*/
/******************************************************************************/
float Ai::getPasserbyAngle()
{
	return PasserbyAngle;
}
 /******************************************************************************/
/*!
\brief
Returns passerby's Position(float)
*/
/******************************************************************************/
Vector3 Ai::getPasserbyPosition()
{
	return PasserbyPos;
}
 /******************************************************************************/
/*!
\brief
Returns passerby's Angle(float)
*/
/******************************************************************************/
float Ai::getPasserbyAngle2()
{
	return PasserbyAngle2;
}
 /******************************************************************************/
/*!
\brief
Returns passerby's Angle(float)
*/
/******************************************************************************/
float Ai::getPasserbyAngle3()
{
	return PasserbyAngle3;
}
 /******************************************************************************/
/*!
\brief
Returns passerby's Position(float)
*/
/******************************************************************************/
Vector3 Ai::getPasserby2Position()
{
	return PasserbyPos2;
}
 /******************************************************************************/
/*!
\brief
Returns passerby's Position(float)
*/
/******************************************************************************/
Vector3 Ai::getPasserby3Position()
{
	return PasserbyPos3;
}
 /******************************************************************************/
/*!
\brief
Returns Guards state (Bool)
*/
/******************************************************************************/
bool Ai::getAlertState()
{
	return guardAlertState;
}
