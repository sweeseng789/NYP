#ifndef MESH_BUILDER_H
#define MESH_BUILDER_H

#include "Mesh.h"
#include "Vertex.h"

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
	static Mesh* GenerateCube(const std::string &meshName, Color color, float length = 1.f);
	static Mesh* GenerateCircle(const std::string &meshname, Color color, unsigned numSlice, float radius);
	static Mesh* GenerateRing(const std::string &meshname, Color color, unsigned numSlice, float outerR, float innerR);
	static Mesh* MeshBuilder::GenerateSphere(const std::string &meshName, Color color,unsigned numStack, unsigned numSlice, float radius);
};

#endif