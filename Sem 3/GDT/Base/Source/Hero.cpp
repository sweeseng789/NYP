#include "Hero.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;


//CHero::CHero():
//	hero_InMidAir_Up(false),
//	hero_InMidAir_Down(false),
//	jumpspeed(0),
//	heroAnimationCounter(0),
//	heroAnimationInvert(0),
//	animate(false),
//	HeroScale(0),
//	HeroPos(NULL),
//	timeDiff(1.f)
//{
//}
//
//
//CHero::~CHero()
//{
//}
//
//void CHero::setData(Vector3 HeroPos, float HeroScale)
//{
//	this->HeroPos = HeroPos;
//	this->HeroScale = HeroScale;
//}
//
//void CHero::setMap(CMap * m_cMap)
//{
//	this->m_cMap = m_cMap;
//}
//
//void CHero::jump()
//{
//	if (Application::IsKeyPressed(' '))
//	{
//		if (hero_InMidAir_Up == false && hero_InMidAir_Down == false)
//		{
//			hero_InMidAir_Up = true;
//			jumpspeed = 12;
//		}
//	}
//}
//
//Vector3 CHero::getPos()
//{
//	return HeroPos;
//}
//
//float CHero::getAnimationCounter()
//{
//	return heroAnimationCounter;
//}
//
//bool CHero::getInvert()
//{
//	return heroAnimationInvert;
//}
//
//bool CHero::notInAir()
//{
//	if (!hero_InMidAir_Up && !hero_InMidAir_Down)
//		return true;
//	else
//		return false;
//}
//
//bool CHero::getAnimate()
//{
//	return animate;
//}
//
//bool CHero::getMidAirDown()
//{
//	return hero_InMidAir_Down;
//}
//
//bool CHero::getMidAirUp()
//{
//	return hero_InMidAir_Up;
//}
//
//void CHero::constrainHero(const int leftBorder, const int rightBorder, const int topBorder, const int bottomBorder, int mapOffSet_x)
//{
//	if (HeroPos.x < leftBorder)
//	{
//		HeroPos.x = leftBorder;
//		mapOffSet_x = mapOffSet_x - (int)(5.f * timeDiff);
//		if (mapOffSet_x < 0)
//			mapOffSet_x = 0;
//	}
//	else if (HeroPos.x > rightBorder / 1.1)
//	{
//		HeroPos.x = rightBorder / 1.1;
//		mapOffSet_x = mapOffSet_x + (int)(5.f * timeDiff);
//		if (mapOffSet_x > 800)
//			mapOffSet_x = 800;
//	}
//
//	if (HeroPos.y < topBorder)
//	{
//		HeroPos.y = topBorder;
//	}
//	else if (HeroPos.y > bottomBorder)
//	{
//		HeroPos.y = bottomBorder;
//	}
//}
//
//void CHero::MoveLeftRight(int mapFineOffSet_x, int tileOffSet_x)
//{
//	int checkPosition_X = (int)ceil(((float)(HeroPos.x + mapFineOffSet_x) / m_cMap->GetTileSize())) + tileOffSet_x;
//	int checkPosition_Y = (int)ceil(((float)HeroPos.y + jumpspeed) / m_cMap->GetTileSize());
//
//	if (Application::IsKeyPressed('A'))
//	{
//		if (m_cMap->theScreenMap[checkPosition_Y][checkPosition_X] != 1)
//		{
//			//Moving Left
//			HeroPos.x = HeroPos.x - (int)(5.0f * timeDiff);
//		}
//
//		heroAnimationInvert = true;
//
//		if (animate == true)
//			heroAnimationCounter -= 0.5f;
//		if (heroAnimationCounter == 0)
//			heroAnimationCounter = 10;
//	}
//
//	if (Application::IsKeyPressed('D'))
//	{
//		if (m_cMap->theScreenMap[checkPosition_Y][checkPosition_X + 1] != 1)
//		{
//			//Moving Right
//			HeroPos.x = HeroPos.x + (int)(5.0f * timeDiff);
//		}
//
//		heroAnimationInvert = false;
//
//		if (animate == true)
//			heroAnimationCounter += 0.5f;
//		if (heroAnimationCounter == 10)
//			heroAnimationCounter = 0;
//	}
//
//	if (Application::IsKeyPressed('A') || Application::IsKeyPressed('D'))
//		animate = true;
//	else
//		animate = false;
//}
//
//void CHero::ModifyPos_x(float HerePos_x)
//{
//	this->HeroPos.x = HerePos_x;
//}
//
//void CHero::update(double dt, int mapOffSet_x, int mapOffset_y, int tileOffSet_x, int tileOffset_y, int mapFineOffSet_x, int mapFineOffset_y)
//{
//	if (hero_InMidAir_Up == false && hero_InMidAir_Down == false)
//	{
//		//Don't Jump
//		int checkPosition_X = (int)ceil(((float)(HeroPos.x + mapFineOffSet_x) / m_cMap->GetTileSize())) + tileOffSet_x;
//		int checkPosition_Y = (int)ceil(((float)HeroPos.y + m_cMap->GetTileSize()) / m_cMap->GetTileSize());
//		if (m_cMap->theScreenMap[checkPosition_Y][checkPosition_X] != 1 && m_cMap->theScreenMap[checkPosition_Y][checkPosition_X + 1] != 1)
//		{
//			hero_InMidAir_Up = false;
//			hero_InMidAir_Down = true;
//			jumpspeed = 10;
//		}
//	}
//	else if (hero_InMidAir_Up == true && hero_InMidAir_Down == false)
//	{
//		// Check if the hero can move up into mid air...
//		int checkPosition_X = (int)ceil(((float)(HeroPos.x + mapFineOffSet_x) / m_cMap->GetTileSize())) + tileOffSet_x;
//		int checkPosition_Y = (int)floor(((float)HeroPos.y - jumpspeed) / m_cMap->GetTileSize());
//		if (m_cMap->theScreenMap[checkPosition_Y][checkPosition_X + 1] == 1 || m_cMap->theScreenMap[checkPosition_Y][checkPosition_X] == 1)
//		{
//			HeroPos.y = (checkPosition_Y + 1.5) * m_cMap->GetTileSize();
//			hero_InMidAir_Up = false;
//			hero_InMidAir_Down = true;
//			jumpspeed = 0;
//		}
//		else
//		{
//			HeroPos.y -= jumpspeed;
//			jumpspeed -= 1;
//			if (jumpspeed == 0)
//			{
//				hero_InMidAir_Up = false;
//				hero_InMidAir_Down = true;
//			}
//		}
//	}
//	else if (hero_InMidAir_Up == false && hero_InMidAir_Down == true)
//	{
//		int checkPosition_X = (int)ceil(((float)(HeroPos.x + mapFineOffSet_x) / m_cMap->GetTileSize())) + tileOffSet_x;
//		int checkPosition_Y = (int)ceil(((float)HeroPos.y + jumpspeed) / m_cMap->GetTileSize());
//		if (m_cMap->theScreenMap[checkPosition_Y][checkPosition_X] == 1 || m_cMap->theScreenMap[checkPosition_Y][checkPosition_X + 1] == 1)
//		{
//			// Since the new position does not allow the hero to move into, then go back to the old position
//			HeroPos.y = (checkPosition_Y - 1) * m_cMap->GetTileSize();
//			hero_InMidAir_Down = false;
//			jumpspeed = 0;
//		}
//		else
//		{
//			HeroPos.y += jumpspeed;
//			jumpspeed += 1;
//		}
//	}
//
//
//	//constrainHero(25, 750, 25, 575, mapOffSet_x);
//	MoveLeftRight(mapFineOffSet_x, tileOffSet_x);
//	jump();
//}

CHero::CHero(void)
	: hero_inMidAir_Up(false)
	, hero_inMidAir_Down(false)
	, jumpspeed(0)
	, heroAnimationCounter(0)
	, heroAnimationInvert(false)
	, mapOffset_x(0)
	, mapOffset_y(0)
	, mapFineOffset_x(0)
	, mapFineOffset_y(0)
{
}
CHero::~CHero(void)
{
}
// Initialise this class instance
void CHero::Init(void)
{
	theHeroPosition.x = 0;
	theHeroPosition.y = 0;
}
// Returns true if the player is on ground
bool CHero::isOnGround(void)
{
	if (hero_inMidAir_Up == false && hero_inMidAir_Down == false)
		return true;
	return false;
}
// Returns true if the player is jumping upwards
bool CHero::isJumpUpwards(void)
{
	if (hero_inMidAir_Up == true && hero_inMidAir_Down == false)
		return true;
	return false;
}
// Returns true if the player is on freefall
bool CHero::isFreeFall(void)
{
	if (hero_inMidAir_Up == false && hero_inMidAir_Down == true)
		return true;
	return false;
}
// Set the player's status to free fall mode
void CHero::SetOnFreeFall(bool isOnFreeFall)
{
	if (isOnFreeFall == true)
	{
		hero_inMidAir_Up = false;
		hero_inMidAir_Down = true;
		jumpspeed = 0;
	}
}

// Set the player to jumping upwards
void CHero::SetToJumpUpwards(bool isOnJumpUpwards)
{
	if (isOnJumpUpwards == true && hero_inMidAir_Up == false && hero_inMidAir_Down == false)
	{
		hero_inMidAir_Up = true;
		hero_inMidAir_Down = false;
		jumpspeed = 15;
	}
}
// Set position x of the player
void CHero::SetPos_x(int pos_x)
{
	theHeroPosition.x = pos_x;
}
// Set position y of the player
void CHero::SetPos_y(int pos_y)
{
	theHeroPosition.y = pos_y;
}
// Set Jumpspeed of the player
void CHero::SetJumpspeed(int jumpspeed)
{
	this->jumpspeed = jumpspeed;
}
// Stop the player's movement
void CHero::SetToStop(void)
{
	hero_inMidAir_Up = false;
	hero_inMidAir_Down = false;
	jumpspeed = 0;
}
/********************************************************************************
Hero Move Up Down
********************************************************************************/
void CHero::MoveUpDown(const bool mode, const float timeDiff)
{
	if (mode)
	{
		theHeroPosition.y = theHeroPosition.y + (int)(5.0f * timeDiff);
	}
	else
	{
		theHeroPosition.y = theHeroPosition.y - (int)(5.0f * timeDiff);
	}
}

/********************************************************************************
Hero Move Left Right
********************************************************************************/
void CHero::MoveLeftRight(const bool mode, const float timeDiff)
{
	if (mode)
	{
		theHeroPosition.x = theHeroPosition.x - (int)(5.0f * timeDiff);
		heroAnimationInvert = true;
		heroAnimationCounter--;
		if (heroAnimationCounter == 0)
			heroAnimationCounter = 3;
	}
	else
	{
		theHeroPosition.x = theHeroPosition.x + (int)(5.0f * timeDiff);
		heroAnimationInvert = false;
		heroAnimationCounter++;
		if (heroAnimationCounter>3)
			heroAnimationCounter = 0;
	}
}
// Get position x of the player
int CHero::GetPos_x(void)
{
	return theHeroPosition.x;
}
// Get position y of the player
int CHero::GetPos_y(void)
{
	return theHeroPosition.y;
}
// Get Jumpspeed of the player
int CHero::GetJumpspeed(void)
{
	return jumpspeed;
}
// Get mapOffset_x
int CHero::GetMapOffset_x(void)
{
	return mapOffset_x;
}
// Get mapOffset_y
int CHero::GetMapOffset_y(void)
{
	return mapOffset_y;
}

// Get mapFineOffset_x
int CHero::GetMapFineOffset_x(void)
{
	return mapFineOffset_x;
}
// Get mapFineOffset_y
int CHero::GetMapFineOffset_y(void)
{
	return mapFineOffset_y;
}
// Update Jump Upwards
void CHero::UpdateJumpUpwards()
{
	theHeroPosition.y -= jumpspeed;
	jumpspeed -= 1;
	if (jumpspeed == 0)
	{
		hero_inMidAir_Up = false;
		hero_inMidAir_Down = true;
	}
}
// Update FreeFall
void CHero::UpdateFreeFall()
{
	theHeroPosition.y += jumpspeed;
	jumpspeed += 1;
}
// Set Animation Invert status of the player
void CHero::SetAnimationInvert(bool heroAnimationInvert)
{
	this->heroAnimationInvert = heroAnimationInvert;
}
// Get Animation Invert status of the player
bool CHero::GetAnimationInvert(void)
{
	return heroAnimationInvert;
}
// Set Animation Counter of the player
void CHero::SetAnimationCounter(int heroAnimationCounter)
{
	this->heroAnimationCounter = heroAnimationCounter;
}
// Get Animation Counter of the player
int CHero::GetAnimationCounter(void)
{
	return heroAnimationCounter;
}

// Constrain the position of the Hero to within the border
void CHero::ConstrainHero(const int leftBorder, const int rightBorder, const int topBorder, const int bottomBorder, float timeDiff)
{
	if (theHeroPosition.x < leftBorder)
	{
		theHeroPosition.x = leftBorder;
		mapOffset_x = mapOffset_x - (int)(5.0f * timeDiff);
		if (mapOffset_x < 0)
			mapOffset_x = 0;
	}
	else if (theHeroPosition.x > rightBorder)
	{
		theHeroPosition.x = rightBorder;
		mapOffset_x = mapOffset_x + (int)(5.0f * timeDiff);
		if (mapOffset_x > 800) // This must be changed to soft-coded
			mapOffset_x = 800;
	}
	if (theHeroPosition.y < topBorder)
		theHeroPosition.y = topBorder;
	else if (theHeroPosition.y > bottomBorder)
		theHeroPosition.y = bottomBorder;
}

/********************************************************************************
Hero Update
********************************************************************************/
void CHero::HeroUpdate(CMap* m_cMap, int tileOffset_x)
{
	//if (hero_inMidAir_Up == false && hero_inMidAir_Down == false)
	//{
	//	//Don't Jump
	//	int checkPosition_X = (int)ceil(((float)(theHeroPosition.x + mapFineOffset_x) / m_cMap->GetTileSize())) + tileOffset_x;
	//	int checkPosition_Y = (int)ceil(((float)theHeroPosition.y + m_cMap->GetTileSize()) / m_cMap->GetTileSize());
	//	if (m_cMap->theScreenMap[checkPosition_Y][checkPosition_X] != 1 && m_cMap->theScreenMap[checkPosition_Y][checkPosition_X + 1] != 1)
	//	{
	//		hero_inMidAir_Up = false;
	//		hero_inMidAir_Down = true;
	//		jumpspeed = 10;
	//	}
	//}
	//else if (hero_inMidAir_Up == true && hero_inMidAir_Down == false)
	//{
	//	// Check if the hero can move up into mid air...
	//	int checkPosition_X = (int)ceil(((float)(theHeroPosition.x + mapFineOffset_x) / m_cMap->GetTileSize())) + tileOffset_x;
	//	int checkPosition_Y = (int)floor(((float)theHeroPosition.y - jumpspeed) / m_cMap->GetTileSize());
	//	if (m_cMap->theScreenMap[checkPosition_Y][checkPosition_X + 1] == 1 || m_cMap->theScreenMap[checkPosition_Y][checkPosition_X] == 1)
	//	{
	//		theHeroPosition.y = (checkPosition_Y + 1.5) * m_cMap->GetTileSize();
	//		hero_inMidAir_Up = false;
	//		hero_inMidAir_Down = true;
	//		jumpspeed = 0;
	//	}
	//	else
	//	{
	//		theHeroPosition.y -= jumpspeed;
	//		jumpspeed -= 1;
	//		if (jumpspeed == 0)
	//		{
	//			hero_inMidAir_Up = false;
	//			hero_inMidAir_Down = true;
	//		}
	//	}
	//}
	//else if (hero_inMidAir_Up == false && hero_inMidAir_Down == true)
	//{
	//	int checkPosition_X = (int)ceil(((float)(theHeroPosition.x + mapFineOffset_x) / m_cMap->GetTileSize())) + tileOffset_x;
	//	int checkPosition_Y = (int)ceil(((float)theHeroPosition.y + jumpspeed) / m_cMap->GetTileSize());
	//	if (m_cMap->theScreenMap[checkPosition_Y][checkPosition_X] == 1 || m_cMap->theScreenMap[checkPosition_Y][checkPosition_X + 1] == 1)
	//	{
	//		// Since the new position does not allow the hero to move into, then go back to the old position
	//		theHeroPosition.y = (checkPosition_Y - 1) * m_cMap->GetTileSize();
	//		hero_inMidAir_Down = false;
	//		jumpspeed = 0;
	//	}
	//	else
	//	{
	//		theHeroPosition.y += jumpspeed;
	//		jumpspeed += 1;
	//	}
	//}
	// Update Hero's info
	if (hero_inMidAir_Up == false && hero_inMidAir_Down == false)
	{
		// Don't jump
		int checkPosition_X = (int)((mapOffset_x + theHeroPosition.x) / m_cMap->GetTileSize());
		int checkPosition_Y = m_cMap->GetNumOfTiles_Height() - (int)ceil((float)(theHeroPosition.y + m_cMap->GetTileSize() + jumpspeed) / m_cMap->GetTileSize());
		if ((m_cMap->theScreenMap[checkPosition_Y][checkPosition_X] != 1) || (m_cMap->theScreenMap[checkPosition_Y][checkPosition_X + 1] != 1))
		{
			hero_inMidAir_Up = false;
			hero_inMidAir_Down = true;
			jumpSpeed = 0;
			jumpspeed = 0;
		}
	}
	else if (hero_inMidAir_Up == true && hero_inMidAir_Down == false)
	{
		// Check if the hero can move up into mid air...
		int checkPosition_X = (int)((mapOffset_x + theHeroPosition.x) / m_cMap ->GetTileSize());
		int checkPosition_Y = m_cMap->GetNumOfTiles_Height() - (int)ceil((float)(theHeroPosition.y + m_cMap->GetTileSize() + jumpspeed) / m_cMap->GetTileSize());
		if ((m_cMap->theScreenMap[checkPosition_Y][checkPosition_X] == 1) ||
			(m_cMap->theScreenMap[checkPosition_Y][checkPosition_X + 1] == 1))
		{
			// Since the new position does not allow the hero to move into, then go back to the old position
				theHeroPosition.y = ((int)(theHeroPosition.y / m_cMap->GetTileSize())) * m_cMap->GetTileSize();
			hero_inMidAir_Up = false;
			jumpspeed = 0;
		}
		else
		{
			theHeroPosition.y += jumpspeed;
			jumpspeed -= 1;
			if (jumpspeed == 0)
			{
				hero_inMidAir_Up = false;
				hero_inMidAir_Down = true;
			}
		}
	}
	else if (hero_inMidAir_Up == false && hero_inMidAir_Down == true)
	{
		// Check if the hero is still in mid air...
		int checkPosition_X = (int)((mapOffset_x + theHeroPosition.x) / m_cMap ->GetTileSize());
		if (checkPosition_X < 0)
			checkPosition_X = 0;
		if (checkPosition_X > m_cMap->getNumOfTiles_MapWidth())
			checkPosition_X = m_cMap->getNumOfTiles_MapWidth();
		int checkPosition_Y = m_cMap->GetNumOfTiles_Height() - (int)ceil((float)
			(theHeroPosition.y - jumpspeed) / m_cMap->GetTileSize());
		if (checkPosition_Y < 0)
			checkPosition_Y = 0;
		if (checkPosition_Y > m_cMap->GetNumOfTiles_Height())
			checkPosition_Y = m_cMap->GetNumOfTiles_Height();
		if (m_cMap->theScreenMap[checkPosition_Y][checkPosition_X] == 1)
		{
			// Since the new position does not allow the hero to move into, then go back to the old position
				theHeroPosition.y = ((int)(theHeroPosition.y / m_cMap->GetTileSize())) * m_cMap->GetTileSize();
			hero_inMidAir_Down = false;
			jumpspeed = 0;
		}
		else
		{
			theHeroPosition.y -= jumpspeed;
			jumpspeed += 1;
		}
	}

	ConstrainHero(25, 750, 25, 575, 1.0f);
	// Calculate the fine offset
	mapFineOffset_x = mapOffset_x % m_cMap->GetTileSize();

	if (Application::IsKeyPressed(VK_F6))
	{
		ofstream saveData;
		saveData.open("Save Data/Hero.txt");
		if (saveData.is_open())
		{
			saveData << "HeroPos_x: " << theHeroPosition.x << endl;
			saveData << "HeroPos_y: " << theHeroPosition.y;
		}
		saveData.close();
	}
}

void CHero::readFromFile()
{
	ifstream saveData;
	string line;
	string line2;
	saveData.open("Save Data/Hero.txt");
	if (saveData.is_open())
	{
		while (getline(saveData, line, ' '))
		{
			cout << line << endl;
		}
	}
	saveData.close();
}