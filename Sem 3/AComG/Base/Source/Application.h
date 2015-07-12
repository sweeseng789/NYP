
#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
class SceneShadow;
class Application
{
public:
	static Application& GetInstance()
	{
		static Application app;
		return app;
	}
	void Init();
	void Run();
	void Exit();
	static bool IsKeyPressed(unsigned short key);
	bool GetKeyboardUpdate();

	//Mouse
	static double mouse_last_x, 
				mouse_last_y,
				mouse_current_x,
				mouse_current_y,
				mouse_diff_x,
				mouse_diff_y;

	static double camera_yaw,
				camera_pitch;

	static bool GetMouseUpdate();


private:
	Application();
	~Application();

	//Declare a window object
	StopWatch m_timer;
	double m_dElapsedTime;
	double m_dAccumulatedTime_SceneUpdate;
	double m_dAccumulatedTime_MouseUpdate;

	//Mouse
	const static int m_window_deadzone = 1000;
	const static int m_window_width = 800;
	const static int m_window_height = 600;

	SceneShadow *scene;
};

#endif