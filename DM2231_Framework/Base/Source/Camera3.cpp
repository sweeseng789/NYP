#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"

Camera3::Camera3()
{
}

Camera3::~Camera3()
{
}

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
}

void Camera3::Update(double dt)
{
	static const float CAMERA_SPEED = 200.f;
	static float MOVEMENT_SPEED = 50.f;
	if(Application::IsKeyPressed('A'))
	{
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		position -= right * MOVEMENT_SPEED * (float)dt;
		target -= right * MOVEMENT_SPEED * (float)dt;
	}
	if(Application::IsKeyPressed('D'))
	{
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		position += right * MOVEMENT_SPEED * (float)dt;
		target += right * MOVEMENT_SPEED * (float)dt;
	}
	if(Application::IsKeyPressed('W'))
	{
		Vector3 view = (target - position).Normalized();
		view.y = 0;
		position += view * MOVEMENT_SPEED * (float)dt;
		target += view * MOVEMENT_SPEED * (float)dt;
	}
	if(Application::IsKeyPressed('S'))
	{
		Vector3 view = (target - position).Normalized();
		view.y = 0;
		position -= view * MOVEMENT_SPEED * (float)dt;
		target -= view * MOVEMENT_SPEED * (float)dt;
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
	}

	if(Application::IsKeyPressed('R'))
	{
		Reset();
	}


	//==============Jump Function==========//
	/*static bool pressedSpace = false;
	static bool currentlyJumping = false;
	static bool currentlyFalling = false;*/
	static float JUMP_SPEED = 7.0f;

	if (Application::IsKeyPressed(VK_SPACE) && pressedSpace == false && currentlyJumping == false && currentlyFalling == false)
	{
		pressedSpace = true;
	}

	if (pressedSpace == true && currentlyFalling == false)
	{
		currentlyJumping = true;
		if (position.y < 5.0f)
		{
			position.y += (float)(JUMP_SPEED * dt);
			target.y += (float)(JUMP_SPEED * dt);
			//JUMP_SPEED -= (float)(10.0f * dt);
		}
		else if (position.y >= 5.0f)
		{
			currentlyFalling = true;
			currentlyJumping = false;
		}
	}

	if (currentlyFalling == true && currentlyJumping == false && pressedSpace == true )
	{
		if (position.y >= 0.0f)
		{
			position.y -= (float)(JUMP_SPEED * dt);
			target.y -= (float)(JUMP_SPEED * dt);
			//JUMP_SPEED += (float)(15.0f * dt);
		}
		if (position.y <= 0.0f)
		{
			pressedSpace = false;
			currentlyJumping = false;
			currentlyFalling = false;
			//position.y = target.y = 0.0f;
		}
	}


	//==============SPRINT===================//
	if (Application::IsKeyPressed(VK_LSHIFT) && Application::IsKeyPressed('W') ||
		Application::IsKeyPressed(VK_LSHIFT) && Application::IsKeyPressed('A') ||
		Application::IsKeyPressed(VK_LSHIFT) && Application::IsKeyPressed('S') ||
		Application::IsKeyPressed(VK_LSHIFT) && Application::IsKeyPressed('D'))
	{
		MOVEMENT_SPEED += 10.f * dt;
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