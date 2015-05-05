/******************************************************************************/
/*!
\file	StudioProject.h
\author Princeton Chew, name, name, name,
\par	email: 141991A@mymail.nyp.edu.sg
\brief
Studio Project Class
*/
/******************************************************************************/
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"

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