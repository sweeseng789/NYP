#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"

Camera3::Camera3()
{
}

Camera3::~Camera3()
{
}

static const float CAMERA_SPEED = 200.f;
static float MOVEMENT_SPEED = 50.f;
Vector3 testingP (0, 0, 0);
Vector3 testingT (0, 0, 0);


void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();

	pressedSpace = false;
	currentlyJumping = false;
	currentlyFalling = false;

	for (int a = 0; a < 255; a++)
	{
		myKeys[a] = false;
	}

	//Initialise the camera type
	sCameraType = LAND_CAM;

	m_bJumping = false;
	JumpVel = 0.0f;
	JUMPMAXSPEED = 10.0f;
	JUMPACCEL = 10.0f;
	GRAVITY = -30.0f;
}

void Camera3::MoveForward(const double dt)
{
	Vector3 view = (target - position).Normalized();
	//view.y = 0;
	position += view * MOVEMENT_SPEED * (float)dt;
	target += view * MOVEMENT_SPEED * (float)dt;
}
void Camera3::MoveBackward(const double dt)
{
	Vector3 view = (target - position).Normalized();
	//view.y = 0;
	position -= view * MOVEMENT_SPEED * (float)dt;
	target -= view * MOVEMENT_SPEED * (float)dt;
}
void Camera3::MoveLeft(const double dt)
{
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	position -= right * MOVEMENT_SPEED * (float)dt;
	target -= right * MOVEMENT_SPEED * (float)dt;
}
void Camera3::MoveRight(const double dt)
{
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	position += right * MOVEMENT_SPEED * (float)dt;
	target += right * MOVEMENT_SPEED * (float)dt;
}

// Update Camera status
void Camera3::UpdateStatus(const unsigned char key)
{
	myKeys[key] = true;
}

void Camera3::Update(double dt)
{
	
	if(myKeys['a'] == true)
	{
		MoveLeft(dt);
		myKeys['a'] = false;
	}
	if(myKeys['d'] == true)
	{
		MoveRight(dt);
		myKeys['d'] = false;
	}
	if(myKeys['w'] == true)
	{
		MoveForward(dt);
		myKeys['w'] = false;
	}
	if(myKeys['s'] == true)
	{
		MoveBackward(dt);
		myKeys['s'] = false;
	}

	if(Application::IsKeyPressed(VK_LEFT))
	{
		Vector3 view = (target - position).Normalized();
		float yaw = (float)(CAMERA_SPEED * (float)dt);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = position + view;
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
	}
	if(Application::IsKeyPressed(VK_RIGHT))
	{
		Vector3 view = (target - position).Normalized();
		float yaw = (float)(-CAMERA_SPEED * (float)dt);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = position + view;
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
	}
	if(Application::IsKeyPressed(VK_UP))
	{
		float pitch = (float)(CAMERA_SPEED * (float)dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = position + view;
	}
	if(Application::IsKeyPressed(VK_DOWN))
	{
		float pitch = (float)(-CAMERA_SPEED * (float)dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = position + view;
	}

	//Update camera base on direction 
	//Left-right rotate
	/*{
		Vector3 view = (target - position).Normalized();
		float yaw = (float)(-CAMERA_SPEED * Application::camera_yaw * (float)dt);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = position + view;
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
	}
	{
		float pitch = (float)(-CAMERA_SPEED * Application::camera_pitch * (float)dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = position + view;
	}*/
	if (Application::camera_yaw != 0 )
		Yaw(dt);
	if (Application::camera_pitch != 0)
		Pitch(dt);

	if(Application::IsKeyPressed('R'))
	{
		Reset();
	}


	//==============Jump Function==========//
	/*static bool pressedSpace = false;
	static bool currentlyJumping = false;
	static bool currentlyFalling = false;*/
	static float JUMP_SPEED = 7.0f;

	//if (Application::IsKeyPressed(VK_SPACE) && pressedSpace == false && currentlyJumping == false && currentlyFalling == false)
	//{
	//	pressedSpace = true;
	//}

	//if (pressedSpace == true && currentlyFalling == false)
	//{
	//	currentlyJumping = true;
	//	if (position.y < 5.0f)
	//	{
	//		position.y += (float)(JUMP_SPEED * dt);
	//		target.y += (float)(JUMP_SPEED * dt);
	//		//JUMP_SPEED -= (float)(10.0f * dt);
	//	}
	//	else if (position.y >= 5.0f)
	//	{
	//		currentlyFalling = true;
	//		currentlyJumping = false;
	//	}
	//}

	//if (currentlyFalling == true && currentlyJumping == false && pressedSpace == true )
	//{
	//	if (position.y >= 0.0f)
	//	{
	//		position.y -= (float)(JUMP_SPEED * dt);
	//		target.y -= (float)(JUMP_SPEED * dt);
	//		JUMP_SPEED += (float)(15.0f * dt);
	//	}
	//	if (position.y <= 0.0f)
	//	{
	//		pressedSpace = false;
	//		currentlyJumping = false;
	//		currentlyFalling = false;
	//		position.y = target.y = 0.0f;
	//	}
	//}

	if (myKeys[32] == true)
	{
		Jump( dt );
		myKeys[32] = false;
	}
	UpdateJump(dt);


	//==============SPRINT===================//
	if (Application::IsKeyPressed(VK_LSHIFT) && Application::IsKeyPressed('W') ||
		Application::IsKeyPressed(VK_LSHIFT) && Application::IsKeyPressed('A') ||
		Application::IsKeyPressed(VK_LSHIFT) && Application::IsKeyPressed('S') ||
		Application::IsKeyPressed(VK_LSHIFT) && Application::IsKeyPressed('D'))
	{
		MOVEMENT_SPEED += 1000.f * dt;
		if (MOVEMENT_SPEED > 80.0f)
		{
			MOVEMENT_SPEED = 80.0f;
		}
	}
	else
	{
		MOVEMENT_SPEED -= 10.f * dt;
		if (MOVEMENT_SPEED < 50.f)
		{
			MOVEMENT_SPEED = 50.0f;
		}
	}

	direction = target - position;
}

void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}

/*************************************************************************
Set Camera Type
*************************************************************************/
void Camera3::SetCameraType(CAM_TYPE sCameraType)
{
	this->sCameraType = sCameraType;
}

/*************************************************************************
Get Camera Type
*************************************************************************/
Camera3::CAM_TYPE Camera3::GetCameraType()
{
	return sCameraType;
}

/*************************************************************************
Walk front or back
*************************************************************************/
void Camera3::Walk(const double dt)
{
	if (dt > 0)
		MoveForward(dt);
	else if (dt < 0)
		MoveBackward(abs(dt));
}

/*************************************************************************
Strafe Left or Right
*************************************************************************/
void Camera3::Strafe(const double dt)
{
	if (dt > 0)
		MoveRight(dt);
	else if (dt < 0)
		MoveLeft(abs(dt));
}

/*************************************************************************
Pitch
*************************************************************************/
void Camera3::Pitch(const double dt)
{
	if (Application::camera_pitch > 0.0)
		LookUp(dt);
	else if (Application::camera_pitch < 0.0)
		LookDown(dt);
}

/*************************************************************************
Yaw
*************************************************************************/
void Camera3::Yaw(const double dt)
{
	if (Application::camera_yaw > 0.0)
		SpinClockWise(dt);
	else if (Application::camera_yaw < 0.0)
		SpinCounterClockWise(dt);
}

/*************************************************************************
Lookup
*************************************************************************/
void Camera3::LookUp(const double dt)
{
	float pitch = (float)(-CAMERA_SPEED * Application::camera_pitch * (float) dt);
	Vector3 view= (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();
	Mtx44 rotation;
	rotation.SetToRotation(pitch, right.x, right.y, right.z);
	view = rotation * view;
	target = position + view;
}

/*************************************************************************
Lookdown
*************************************************************************/
void Camera3::LookDown(const double dt)
{
	float pitch = (float)(-CAMERA_SPEED * Application::camera_pitch * (float) dt);
	Vector3 view= (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();
	Mtx44 rotation;
	rotation.SetToRotation(pitch, right.x, right.y, right.z);
	view = rotation * view;
	target = position + view;
}

/*************************************************************************
ClockWise
*************************************************************************/
void Camera3::SpinClockWise(const double dt)
{
	Vector3 view = (target - position).Normalized();
	float yaw = (float)(-CAMERA_SPEED * Application::camera_yaw * (float)dt);
	Mtx44 rotation;
	rotation.SetToRotation(yaw, 0, 1, 0);
	view = rotation * view;
	target = position + view;
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();
}

/*************************************************************************
Counter ClockWise
*************************************************************************/
void Camera3::SpinCounterClockWise(const double dt)
{
	Vector3 view = (target - position).Normalized();
	float yaw = (float)(-CAMERA_SPEED * Application::camera_yaw * (float)dt);
	Mtx44 rotation;
	rotation.SetToRotation(yaw, 0, 1, 0);
	view = rotation * view;
	target = position + view;
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	up = right.Cross(view).Normalized();
}

/*************************************************************************
Jump
*************************************************************************/
void Camera3::Jump(const double dt)
{
	if (m_bJumping == false)
	{
		m_bJumping = true;
		// Calculate the jump velocity
		JumpVel = JUMPACCEL;// * dt;
		// Factor in maximum speed limit
		if (JumpVel > JUMPMAXSPEED)
			JumpVel = JUMPMAXSPEED;
	}
}

	/********************************************************************************
	Update Jump
	********************************************************************************/
	void Camera3::UpdateJump(const double dt)
	{
		if (m_bJumping == true)
		{
			// Factor in gravity
			JumpVel += GRAVITY * dt;
			// Update the camera and target position
			position.y += JumpVel * (float)dt;
			target.y += JumpVel * (float)dt;

			std::cout << position << std::endl;

			// Check if the camera has reached the ground
			if (position.y <= 0)
			{
				position.y = 0;
				target.y = 0;
				JumpVel = 0.0f;
				m_bJumping = false;
			}
		}
	}