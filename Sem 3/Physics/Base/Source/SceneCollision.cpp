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

	powerBar_y = 0;
	moveGameMenu = 0;
	showGameMenu = true;
	movingBall = false;
	player1Score = 0;
	player2Score = 0;
	turn = 1;
	highestValue = 0;
	lowestValue = 0;

	highX = highY = lowX = lowY = 0;
	offSet_highX = 0, offSet_highY = 0, offSet_lowX = 0, offSet_lowY = 0;

	int i = Math::RandIntMinMax(0, 1);
	if (i == 0)
	{
		player1Turn = true;
		player2Turn = false;
	}
	else
	{
		player1Turn = false;
		player2Turn = true;
	}


	ball = FetchGO();
	ball->pos.Set(m_worldWidth * 0.5f, m_worldHeight * 0.5f, 0);
	ball->scale.Set(2, 2, 2);
	ball->mass = 2 * 2 * 2;
	ball->angle = 0;
	ball->offset = 0;

	std::cout << GameObject::GO_BALL16 << std::endl;
	ifstream ballPos("Text/ballPos.txt");
	if (ballPos.is_open())
	{
		while (!ballPos.eof())
		{
			static int testing = GameObject::GO_BALL;
			static int count = 1;
			string posX, posY;
			getline(ballPos, posX, ',');
			getline(ballPos, posY);
			posY.erase(0, 1);

			GameObject* go = FetchGO();
			//go->type = static_cast<GameObject::GAMEOBJECT_TYPE>(testing);
			go->type = GameObject::GO_BALL2;
			go->pos.Set(stoi(posX), stoi(posY), 0);
			go->scale.Set(2, 2, 2);
			go->mass = 2 * 2 * 2;
			go->offset = count;
			testing += 1;
			//count += 1;
		}
		ballPos.close();
	}

	ifstream wallPos("Text/wallPos.txt");
	if (wallPos.is_open())
	{
		while (!wallPos.eof())
		{
			string posX, posY, normalX, normalY, normalZ, scaleX, scaleY, scaleZ;
			getline(wallPos, posX, ',');
			getline(wallPos, posY, ',');
			getline(wallPos, normalX, ',');
			getline(wallPos, normalY, ',');
			getline(wallPos, normalZ, ',');
			getline(wallPos, scaleX, ',');
			getline(wallPos, scaleY, ',');
			getline(wallPos, scaleZ);

			GameObject* go = FetchGO();
			go->type = GameObject::GO_WALL;
			go->pos.Set(stoi(posX), stoi(posY), 0);
			go->normal.Set(stoi(normalX), stoi(normalY), stoi(normalZ));
			go->normal.Normalize();
			go->scale.Set(stoi(scaleX), stoi(scaleY), stoi(scaleZ));
			go->angle = Math::RadianToDegree(atan2(go->normal.y, go->normal.x));
		}
	}
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
	if (go2->type >= GameObject::GO_BALL && go2->type <= GameObject::GO_BALL15)
	{
		//Exercise 1: move collision code to CheckCollision()
		float distSquared = (go1->pos - go2->pos).LengthSquared();
		float combinedRadius = go1->scale.x + go2->scale.x;
		Vector3 c = go1->vel - go2->vel;
		Vector3 d = go2->pos - go1->pos;

		//Practical 4, Exercise 13: improve collision detection algorithm
		if (distSquared <= combinedRadius * combinedRadius && c.Dot(d) > 0)
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
	if (go2->type >= GameObject::GO_BALL && go2->type <= GameObject::GO_BALL15)
	{
		m1 = go1->mass;
		m2 = go2->mass;
		u1 = go1->vel;
		u2 = go2->vel;

		initialMomentum = m1 * u1 + m2 * u2;

		Vector3 N = (go2->pos - go1->pos).Normalized();
		Vector3 u1N = u1.Dot(N) * N;
		Vector3 u2N = u2.Dot(N) * N;

		go1->vel = u1 + 2 * m2 / (m1 + m2) * (u2N - u1N);
		go2->vel = u2 + 2 * m1 / (m1 + m2) * (u1N - u2N);

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
			if (go->type >= GameObject::GO_BALL && go->type <= GameObject::GO_BALL16)
			{
				go->pos += go->vel * static_cast<float>(dt);

				initialKE = 0.5f * m1 * u1.Dot(u1) + 0.5f * m2 * u2.Dot(u2);
				finalKE = 0.5f * m1 * v1.Dot(v1) + 0.5f * m2 * v2.Dot(v2);

				go->vel -= go->vel * 0.6 * dt;

				if (go->vel.x < 1 && go->vel.x > -1)
				{
					if (go->vel.y < 1 && go->vel.y > -1)
					{
						go->vel.SetZero();
					}
				}

				if (go->vel.x > highX)
				{
					offSet_highX = go->offset;
					highX = go->vel.x;
				}
				else if (go->vel.x < lowX)
				{
					offSet_lowX = go->offset;
					lowX = go->vel.x;
				}

				if (go->vel.y > highY)
				{
					offSet_highY = go->offset;
					highY = go->vel.y;
				}
				else if (go->vel.y < lowY)
				{
					offSet_lowY = go->offset;
					lowY = go->vel.y;
				}

				if (offSet_highX == go->offset)
				{
					if (go->vel.IsZero())
						highX = 0;
				}

				if (offSet_highY == go->offset)
				{
					if (go->vel.IsZero())
						highY = 0;
				}

				if (offSet_lowX == go->offset)
				{
					if (go->vel.IsZero())
						lowX = 0;
				}

				if (offSet_lowY == go->offset)
				{
					if (go->vel.IsZero())
						lowY = 0;
				}


				if (go->pos.x > m_worldWidth || go->pos.x < 0 || go->pos.y > m_worldHeight || go->pos.y < 0)
				{
					go->active = false;
					this->m_objectCount--;

					if (go->type != GameObject::GO_BALL)
					{
						player1Score++;
					}
				}
			}


			for (std::vector<GameObject *>::iterator it2 = it + 1; it2 != m_goList.end(); ++it2)
			{
				GameObject *go2 = static_cast<GameObject *>(*it2);
				if (go2->active)
				{
					GameObject *goA = go;
					GameObject *goB = go2;
					if (go->type != GameObject::GO_BALL && go->type != GameObject::GO_BALL2)
					{
						if (go2->type != GameObject::GO_BALL && go2->type != GameObject::GO_BALL2)
							continue;
						goA = go2;
						goB = go;
					}

					//Practical 4, Exercise 13: improve collision detection algorithm
					if (CheckCollision(goA, goB, dt))
					{
						CollisionResponse(goA, goB);
					}

					float collisionTime = CheckCollision2(goA, goB);
					if (collisionTime > 0)
					{
						if (m_estimatedTime < 0)
							m_estimatedTime = collisionTime;
					}
				}
			}
		}
	}
	m_estimatedTime -= dt;
}

void SceneCollision::PlayerControl(double dt)
{
	//Set ball to previous pos if it becomes inactive
	if (ball->active == false)
	{
		ball->pos = ball->tempPos;
		ball->active = true;
		ball->vel.SetZero();
	}

	//Player Control
	//Check whether all the balls have stopped moving
	if (highX == 0 && highY == 0 && lowX == 0 && lowY == 0)
	{
		if (movingBall == false)
		{
			//Set ball to previous position
			ball->tempPos = ball->pos;

			if (Application::IsKeyPressed(' '))
			{
				movingBall = true;
				ball->vel.x = cos(Math::DegreeToRadian(ball->angle)) * powerBar_y * 250 * (float)dt;
				ball->vel.y = sin(Math::DegreeToRadian(ball->angle)) * powerBar_y * 250 * (float)dt;
			}

			if (Application::IsKeyPressed('A'))
				ball->angle += 100 * dt;
			if (Application::IsKeyPressed('D'))
				ball->angle -= 100 * dt;
		}
		else
		{
			turn++;
			movingBall = false;
		}
	}

	if (ball->angle < 0)
		ball->angle = 360;
	else if (ball->angle > 360)
		ball->angle = 0;
}

void SceneCollision::GameMenuUpdate(double dt)
{
	//game Menu
	static bool moveUp = true;
	if (moveUp)
	{
		powerBar_y += 35 * dt;
		if (powerBar_y > 25)
			moveUp = false;
	}
	else
	{
		powerBar_y -= 35 * dt;
		if (powerBar_y < 0)
			moveUp = true;
	}

	static bool lockMenu = false;

	if (Application::IsKeyPressed('9'))
		showGameMenu = true;
	if (Application::IsKeyPressed('8'))
		showGameMenu = false;

	if (movingBall == true)
	{
		lockMenu = true;
		showGameMenu = false;
		moveGameMenu = -35;
	}
	else
	{
		if (lockMenu == true && showGameMenu == false)
		{
			if(highestValue.IsZero() == true)
			{
				lockMenu = false;
				showGameMenu = true;
			}
		}
	}

	if (showGameMenu == false && moveGameMenu > -35)
	{
		moveGameMenu -= 50 * dt;
		if (moveGameMenu < -35)
		{
			moveGameMenu = -35;
		}
	}
	else if (showGameMenu == true && moveGameMenu < 0)
	{
		moveGameMenu += 50 * dt;
		if (moveGameMenu > 0)
		{
			moveGameMenu = 0;
		}
	}
}

void SceneCollision::Update(double dt)
{
	SceneBase::Update(dt);

	/*if (Application::IsKeyPressed('9'))
	{
		m_speed = Math::Max(0.f, m_speed - 0.1f);
	}
	if (Application::IsKeyPressed('0'))
	{
		m_speed += 0.1f;
	}*/


	//Physics Simulation Section
	dt *= m_speed;


	if (player1Score >= 15)
		std::cout << "Finish" << std::endl;
	GOUpdate(dt);
	PlayerControl(dt);
	GameMenuUpdate(dt);
}


void SceneCollision::RenderGO(GameObject *go)
{
	/*switch (go->type)
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
	}*/
	if (go->type == GameObject::GO_WALL)
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Rotate(go->angle, 0, 0, 1);
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
	}
	else if (go->type == GameObject::GO_BALL2)
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_BALL2], false);
		modelStack.PopMatrix();
	}
}

void SceneCollision::RenderPowerBar()
{
	modelStack.PushMatrix();
	modelStack.Translate(55, -33, 10);

	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidth * 0.5f - 1.9, m_worldHeight * 0.5f - 12.5 + powerBar_y, 0);
	RenderMesh(meshList[GEO_POWERBAR_LINE], false);
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidth * 0.5f, m_worldHeight * 0.5f, 0);
	modelStack.Scale(30, 30, 30);
	RenderMesh(meshList[Power_Bar], false);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
}

void SceneCollision::RenderBlackScreen()
{
	modelStack.PushMatrix();
	modelStack.Translate(m_worldWidth * 0.5, m_worldHeight * 0.5 - 33, 9);
	modelStack.Scale(140, 35, 10);
	RenderMesh(meshList[black_background], false);
	modelStack.PopMatrix();
}

void SceneCollision::RenderText()
{
	//On screen text
	std::ostringstream ss;
	ss << "Player 1 Score: " << player1Score;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 18);

	ss.str(std::string());
	ss.precision(5);
	ss << "Player 2 Score: " << m_estimatedTime;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 15);

	ss.str(std::string());
	ss.precision(5);
	ss << "Turns: " << turn;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 12);

	ss.str(std::string());
	ss.precision(3);
	ss << "Speed: " << m_speed;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 9);

	//Exercise 3: render initial and final kinetic energy
	ss.str(std::string());
	ss.precision(5);
	ss << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 6);
}

void SceneCollision::RenderPlayerTurn()
{
	if (player1Turn == true && player2Turn == false)
	{
		modelStack.PushMatrix();
		modelStack.Translate(m_worldWidth * 0.5 + 20, m_worldHeight * 0.5 - 33, 10);
		modelStack.Scale(25, 25, 25);
		RenderMesh(meshList[GEO_PLAYER1_TURN], false);
		modelStack.PopMatrix();
	}
	else if (player1Turn == false && player2Turn == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(m_worldWidth * 0.5 + 20, m_worldHeight * 0.5 - 33, 10);
		modelStack.Scale(25, 25, 25);
		RenderMesh(meshList[GEO_PLAYER2_TURN], false);
		modelStack.PopMatrix();
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

	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go->active)
		{
			RenderGO(go);
		}
	}

	if (movingBall == false && highX == 0 && highY == 0 && lowX == 0 && lowY == 0)
	{
		modelStack.PushMatrix();
		modelStack.Translate(ball->pos.x, ball->pos.y, 0);
		modelStack.Rotate(ball->angle, 0, 0, 1);
		RenderMesh(meshList[GEO_LINE], false);
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	modelStack.Translate(0, moveGameMenu, 0);

	//RenderBlackScreen();
	RenderPowerBar();

	modelStack.PopMatrix();

	RenderText();
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
