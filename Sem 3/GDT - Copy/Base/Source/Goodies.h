#pragma once

#include "Mesh.h"
#include "Vector3.h"
class CGoodies
{
public:
	CGoodies(void);
	~CGoodies(void);

protected:
	int pos_x;
	int pos_y;

public:
	//Store texture for goodies
	Mesh* theMesh;

	
	int GetPos_x(void);
	int GetPos_y(void);
	void SetPos(const int x, const int y);

	//Get mesh
	Mesh* getMesh();

	//Set Mesh
	void setMesh(Mesh* theMesh);

	//Set Texture ID
	void SetTextureID(const int TextureID);
};

