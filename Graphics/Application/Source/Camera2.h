#ifndef CAMERA_2_H
#define CAMERA_2_H

#include "Camera.h"

/******************************************************************************/
/*!
		Class Camera2:
\brief	Provides methods to rotate around model. This is preferred as it rotates around the model in a circle
*/
/******************************************************************************/

class Camera2 : public Camera
{
public:
	//Vector3 position;
	//Vector3 target;
	//Vector3 up;

	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
	int mousex;
	int mousey;
	int oldMousex;
	int oldMousey;
	float testing;
	Vector3 mouse;

	Camera2();
	~Camera2();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt);
	virtual void Reset();
};

#endif