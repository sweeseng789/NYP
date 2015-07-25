#ifndef SCENE_COLLISION_H
#define SCENE_COLLISION_H

#include "Camera.h"
#include "GameObject.h"
#include <vector>
#include "SceneBase.h"

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

	//Camera camera;
};

#endif