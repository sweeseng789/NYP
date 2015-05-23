#ifndef SCENE_ASTEROID_H
#define SCENE_ASTEROID_H

#include "GameObject.h"
#include <vector>
#include "SceneBase.h"
#include "Mesh.h"

using std::cout;
using std::endl;

class SceneAsteroid : public SceneBase
{
	static const int MAX_SPEED = 100;
	static const int BULLET_SPEED = 10000;
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
	void wrapGONearScreen(GameObject * go);
	void deleteGONearScreen(GameObject * go);
	void moveBullet(GameObject* go, double dt);
	void CollisionForAsteroid(GameObject *go, double dt);
	void SpawnAsteroid(GameObject *go);
	void BouncingAsteroid(GameObject *go, GameObject *GOtoCheck);
	void deleteTwoGO(GameObject *go, GameObject *GOtoCheck);
	void AsteroidCollision(GameObject *go, GameObject *GOtoCheck);
protected:

	//Physics
	std::vector<GameObject *> m_goList;
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	GameObject *m_ship;
	Vector3 m_force;
	int m_objectCount;
	int m_lives;
	int m_score;

private:
	float rotateShip;
	float bulletAngle;
	Vector3 bullet;
	float BulletGapLimit;
};

#endif