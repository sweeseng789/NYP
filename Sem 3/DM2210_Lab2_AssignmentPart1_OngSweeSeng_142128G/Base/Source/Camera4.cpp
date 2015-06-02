#include "Camera4.h"


Camera4::Camera4(void)
{
}

Camera4::Camera4(CAM_TYPE ct)
{
	SetCameraType(ct);
	Reset();
}


Camera4::~Camera4(void)
{
}

void Camera4::SetCameraType(CAM_TYPE ct)
{
	CameraType = ct;
}

void Camera4::Reset()
{
	Position = Vector3(0.0, 0.0, 0.0);
	Along = Vector3(1.0, 0.0, 0.0);
	Up = Vector3(0.0, 1.0, 0.0);
	Forward = Vector3(0.0, 0.0, -1.0);
}

void Camera4::Update()
{
	gluLookAt(	Position.x, Position.y, Position.z,
				Position.x + Forward.x, Position.y + Forward.y, Position.z + Forward.z,
				0.0f, 1.0f, 0.0f);
}

Vector3 Camera4::GetPosition()
{
	return this->Position;
}

void Camera4::SetPosition(GLfloat x, GLfloat y, GLfloat z)
{
	this->Position.Set(x, y, z);
}

void Camera4::SetDirection(GLfloat x, GLfloat y, GLfloat z)
{
	this->Forward.Set(x, y, z);
}

void Camera4::Pitch(GLfloat theta)
{
	Forward.y -= theta;
	if (Forward.y > 3.142f)
		Forward.y = 3.142f;
	else if (Forward.y < -3.142f)
		Forward.y = -3.142f;
}

void Camera4::Yaw(GLfloat theta)
{
	Forward.x = sin(- theta);
	Forward.z = -cos(- theta);
}

void Camera4::Roll(GLfloat theta)
{

}

void Camera4::Walk(GLfloat delta)
{
	Position.Set(	Position.x + Forward.x * delta,
					Position.y + Forward.y * delta,
					Position.z + Forward.z * delta);
}

void Camera4::Strafe(GLfloat delta)
{
	Along = Forward.Cross(Up);
	Along.Normalize();
	Position.Set (	Position.x + Along.x * delta,
					Position.y + Along.y * delta,
					Position.z + Along.z * delta);
}

void Camera4::Fly(GLfloat delta)
{
}