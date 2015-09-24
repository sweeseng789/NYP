
#ifndef APPLICATION_H
#define APPLICATION_H

#include <string>
#include "timer.h"


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

	//Getter
	static bool IsKeyPressed(unsigned short key);
	static bool IsMousePressed(unsigned short key);
	static bool GetMouseUpdate();
	static double getCamera_yaw();
	static double getCamera_pitch();
	static int getWorld_Width();
	static int getWorld_Height();
	static bool get_enableMouseUpdate();
	static void getMousePos(double &pos_x, double &pos_y);
	static bool getFullscreen();

	//Setter
	static void setMouseUpdate();
	static void setFullscreen();
	static void quitProgramme();
private:
	Application();
	~Application();

	// Declare the window width and height as constant integer
	const static int m_window_deadzone = 100;
	static int init_window_width;
	static int init_window_height;
	static int m_window_width;
	static int m_window_height;

	//Fullscreen
	static bool toggleFullscreen;
	static bool isFullscreen;

	//Window
	static std::string windowName;
	static bool b_quitProgramme;

	//Mouse Update
	static bool b_enableMouseUpdate;
	//Declare variables to store the last and current mouse position
	static double mouse_last_x, mouse_last_y, mouse_current_x, mouse_current_y, mouse_diff_x, mouse_diff_y, previous_mouse_x, previous_mouse_y;
	static double camera_yaw, camera_pitch;

	//Declare a window object
	StopWatch m_timer;
};

#endif