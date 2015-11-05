#pragma once
#include "SceneSplashScreen.h"
#include "gamestate.h"
#include "Application.h"

class CIntroState : public CGameState
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
	void Update(CGameStateManager*, const double m_dElapsedTime);
	void Update(const double m_dElapsedTime);
	void Draw(CGameStateManager* theGSM);

	static CIntroState* Instance() {
		return &theIntroState;
	}

protected:
	CIntroState() { }

private:
	static CIntroState theIntroState;

	SceneSplashScreen *scene;
};
