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

	newModel->Init(MeshBuilder::GenerateOBJ("Transient Head", "OBJ//Transient_Head.obj"), "Image//Transient//Transient_Head.tga");
	transform->SetScale(10, 10, 10);
	nodeInfo->first = m_cSceneGraph->SetNode(transform, newModel);
	nodeInfo->second = "Head";
	nodeList.insert(*nodeInfo);
}

AI::AI(Vector3 pos)
{
	this->pos = pos;
	this->vel.SetZero();
	this->scale.Set(10, 10, 10);
	active = true;
	type = CGameObject::ENEMY;

	m_cSceneGraph = new CSceneNode();
	CModel* newModel = new CModel();
	CTransform* transform = new CTransform();
	std::pair<int, std::string>* nodeInfo = new std::pair<int, std::string>();

	//Head
	newModel->Init(MeshBuilder::GenerateOBJ("Transient Head", "OBJ//Transient_Head.obj"), "Image//Transient//Transient_Head.tga");
	transform->SetTranslate(0, 30.2, 0);
	transform->SetScale(scale.x, scale.y, scale.z);
	nodeInfo->first = m_cSceneGraph->SetNode(transform, newModel);
	nodeInfo->second = "Head";
	nodeList.insert(*nodeInfo);

	//Torso
	newModel = new CModel();
	transform = new CTransform();
	nodeInfo = new std::pair<int, std::string>();
	newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Torso", "OBJ//Unicorn_Torso.obj"), "Image//Transient//Transient_Torso.tga");
	transform->SetTranslate(0, 16.5, 0);
	transform->SetScale(scale.x, scale.y, scale.z);
	nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	nodeInfo->second = "Torso";
	nodeList.insert(*nodeInfo);

	//Left Arm
	newModel = new CModel();
	transform = new CTransform();
	nodeInfo = new std::pair<int, std::string>();
	newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Left Arm", "OBJ//Transient_LeftArm.obj"), "Image//Transient//Transient_Arm.tga");
	transform->SetTranslate(9.5, 16.5, 0);
	transform->SetScale(scale.x, scale.y, scale.z);
	nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	nodeInfo->second = "LeftArm";
	nodeList.insert(*nodeInfo);

	//Right Arm
	newModel = new CModel();
	transform = new CTransform();
	nodeInfo = new std::pair<int, std::string>();
	newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Right Arm", "OBJ//Transient_RightArm.obj"), "Image//Transient//Transient_Arm.tga");
	transform->SetTranslate(-9.5, 16.5, 0);
	transform->SetScale(scale.x, scale.y, scale.z);
	nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	nodeInfo->second = "RightArm";
	nodeList.insert(*nodeInfo);

	//Left Leg
	newModel = new CModel();
	transform = new CTransform();
	nodeInfo = new std::pair<int, std::string>();
	newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Left Leg", "OBJ//Transient_LeftLeg.obj"), "Image//Transient//Transient_Leg.tga");
	transform->SetTranslate(3.38, 0.5, 0);
	transform->SetScale(scale.x, scale.y, scale.z);
	nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	nodeInfo->second = "LeftLeg";
	nodeList.insert(*nodeInfo);

	//Right Leg
	newModel = new CModel();
	transform = new CTransform();
	nodeInfo = new std::pair<int, std::string>();
	newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Right Leg", "OBJ//Transient_RightLeg.obj"), "Image//Transient//Transient_Leg.tga");
	transform->SetTranslate(-3.08, 0.5, 0);
	transform->SetScale(scale.x, scale.y, scale.z);
	nodeInfo->first = m_cSceneGraph->AddChild(transform, newModel);
	nodeInfo->second = "RightLeg";
	nodeList.insert(*nodeInfo);

}

AI::~AI()
{
}

void AI::Update(double dt, Vector3 playerPos)
{

}