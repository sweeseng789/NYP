#pragma once
#include "Vector3.h"
#include "Mesh.h"
#include "Camera3.h"
#include "SSDLC.h"
#include "Mtx44.h"
#include "CharAnimation.h"

class CPlayInfo3PV
{
public:
	CPlayInfo3PV(void);
	virtual ~CPlayInfo3PV(void);

	enum GEOMETRY_TYPE
	{
		GEO_AVATAR,
		NUM_GEOMETRY,
	};

	// Initialise this class instance
	void Init(void);

	// Set Model
	bool SetModel( Mesh* theAvatarMesh );

	// Returns true if the player is on ground
	bool isOnGround(void);
	// Returns true if the player is jumping upwards
	bool isJumpUpwards(void);
	// Returns true if the player is on freefall
	bool isFreeFall(void);
	// Set the player's status to free fall mode
	void SetOnFreeFall(bool isOnFreeFall);
	// Set the player to jumping upwards
	void SetToJumpUpwards(bool isOnJumpUpwards);
	// Stop the player's movement
	void SetToStop(void);
	// Set position x of the player
	void SetPos_x(int pos_x);
	// Set position y of the player
	void SetPos_y(int pos_y);
	// Set position z of the player
	void SetPos_z(int pos_y);	
	// Set Jumpspeed of the player
	void SetJumpspeed(int jumpspeed);

	// Update Movements
	void MoveFrontBack(const bool mode, const float timeDiff);
	void MoveLeftRight(const bool mode, const float timeDiff);

	// Get position x of the player
	int GetPos_x(void);
	// Get position y of the player
	int GetPos_y(void);
	// Get position z of the player
	int GetPos_z(void);
	// Get position of the player
	Vector3 GetPosition();
	// Get direction of the player
	Vector3 GetDirection();
	// Get Jumpspeed of the player
	int GetJumpspeed(void);

	// Update Jump Upwards
	void UpdateJumpUpwards();
	// Update FreeFall
	void UpdateFreeFall();
	// Update
	void UpdateMovement(const unsigned char key, const bool status = true);
	// Update
	void Update(double dt, Camera3 &camera);

	// Constrain the position of the Hero to within the border
	void ConstrainHero(const int leftBorder, const int rightBorder, 
					   const int topBorder, const int bottomBorder, 
					   float timeDiff);

	// Avatar's Mesh
	Mesh*	theAvatarMesh;

	Mesh* head;
	Mesh* torso;
	Mesh* leftArm;
	Mesh* rightArm;
	Mesh* leftLeg;
	Mesh* rightLeg;
	Mesh* rifle;
	Mesh* shield;
	CharAnimation animation;

	float getRotationAngle();

	Vector3 getVel();
	bool isMoving;

private:
	// Hero's information
	Vector3 curPosition;
	Vector3 curDirection;
	Vector3 target;
	Vector3 vel;
	static float velSpeed;
	int jumpspeed;
	float rotateAngle;
	

	bool myKeys[255];
};

