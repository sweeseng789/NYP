#include "PlayInfo3PV.h"
#include "MeshBuilder.h"

float CPlayInfo3PV::velSpeed = 30.f;

CPlayInfo3PV::CPlayInfo3PV(void)
	: theAvatarMesh(NULL)
	, head(NULL)
	, torso(NULL)
	, leftArm(NULL)
	, leftLeg(NULL)
	, rightArm(NULL)
	, rightLeg(NULL)
	, rifle(NULL)
	, shield(NULL)
	, saber(NULL)
	, jumpspeed(0)
	, avatarInfo(NULL)
{
	Init();
}


CPlayInfo3PV::~CPlayInfo3PV(void)
{
	if (theAvatarMesh)
	{
		delete theAvatarMesh;
		theAvatarMesh = NULL;
	}

	if (avatarInfo)
	{
		delete avatarInfo;
		avatarInfo = NULL;
	}
}

// Initialise this class instance
void CPlayInfo3PV::Init(void)
{
	curPosition.Set( 0, 0, 0);
	curDirection.Set( 0, 0, 1 );

	// Initialise the Avatar's movement flags
	for(int i=0; i<255; i++){
		myKeys[i] = false;
	}

	vel.SetZero();
	rotateAngle = 0.f;
	isMoving = false;

	avatarInfo = new CSceneNode();
	CModel* newModel = new CModel();
	CTransform* transform = new CTransform();
	std::pair<int, std::string>* nodeInfo = new std::pair<int, std::string>();

	//Head
	newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Head", "OBJ//Unicorn_Head.obj"), "Image//Unicorn_Gundam//Unicorn_Head.tga");
	transform->SetTranslate(0, 30.2, 0);
	transform->SetScale(10, 10, 10);
	nodeInfo->first = avatarInfo->SetNode(transform, newModel);
	nodeInfo->second = "Head";
	nodeList.insert(*nodeInfo);

	////Torso
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Torso", "OBJ//Unicorn_Torso.obj"), "Image//Unicorn_Gundam//Unicorn_Torso.tga");
	//transform->SetTranslate(0, 16.5, 0);
	//transform->SetScale(10, 10, 10);
	//nodeInfo->first = avatarInfo->AddChild(transform, newModel);
	//nodeInfo->second = "Torso";
	//nodeList.insert(*nodeInfo);

	////Left Arm
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Left Arm", "OBJ//Unicorn_Arm.obj"), "Image//Unicorn_Gundam//Unicorn_ArmLeft.tga");
	//transform->SetTranslate(9.5, 16.5, 0);
	//transform->SetScale(10, 10, 10);
	//nodeInfo->first = avatarInfo->AddChild(transform, newModel);
	//nodeInfo->second = "LeftArm";
	//nodeList.insert(*nodeInfo);

	////Right Arm
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Right Arm", "OBJ//Unicorn_Arm.obj"), "Image//Unicorn_Gundam//Unicorn_ArmRight.tga");
	//transform->SetTranslate(-9.5, 16.5, 0);
	//transform->SetScale(10, 10, 10);
	//nodeInfo->first = avatarInfo->AddChild(transform, newModel);
	//nodeInfo->second = "RightArm";
	//nodeList.insert(*nodeInfo);

	////Left Leg
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Left Leg", "OBJ//Unicorn_Leg.obj"), "Image//Unicorn_Gundam//Unicorn_LegLeft.tga");
	//transform->SetTranslate(3.38, 0.5, 0);
	//transform->SetScale(10, 10, 10);
	//nodeInfo->first = avatarInfo->AddChild(transform, newModel);
	//nodeInfo->second = "LeftLeg";
	//nodeList.insert(*nodeInfo);

	////Right Leg
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Right Leg", "OBJ//Unicorn_Leg.obj"), "Image//Unicorn_Gundam//Unicorn_LegRight.tga");
	//transform->SetTranslate(-3.08, 0.5, 0);
	//transform->SetScale(10, 10, 10);
	//nodeInfo->first = avatarInfo->AddChild(transform, newModel);
	//nodeInfo->second = "RightLeg";
	//nodeList.insert(*nodeInfo);

	////===============WEAPONS & SHIELD===============//

	////Left Arm Shield
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Shield", "OBJ//Unicorn_Shield.obj"), "Image//Unicorn_Gundam//Unicorn_Shield.tga");
	//transform->SetTranslate(13, 16.5, 0);
	//transform->SetScale(10, 10, 10);
	//nodeInfo->first = avatarInfo->AddChild(transform, newModel);
	//nodeInfo->second = "LeftShield";
	//nodeList.insert(*nodeInfo);

	////Right Arm Shield
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Shield", "OBJ//Unicorn_Shield.obj"), "Image//Unicorn_Gundam//Unicorn_Shield.tga");
	//transform->SetTranslate(-13, 16.5, 0);
	//transform->setRotationOrientation(180, 0, 1, 0);
	//transform->SetScale(10, 10, 10);
	//nodeInfo->first = avatarInfo->AddChild(transform, newModel);
	//nodeInfo->second = "RightShield";
	//nodeList.insert(*nodeInfo);

	////Middle Shield
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Shield", "OBJ//Unicorn_Shield.obj"), "Image//Unicorn_Gundam//Unicorn_Shield.tga");
	//transform->SetTranslate(0, 22, -10);
	//transform->setRotationOrientation(90, 0, 1, 0);
	//transform->setRotationOrientation(180, 1, 0, 0);
	//transform->SetScale(10, 10, 10);
	//nodeInfo->first = avatarInfo->AddChild(transform, newModel);
	//nodeInfo->second = "MiddleShield";
	//nodeList.insert(*nodeInfo);

	////Right Beam Magnum
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Beam Magnum", "OBJ//Beam_Magnum.obj"), "Image//Unicorn_Gundam//Beam_Magnum.tga");
	//transform->SetTranslate(-9.5, 16.5, 0);
	//transform->SetScale(10, 10, 10);
	//nodeInfo->first = avatarInfo->AddChild(transform, newModel);
	//nodeInfo->second = "RightBeamMagnum";
	//nodeList.insert(*nodeInfo);

	////Left Beam Saber
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Beam Magnum", "OBJ//Beam_Saber.obj"), "Image//Unicorn_Gundam//Beam_Saber.tga");
	//transform->SetTranslate(-3, 27.3, -6);
	//transform->SetScale(10, 10, 10);
	//nodeInfo->first = avatarInfo->AddChild(transform, newModel);
	//nodeInfo->second = "LeftBeamSaber";
	//nodeList.insert(*nodeInfo);

	////RightBeamSaber
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Beam Magnum", "OBJ//Beam_Saber.obj"), "Image//Unicorn_Gundam//Beam_Saber.tga");
	//transform->SetTranslate(2.8, 27.3, -6);
	//transform->SetScale(10, 10, 10);
	//nodeInfo->first = avatarInfo->AddChild(transform, newModel);
	//nodeInfo->second = "RightBeamSaber";
	//nodeList.insert(*nodeInfo);

	////Left Rocket Launcher
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Beam Magnum", "OBJ//UnicornRocketLauncherLeft.obj"), "Image//Unicorn_Gundam//UnicornRocketLauncher.tga");
	//transform->SetTranslate(8.5, 27.3, -13);
	//transform->SetScale(10, 10, 10);
	//nodeInfo->first = avatarInfo->AddChild(transform, newModel);
	//nodeInfo->second = "LeftRocketLauncher";
	//nodeList.insert(*nodeInfo);

	////Right Rocket Launcher
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Beam Magnum", "OBJ//UnicornRocketLauncherRight.obj"), "Image//Unicorn_Gundam//UnicornRocketLauncher.tga");
	//transform->SetTranslate(-8.5, 27.3, -13);
	//transform->SetScale(10, 10, 10);
	//nodeInfo->first = avatarInfo->AddChild(transform, newModel);
	//nodeInfo->second = "RightRocketLauncher";
	//nodeList.insert(*nodeInfo);

	////Left Mini Rocket Top
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Beam Magnum", "OBJ//UnicornMiniRocket.obj"), "Image//Unicorn_Gundam//UnicornMiniRocket.tga");
	//transform->SetTranslate(10, 32, -9.5);
	//transform->SetScale(10, 10, 10);
	//nodeInfo->first = avatarInfo->AddChild(transform, newModel);
	//nodeInfo->second = "LeftMiniRocketTop";
	//nodeList.insert(*nodeInfo);

	////Right Mini Rocket Top
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Beam Magnum", "OBJ//UnicornMiniRocket.obj"), "Image//Unicorn_Gundam//UnicornMiniRocket.tga");
	//transform->SetTranslate(-10, 32, -9.5);
	//transform->SetScale(10, 10, 10);
	//nodeInfo->first = avatarInfo->AddChild(transform, newModel);
	//nodeInfo->second = "RightMiniRocketTop";
	//nodeList.insert(*nodeInfo);

	////Left Mini Rocket Bottom
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Left Leg", "OBJ//UnicornMiniRocket.obj"), "Image//Unicorn_Gundam//UnicornMiniRocket.tga");
	//transform->SetTranslate(7.2, 0.5, 0);
	//transform->SetScale(10, 10, 10);
	//nodeInfo->first = avatarInfo->AddChild(transform, newModel);
	//nodeInfo->second = "LeftMiniRocketBottom";
	//nodeList.insert(*nodeInfo);

	////Right Mini Rocket Bottom
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Right Leg", "OBJ//UnicornMiniRocket.obj"), "Image//Unicorn_Gundam//UnicornMiniRocket.tga");
	//transform->SetTranslate(-7, 0.5, 0);
	//transform->SetScale(10, 10, 10);
	//nodeInfo->first = avatarInfo->AddChild(transform, newModel);
	//nodeInfo->second = "RightMiniRocketBottom";
	//nodeList.insert(*nodeInfo);

	////Left Propellant Tank
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Right Leg", "OBJ//PropellantTanks.obj"), "Image//Unicorn_Gundam//PropellantTanks.tga");
	//transform->SetTranslate(5, 4, -12);
	//transform->setRotationOrientation(45, 1, -1, 0);
	//transform->SetScale(10, 10, 10);
	//nodeInfo->first = avatarInfo->AddChild(transform, newModel);
	//nodeInfo->second = "LeftPropellantTanks";
	//nodeList.insert(*nodeInfo);

	////Right Propellant Tank
	//newModel = new CModel();
	//transform = new CTransform();
	//nodeInfo = new std::pair<int, std::string>();
	//newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Right Leg", "OBJ//PropellantTanks.obj"), "Image//Unicorn_Gundam//PropellantTanks.tga");
	//transform->SetTranslate(-5, 4, -12);
	//transform->setRotationOrientation(45, 1, 1, 0);
	//transform->SetScale(10, 10, 10);
	//nodeInfo->first = avatarInfo->AddChild(transform, newModel);
	//nodeInfo->second = "RightPropellantTanks";
	//nodeList.insert(*nodeInfo);
}

// Set Model
bool CPlayInfo3PV::SetModel( Mesh* theAvatarMesh )
{
	this->theAvatarMesh = theAvatarMesh;
	if (this->theAvatarMesh == NULL)
		return false;

	return true;
}

// Returns true if the player is on ground
bool CPlayInfo3PV::isOnGround(void)
{
	return true;
}

// Returns true if the player is jumping upwards
bool CPlayInfo3PV::isJumpUpwards(void)
{
	return true;
}

// Returns true if the player is on freefall
bool CPlayInfo3PV::isFreeFall(void)
{
	return true;
}

// Set the player's status to free fall mode
void CPlayInfo3PV::SetOnFreeFall(bool isOnFreeFall)
{
	if (isOnFreeFall == true)
	{
		jumpspeed = 0;
	}
}

// Set the player to jumping upwards
void CPlayInfo3PV::SetToJumpUpwards(bool isOnJumpUpwards)
{
	if (isOnJumpUpwards == true)
	{
		jumpspeed = 15;
	}
}

// Set position x of the player
void CPlayInfo3PV::SetPos_x(int pos_x)
{
	curPosition.x = pos_x;
}

// Set position y of the player
void CPlayInfo3PV::SetPos_y(int pos_y)
{
	curPosition.y = pos_y;
}

// Set position y of the player
void CPlayInfo3PV::SetPos_z(int pos_z)
{
	curPosition.z = pos_z;
}

// Set Jumpspeed of the player
void CPlayInfo3PV::SetJumpspeed(int jumpspeed)
{
	this->jumpspeed = jumpspeed;
}

// Stop the player's movement
void CPlayInfo3PV::SetToStop(void)
{
	jumpspeed = 0;
}

/********************************************************************************
 Hero Move Up Down
 ********************************************************************************/
void CPlayInfo3PV::MoveFrontBack(const bool mode, const float timeDiff)
{
	if (mode)
	{
		curPosition.z = curPosition.z - (int) (200.0f * timeDiff);
	}
	else
	{
		curPosition.z = curPosition.z + (int) (200.0f * timeDiff);
	}
}

/********************************************************************************
 Hero Move Left Right
 ********************************************************************************/
void CPlayInfo3PV::MoveLeftRight(const bool mode, const float timeDiff)
{
	if (mode)
	{
		curPosition.x = curPosition.x + (int) (200.0f * timeDiff);
	}
	else
	{
		curPosition.x = curPosition.x - (int) (200.0f * timeDiff);
	}
}


// Get position x of the player
int CPlayInfo3PV::GetPos_x(void)
{
	return curPosition.x;
}

// Get position y of the player
int CPlayInfo3PV::GetPos_y(void)
{
	return curPosition.y;
}

// Get position y of the player
int CPlayInfo3PV::GetPos_z(void)
{
	return curPosition.z;
}

// Get position of the player
Vector3 CPlayInfo3PV::GetPosition()
{
	return curPosition;
}

// Get direction of the player
Vector3 CPlayInfo3PV::GetDirection()
{
	return curDirection;
}

// Get Jumpspeed of the player
int CPlayInfo3PV::GetJumpspeed(void)
{
	return jumpspeed;
}

// Update Jump Upwards
void CPlayInfo3PV::UpdateJumpUpwards()
{
	curPosition.y -= jumpspeed;
	jumpspeed -= 1;
	if (jumpspeed == 0)
	{
	}
}

// Update FreeFall
void CPlayInfo3PV::UpdateFreeFall()
{
	curPosition.y += jumpspeed;
	jumpspeed += 1;
}

// Constrain the position of the Hero to within the border
void CPlayInfo3PV::ConstrainHero(const int leftBorder, const int rightBorder, 
								  const int topBorder, const int bottomBorder, 
								  float timeDiff)
{
	if (curPosition.x < leftBorder)
	{
		curPosition.x = leftBorder;
	}
	else if (curPosition.x > rightBorder)
	{
		curPosition.x = rightBorder;
	}

	if (curPosition.y < topBorder)
		curPosition.y = topBorder;
	else if (curPosition.y > bottomBorder)
		curPosition.y = bottomBorder;
}

float CPlayInfo3PV::getRotationAngle()
{
	return rotateAngle;
}

Vector3 CPlayInfo3PV::getVel()
{
	return vel;
}


/********************************************************************************
 Update Movement
 ********************************************************************************/
void CPlayInfo3PV::UpdateMovement(const unsigned char key, const bool status)
{
	myKeys[key] = status;
}

/********************************************************************************
 Update
 ********************************************************************************/
void CPlayInfo3PV::Update(double dt, Camera3 &camera)
{
	animation.Update(dt, vel.LengthSquared() * 15);

	for (std::unordered_map<int, std::string>::iterator it = nodeList.begin(); it != nodeList.end(); ++it)
	{
		CSceneNode* node = avatarInfo->GetNode(it->first);
		if (node != NULL)
		{
			if (it->second == "LeftLeg" || it->second == "LeftMiniRocketBottom")
			{
				node->getTransform()->SetRotate2(animation.vel_LeftLeg, 1, 0, 0, 0, 9, 0);
			}
			else if (it->second == "RightLeg" || it->second == "RightMiniRocketBottom")
			{
				node->getTransform()->SetRotate2(animation.vel_RightLeg, 1, 0, 0, 0, 9, 0);
			}
			else if (it->second == "LeftArm" || it->second == "LeftShield" || it->second == "RightShield")
			{
				node->getTransform()->SetRotate2(animation.vel_LeftArm, 1, 0, 0, 0, 1, 0);
			}
			else if (it->second == "RightArm" || it->second == "RightBeamMagnum")
			{
				node->getTransform()->SetRotate2(animation.vel_RightArm, 1, 0, 0, 0, 1, 0);
			}
		}
	}

	Vector3 view = camera.direction;
	view.Normalize();
	view.y = 0;

	Vector3 right = view.Cross(camera.up);
	right.y = 0;
	right.Normalize();

	// WASD movement
	if ( myKeys['w'] == true)
	{
		vel += view * velSpeed * dt;
	}

	if (myKeys['s'] == true)
	{
		vel -= view * velSpeed * dt;
	}

	if (myKeys['a'] == true)
	{
		vel -= right * velSpeed * dt;
	}

	if (myKeys['d'] == true)
	{
		vel += right * velSpeed * dt;
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

	curPosition += vel;

	// Rotation
	/*
	if ( myKeys[VK_UP] == true)
	{
		LookUp( dt );
	}
	if (myKeys[VK_DOWN] == true)
	{
		LookUp( -dt );
	}
	if (myKeys[VK_LEFT] == true)
	{
		TurnLeft( -dt );
	}
	if (myKeys[VK_RIGHT] == true)
	{
		TurnRight( dt );
	}

	// Jump
	if (myKeys[32] == true)
	{
		Jump( dt );
		myKeys[32]	= false;
	}
	UpdateJump(dt);

	//Update the camera direction based on mouse move
	// left-right rotate
	if ( Application::camera_yaw != 0 )
		Yaw( dt );
	if ( Application::camera_pitch != 0 )
		Pitch( dt );

	if(Application::IsKeyPressed('R'))
	{
		Reset();
	}
	*/
}

void CPlayInfo3PV::Exit()
{
	/*for (std::unordered_map<int, std::string>::iterator it = nodeList->begin(); it != nodeList->end(); ++it)
	{
		std::pair<int, std::string> node = *it;
		std::cout << node.first << ", " << node.second << std::endl;
	}*/
}