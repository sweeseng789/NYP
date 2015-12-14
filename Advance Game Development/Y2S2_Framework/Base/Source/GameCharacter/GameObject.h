#pragma once

#include "Vector3.h"
#include "../SceneGraph/SceneNode.h"
#include "../Camera3.h"
#include "SSDLC.h"
#include "../MeshBuilder.h"
#include <unordered_map>

class CGameObject
{
public:
	struct CharAnimation
	{
		CharAnimation();
		~CharAnimation();

		bool invertWalkingDirection;

		float vel_LeftArm;

		float vel_RightArm;

		float vel_LeftLeg;

		float vel_RightLeg;

		void Update(const double &dt, float vel);
		void setZero();
	};

	enum GO_TYPE
	{
		STATIC_OBJ,
		MOVABLE_OBJ,
		PLAYER,
		ENEMY,
		PLAYERBULLET,
		ENEMYBULLET
	};
	
	CGameObject();
	virtual ~CGameObject();

	//Setter
	void setPos(Vector3 pos);
	void setPos_x(float pos_x);
	void setPos_y(float pos_y);
	void setPos_z(float pos_z);
	void setVel(Vector3 vel);
	void setScale(Vector3 scale);
	void setDirection(Vector3 direction);
	void setActive(bool active);
	void setType_PlayerBullet();
	void setType_EnemyBullet();

	//Getter
	bool isPlayer();
	bool isEnemy();
	bool isStaticOBJ();
	bool isMovableObj();
	bool isPlayerBullet();
	bool isEnemyBullet();
	bool getActive();
	Vector3 getPos();
	Vector3 getVel();
	Vector3 getScale();
	Vector3 getTarget();
	Vector3 getDirection();
	CSceneNode* getNode();
	GO_TYPE getType();
	std::unordered_map<int, std::string> getNodeList();
	CSceneNode* getSceneGraph();
protected:
	//float
	static float velSpeed;
	float rotateAngle;

	//bool
	bool active;

	//Class or Struct Variables
	Vector3 pos;
	Vector3 vel;
	Vector3 scale;
	Vector3 target;
	Vector3 direction;
	CharAnimation* animation;
	CSceneNode* m_cSceneGraph;
	GO_TYPE type;

	//Map
	std::unordered_map<int, std::string> nodeList;
};

