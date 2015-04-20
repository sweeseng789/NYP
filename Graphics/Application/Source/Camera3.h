#ifndef CAMERA_3_H
#define CAMERA_3_H
#include "Camera.h"

/******************************************************************************/
/*!
		Class Camera3:
\brief	Provides methods to rotate around model. This is preferred as it rotates around the model in a circle
*/
/******************************************************************************/

class Camera3 : public Camera
{
public:
	//Camera3 position;
	//Camera3 target;
	//Camera3 up;

	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;

	Vector3 mouse;
	Vector3 CrossHair;
	Vector3 World;
	Vector3 CharacterMovement;
	Vector3 CharacterRotation;
	float angleX;
	float angleY;

	bool nearDoor1;
	bool nearDoor2;
	bool nearDoor3;
	bool nearDoor4;
	bool boundCheckFront, boundCheckBack, boundCheckLeft, boundCheckRight;
	bool HaventOpenDoor, HaventOpenDoor2;
	bool edgeOfWorld1, edgeOfWorld2, edgeOfWorld3, edgeOfWorld4, edgeOfWorld5, edgeOfWorld6, edgeOfWorld7, edgeOfWorld8;
	bool nearAnywhereDoor;
	bool DoraemonActivation;
	float oldY;
	float testing;
	bool light;

	Camera3();
	~Camera3();
	void UpdateCrossHair();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt);
	virtual void Reset();
};

#endif