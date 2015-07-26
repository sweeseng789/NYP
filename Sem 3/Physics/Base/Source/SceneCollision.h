#ifndef SCENE_COLLISION_H
#define SCENE_COLLISION_H

#include <fstream>
#include <string>
#include "Camera.h"
#include "GameObject.h"
#include <vector>
#include "SceneBase.h"

using std::ifstream;
using std::string;
using std::getline;
using std::stoi;

class SceneCollision : public SceneBase
{
	static const int MAX_SPEED = 10;
	static const int BULLET_SPEED = 50;
	static const int MISSILE_SPEED = 20;
	static const int MISSILE_POWER = 1;

public:
	SceneCollision();
	~SceneCollision();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderGO(GameObject *go);
	void GOUpdate(const double dt);
	void PlayerControl(double dt);
	void GameMenuUpdate(double dt);

	void RenderPowerBar();
	void RenderBlackScreen();
	void RenderText();
	void RenderPlayerTurn();

	GameObject* FetchGO();

	bool CheckCollision(GameObject *go1, GameObject *go2, float dt);
	float CheckCollision2(GameObject* go, GameObject* go2);
	void CollisionResponse(GameObject *go1, GameObject *go2);

protected:

	//Physics
	std::vector<GameObject *> m_goList;
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	GameObject *m_ghost;
	GameObject * ball;
	int m_objectCount;

	//Auditing
	float m1, m2;
	Vector3 u1, u2, v1, v2;
	Vector3 initialMomentum, finalMomentum;
	float initialKE, finalKE;
	float m_estimatedTime;

	float powerBar_y;
	float moveGameMenu;
	bool showGameMenu;
	bool movingBall;
	int player1Score;
	int player2Score;
	int turn;
	bool player1Turn;
	bool player2Turn;
	//Camera camera;
};

#endif