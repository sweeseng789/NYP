#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"

/****************************************************************************/
/*!
\file SceneLight.cpp
\author Ong Swee Seng
\brief MeshBuilder.h is used to set the function prototype for different shapes
*/
/****************************************************************************/


/******************************************************************************/
/*!
		Class MeshBuilder:
\brief	Provides methods to generate mesh of different shapes
*/
/******************************************************************************/
class MeshBuilder
{
public:
	static Mesh* GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string &meshName, Color color ,float length);
	static Mesh* GenerateTriangle(const std::string &meshName, Color color ,float length);
	static Mesh* GenerateCube(const std::string &meshName, Color color, float length = 1.f);
	static Mesh* GenerateCircle(const std::string &meshname, Color color, unsigned numSlice, float radius);
	static Mesh* GenerateRing(const std::string &meshname, Color color, unsigned numSlice, float outerR, float innerR);
	static Mesh* GenerateSphere(const std::string &meshName, Color color,unsigned numStack, unsigned numSlice, float radius);
	static Mesh* GenerateHemisphere(const std::string &meshName, Color color,unsigned numStack, unsigned numSlice, float radius);
	static Mesh* GenerateCone(const std::string &meshname, Color color, unsigned numSlice, float radius, float height);
	static Mesh* GenerateCylinder(const std::string &meshName, Color color, unsigned numStack, unsigned numSlice, unsigned stackHeight, float height, float radius);
};

#endif