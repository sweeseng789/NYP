#include "Hero.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;


CHero::CHero():
	hero_InMidAir_Up(false),
	hero_InMidAir_Down(false),
	jumpspeed(0),
	heroAnimationCounter(0),
	heroAnimationInvert(0),
	animate(false),
	HeroScale(0),
	HeroPos(NULL),
	timeDiff(1.f)
{
}


CHero::~CHero()
{
}

void CHero::setData(Vector3 HeroPos, float HeroScale)
{
	this->HeroPos = HeroPos;
	this->HeroScale = HeroScale;
}

void CHero::setMap(CMap * m_cMap)
{
	this->m_cMap = m_cMap;
}

void CHero::jump()
{
	if (Application::IsKeyPressed(' '))
	{
		if (hero_InMidAir_Up == false && hero_InMidAir_Down == false)
		{
			hero_InMidAir_Up = true;
			jumpspeed = 12;
		}
	}
}

Vector3 CHero::getPos()
{
	return HeroPos;
}

float CHero::getAnimationCounter()
{
	return heroAnimationCounter;
}

bool CHero::getInvert()
{
	return heroAnimationInvert;
}

bool CHero::notInAir()
{
	if (!hero_InMidAir_Up && !hero_InMidAir_Down)
		return true;
	else
		return false;
}

bool CHero::getAnimate()
{
	return animate;
}

bool CHero::getMidAirDown()
{
	return hero_InMidAir_Down;
}

bool CHero::getMidAirUp()
{
	return hero_InMidAir_Up;
}

void CHero::constrainHero(const int leftBorder, const int rightBorder, const int topBorder, const int bottomBorder, int mapOffSet_x)
{
	if (HeroPos.x < leftBorder)
	{
		HeroPos.x = leftBorder;
		mapOffSet_x = mapOffSet_x - (int)(5.f * timeDiff);
		if (mapOffSet_x < 0)
			mapOffSet_x = 0;
	}
	else if (HeroPos.x > rightBorder / 1.1)
	{
		HeroPos.x = rightBorder / 1.1;
		mapOffSet_x = mapOffSet_x + (int)(5.f * timeDiff);
		if (mapOffSet_x > 800)
			mapOffSet_x = 800;
	}

	if (HeroPos.y < topBorder)
	{
		HeroPos.y = topBorder;
	}
	else if (HeroPos.y > bottomBorder)
	{
		HeroPos.y = bottomBorder;
	}
}

void CHero::MoveLeftRight(int mapFineOffSet_x, int tileOffSet_x)
{
	int checkPosition_X = (int)ceil(((float)(HeroPos.x + mapFineOffSet_x) / m_cMap->GetTileSize())) + tileOffSet_x;
	int checkPosition_Y = (int)ceil(((float)HeroPos.y + jumpspeed) / m_cMap->GetTileSize());

	if (Application::IsKeyPressed('A'))
	{
		if (m_cMap->theScreenMap[checkPosition_Y][checkPosition_X] != 1)
		{
			//Moving Left
			HeroPos.x = HeroPos.x - (int)(5.0f * timeDiff);
		}

		heroAnimationInvert = true;

		if (animate == true)
			heroAnimationCounter -= 0.5f;
		if (heroAnimationCounter == 0)
			heroAnimationCounter = 10;
	}

	if (Application::IsKeyPressed('D'))
	{
		if (m_cMap->theScreenMap[checkPosition_Y][checkPosition_X + 1] != 1)
		{
			//Moving Right
			HeroPos.x = HeroPos.x + (int)(5.0f * timeDiff);
		}

		heroAnimationInvert = false;

		if (animate == true)
			heroAnimationCounter += 0.5f;
		if (heroAnimationCounter == 10)
			heroAnimationCounter = 0;
	}

	if (Application::IsKeyPressed('A') || Application::IsKeyPressed('D'))
		animate = true;
	else
		animate = false;
}

void CHero::ModifyPos_x(float HerePos_x)
{
	this->HeroPos.x = HerePos_x;
}

void CHero::update(double dt, int mapOffSet_x, int mapOffset_y, int tileOffSet_x, int tileOffset_y, int mapFineOffSet_x, int mapFineOffset_y)
{
	if (hero_InMidAir_Up == false && hero_InMidAir_Down == false)
	{
		//Don't Jump
		/*int checkPosition_X = (int)ceil(((float)(HeroPos.x + mapFineOffSet_x) / m_cMap->GetTileSize())) + tileOffSet_x;
		int checkPosition_Y = (int)ceil(((float)HeroPos.y + m_cMap->GetTileSize()) / m_cMap->GetTileSize());
		if (m_cMap->theScreenMap[checkPosition_Y][checkPosition_X] != 1 && m_cMap->theScreenMap[checkPosition_Y][checkPosition_X + 1] != 1)
		{
			hero_InMidAir_Up = false;
			hero_InMidAir_Down = true;
			jumpspeed = 10;
		}*/
	}
	else if (hero_InMidAir_Up == true && hero_InMidAir_Down == false)
	{
		// Check if the hero can move up into mid air...
		int checkPosition_X = (int)ceil(((float)(HeroPos.x + mapFineOffSet_x) / m_cMap->GetTileSize())) + tileOffSet_x;
		int checkPosition_Y = (int)floor(((float)HeroPos.y - jumpspeed) / m_cMap->GetTileSize());
		if (m_cMap->theScreenMap[checkPosition_Y][checkPosition_X + 1] == 1 || m_cMap->theScreenMap[checkPosition_Y][checkPosition_X] == 1)
		{
			HeroPos.y = (checkPosition_Y + 1.5) * m_cMap->GetTileSize();
			hero_InMidAir_Up = false;
			hero_InMidAir_Down = true;
			jumpspeed = 0;
		}
		else
		{
			HeroPos.y -= jumpspeed;
			jumpspeed -= 1;
			if (jumpspeed == 0)
			{
				hero_InMidAir_Up = false;
				hero_InMidAir_Down = true;
			}
		}
	}
	else if (hero_InMidAir_Up == false && hero_InMidAir_Down == true)
	{
		int checkPosition_X = (int)ceil(((float)(HeroPos.x + mapFineOffSet_x) / m_cMap->GetTileSize())) + tileOffSet_x;
		int checkPosition_Y = (int)ceil(((float)HeroPos.y + jumpspeed) / m_cMap->GetTileSize());
		if (m_cMap->theScreenMap[checkPosition_Y][checkPosition_X] == 1 || m_cMap->theScreenMap[checkPosition_Y][checkPosition_X + 1] == 1)
		{
			// Since the new position does not allow the hero to move into, then go back to the old position
			HeroPos.y = (checkPosition_Y - 1) * m_cMap->GetTileSize();
			hero_InMidAir_Down = false;
			jumpspeed = 0;
		}
		else
		{
			HeroPos.y += jumpspeed;
			jumpspeed += 1;
		}
	}


	//constrainHero(25, 750, 25, 575, mapOffSet_x);
	MoveLeftRight(mapFineOffSet_x, tileOffSet_x);
	jump();
}