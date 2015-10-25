#include "PlayInfo3PV.h"
#include "MeshBuilder.h"

float CPlayInfo3PV::velSpeed = 30.f;

CPlayInfo3PV::CPlayInfo3PV(void)
	: theAvatarMesh(NULL)
	, jumpspeed(0)
{
	Init();
}


CPlayInfo3PV::~CPlayInfo3PV(void)
{
	if (theAvatarMesh)
	{
		delete theAvatarMesh;
		theAvatarMesh = NULL;
	}
}

// Initialise this class instance
void CPlayInfo3PV::Init(void)
{
	curPosition.Set( 0, 0, 0);
	curDirection.Set( 0, 0, 1 );

	// Initialise the Avatar's movement flags
	for(int i=0; i<255; i++){
		myKeys[i] = false;
	}

	vel.SetZero();
	rotateAngle = 0.f;
}

// Set Model
bool CPlayInfo3PV::SetModel( Mesh* theAvatarMesh )
{
	this->theAvatarMesh = theAvatarMesh;
	if (this->theAvatarMesh == NULL)
		return false;

	return true;
}

// Returns true if the player is on ground
bool CPlayInfo3PV::isOnGround(void)
{
	return true;
}

// Returns true if the player is jumping upwards
bool CPlayInfo3PV::isJumpUpwards(void)
{
	return true;
}

// Returns true if the player is on freefall
bool CPlayInfo3PV::isFreeFall(void)
{
	return true;
}

// Set the player's status to free fall mode
void CPlayInfo3PV::SetOnFreeFall(bool isOnFreeFall)
{
	if (isOnFreeFall == true)
	{
		jumpspeed = 0;
	}
}

// Set the player to jumping upwards
void CPlayInfo3PV::SetToJumpUpwards(bool isOnJumpUpwards)
{
	if (isOnJumpUpwards == true)
	{
		jumpspeed = 15;
	}
}

// Set position x of the player
void CPlayInfo3PV::SetPos_x(int pos_x)
{
	curPosition.x = pos_x;
}

// Set position y of the player
void CPlayInfo3PV::SetPos_y(int pos_y)
{
	curPosition.y = pos_y;
}

// Set position y of the player
void CPlayInfo3PV::SetPos_z(int pos_z)
{
	curPosition.z = pos_z;
}

// Set Jumpspeed of the player
void CPlayInfo3PV::SetJumpspeed(int jumpspeed)
{
	this->jumpspeed = jumpspeed;
}

// Stop the player's movement
void CPlayInfo3PV::SetToStop(void)
{
	jumpspeed = 0;
}

/********************************************************************************
 Hero Move Up Down
 ********************************************************************************/
void CPlayInfo3PV::MoveFrontBack(const bool mode, const float timeDiff)
{
	if (mode)
	{
		curPosition.z = curPosition.z - (int) (200.0f * timeDiff);
	}
	else
	{
		curPosition.z = curPosition.z + (int) (200.0f * timeDiff);
	}
}

/********************************************************************************
 Hero Move Left Right
 ********************************************************************************/
void CPlayInfo3PV::MoveLeftRight(const bool mode, const float timeDiff)
{
	if (mode)
	{
		curPosition.x = curPosition.x + (int) (200.0f * timeDiff);
	}
	else
	{
		curPosition.x = curPosition.x - (int) (200.0f * timeDiff);
	}
}


// Get position x of the player
int CPlayInfo3PV::GetPos_x(void)
{
	return curPosition.x;
}

// Get position y of the player
int CPlayInfo3PV::GetPos_y(void)
{
	return curPosition.y;
}

// Get position y of the player
int CPlayInfo3PV::GetPos_z(void)
{
	return curPosition.z;
}

// Get position of the player
Vector3 CPlayInfo3PV::GetPosition()
{
	return curPosition;
}

// Get direction of the player
Vector3 CPlayInfo3PV::GetDirection()
{
	return curDirection;
}

// Get Jumpspeed of the player
int CPlayInfo3PV::GetJumpspeed(void)
{
	return jumpspeed;
}

// Update Jump Upwards
void CPlayInfo3PV::UpdateJumpUpwards()
{
	curPosition.y -= jumpspeed;
	jumpspeed -= 1;
	if (jumpspeed == 0)
	{
	}
}

// Update FreeFall
void CPlayInfo3PV::UpdateFreeFall()
{
	curPosition.y += jumpspeed;
	jumpspeed += 1;
}

// Constrain the position of the Hero to within the border
void CPlayInfo3PV::ConstrainHero(const int leftBorder, const int rightBorder, 
								  const int topBorder, const int bottomBorder, 
								  float timeDiff)
{
	if (curPosition.x < leftBorder)
	{
		curPosition.x = leftBorder;
	}
	else if (curPosition.x > rightBorder)
	{
		curPosition.x = rightBorder;
	}

	if (curPosition.y < topBorder)
		curPosition.y = topBorder;
	else if (curPosition.y > bottomBorder)
		curPosition.y = bottomBorder;
}

float CPlayInfo3PV::getRotationAngle()
{
	return rotateAngle;
}


/********************************************************************************
 Update Movement
 ********************************************************************************/
void CPlayInfo3PV::UpdateMovement(const unsigned char key, const bool status)
{
	myKeys[key] = status;
}

/********************************************************************************
 Update
 ********************************************************************************/
void CPlayInfo3PV::Update(double dt, Camera3 &camera)
{
	Vector3 view = camera.direction;
	view.Normalize();
	view.y = 0;

	Vector3 right = view.Cross(camera.up);
	right.y = 0;
	right.Normalize();

	// WASD movement
	if ( myKeys['w'] == true)
	{
		vel += view * velSpeed * dt;
	}

	if (myKeys['s'] == true)
	{
		vel -= view * velSpeed * dt;
	}

	if (myKeys['a'] == true)
	{
		vel -= right * velSpeed * dt;
	}

	if (myKeys['d'] == true)
	{
		vel += right * velSpeed * dt;
	}


	//Friction
	if (vel.x != 0)
	{
		float Fforce_x = 0 - vel.x;
		vel.x += Fforce_x * dt * 5.f;
	}

	if (vel.z != 0)
	{
		float Fforce_z = 0 - vel.z;
		vel.z += Fforce_z * dt * 5.f;
	}

	curPosition += vel;

	if (curDirection != view)
	{
		target = curPosition + curDirection;

		float rotationDiff = SSDLC::findAngleFromPos(target, curPosition) - SSDLC::findAngleFromPos(target, curPosition);

		rotateAngle = -rotationDiff;
	}

	// Rotation
	/*
	if ( myKeys[VK_UP] == true)
	{
		LookUp( dt );
	}
	if (myKeys[VK_DOWN] == true)
	{
		LookUp( -dt );
	}
	if (myKeys[VK_LEFT] == true)
	{
		TurnLeft( -dt );
	}
	if (myKeys[VK_RIGHT] == true)
	{
		TurnRight( dt );
	}

	// Jump
	if (myKeys[32] == true)
	{
		Jump( dt );
		myKeys[32]	= false;
	}
	UpdateJump(dt);

	//Update the camera direction based on mouse move
	// left-right rotate
	if ( Application::camera_yaw != 0 )
		Yaw( dt );
	if ( Application::camera_pitch != 0 )
		Pitch( dt );

	if(Application::IsKeyPressed('R'))
	{
		Reset();
	}
	*/
}