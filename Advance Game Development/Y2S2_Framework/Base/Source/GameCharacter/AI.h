#pragma once
#include "GameObject.h"

class AI : public CGameObject
{
public:
	enum  AI_STATES
	{
		s_PATROL,
		s_ALERTED,
		s_ATTACK,
		s_COLLIDED,
	};
	AI();
	AI(Vector3 pos);
	~AI();

	void Update(double dt, Vector3 playerPos, const float& terrainY);
	float getAngle();

	void animationUpdate(const double &dt);

	void patrolUpdate(const double &dt);
	void alertUpdate(const double &dt, Vector3 playerPos);
	void collideUpdate(const double &dt);
	void attackUpdate(const double &dt, Vector3 playerPos);

	void switchState(AI_STATES currentState);
	float worldSize;

	std::string renderState();
	Vector3 getDestination();
	float getAttackRange();
	float getAlertRange();
	float getEscapeRange()
	{
		return ESCAPE_RANGE;
	}

	bool isPatrol()
	{
		if (currentState == s_PATROL)
			return true;
		return false;
	}
	bool isAlerted()
	{
		if (currentState == s_ALERTED)
			return true;
		return false;
	}
	bool isAttacking()
	{
		if (currentState == s_ATTACK)
			return true;
		return false;
	}

	bool getShooting();
	void resetShooting();
private:
	AI_STATES currentState;
	AI_STATES previousState;

	Vector3 playerPosition;
	Vector3 destination;
	float rotateAngle;

	bool readyToShoot;
	float shootingTime;
	float currentTime_Shooting;

	static float ALERT_RANGE;
	static float ATTACK_RANGE;
	static float ESCAPE_RANGE;
};

