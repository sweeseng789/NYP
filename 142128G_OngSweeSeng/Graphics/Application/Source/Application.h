#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
/****************************************************************************/
/*!
\file Application.h
\author Ong Swee Seng
\briefApplication.h is used to provides methods to detect user input
*/
/****************************************************************************/

/******************************************************************************/
/*!
		Class Application:
\brief	Provides methods to detect user input
*/
/******************************************************************************/

class Application
{
public:
	Application();
	~Application();
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);

private:

	//Declare a window object
	StopWatch m_timer;
};

#endif