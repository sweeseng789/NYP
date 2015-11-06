#pragma once

#include "Vector3.h"
#include "GL\glew.h"
#include "..\Mesh.h"
#include "Mtx44.h"
#include "../LoadTGA.h"

class CModel
{
private:
	Vector3 vTopLeft, vBottomRight;
	float red, green, blue;
	
	// Handle to the Mesh
	Mesh* m_cModelMesh;

public:
	CModel(void);
	~CModel(void);

	void Init(Mesh* m_cModelMesh, const char * texturePath);
	void Draw(bool m_bLight = false);
	void SetColor(const float red, const float green, const float blue);
	void setMesh(Mesh* m_cModelMesh);
	Mesh* getMesh();

	// Get the top left of the bounding box of the instance
	Vector3 GetTopLeft(void);
	// Get the bottomright of the bounding box of the instance
	Vector3 GetBottomRight(void);

};
