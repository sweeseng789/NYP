#pragma once
#include "SceneMenu.h"
#include "GameState.h"

//Include GLEW
#include <GL/glew.h>

//Include GLFW
#include <GLFW/glfw3.h>

class CMenuState : public CGameState
{
public:
	void Init();
	void Init(const int width, const int height);
	void InitShaders();
	void Cleanup();

	void Pause();
	void Resume();

	void HandleEvents(CGameStateManager* theGSM);
	void HandleEvents(CGameStateManager* theGSM, const unsigned char key, const bool status = true);
	void HandleEvents(CGameStateManager* theGSM, const double mouse_x, const double mouse_y, const int button_Left, const int button_Middle, const int button_Right);
	void Update(CGameStateManager* theGSM);
	void Update(CGameStateManager* theGSM, const double m_dElapsedTime);
	void Draw(CGameStateManager* theGSM);

	static CMenuState* Instance() {
		return &theMenuState;
	}

	static void startGame();
protected:
	CMenuState() { }

private:
	static CMenuState theMenuState;

	double mouse_last_x, mouse_last_y, mouse_diff_x, mouse_diff_y, camera_yaw, cmaera_pitch;
	GLFWwindow* m_window;
	
	static bool switchToPlay;

	SceneMenu *scene;
};
