#include "Goodies.h"


CGoodies::CGoodies(void)
	: pos_x(0)
	, pos_y(0)
	, theMesh(NULL)
{
}

CGoodies::~CGoodies(void)
{
	if(theMesh != NULL)
	{
		delete theMesh;
		theMesh = NULL;
	}
}

int CGoodies::GetPos_x(void)
{
	return pos_x;
}

int CGoodies::GetPos_y(void)
{
	return pos_y;
}

void CGoodies::SetPos(const int pos_x, const int pos_y)
{
	this->pos_x = pos_x;
	this->pos_y = pos_y;
}

void CGoodies::setMesh(Mesh* theMesh)
{
	this->theMesh = theMesh;
}

Mesh* CGoodies::getMesh()
{
	return theMesh;
}

void CGoodies::SetTextureID(const int TextureID)
{
	if ((this->theMesh != NULL) && (TextureID != 0))
	{
		this->theMesh->textureID = TextureID;
	}
}