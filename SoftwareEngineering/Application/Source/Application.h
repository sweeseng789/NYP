#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"

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