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

	//Exercise 2a: Construct 100 GameObject with type GO_ASTEROID and add into m_goList_Asteroid
	for (unsigned i = 0; i < 100; ++i)
	{
		GameObject *go = new GameObject(GameObject::GO_ASTEROID);
		m_goList_Asteroid.push_back(go);
	}

	
	//Exercise 2b: Initialize m_lives and m_score
	m_lives = 3;
	m_score = 0;

	//Exercise 2c: Construct m_ship, set active, type, scale and pos
	m_ship = new GameObject(GameObject::GO_SHIP);
	m_ship->active = true;
	//m_ship->scale.Set(12, 12, 12);
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();
	m_ship->pos.Set(m_worldWidth * 0.5f, m_worldHeight * 0.5f, 0);
	m_ship->mass = 0.1f;

	//Set Paramters
	rotateShip = 0.f;
	bulletAngle = 0.f;
	BulletGapLimit = 0.5f;
}

GameObject* SceneAsteroid::FetchGO()
{
	//Exercise 3a: Fetch a game object from m_goList_Asteroid and return it
	for(std::vector<GameObject *>::iterator it = m_goList_Asteroid.begin(); it != m_goList_Asteroid.end(); ++it)
	{
		GameObject * go = (GameObject*)*it;
		if (!go->active)
		{
			go->active = true;
			return go;
		}
	}

	//Exercise 3b: Handle the situation whenever m_goList_Asteroid runs out of objects
	for (unsigned i = 0; i < 10; ++i)
	{
		GameObject *go = new GameObject(GameObject::GO_ASTEROID);
		m_goList_Asteroid.push_back(go);
	}

	GameObject *go = m_goList_Asteroid.back();
	go->active = true;

	return go;
}

GameObject* SceneAsteroid::FetchGO2()
{
	//Exercise 3a: Fetch a game object from m_goList_Asteroid and return it
	for(std::vector<GameObject *>::iterator it = m_goList_Bullet.begin(); it != m_goList_Bullet.end(); ++it)
	{
		GameObject * go = (GameObject*)*it;
		if (!go->active)
		{
			go->active = true;
			return go;
		}
	}

	//Exercise 3b: Handle the situation whenever m_goList_Asteroid runs out of objects
	for (unsigned i = 0; i < 10; ++i)
	{
		GameObject *go = new GameObject(GameObject::GO_BULLET);
		m_goList_Bullet.push_back(go);
	}

	GameObject *go = m_goList_Bullet.back();
	go->active = true;

	return go;
}

void SceneAsteroid::GOUpdate(float dt)
{
	for(std::vector<GameObject *>::iterator it = m_goList_Asteroid.begin(); it != m_goList_Asteroid.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if(go->active)
		{
			//Exercise 12: handle collision between GO_SHIP and GO_ASTEROID using simple distance-based check
			if(go->type == GameObject::GO_ASTEROID)
			{
				float distSquared = (go->pos - m_ship->pos).LengthSquared();
				float combinedRadius = go->scale.x * 3 + m_ship->scale.x * 3;

				if (distSquared <= combinedRadius * combinedRadius)
				{
					go->active = false;
					m_lives --;
					m_ship->pos.Set(m_worldWidth * 0.5f, m_worldHeight * 0.5f, 0);
					m_ship->vel.SetZero();
				}

				//Exercise 13: asteroids should wrap around the screen like the ship
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
			go->pos += go->vel * dt;


			//Exercise 18: collision check between GO_BULLET and GO_ASTEROID
			for(std::vector<GameObject *>::iterator bulletIT = m_goList_Bullet.begin(); bulletIT != m_goList_Bullet.end(); ++bulletIT)
			{
				GameObject *bullet = (GameObject *)*bulletIT;
				//Exercise 16: unspawn bullets when they leave screen
				if (bullet->type == GameObject::GO_BULLET)
				{
					if((bullet->pos - go->pos).Length() < 2)
					{
						go->active = bullet->active = false;
						this->m_score += 1;
					}
				}
			}
		}
	}


	for(std::vector<GameObject *>::iterator it = m_goList_Bullet.begin(); it != m_goList_Bullet.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		//Exercise 16: unspawn bullets when they leave screen
		if (go->type == GameObject::GO_BULLET)
		{
			if(go->pos.x > m_worldWidth || go->pos.x < 0 || go->pos.y > m_worldHeight || go->pos.y < 0)
			{
				go->active = false;
			}

			//If bullet is still active, it will keep moving in the angle that it was given
			go->pos.x += cos(Math::DegreeToRadian(go->angle)) * (float)go->bulletSpeed * (float)dt;
			go->pos.y += sin(Math::DegreeToRadian(go->angle)) * (float)go->bulletSpeed * (float)dt;
		}
	}
}

void SceneAsteroid::Update(double dt)
{
	SceneBase::Update(dt);
	
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
	//Exercise 6: set m_force values based on WASD
	if(Application::IsKeyPressed('W'))
	{
		//m_force.Set(0, 10, 0);
		//m_force.y += 100 * dt;
		m_force.x += cos(Math::DegreeToRadian(rotateShip)) * 100 * (float)dt;
		m_force.y += sin(Math::DegreeToRadian(rotateShip)) * 100 * (float)dt;
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
		m_force.y -= sin(Math::DegreeToRadian(rotateShip)) * 100* (float)dt;
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


	//Exercise 11: use a key to spawn some asteroids
	if (Application::IsKeyPressed('V'))
	{
		GameObject * go = FetchGO();
		go->type = GameObject::GO_ASTEROID;
		go->scale.Set(1.f, 1.f, 1.f);

		go->pos.Set(Math::RandFloatMinMax(0, m_worldWidth), Math::RandFloatMinMax(0, m_worldHeight), 0);
		go->vel.Set(Math::RandFloatMinMax(-10, 10), Math::RandFloatMinMax(-10, 10) ,0);

	}

	static float BulletTGap = 0.f;
	static float elapsedTime1 = 0.f;

	elapsedTime1 = fmod((float)dt, 1);

	if (BulletTGap <= BulletGapLimit)
	{
		BulletTGap += elapsedTime1;
	}

	//Exercise 14: use a key to spawn a bullet
	if (Application::IsKeyPressed(VK_SPACE))
	{
		if (BulletTGap >= BulletGapLimit)
		{
			GameObject * go = FetchGO2();
			go->type = GameObject::GO_BULLET;
			go->scale.Set(1.f, 1.f, 1.f);

			
			go->pos.Set(m_ship->pos.x, m_ship->pos.y, m_ship->pos.z);
			go->setAngle(rotateShip);
			BulletTGap -= BulletGapLimit;
		}
	}

	//Exercise 15: limit the spawn rate of bullets

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

	//Physics Simulation Section

	//Exercise 7: Update ship's velocity based on m_force
	Vector3 acc = m_force * (1.f / m_ship->mass);
	m_ship->vel += acc * (float)dt;
	m_ship->pos += m_ship->vel * (float)dt;

	//limit speed
	if (m_ship->vel.Length() > MAX_SPEED)
	{
		m_ship->vel.Normalize();
		m_ship->vel *= MAX_SPEED;
	}

	//Exercise 9: wrap ship position if it leaves screen
	if(m_ship->pos.x > m_worldWidth)
	{
		m_ship->pos.x = 0;
	}
	else if(m_ship->pos.x < 0)
	{
		m_ship->pos.x = m_worldWidth;
	}

	if(m_ship->pos.y > m_worldHeight)
	{
		m_ship->pos.y = 0;
	}
	else if(m_ship->pos.y < 0)
	{
		m_ship->pos.y = m_worldHeight;
	}

	GOUpdate((float) dt);
}


void SceneAsteroid::RenderGO(GameObject *go)
{
	switch(go->type)
	{
	case GameObject::GO_SHIP:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Rotate(rotateShip, 0, 0, 1);
		modelStack.Scale(go->scale.x * 12, go->scale.y * 12, go->scale.z);
		if (Application::IsKeyPressed('W'))
		{
			//If i press W, render the thruster
			RenderMesh(meshList[Spaceship_Thurster], false);
		}
		else if (Application::IsKeyPressed('S'))
		{
			//If i press S, render the thruster
			RenderMesh(meshList[SpaceShip_Thurster_back], false);
		}
		else
		{
			RenderMesh(meshList[Spaceship], false);
		}
		modelStack.PopMatrix();
		break;

		//Exercise 17a: render a ship texture or 3D ship model
		//Exercise 17b:	re-orientate the ship with velocity
		break;

	case GameObject::GO_ASTEROID:
		//Exercise 4b: render a cube with length 2
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, 0);
		modelStack.Scale(go->scale.x * 5, go->scale.y * 5, go->scale.z);
		RenderMesh(meshList[Asteroid_Sprite], false);
		modelStack.PopMatrix();
		break;

	case GameObject::GO_BULLET:
		//Exercise 4b: render a cube with length 2
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Rotate(rotateShip, 0, 0, 1);
		modelStack.Scale(go->scale.x * 3, go->scale.y * 3, go->scale.z);
		RenderMesh(meshList[Laser], false);
		modelStack.PopMatrix();
		break;
	}
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
	
	RenderMesh(meshList[GEO_AXES], false);

	for(std::vector<GameObject *>::iterator it = m_goList_Asteroid.begin(); it != m_goList_Asteroid.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if(go->active)
		{
			RenderGO(go);
		}
	}

	for(std::vector<GameObject *>::iterator it = m_goList_Bullet.begin(); it != m_goList_Bullet.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if(go->active)
		{
			RenderGO(go);
		}
	}
	RenderGO(m_ship);

	//On screen text

	//Exercise 5a: Render m_lives, m_score
	std::ostringstream ss3;
	ss3.precision(3);
	ss3 << "Lives: " << m_lives << " Scores: " << m_score;
	RenderTextOnScreen(meshList[GEO_TEXT], ss3.str(), Color(0, 1, 0), 3, 0, 9);

	//Exercise 5b: Render position, velocity & mass of ship
	std::ostringstream ss4;
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
	RenderTextOnScreen(meshList[GEO_TEXT], ss2.str(), Color(0, 1, 0), 3, 0, 6);
	
	std::ostringstream ss;
	ss.precision(5);
	ss << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 3);
	
	RenderTextOnScreen(meshList[GEO_TEXT], "Asteroid", Color(0, 1, 0), 3, 0, 0);
}

void SceneAsteroid::Exit()
{
	SceneBase::Exit();
	//Cleanup GameObjects
	while(m_goList_Asteroid.size() > 0)
	{
		GameObject *go = m_goList_Asteroid.back();
		delete go;
		m_goList_Asteroid.pop_back();
	}
	if(m_ship)
	{
		delete m_ship;
		m_ship = NULL;
	}
}
