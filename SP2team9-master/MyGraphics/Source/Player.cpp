/******************************************************************************/
/*!
\file	Player.cpp
\author Princeton Chew
\par	email: 141991A@mymail.nyp.edu.sg
\brief
Player Class
*/
/******************************************************************************/
#include "Player.h"

/******************************************************************************/
/*!
\brief
Default constructor for class
*/
/******************************************************************************/
CPlayer::CPlayer(void)
{
	Money = 50.f;
}

/******************************************************************************/
/*!
\brief
Default destructor for class
*/
/******************************************************************************/
CPlayer::~CPlayer(void)
{
}

/******************************************************************************/
/*!
\brief
Set player's money

\param a - Float of player's money
*/
/******************************************************************************/
void CPlayer::setMoney(float a)
{
	Money = a;
}

/******************************************************************************/
/*!
\brief
Get player's money

\return Float storing player's money
*/
/******************************************************************************/
float CPlayer::getMoney(void)
{
	return Money;
}

/******************************************************************************/
/*!
\brief
Get player's inventory

\return CInventory storing player's inventory
*/
/******************************************************************************/
CInventory& CPlayer::getInventory(void)
{
	return Invent;
}

