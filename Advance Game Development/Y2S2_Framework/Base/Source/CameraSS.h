#pragma once
#include "Camera.h"

class CameraSS : public Camera
{
public:
	CameraSS();
	~CameraSS();

	float mouseSensitivity;
	float f_currentPitch;
	float f_pitchLimit;

	Vector3 defaultPos;
	Vector3 defaultTarget;
	Vector3 defaultUp;

	void Init(const Vector3 &pos, const Vector3 &target, const Vector3 &up, const float mouseSenstivity);
	void Update(double dt);

private:
	double mouseX, mouseY;
	double Xaxis, Yaxis;
};

