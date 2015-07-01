#include "SceneCollision.h"
#include "GL\glew.h"
#include "Application.h"
#include <sstream>

SceneCollision::SceneCollision()
{
}

SceneCollision::~SceneCollision()
{
}

void SceneCollision::Init()
{
	SceneBase::Init();

	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();

	m_objectCount = 0;

	m_ghost = new GameObject(GameObject::GO_BALL);
}

GameObject* SceneCollision::FetchGO()
{
	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (!go->active)
		{
			go->active = true;
			++m_objectCount;
			return go;
		}
	}
	for (unsigned i = 0; i < 10; ++i)
	{
		GameObject *go = new GameObject(GameObject::GO_BALL);
		m_goList.push_back(go);
	}
	GameObject *go = m_goList.back();
	go->active = true;
	++m_objectCount;
	return go;
}

bool SceneCollision::CheckCollision(GameObject *go1, GameObject *go2, float dt)
{
	//Exercise 1: move collision code to CheckCollision()
	float distSquared = (go1->pos - go2->pos).LengthSquared();
	float combinedRadius = go1->scale.x + go2->scale.x;
	Vector3 c = go1->vel - go2->vel;
	Vector3 d = go2->pos - go1->pos;

	//Practical 4, Exercise 13: improve collision detection algorithm
	if (distSquared <= combinedRadius * combinedRadius &&c.Dot(d) > 0)
		return true;
	else
		return false;
}

void SceneCollision::GOUpdate(const double dt)
{
	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go->active)
		{ 
			go->pos += go->vel * static_cast<float>(dt);

			//Exercise 2a: Rebound game object at screen edges

			//Exercise 2b: Unspawn if it really leave the screen
			/*	if (go->pos.x > m_worldWidth || go->pos.x < 0 || go->pos.y > m_worldHeight || go->pos.y < 0)
			{
			go->active = false;
			--m_objectCount;
			}*/
			initialKE = 0.5f * m1 * u1.Dot(u1) + 0.5f * m2 * u2.Dot(u2);
			finalKE = 0.5f * m1 * v1.Dot(v1) + 0.5f * m2 * v2.Dot(v2);

			/*if (go->pos.x > m_worldWidth || go->pos.x < 0)
			{
				go->vel.x = -go->vel.x;
			}*/
			if (go->pos.x > m_worldWidth - go->scale.x && go->vel.x > 0)
			{
				go->vel.x = -go->vel.x;
			}
			else if(go->pos.x < 0 + go->scale.x && go->vel.x < 0)
			{
				go->vel.x = -go->vel.x;
			}

			if (go->pos.y > m_worldHeight - go->scale.x && go->vel.y > 0)
			{
				go->vel.y = -go->vel.y;
			}
			else if (go->pos.y < 0 + go->scale.x && go->vel.y < 0)
			{
				go->vel.y = -go->vel.y;
			}

			if (go->pos.x > m_worldWidth + 5 || go->pos.x < -5 || go->pos.y > m_worldHeight + 5 || go->pos.y < -5)
			{
				go->active = false;
				this->m_objectCount--;
			}

			/*if (go->pos.y > m_worldHeight || go->pos.y < 0)
			{
				go->vel.y = -go->vel.y;
			}*/


			for (std::vector<GameObject *>::iterator it2 = it + 1; it2 != m_goList.end(); ++it2)
			{
				GameObject *go2 = static_cast<GameObject *>(*it2);
				if (go2->active)
				{
					//Practical 4, Exercise 13: improve collision detection algorithm
					if (CheckCollision(go, go2, dt))
					{
						initialMomentum = go->mass * go->vel + go2->mass * go2->vel;

						//getting the translateDist
						Vector3 posDiff = go->pos - go2->pos;
						//Mininum translate distance to push ball after intersecting
						Vector3 translateDist = posDiff *(((go->scale.x + go2->scale.x)) - posDiff.Length() / posDiff.Length());

						//inverse mass quantities
						float im1 = 1 / go->mass;
						float im2 = 1 / go2->mass;

						//Impact speed
						Vector3 velDiff = (go->vel - go2->vel);
						float velNormalize = velDiff.Dot(translateDist.Normalize());

						//Collision impulse
						float i = (-(1.f + 1) * velNormalize) / (im1 + im2);
						Vector3 impulse = translateDist * i;

						//Change in momentum
						go->vel = go->vel + (impulse * im1);
						go2->vel = go2->vel - (impulse * im2);

						finalMomentum = go->mass * go->vel + go2->mass * go2->vel;

						/*m1 = go->mass;
						m2 = go2->mass;
						u1 = go->vel;
						u2 = go2->vel;

						Vector3 N = (go2->pos - go->pos).Normalized();
						Vector3 u1N = u1.Dot(N) * N;
						Vector3 u2N = u2.Dot(N) * N;

						go->vel = u1 + 2 * m2 / (m1 + m2) * (u2N - u1N);
						go2->vel = u2 + 2 * m1 / (m2 + m1) * (u1N - u2N);*/
					}
				}
			}
		}
	}
}

void SceneCollision::Update(double dt)
{
	SceneBase::Update(dt);

	if (Application::IsKeyPressed('9'))
	{
		m_speed = Math::Max(0.f, m_speed - 0.1f);
	}
	if (Application::IsKeyPressed('0'))
	{
		m_speed += 0.1f;
	}

	//Mouse Section
	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
		std::cout << "LBUTTON DOWN" << std::endl;

		double x, y;
		Application::GetCursorPos(&x, &y);
		int w = Application::GetWindowWidth();
		int h = Application::GetWindowHeight();
		float posX = static_cast<float>(x) / w * m_worldWidth;
		float posY = (h - static_cast<float>(y)) / h * m_worldHeight;

		m_ghost->pos.Set(posX, posY, 0); //IMPT
		m_ghost->active = true;
		float sc = posX;
		m_ghost->scale.Set(sc, sc, sc);
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
		std::cout << "LBUTTON UP" << std::endl;

		//spawn small GO_BALL
		GameObject *go = FetchGO();
		go->active = true;
		go->type = GameObject::GO_BALL;
		double x, y;
		Application::GetCursorPos(&x, &y);
		int w = Application::GetWindowWidth();
		int h = Application::GetWindowHeight();
		float posX = static_cast<float>(x) / w * m_worldWidth;
		float posY = (h - static_cast<float>(y)) / h * m_worldHeight;

		go->pos = m_ghost->pos;
		go->vel.Set(m_ghost->pos.x - posX, m_ghost->pos.y - posY, 0);
		m_ghost->active = false;
		float sc = 2;
		go->scale.Set(sc, sc, sc);
		go->mass = sc * sc * sc;
	}
	static bool bRButtonState = false;
	if (!bRButtonState && Application::IsMousePressed(1))
	{
		bRButtonState = true;
		std::cout << "RBUTTON DOWN" << std::endl;

		double x, y;
		Application::GetCursorPos(&x, &y);
		int w = Application::GetWindowWidth();
		int h = Application::GetWindowHeight();
		float posX = static_cast<float>(x) / w * m_worldWidth;
		float posY = (h - static_cast<float>(y)) / h * m_worldHeight;

		m_ghost->pos.Set(posX, posY, 0); //IMPT
		m_ghost->active = true;
		float sc = 3;
		m_ghost->scale.Set(sc, sc, sc);
	}
	else if (bRButtonState && !Application::IsMousePressed(1))
	{
		bRButtonState = false;
		std::cout << "RBUTTON UP" << std::endl;

		//spawn large GO_BALL
		GameObject *go = FetchGO();
		go->active = true;
		go->type = GameObject::GO_BALL;
		double x, y;
		Application::GetCursorPos(&x, &y);
		int w = Application::GetWindowWidth();
		int h = Application::GetWindowHeight();
		float posX = static_cast<float>(x) / w * m_worldWidth;
		float posY = (h - static_cast<float>(y)) / h * m_worldHeight;

		go->pos = m_ghost->pos;
		go->vel.Set(m_ghost->pos.x - posX, m_ghost->pos.y - posY, 0);
		m_ghost->active = false;
		float sc = 3;
		go->scale.Set(sc, sc, sc);
		go->mass = sc * sc * sc;
	}

	//Physics Simulation Section
	dt *= m_speed;

	GOUpdate(dt);
}


void SceneCollision::RenderGO(GameObject *go)
{
	switch (go->type)
	{
	case GameObject::GO_BALL:
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_BALL], false);
		modelStack.PopMatrix();
		break;
	}
}

void SceneCollision::Render()
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

	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go->active)
		{
			RenderGO(go);
		}
	}
	if (m_ghost->active)
		RenderGO(m_ghost);

	//On screen text
	std::ostringstream ss;
	ss << "Object count: " << m_objectCount;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 9);

	ss.str(std::string());
	ss.precision(5);
	ss << "Initial energy: " << initialKE;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 15);

	ss.str(std::string());
	ss.precision(5);
	ss << "Final   energy: " << finalKE;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 12);

	//Exercise 3: render initial and final kinetic energy

	ss.str(std::string());
	ss.precision(3);
	ss << "Speed: " << m_speed;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 6);

	ss.str(std::string());
	ss.precision(5);
	ss << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 3);

	RenderTextOnScreen(meshList[GEO_TEXT], "Collision", Color(0, 1, 0), 3, 0, 0);
}

void SceneCollision::Exit()
{
	SceneBase::Exit();
	//Cleanup GameObjects
	while (m_goList.size() > 0)
	{
		GameObject *go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}
	if (m_ghost)
	{
		delete m_ghost;
		m_ghost = NULL;
	}
}
