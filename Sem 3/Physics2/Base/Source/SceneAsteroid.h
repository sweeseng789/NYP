#ifndef SCENE_ASTEROID_H
#define SCENE_ASTEROID_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"
#include "Mesh.h"
#include "StartMenu.h"

using std::endl;
using std::cout;

class SceneAsteroid : public SceneBase
{
	static const int MAX_SPEED = 100;
	static const int BULLET_SPEED = 50;
	static const int MISSILE_SPEED = 20;
	static const int MISSILE_POWER = 1;

	/*enum GEOMETRY_TYPE
	{
		GEO_AXES,
		SpaceShip,
		NUM_GEOMETRY,
	};*/
public:
	SceneAsteroid();
	~SceneAsteroid();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderGO(GameObject *go);

	GameObject* FetchGO();

	void GOUpdate(float dt);
	void WrapGONearScreen(GameObject * go);
	void DeleteGONearScreen(GameObject * go);
	void SpawnAsteroid(GameObject * go);
	void playExplosionAnimation(GameObject * go);
	void BossUpdate(float dt);
	void SpawnUpdate(float dt);
	void RenderScene();
	void RenderMenu();
	void reset();
	void shipUpdate(float dt);
	float findCollision(GameObject * go, GameObject * GotoCheck);
protected:

	//Physics
	std::vector<GameObject *> m_goList;
	std::vector<GameObject *> m_goList_Bullet;
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	GameObject *m_ship;
	GameObject *m_enemyShip;
	Vector3 m_force;
	int m_objectCount;
	int m_lives;
	int m_score;

private:

	//int
	int asteroidCount;
	int enemyCount;
	int heartCount;
	int PUCount;
	int lv2_killCount;

	//Bool
	bool powerUp;
	bool Gameover;
	bool Won;
	bool throwBomb;

	//Float
	float rotateShip;
	float bulletAngle;
	float BulletGapLimit;
	float BombGapLimit;
	float evenEShoot;
	float oddEShoot;
	float totalTime;
	float powerUpTime;
	float lv1_time;

	//Double
	double GodModeTime;

	//Vector3
	Vector3 bullet;

	//Bool
	bool shot;
	bool GodMode;
	bool lv1, lv2, lv3;

	//Class
	CStartMenu menu;
};

#endif