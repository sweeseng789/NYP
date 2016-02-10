
#include "Application.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

//Include the standard C++ headers
#include <stdio.h>
#include <stdlib.h>

GLFWwindow* m_window;
CLua* Application::lua = new CLua("my");

const unsigned char FPS = 60; // FPS of this game
const unsigned int frameTime = 1000 / FPS; // time for each frame
int Application::init_window_width = Application::lua->getData<int>("SCREENWIDTH");
int Application::init_window_height = Application::lua->getData<int>("SCREENHEIGHT");
int Application::m_window_width = Application::init_window_width;
int Application::m_window_height = Application::init_window_height;

double Application::mouse_last_x = 0.0, Application::mouse_last_y = 0.0, 
	   Application::mouse_current_x = 0.0, Application::mouse_current_y = 0.0,
	   Application::mouse_diff_x = 0.0, Application::mouse_diff_y = 0.0,
		Application::camera_yaw = 0.0, Application::camera_pitch = 0.0,
		Application::d_mouseScroll = 0.0;

bool Application::d_isMouseScrolling = false, Application::updateMouse = false,
	Application::toggleFullscreen = false, Application::FULL_SCREEN = false,
	Application::b_exitGame = false, Application::b_startGame = false, Application::b_BacktoMenu = false, Application::b_skipSplashscreen = false;

int Application::scrollCount = 3, Application::scrollCount_min = 0, Application::scrollCount_max = 6, 
	Application::button_Left = 0, Application::button_Middle = 0, Application::button_Right = 0;




void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	if (Application::d_mouseScroll == 0)
	{
		Application::d_mouseScroll = yoffset;
	}
}

/********************************************************************************
 Define an error callback
 ********************************************************************************/
static void error_callback(int error, const char* description)
{
	fputs(description, stderr);
	_fgetchar();
}

/********************************************************************************
 Define the key input callback
 ********************************************************************************/
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

/********************************************************************************
 Callback function when the window is resized
 ********************************************************************************/
void resize_callback(GLFWwindow* window, int w, int h)
{
	glViewport(0, 0, w, h);
}

/********************************************************************************
 Get keyboard's key states
 ********************************************************************************/
bool Application::IsKeyPressed(unsigned short key)
{
    return ((GetAsyncKeyState(key) & 0x8001) != 0);
}

/********************************************************************************
Get mouse's key states
********************************************************************************/
bool Application::IsMousePressed(unsigned short key) //0 - Left, 1 - Right, 2 - Middle
{
	return glfwGetMouseButton(m_window, key) != 0;
}

/********************************************************************************
 Get mouse updates
 ********************************************************************************/
bool Application::GetMouseUpdate()
{
	//Mouse Scrolling
	updateMouseScrolling();

    glfwGetCursorPos(m_window, &mouse_current_x, &mouse_current_y);

	if (updateMouse)
	{
		//Getting thw differenece
		mouse_diff_x = mouse_current_x - mouse_last_x;
		mouse_diff_y = mouse_current_y - mouse_last_y;

		//Updating camera pitch and yaw
		camera_yaw = (float)mouse_diff_x * 0.0174555555555556f;// * 3.142f / 180.0f;
		camera_pitch = mouse_diff_y * 0.0174555555555556f;// 3.142f / 180.0f );

		//Wrap around
		//X - Axis
		if (mouse_current_x < m_window_deadzone || mouse_current_x > m_window_width - m_window_deadzone)
		{
			mouse_current_x = m_window_width >> 1;
		}
		//Y - Axis
		if (mouse_current_y < m_window_deadzone || mouse_current_y > m_window_width - m_window_deadzone)
		{
			mouse_current_y = m_window_height >> 1;
		}
		glfwSetCursorPos(m_window, mouse_current_x, mouse_current_y);
	}

	//Get the mouse button status
	button_Left = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_LEFT);
	button_Middle = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_MIDDLE);
	button_Right = glfwGetMouseButton(m_window, GLFW_MOUSE_BUTTON_RIGHT);

	//Update GSM
	theGSM->HandleEvents(mouse_current_x, mouse_current_y, button_Left, button_Middle, button_Right);

	//Update mouse last 
	mouse_last_x = mouse_current_x;
	mouse_last_y = mouse_current_y;

    return false;
}

/********************************************************************************
 Get keyboard updates
 ********************************************************************************/
bool Application::GetKeyboardUpdate()
{
	//Press A
	if (IsKeyPressed('A'))
	{
		//scene->UpdateAvatarStatus('a');
		theGSM->HandleEvents('a');
	}
	else
	{
		theGSM->HandleEvents('a', false);
	}

	//Press D
	if (IsKeyPressed('D'))
	{
		theGSM->HandleEvents('d');
	}
	else
	{
		theGSM->HandleEvents('d', false);
	}

	//Press W
	if (IsKeyPressed('W'))
	{
		theGSM->HandleEvents('w');
	}
	else
	{
		theGSM->HandleEvents('w', false);
	}

	//Press S
	if (IsKeyPressed('S'))
	{
		theGSM->HandleEvents('s');
	}
	else
	{
		theGSM->HandleEvents('s', false);
	}

	if (IsKeyPressed(VK_TAB))
	{
		theGSM->HandleEvents(VK_TAB);
	}
	else
	{
		theGSM->HandleEvents(VK_TAB, false);
	}

	if (IsKeyPressed(VK_SPACE))
	{
		theGSM->HandleEvents(VK_SPACE);
	}
	else
	{
		theGSM->HandleEvents(VK_SPACE, false);
	}

	//// Jump
	//if (IsKeyPressed(32))
	//{
	//	theGSM->HandleEvents(32);
	//}

	//// Rotate camera
	//if (IsKeyPressed(VK_LEFT))
	//{
	//	scene->UpdateCameraStatus(VK_LEFT);
	//}
	//else
	//{
	//	scene->UpdateCameraStatus(VK_LEFT, false);
	//}
	//if (IsKeyPressed(VK_RIGHT))
	//{
	//	scene->UpdateCameraStatus(VK_RIGHT);
	//}
	//else
	//{
	//	scene->UpdateCameraStatus(VK_RIGHT, false);
	//}
	//if (IsKeyPressed(VK_UP))
	//{
	//	scene->UpdateCameraStatus(VK_UP);
	//}
	//else
	//{
	//	scene->UpdateCameraStatus(VK_UP, false);
	//}
	//if (IsKeyPressed(VK_DOWN))
	//{
	//	scene->UpdateCameraStatus(VK_DOWN);
	//}
	//else
	//{
	//	scene->UpdateCameraStatus(VK_DOWN, false);
	//}
    return true;
}



/********************************************************************************
 Constructor
 ********************************************************************************/
Application::Application()
	: scene(NULL)
	, theGSM(NULL)
{
}

/********************************************************************************
 Destructor
 ********************************************************************************/
Application::~Application()
{
	if (theGSM)
	{
		delete theGSM;
		theGSM = NULL;
	}
}

void Application::updateMouseScrolling()
{
	glfwSetScrollCallback(m_window, scroll_callback);

	if (d_mouseScroll != 0)
	{
		d_isMouseScrolling = true;

		static double timeLimit = 0.5;
		static double currentTime = 0.0;

		currentTime += m_dElapsedTime;

		if (currentTime >= timeLimit)
		{
			if (d_mouseScroll < 0.0 && scrollCount < scrollCount_max)
			{
				scrollCount += 1;
			}
			else if (d_mouseScroll > 0.0 && scrollCount > scrollCount_min)
			{
				scrollCount -= 1;
			}

			currentTime = 0.0;
			d_mouseScroll = 0.0;
			d_isMouseScrolling = false;
		}
	}
}

void Application::activateMouse(bool status)
{
	updateMouse = status;

	if (!updateMouse)
	{
		//Show cursor
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else
	{
		//Hide Cursor
		glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
		glfwSetCursorPos(m_window, m_window_width / 2, m_window_height / 2);
	}
}

int Application::getWindow_Height()
{
	return m_window_height;
}

int Application::getWindow_Width()
{
	return m_window_width;
}

void Application::GetMousePos(double & mousePos_x, double & mousePos_Y)
{
	double *xpos = new double;
	double *ypos = new double;

	glfwGetCursorPos(m_window, xpos, ypos);

	mousePos_x = static_cast<float>(*xpos);
	mousePos_Y = static_cast<float>(*ypos);

	delete xpos;
	delete ypos;
}

void Application::fullscreenToggle()
{
	toggleFullscreen = true;
}

void Application::quitGame()
{
	b_exitGame = true;
}

/********************************************************************************
 Initialise this program
 ********************************************************************************/
void Application::Init()
{
	//Set the error callback
	glfwSetErrorCallback(error_callback);

	//Initialize GLFW
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}

	//Set the GLFW window creation hints - these are optional
	glfwWindowHint(GLFW_SAMPLES, 4); //Request 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); //Request a specific OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); //Request a specific OpenGL version
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 


	std::ifstream setting("Text/Setting.txt");
	if (setting.is_open())
	{
		std::string settingName = "";
		std::string settingInfo = "";

		while (!setting.eof())
		{
			getline(setting, settingName, ':');
			getline(setting, settingInfo);

			FILE_SETTING newInfo;
			newInfo.settingName = settingName;
			newInfo.settingInfo = settingInfo;
			v_fileSetting.push_back(newInfo);

			//Clear whitespace
			settingInfo.erase(remove_if(settingInfo.begin(), settingInfo.end(), isspace), settingInfo.end());

			if (settingName == "Fullscreen")
			{
				if (settingInfo == "True")
				{
					FULL_SCREEN = true;
				}
				else
				{
					FULL_SCREEN = false;
				}
			}
		}
	}
	setting.close();
	/*std::vector<int> hello = lua->getIntVector("TESTVECTOR");
	std::cout << "Start" << std::endl;
	for (int a = 0; a < hello.size(); ++a)
	{
		std::cout << hello[a] << std::endl;
	}
	std::cout << "End" << std::endl;*/
	/*std::vector<int> hello = lua->getVector<int>("TESTVECTOR");*/

	lua->add(2, 2, 3);

	/*int a = lua->getData<int>("SCREENWIDTH");
	std::cout << a << std::endl;

	std::cout << lua->getData<int>("SCREENHEIGHT") << std::endl;

	bool b = lua->getData<bool>("FULLSCREEN");
	std::cout << b << std::endl;*/

	//Create a window and create its OpenGL context
	if (FULL_SCREEN)
	{
		const GLFWvidmode *win_data = glfwGetVideoMode(glfwGetPrimaryMonitor());
		m_window_width = win_data->width;
		m_window_height = win_data->height;
		m_window = glfwCreateWindow(win_data->width, win_data->height, "Y2S2_Framework", glfwGetPrimaryMonitor(), NULL);
	}
	else
	{
		m_window = glfwCreateWindow(m_window_width, m_window_height, "Y2S2_Framework", NULL, NULL);
	}

	//If the window couldn't be created
	if (!m_window)
	{
		fprintf( stderr, "Failed to open GLFW window.\n" );
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//This function makes the context of the specified window current on the calling thread. 
	glfwMakeContextCurrent(m_window);

	//Sets the key callback
	//glfwSetKeyCallback(m_window, key_callback);
	glfwSetWindowSizeCallback(m_window, resize_callback);

	glewExperimental = true; // Needed for core profile
	//Initialize GLEW
	GLenum err = glewInit();

	//If GLEW hasn't initialized
	if (err != GLEW_OK) 
	{
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		//return -1;
	}

	// Set these 2 variables to zero
	m_dElapsedTime = 0.0;
	m_dAccumulatedTime_ThreadOne = 0.0;
	m_dAccumulatedTime_ThreadTwo = 0.0;

	theGSM = new CGameStateManager();
	theGSM->Init("DM220 With Game State Management", Application::m_window_width, Application::m_window_height);
	theGSM->ChangeState(CIntroState::Instance());
	//activateMouse(true);
}

/********************************************************************************
 Run this program
 ********************************************************************************/
void Application::Run()
{
	//#if TYPE_OF_VIEW == 3
	//	scene = new SceneGame(m_window_width, m_window_height);	// Use this for 3D gameplay
	//#else
	//	scene = new SceneGame2D(m_window_width, m_window_height);	// Use this for 2D gameplay
	//#endif
	//scene->Init();

	m_timer.startTimer();    // Start timer to calculate how long it takes to render this frame
	while (!glfwWindowShouldClose(m_window) && !b_exitGame)
	{
		// Get the elapsed time
		m_dElapsedTime = m_timer.getElapsedTime();
		m_dAccumulatedTime_ThreadOne += m_dElapsedTime;
		m_dAccumulatedTime_ThreadTwo += m_dElapsedTime;


		if (m_dAccumulatedTime_ThreadOne > 0.03)
		{
			GetMouseUpdate();
			GetKeyboardUpdate();
			theGSM->HandleEvents();
			theGSM->Update(m_dElapsedTime);
			m_dAccumulatedTime_ThreadOne = 0.0;
		}
		if (m_dAccumulatedTime_ThreadTwo > 1.0)
		{
			//UpdateAI();
			m_dAccumulatedTime_ThreadTwo = 0.0;
		}
		// Render the scene
		theGSM->Draw();
		//Swap buffers
		glfwSwapBuffers(m_window);
		//Get and organize events, like keyboard and mouse input, window resizing, etc...
		glfwPollEvents();
        m_timer.waitUntil(frameTime);       // Frame rate limiter. Limits each frame to a specified time in ms.


		//if player toggle fullscreen
		if (toggleFullscreen)
		{
			glfwDestroyWindow(m_window);

			//Currently in fullscreen
			if (FULL_SCREEN)
			{
				FULL_SCREEN = false;
				m_window_width = init_window_width;
				m_window_height = init_window_height;
				m_window = glfwCreateWindow(m_window_width, m_window_height, "Y2S2_Framework", NULL, NULL);
			}
			//Not in fullscreen
			else
			{
				FULL_SCREEN = true;
				const GLFWvidmode *win_data = glfwGetVideoMode(glfwGetPrimaryMonitor());
				m_window_width = win_data->width;
				m_window_height = win_data->height;
				m_window = glfwCreateWindow(win_data->width, win_data->height, "Y2S2_Framework", glfwGetPrimaryMonitor(), NULL);
			}

			glfwMakeContextCurrent(m_window);
			theGSM->ChangeState(CMenuState::Instance());
			toggleFullscreen = false;
		}

		//Skip splashscreen
		if(b_skipSplashscreen)
		{
			theGSM->ChangeState(CMenuState::Instance());
			b_skipSplashscreen = false;
		}

		//Start game
		if (b_startGame)
		{
			theGSM->ChangeState(CPlayState::Instance());
			//activateMouse(false);
			b_startGame = false;
		}

		//Go back to menu
		if (b_BacktoMenu)
		{
			theGSM->ChangeState(CMenuState::Instance());
			b_BacktoMenu = false;
		}

	} //Check if the ESC key had been pressed or if the window had been closed

	// Delete the scene
	theGSM->Cleanup();
}

/********************************************************************************
 Exit this program
 ********************************************************************************/
void Application::Exit()
{
	//Write Current Setting
	ofstream setting;
	setting.open("Text/Setting.txt", std::ofstream::out | std::ofstream::trunc);
	int count = 0;
	for (std::vector<FILE_SETTING>::iterator it = v_fileSetting.begin(); it != v_fileSetting.end(); ++it)
	{
		count++;
		std::string name  = "", info = " ";
		if (it->settingName == "Fullscreen")
		{
			name = it->settingName;

			if (FULL_SCREEN)
				info += "True";
			else
				info += "False";
		}
		else
		{
			name = it->settingName;
			info =it->settingInfo;
		}


		setting << name << ":" << info;

		if (count != v_fileSetting.size())
		{
			setting << std::endl;
		}
	}
	setting.close();

	if (lua)
	{
		delete lua;
	}

	//Close OpenGL window and terminate GLFW
	glfwDestroyWindow(m_window);
	//Finalize and clean up GLFW
	glfwTerminate();
}

void Application::setMousePos(double& mousePos_X, double& mousePos_Y)
{
	glfwSetCursorPos(m_window, mousePos_X, mousePos_Y);
}