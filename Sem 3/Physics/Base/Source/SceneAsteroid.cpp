#include "SceneAsteroid.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

SceneAsteroid::SceneAsteroid()
{
}

SceneAsteroid::~SceneAsteroid()
{
}

void SceneAsteroid::Init()
{
	SceneBase::Init();

	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();

	//Exercise 2a: Construct 100 GameObject with type GO_ASTEROID_SMALL and add into m_goList
	/*for (unsigned i = 0; i < 100; ++i)
	{
	GameObject *go = new GameObject(GameObject::GO_ASTEROID_SMALL);
	m_goList.push_back(go);
	}*/


	//Exercise 2b: Initialize m_lives and m_score
	m_lives = 3;
	m_score = 0;

	//Exercise 2c: Construct m_ship, set active, type, scale and pos
	m_ship = new GameObject(GameObject::GO_SHIP);
	m_ship->active = true;
	m_ship->scale.Set(12, 12, 12);
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	m_ship->pos.Set(m_worldWidth * 0.5f, m_worldHeight * 0.5f, 0);
	m_ship->mass = 0.1f;

	m_enemyShip = new GameObject(GameObject::GO_BOSS);
	m_enemyShip->active = false;
	m_enemyShip->scale.Set(30.f, 30.f, 30.f);
	m_enemyShip->vel.SetZero();
	m_enemyShip->health = 150.f;
	m_enemyShip->setAngle(180);
	m_enemyShip->pos.Set(m_worldWidth, m_worldHeight - 10, 0);
	m_enemyShip->m_shieldTime = 0.f;

	//Set Paramters
	rotateShip = 0.f;
	bulletAngle = 0.f;
	BulletGapLimit = 0.5f;
	BombGapLimit = 0.5f;
	asteroidCount = 0;
	enemyCount = 0;
	evenEShoot = 0;
	oddEShoot = 0;
	heartCount = 0;
	totalTime = 0.f;
	PUCount = 0;
	powerUp = false;
	powerUpTime = 20.0f;
	GodMode = true;
	GodModeTime = 3.0f;
	Gameover = false;
	Won = false;
	lv1 = true;
	lv2 = false;
	lv3 = false;
	lv1_time = 0.f;
	lv2_killCount = 0;
	throwBomb = false;
}

GameObject* SceneAsteroid::FetchGO()
{
	//Exercise 3a: Fetch a game object from m_goList and return it

	static float loopy = 0;

	for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it, ++loopy)
	{
		GameObject * go = (GameObject*)*it;
		if (!go->active)
		{
			go->active = true;
			go->pos.Set(0, 0, Math::RandFloatMinMax(-10, 10) / loopy);
			return go;
		}
	}
	//Exercise 3b: Handle the situation whenever m_goList runs out of objects
	for (unsigned i = 0; i < 10; ++i)
	{
		GameObject *go = new GameObject(GameObject::GO_ASTEROID_BIG);
		m_goList.push_back(go);
	}

	GameObject *go = m_goList.back();
	go->active = true;

	return go;
}

void SceneAsteroid::WrapGONearScreen(GameObject * go)
{
	if(go->pos.x > m_worldWidth)
	{
		go->pos.x = 0;
	}
	else if(go->pos.x < 0)
	{
		go->pos.x = m_worldWidth;
	}

	if(go->pos.y > m_worldHeight)
	{
		go->pos.y = 0;
	}
	else if(go->pos.y < 0)
	{
		go->pos.y = m_worldHeight;
	}
}

void SceneAsteroid::DeleteGONearScreen(GameObject * go)
{
	if(go->pos.x > m_worldWidth || go->pos.x < 0 || go->pos.y > m_worldHeight || go->pos.y < 0)
	{
		go->active = false;
	}
}

float SceneAsteroid::findCollision(GameObject * go, GameObject * GotoCheck)
{
	float dist = (go->pos - GotoCheck->pos).LengthNZ();
	float combinedRadius = (go->scale.x + GotoCheck->scale.x) / 2;

	if (dist <= combinedRadius)
		return true;
	else
		return false;
}

void SceneAsteroid::SpawnAsteroid(GameObject * go)
{
	Vector3 testing = 0;
	testing = go->pos;

	for (unsigned a = 0; a < 2; a++)
	{
		GameObject * newAsteroid = FetchGO();
		newAsteroid->type = GameObject::GO_ASTEROID_SMALL;
		newAsteroid->scale.Set(5.f, 5.f, 5.f);

		if(a == 0)
		{
			testing.x = abs(testing.x + 5);
			testing.y = abs(testing.y + 5);
		}
		else
		{
			testing.x = abs(-(testing.x - 5));
			testing.y = abs(-(testing.y - 5));
		}
		newAsteroid->pos.Set(testing.x, testing.y, go->pos.z);
		newAsteroid->vel.Set(Math::RandFloatMinMax(-10, 10), Math::RandFloatMinMax(-10, 10) ,0);
		newAsteroid->health = 1.0;

		asteroidCount++;
	}
}

void SceneAsteroid::GOUpdate(float dt)
{
	for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if(go->active)
		{

			go->pos += go->vel * dt;

			//Exercise 12: handle collision between GO_SHIP and GO_ASTEROID_SMALL using simple distance-based check
			if(go->type == GameObject::GO_ASTEROID_SMALL || go->type == GameObject::GO_ASTEROID_BIG)
			{
				if (findCollision(go, m_ship) && GodMode == false)
				{
					go->active = false;
					m_lives --;
					m_ship->pos.Set(m_worldWidth * 0.5f, m_worldHeight * 0.5f, 0);
					m_ship->vel.SetZero();
					GodMode = true;
					GodModeTime = 3.0f;
					asteroidCount--;
				}
				else if(findCollision(go, m_enemyShip))
				{
					go->active = false;
					asteroidCount--;
				}

				//Exercise 13: asteroids should wrap around the screen like the ship
				WrapGONearScreen(go);
			}
			else if (go->type == GameObject::GO_BULLET || go->type == GameObject::GO_MISSILE)
			{
				//Exercise 16: unspawn bullets when they leave screen
				DeleteGONearScreen(go);

				if(go->type == GameObject::GO_BULLET)
				{
					go->pos.x += cos(Math::DegreeToRadian(go->angle)) * go->bulletSpeed * (float)dt;
					go->pos.y += sin(Math::DegreeToRadian(go->angle)) * go->bulletSpeed * (float)dt;

					if(findCollision(go, m_enemyShip))
					{
						go->active = false;
						if(m_enemyShip->type == GameObject::GO_BOSS)
						{
							m_enemyShip->health -= go->damage;
						}
						else if(m_enemyShip->type == GameObject::GO_BOSS_SHIELD)
						{
							m_enemyShip->health -= go->damage/2;
						}
					}
				}
				else
				{
					go->pos.x += cos(Math::DegreeToRadian(go->angle)) * 50 * (float)dt;
					go->pos.y += sin(Math::DegreeToRadian(go->angle)) * 50 * (float)dt;

					if(findCollision(go, m_enemyShip))
					{
						go->vel.SetZero();
						go->type = GameObject::GO_EXPLOSION;
						go->ScaleSize = 0;
					}
				}
			}
			else if(go->type == GameObject::GO_BOMB)
			{
				DeleteGONearScreen(go);

				go->bombTime -= dt;
				go->pos += go->vel * 5 * dt;

				if(go->bombTime <= 0)
				{
					go->type = GameObject::GO_EXPLOSION;
					go->vel.SetZero();
				}
				else if(findCollision(go, m_enemyShip))
				{
					go->type = GameObject::GO_EXPLOSION;
					go->vel.SetZero();
				}
			}
			else if(go->type == GameObject::GO_EXPLOSION)
			{
				if(go->ScaleSize < 30)
				{
					go->ScaleSize += 100 * dt;
					go->scale.Set((float)go->ScaleSize, (float)go->ScaleSize, (float)go->ScaleSize);
				}
				else if(go->bombDuration <= 0)
				{
					go->ScaleSize = 30;
					go->active = false;

					if(throwBomb = false)
					{
						throwBomb = true;
					}
				}

				if(findCollision(go, m_enemyShip))
				{
					if(go->ScaleSize == 30.f)
					{
						if(m_enemyShip->type == GameObject::GO_BOSS)
						{
							m_enemyShip->health -= go->damage;
						}
						else if(m_enemyShip->type == GameObject::GO_BOSS_SHIELD)
						{
							m_enemyShip->health -= go->damage/2;
						}
					}
				}
				go->bombDuration -= dt;
			}
			else if(go->type == GameObject::GO_ENEMY)
			{
				static float elaspedTime = 0;
				elaspedTime += dt;

				if(elaspedTime >= 1)
				{
					static int randNum = (Math::RandIntMinMax(2, 3));

					if(randNum == 2)
					{
						if(go->number % 2 == 0)
						{
							evenEShoot += 0.5;
						}
					}
					else
					{
						oddEShoot += 0.5;
					}
					elaspedTime = 0;
				}

				if(evenEShoot >= 10 || oddEShoot >= 10)
				{

					GameObject * newEbullet = FetchGO();
					newEbullet->type = GameObject::GO_ENEMY_LASER;
					newEbullet->scale.Set(3.f, 3.f, 3.f);

					newEbullet->pos.Set(go->pos.x, go->pos.y, go->pos.z);
					newEbullet->vel.Set(0, 1, 0);
					newEbullet->vel.Normalized();
					newEbullet->vel.Set(0, 1, 0);

					if(evenEShoot >= 10)
						evenEShoot = 0;
					else if(oddEShoot >= 10)
						oddEShoot = 0;
				}

				if(findCollision(go, m_ship))
				{
					go->active = false;
					m_lives --;
					m_ship->pos.Set(m_worldWidth * 0.5f, m_worldHeight * 0.5f, 0);
					m_ship->vel.SetZero();
					GodMode = true;
					GodModeTime = 3.0f;
				}
			}
			else if(go->type == GameObject::GO_ENEMY_LASER)
			{
				DeleteGONearScreen(go);
				go->pos.x +=  go->vel.x * 40 * (float)dt;
				go->pos.y +=  go->vel.y * 40 * (float)dt;

				if (findCollision(go, m_ship) && GodMode == false)
				{
					go->active = false;
					m_lives --;
					m_ship->pos.Set(m_worldWidth * 0.5f, m_worldHeight * 0.5f, 0);
					m_ship->vel.SetZero();
					GodMode = true;
					GodModeTime = 3.0f;
				}
			}
			else if(go->type == GameObject::GO_HEART)
			{
				WrapGONearScreen(go);

				if(findCollision(go, m_ship))
				{
					go->active = false;
					m_lives ++;
					heartCount--;
				}
				else if(findCollision(go, m_enemyShip))
				{
					go->active = false;
					heartCount--;
				}
			}
			else if(go->type == GameObject::GO_POWERUP_Ironman)
			{
				WrapGONearScreen(go);

				if(findCollision(go, m_ship))
				{
					go->active = false;
					powerUp = true;
				}
				else if(findCollision(go, m_enemyShip))
				{
					go->active = false;
					PUCount--;
				}
			}

			//Exercise 18: collision check between GO_BULLET and GO_ASTEROID_SMALL

			//=============================COLLISION CODE=============================//
			for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
			{
				GameObject *GotoCheck = (GameObject *)*it;

				if (go != GotoCheck && GotoCheck->active == true)
				{
					if (go->type == GameObject::GO_ASTEROID_BIG ||go->type == GameObject::GO_ASTEROID_SMALL)
					{
						if (GotoCheck->type == GameObject::GO_BULLET)
						{
							if (findCollision(go, GotoCheck))
							{
								GotoCheck->active = false;
								go->health -= GotoCheck->damage;
							}

							if(go->health <= 0)
							{
								go->active = false;
								m_score += 10;
								asteroidCount--;

								if (go->type == GameObject::GO_ASTEROID_BIG)
									SpawnAsteroid(go);
							}
						}
						else if(GotoCheck->type == GameObject::GO_ASTEROID_BIG || GotoCheck->type == GameObject::GO_ASTEROID_SMALL)
						{
							if (findCollision(go, GotoCheck))
							{
								go->vel = -go->vel;
								GotoCheck->vel = -GotoCheck->vel;
							}
						}
						else if(GotoCheck->type == GameObject::GO_BOMB || GotoCheck->type == GameObject::GO_MISSILE)
						{
							if(findCollision(go, GotoCheck))
							{
								GotoCheck->vel.SetZero();
								GotoCheck->type = GameObject::GO_EXPLOSION;
								GotoCheck->ScaleSize = 0;
							}
						}
						else if(GotoCheck->type == GameObject::GO_EXPLOSION)
						{
							if (findCollision(go, GotoCheck))
							{
								go->active = false;
								m_score += 5;
								asteroidCount--;
							}
						}
					}
					else if (go->type == GameObject::GO_BOMB)
					{
						if(GotoCheck->type == GameObject::GO_EXPLOSION ||
							GotoCheck->type == GameObject::GO_BULLET || 
							GotoCheck->type == GameObject::GO_ENEMY_LASER || 
							GotoCheck->type == GameObject::GO_MISSILE)
						{
							if(findCollision(go, GotoCheck))
							{
								go->type = GameObject::GO_EXPLOSION;
								go->vel.SetZero();

								if(GotoCheck->type == GameObject::GO_MISSILE)
								{
									GotoCheck->vel.SetZero();
									GotoCheck->type = GameObject::GO_EXPLOSION;
									GotoCheck->ScaleSize = 0;
								}
								else
									GotoCheck->active = false;
							}
						}
					}
					else if(go->type == GameObject::GO_EXPLOSION)
					{
						if(GotoCheck->type == GameObject::GO_MISSILE)
						{
							if(findCollision(go, GotoCheck))
							{
								GotoCheck->vel.SetZero();
								GotoCheck->type = GameObject::GO_EXPLOSION;
								GotoCheck->ScaleSize = 0;
							}
						}
						else if(GotoCheck->type == GameObject::GO_ENEMY)
						{
							if(findCollision(go, GotoCheck))
							{
								GotoCheck->active = false;
								if(lv2 == true)
								{
									lv2_killCount++;
								}
							}
						}
					}
					else if(go->type == GameObject::GO_ENEMY)
					{
						if(GotoCheck->type == GameObject::GO_BULLET)
						{
							if(findCollision(go, GotoCheck))
							{
								GotoCheck->active = false;
								go->health -= GotoCheck->damage;

								if(go->health <= 0)
								{
									go->active = false;
									m_score += 10;
									if(lv2 == true)
									{
										lv2_killCount++;
									}
								}
							}
						}
						else if(GotoCheck->type == GameObject::GO_BOMB || GotoCheck->type == GameObject::GO_MISSILE)
						{
							if(findCollision(go, GotoCheck))
							{
								GotoCheck->vel.SetZero();
								GotoCheck->type = GameObject::GO_EXPLOSION;
								GotoCheck->ScaleSize = 0;
							}
						}
					}
				}
			}
		}
	}
}

void SceneAsteroid::BossUpdate(float dt)
{
	if(m_enemyShip->type == GameObject::GO_BOSS || m_enemyShip->type == GameObject::GO_BOSS_SHIELD)
	{
		if(m_enemyShip->active == true)
		{
			static bool moveLeft = true;
			static bool moveRight = false;

			if(moveLeft == true && moveRight == false && m_enemyShip->pos.x > 0)
			{
				m_enemyShip->pos.x -= 10 * dt;
				if(m_enemyShip->pos.x <= 0)
				{
					m_enemyShip->pos.x = 0;
					moveLeft = false;
					moveRight = true;
				}
			}
			else if(moveRight == true && moveLeft == false && m_enemyShip->pos.x < m_worldWidth)
			{
				m_enemyShip->pos.x += 10 * dt;
				if(m_enemyShip->pos.x >= m_worldWidth)
				{
					m_enemyShip->pos.x = m_worldWidth;
					moveRight = false;
					moveLeft = true;
				}
			}

			static float m_bossShootGap = 0.f;
			m_bossShootGap += dt;

			if(fmod(m_bossShootGap, 5) >= 4.99f)
			{
				GameObject * newEbullet = FetchGO();
				newEbullet->type = GameObject::GO_ENEMY_LASER;
				newEbullet->scale.Set(3.f, 3.f, 3.f);

				newEbullet->pos.Set(m_enemyShip->pos.x, m_enemyShip->pos.y, m_enemyShip->pos.z);
				newEbullet->vel.Set(0, -3, 0);
				newEbullet->vel.Normalized();
			}

			if(m_enemyShip->type == GameObject::GO_BOSS)
			{
				m_enemyShip->m_shieldTime += dt;
			}
			else if(m_enemyShip->type == GameObject::GO_BOSS_SHIELD)
			{
				m_enemyShip->m_shieldTime -= dt/2;
			}

			if(m_enemyShip->type == GameObject::GO_BOSS && m_enemyShip->m_shieldTime >= 10)
			{
				m_enemyShip->type = GameObject::GO_BOSS_SHIELD;
			}
			else if(m_enemyShip->type == GameObject::GO_BOSS_SHIELD && m_enemyShip->m_shieldTime < 0)
			{
				m_enemyShip->type = GameObject::GO_BOSS;
			}

			if(m_enemyShip->health <= 0)
			{
				m_enemyShip->active = false;
			}

			if(findCollision(m_ship, m_enemyShip) && GodMode == false)
			{
				m_lives --;
				m_ship->pos.Set(m_worldWidth * 0.5f, m_worldHeight * 0.5f, 0);
				m_ship->vel.SetZero();
				GodMode = true;
				GodModeTime = 3.0f;
			}
		}
	}
}

void SceneAsteroid::SpawnUpdate(float dt)
{
	//Exercise 11: use a key to spawn some asteroids
	if (asteroidCount < 15)
	{
		GameObject *go = FetchGO();
		go->type = GameObject::GO_ASTEROID_BIG;
		go->scale.Set(10.f, 10.f, 10.f);
		go->pos.Set(Math::RandFloatMinMax(0, m_worldWidth), Math::RandFloatMinMax(0, m_worldHeight), go->pos.z);
		go->vel.Set(Math::RandFloatMinMax(-10, 10), Math::RandFloatMinMax(-10, 10) ,0);
		go->health = 3.0;

		asteroidCount ++;
	}

	if(heartCount < 1 && m_lives < 2)
	{
		GameObject *go = FetchGO();
		go->type = GameObject::GO_HEART;
		go->scale.Set(5.f, 5.f, 5.f);
		go->pos.Set(Math::RandFloatMinMax(0, m_worldWidth), Math::RandFloatMinMax(0, m_worldHeight), go->pos.z);
		go->vel.Set(Math::RandFloatMinMax(-10, 10), Math::RandFloatMinMax(-10, 10) ,0);

		heartCount ++;
	}

	if(fmod(totalTime, 10) >= 9.9 && PUCount < 1)
	{
		GameObject * go = FetchGO();
		go->type = GameObject::GO_POWERUP_Ironman;
		go->scale.Set(7.f, 7.f, 7.f);
		go->pos.Set(Math::RandFloatMinMax(0, m_worldWidth), Math::RandFloatMinMax(0, m_worldHeight), go->pos.z);
		go->vel.Set(Math::RandFloatMinMax(-10, 10), Math::RandFloatMinMax(-10, 10) ,0);

		PUCount ++;
	}

	if(powerUp == true && PUCount == 1)
	{
		powerUpTime -= (float)dt;

		if(powerUpTime <= 0)
		{
			powerUp = false;
			powerUpTime = 20.0f;
			PUCount--;
		}
	}

	if (enemyCount != 7 && lv2 == true)
	{
		for(unsigned a = 5; a < m_worldWidth; a += 20)
		{
			GameObject * go = FetchGO();
			go->active = true;
			go->type = GameObject::GO_ENEMY;
			go->scale.Set(12.f, 12.f, 12.f);
			go->pos.Set((float)a, 7.f, (float)go->pos.z);
			go->health = 10;
			go->vel.SetZero();
			enemyCount ++;
		}
	}
}

void SceneAsteroid::reset()
{
	menu.reset();

	m_lives = 3;
	m_score = 0;

	m_ship = new GameObject(GameObject::GO_SHIP);
	m_ship->active = true;
	m_ship->scale.Set(12, 12, 12);
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	m_ship->pos.Set(m_worldWidth * 0.5f, m_worldHeight * 0.5f, 0);
	m_ship->mass = 0.1f;

	m_enemyShip = new GameObject(GameObject::GO_BOSS);
	m_enemyShip->active = false;
	m_enemyShip->scale.Set(30.f, 30.f, 30.f);
	m_enemyShip->vel.SetZero();
	m_enemyShip->health = 150.f;
	m_enemyShip->setAngle(180);
	m_enemyShip->pos.Set(m_worldWidth, m_worldHeight - 10, 0);
	m_enemyShip->m_shieldTime = 0.f;

	//Set Paramters
	rotateShip = 0.f;
	bulletAngle = 0.f;
	BulletGapLimit = 0.5f;
	BombGapLimit = 0.5f;
	asteroidCount = 0;
	enemyCount = 0;
	evenEShoot = 0;
	oddEShoot = 0;
	heartCount = 0;
	totalTime = 0.f;
	PUCount = 0;
	powerUp = false;
	powerUpTime = 20.0f;
	GodMode = true;
	GodModeTime = 3.0f;
	Gameover = false;
	Won = false;
	lv1 = true;
	lv2 = false;
	lv3 = false;
	lv1_time = 0.f;
	lv2_killCount = 0;
	throwBomb = false;

	while(m_goList.size() > 0)
	{
		GameObject *go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}
}

void SceneAsteroid::shipUpdate(float dt)
{
	//Exercise 6: set m_force values based on WASD
	if(Application::IsKeyPressed('W'))
	{
		//m_force.Set(0, 10, 0);
		//m_force.y += 100 * dt;
		m_force.x += cos(Math::DegreeToRadian(rotateShip)) * 150 * (float)dt;
		m_force.y += sin(Math::DegreeToRadian(rotateShip)) * 150 * (float)dt;
	}
	if(Application::IsKeyPressed('A'))
	{
		//m_force.Set(-10, 0, 0);
		//m_force.x -= 100 * dt;
		rotateShip += 100 * (float)dt;
	}
	if(Application::IsKeyPressed('S'))
	{
		//m_force.Set(0, -10, 0);
		//m_force.y += 100 * dt;
		m_force.x -= cos(Math::DegreeToRadian(rotateShip)) * 100 * (float)dt;
		m_force.y -= sin(Math::DegreeToRadian(rotateShip)) * 100 * (float)dt;
	}
	if(Application::IsKeyPressed('D'))
	{
		//m_force.Set(10, 0, 0);
		//m_force.x += 100 * dt;
		rotateShip -= 100 * (float)dt;
	}

	//Exercise 8: use 2 keys to increase and decrease mass of ship
	if (Application::IsKeyPressed('K'))
	{
		m_ship->mass += 0.1f;
	}
	if (Application::IsKeyPressed('L'))
	{
		m_ship->mass -= 0.1f;
		if (m_ship->mass < 0.1f)
		{
			m_ship->mass = 0.1f;
		}
	}

	if(GodMode == true)
	{
		GodModeTime -= dt;
		if(GodModeTime <= 0)
		{
			GodMode = false;
		}
	}
	static float BulletTGap = 0.f;
	static float BombTGap = 0.f;
	static float elapsedTime1 = 0.f;


	elapsedTime1 = fmod((float)dt, 1);
	BulletTGap += elapsedTime1;

	if (BulletTGap > BulletGapLimit)
	{
		BulletTGap = BulletGapLimit;
	}

	//Exercise 14: use a key to spawn a bullet
	if (Application::IsKeyPressed(VK_SPACE))
	{
		if (BulletTGap >= BulletGapLimit)
		{
			GameObject * go = FetchGO();

			if(powerUp == true)
			{
				go->type = GameObject::GO_MISSILE;
				go->scale.Set(5.f, 5.f, 5.f);
				go->damage = 3.0;
				go->bombTime = 5.0;
				go->bombDuration = 1.2f;
			}
			else
			{
				go->type = GameObject::GO_BULLET;
				go->scale.Set(3.f, 3.f, 3.f);
				go->damage = 1.0;
			}

			go->pos.Set(m_ship->pos.x, m_ship->pos.y, m_ship->pos.z);
			go->setAngle(rotateShip);

			BulletTGap -= BulletGapLimit;
		}
	}

	if (Application::IsKeyPressed('E'))
	{
		if (throwBomb == false)
		{
			GameObject * go = FetchGO();

			go->type = GameObject::GO_BOMB;
			go->scale.Set(3.f, 3.f, 3.f);
			go->pos.Set(m_ship->pos.x, m_ship->pos.y, m_ship->pos.z);
			go->setAngle(rotateShip);
			go->bombTime = 5.0;
			go->bombDuration = 1.2f;
			go->ScaleSize = 0;
			go->damage = 5.0;
			if(m_ship->vel.IsZero())
				go->vel.Set(1, 0, 0);
			else
				go->vel = m_ship->vel;
			go->vel.Normalize();
			throwBomb = true;
		}
	}

	//Physics Simulation Section

	//Exercise 7: Update ship's velocity based on m_force
	Vector3 acc = m_force * (1.f / m_ship->mass);
	m_ship->vel += acc * (float)dt;
	m_ship->pos += m_ship->vel * (float)dt;

	//limit speed
	if (m_ship->vel.Length() > 200)
	{
		m_ship->vel.Normalize();
		m_ship->vel *= MAX_SPEED;
	}

	//Exercise 9: wrap ship position if it leaves screen
	WrapGONearScreen(m_ship);
}

void SceneAsteroid::Update(double dt)
{
	if (menu.getStartGame() == false)
	{
		menu.MenuUpdate((float) dt);
		if(Application::IsKeyPressed(VK_TAB))
		{
			reset();
		}
	}
	else if(menu.getStartGame() == true)
	{
		SceneBase::Update(dt);

		if(Application::IsKeyPressed(VK_TAB))
		{
			reset();
		}

		if(Application::IsKeyPressed('9'))
		{
			m_speed = Math::Max(0.f, m_speed - 0.1f);
		}
		if(Application::IsKeyPressed('0'))
		{
			m_speed += 0.1f;
		}
		dt *= m_speed;
		m_force.SetZero();

		//Mouse Section
		static bool bLButtonState = false;
		if(!bLButtonState && Application::IsMousePressed(0))
		{
			bLButtonState = true;
			std::cout << "LBUTTON DOWN" << std::endl;
		}
		else if(bLButtonState && !Application::IsMousePressed(0))
		{
			bLButtonState = false;
			std::cout << "LBUTTON UP" << std::endl;
		}
		static bool bRButtonState = false;
		if(!bRButtonState && Application::IsMousePressed(1))
		{
			bRButtonState = true;
			std::cout << "RBUTTON DOWN" << std::endl;
		}
		else if(bRButtonState && !Application::IsMousePressed(1))
		{
			bRButtonState = false;
			std::cout << "RBUTTON UP" << std::endl;
		}

		totalTime += (float)dt;

		if(m_lives <= 0)
		{
			Gameover = true;
		}
		else if(m_enemyShip->health <= 0)
		{
			m_enemyShip->active = false;
			Won = true;
		}

		if(lv1 == true && lv2 == false && lv3 == false)
		{
			if(lv1_time < 30)
			{
				lv1_time += dt;
			}
			else
			{
				lv2 = true;
			}
		}
		else if(lv1 == true && lv2 == true && lv3 == false)
		{
			if(lv2_killCount >= 6)
			{
				lv3 = true;
			}
		}
		else if (lv1 == true && lv2 == true && lv3 == true)
		{
			for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
			{
				GameObject *go = (GameObject *)*it;
				if(go->type == GameObject::GO_ENEMY)
				{
					go->active = false;
				}
			}

			if(m_enemyShip->active == false)
			{
				m_enemyShip->active = true;
			}
		}

		GOUpdate((float) dt);
		BossUpdate((float) dt);
		SpawnUpdate((float) dt);
		shipUpdate((float) dt);
	}
}


void SceneAsteroid::RenderGO(GameObject *go)
{
	switch(go->type)
	{
	case GameObject::GO_SHIP:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Rotate(rotateShip, 0, 0, 1);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[Spaceship], false);
		modelStack.PopMatrix();
		break;

		//Exercise 17a: render a ship texture or 3D ship model
		//Exercise 17b:	re-orientate the ship with velocity
		break;

	case GameObject::GO_ASTEROID_SMALL:
		//Exercise 4b: render a cube with length 2
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[Asteroid_Sprite], false);
		modelStack.PopMatrix();
		break;

	case GameObject::GO_ASTEROID_BIG:
		//Exercise 4b: render a cube with length 2
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[Asteroid_Sprite], false);
		modelStack.PopMatrix();
		break;

	case GameObject::GO_BULLET:
		//Exercise 4b: render a cube with length 2
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Rotate(go->angle, 0, 0, 1);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[Laser], false);
		modelStack.PopMatrix();
		break;

	case GameObject::GO_BOMB:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Rotate(go->angle, 0, 0, 1);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[Bomb], false);
		modelStack.PopMatrix();
		break;

	case GameObject::GO_EXPLOSION:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[Explosion_Asteroid], false);
		modelStack.PopMatrix();
		break;

	case GameObject::GO_ENEMY:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[Enemy], false);
		modelStack.PopMatrix();
		break;

	case GameObject::GO_ENEMY_LASER:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[Enemy_Laser], false);
		modelStack.PopMatrix();
		break;

	case GameObject::GO_HEART:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[heart], false);
		modelStack.PopMatrix();
		break;

	case GameObject::GO_MISSILE:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Rotate(go->angle, 0, 0, 1);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[Missile], false);
		modelStack.PopMatrix();
		break;

	case GameObject::GO_POWERUP_Ironman:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[PowerUp_Ironman], false);
		modelStack.PopMatrix();
		break;

	case GameObject::GO_BOSS:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Rotate(go->angle, 0, 0, 1);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[Boss], false);
		modelStack.PopMatrix();
		break;

	case GameObject::GO_BOSS_SHIELD:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Rotate(go->angle, 0, 0, 1);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[Boss_Shield], false);
		modelStack.PopMatrix();
		break;

	}
}

void SceneAsteroid::RenderMenu()
{
	if(menu.getShowControl() == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(66.f, 50.f, 8.f);
		modelStack.Scale(160, 160, 160);
		RenderMesh(meshList[ShowControl], false);
		modelStack.PopMatrix();
	}
	else
	{
		modelStack.PushMatrix();
		modelStack.Translate(66.f, 50.f, 8.f);
		modelStack.Scale(160, 160, 160);
		RenderMesh(meshList[StartMenu], false);
		modelStack.PopMatrix();

		if(menu.StartConfirm() == true)
		{
			modelStack.PushMatrix();
			modelStack.Translate(68.f, 20.f, 9.f);
			modelStack.Scale(80, 80, 80);
			RenderMesh(meshList[StartTrue], false);
			modelStack.PopMatrix();
		}
		else if(menu.ControlConfirm() == true)
		{
			modelStack.PushMatrix();
			modelStack.Translate(68.f, 20.f, 9.f);
			modelStack.Scale(80, 80, 80);
			RenderMesh(meshList[ControlTrue], false);
			modelStack.PopMatrix();
		}
		else if(menu.ExitConfirm() == true)
		{
			modelStack.PushMatrix();
			modelStack.Translate(68.f, 20.f, 9.f);
			modelStack.Scale(80, 80, 80);
			RenderMesh(meshList[ExitTrue], false);
			modelStack.PopMatrix();
		}
	}
}

void SceneAsteroid::RenderScene()
{
	modelStack.PushMatrix();
	modelStack.Translate(66.f, 33.f, -8.f);
	modelStack.Scale(135.f, 135.f, 135.f);
	RenderMesh(meshList[Background], false);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(20.f, 97.5f ,-7.f);
	modelStack.Scale(40, 40, 40);
	RenderMesh(meshList[HUD], false);
	modelStack.PopMatrix();

	for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if(go->active)
		{
			RenderGO(go);
		}
	}

	RenderGO(m_ship);

	if(m_enemyShip->active)
	{
		RenderGO(m_enemyShip);
	}


	//On screen text
	//Exercise 5a: Render m_lives, m_score
	std::ostringstream ss3;
	ss3.precision(3);
	ss3 << m_lives << "					" << m_score;
	RenderTextOnScreen(meshList[GEO_TEXT], ss3.str(), Color(1, 1, 1), 3.f, 6.5f, 57.1f);

	//Exercise 5b: Render position, velocity & mass of ship
	/*std::ostringstream ss4;
	ss4.precision(3);
	ss4 << "Position: " << m_ship->pos;
	RenderTextOnScreen(meshList[GEO_TEXT], ss4.str(), Color(0, 1, 0), 3, 0, 12);

	std::ostringstream ss5;
	ss5.precision(3);
	ss5 << "Velocity: " << m_ship->vel;
	RenderTextOnScreen(meshList[GEO_TEXT], ss5.str(), Color(0, 1, 0), 3, 0, 15);

	std::ostringstream ss6;
	ss6.precision(3);
	ss6 << "Mass: " << m_ship->mass;
	RenderTextOnScreen(meshList[GEO_TEXT], ss6.str(), Color(0, 1, 0), 3, 0, 18);

	std::ostringstream ss2;
	ss2.precision(3);
	ss2 << "Speed: " << m_speed;
	RenderTextOnScreen(meshList[GEO_TEXT], ss2.str(), Color(0, 1, 0), 3, 0, 6);*/

	modelStack.PushMatrix();
	modelStack.Translate(15, 2, 10);
	modelStack.Scale(30, 10, 20);
	RenderMesh(meshList[black_background], false);
	modelStack.PopMatrix();
	std::ostringstream ss7;
	ss7.precision(3);
	ss7 << "Time:" << totalTime;
	RenderTextOnScreen(meshList[GEO_TEXT], ss7.str(), Color(1, 1, 1), 3, 0, 1);


	modelStack.PushMatrix();
	modelStack.Translate(128, 99, 10);
	modelStack.Scale(30, 10, 20);
	RenderMesh(meshList[black_background], false);
	modelStack.PopMatrix();
	std::ostringstream ss;
	ss.precision(5);
	ss << "FPS:" << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 1, 1), 3.f, 69.f, 57.1f);
}

void SceneAsteroid::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);

	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	if(menu.getStartGame() == false)
	{
		RenderMenu();
	}
	else if (menu.getStartGame() == true && Gameover == false && Won == false)
	{
		RenderScene();
	}
	else if (Gameover == true && Won == false)
	{
		modelStack.PushMatrix();
		modelStack.Translate(66.f, 50.f, 8.f);
		modelStack.Scale(160, 160, 160);
		RenderMesh(meshList[GameoverScreen], false);
		modelStack.PopMatrix();
	}
	else if(Gameover == false && Won == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(66.f, 50.f, 8.f);
		modelStack.Scale(170, 170, 170);
		RenderMesh(meshList[WinScreen], false);
		modelStack.PopMatrix();
	}
}

void SceneAsteroid::Exit()
{
	SceneBase::Exit();
	//Cleanup GameObjects
	while(m_goList.size() > 0)
	{
		GameObject *go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}
	if(m_ship)
	{
		delete m_ship;
		m_ship = NULL;
	}

	if(m_enemyShip)
	{
		delete m_enemyShip;
		m_enemyShip = NULL;
	}
}