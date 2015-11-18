#include "Opponent.h"



COpponent::COpponent()
{
}

COpponent::COpponent(Vector3 pos)
{
	this->mesh = mesh;
	this->pos = pos;
	this->vel.SetZero();
	active = true;

	enemyInfo = new CSceneNode();
	CModel* newModel = new CModel();
	CTransform* transfrom = new CTransform();
	std::pair<int, std::string>* nodeInfo = new std::pair<int, std::string>();

	newModel->Init(MeshBuilder::GenerateCube("Cube", Color(1, 0, 0), 1), "Image//Unicorn_Gundam//Unicorn_Head.tga");
	transfrom->SetScale(10, 10, 10);
	nodeInfo->first = enemyInfo->SetNode(transfrom, newModel);
	nodeInfo->second = "Body";
	nodeList.insert(*nodeInfo);
}

COpponent::~COpponent()
{
}

Vector3 COpponent::getPos()
{
	return pos;
}

CSceneNode* COpponent::getNode()
{
	return enemyInfo;
}

bool COpponent::getActive()
{
	return active;
}

void COpponent::Update(double dt, Vector3 playerPos)
{

}