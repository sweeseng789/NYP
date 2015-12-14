#pragma once
#include "GameObject.h"

class CPlayInfo3PV : public CGameObject
{
	enum MODE
	{
		ATTACK,
		STANDBY
	};

	enum STAGES
	{
		FAWithBooster,
		FAWithoutBooster,
		AWAKENED
	};
public:
	CPlayInfo3PV(void);
	virtual ~CPlayInfo3PV(void);


	void Init();
	void Exit();
	void Update(const double &dt, Camera3 &camera, const float& terrainY);
	void UpdateMovement(const unsigned char key, const bool status = true);
	void modelAnimationUpdate(Camera3 &camera);
	void controlUpdate(const double& dt, Camera3 &camera, const float& terrainY);

	void switchMode();
	float getAngle();
	bool isAttackMode();
	bool isStandByMode();
private:
	//bool
	bool myKeys[255];
	bool isFlying;

	//float
	float angle;

	//Struct variables
	MODE mode;
	STAGES stage;
};

