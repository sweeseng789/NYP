/******************************************************************************/
/*!
\file	Character.cpp
\author Ong Swee Seng
\par	email: 142128G@mymail.nyp.edu.sg
\brief
MenuClass Class
*/
/******************************************************************************/
#include "MenuClass.h"

/******************************************************************************/
/*!
\brief
Default constructor for Menu
*/
/******************************************************************************/
Menu::Menu(void)
{
	StartGameTrue =
	StartGameFalse =
	EndGameTrue =
	EndGameFalse =
	Arrow =
	MenuBackground =
	GameOver = 
	Win = 0;

	pointToGame = true;
	pointToExit = false;
	showMenu = true;
	GameOverState = false;
	pointToControl = false;
	showControl = false;
	WinState = false;
}

Menu::~Menu(void)
{
}
/******************************************************************************/
/*!
\brief
Sets the menu background
*/
/******************************************************************************/
void Menu::SetBackground(int newObj)
{
	MenuBackground = newObj;
}
/******************************************************************************/
/*!
\brief
Returns the menu background
*/
/******************************************************************************/
int Menu::getBackgroundMesh()
{
	return MenuBackground;
}
/******************************************************************************/
/*!
\brief
Creates the arrow for the menu
*/
/******************************************************************************/
void Menu::SetArrow(int newObj)
{
	Arrow = newObj;
}
/******************************************************************************/
/*!
\brief
Returns the arrow obj
*/
/******************************************************************************/
int Menu::getArrowMesh()
{
	return Arrow;
}

/******************************************************************************/
/*!
\brief
Sets the state when game starts = true
*/
/******************************************************************************/
void Menu::SetStartGameTrue(int newObj)
{
	StartGameTrue = newObj;
}
/******************************************************************************/
/*!
\brief
Returns the game menu
*/
/******************************************************************************/
int Menu::getStartGameTrueMesh()
{
	return StartGameTrue;
}

/******************************************************************************/
/*!
\brief
Returns the menu obj
*/
/******************************************************************************/
void Menu::SetStartGameFalse(int newObj)
{
	StartGameFalse = newObj;
}
/******************************************************************************/
/*!
\brief
Returns the game state 
*/
/******************************************************************************/
int Menu::getStartGameFalseMesh()
{
	return StartGameFalse;
}

/******************************************************************************/
/*!
\brief
sets game state
*/
/******************************************************************************/
void Menu::SetEndGameTrue(int newObj)
{
	EndGameTrue = newObj;
}
/******************************************************************************/
/*!
\brief
returns end game state
*/
/******************************************************************************/
int Menu::getEndGameTrueMesh()
{
	return EndGameTrue;
}
/******************************************************************************/
/*!
\brief
set end game state
*/
/******************************************************************************/
void Menu::SetEndGameFalse(int newObj)
{
	EndGameFalse = newObj;
}
/******************************************************************************/
/*!
\brief
returns end game state
*/
/******************************************************************************/
int Menu::getEndGameFalseMesh()
{
	return EndGameFalse;
}
/******************************************************************************/
/*!
\brief
returns if pointer points to start game
*/
/******************************************************************************/
bool Menu::getPointToGame()
{
	return pointToGame;
}
/******************************************************************************/
/*!
\brief
bool if pointer is at exit or not
*/
/******************************************************************************/
bool Menu::getPointToExit()
{
	return pointToExit;
}
/******************************************************************************/
/*!
\brief
returns to game menu
*/
/******************************************************************************/
bool Menu::getShowMenuStatus()
{
	return showMenu;
}
/******************************************************************************/
/*!
\brief
returns game over obj
*/
/******************************************************************************/
void Menu::SetGameOverMesh(int newObj)
{
	GameOver = newObj;
}
/******************************************************************************/
/*!
\brief
returns Game over state
*/
/******************************************************************************/
int Menu::getGameOverMesh()
{
	return GameOver;
}
/******************************************************************************/
/*!
\brief
Sets control obj
*/
/******************************************************************************/
void Menu::SetControlMesh(int newObj)
{
	Control = newObj;
}
/******************************************************************************/
/*!
\brief
returns Control state
*/
/******************************************************************************/
int Menu::getControlMesh()
{
	return Control;
}
/******************************************************************************/
/*!
\brief
Set pointer to control 
*/
/******************************************************************************/
void Menu::SetPointControlTrue(int newObj)
{
	PointToControlTrue = newObj;
}
/******************************************************************************/
/*!
\brief
returns if pointer is at control
*/
/******************************************************************************/
int Menu::getControlTrueMesh()
{
	return PointToControlTrue;
}
/******************************************************************************/
/*!
\brief
Sets pointer boolean
*/
/******************************************************************************/
void Menu::SetPointControlFalse(int newObj)
{
	PointToControlFalse = newObj;
}
/******************************************************************************/
/*!
\brief
returns if pointer is at control
*/
/******************************************************************************/
int Menu::getControlFalseMesh()
{
	return PointToControlFalse;
}
/******************************************************************************/
/*!
\brief
returns the showcontrol bool
*/
/******************************************************************************/
bool Menu::getShowContorlStatus()
{
	return showControl;
}
/******************************************************************************/
/*!
\brief
returns if pointer is pointing to control
/******************************************************************************/
bool Menu::getPointToContorl()
{
	return pointToControl;
}
/******************************************************************************/
/*!
\brief
Sets winning state
*/
/******************************************************************************/
void Menu::SetWinMesh(int newObj)
{
	Win = newObj;
}
/******************************************************************************/
/*!
\brief
returns Winning state
*/
/******************************************************************************/
int Menu::getWinMesh()
{
	return Win;
}
/******************************************************************************/
/*!
\brief
Sets-up the whole menu. Pointer and words (Game start , controls , exit)
*/
/******************************************************************************/
void Menu::update(double dt)
{
	static float elapsedTime1 = 0, elapsedTime2 = 0;
	elapsedTime1 = fmod(Timer.getElapsedTime(), 1);

	if (elapsedTime2 <= 0.5)
	{
		elapsedTime2 += elapsedTime1;
	}
	else
	{
		elapsedTime2 += 0;
	}

	//======================UP ARROW KEY==================//
	if(Application::IsKeyPressed(VK_UP) && elapsedTime2 >= 0.5)
	{
		//=======================Pointing to start game====================//
		if (pointToGame == true && pointToExit == false && pointToControl == false)
		{
			pointToGame = false;
			pointToExit = true;
			pointToControl = false;
		}//=======================Pointing to Controls====================//
		else if (pointToGame == false && pointToExit == false && pointToControl == true)
		{
			pointToGame = true;
			pointToExit = false;
			pointToControl = false;
		}//=======================Pointing to End game====================//
		else if (pointToGame == false && pointToExit == true && pointToControl == false)
		{
			pointToGame = false;
			pointToExit = false;
			pointToControl = true;
		}
		elapsedTime2 -= 0.5;
	}

	//======================DOWN ARROW KEY==================//
	if(Application::IsKeyPressed(VK_DOWN) && elapsedTime2 >= 0.5)
	{
		//=======================Pointing to start game====================//
		if (pointToGame == true && pointToExit == false && pointToControl == false)
		{
			pointToGame = false;
			pointToExit = false;
			pointToControl = true;
		}//=======================Pointing to Controls====================//
		else if (pointToGame == false && pointToExit == false && pointToControl == true)
		{
			pointToGame = false;
			pointToExit = true;
			pointToControl = false;
		}//=======================Pointing to End game====================//
		else if (pointToGame == false && pointToExit == true && pointToControl == false)
		{
			pointToGame = true;
			pointToExit = false;
			pointToControl = false;
		}
		elapsedTime2 -= 0.5;
	}

	if (pointToGame == true && pointToExit == false && pointToControl == false) //Start Game
	{
		if(Application::IsKeyPressed(VK_RETURN))
		{
			showMenu = false;
		}
	}
	if (pointToGame == false && pointToExit == false && pointToControl == true) //Show Control
	{
		if(Application::IsKeyPressed(VK_RETURN))
		{
			showControl = true;
		}
	}
	if (pointToGame == false && pointToExit == true && pointToControl == false) // End Game
	{
		if (Application::IsKeyPressed(VK_RETURN))
		{
			exit (NULL);
		}
	}

	if (Application::IsKeyPressed('R') && showMenu == false ||
		Application::IsKeyPressed('R') && showControl == true)
	{
		showMenu = true;
		pointToGame = true;
		pointToExit = false;
		pointToControl = false;
		showControl = false;
	}
}
