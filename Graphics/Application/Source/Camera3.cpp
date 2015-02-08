#include "Camera3.h"
#include "Application.h"
#include "Mtx44.h"
Camera3::Camera3()
{
}

Camera3::~Camera3()
{
}
/*
Left = cameraWorldPos.x - Vector3(1.0f,0.0f,0.0f) * (skyBoxScale.x * 0.5f);
Top = cameraWorldPos.y + Vector3(0.0f,1.0f,0.0f) * (skyBoxScale.y * 0.5f);
Right = Left + skyBoxScale.x;
Bottom = Top + skyBoxScale.y;
Front = cameraWorldPos.x + Vector3(0.0f,0.0f,1.0f) * (skyBoxScale.z * 0.5f);
Back = Front - skyBoxScale.z;
*/

void Camera3::Init(const Vector3& pos, const Vector3& target, const Vector3& up)
{
	angleX = angleY = 0.1;
	this->position = defaultPosition = pos;
	this->target = defaultTarget = target; 
	Vector3 view = (target - position).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	nearDoor1 = nearDoor2 = false;
	boundCheckFront = boundCheckBack = boundCheckLeft = boundCheckRight = false;
	HaventOpenDoor = false;
	edgeOfWorld = false;
}

void Camera3::Update(double dt)
{
	static const float CAMERA_SPEED = 10.f;

	if(Application::IsKeyPressed(VK_LEFT))
	{
		Vector3 view = (target - position).Normalized();
		float yaw = (float)(100 * dt);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);//rotate by Y
		view = rotation * view;//transient value
		target = view + position;//update position
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		CharacterRotation = right.Cross(view).Normalized();
	}

	if(Application::IsKeyPressed(VK_RIGHT))
	{
		Vector3 view = (target - position).Normalized();
		float yaw = (float)(-100 * dt);
		Mtx44 rotation;
		rotation.SetToRotation(yaw, 0, 1, 0);
		view = rotation * view;
		target = view + position;
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		CharacterRotation = right.Cross(view).Normalized();
	}

	if(Application::IsKeyPressed(VK_UP))
	{
		float pitch = (float)(100 * dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = view + position;
	}

	if(Application::IsKeyPressed(VK_DOWN))
	{
		float pitch = (float)(-100 * dt);
		Vector3 view = (target - position).Normalized();
		Vector3 right = view.Cross(up);
		right.y = 0;
		right.Normalize();
		up = right.Cross(view).Normalized();
		Mtx44 rotation;
		rotation.SetToRotation(pitch, right.x, right.y, right.z);
		view = rotation * view;
		target = view + position;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////
	if (position.x <= -8.8 && nearDoor1 == false) //left
	{
		position.x = -8.8;
		boundCheckLeft = true;
	}
	if (position.x >= 8.8 && nearDoor1 == false)
	{
		position.x = 8.8;
		boundCheckRight = true;
	}
	if (position.z <= -1 && nearDoor1 == false)
	{
		position.z = -1;
		boundCheckFront = true;
	}
	if (position.z >= 15 && nearDoor1 == false)
	{
		position.z = 15;
		boundCheckBack = true;
	}

	if (position.x > -8.8 && position.x < 8.8)
	{
		boundCheckLeft = boundCheckRight = false;
	}
	if (position.z > -1 && position.z < 15)
	{
		boundCheckBack = boundCheckFront = false;
	}

	if (position.x <= 2.5 && position.x >= -2.5 && nearDoor1 == false)
	{
		if (position.z >= 14.8 && position.z <= 15)
		{
			HaventOpenDoor = true;
			if (Application::IsKeyPressed('E'))
			{
				nearDoor1 = true;
			}
		}
		else
		{
			HaventOpenDoor = false;
		}
	}
	if (position.x >= 8 && position.x <= 8.8 && nearDoor1 == false)
	{
		if (position.z >= 1.8 && position.z <= 2.5)
		{
			if (Application::IsKeyPressed('E'))
			{
				std::cout << "Detected" << std::endl;
			}
		}
	}
	if (nearDoor1 == true && nearDoor2 == false)
	{
		position.x = -0.196141;
		position.z = 22.2031;
		target.x = -0.140504;
		target.z = 23.2016;
		nearDoor2 = true;
		HaventOpenDoor = false;
	}

	if (nearDoor2 == true && position.z <= 21)
	{
		position.z = 21;
	}
	if (nearDoor2 == true && position.x >= 8)
	{
		position.x = 8;
	}
	if (nearDoor2 == true && position.z >= 35)
	{
		position.z = 35;
	}
	if (nearDoor2 == true && position.x <= -25)
	{
		position.x = -25;
		edgeOfWorld = true;
	}
	else
	{
		edgeOfWorld = false;
	}

	if (position.x > -2.3 && position.x < 2.3 && nearDoor2 == true)
	{
		if (position.z >= 21 && position.z < 22)
		{
			HaventOpenDoor = true;
			if (Application::IsKeyPressed('E'))
			{
				position.x = 3;
				position.z = 16;
				target.x = 2.89892;
				target.z = 14.0051;
				nearDoor1 = false;
				nearDoor2 = false;
				HaventOpenDoor = false;
			}
		}
		else
		{
			HaventOpenDoor = false;
		}
	}
	///////////////////////////////////////////////////////////////////////////////////////////////////

	if(Application::IsKeyPressed('A'))
	{
		Vector3 view = (target - position).Normalize();
		Vector3 right = view.Cross(up);
		right.y = 0;
		//right.Normalize();
		position -= right * CAMERA_SPEED * dt;
		target -= right * CAMERA_SPEED* dt;
		//limit is -495
		//Left = cameraWorldPos.x - Vector3(1.0f,0.0f,0.0f) * (skyBoxScale.x * 0.5f);
		World = target;
		CharacterMovement.z += (float)(CAMERA_SPEED * dt);
	}

	if(Application::IsKeyPressed('D'))
	{
		Vector3 view = (target - position).Normalize();
		Vector3 right = view.Cross(up);
		right.y = 0;
		//right.Normalize();
		position += right * CAMERA_SPEED * dt;
		target += right * CAMERA_SPEED* dt;
		//Limit is 49
		World = target;
		CharacterMovement.z -= (float)(CAMERA_SPEED * dt);
	}

	if(Application::IsKeyPressed('W'))
	{
		Vector3 view = (target - position).Normalize();
		position += view * CAMERA_SPEED * dt;
		target += view * CAMERA_SPEED * dt;
		//Limit is -889
		CrossHair += target;
		World = position;
		CharacterMovement.x -= (float)(CAMERA_SPEED * dt);
	}

	if(Application::IsKeyPressed('S'))
	{
		/*Vector3 view = (target - position).Normalize();
		position -= view * CAMERA_SPEED * dt;
		target -= view * CAMERA_SPEED * dt;*/
		//Limit is 89
		
		Vector3 view = (target - position).Normalize();
		position -= view * CAMERA_SPEED * dt;
		target -= view * CAMERA_SPEED * dt;
		CrossHair -= target;
		World = position;
		CharacterMovement.x += (float)(CAMERA_SPEED * dt);
	}

	if(Application::IsKeyPressed('N'))
	{
		Vector3 direction = target - position;
		if(direction.Length() > 5)
		{
			Vector3 view = (target - position).Normalized();
			position += view * (float)(CAMERA_SPEED * dt);
		}
	}

	if(Application::IsKeyPressed('M'))
	{
		Vector3 view = (target - position).Normalized();
		position -= view * (float)(CAMERA_SPEED * dt);
	}

	if(Application::IsKeyPressed('R'))
	{
		Reset();
	}
	//std::cout << position << std::endl;
}

void Camera3::Reset()
{
	position = defaultPosition;
	target = defaultTarget;
	up = defaultUp;
}

void Camera3::UpdateCrossHair()
{

}