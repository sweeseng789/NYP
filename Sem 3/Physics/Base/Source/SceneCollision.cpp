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

	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();

	m_objectCount = 0;

	m_ghost = new GameObject(GameObject::GO_BALL);


	GameObject* go = FetchGO();
	//go->active = true;
	go->type = GameObject::GO_WALL;
	go->pos.Set(35, m_worldHeight * 0.5f, 0);
	go->normal.Set(1, 0, 0);
	go->normal.Normalize();
	go->scale.Set(5, 80, 1);
	go->angle = Math::RadianToDegree(atan2(go->normal.y, go->normal.x));

	GameObject* go2 = FetchGO();
	//go->active = true;
	go2->type = GameObject::GO_WALL;
	go2->pos.Set(m_worldWidth - 35, m_worldHeight * 0.5f, 0);
	go2->normal.Set(-1, 0, 0);
	go2->normal.Normalize();
	go2->scale.Set(5, 80, 1);
	go2->angle = Math::RadianToDegree(atan2(go2->normal.y, go2->normal.x));

	GameObject* go3 = FetchGO();
	//go->active = true;
	go3->type = GameObject::GO_WALL2;
	go3->pos.Set(35, m_worldHeight - 5, 0);
	go3->normal.Set(1, 0, 0);
	go3->normal.Normalize();
	go3->scale.Set(5, 10, 1);
	go3->angle = Math::RadianToDegree(atan2(go3->normal.y, go3->normal.x));

	GameObject* go5 = FetchGO();
	//go->active = true;
	go5->type = GameObject::GO_WALL2;
	go5->pos.Set(38.5, m_worldHeight - 1, 0);
	go5->normal.Set(0, 1, 0);
	go5->normal.Normalize();
	go5->scale.Set(3, 5, 1);
	go5->angle = Math::RadianToDegree(atan2(go5->normal.y, go5->normal.x));

	GameObject* go6 = FetchGO();
	//go->active = true;
	go6->type = GameObject::GO_WALL;
	go6->pos.Set(m_worldWidth * 0.5f, m_worldHeight - 1, 0);
	go6->normal.Set(0, 1, 0);
	go6->normal.Normalize();
	go6->scale.Set(3, 52, 1);
	go6->angle = Math::RadianToDegree(atan2(go6->normal.y, go6->normal.x));

	GameObject* go4 = FetchGO();
	//go->active = true;
	go4->type = GameObject::GO_WALL;
	go4->pos.Set(m_worldWidth * 0.5f, 1, 0);
	go4->normal.Set(0, 1, 0);
	go4->normal.Normalize();
	go4->scale.Set(3, 52, 1);
	go4->angle = Math::RadianToDegree(atan2(go4->normal.y, go4->normal.x));

	GameObject* go7 = FetchGO();
	//go->active = true;
	go7->type = GameObject::GO_WALL2;
	go7->pos.Set(m_worldWidth -38.5, m_worldHeight - 1, 0);
	go7->normal.Set(0, 1, 0);
	go7->normal.Normalize();
	go7->scale.Set(3, 5, 1);
	go7->angle = Math::RadianToDegree(atan2(go7->normal.y, go7->normal.x));

	GameObject* go8 = FetchGO();
	//go->active = true;
	go8->type = GameObject::GO_WALL2;
	go8->pos.Set(m_worldWidth - 35, m_worldHeight - 5, 0);
	go8->normal.Set(1, 0, 0);
	go8->normal.Normalize();
	go8->scale.Set(5, 10, 1);
	go8->angle = Math::RadianToDegree(atan2(go8->normal.y, go8->normal.x));

	GameObject* go9 = FetchGO();
	//go->active = true;
	go9->type = GameObject::GO_WALL2;
	go9->pos.Set(m_worldWidth - 35, 5, 0);
	go9->normal.Set(1, 0, 0);
	go9->normal.Normalize();
	go9->scale.Set(5, 10, 1);
	go9->angle = Math::RadianToDegree(atan2(go9->normal.y, go9->normal.x));

	GameObject* go10 = FetchGO();
	//go->active = true;
	go10->type = GameObject::GO_WALL2;
	go10->pos.Set( 35, 5, 0);
	go10->normal.Set(1, 0, 0);
	go10->normal.Normalize();
	go10->scale.Set(5, 10, 1);
	go10->angle = Math::RadianToDegree(atan2(go10->normal.y, go10->normal.x));

	GameObject* go12 = FetchGO();
	//go->active = true;
	go12->type = GameObject::GO_WALL2;
	go12->pos.Set(m_worldWidth - 38.5, 1, 0);
	go12->normal.Set(0, 1, 0);
	go12->normal.Normalize();
	go12->scale.Set(3, 5, 1);
	go12->angle = Math::RadianToDegree(atan2(go12->normal.y, go12->normal.x));

	GameObject* go11 = FetchGO();
	//go->active = true;
	go11->type = GameObject::GO_WALL2;
	go11->pos.Set(38.5, 1, 0);
	go11->normal.Set(0, 1, 0);
	go11->normal.Normalize();
	go11->scale.Set(3, 5, 1);
	go11->angle = Math::RadianToDegree(atan2(go11->normal.y, go11->normal.x));
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

float SceneCollision::CheckCollision2(GameObject* go, GameObject* go2)
{
	if(go2->type == GameObject::GO_BALL)
	{
		Vector3 p1 = go->pos;
		Vector3 p2 = go2->pos;
		Vector3 v1 = go->vel;
		Vector3 v2 = go2->vel;
		Vector3 D = p1 - p2;
		Vector3 C = v1 - v2;

		if (C.Dot(-D) < 0)
			return -1;

		float r = go->scale.x + go2->scale.x;
		float a = C.Dot(C);
		float b = 2 * C.Dot(D);
		float c = D.Dot(D) - r * r;
		float discriminant = b * b - 4 * a * c;
		if (discriminant < 0)
			return -1;

		float t = (-b - sqrt(discriminant)) / (2 * a);
		if (t < 0)
			t = (-b + sqrt(discriminant)) / (2 * a);
		return t;
	}

	return -1;
}

bool SceneCollision::CheckCollision(GameObject *go1, GameObject *go2, float dt)
{
	if (go2->type == GameObject::GO_BALL)
	{
		//Exercise 1: move collision code to CheckCollision()
		float distSquared = (go1->pos - go2->pos).LengthSquared();
		float combinedRadius = go1->scale.x + go2->scale.x;
		Vector3 c = go1->vel - go2->vel;
		Vector3 d = go2->pos - go1->pos;

		//Practical 4, Exercise 13: improve collision detection algorithm
		if (distSquared <= combinedRadius * combinedRadius &&c.Dot(d) > 0)
			return true;
		return false;
	}
	if (go2->type == GameObject::GO_WALL || go2->type == GameObject::GO_WALL2)
	{
		//|(w0 - b1).N| < r + h / 2
		Vector3 w0 = go2->pos;
		Vector3 b1 = go1->pos + go1->vel * dt;
		Vector3 N = go2->normal;
		float r = go1->scale.x;
		float h = go2->scale.x;


		//|(w0 - b1).NP| < r + l / 2
		Vector3 NP(-N.y, N.x);
		float l = go2->scale.y;


		if (abs((w0 - b1).Dot(N)) < r + h * 0.5 && abs((w0 - b1).Dot(NP)) < r + l * 0.5)
			return true;
		return false;
	}
}

void SceneCollision::CollisionResponse(GameObject *go1, GameObject *go2)
{
	if (go2->type == GameObject::GO_BALL)
	{
		m1 = go1->mass;
		m2 = go2->mass;
		u1 = go1->vel;
		u2 = go2->vel;

		initialMomentum = m1 * u1 + m2 * u2;

		Vector3 N = (go2->pos - go1->pos).Normalized();
		Vector3 u1N = u1.Dot(N) * N;
		Vector3 u2N = u2.Dot(N) * N;

		go1->vel = (2 * m2 * u2 + u1 * (m1 - m2)) * (1 / (m1 + m2));
		go2->vel = (2 * m1 * u1 + u2 * (m2 - m1)) * (1 / (m1 + m2));

		finalMomentum = m1 * v1 + m2 * v2;
		initialKE = 0.5f * m1 * u1.Dot(u1) + 0.5f * m2 * u2.Dot(u2);
		finalKE = 0.5f * m1 * v1.Dot(v1) + 0.5f * m2 * v2.Dot(v2);
	}
	else if (go2->type == GameObject::GO_WALL || go2->type == GameObject::GO_WALL2)
	{
		Vector3 w0 = go2->pos;
		Vector3 b1 = go1->pos;
		Vector3 N = go2->normal;
		float r = go1->scale.x;
		float h = go2->scale.x;


		//|(w0 - b1).NP| < r + l / 2
		Vector3 NP(-N.y, N.x);
		float l = go2->scale.y;

		//Long wall
		if (abs((w0 - b1).Dot(N)) < r + h * 0.5)
		{
			//v = u - (2 * u.N)N
			Vector3 u = go1->vel;
			Vector3 N = go2->normal;

			Vector3 v = u - (2 * u.Dot(N)) * N;
			go1->vel = v;
		}
		if (abs((w0 - b1).Dot(NP)) < r + l * 0.5)
		{
			Vector3 u = go1->vel;
			Vector3 v = u - 2 * u.Dot(NP) * NP;
			go1->vel = v;
		}
	}
}

void SceneCollision::GOUpdate(const double dt)
{
	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go->active)
		{ 
			if (go->type == GameObject::GO_BALL)
			{
				go->pos += go->vel * static_cast<float>(dt);
				/*go->vel.x = (go->vel.x / 100) * 99.2;
				go->vel.y = (go->vel.y / 100) * 99.2;*/

				initialKE = 0.5f * m1 * u1.Dot(u1) + 0.5f * m2 * u2.Dot(u2);
				finalKE = 0.5f * m1 * v1.Dot(v1) + 0.5f * m2 * v2.Dot(v2);

				if (go->pos.x > m_worldWidth - go->scale.x && go->vel.x > 0)
				{
					go->vel.x = -go->vel.x;
				}
				else if (go->pos.x < 0 + go->scale.x && go->vel.x < 0)
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

				/*if (go->pos.x > m_worldWidth + 5 || go->pos.x < -5 || go->pos.y > m_worldHeight + 5 || go->pos.y < -5)
				{
					go->active = false;
					this->m_objectCount--;
				}*/
			}


			for (std::vector<GameObject *>::iterator it2 = it + 1; it2 != m_goList.end(); ++it2)
			{
				GameObject *go2 = static_cast<GameObject *>(*it2);
				if (go2->active)
				{
					GameObject *goA = go;
					GameObject *goB = go2;
					if (go->type != GameObject::GO_BALL)
					{
						if (go2->type != GameObject::GO_BALL)
							continue;
						goA = go2;
						goB = go;
					}
					//Practical 4, Exercise 13: improve collision detection algorithm
					if (CheckCollision(goA, goB, dt))
					{
						CollisionResponse(goA, goB);
					}
				}
			}
		}
	}
	m_estimatedTime -= dt;
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

	if (Application::IsKeyPressed('C'))
	{
		for (std::vector<GameObject*>::iterator it = m_goList.begin(); it != m_goList.end(); it++)
		{
			GameObject * go = (GameObject*)*it;
			if (go->active && go->type == GameObject::GO_BALL)
			{
				go->active = false;
			}
		}
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
		float sc = 2;
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

	if (Application::IsKeyPressed('R'))
	{
		
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
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			RenderMesh(meshList[GEO_BALL], false);
			modelStack.PopMatrix();
		}
		break;

	case GameObject::GO_WALL:
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Rotate(go->angle, 0, 0, 1);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			RenderMesh(meshList[GEO_CUBE], false);
			modelStack.PopMatrix();
		}
		break;
	case GameObject::GO_WALL2:
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
			modelStack.Rotate(go->angle, 0, 0, 1);
			modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
			RenderMesh(meshList[GEO_CUBE2], false);
			modelStack.PopMatrix();
		}
		break;
	}
	/*if (go->type == GameObject::GO_WALL)
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_CUBE], false);
		modelStack.PopMatrix();
	}
	else if (go->type == GameObject::GO_BALL)
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_BALL], false);
		modelStack.PopMatrix();
	}*/
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
	ss << "Collison In: " << m_estimatedTime;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 18);

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
