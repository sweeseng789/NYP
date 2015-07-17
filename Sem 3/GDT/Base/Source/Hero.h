#pragma once
#include <fstream>
#include "Map.h"
#include "Vector3.h"
#include "Application.h"

using std::ostream;
using std::ifstream;

class CHero
{
public:
	CHero();
	~CHero();

	enum GEOMETRY_TYPE
	{
		GEO_HERO_DEFAULT,
		GEO_HERO_SHOOT,
		GEO_HERO_WALK_FRAME01,
		GEO_HERO_WALK_FRAME02,
		GEO_HERO_WALK_FRAME03,
		GEO_HERO_WALK_FRAME04,
		GEO_HERO_WALK_FRAME05,
		GEO_HERO_WALK_FRAME06,
		GEO_HERO_WALK_FRAME07,
		GEO_HERO_WALK_FRAME08,
		GEO_HERO_WALK_FRAME09,
		GEO_HERO_WALK_FRAME10,
		GEO_HERO_JUMP,
		GEO_HERO_LAND,
		GEO_HERO_DEFAULT_INVERSE,
		GEO_HERO_SHOOT_INVERSE,
		GEO_HERO_WALK_FRAME01_INVERSE,
		GEO_HERO_WALK_FRAME02_INVERSE,
		GEO_HERO_WALK_FRAME03_INVERSE,
		GEO_HERO_WALK_FRAME04_INVERSE,
		GEO_HERO_WALK_FRAME05_INVERSE,
		GEO_HERO_WALK_FRAME06_INVERSE,
		GEO_HERO_WALK_FRAME07_INVERSE,
		GEO_HERO_WALK_FRAME08_INVERSE,
		GEO_HERO_WALK_FRAME09_INVERSE,
		GEO_HERO_WALK_FRAME10_INVERSE,
		GEO_HERO_JUMP_INVERSE,
		GEO_HERO_LAND_INVERSE,
		GEO_HERO_BULLET,
		NUM_GEOMETRY,
	};


	/*void setData(Vector3 HeroPos, float HeroScale);
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
	bool getMidAirDown();*/

	//GDT stuff

	// Initialise this class instance
	void Init(void);
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
	// Set Jumpspeed of the player
	void SetJumpspeed(int jumpspeed);

	// Update Movements
	void MoveUpDown(const bool mode, const float timeDiff);
	void MoveLeftRight(const bool mode, const float timeDiff);
	// Get position x of the player
	int GetPos_x(void);
	// Get position y of the player
	int GetPos_y(void);
	// Get Jumpspeed of the player
	int GetJumpspeed(void);
	// Get mapOffset_x
	int GetMapOffset_x(void);
	// Get mapOffset_y
	int GetMapOffset_y(void);
	// Get mapFineOffset_x
	int GetMapFineOffset_x(void);
	// Get mapFineOffset_y
	int GetMapFineOffset_y(void);
	// Update Jump Upwards
	void UpdateJumpUpwards();
	// Update FreeFall
	void UpdateFreeFall();
	// Hero Update
	void HeroUpdate(CMap* m_cMap, int tileOffset_x);
	// Set Animation Invert status of the player
	void SetAnimationInvert(bool heroAnimationInvert);
	// Get Animation Invert status of the player
	bool GetAnimationInvert(void);
	// Set Animation Counter of the player
	void SetAnimationCounter(int heroAnimationCounter);
	// Get Animation Counter of the player
	int GetAnimationCounter(void);
	// Constrain the position of the Hero to within the border
	void ConstrainHero(const int leftBorder, const int rightBorder, const int topBorder, const int bottomBorder, float timeDiff);

	void readFromFile();
private:
	Vector3 HeroPos;
	bool hero_InMidAir_Up;
	bool hero_InMidAir_Down;
	int jumpSpeed;
	bool heroAnimationinvert;
	float heroAnimationcounter;
	float HeroScale;
	bool animate;
	float timeDiff;

	CMap* m_cMap;

	//GDT Stuff
	// Hero's information
	Vector3 theHeroPosition;
	int jumpspeed;
	bool hero_inMidAir_Up;
	bool hero_inMidAir_Down;
	bool heroAnimationInvert;
	int heroAnimationCounter;
	// For scrolling.
	int mapOffset_x, mapOffset_y;
	int mapFineOffset_x, mapFineOffset_y;
};