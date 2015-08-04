#include "StartMenu.h"


CStartMenu::CStartMenu(void):
startGame(false),
StartTrue(true),
ControlTrue(false),
ExitTrue(false),
showControl(false)
{
}


CStartMenu::~CStartMenu(void)
{
}

bool CStartMenu::StartConfirm()
{
	if(StartTrue == true && ControlTrue == false && ExitTrue == false)
		return true;
	else
		return false;
}

bool CStartMenu::ControlConfirm()
{
	if(StartTrue == false && ControlTrue == true && ExitTrue == false)
		return true;
	else
		return false;
}

bool CStartMenu::ExitConfirm()
{
	if(StartTrue == false && ControlTrue == false && ExitTrue == true)
		return true;
	else
		return false;
}

bool CStartMenu::getStartGame()
{
	return this->startGame;
}

bool CStartMenu::getShowControl()
{
	return this->showControl;
}

void CStartMenu::b_setStart()
{
	StartTrue = true;
	ControlTrue = false;
	ExitTrue = false;
}

void CStartMenu::b_setControl()
{
	StartTrue = false;
	ControlTrue = true;
	ExitTrue = false;
}

void CStartMenu::b_setExit()
{
	StartTrue = false;
	ControlTrue = false;
	ExitTrue = true;
}

void CStartMenu::reset()
{
	startGame = false;
	StartTrue = true;
	ControlTrue = false;
	ExitTrue = false;
	showControl = false;
}

void CStartMenu::MenuUpdate(float dt)
{
	static float elapsedTime = 0;
	elapsedTime += dt;

	if(elapsedTime >= 0.2f)
		elapsedTime = 0.2f;

	if(startGame == false)
	{
		if(elapsedTime >= 0.2f)
		{
			if(StartConfirm())
			{
				if(Application::IsKeyPressed(VK_UP))
				{
					b_setExit();
					elapsedTime = 0.f;
				}
				else if(Application::IsKeyPressed(VK_DOWN))
				{
					b_setControl();
					elapsedTime = 0.f;
				}
				else if(Application::IsKeyPressed(VK_RETURN))
				{
					startGame = true;
				}
			}
			else if(ControlConfirm())
			{
				if(Application::IsKeyPressed(VK_UP))
				{
					b_setStart();
					elapsedTime = 0.f;
				}
				else if(Application::IsKeyPressed(VK_DOWN))
				{
					b_setExit();
					elapsedTime = 0.f;
				}
				else if(Application::IsKeyPressed(VK_RETURN))
				{
					showControl = true;
				}
			}
			else if(ExitConfirm())
			{
				if(Application::IsKeyPressed(VK_UP))
				{
					b_setControl();
					elapsedTime = 0.f;
				}
				else if(Application::IsKeyPressed(VK_DOWN))
				{
					b_setStart();
					elapsedTime = 0.f;
				}
				else if(Application::IsKeyPressed(VK_RETURN))
				{
					exit(NULL);
				}
			}
		}
	}
}