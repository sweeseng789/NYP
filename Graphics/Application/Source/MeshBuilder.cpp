#include "MeshBuilder.h"
#include <GL\glew.h>
#include <vector>
#include "Vertex.h"
#include "MyMath.h"
/****************************************************************************/
/*!
\file MeshBuilder.cpp
\author Ong Swee Seng
\brief MeshBuilder.cpp is used to create the VBO and IBO of all primitive shapes
*/
/****************************************************************************/

/******************************************************************************/
/*!
\brief
Generate the vertices of a reference Axes; Use red for x-axis, green for y-axis, blue for z-axis
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - x-axis should start at -lengthX / 2 and end at lengthX / 2
\param lengthY - y-axis should start at -lengthY / 2 and end at lengthY / 2
\param lengthZ - z-axis should start at -lengthZ / 2 and end at lengthZ / 2

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateAxes(const std::string &meshName, float lengthX, float lengthY, float lengthZ)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	v.pos.Set(-1000, 0, 0);
	v.color.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(1000, 0, 0);
	v.color.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, -1000, 0);
	v.color.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 1000, 0);
	v.color.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, -1000);
	v.color.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);
	v.pos.Set(0, 0, 1000);
	v.color.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	std::vector<GLuint> index_buffer_data;
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(5);

	Mesh *mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_LINES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a quad; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of quad
\param lengthY - height of quad

\return Pointer to mesh storing VBO/IBO of quad
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateQuad(const std::string &meshName, Color color, float length)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	v.pos.Set(-0.5f,-0.5f,-0);
	v.color = color;
	v.normal.Set(0, 0 ,1);
	v.texCoord.Set(0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f,-0.5f,-0);
	v.color = color;
	v.normal.Set(0, 0 ,1);
	v.texCoord.Set(1, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.5f,-0);
	v.color = color;
	v.normal.Set(0, 0 ,1);
	v.texCoord.Set(1, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f, 0.5f,-0);
	v.color = color;
	v.normal.Set(0, 0 ,1);
	v.texCoord.Set(0, 1);
	vertex_buffer_data.push_back(v);
	
	std::vector<GLuint> index_buffer_data;
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(0);

	index_buffer_data.push_back(2);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(1);


	Mesh *mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = 36;
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a triangle;
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param color - set color
\param length - set the length of triangle

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateTriangle(const std::string &meshName, Color color, float length)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	v.pos.Set(-0.5f,-0.5f,-0);
	v.color = color;
	v.normal.Set(0, 0 ,1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f,-0.5f,-0);
	v.color = color;
	v.normal.Set(0, 0 ,1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.5f,-0);
	v.color = color;
	v.normal.Set(0, 0 ,1);
	vertex_buffer_data.push_back(v);
	
	std::vector<GLuint> index_buffer_data;

	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(0);

	index_buffer_data.push_back(0);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(1);
	
	Mesh *mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = 36;
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a cube; Use random color for each vertex
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param lengthX - width of cube
\param lengthY - height of cube
\param lengthZ - depth of cube

\return Pointer to mesh storing VBO/IBO of cube
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCube(const std::string &meshName, Color color, float length)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;

	v.pos.Set(-0.5f,-0.5f,-0.5f);//back start
	v.color = color;
	//v.normal.Set(0.707, 0.707, 0.707);
	v.normal.Set(0, 0, -1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f,-0.5f,-0.5f);
	v.color = color;
	//v.normal.Set(0.707, 0.707, 0.707);
	v.normal.Set(0, 0, -1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.5f,-0.5f);
	v.color = color;
	//v.normal.Set(0.707, 0.707, 0.707);
	v.normal.Set(0, 0, -1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f, 0.5f,-0.5f); //back end
	v.color = color;
	//v.normal.Set(0.707, 0.707, 0.707);
	v.normal.Set(0, 0, -1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f,-0.5f, 0.5f);//front start
	v.color = color;
	//v.normal.Set(0.707, 0.707, 0.707);
	v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f,-0.5f, 0.5f);
	v.color = color;
	//v.normal.Set(0.707, 0.707, 0.707);
	v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.5f, 0.5f);
	v.color = color;
	//v.normal.Set(0.707, 0.707, 0.707);
	v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f, 0.5f, 0.5f);//front end
	v.color = color;
	//v.normal.Set(0.707, 0.707, 0.707);
	v.normal.Set(0, 0, 1);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.5f, -0.5f);//right start
	v.color = color;
	v.normal.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.5f, 0.5f);
	v.color = color;
	v.normal.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, -0.5f, 0.5f);
	v.color = color;
	v.normal.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, -0.5f, -0.5f);//right end
	v.color = color;
	v.normal.Set(1, 0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, -0.5f, -0.5f);//bottom start
	v.color = color;
	v.normal.Set(0, -1, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f, -0.5f, -0.5f);
	v.color = color;
	v.normal.Set(0, -1, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f, -0.5f, 0.5f);
	v.color = color;
	v.normal.Set(0, -1, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, -0.5f, 0.5f);//bottom end
	v.color = color;
	v.normal.Set(0, -1, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.5f, 0.5f);//top statr
	v.color = color;
	v.normal.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(0.5f, 0.5f, -0.5f);
	v.color = color;
	v.normal.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f, 0.5f, -0.5f);
	v.color = color;
	v.normal.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f, 0.5f, 0.5f);//topend
	v.color = color;
	v.normal.Set(0, 1, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f, 0.5f, 0.5f);//left start
	v.color = color;
	v.normal.Set(-1, 0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f, 0.5f, -0.5f);
	v.color = color;
	v.normal.Set(-1, 0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f, -0.5f, -0.5f);
	v.color = color;
	v.normal.Set(-1, 0, 0);
	vertex_buffer_data.push_back(v);

	v.pos.Set(-0.5f, -0.5f, 0.5f);
	v.color = color;
	v.normal.Set(-1, 0, 0);
	vertex_buffer_data.push_back(v);

	std::vector<GLuint> index_buffer_data;
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(6);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(2);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(3);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(7);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(1);
	index_buffer_data.push_back(5);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(4);
	index_buffer_data.push_back(0);
	index_buffer_data.push_back(5);
	
	Mesh *mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = 36;
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a Circle;
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param color - set color
\param numSlice - set the Index buffer data
\param radius - set the radius of triangle

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCircle(const std::string &meshName, Color color, unsigned numSlice, float radius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	float degreePerSlice = 360.0f / numSlice;
	
	for(unsigned slice = 0; slice < numSlice; ++slice)
	{
		float theta = slice * degreePerSlice;

		//v0
		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), 0, radius * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal.Set( 0, 1, 0);
		vertex_buffer_data.push_back(v);

		//v1
		v.pos.Set(0, 0, 0);
		v.color = color;
		v.normal.Set( 0, 1, 0);
		vertex_buffer_data.push_back(v);
		float theta2 = (slice + 1) * degreePerSlice;

		//v2
		v.pos.Set(radius * cos(Math::DegreeToRadian(theta2)), 0, radius * sin(Math::DegreeToRadian(theta2)));
		v.color = color;
		v.normal.Set( 0, 1, 0);
		vertex_buffer_data.push_back(v);
	}

	for (unsigned slice = 0; slice< numSlice; ++slice)
	{
		index_buffer_data.push_back(slice * 3 + 0);
		index_buffer_data.push_back(slice * 3 + 1);
		index_buffer_data.push_back(slice * 3 + 2);

		index_buffer_data.push_back(slice * 3 + 2);
		index_buffer_data.push_back(slice * 3 + 1);
		index_buffer_data.push_back(slice * 3 + 0);
	}

	Mesh *mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}


/******************************************************************************/
/*!
\brief
Generate the vertices of a Ring;
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param color - set color
\param numSlice - set the Index buffer data
\param outerR - set the radius of outer cicrle
\param innerR - set the radius of the inner cicrcle

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateRing(const std::string &meshName, Color color, unsigned numSlice, float outerR, float innerR)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	float degreePerSlice = 360.f / numSlice;
	for(unsigned slice = 0; slice < numSlice; ++slice) {

		float theta = slice * degreePerSlice;
/*v0*/	v.pos.Set(outerR * cos(Math::DegreeToRadian(theta)), 0, outerR * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal.Set(0 ,1, 0);
		vertex_buffer_data.push_back(v);

/*v1*/	v.pos.Set(innerR * cos(Math::DegreeToRadian(theta)), 0, innerR * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal.Set(0 ,1, 0);
		vertex_buffer_data.push_back(v);

		float theta2 = (slice + 1) * degreePerSlice;
/*v2*/	v.pos.Set(outerR * cos(Math::DegreeToRadian(theta2)), 0, outerR * sin(Math::DegreeToRadian(theta2)));
		v.color = color;
		v.normal.Set(0 ,1, 0);
		vertex_buffer_data.push_back(v);

/*v3*/	v.pos.Set(innerR * cos(Math::DegreeToRadian(theta2)), 0, innerR * sin(Math::DegreeToRadian(theta2)));
		v.color = color;
		v.normal.Set(0 ,1, 0);
		vertex_buffer_data.push_back(v);
	}
	for(unsigned slice = 0; slice < numSlice; ++slice) {
		index_buffer_data.push_back(slice * 4 + 0);
		index_buffer_data.push_back(slice * 4 + 1);
		index_buffer_data.push_back(slice * 4 + 2);
		
		index_buffer_data.push_back(slice * 4 + 3);
		index_buffer_data.push_back(slice * 4 + 2);
		index_buffer_data.push_back(slice * 4 + 1);


		//bOTTOM
		index_buffer_data.push_back(slice * 4 + 2);
		index_buffer_data.push_back(slice * 4 + 1);
		index_buffer_data.push_back(slice * 4 + 0);

		index_buffer_data.push_back(slice * 4 + 1);
		index_buffer_data.push_back(slice * 4 + 2);
		index_buffer_data.push_back(slice * 4 + 3);

	}
	Mesh *mesh = new Mesh(meshName);
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	return mesh;
}




/******************************************************************************/
/*!
\brief
Calculate the x coordinate of the sphere then return the value back to GenerateSphere

\param theta - value of theta
\param phi - value of phi

\return x coordinates back to GenerateSphere
*/
/******************************************************************************/
float sphereX(float phi, float theta){
	return cos(Math::DegreeToRadian(phi)) * cos(Math::DegreeToRadian(theta));
}

/******************************************************************************/
/*!
\brief
Calculate the y coordinate of the sphere then return the value back to GenerateSphere

\param theta - value of theta
\param phi - value of phi

\return y coordinates back to GenerateSphere
*/
/******************************************************************************/
float sphereY(float phi, float theta){
	return sin(Math::DegreeToRadian(phi));
}

/******************************************************************************/
/*!
\brief
Calculate the z coordinate of the sphere then return the value back to GenerateSphere

\param theta - value of theta
\param phi - value of phi

\return z coordinates back to GenerateSphere
*/
/******************************************************************************/
float sphereZ(float phi, float theta){
	return cos(Math::DegreeToRadian(phi)) * sin(Math::DegreeToRadian(theta));
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a Sphere;
Then generate the VBO/IBO and store them in Mesh object
Functions called: sphereX, sphereY, sphereZ

\param meshName - name of mesh
\param color - set color
\param numStack - set the Index buffer data
\param numSlice - set the Vertex buffer data
\param radius - set the length of the sphere

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateSphere(const std::string &meshName, Color color, unsigned numStack, unsigned numSlice, float radius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	float degreePerStack = 180.0f / numStack;
	float degreePerSlice = 360.0f / numSlice;

	for(unsigned stack = 0; stack < numStack + 1; ++stack)
	{
		float phi = -90 + stack * degreePerStack;

		for(unsigned slice = 0; slice < numSlice + 1; ++slice)
		{
			float theta = slice * degreePerSlice;

			v.pos.Set(radius * sphereX(phi, theta), radius * sphereY(phi, theta), radius * sphereZ(phi, theta));
			v.color = color;
			v.normal.Set(sphereX(phi, theta), sphereY(phi, theta), sphereZ(phi, theta));
			vertex_buffer_data.push_back(v);
		}
	}

	for (unsigned stack = 0; stack < numStack; ++stack)
	{
		for (unsigned slice = 0; slice < numSlice + 1; ++ slice)
		{
			index_buffer_data.push_back(stack * (numSlice + 1) +slice);

			index_buffer_data.push_back((stack + 1) * (numSlice + 1) + slice);
		}
	}

	Mesh *mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Generate the vertices of a Hemisphere;
Then generate the VBO/IBO and store them in Mesh object
Functions called: sphereX, sphereY, sphereZ

\param meshName - name of mesh
\param color - set color
\param numStack - set the Index buffer data
\param numSlice - set the Vertex buffer data
\param radius - set the length of the sphere


\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateHemisphere(const std::string &meshName, Color color, unsigned numStack, unsigned numSlice, float radius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	float degreePerStack = 180.0f / numStack;
	float degreePerSlice = 360.0f / numSlice;

	for(unsigned stack = 0; stack < numStack + 1; ++stack)
	{
		float phi = stack * degreePerStack;

		for(unsigned slice = 0; slice < numSlice + 1; ++slice)
		{
			float theta = slice * degreePerSlice;

			v.pos.Set(radius * sphereX(phi, theta), radius * sphereY(phi, theta), radius * sphereZ(phi, theta));
			v.color = color;
			v.normal.Set(sphereX(phi, theta), sphereY(phi, theta), sphereZ(phi, theta));
			vertex_buffer_data.push_back(v);
		}
	}

	for (unsigned stack = 0; stack < numStack; ++stack)
	{
		for (unsigned slice = 0; slice < numSlice + 1; ++ slice)
		{
			index_buffer_data.push_back(stack * (numSlice + 1) +slice);

			index_buffer_data.push_back((stack + 1) * (numSlice + 1) + slice);

			index_buffer_data.push_back((stack + 1) * (numSlice + 1) + slice);

			index_buffer_data.push_back(stack * (numSlice + 1) + slice);
		}
	}

	Mesh *mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}


/******************************************************************************/
/*!
\brief
Generate the vertices of a Cone;
Then generate the VBO/IBO and store them in Mesh object

\param meshName - name of mesh
\param color - set color
\param numSlice - set the Index buffer data
\param radius - set the radius of triangle

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCone(const std::string &meshName, Color color, unsigned numSlice, float radius, float height)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	float degreePerSlice = 360.0f / numSlice;
	
	for(unsigned slice = 0; slice < numSlice; ++slice)
	{
		float theta = slice * degreePerSlice;

		//v0
		v.pos.Set(radius * cos(Math::DegreeToRadian(theta)), 0, radius * sin(Math::DegreeToRadian(theta)));
		v.color = color;
		v.normal.Set(0, 1 , 0);
		vertex_buffer_data.push_back(v);

		//v1
		v.pos.Set(0, 20, 0);
		v.color = color;
		v.normal.Set(0, 1 , 0);
		vertex_buffer_data.push_back(v);


		float theta2 = (slice + 1) * degreePerSlice;


		//v2
		v.pos.Set(radius * cos(Math::DegreeToRadian(theta2)), 0, radius * sin(Math::DegreeToRadian(theta2)));
		v.color = color;
		v.normal.Set(0, 1 , 0);
		vertex_buffer_data.push_back(v);
	}

	for (unsigned slice = 0; slice< numSlice; ++slice)
	{
		index_buffer_data.push_back(slice * 3 + 0);
		index_buffer_data.push_back(slice * 3 + 1);
		index_buffer_data.push_back(slice * 3 + 2);


	}

	Mesh *mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

/******************************************************************************/
/*!
\brief
Calculate calculate radian of theta for the x axis before returning it to GenerateCylinder

\param theta - value of theta

\return x coordinates back to GenerateCylinder
*/
/******************************************************************************/
float CylinderX(float theta){
	return cos(Math::DegreeToRadian(theta));
}

/******************************************************************************/
/*!
\brief
Calculate calculate radian of theta for the z axis before returning it to GenerateCylinder

\param theta - value of theta

\return z coordinates back to GenerateCylinder
*/
/******************************************************************************/
float CylinderZ(float theta){
	return sin(Math::DegreeToRadian(theta));
}


/******************************************************************************/
/*!
\brief
Generate the vertices of a Cylinder;
Then generate the VBO/IBO and store them in Mesh object
Functions called: CylinderX, CylinderZ

\param meshName - name of mesh
\param color - set color
\param numStack - set the Index buffer data
\param numSlice - set the Vertex buffer data
\param stackHeight - set the y axis
\param height - set the height of the cylinder
\param radius - set the length of the cylinder

\return Pointer to mesh storing VBO/IBO of reference axes
*/
/******************************************************************************/
Mesh* MeshBuilder::GenerateCylinder(const std::string &meshName, Color color, unsigned numStack, unsigned numSlice, unsigned stackHeight, float height, float radius)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float degreePerSlice = 360.0f / numSlice;

	

	for(unsigned stack = 0; stack < numStack + 1; ++stack)
	{


    	for(unsigned slice = 0; slice < numSlice + 1; ++slice)
		{
			float theta = slice * degreePerSlice;

			v.pos.Set(radius * CylinderX(theta), -height /  stack * stackHeight, radius * CylinderZ (theta));
			v.color = color;
			v.normal.Set(CylinderX( theta), 0, CylinderZ(theta));
			vertex_buffer_data.push_back(v);
		}
	}


	for (unsigned stack = 0; stack < numStack; ++stack)
	{
		for (unsigned slice = 0; slice < numSlice + 1; ++ slice)
		{
			index_buffer_data.push_back(stack * (numSlice + 1) +slice);

			index_buffer_data.push_back((stack + 1) * (numSlice + 1) + slice);
		}
	}


	Mesh *mesh = new Mesh(meshName);
	
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLE_STRIP;

	return mesh;
}

Mesh* MeshBuilder::GenerateOBJ(const std::string &meshName, const std::string &file_path) 
{
	//Read vertices, texcoords & normals from OBJ
	std::vector<Position> vertices;
	std::vector<TexCoord> uvs;
	std::vector<Vector3> normals;
	bool success = LoadOBJ(file_path.c_str(), vertices, uvs, normals);
	if(!success)
		return NULL;
	//Index the vertices, texcoords & normals properly
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;
	IndexVBO(vertices, uvs, normals, index_buffer_data, vertex_buffer_data);

	//Create the mesh and call glBindBuffer, glBufferData
	Mesh *mesh = new Mesh(meshName);

	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);

	//Use triangle list and remember to set index size
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;

	return mesh;
}

Mesh* MeshBuilder::GenerateText(const std::string &meshName, unsigned numRow, unsigned numCol)
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;

	float width = 1.f / numCol;
	float height = 1.f / numRow;
	int offset = 0;
	for(unsigned j = 0; j < numRow; ++j)
	{
		for(unsigned i = 0; i < numCol; ++i)
		{
			//Task: Add 4 vertices into vertex_buffer_data
			float u1 = j * width;
			float v1 = 1.f - height - i * height;

			v.pos.Set(-0.5f,-0.5f,-0);
			v.texCoord.Set(u1, v1);
			vertex_buffer_data.push_back(v);

			v.pos.Set(0.5f,-0.5f,-0);
			v.texCoord.Set(u1 + width, v1);
			vertex_buffer_data.push_back(v);

			v.pos.Set(0.5f, 0.5f,-0);
			v.texCoord.Set(u1 + width, v1 + height);
			vertex_buffer_data.push_back(v);

			v.pos.Set(-0.5f, 0.5f,-0);
			v.texCoord.Set(u1, v1 + height);
			vertex_buffer_data.push_back(v);

			//Task: Add 6 indices into index_buffer_data
			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 1);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 0);
			index_buffer_data.push_back(offset + 2);
			index_buffer_data.push_back(offset + 3);
			offset += 4;
			//012 023
		}
		
		Mesh *mesh = new Mesh(meshName);
	
		glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() * sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size() * sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
		mesh->indexSize = index_buffer_data.size();
		mesh->mode = Mesh::DRAW_TRIANGLES;
		return mesh;
	}
}