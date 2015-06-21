#ifndef SCENE_COLLISION_H
#define SCENE_COLLISION_H

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

protected:

	//Physics
	std::vector<GameObject *> m_goList;
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	GameObject *m_ghost;
	int m_objectCount;

	//Auditing
	float m1, m2;
	Vector3 u1, u2, v1, v2;
	Vector3 initialMomentum, finalMomentum;
	float initialKE, finalKE;

	////getting the mtd
	//Vector3 delta = go->pos - go2->pos;
	//float d = delta.Length();
	////Mininum translate distance to push ball after intersecting
	//Vector3 mtd = delta *(((go->scale.x + go2->scale.x)) - d / d);

	////resolve intersection
	////inverse mass quantities
	//float im1 = 1 / go->mass;
	//float im2 = 1 / go2->mass;

	////Impact speed
	//Vector3 v = (go->vel - go2->vel);
	//float vn = v.Dot(mtd.Normalize());

	////Collision impulse
	//float i = (-(1.f + 1) * vn) / (im1 + im2);
	//Vector3 impulse = mtd * i;

	////Change in momentum
	//go->vel = go->vel + (impulse * im1);
	//go2->vel = go2->vel - (impulse * im2);
};

#endif