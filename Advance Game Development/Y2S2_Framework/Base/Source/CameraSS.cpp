#include "CameraSS.h"
#include "SSDLC.h"
#include "Application.h"


CameraSS::CameraSS()
{
}


CameraSS::~CameraSS()
{
}

void CameraSS::Init(const Vector3 &pos, const Vector3 &target, const Vector3 &up, const float mouseSenstivity)
{
	this->position = defaultPos = pos;
	this->target = defaultTarget = target;
	Vector3 view = (target - pos).Normalized();
	Vector3 right = view.Cross(up);
	right.y = 0;
	right.Normalize();
	this->up = defaultUp = right.Cross(view).Normalized();
	this->mouseSensitivity = mouseSenstivity;
	mouseX = mouseY = 0.0;

	f_currentPitch = SSDLC::findAngleFromPos(target, pos, false);
	f_pitchLimit = 80.f;
}

void CameraSS::Update(double dt)
{
	double Xaxis = (Application::getWindow_Width() * 0.5);
	double Yaxis = (Application::getWindow_Height() * 0.5);
	Application::GetMousePos(mouseX, mouseY);
	mouseX = Xaxis - mouseX;
	mouseY = Yaxis - mouseY;
	mouseX *= 0.1;
	mouseY *= 0.1;
	mouseX *= static_cast<double>(mouseSensitivity);
	mouseY *= static_cast<double>(mouseSensitivity);

	if (mouseX != 0)
	{
		Mtx44 rotation;
		target -= position;
		rotation.SetToRotation(mouseX, 0, 1, 0);
		target = rotation * target;
		up = rotation * up;
		target += position;
	}

	if (mouseY != 0)
	{
		if (mouseY + f_currentPitch > f_pitchLimit && mouseY > 0)
		{
			mouseY = f_pitchLimit - f_currentPitch;
			if (f_currentPitch >= f_pitchLimit)
			{
				mouseY = 0.f;
			}
		}
		else if (mouseY + f_currentPitch < -f_pitchLimit && mouseY < 0)
		{
			mouseY = -f_pitchLimit - f_currentPitch;
			if (f_currentPitch <= -f_pitchLimit)
			{
				mouseY = 0.f;
			}
		}

		if(mouseY != 0)
		{
			Vector3 view = (target - position).Normalized();
			Vector3 right = view.Cross(up);
			right.y = 0;
			right.Normalize();
			up = right.Cross(view).Normalized();
			Mtx44 rotation;
			target -= position;
			f_currentPitch += mouseY;
			rotation.SetToRotation(static_cast<float>(mouseY), right.x, right.y, right.z);
			target = rotation * target;
			target += position;
		}
	}

	Application::setMousePos(Xaxis, Yaxis);
}