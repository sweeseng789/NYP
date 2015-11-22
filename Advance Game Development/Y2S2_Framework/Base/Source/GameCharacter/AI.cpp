#include "AI.h"

AI::AI()
{
	this->pos.SetZero();
	this->vel.SetZero();
	active = true;
	type = CGameObject::ENEMY;

	m_cSceneGraph = new CSceneNode();
	CModel* newModel = new CModel();
	CTransform* transform = new CTransform();
	std::pair<int, std::string>* nodeInfo = new std::pair<int, std::string>();

	newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Head", "OBJ//Unicorn_Head.obj"), "Image//Unicorn_Gundam//Unicorn_Head.tga");
	transform->SetScale(10, 10, 10);
	nodeInfo->first = m_cSceneGraph->SetNode(transform, newModel);
	nodeInfo->second = "Head";
	nodeList.insert(*nodeInfo);
}

AI::AI(Vector3 pos)
{
	this->pos = pos;
	this->vel.SetZero();
	active = true;
	type = CGameObject::ENEMY;

	m_cSceneGraph = new CSceneNode();
	CModel* newModel = new CModel();
	CTransform* transform = new CTransform();
	std::pair<int, std::string>* nodeInfo = new std::pair<int, std::string>();

	newModel->Init(MeshBuilder::GenerateOBJ("Unicorn Head", "OBJ//Unicorn_Head.obj"), "Image//Unicorn_Gundam//Unicorn_Head.tga");
	transform->SetScale(10, 10, 10);
	nodeInfo->first = m_cSceneGraph->SetNode(transform, newModel);
	nodeInfo->second = "Head";
	nodeList.insert(*nodeInfo);
}

AI::~AI()
{
}

void AI::Update(double dt, Vector3 playerPos)
{

}