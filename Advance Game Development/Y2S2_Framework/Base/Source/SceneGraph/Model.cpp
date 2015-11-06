#include "Model.h"

#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#include <windows.h> // Header File For Windows
#include <gl\gl.h> // Header File For The OpenGL32 Library
#include <gl\glu.h> // Header File For The GLu32 Library

#include <stdio.h>
#include "..\MeshBuilder.h"

CModel::CModel(void)
	: m_cModelMesh(NULL)
{
	vTopLeft = Vector3( 1.0f, 1.0f, 1.0f );
	vBottomRight = Vector3( -1.0f, -1.0f, -1.0f );
	red = 128;
	green = 255;
	blue = 0;
}

CModel::~CModel(void)
{
	if (m_cModelMesh != NULL)
	{
		delete m_cModelMesh;
		m_cModelMesh = NULL;
	}
}

void CModel::Init(Mesh* m_cModelMesh, const char *texturePath)
{
	this->m_cModelMesh = m_cModelMesh;
	this->m_cModelMesh->textureID = LoadTGA(texturePath);
}

void CModel::Draw(bool m_bLight)
{
	if (m_cModelMesh)
		m_cModelMesh->Render();
}

void CModel::SetColor(const float red, const float green, const float blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}

void CModel::setMesh(Mesh* m_cModelMesh)
{
	this->m_cModelMesh = m_cModelMesh;
}

Mesh* CModel::getMesh()
{
	return m_cModelMesh;
}

// Get the top left of the bounding box of the instance
Vector3 CModel::GetTopLeft(void)
{
	return Vector3(vTopLeft.x, vTopLeft.y, vTopLeft.z);
}

// Get the bottomright of the bounding box of the instance
Vector3 CModel::GetBottomRight(void)
{
	return Vector3(vBottomRight.x, vBottomRight.y, vBottomRight.z);
}