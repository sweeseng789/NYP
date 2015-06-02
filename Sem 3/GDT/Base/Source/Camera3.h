#ifndef CAMERA_3_H
#define CAMERA_3_H

#include "Camera.h"

class Camera3 : public Camera
{
public:
	//Enum
	enum CAM_TYPE {	LAND_CAM, 
					AIR_CAM,
					NUM_CAM_TYPE};
	//Vector3 position;
	//Vector3 target;
	//Vector3 up;

	Vector3 defaultPosition;
	Vector3 defaultTarget;
	Vector3 defaultUp;
	Vector3 direction;

	Camera3();
	~Camera3();
	virtual void Init(const Vector3& pos, const Vector3& target, const Vector3& up);
	virtual void Update(double dt);
	virtual void Reset();
	virtual void MoveForward(const double dt);
	virtual void MoveBackward(const double dt);
	virtual void MoveLeft(const double dt);
	virtual void MoveRight(const double dt);
	virtual void SetCameraType(CAM_TYPE sCameraType);
	virtual CAM_TYPE GetCameraType();
	//virtual void TurnLeft(const double dt);
	//virtual void TurnRight(const double dt);
	virtual void LookUp(const double dt);
	virtual void LookDown(const double dt);
	virtual void SpinClockWise(const double dt);
	virtual void SpinCounterClockWise(const double dt);
	virtual void Jump(const double dt);

	virtual void Pitch(const double dt);
	virtual void Yaw(const double dt);
	//virtual void Roll(const double dt);
	virtual void Walk(const double dt);
	virtual void Strafe(const double dt);
	/*virtual void Jump(const double dt);*/
	virtual void UpdateJump(const double dt);
	virtual void UpdateScope(const double dt);

	bool pressedSpace;
	bool currentlyJumping;
	bool currentlyFalling;
	// Update Camera status
	virtual void UpdateStatus(const unsigned char key);
private:
	bool myKeys[255];
	CAM_TYPE sCameraType;

	//For jumping
	bool m_bJumping;
	bool m_Scope;
	bool crouched;
	bool crouching;
	bool scoped;
	bool scoping;
	float GRAVITY;
	float JumpVel;
	float JUMPMAXSPEED, JUMPACCEL;
};

#endif