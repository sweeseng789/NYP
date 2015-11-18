#pragma once

#include "MeshBuilder.h"
#include "Vector3.h"
#include "SceneGraph/SceneNode.h"
#include <unordered_map>

class COpponent
{
public:
	COpponent();
	COpponent(Vector3 pos);
	~COpponent();

	void Update(double dt, Vector3 playerPos);
	Vector3 getPos();
	CSceneNode* getNode();
	bool getActive();

private:
	Mesh* mesh;
	Vector3 pos;
	Vector3 vel;
	CSceneNode* enemyInfo;
	std::unordered_map<int, std::string> nodeList;

	bool active;
};

