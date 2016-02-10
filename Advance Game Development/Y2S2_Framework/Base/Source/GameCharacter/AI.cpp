#include "AI.h"

AI::AI()
{
	this->pos.SetZero();
	this->vel.SetZero();
	this->scale.Set(10, 10, 10);
	active = true;
	type = CGameObject::ENEMY;

	m_cSceneGraph = new CSceneNode();
	CModel* newModel = new CModel();
	CTransform* transform = new CTransform();
	std::pair<int, std::string>* nodeInfo = new std::pair<int, std::string>();


	movementTime = 0.f;
	currentTime = 0.f;
	moveDir.SetZero();
	rotateAngle = 0.f;
	/*newModel->Init(MeshBuilder::GenerateOBJ("Transient Head", "OBJ//Unicorn_Head.obj"), "Image//Transient//Transient_Head.tga");
	transform->SetScale(10, 10, 10);
	nodeInfo->first = m_cSceneGraph->SetNode(transform, newModel);
	nodeInfo->second = "Head";
	nodeList.insert(*nodeInfo);*/
}

AI::AI(Vector3 pos)
{
	animation = new CharAnimation();
	this->pos = pos;
	this->vel.SetZero();
	this->scale.Set(10, 10, 10);
	active = true;
	type = CGameObject::ENEMY;
	currentState = s_PATROL;

	movementTime = 0.f;
	currentTime = 0.f;
	moveDir.SetZero();
	rotateAngle = 0.f;

	m_cSceneGraph = new CSceneNode();
	CModel* newModel = new CModel();
	CTransform* transform = new CTransform();
	std::pair<int, std::string>* nodeInfo = new std::pair<int, std::string>();

	//Head
	newModel->setMesh(CModel::s_LOW, MeshBuilder::GenerateOBJ("Transient Head", "OBJ//Transient_Head.obj"), "Image//Transient//Transient_Head.tga");
	newModel->setMesh(CModel::s_MID, MeshBuilder::GenerateOBJ("Transient Head", "OBJ//Transient_Head.obj"), "Image//Transient//Transient_Head.tga");
	newModel->setMesh(CModel::s_HIGH, MeshBuilder::GenerateOBJ("Transient Head", "OBJ//Transient_Head.obj"), "Image//Transient//Transient_Head.tga");
	transform->SetTranslate(0, 30.2, 0);
	transform->SetScale(scale.x, scale.y, scale.z);

	nodeInfo->first = m_cSceneGraph->SetNode(transform, newModel);
	nodeInfo->second = "Head";
	nodeList.insert(*nodeInfo);

	//Torso
	newModel = new CModel();
	transform = new CTransform();
	nodeInfo = new std::pair<int, std::string>();
	newModel->setMesh(CModel::s_LOW, MeshBuilder::GenerateOBJ("Unicorn Torso", "OBJ//Unicorn_Torso.obj"), "Image//Transient//Transient_Torso.tga");
	newModel->setMesh(CModel::s_MID, MeshBuilder::GenerateOBJ("Unicorn Torso", "OBJ//Unicorn_Torso.obj"), "Image//Transient//Transient_Torso.tga");
	newModel->setMesh(CModel::s_HIGH, MeshBuilder::GenerateOBJ("Unicorn Torso", "OBJ//Unicorn_Torso.obj"), "Image//Transient//Transient_Torso.tga");
	transform->SetTranslate(0, 16.5, 0);
	transform->SetScale(scale.x, scale.y, scale.z);
	nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	nodeInfo->second = "Torso";
	nodeList.insert(*nodeInfo);

	//Left Arm
	newModel = new CModel();
	transform = new CTransform();
	nodeInfo = new std::pair<int, std::string>();
	newModel->setMesh(CModel::s_LOW, MeshBuilder::GenerateOBJ("Unicorn Left Arm", "OBJ//Transient_LeftArm.obj"), "Image//Transient//Transient_Arm.tga");
	newModel->setMesh(CModel::s_MID, MeshBuilder::GenerateOBJ("Unicorn Left Arm", "OBJ//Transient_LeftArm.obj"), "Image//Transient//Transient_Arm.tga");
	newModel->setMesh(CModel::s_HIGH, MeshBuilder::GenerateOBJ("Unicorn Left Arm", "OBJ//Transient_LeftArm.obj"), "Image//Transient//Transient_Arm.tga");
	transform->SetTranslate(9.5, 16.5, 0);
	transform->SetScale(scale.x, scale.y, scale.z);
	nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	nodeInfo->second = "LeftArm";
	nodeList.insert(*nodeInfo);

	//Right Arm
	newModel = new CModel();
	transform = new CTransform();
	nodeInfo = new std::pair<int, std::string>();
	newModel->setMesh(CModel::s_LOW, MeshBuilder::GenerateOBJ("Unicorn Right Arm", "OBJ//Transient_RightArm.obj"), "Image//Transient//Transient_Arm.tga");
	newModel->setMesh(CModel::s_MID, MeshBuilder::GenerateOBJ("Unicorn Right Arm", "OBJ//Transient_RightArm.obj"), "Image//Transient//Transient_Arm.tga");
	newModel->setMesh(CModel::s_HIGH, MeshBuilder::GenerateOBJ("Unicorn Right Arm", "OBJ//Transient_RightArm.obj"), "Image//Transient//Transient_Arm.tga");
	transform->SetTranslate(-9.5, 16.5, 0);
	transform->SetScale(scale.x, scale.y, scale.z);
	nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	nodeInfo->second = "RightArm";
	nodeList.insert(*nodeInfo);

	//Left Leg
	newModel = new CModel();
	transform = new CTransform();
	nodeInfo = new std::pair<int, std::string>();
	newModel->setMesh(CModel::s_LOW, MeshBuilder::GenerateOBJ("Unicorn Left Leg", "OBJ//Transient_LeftLeg.obj"), "Image//Transient//Transient_Leg.tga");
	newModel->setMesh(CModel::s_MID, MeshBuilder::GenerateOBJ("Unicorn Left Leg", "OBJ//Transient_LeftLeg.obj"), "Image//Transient//Transient_Leg.tga");
	newModel->setMesh(CModel::s_HIGH, MeshBuilder::GenerateOBJ("Unicorn Left Leg", "OBJ//Transient_LeftLeg.obj"), "Image//Transient//Transient_Leg.tga");
	transform->SetTranslate(3.38, 0.5, 0);
	transform->SetScale(scale.x, scale.y, scale.z);
	nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	nodeInfo->second = "LeftLeg";
	nodeList.insert(*nodeInfo);

	//Right Leg
	newModel = new CModel();
	transform = new CTransform();
	nodeInfo = new std::pair<int, std::string>();
	newModel->setMesh(CModel::s_LOW, MeshBuilder::GenerateOBJ("Unicorn Right Leg", "OBJ//Transient_RightLeg.obj"), "Image//Transient//Transient_Leg.tga");
	newModel->setMesh(CModel::s_MID, MeshBuilder::GenerateOBJ("Unicorn Right Leg", "OBJ//Transient_RightLeg.obj"), "Image//Transient//Transient_Leg.tga");
	newModel->setMesh(CModel::s_HIGH, MeshBuilder::GenerateOBJ("Unicorn Right Leg", "OBJ//Transient_RightLeg.obj"), "Image//Transient//Transient_Leg.tga");
	transform->SetTranslate(-3.08, 0.5, 0);
	transform->SetScale(scale.x, scale.y, scale.z);
	nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	nodeInfo->second = "RightLeg";
	nodeList.insert(*nodeInfo);
}

AI::~AI()
{
}

float AI::getAngle()
{
	return rotateAngle;
}

void AI::Update(double dt, Vector3 playerPos, const float& terrainY)
{
	pos += vel;

	//Ai To Terrain Code
	float diff = terrainY - pos.y;
	pos.y += diff * static_cast<float>(dt) * 10;

	/*std::cout << currentState << std::endl;

	switch (currentState)
	{
	s_PATROL:
		patrolUpdate(dt);
		break;

	default:
		break;
	}
*/
	if (currentState == s_PATROL)
	{
		patrolUpdate(dt);
	}
	else if (currentState == s_COLLIDED)
	{
		collideUpdate(dt);
	}

	//Friction
	if (vel.x != 0)
	{
		float Fforce_x = 0 - vel.x;
		vel.x += Fforce_x * dt * 5.f;

		if (vel.x < 0.1 && vel.x > -0.1)
		{
			vel.x = 0;
		}
	}

	if (vel.z != 0)
	{
		float Fforce_z = 0 - vel.z;
		vel.z += Fforce_z * dt * 5.f;

		if (vel.z < 0.1 && vel.z > -0.1)
		{
			vel.z = 0;
		}
	}
}

void AI::patrolUpdate(const double &dt)
{
	if (moveDir.IsZero())
	{
		float dir = (float)Math::RandIntMinMax(-1, 1);
		while (dir == 0)
		{
			dir = (float)Math::RandIntMinMax(-1, 1);
		}
		bool moveByX = (bool)Math::RandIntMinMax(0, 1);

		if (moveByX)
			moveDir.x = dir;
		else
			moveDir.z = dir;

		movementTime = Math::RandFloatMinMax(5.f, 10.f);
	}
	else
	{
		if (currentTime < movementTime)
		{
			currentTime += (float)dt;
			animationUpdate(dt);
			vel += moveDir * dt * 7.f;

			if (moveDir.x == 1)
			{
				rotateAngle = 90;
			}
			else if (moveDir.x == -1)
			{
				rotateAngle = 270;
			}
			else if (moveDir.z == 1)
			{
				rotateAngle = 360;
			}
			else if (moveDir.z == -1)
			{
				rotateAngle = 180;
			}
		}
		else
		{
			moveDir.SetZero();
			currentTime = 0.f;
		}
	}
}

void AI::animationUpdate(const double& dt)
{
	animation->Update(dt, Vector3(vel.x, 0, vel.z).LengthSquared() * 50);

	for (std::unordered_map<int, std::string>::iterator it = nodeList.begin(); it != nodeList.end(); ++it)
	{
		CSceneNode* node = m_cSceneGraph->GetNode(it->first);
		if (node != NULL)
		{
			if (it->second == "LeftArm")
			{
				node->getTransform()->SetRotate2(animation->vel_LeftArm, 1, 0, 0, 0, 1, 0);
			}
			else if (it->second == "RightArm")
			{
				node->getTransform()->SetRotate2(animation->vel_RightArm, 1, 0, 0, 0, 1, 0);
			}
			else if (it->second == "LeftLeg")
			{
				node->getTransform()->SetRotate2(animation->vel_LeftLeg, 1, 0, 0, 0, 9, 0);
			}
			else if (it->second == "RightLeg")
			{
				node->getTransform()->SetRotate2(animation->vel_RightLeg, 1, 0, 0, 0, 9, 0);
			}
		}
	}
}

void AI::switchState(AI::AI_STATES currentState)
{
	this->currentState = currentState;
}

void AI::collideUpdate(const double &dt)
{
	Vector3 temp = moveDir;
	moveDir.SetZero();
	currentTime = 0.f;

	float dir = (float)Math::RandIntMinMax(-1, 1);
	while (dir == 0)
	{
		dir = (float)Math::RandIntMinMax(-1, 1);
	}
	bool moveByX = (bool)Math::RandIntMinMax(0, 1);

	if (moveByX)
		moveDir.x = dir;
	else
		moveDir.z = dir;

	if (moveDir == temp)
	{
		moveDir.SetZero();
		moveDir.x = temp.z;
		moveDir.z = temp.x;
	}

	currentState = s_PATROL;
}