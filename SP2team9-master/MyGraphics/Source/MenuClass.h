/******************************************************************************/
/*!
\file	MenuClass.h
\author On gSwee Seng
\par	email: 141991A@mymail.nyp.edu.sg
\brief
MenuClass Class
*/
/******************************************************************************/
#pragma once
#include <string>
#include "Vector3.h"
#include "Mesh.h"
#include "Mtx44.h"
#include "Player.h"
#include "MatrixStack.h"
#include "Application.h"
#include "timer.h"

using std::string;
using std::cout;
using std::endl;
/******************************************************************************/
/*!
	Class MenuClass
\brief
Defines the variables and functions required for the MenuClass

*/
/******************************************************************************/
class Menu
{
public:
	Menu(void);
	~Menu(void);

	void SetBackground(int newObj);
	void SetArrow(int newObj);
	void SetStartGameTrue(int newObj);
	void SetStartGameFalse(int newObj);
	void SetEndGameTrue(int newObj);
	void SetEndGameFalse(int newObj);
	void SetPointControlTrue(int newObj);
	void SetPointControlFalse(int newObj);
	void SetGameOverMesh(int newObj);
	void SetControlMesh(int newObj);
	void SetWinMesh(int newObj);

	void update(double dt);

	int getBackgroundMesh();
	int getArrowMesh();
	int getStartGameTrueMesh();
	int getStartGameFalseMesh();
	int getEndGameTrueMesh();
	int getEndGameFalseMesh();
	int getControlTrueMesh();
	int getControlFalseMesh();
	int getControlMesh();
	int getGameOverMesh();
	int getWinMesh();
	bool getPointToGame();
	bool getPointToExit();
	bool getPointToContorl();
	bool getShowMenuStatus();
	bool getShowContorlStatus();

private:
	int StartGameTrue,
		StartGameFalse,
		EndGameTrue,
		EndGameFalse,
		Arrow,
		MenuBackground,
		GameOver,
		Win,
		Control,
		PointToControlTrue,
		PointToControlFalse;

	bool pointToGame,
		pointToExit,
		pointToControl,
		showMenu,
		showControl,
		GameOverState,
		WinState;

	StopWatch Timer;
};

