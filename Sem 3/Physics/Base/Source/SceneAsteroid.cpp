#include "SceneAsteroid.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>
#include "vld.h"

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
	for (unsigned i = 0; i < 100; ++i)
	{
	GameObject *go = new GameObject(GameObject::GO_ASTEROID_SMALL);
	go->scale.Set(10, 10, 0);
	m_goList.push_back(go);
	}


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
	m_ship->SetData(m_ship->pos, Vector3(1, 0, 0), Vector3(1, 0, 0));

	//Set Paramters
	rotateShip = 0.f;
	bulletAngle = 0.f;
	BulletGapLimit = 0.5f;
}

GameObject* SceneAsteroid::FetchGO()
{
	//Exercise 3a: Fetch a game object from m_goList and return it
	for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject * go = (GameObject*)*it;
		if (!go->active)
		{
			go->active = true;
			return go;
		}
	}

	//Exercise 3b: Handle the situation whenever m_goList runs out of objects6
	for (unsigned i = 0; i < 1; ++i)
	{
		GameObject *go = new GameObject(GameObject::GO_ASTEROID_SMALL);
		m_goList.push_back(go);
	}

	GameObject *go = m_goList.back();
	go->active = true;

	return go;
}

void SceneAsteroid::wrapGONearScreen(GameObject* go)
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

void SceneAsteroid::deleteGONearScreen(GameObject* go)
{
	if(go->pos.x > m_worldWidth || go->pos.x < 0 || go->pos.y > m_worldHeight || go->pos.y < 0)
	{
		go->active = false;
	}
}

void SceneAsteroid::moveBullet(GameObject * go, double dt)
{
	go->pos.x += cos(Math::DegreeToRadian(go->angle)) * BULLET_SPEED * (float)dt;
	go->pos.y += sin(Math::DegreeToRadian(go->angle)) * BULLET_SPEED * (float)dt;
}

void SceneAsteroid::SpawnAsteroid(GameObject *go)
{
	for (int a = 0; a < 2; ++a)
	{
		GameObject * newA = FetchGO();
		newA->type = GameObject::GO_ASTEROID_SMALL;
		newA->scale.Set(5.f, 5.f, 5.f);

		newA->pos.Set(Math::RandFloatMinMax(go->pos.x + 5, go->pos.x - 5), 
			Math::RandFloatMinMax(go->pos.y + 5, go->pos.y - 5) ,0);

		newA->vel.Set(Math::RandFloatMinMax(-30, 30), Math::RandFloatMinMax(-30, 30) ,0);
	}
}
/*
float distSquared = (go->pos - m_ship->pos).length();


*/
void SceneAsteroid::CollisionForAsteroid(GameObject * go, double dt)
{
	//Exercise 12: handle collision between GO_SHIP and GO_ASTEROID_SMALL using simple distance-based check
	if ((go->pos - m_ship->pos).LengthNZ() < 10 && go->type == GameObject::GO_ASTEROID_BIG)
	{
		go->active = false;
		m_lives --;
		m_ship->pos.Set(m_worldWidth * 0.5f, m_worldHeight * 0.5f, 0);
		m_ship->vel.SetZero();
	}
	else if ((go->pos - m_ship->pos).LengthNZ() < 5 && go->type == GameObject::GO_ASTEROID_SMALL)
	{
		go->active = false;
		m_lives --;
		m_ship->pos.Set(m_worldWidth * 0.5f, m_worldHeight * 0.5f, 0);
		m_ship->vel.SetZero();
	}

	//Exercise 13: asteroids should wrap around the screen like the ship
	wrapGONearScreen(go);
}

void SceneAsteroid::AsteroidCollision(GameObject *go, GameObject *GOtoCheck)
{
	if (go->type == GameObject::GO_ASTEROID_BIG && GOtoCheck->type == GameObject::GO_ASTEROID_BIG)
	{
		if((go->pos - GOtoCheck->pos).LengthNZ() < 10)
		{
			BouncingAsteroid(go, GOtoCheck);
		}
	}
	else if(go->type == GameObject::GO_ASTEROID_BIG && GOtoCheck->type == GameObject::GO_ASTEROID_SMALL)
	{
		if((go->pos - GOtoCheck->pos).LengthNZ() < 4)
		{
			BouncingAsteroid(go, GOtoCheck);
		}
	}
	else if(go->type == GameObject::GO_ASTEROID_SMALL && 
		GOtoCheck->type == GameObject::GO_ASTEROID_SMALL)
	{
		if((go->pos - GOtoCheck->pos).LengthNZ() < 2)
		{
			BouncingAsteroid(go, GOtoCheck);
		}
	}
}

void SceneAsteroid::BouncingAsteroid(GameObject *go, GameObject *GOtoCheck)
{
	/*go->vel.Set(Math::RandFloatMinMax(-10, 10), Math::RandFloatMinMax(-10, 10) ,0);
	GOtoCheck->vel.Set(Math::RandFloatMinMax(-10, 10), Math::RandFloatMinMax(-10, 10) ,0);*/
	go->vel = -go->vel;
	GOtoCheck->vel = -GOtoCheck->vel;
}

void SceneAsteroid::deleteTwoGO(GameObject *go, GameObject *GOtoCheck)
{
	go->active = GOtoCheck->active = false;
}

void SceneAsteroid::GOUpdate(float dt)
{
	for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if(go->active)
		{
			if (go->type == GameObject::GO_ASTEROID_SMALL || go->type == GameObject::GO_ASTEROID_BIG)
			{
				CollisionForAsteroid(go, dt);
			}
			else if (go->type == GameObject::GO_ENEMY)
			{
				//CollisionForAsteroid(go, dt);
			}
			else if (go->type == GameObject::GO_BULLET)
			{
				deleteGONearScreen(go);
				moveBullet(go, dt);
			}

			go->pos += go->vel * dt;

			//Collision for Asteroid
			for(std::vector<GameObject *>::iterator it2 = m_goList.begin(); it2 != m_goList.end(); ++it2)
			{
				GameObject *GOtoCheck = (GameObject *)*it2;

				if (go->type == GameObject::GO_ASTEROID_BIG || go->type == GameObject::GO_ASTEROID_SMALL)
				{
					if(GOtoCheck->type == GameObject::GO_BULLET)
					{
						if(go->type == GameObject::GO_ASTEROID_BIG && (go->pos - GOtoCheck->pos).LengthNZ() < 5)
						{
							deleteTwoGO(go, GOtoCheck);
							SpawnAsteroid(go);
						}
						else if(go->type == GameObject::GO_ASTEROID_SMALL && (go->pos - GOtoCheck->pos).LengthNZ() < 2)
						{
							deleteTwoGO(go, GOtoCheck);
						}
					}
					else if(GOtoCheck->type == GameObject::GO_ASTEROID_BIG || GOtoCheck->type == GameObject::GO_ASTEROID_SMALL)
					{
						if (go != GOtoCheck)
						{
							AsteroidCollision(go, GOtoCheck);
						}
					}
				}
			}
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
		m_force.x += cos(Math::DegreeToRadian(rotateShip)) * 200 * (float)dt;
		m_force.y += sin(Math::DegreeToRadian(rotateShip)) * 200 * (float)dt;
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
		m_force.x -= cos(Math::DegreeToRadian(rotateShip)) * 200 * (float)dt;
		m_force.y -= sin(Math::DegreeToRadian(rotateShip)) * 200 * (float)dt;
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
		go->type = GameObject::GO_ASTEROID_BIG;
		go->scale.Set(10.f, 10.f, 10.f);

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
	//Exercise 15: limit the spawn rate of bullets
	if (Application::IsKeyPressed(VK_SPACE))
	{
		if (BulletTGap >= BulletGapLimit)
		{
			GameObject * go = FetchGO();
			go->type = GameObject::GO_BULLET;
			go->scale.Set(3.f, 3.f, 3.f);

			go->pos.Set(m_ship->pos.x, m_ship->pos.y, m_ship->pos.z);
			go->setAngle(rotateShip);

			go->vel.IsZero();
			BulletTGap -= BulletGapLimit;
		}
	}

	if (Application::IsKeyPressed('U'))
	{
		if (BulletTGap >= BulletGapLimit)
		{
			for (unsigned a = 10; a < m_worldWidth; a+=20)
			{
				GameObject * go = FetchGO();
				go->type = GameObject::GO_ENEMY;
				go->scale.Set(13.f, 13.f, 13.f);

				go->pos.Set(a, 3, 0);

				go->vel.Set(0, 1 ,0);
				go->vel.Normalize();
			}
		}
	}

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
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[Spaceship], false);
		modelStack.PopMatrix();
		break;

		//Exercise 17a: render a ship texture or 3D ship model
		//Exercise 17b:	re-orientate the ship with velocity

	case GameObject::GO_ASTEROID_SMALL:
		//Exercise 4b: render a cube with length 2
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, -1);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[Asteroid_Sprite], false);
		modelStack.PopMatrix();
		break;

	case GameObject::GO_ASTEROID_BIG:
		//Exercise 4b: render a cube with length 2
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, -1);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[Asteroid_Sprite], false);
		modelStack.PopMatrix();
		break;

	case GameObject::GO_BULLET:
		//Exercise 4b: render a cube with length 2
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Rotate(go->angle, 0, 0, 1);
		modelStack.Scale(go->scale.x, go->scale.y , go->scale.z);
		RenderMesh(meshList[Laser], false);
		modelStack.PopMatrix();
		break;

	case GameObject::GO_ENEMY:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Rotate(go->angle, 0, 0, 1);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[Enemy_SpaceShip], false);
		modelStack.PopMatrix();
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

	modelStack.PushMatrix();
	modelStack.Translate(100.247, 0, -4);
	modelStack.Scale(200.875, 200.875, 0);
	RenderMesh(meshList[Background], false);
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
}
