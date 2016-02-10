#pragma once
#include "GameObject.h"

class AI : public CGameObject
{
public:
	enum  AI_STATES
	{
		s_IDLE,
		s_PATROL,
		s_COLLIDED,
	};
	AI();
	AI(Vector3 pos);
	~AI();

	void Update(double dt, Vector3 playerPos, const float& terrainY);
	float getAngle();

	void animationUpdate(const double &dt);

	void patrolUpdate(const double &dt);
	void collideUpdate(const double &dt);

	void switchState(AI_STATES currentState);
private:
	AI_STATES currentState;
	AI_STATES previousState;

	float movementTime;
	float currentTime;
	Vector3 moveDir;
	float rotateAngle;
};

