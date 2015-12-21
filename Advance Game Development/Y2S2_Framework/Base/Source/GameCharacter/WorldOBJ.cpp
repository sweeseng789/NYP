#include "WorldOBJ.h"



CWorldOBJ::CWorldOBJ()
{
	m_cSceneGraph = new CSceneNode();
	CModel* newModel = new CModel();
	CTransform* transform = new CTransform();
	std::pair<int, std::string>* nodeInfo = new std::pair<int, std::string>();

	//Church
	/*newModel->Init(MeshBuilder::GenerateOBJ("Church", "OBJ//church.obj"), "Image//church.tga");
	transform->SetTranslate(0, 30.2, 0);
	transform->SetScale(scale.x, scale.y, scale.z);
	nodeInfo->first = m_cSceneGraph->SetNode(transform, newModel);
	nodeInfo->second = "Head";
	nodeList.insert(*nodeInfo);*/
}

CWorldOBJ::CWorldOBJ(Vector3 pos, float scale)
{
	this->pos = pos;
	this->scale.x = this->scale.y = this->scale.z = scale;
	active = true;
	health = newHealth = 100.f;

	m_cSceneGraph = new CSceneNode();
	CModel* newModel = new CModel();
	CTransform* transform = new CTransform();

	//Church
	newModel->Init(MeshBuilder::GenerateOBJ("Church", "OBJ//building.obj"), "Image//building.tga");
	transform->SetTranslate(0, 30.2, 0);
	transform->SetScale(this->scale.x, this->scale.y, this->scale.z);
	m_cSceneGraph->SetNode(transform, newModel);
}


CWorldOBJ::~CWorldOBJ()
{
}

void CWorldOBJ::update(const double& dt, float& terrainY)
{
	float diff = terrainY - pos.y;
	//if (health > 0)
	{
		/*if (health > newHealth)
		{
			health -= 100 * dt;
		}*/
		pos.y += diff * static_cast<float>(dt) * 100;
	}
	/*else
	{
		pos.y -= 20 * dt;
		if (pos.y < terrainY - 100)
		{
			active = false;
		}
	}*/
}