#ifndef APPLICATION_H
#define APPLICATION_H

#include "timer.h"
#include "SceneGame.h"
#include "SceneManager2D.h"
#include "GameStateManager.h"
#include "PlayState.h"
#include "IntroState.h"
#include "MenuState.h"

#define TYPE_OF_VIEW 3	// 2 = 2D, 3 = 3D

class Application
{
public:
	static Application& GetInstance()
	{
		static Application app;
		return app;
	}

	static bool IsKeyPressed(unsigned short key);
	static bool IsMousePressed(unsigned short key);
	bool GetMouseUpdate();
	bool GetKeyboardUpdate();
	void updateMouseScrolling();

	void Init();
	void Run();
	void Exit();


	//Declare variables to store the last and current mouse position
	static double mouse_last_x, mouse_last_y, mouse_current_x, mouse_current_y, mouse_diff_x, mouse_diff_y;
	static double camera_yaw, camera_pitch;
	//Mouse scroll variable
	static double d_mouseScroll;
	static bool d_isMouseScrolling;
	static int scrollCount;
	static int scrollCount_min, scrollCount_max;
	static int button_Left, button_Middle, button_Right;
	static bool updateMouse;
	static void GetMousePos(float & mousePos_x, float & mousePos_Y);
	static void activateMouse(bool status);

	static int getWindow_Width();
	static int getWindow_Height();

	//Game status
	static void startGame();
	static void returnToMenu();

	//Fullscreen
	static void fullscreenToggle();

	static void quitGame();

private:
	Application();
	~Application();

	// Declare the window width and height as constant integer
	const static int m_window_deadzone = 99999;
	static int m_window_width;
	static int m_window_height;
	const static int init_window_width = 1080;
	const static int init_window_height = 720;

	//Declare a window object
	StopWatch m_timer;
	double m_dElapsedTime;
	double m_dAccumulatedTime_ThreadOne;
	double m_dAccumulatedTime_ThreadTwo;

	//Fullscreen
	static bool toggleFullscreen;
	static bool FULL_SCREEN;

	//Exit
	static bool b_exitGame;

	// The handler for the scene
	#if TYPE_OF_VIEW == 3
		//SceneGame *scene;	// Use this for 3D gameplay
	SceneMenu *scene;
	#else
		SceneGame2D *scene;	// Use this for 2D gameplay
	#endif


	//Game State Management
	CGameStateManager* theGSM;
};

#endif