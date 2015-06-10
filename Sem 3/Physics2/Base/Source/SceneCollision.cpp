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

	//Exercise 1: initialize m_objectCount
	m_objectCount = 0;

	m_ghost = new GameObject(GameObject::GO_BALL);
}

GameObject* SceneCollision::FetchGO()
{
	//Exercise 2a: implement FetchGO()
	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject * go = (GameObject*)*it;
		if (!go->active)
		{
			go->active = true;
			return go;
		}
	}

	//Exercise 2b: increase object count every time an object is set to active
	for (unsigned i = 0; i < 10; ++i)
	{
		GameObject *go = new GameObject(GameObject::GO_BALL);
		m_goList.push_back(go);
	}

	GameObject *go = m_goList.back();
	go->active = true;

	return go;
}

void SceneCollision::Update(double dt)
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

		//Exercise 6: spawn small GO_BALL
		GameObject * go = FetchGO();
		go->type = GameObject::GO_BALL;
		double x, y;
		Application::GetCursorPos(&x, &y);
		int w = Application::GetWindowWidth();
		int h = Application::GetWindowHeight();
		float posX = x / w * m_worldWidth;
		float posY = (h - y) / h * m_worldHeight;
		//Exercise 10: spawn ghost ball
		m_ghost->pos.Set(posX, posY, 0);
		m_ghost->active = true;

		go->pos = m_ghost->pos;
		go->vel = m_ghost->pos - Vector3(posX, posY);//Important
		m_ghost->active = false;
		float sc = 2;
		go->scale.Set(sc, sc, sc);
		go->mass = sc * sc * sc;
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

		//Exercise 10: spawn large GO_BALL
	}

	//Physics Simulation Section
	dt * m_speed;

	for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if(go->active)
		{
			go->pos == go->vel * dt;
			//Exercise 7: handle out of bound game objects
			if (go->pos.x > m_worldWidth || go->pos.x < 0 || go->pos.y > m_worldHeight || go->pos.y < 0)
			{
				go->active = false;
				m_objectCount--;
			}

			for (std::vector<GameObject *>::iterator it2 = it + 1; it2 != m_goList.end(); ++it2)
			{
				GameObject* go2 = (GameObject *) *it2;

				if (go != go2 && go2->active)
				{
					float distSqaured = (go->pos - go2->pos).LengthSquared();
					float combinedRadius = go->scale.x + go2->scale.x;

					if (distSqaured <= combinedRadius * combinedRadius)
					{
						m1 = go->mass;
						m2 = go2->mass;
						u1 = go->vel;
						u2 = go2->vel;

						Vector3 momentum1 = go->mass * go->vel;
						Vector3 momentum2 = go2->mass * go2->vel;

						go->vel = momentum2 * (1.f / go->mass);
						go2->vel = momentum1 * (1.f / go2->mass);

						Vector3 temp = go->vel;
						go->vel = go2->vel;
						go2->vel = temp;

						v1 = go->vel;
					}
				}
			}

			//Exercise 8a: handle collision between GO_BALL and GO_BALL using velocity swap

			//Exercise 8b: store values in auditing variables

			//Exercise 10: handle collision using momentum swap instead

			//Exercise 12: improve inner loop to prevent double collision

			//Exercise 13: improve collision detection algorithm [solution to be given later] 
		}
	}
}


void SceneCollision::RenderGO(GameObject *go)
{
	switch(go->type)
	{
	case GameObject::GO_BALL:
		//Exercise 4: render a sphere using scale and pos
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_BALL], false);
		modelStack.PopMatrix();
		//Exercise 11: think of a way to give balls different colors
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

	for(std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if(go->active)
		{
			RenderGO(go);
		}
	}

	//On screen text

	//Exercise 5: Render m_objectCount

	//Exercise 8c: Render initial and final momentum

	std::ostringstream ss2;
	ss2.precision(3);
	ss2 << "Speed: " << m_speed;
	RenderTextOnScreen(meshList[GEO_TEXT], ss2.str(), Color(0, 1, 0), 3, 0, 6);
	
	std::ostringstream ss;
	ss.precision(5);
	ss << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 3);

	Vector3 initialM = m1 * u1 + m2 * u2;
	Vector3 finalM = m1 * v1 + m2 * v2;

	/*std::ostringstream ss3;
	ss3.precision(3);
	ss3 << "Speed: " << finalmom;
	RenderTextOnScreen(meshList[GEO_TEXT], ss3.str(), Color(0, 1, 0), 3, 0, 9);

	std::ostringstream ss4;
	ss4.precision(3);
	ss4 << "Speed: " << m_speed;
	RenderTextOnScreen(meshList[GEO_TEXT], ss4.str(), Color(0, 1, 0), 3, 0, 12);*/

	
	RenderTextOnScreen(meshList[GEO_TEXT], "Collision", Color(0, 1, 0), 3, 0, 0);
}

void SceneCollision::Exit()
{
	SceneBase::Exit();
	//Cleanup GameObjects
	while(m_goList.size() > 0)
	{
		GameObject *go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}
	if(m_ghost)
	{
		delete m_ghost;
		m_ghost = NULL;
	}
}
