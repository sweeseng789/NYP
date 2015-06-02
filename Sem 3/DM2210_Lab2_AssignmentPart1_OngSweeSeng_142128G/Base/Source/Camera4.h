#pragma once

#include "Camera.h"
#include "Vector3.h"
#include <gl/glew.h>

class Camera4
{
public:
	//Enum
	enum CAM_TYPE {LAND_CAM, AIR_CAM};

	Camera4(void);
	Camera4(CAM_TYPE ct);
	~Camera4(void);

	void SetCameraType(CAM_TYPE ct);
	void Reset();
	void Update();
	Vector3 GetPosition();
	void SetPosition(GLfloat x, GLfloat y, GLfloat z);
	void SetDirection(GLfloat x, GLfloat y, GLfloat z);

	void Pitch(GLfloat theta);
	void Yaw(GLfloat theta);
	void Roll(GLfloat theta);
	void Walk(GLfloat delta);
	void Strafe(GLfloat delta);
	void Fly(GLfloat delta);

private:
	//Enum
	CAM_TYPE CameraType;

	//Vector3
	Vector3 Position;
	Vector3 Along;
	Vector3 Up;
	Vector3 Forward;
};

