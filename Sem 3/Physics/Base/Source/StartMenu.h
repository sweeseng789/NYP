#pragma once
#include <iostream>
#include "Application.h"

class CStartMenu
{
public:
	CStartMenu(void);
	~CStartMenu(void);

	//Setter
	void MenuUpdate(float dt);
	void b_setStart();
	void b_setControl();
	void b_setExit();
	void reset();

	//Getter
	bool StartConfirm();
	bool ControlConfirm();
	bool ExitConfirm();
	bool getStartGame();
	bool getShowControl();
private:
	//bool
	bool startGame;
	bool showControl;
	bool StartTrue;
	bool ControlTrue;
	bool ExitTrue;
};

