/******************************************************************************/
/*!
\file	MeshBuilder.h
\author Ong Swee Seng, Lazarus Tan , Princeton Chew , Adela Quek
\par	email: 142128G@mymail.nyp.edu.sg
\brief
Mesh Builder class
*/
/******************************************************************************/
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
	static Mesh* GenerateAxes(const std::string &meshName,Color color, float lengthX, float lengthY, float lengthZ);
	static Mesh* GenerateQuad(const std::string &meshName,Color color, float lengthX, float lengthY);
	static Mesh* GenerateCube(const std::string &meshName,Color color, float length);

	static Mesh* GenerateTopPart(const std::string &meshName,Color color,unsigned numSlices, float radius);
	static Mesh* GenerateBtmPart(const std::string &meshName,Color color,unsigned numSlices, float radius);

	static Mesh* GenerateCircle(const std::string &meshName,Color color,unsigned numSlices, float radius);

	static Mesh* GenerateRing(const std::string &meshName,Color color,unsigned numSlices, float outerR, float innerR);

	static Mesh* GenerateSphere(const std::string &meshName,Color color,unsigned numStack, unsigned numSlice, float radius);

	static Mesh* GenerateCylinder(const std::string &meshName, Color color, unsigned numStack, unsigned numSlice, float radius, float height);

	static Mesh* GenerateHemiSphere(const std::string &meshName,Color color,unsigned numStack, unsigned numSlices, float radius);

	static Mesh* GenerateCone(const std::string &meshName, Color color, unsigned numStack, unsigned numSlice, float radius, float height);

	static Mesh* GenerateTorus(const std::string &meshName, Color color, float ringRadius, float distRadius);

	static Mesh* GenerateMask(const std::string &meshName, Color color, float ringRadius, float distRadius);

	static Mesh* GenerateOBJ(const std::string &meshName, const std::string &file_path);

	static Mesh* MeshBuilder::GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol);
};

#endif