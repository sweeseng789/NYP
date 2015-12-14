#include "PlayInfo3PV.h"
#include <Windows.h>

CPlayInfo3PV::CPlayInfo3PV(void)
{
	Init();
}


CPlayInfo3PV::~CPlayInfo3PV(void)
{
	if (m_cSceneGraph)
	{
		delete m_cSceneGraph;
		m_cSceneGraph = NULL;
	}

	Exit();
}

void CPlayInfo3PV::Init()
{
	animation = new CharAnimation();
	pos.SetZero();
	direction.Set(0, 0, 1);
	scale.Set(10, 10, 10);
	type = CGameObject::PLAYER;
	active = true;
	mode = STANDBY;
	stage = FAWithBooster;
	isFlying = false;

	// Initialise the Avatar's movement flags
	for (int i = 0; i < 255; i++) 
	{
		myKeys[i] = false;
	}

	m_cSceneGraph = new CSceneNode();
	CModel* newModel = new CModel();
	CTransform* transform = new CTransform();
	std::pair<int, std::string>* nodeInfo = new std::pair<int, std::string>();

	//Head
	newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Head", "OBJ//Unicorn_Head.obj"), "Image//Unicorn_Gundam//Unicorn_Head.tga");
	transform->SetTranslate(0, 30.2, 0);
	transform->SetScale(scale.x, scale.y, scale.z);
	nodeInfo->first = m_cSceneGraph->SetNode(transform, newModel);
	nodeInfo->second = "Head";
	nodeList.insert(*nodeInfo);

	//Torso
	newModel = new CModel();
	transform = new CTransform();
	nodeInfo = new std::pair<int, std::string>();
	newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Torso", "OBJ//Unicorn_Torso.obj"), "Image//Unicorn_Gundam//Unicorn_Torso.tga");
	transform->SetTranslate(0, 16.5, 0);
	transform->SetScale(scale.x, scale.y, scale.z);
	nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	nodeInfo->second = "Torso";
	nodeList.insert(*nodeInfo);

	//Left Arm
	newModel = new CModel();
	transform = new CTransform();
	nodeInfo = new std::pair<int, std::string>();
	newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Left Arm", "OBJ//Unicorn_Arm.obj"), "Image//Unicorn_Gundam//Unicorn_ArmLeft.tga");
	transform->SetTranslate(9.5, 16.5, 0);
	transform->SetScale(scale.x, scale.y, scale.z);
	nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	nodeInfo->second = "LeftArm";
	nodeList.insert(*nodeInfo);

	//Right Arm
	newModel = new CModel();
	transform = new CTransform();
	nodeInfo = new std::pair<int, std::string>();
	newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Right Arm", "OBJ//Unicorn_Arm.obj"), "Image//Unicorn_Gundam//Unicorn_ArmRight.tga");
	transform->SetTranslate(-9.5, 16.5, 0);
	transform->SetScale(scale.x, scale.y, scale.z);
	nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	nodeInfo->second = "RightArm";
	nodeList.insert(*nodeInfo);

	//Left Leg
	newModel = new CModel();
	transform = new CTransform();
	nodeInfo = new std::pair<int, std::string>();
	newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Left Leg", "OBJ//Unicorn_Leg.obj"), "Image//Unicorn_Gundam//Unicorn_LegLeft.tga");
	transform->SetTranslate(3.38, 0.5, 0);
	transform->SetScale(scale.x, scale.y, scale.z);
	nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	nodeInfo->second = "LeftLeg";
	nodeList.insert(*nodeInfo);

	//Right Leg
	newModel = new CModel();
	transform = new CTransform();
	nodeInfo = new std::pair<int, std::string>();
	newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Right Leg", "OBJ//Unicorn_Leg.obj"), "Image//Unicorn_Gundam//Unicorn_LegRight.tga");
	transform->SetTranslate(-3.08, 0.5, 0);
	transform->SetScale(scale.x, scale.y, scale.z);
	nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	nodeInfo->second = "RightLeg";
	nodeList.insert(*nodeInfo);

	//===============WEAPONS & SHIELD===============//

	//Left Arm Shield
	newModel = new CModel();
	transform = new CTransform();
	nodeInfo = new std::pair<int, std::string>();
	newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Shield", "OBJ//Unicorn_Shield.obj"), "Image//Unicorn_Gundam//Unicorn_Shield.tga");
	transform->SetTranslate(13, 16.5, 0);
	transform->SetScale(scale.x, scale.y, scale.z);
	nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	nodeInfo->second = "LeftShield";
	nodeList.insert(*nodeInfo);

	//Right Arm Shield
	newModel = new CModel();
	transform = new CTransform();
	nodeInfo = new std::pair<int, std::string>();
	newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Shield", "OBJ//Unicorn_Shield.obj"), "Image//Unicorn_Gundam//Unicorn_Shield.tga");
	transform->SetTranslate(-13, 16.5, 0);
	transform->setRotationOrientation(180, 0, 1, 0);
	transform->SetScale(10, 10, 10);
	nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	nodeInfo->second = "RightShield";
	nodeList.insert(*nodeInfo);

	////Middle Shield
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Shield", "OBJ//Unicorn_Shield.obj"), "Image//Unicorn_Gundam//Unicorn_Shield.tga");
	//transform->SetTranslate(0, 22, -10);
	//transform->setRotationOrientation(90, 0, 1, 0);
	//transform->setRotationOrientation(180, 1, 0, 0);
	//transform->SetScale(scale.x, scale.y, scale.z);
	//nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	//nodeInfo->second = "MiddleShield";
	//nodeList.insert(*nodeInfo);

	//Right Beam Magnum
	newModel = new CModel();
	transform = new CTransform();
	nodeInfo = new std::pair<int, std::string>();
	newModel->Init(MeshBuilder::GenerateOBJ("Beam Magnum", "OBJ//Beam_Magnum.obj"), "Image//Unicorn_Gundam//Beam_Magnum.tga");
	transform->SetTranslate(-9.5, 16.5, 0);
	transform->SetScale(scale.x, scale.y, scale.z);
	nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	nodeInfo->second = "RightBeamMagnum";
	nodeList.insert(*nodeInfo);

	////Left Beam Saber
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Beam Magnum", "OBJ//Beam_Saber.obj"), "Image//Unicorn_Gundam//Beam_Saber.tga");
	//transform->SetTranslate(-3, 27.3, -6);
	//transform->SetScale(scale.x, scale.y, scale.z);
	//nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	//nodeInfo->second = "LeftBeamSaber";
	//nodeList.insert(*nodeInfo);

	////RightBeamSaber
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Beam Magnum", "OBJ//Beam_Saber.obj"), "Image//Unicorn_Gundam//Beam_Saber.tga");
	//transform->SetTranslate(2.8, 27.3, -6);
	//transform->SetScale(scale.x, scale.y, scale.z);
	//nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	//nodeInfo->second = "RightBeamSaber";
	//nodeList.insert(*nodeInfo);

	////Left Rocket Launcher
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Beam Magnum", "OBJ//UnicornRocketLauncherLeft.obj"), "Image//Unicorn_Gundam//UnicornRocketLauncher.tga");
	//transform->SetTranslate(8.5, 27.3, -13);
	//transform->SetScale(scale.x, scale.y, scale.z);
	//nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	//nodeInfo->second = "LeftRocketLauncher";
	//nodeList.insert(*nodeInfo);

	////Right Rocket Launcher
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Beam Magnum", "OBJ//UnicornRocketLauncherRight.obj"), "Image//Unicorn_Gundam//UnicornRocketLauncher.tga");
	//transform->SetTranslate(-8.5, 27.3, -13);
	//transform->SetScale(scale.x, scale.y, scale.z);
	//nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	//nodeInfo->second = "RightRocketLauncher";
	//nodeList.insert(*nodeInfo);

	////Left Mini Rocket Top
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Beam Magnum", "OBJ//UnicornMiniRocket.obj"), "Image//Unicorn_Gundam//UnicornMiniRocket.tga");
	//transform->SetTranslate(10, 32, -9.5);
	//transform->SetScale(scale.x, scale.y, scale.z);
	//nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	//nodeInfo->second = "LeftMiniRocketTop";
	//nodeList.insert(*nodeInfo);

	////Right Mini Rocket Top
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Beam Magnum", "OBJ//UnicornMiniRocket.obj"), "Image//Unicorn_Gundam//UnicornMiniRocket.tga");
	//transform->SetTranslate(-10, 32, -9.5);
	//transform->SetScale(scale.x, scale.y, scale.z);
	//nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	//nodeInfo->second = "RightMiniRocketTop";
	//nodeList.insert(*nodeInfo);

	////Left Mini Rocket Bottom
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Left Leg", "OBJ//UnicornMiniRocket.obj"), "Image//Unicorn_Gundam//UnicornMiniRocket.tga");
	//transform->SetTranslate(7.2, 0.5, 0);
	//transform->SetScale(scale.x, scale.y, scale.z);
	//nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	//nodeInfo->second = "LeftMiniRocketBottom";
	//nodeList.insert(*nodeInfo);

	////Right Mini Rocket Bottom
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Right Leg", "OBJ//UnicornMiniRocket.obj"), "Image//Unicorn_Gundam//UnicornMiniRocket.tga");
	//transform->SetTranslate(-7, 0.5, 0);
	//transform->SetScale(scale.x, scale.y, scale.z);
	//nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	//nodeInfo->second = "RightMiniRocketBottom";
	//nodeList.insert(*nodeInfo);

	////Left Propellant Tank
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Right Leg", "OBJ//PropellantTanks.obj"), "Image//Unicorn_Gundam//PropellantTanks.tga");
	//transform->SetTranslate(5, 4, -12);
	//transform->setRotationOrientation(45, 1, -1, 0);
	//transform->SetScale(scale.x, scale.y, scale.z);
	//nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	//nodeInfo->second = "LeftPropellantTanks";
	//nodeList.insert(*nodeInfo);

	////Right Propellant Tank
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Right Leg", "OBJ//PropellantTanks.obj"), "Image//Unicorn_Gundam//PropellantTanks.tga");
	//transform->SetTranslate(-5, 4, -12);
	//transform->setRotationOrientation(45, 1, 1, 0);
	//transform->SetScale(scale.x, scale.y, scale.z);
	//nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	//nodeInfo->second = "RightPropellantTanks";
	//nodeList.insert(*nodeInfo);
}

void CPlayInfo3PV::Exit()
{
	/*for (std::unordered_map<int, std::string>::iterator it = nodeList.begin(); it != nodeList.end(); ++it)
	{
		std::pair<int, std::string> node = *it;
		std::cout << node.first << ", " << node.second << std::endl;
	}*/
	nodeList.clear();
}

void CPlayInfo3PV::Update(const double &dt, Camera3 &camera, const float& terrainY)
{
	//Control Update
	controlUpdate(dt, camera, terrainY);

	//Model Animation Update
	modelAnimationUpdate(camera);

	//Animation Update
	if (!isFlying)
		animation->Update(dt, Vector3(vel.x, 0, vel.z).LengthSquared() * 15);


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

	//Position Update
	pos += vel;

	//Character to Terrain
	if (!isFlying)
	{
		float diff = terrainY - pos.y;
		pos.y += diff * static_cast<float>(dt) * 10;
	}
}

///********************************************************************************
// Update Movement
// ********************************************************************************/
void CPlayInfo3PV::UpdateMovement(const unsigned char key, const bool status)
{
	myKeys[key] = status;
}

void CPlayInfo3PV::modelAnimationUpdate(Camera3 &camera)
{
	for (std::unordered_map<int, std::string>::iterator it = nodeList.begin(); it != nodeList.end(); ++it)
	{
		CSceneNode* node = m_cSceneGraph->GetNode(it->first);
		if (node != NULL)
		{
			if (it->second == "LeftLeg" || it->second == "LeftMiniRocketBottom")
			{
				node->getTransform()->SetRotate2(animation->vel_LeftLeg, 1, 0, 0, 0, 9, 0);
			}
			else if (it->second == "RightLeg" || it->second == "RightMiniRocketBottom")
			{

				node->getTransform()->SetRotate2(animation->vel_RightLeg, 1, 0, 0, 0, 9, 0);
			}
			else if (it->second == "LeftArm" || it->second == "LeftShield")
			{
				if (isStandByMode() || camera.isLookingRight())
				{
					node->getTransform()->SetRotate2(animation->vel_LeftArm, 1, 0, 0, 0, 1, 0);
				}
				else
				{
					if (!camera.isLookingRight())
					{
						node->getTransform()->SetRotate2((camera.getPitchAroundObj()) - 90, 1, 0, 0, 0, 5, 0);
					}
				}
			}
			else if (it->second == "RightArm" || it->second == "RightBeamMagnum")
			{
				if (isStandByMode() || !camera.isLookingRight())
				{

					node->getTransform()->SetRotate2(animation->vel_RightArm, 1, 0, 0, 0, 1, 0);
				}
				else
				{
					if (camera.isLookingRight())
					{
						node->getTransform()->SetRotate2((camera.getPitchAroundObj()) - 90, 1, 0, 0, 0, 5, 0);
					}
				}
			}
			else if (it->second == "RightShield")
			{
				if (isStandByMode() || !camera.isLookingRight())
				{
					node->getTransform()->SetRotate2(animation->vel_LeftArm, 1, 0, 0, 0, 1, 0);
				}
				else
				{
					if (camera.isLookingRight())
					{
						node->getTransform()->SetRotate2(-(camera.getPitchAroundObj() - 90), 1, 0, 0, 0, 5, 0);
					}
				}
			}
		}
	}
}

void CPlayInfo3PV::controlUpdate(const double& dt, Camera3 &camera, const float& terrainY)
{
	Vector3 view = camera.getView();
	view.y = 0;

	Vector3 right = camera.getRight();
	right.y = 0;

	if (!isFlying)
		velSpeed = 30.f;
	else
		velSpeed = 15.f;

	if (myKeys['w'])
	{
		vel += view * velSpeed * dt;
	}

	if (myKeys['s'])
	{
		vel -= view * velSpeed * dt;
	}

	if (myKeys['a'])
	{
		vel -= right * velSpeed * dt;
	}

	if (myKeys['d'])
	{
		vel += right * velSpeed * dt;
	}


	if (myKeys[VK_SPACE])
	{
		animation->setZero();
		isFlying = true;
		pos.y += 9.82 * 20 * dt;

		if (vel.y < 0.f)
		{
			vel.y += 9.82 * 20 * dt;
		}
	}
	else
	{
		if (isFlying)
		{
			vel.y -= 9.82 * 5 * dt;

			if (pos.y < terrainY)
			{
				isFlying = false;
				vel.y = 0.f;
			}
		}
	}

	static double timeLimit_Mode = 0;
	static double timeLimit = 0.5;

	if (timeLimit_Mode < timeLimit)
	{
		timeLimit_Mode += dt;
	}
	else
	{
		if (myKeys[VK_TAB])
		{
			switchMode();
			timeLimit_Mode = 0.0;
		}
	}
}

void CPlayInfo3PV::switchMode()
{
	if (mode == STANDBY)
	{
		mode = ATTACK;
	}
	else
	{
		mode = STANDBY;
	}
}

float CPlayInfo3PV::getAngle()
{
	return angle;
}

bool CPlayInfo3PV::isAttackMode()
{
	if (mode == ATTACK)
		return true;
	return false;
}

bool CPlayInfo3PV::isStandByMode()
{
	if (mode == STANDBY)
		return true;
	return false;
}