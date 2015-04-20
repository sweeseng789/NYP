/******************************************************************************/
/*!
\file	Camera3.cpp
\author Princeton Chew, name, name, name,
\par	email: 141991A@mymail.nyp.edu.sg
\brief
Camera3 Class
*/
/******************************************************************************/
#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"

/******************************************************************************/
/*!
\brief
Default constructor for class
*/
/******************************************************************************/
Camera3::Camera3()
{
}

/******************************************************************************/
/*!
\brief
Default destructor for class
*/
/******************************************************************************/
Camera3::~Camera3()
{
}

/******************************************************************************/
/*!
\brief
Initializes all the data for the camera

\param pos - Vector3 position of camera
\param target - Vector3 target of camera
\param up - Vector3 up of camera
*/
/******************************************************************************/
void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	escal = false;
	escaldown = false;
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	temp = 0;
	isCrouching = false;
	Crouching = false;
	Jumping = false;
	isJumping = false;
	isFalling = false;
	checkingOut = false;
	tempJumpY = 0.f;
	tempJumpTargY = 0.f;
	tempCrouchY = position.y;
	tempCrouchTargY = target.y;
	CAMERA_SPEED = 15.f;
	JUMP_SPEED = 12.f;
	CollisionWithAi = false;
	gotCaught = false;
	showingMenu = true;
	//=======Collision=========//
	//Middle shelf
	maxPos.Set(13.4, 10, 15.2);
	minPos.Set(8.3, -10, -9.3);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Left shelf (closer to cashier)
	maxPos.Set(18.3,10,-33.5);
	minPos.Set(-30.6,-10,-37.5);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Extreme left shelf
	maxPos.Set(21.5,10,-55.7);
	minPos.Set(-33.1,-10,-60.7);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Left frozen food shelf
	maxPos.Set(36.1,10,-88.2);
	minPos.Set(-35.5,-10,-94);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Back frozen food shelf
	maxPos.Set(54.8,10,63.4);
	minPos.Set(48.9,-10,-77.5);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Right wooden shelf
	maxPos.Set(18.6,10,36.8);
	minPos.Set(-30.3,-10,32.4);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//extreme Right Metal shelf
	maxPos.Set(21.4,10,60.3);
	minPos.Set(-33.2,-10,55.3);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Right metal fence
	maxPos.Set(-18.7,6,27.2);
	minPos.Set(-30.6,-5,24.9);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Middle metal fence
	maxPos.Set(-19.6,6,8.7);
	minPos.Set(-29.3,-5,7.2);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Left metal fence
	maxPos.Set(-18.9,6,-9.1);
	minPos.Set(-29.6,-5,-11.4);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Right cashier
	maxPos.Set(-18,6,22);
	minPos.Set(-30,-5,17.6);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Right cashier (cash register)
	maxPos.Set(-26.6,6,19);
	minPos.Set(-29.9,-5,14);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Middle cashier
	maxPos.Set(-18.1,6,4.6);
	minPos.Set(-30.1,-5,0.84);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Middle cashier(Cash Register)
	maxPos.Set(-26,6,2.1);
	minPos.Set(-30.1,-5,-2.1);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Left Cashier
	maxPos.Set(-18,6,-13);
	minPos.Set(-30.4,-5,-17.1);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Left Cashier(Cash Register)
	maxPos.Set(-26,6,-17);
	minPos.Set(-30.5,-5,-20.4);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Right entrance (wall)
	maxPos.Set(-53.8,40,96.2);
	minPos.Set(-57,-5,19.4);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Left entrance (wall)
	maxPos.Set(-54.3,40,-19.2);
	minPos.Set(-57,-5,-96.2);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Left side (wall)
	maxPos.Set(56.8,40,-93.5);
	minPos.Set(-57,-5,-96.4);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Back (wall)
	maxPos.Set(57.5,40,96.2);
	minPos.Set(54.5,-5,-96);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Right side (wall)
	maxPos.Set(95,40,96.4);
	minPos.Set(-57.5,-5,93.2);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Escalator bottom
	maxPos.Set(-6.9,10,91);
	minPos.Set(-28.4,-6,63.4);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Escalator Left Handle (Bottom facing escalator)
	maxPos.Set(-29,10,64.7);
	minPos.Set(-33,-5,63);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Escalator Left Handle (Bottom facing escalator)
	maxPos.Set(-30.1,10,91.3);
	minPos.Set(-32.7,-5,89.8);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//==========================Collision for 2nd floor============================//

	//Escalator Right Handle (Top facing escalator)
	maxPos.Set(28.4,30,64.6);
	minPos.Set(25.6,23,63);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Escalator Left Handle (Top facing escalator)
	maxPos.Set(29,30,93);
	minPos.Set(27,23,89.6);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Escalator middle Handle (Top facing escalator)
	maxPos.Set(28.7,30,78.4);
	minPos.Set(26.2,23,76);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Escalator (prevents going down on wrong escalator)
	maxPos.Set(27.4,30,76);
	minPos.Set(26.2,23,64.7);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Railing collision (length)
	maxPos.Set(28.8,30,63.6);
	minPos.Set(-27.8,23,60.9);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Railing collision (opposite of railing)
	maxPos.Set(-26.3,30,95);
	minPos.Set(-27.36,23,60.9);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Metal shelf (front right)
	maxPos.Set(25.2,30,45.4);
	minPos.Set(20.6,23,14.5);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//wooden shelf (front Middle)
	maxPos.Set(6.9,30,42.8);
	minPos.Set(2,23,17.6);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Metal shelf (front Left)
	maxPos.Set(-12,30,45.2);
	minPos.Set(-16.8,23,14.6);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Metal shelf (Middle right)
	maxPos.Set(25.3,30,-2.6);
	minPos.Set(20.6,23,-21.4);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//wooden shelf (Middle Middle)
	maxPos.Set(6.9,30,-5.5);
	minPos.Set(2,23,-18.4);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Metal shelf (Middle Left)
	maxPos.Set(-12,30,-2.5);
	minPos.Set(-16.8,23,-21.5);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Metal shelf (Back right)
	maxPos.Set(25.3,30,-38.5);
	minPos.Set(20.6,23,-69.5);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//wooden shelf (Back Middle)
	maxPos.Set(6.9,30,-41.4);
	minPos.Set(2,23,-66.3);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Metal shelf (Back Left)
	maxPos.Set(-12,30,-38.33);
	minPos.Set(-16.8,23,-69.55);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//COLD FOOD SHELF
	maxPos.Set(-49.1,30,50.2);
	minPos.Set(-54.6,23,-77.2);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//Dust bin
	maxPos.Set(-60,8,-19);
	minPos.Set(-63.5,0,-23);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//===========NPC COLLISION===============//
	//GTP
	maxPos.Set(31.5,10,91);
	minPos.Set(28,0,88);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);

	//TA
	maxPos.Set(-150,10,0);
	minPos.Set(-152,0,-4);
	maximum.push_back(maxPos);
	minimum.push_back(minPos);
}

/******************************************************************************/
/*!
\brief
Set Bound check for the Y axis of camera
*/
/******************************************************************************/
void Camera3::BoundsCheck()
{
	if(position.y >= 5)
	{
		position.y = tempPos.y;
		target.y = tempTarg.y;
	}
	if(position.y <= 5)
	{
		position.y = tempPos.y;
		target.y = tempTarg.y;
	}
}

/******************************************************************************/
/*!
\brief
Check if camera is going into bounds

\param maximum - Vector3 maximum position 
\param minimum - Vector3 minimum position
*/
/******************************************************************************/
void Camera3::bound(Vector3 maximum, Vector3 minimum)
{
	//===Collision==//
	if((position.x <= maximum.x) && (position.y <= maximum.y) &&(position.z <= maximum.z) && (position.x >= minimum.x) && (position.y >= minimum.y)&& (position.z >= minimum.z) )
	{
		position.x = tempPos.x;
		position.y = tempPos.y;
		position.z = tempPos.z;

		target.x = tempTarg.x;
		target.y = tempTarg.y;
		target.z = tempTarg.z;
	}
}

/******************************************************************************/
/*!
\brief
Updates camera based on delta time

\param dt - delta time
*/
/******************************************************************************/
void Camera3::Update(double dt)
{
	static const float TURN_SPEED = 100.f;
	bool walk = true;
	/*===========================================================
							MOVING AROUND
	==============================================================*/
	//==========STRAFE LEFT===========//
	//Sprint
	
	if(Application::IsKeyPressed(VK_SHIFT) && Application::IsKeyPressed('A') && escal == false && escaldown == false && checkingOut == false)
	{
		if(CAMERA_SPEED <= 40)
		{
			CAMERA_SPEED += (float)(10*dt);
		}

		tempPos = position;
		tempTarg = target;
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		position -= right * CAMERA_SPEED * dt;
		target -= right * CAMERA_SPEED * dt;

		//===Collision Check==//
		BoundsCheck();

		for(int i = 0; i < maximum.size();i++)
		{
			bound(maximum[i], minimum[i]);
		}

	}
	//Walk
	else if(Application::IsKeyPressed('A') && escal == false && escaldown == false && checkingOut == false)
	{
		if(CAMERA_SPEED >15.f)
		{
			CAMERA_SPEED -= (float)(10*dt);
		}
		tempPos = position;
		tempTarg = target;

		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		position -= right * CAMERA_SPEED * dt;
		target -= right * CAMERA_SPEED * dt;

		//===Collision Check==//
		BoundsCheck();

		for(int i = 0; i < maximum.size();i++)
		{
			bound(maximum[i], minimum[i]);
		}
	}
	//=========MOVE BACKWARDS==========//
	//Sprint
	else if(Application::IsKeyPressed(VK_SHIFT) && Application::IsKeyPressed('S') && escal == false && escaldown == false && checkingOut == false)
	{
		if(CAMERA_SPEED <= 40)
		{
			CAMERA_SPEED += (float)(10*dt);
		}
		tempPos = position;
		tempTarg = target;

		Vector3 view = (target - position).Normalized();
		target -= view * CAMERA_SPEED * dt;
		position -= view * CAMERA_SPEED * dt;

		//===Collision Check==//

		BoundsCheck();

		for(int i = 0; i < maximum.size();i++)
		{
			bound(maximum[i], minimum[i]);
		}
	}
	//Walk
	else if(Application::IsKeyPressed('S') && escal == false && escaldown == false && checkingOut == false)
	{
		if(CAMERA_SPEED >15.f)
		{
			CAMERA_SPEED -= (float)(10*dt);
		}
		tempPos = position;
		tempTarg = target;

		Vector3 view = (target - position).Normalized();
		target -= view * CAMERA_SPEED * dt;
		position -= view * CAMERA_SPEED * dt;

		//===Collision Check==//

		BoundsCheck();

		for(int i = 0; i < maximum.size();i++)
		{
			bound(maximum[i], minimum[i]);
		}
	}

	//=============STRAFE RIGHT================//
	//Sprint
	else if(Application::IsKeyPressed(VK_SHIFT) && Application::IsKeyPressed('D') && escal == false && escaldown == false && checkingOut == false)
	{
		if(CAMERA_SPEED <= 40)
		{
			CAMERA_SPEED += (float)(10*dt);
		}
		tempPos = position;
		tempTarg = target;

		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		position += right * CAMERA_SPEED * dt;
		target += right * CAMERA_SPEED * dt;

		//===Collision Check==//
		BoundsCheck();

		for(int i = 0; i < maximum.size();i++)
		{
			bound(maximum[i], minimum[i]);
		}
	}
	//Walk
	else if(Application::IsKeyPressed('D') && escal == false && escaldown == false && checkingOut == false)
	{
		if(CAMERA_SPEED >15.f)
		{
			CAMERA_SPEED -= (float)(10*dt);
		}
		tempPos = position;
		tempTarg = target;

		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		position += right * CAMERA_SPEED * dt;
		target += right * CAMERA_SPEED * dt;

		//===Collision Check==//
		BoundsCheck();

		for(int i = 0; i < maximum.size();i++)
		{
			bound(maximum[i], minimum[i]);
		}
	}

	//===============MOVE FORWARD==========//
	//Sprint
	else if(Application::IsKeyPressed(VK_SHIFT) && Application::IsKeyPressed('W') && escal == false && escaldown == false && CollisionWithAi == false && checkingOut == false)
	{
		if(CAMERA_SPEED <= 40)
		{
			CAMERA_SPEED += (float)(10*dt);
		}
		tempPos = position;
		tempTarg = target;

		Vector3 view = (target - position).Normalized();
		target += view * CAMERA_SPEED * dt;
		position += view * CAMERA_SPEED * dt;

		//===Collision Check==//
		BoundsCheck();

		for(int i = 0; i < maximum.size();i++)
		{
			bound(maximum[i], minimum[i]);
		}
	}
	//Walk
	else if(Application::IsKeyPressed('W') && escal == false && escaldown == false && CollisionWithAi == false && checkingOut == false)
	{
		if(CAMERA_SPEED >15.f)
		{
			CAMERA_SPEED -= (float)(10*dt);
		}
		tempPos = position;
		tempTarg = target;

		Vector3 view = (target - position).Normalized();
		target += view * CAMERA_SPEED * dt;
		position += view * CAMERA_SPEED * dt;

		//===Collision Check==//
		BoundsCheck();

		for(int i = 0; i < maximum.size();i++)
		{
			bound(maximum[i], minimum[i]);
		}
	}
	//Return to normal Speed
	else
	{
		if(CAMERA_SPEED >15.f)
		{
			CAMERA_SPEED -= (float)(10*dt);
		}
	}
	/*===================================================
					LOOKING AROUND
	=====================================================*/
	//==Look Right==//
	if(Application::IsKeyPressed(VK_RIGHT))
	{
		float pitch = (float)(-TURN_SPEED * dt);
		Vector3 view = (target - position).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, 0,1, 0);
		up = rotation * up;
		view = rotation * view;
		target = (rotation * (target - position)) + position;
	}
	//==Look Left==//
	if(Application::IsKeyPressed(VK_LEFT))
	{
		float pitch = (float)(TURN_SPEED * dt);
		Vector3 view = (target - position).Normalized();	
		Mtx44 rotation;
		rotation.SetToRotation(pitch, 0,1, 0);
		up = rotation * up;
		view = rotation * view;
		target = (rotation * (target - position)) + position;
	}
	//==Look Down==//
	if(temp > -20)
	{
		if(Application::IsKeyPressed(VK_DOWN) && showingMenu == false)
		{
			float pitch = (float)(-TURN_SPEED * dt);
			Vector3 view = (target - position).Normalized();
			Vector3 right = view.Cross(up);
			right.y = 0;
			right.Normalize();
			up = right.Cross(view).Normalized();
			Mtx44 rotation;
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			view = rotation * view;
			target = (rotation * (target - position)) + position;

			//==View Limiter==//
			temp--;
		}
	}
	//==Look Up==//
	if(temp < 20)
	{
		if(Application::IsKeyPressed(VK_UP) && showingMenu == false)
		{
			float pitch = (float)(TURN_SPEED * dt);
			Vector3 view = (target - position).Normalized();
			Vector3 right = view.Cross(up);
			right.y = 0;
			right.Normalize();
			up = right.Cross(view).Normalized();
			Mtx44 rotation;
			rotation.SetToRotation(pitch, right.x, right.y, right.z);
			view = rotation * view;
			target = (rotation * (target - position)) + position;


			//==View Limiter==//
			temp++;
		}
	}
	

	////=====================================Escalator===============================================

	Vector3 direction = Vector3(30,23,0) - Vector3(-25,5,0);
	direction.Normalized();

	if (escal == true) //Movement from bottom to top
	{
		position += direction *(0.5*dt);
		target += direction * (0.5*dt);
		
	}

	if (escaldown == true) //Movement from top to bottom
	{
		position -= direction *(0.5*dt);
		target -= direction * (0.5*dt);
		
	}

	if(position.x >= -35 && position.x <=-28 && position.y >= 3 && position.y <=6 && position.z >= 64.9 && position.z <= 75) //Area to trigger going up
	{	
		escaldown = false;
		escal = true;
	
	}
	if(position.x <=29.9  && position.x >= 14 && position.y >= 20 && position.y <=30 && position.z >= 80 && position.z <=90) //Area to trigger going down.
	{
		escal = false;
		escaldown = true;
	}
	else if(position.x >= 27.5)
	{
		escal = false;
		
	}
	else if (position.y <= 5)
	{
		escaldown = false;
	}
	

	//==================================== end of escalator ============================= //
	/*====================================================================================
										JUMPING
	=======================================================================================*/

	//==============LEVEL 1==============//
	if(position.y < 15)
	{
		if(Application::IsKeyPressed(VK_SPACE) && isJumping == false && isFalling == false && Crouching == false && isCrouching == false)
		{
			Jumping = true;
			tempJumpY = position.y;
		}

		if(Jumping == true)
		{
			isJumping = true;

			if(position.y <= 8)
			{
				position.y += (float)(JUMP_SPEED * dt);
				target.y += (float)(JUMP_SPEED * dt);
				JUMP_SPEED -= (float)(20 * dt);
			}
			else
			{
				isJumping = false;
				Jumping = false;
				isFalling = true;
			}
		}
		if(isFalling == true)
		{
			if(position.y >= 5)
			{
				position.y -= (float)(JUMP_SPEED * dt);
				target.y -= (float)(JUMP_SPEED * dt);
				JUMP_SPEED += (float)(40 * dt);
			}
			if(position.y <= 5)
			{
				isFalling = false;
				JUMP_SPEED = 12.f;
			}
		}
	}

	//==================LEVEL 2==================//
	if(position.y > 20)
	{
		if(Application::IsKeyPressed(VK_SPACE) && isJumping == false && isFalling == false && Crouching == false && isCrouching == false)
		{
			Jumping = true;
			tempJumpY = position.y;
		}

		if(Jumping == true)
		{
			isJumping = true;

			if(position.y <= 28.5)
			{
				position.y += (float)(JUMP_SPEED * dt);
				target.y += (float)(JUMP_SPEED * dt);
				JUMP_SPEED -= (float)(20 * dt);
			}
			else
			{
				isJumping = false;
				Jumping = false;
				isFalling = true;
			}
		}
		if(isFalling == true)
		{
			if(position.y >= 25.5)
			{
				position.y -= (float)(JUMP_SPEED * dt);
				target.y -= (float)(JUMP_SPEED * dt);
				JUMP_SPEED += (float)(40 * dt);
			}
			if(position.y <= 25.5)
			{
				isFalling = false;
				JUMP_SPEED = 12.f;
			}
		}
	}
	/*=======================================================================================
										CROUCHING
	======================================================================================*/
	//==========LEVEL 1=============//
	if(position.y < 15)
	{
		if(Application::IsKeyPressed(VK_LCONTROL) && isCrouching == false && Crouching == false && isJumping == false && isFalling == false)
		{
			Crouching = true;
			tempCrouchY = position.y;
			tempCrouchTargY = target.y;
		}
		else if(Application::IsKeyPressed(VK_LCONTROL) && isCrouching == false && Crouching == true)
		{
			Crouching = false;
			isCrouching = true;
		}
		if(Crouching == true)
		{
			isCrouching = true;
			if(position.y >= 3)
			{
				position.y -= (float)(CAMERA_SPEED * dt);
				target.y  -= (float)(CAMERA_SPEED * dt);
			}
			else
			{
				isCrouching = false;
			}
		}
		else if(Crouching == false && isCrouching == true)
		{
			if(position.y < 5)
			{
				position.y += (float)(CAMERA_SPEED * dt);
				target.y  += (float)(CAMERA_SPEED * dt);
			}
			if(position.y >= 5)
			{
				isCrouching = false;
			}
		}
	}
	//=============LEVEL 2=================//
	if(position.y > 20)
	{
		if(Application::IsKeyPressed(VK_LCONTROL) && isCrouching == false && Crouching == false && isJumping == false && isFalling == false)
		{
			Crouching = true;
			tempCrouchY = position.y;
			tempCrouchTargY = target.y;
		}
		else if(Application::IsKeyPressed(VK_LCONTROL) && isCrouching == false && Crouching == true)
		{
			Crouching = false;
			isCrouching = true;
		}
		if(Crouching == true)
		{
			isCrouching = true;
			if(position.y >= 23.5)
			{
				position.y -= (float)(CAMERA_SPEED * dt);
				target.y  -= (float)(CAMERA_SPEED * dt);
			}
			else
			{
				isCrouching = false;
			}
		}
		else if(Crouching == false && isCrouching == true)
		{
			if(position.y < 25.5)
			{
				position.y += (float)(CAMERA_SPEED * dt);
				target.y  += (float)(CAMERA_SPEED * dt);
			}
			if(position.y >= 25.5)
			{
				isCrouching = false;
			}
		}
	}
	if(Application::IsKeyPressed('R'))
	{
		Reset();
	}
}

/******************************************************************************/
/*!
\brief
Sets bool if player is checking out

\param a - Bool of checking out status
*/
/******************************************************************************/
void Camera3::setCheckingOut(bool a)
{
	checkingOut = a;
}

/******************************************************************************/
/*!
\brief
Resets camera to initial position, target and up
*/
/******************************************************************************/
void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}