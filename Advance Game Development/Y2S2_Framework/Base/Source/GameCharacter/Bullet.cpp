#include "Bullet.h"

const float CBullet::bulletSpeed = 1000.f;
const double CBullet::displaybulletLimit = 0.03;

CBullet::CBullet()
{
	type = PLAYERBULLET;
	scale = Vector3(1, 1, 1);
	displayBulletTimeLimit = 0;
	displayBullet = false;

	m_cSceneGraph = new CSceneNode();
	CModel* newModel = new CModel();
	CTransform* transform = new CTransform();

	newModel->Init(MeshBuilder::GenerateSphere("Player Bullet", Color(1, 1, 1), 18, 36, 1.f), NULL);
	transform->SetScale(scale.x, scale.y, scale.z);
	m_cSceneGraph->SetNode(transform, newModel);
}


CBullet::~CBullet()
{
}

void CBullet::Update(const double &dt)
{
	timeLimit -= dt;
	pos += bulletSpeed * direction * dt;

	if (displayBulletTimeLimit < displaybulletLimit)
	{
		displayBulletTimeLimit += dt;
	}
	else
	{
		displayBullet = true;
	}

	if (timeLimit < 0)
	{
		active = false;
	}
}

void CBullet::setTimeLimit(double timeLimit)
{
	this->timeLimit = timeLimit;
}

void CBullet::setDisplayBullet(bool displayBullet)
{
	this->displayBullet = displayBullet;
	displayBulletTimeLimit = 0.0;
}

bool CBullet::getDisplayBullet()
{
	return displayBullet;
}