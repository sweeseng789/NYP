#pragma once

#include "Map.h"
#include "Vector3.h"
#include "Application.h"
class CHero
{
public:
	CHero();
	~CHero();

	void setData(Vector3 HeroPos, float HeroScale);
	void setMap(CMap* m_cMap);
	void update(double dt, int mapOffSet_x, int mapOffset_y, int tileOffSet_x, int tileOffset_y, int mapFineOffSet_x, int mapFineOffset_y);
	void jump();
	void constrainHero(const int leftBorder, const int rightBorder, const int topBorder, const int bottomBorder, int mapOffSet_x);
	void MoveLeftRight(int mapFineOffSet_x, int tileOffSet_x);
	void ModifyPos_x(float HerePos_x);

	Vector3 getPos();
	float getAnimationCounter();
	bool getInvert();
	bool notInAir();
	bool getAnimate();
	bool getMidAirUp();
	bool getMidAirDown();

private:
	Vector3 HeroPos;
	bool hero_InMidAir_Up;
	bool hero_InMidAir_Down;
	int jumpspeed;
	bool heroAnimationInvert;
	float heroAnimationCounter;
	float HeroScale;
	bool animate;
	float timeDiff;

	CMap* m_cMap;
};