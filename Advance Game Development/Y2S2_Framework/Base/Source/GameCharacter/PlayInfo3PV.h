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
	void Update(const double &dt, Camera3 &camera);
	void UpdateMovement(const unsigned char key, const bool status = true);

	void switchMode();
	float getAngle();
	bool isAttackMode();
	bool isStandByMode();
private:
	//bool
	bool myKeys[255];

	//float
	float angle;

	//Struct variables
	MODE mode;
	STAGES stage;
};

