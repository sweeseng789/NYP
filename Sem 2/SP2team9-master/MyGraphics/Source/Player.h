/******************************************************************************/
/*!
\file	Player.h
\author Princeton Chew
\par	email: 141991A@mymail.nyp.edu.sg
\brief
Player Class
*/
/******************************************************************************/
#pragma once
#include "Character.h"
#include "Inventory.h"

/******************************************************************************/
/*!
	Class CPlyaer
\brief
Defines the variables and functions required for the player

*/
/******************************************************************************/
class CPlayer : public CCharacter
{
public:
	CPlayer(void);	//Constructor
	~CPlayer(void);	//Destructor
	void setMoney(float a);	//Set money
	float getMoney(void);	//get money
	CInventory& getInventory(void);	//Get by reference inventory

private:
	CInventory Invent;
	float Money;
};

