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

void SceneCollision::setParameters()
{
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();

	m_objectCount = 0;

	//m_ghost = new GameObject(GameObject::GO_BALL);

	powerBar_y = 0;
	moveGameMenu = 0;
	showGameMenu = true;
	movingBall = false;
	player1Score = 0;
	player2Score = 0;
	turn = 1;
	highestValue = 0;
	lowestValue = 0;
	elapsedTime = 0;
	showBlock = 0;
	calculateShowBlock = false;
	ballCount = 0;
	previousTurn = 0;

	powerUp = false;
	powerUpType = 0;
	powerUpSpawned = false;
	AntManPowerUp = false;
	powerUpTurns = 0;
	FrictionPowerUp = false;
	frictionSpeed = 0.6;
	godMode = false;

	pause = false; 
	finishGame = false;
	rotateSpeed = 100;

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
	ball->type = GameObject::GO_BALL;
	ball->pos.Set(m_worldWidth * 0.5f - 50, m_worldHeight * 0.5f, 0);
	ball->scale.Set(2, 2, 2);
	ball->mass = 2 * 2 * 2;
	ball->angle = 0;
	ball->offset = 0;

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
			ballCount ++;
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
		wallPos.close();
	}

	ifstream highScore_Text("Text/BestRecords.txt");
	if (highScore_Text.is_open())
	{
		while (!highScore_Text.eof())
		{
			string hsm;
			string time;
			getline(highScore_Text, hsm, ',');
			getline(highScore_Text, time);
			highScore = stoi(hsm);
			fastestTiming = stoi(time);
		}
		highScore_Text.close();
	}

	GameObject* go = FetchGO();
	go->type = GameObject::GO_BALL3;
	go->pos.Set(m_worldWidth * 0.5f, m_worldHeight + 1.5, 0);
	go->scale.Set(7, 7, 7);
	go->vel.SetZero();

	GameObject* go2 = FetchGO();
	go2->type = GameObject::GO_BALL3;
	go2->pos.Set(m_worldWidth - 2, m_worldHeight - 4, 0);
	go2->scale.Set(9, 9, 9);
	go2->vel.SetZero();

	GameObject* go3 = FetchGO();
	go3->type = GameObject::GO_BALL3;
	go3->pos.Set(m_worldWidth - 2, 4, 0);
	go3->scale.Set(9, 9, 9);
	go3->vel.SetZero();

	GameObject* go4 = FetchGO();
	go4->type = GameObject::GO_BALL3;
	go4->pos.Set(m_worldWidth * 0.5f, -1.5, 0);
	go4->scale.Set(7, 7, 7);
	go4->vel.SetZero();

	GameObject* go5 = FetchGO();
	go5->type = GameObject::GO_BALL3;
	go5->pos.Set(2, 4, 0);
	go5->scale.Set(9, 9, 9);
	go5->vel.SetZero();

	GameObject* go6 = FetchGO();
	go6->type = GameObject::GO_BALL3;
	go6->pos.Set(2, m_worldHeight - 4, 0);
	go6->scale.Set(9, 9, 9);
	go6->vel.SetZero();
}

void SceneCollision::Init()
{
	SceneBase::Init();

	setParameters();
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
	if (go2->type == GameObject::GO_BALL)
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
	if (go2->type >= GameObject::GO_BALL && go2->type <= GameObject::GO_BALL5)
	{
		//Exercise 1: move collision code to CheckCollision()
		float distSquared = (go1->pos - go2->pos).LengthSquared();
		float combinedRadius = go1->scale.x + go2->scale.x;
		Vector3 c = go1->vel - go2->vel;
		Vector3 d = go2->pos - go1->pos;

		//Practical 4, Exercise 13: improve collision detection algorithm
		if (distSquared <= combinedRadius * combinedRadius && c.Dot(d) > 0)
		{
			Sound::playCollidingSound();
			return true;
		}
		return false;
	}
	if (go2->type == GameObject::GO_WALL || go2->type == GameObject::GO_WALL3)
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
		{
			//Sound::playCollidingSound_Wall();
			//Sound::playCollidingSound();
			return true;
		}
		else
			return false;
	}
}

void SceneCollision::CollisionResponse(GameObject *go1, GameObject *go2, float dt)
{
	if (go2->type == GameObject::GO_BALL || go2->type == GameObject::GO_BALL2)
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

		if(go2->type == GameObject::GO_BALL2 && this->FrictionPowerUp == true)
		{
			go2->vel.x = (go2->vel.x / 100) * 180;
			go2->vel.y = (go2->vel.y / 100) * 180;
			go2->vel.z = (go2->vel.z / 100) * 180;
		}

		finalMomentum = m1 * v1 + m2 * v2;
		initialKE = 0.5f * m1 * u1.Dot(u1) + 0.5f * m2 * u2.Dot(u2);
		finalKE = 0.5f * m1 * v1.Dot(v1) + 0.5f * m2 * v2.Dot(v2);
	}
	else if (go2->type == GameObject::GO_WALL || go2->type == GameObject::GO_WALL3)
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
	else if(go2->type == GameObject::GO_BALL3 && go1->type == GameObject::GO_BALL)
	{
		Sound::playBooing();
		go1->active = false;
	}
	else if(go2->type == GameObject::GO_BALL3 && go1->type == GameObject::GO_BALL2)
	{
		Sound::playWinningSound();
		go1->active = false;
		player1Score ++;
	}
	else if (go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_BALL4 ||
			go1->type == GameObject::GO_BALL && go2->type == GameObject::GO_BALL5)
	{
		if (go2->type == GameObject::GO_BALL4)
		{
			go1->vel.SetZero();
			go2->active = false;
			AntManPowerUp = true;
		}
		else
		{
			go1->vel.SetZero();
			go2->active = false;
			FrictionPowerUp = true;
		}
	}
}

void SceneCollision::GOUpdate(const double dt)
{
	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go->active == true)
		{
			if (go->type >= GameObject::GO_BALL && go->type <= GameObject::GO_BALL2)
			{
				go->pos += go->vel * static_cast<float>(dt);

				initialKE = 0.5f * m1 * u1.Dot(u1) + 0.5f * m2 * u2.Dot(u2);
				finalKE = 0.5f * m1 * v1.Dot(v1) + 0.5f * m2 * v2.Dot(v2);

				go->vel -= go->vel * frictionSpeed * dt;

				if (go->vel.x < 1 && go->vel.x > -1)
				{
					if (go->vel.y < 1 && go->vel.y > -1)
					{
						go->vel.SetZero();
					}
				}

				if (Application::IsKeyPressed(' '))
					go->tempPos = go->pos;

				if (!godMode)
				{
					if (Application::IsKeyPressed('O') && turn > 1)
					{
						go->vel.SetZero();
						go->pos = go->tempPos;
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
				
				if(go->type == GameObject::GO_BALL2)
				{
					if (AntManPowerUp == true)
					{	
						go->scale.x = 1;
						go->scale.y = 1;
						go->scale.z = 1;
						go->mass = go->scale.x * go->scale.y * go->scale.z;
					}
					else
					{
						go->scale.x = 2;
						go->scale.y = 2;
						go->scale.z = 2;
						go->mass = go->scale.x * go->scale.y * go->scale.z;
					}
				}

			}
			else if (go->type == GameObject::GO_WALL3)
			{
				if (showBlock == go->offset && calculateShowBlock == true)
				{
					if (highX == 0 && highY == 0 && lowX == 0 && lowY == 0 && movingBall == true)
							go->turns++;

					if (go->turns >= 5)
					{
						go->turns = 0;
						go->active = false;
						calculateShowBlock = false;
						showBlock = 0;
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
						CollisionResponse(goA, goB, dt);
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
		godMode = true;
	}

	//Player Control
	//Check whether all the balls have stopped moving
	if (highX == 0 && highY == 0 && lowX == 0 && lowY == 0)
	{
		if (movingBall == false)
		{
			if (!godMode)
			{
				if (Application::IsKeyPressed(' ') && GetAsyncKeyState(VK_SPACE) < 0)
				{
					//Set ball to previous position
					ball->tempPos = ball->pos;

					movingBall = true;
					ball->vel.x = cos(Math::DegreeToRadian(ball->angle)) * powerBar_y * 250 * (float)dt;
					ball->vel.y = sin(Math::DegreeToRadian(ball->angle)) * powerBar_y * 250 * (float)dt;
				}

				if (Application::IsKeyPressed('A'))
					ball->angle += rotateSpeed * dt;
				if (Application::IsKeyPressed('D'))
					ball->angle -= rotateSpeed * dt;
				if (Application::IsKeyPressed('O') && turn > 1)
				{
					turn = previousTurn;
					ball->pos = ball->tempPos;
				}


				if (Application::IsKeyPressed(VK_CONTROL))
					rotateSpeed = 50;
				else
					rotateSpeed = 100;
			}
			else
			{
				if (Application::IsKeyPressed('W'))
					ball->pos.y += 50 * dt;
				if (Application::IsKeyPressed('S'))
					ball->pos.y -= 50 * dt;
				if (Application::IsKeyPressed('A'))
					ball->pos.x -= 50 * dt;
				if (Application::IsKeyPressed('D'))
					ball->pos.x += 50 * dt;

				if (Application::IsKeyPressed(VK_RETURN))
					godMode = false;
			}
		}
		else
		{
			turn++;
			previousTurn = turn - 1;
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


	static float keyPress = 0.f;
	keyPress += dt;

	if (keyPress >= 0.2)
		keyPress = 0.2;


	if (Application::IsKeyPressed('Z') && keyPress >= 0.2)
	{
		if (showGameMenu == true)
			showGameMenu = false;
		else
			showGameMenu = true;
		keyPress = 0.f;
	}

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
			if (highestValue.IsZero() == true)
			//if(highX == highY == lowX == lowY == 0)
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

void SceneCollision::reset()
{
	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (go->active == true)
		{
			go->active = false;
			go->vel.SetZero();
		}
	}

	setParameters();
	menu.reset();
}

void SceneCollision::PowerupUpdate()
{
	if (FrictionPowerUp == true)
		frictionSpeed = 0.2;
	else
		frictionSpeed = 0.6;

	if (AntManPowerUp == true || FrictionPowerUp == true)
	{
		if (highX == 0 && highY == 0 && lowX == 0 && lowY == 0)
		{
			if (movingBall == true)
				powerUpTurns++;
		}

		if (powerUpTurns >= 5)
		{
			powerUp = false;
			powerUpType = 0;
			powerUpSpawned = false;
			AntManPowerUp = false;
			powerUpTurns = 0;
			FrictionPowerUp = false;
		}
	}

	if (elapsedTime > 5)
	{
		if (fmod(elapsedTime, 50) < 0.5 && powerUp == false)
		{
			powerUp = true;
			powerUpType = Math::RandIntMinMax(1, 2);
		}
	}

	if (powerUpSpawned == false)
	{
		switch (powerUpType)
		{
		case(1) :
		{
			GameObject* go = FetchGO();
			go->type = GameObject::GO_BALL4;
			go->pos.Set(Math::RandFloatMinMax(5, m_worldWidth - 10), Math::RandFloatMinMax(5, m_worldHeight - 10), 0);
			go->scale.Set(3, 3, 3);
			go->mass = go->scale.x * go->scale.y * go->scale.z;
			powerUpSpawned = true;
			break;
		}

		case(2) :
		{
			GameObject* go = FetchGO();
			go->type = GameObject::GO_BALL5;
			go->pos.Set(Math::RandFloatMinMax(5, m_worldWidth - 10), Math::RandFloatMinMax(5, m_worldHeight - 10), 0);
			go->scale.Set(3, 3, 3);
			go->mass = go->scale.x * go->scale.y * go->scale.z;
			powerUpSpawned = true;
			break;
		}

		default:
			break;
		}
	}
}

void SceneCollision::ObstacleUpdate()
{
	if (turn % 10 == 0 && calculateShowBlock == false)
	{
		calculateShowBlock = true;
		showBlock = Math::RandIntMinMax(1, 6);
		std::cout << showBlock << std::endl;

		GameObject * go = FetchGO();
		go->type = GameObject::GO_WALL3;
		go->offset = 0;

		if (showBlock == 1)
		{
			go->pos.Set(9, m_worldHeight - 9, 0);
			go->normal.Set(-1, 1, 0);
			go->normal.Normalize();
			go->scale.Set(5, 20, 0);
			go->offset = showBlock;
			go->angle = Math::RadianToDegree(atan2(go->normal.y, go->normal.x));
		}
		else if (showBlock == 2)
		{
			go->pos.Set(m_worldWidth - 9, m_worldHeight - 9, 0);
			go->normal.Set(-1, -1, 0);
			go->normal.Normalize();
			go->scale.Set(5, 20, 0);
			go->offset = showBlock;
			go->angle = Math::RadianToDegree(atan2(go->normal.y, go->normal.x));
		}
		else if (showBlock == 3)
		{
			go->pos.Set(9, 9, 0);
			go->normal.Set(-1, -1, 0);
			go->normal.Normalize();
			go->scale.Set(5, 20, 0);
			go->offset = showBlock;
			go->angle = Math::RadianToDegree(atan2(go->normal.y, go->normal.x));
		}
		else if (showBlock == 4)
		{
			go->pos.Set(m_worldWidth - 9, 9, 0);
			go->normal.Set(-1, 1, 0);
			go->normal.Normalize();
			go->scale.Set(5, 20, 0);
			go->offset = showBlock;
			go->angle = Math::RadianToDegree(atan2(go->normal.y, go->normal.x));
		}
		else if (showBlock == 5)
		{
			go->pos.Set(m_worldWidth * 0.5, m_worldHeight - 7, 0);
			go->normal.Set(0, 1, 0);
			go->normal.Normalize();
			go->scale.Set(5, 20, 0);
			go->offset = showBlock;
			go->angle = Math::RadianToDegree(atan2(go->normal.y, go->normal.x));
		}
		else if (showBlock == 6)
		{
			go->pos.Set(m_worldWidth * 0.5, 7, 0);
			go->normal.Set(0, 1, 0);
			go->normal.Normalize();
			go->scale.Set(5, 20, 0);
			go->offset = showBlock;
			go->angle = Math::RadianToDegree(atan2(go->normal.y, go->normal.x));
		}
	}
}

void SceneCollision::Update(double dt)
{
	SceneBase::Update(dt);

	Sound::playAmbience(dt);
	menu.MenuUpdate(dt);

	static float pauseKeyPress = 0.f;
	pauseKeyPress += dt;

	if (pauseKeyPress >= 0.2)
		pauseKeyPress = 0.2;

	if (Application::IsKeyPressed('P') && pauseKeyPress >= 0.2 && finishGame == false)
	{
		if (pause == true)
			pause = false;
		else
			pause = true;
		pauseKeyPress = 0.f;
	}

	if (menu.getStartGame())
	{
		if (pause == false)
		{
			if (player1Score != ballCount)
			{
				if (finishGame == false)
				{
					PowerupUpdate();
					ObstacleUpdate();
					GOUpdate(dt);
					PlayerControl(dt);
					GameMenuUpdate(dt);
				}
			}
			else
			{
				finishGame = true;

				if (finishGame == true)
				{
					if (Application::IsKeyPressed(VK_TAB) && GetAsyncKeyState(VK_TAB) < 0)
						reset();
				}
			}
		}
		else
		{
			if (Application::IsKeyPressed(VK_TAB) && GetAsyncKeyState(VK_TAB) < 0)
				reset();
		}

		dt *= m_speed;

		if(finishGame != true)
			elapsedTime += dt;
	}
	else
	{
		if (Application::IsKeyPressed(VK_TAB))
			reset();
	}
}


void SceneCollision::RenderGO(GameObject *go)
{
	if (go->type == GameObject::GO_WALL)
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Rotate(go->angle, 0, 0, 1);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_CUBE], false);
		modelStack.PopMatrix();
	}
	else if (go->type == GameObject::GO_WALL3)
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
	else if (go->type == GameObject::GO_BALL3)
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_BALL3], false);
		modelStack.PopMatrix();
	}
	else if (go->type == GameObject::GO_BALL4)
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_BALL4], false);
		modelStack.PopMatrix();
	}
	else if (go->type == GameObject::GO_BALL5)
	{
		modelStack.PushMatrix();
		modelStack.Translate(go->pos.x, go->pos.y, go->pos.z);
		modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
		RenderMesh(meshList[GEO_BALL5], false);
		modelStack.PopMatrix();
	}
}

void SceneCollision::RenderPowerBar()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, moveGameMenu, 0);

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
	ss << "Player Score: " << player1Score;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 18 + moveGameMenu);

	ss.str(std::string());
	ss.precision(5);
	ss << "Elapsed Time: " << elapsedTime;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 15 + moveGameMenu);

	ss.str(std::string());
	ss.precision(5);
	ss << "Turns: " << turn;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 12 + moveGameMenu);

	ss.str(std::string());
	ss.precision(3);
	ss << "Speed: " << m_speed;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 9 + moveGameMenu);

	//Exercise 3: render initial and final kinetic energy
	ss.str(std::string());
	ss.precision(5);
	ss << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 6 + moveGameMenu);

	ss.str(std::string());
	ss.precision(5);
	ss << "Highscore: " << highScore;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 3 + moveGameMenu);

	ss.str(std::string());
	ss.precision(5);
	ss << "Fastest timing: " << fastestTiming;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 0 + moveGameMenu);
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


	if (!menu.getStartGame())
	{
		if(menu.getShowControl() == false)
		{
			modelStack.PushMatrix();
			modelStack.Translate(m_worldWidth * 0.5, m_worldHeight * 0.5, 9);
			modelStack.Scale(135, 161, 100);
			RenderMesh(meshList[StartMenu], false);
			modelStack.PopMatrix();

			if (menu.StartConfirm())
			{
				modelStack.PushMatrix();
				modelStack.Translate(m_worldWidth * 0.5, m_worldHeight * 0.5, 10);
				modelStack.Scale(100, 100, 100);
				RenderMesh(meshList[StartTrue], false);
				modelStack.PopMatrix();
			}
			else if (menu.ControlConfirm())
			{
				modelStack.PushMatrix();
				modelStack.Translate(m_worldWidth * 0.5, m_worldHeight * 0.5, 10);
				modelStack.Scale(100, 100, 100);
				RenderMesh(meshList[ControlTrue], false);
				modelStack.PopMatrix();
			}
			else if (menu.ExitConfirm())
			{
				modelStack.PushMatrix();
				modelStack.Translate(m_worldWidth * 0.5, m_worldHeight * 0.5, 10);
				modelStack.Scale(100, 100, 100);
				RenderMesh(meshList[ExitTrue], false);
				modelStack.PopMatrix();
			}
		}
		else
		{
			modelStack.PushMatrix();
			modelStack.Translate(m_worldWidth * 0.5, m_worldHeight * 0.5, 10);
			modelStack.Scale(135, 160 ,100);
			RenderMesh(meshList[ShowControl], false);
			modelStack.PopMatrix();
		}
	}
	else
	{
		if (finishGame == false)
		{
			modelStack.PushMatrix();
			modelStack.Translate(m_worldWidth * 0.5f, m_worldHeight * 0.5f, -2);
			modelStack.Scale(133.5, 100, 10);
			RenderMesh(meshList[Background], false);
			modelStack.PopMatrix();

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

			if (pause == true)
			{
				modelStack.PushMatrix();
				modelStack.Translate(m_worldWidth* 0.5f, m_worldHeight * 0.5f, 10);
				modelStack.Scale(135, 165, 100);
				RenderMesh(meshList[GEO_PLAYER1_TURN], false);
				modelStack.PopMatrix();
			}
			else
			{
				RenderPowerBar();
				RenderText();
			}
		}
		else
		{
			modelStack.PushMatrix();
			modelStack.Translate(m_worldWidth * 0.5, m_worldHeight * 0.5, 0);
			modelStack.Scale(135, 161, 100);
			RenderMesh(meshList[WinScreen], false);
			modelStack.PopMatrix();

			std::ostringstream ss2;
			ss2 << elapsedTime;
			RenderTextOnScreen(meshList[GEO_TEXT], ss2.str(), Color(0, 1, 0), 8, 35, 12);
		}
	}
}

void SceneCollision::Exit()
{
	SceneBase::Exit();

	if (player1Score >= ballCount && elapsedTime < fastestTiming)
	{
		ofstream highScore_Text("Text/BestRecords.txt");
		if (highScore_Text.is_open())
		{
			highScore_Text << player1Score << "," << elapsedTime;
			highScore_Text.close();
		}
	}

	//Cleanup GameObjects
	while (m_goList.size() > 0)
	{
		GameObject *go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}

}
