#ifndef VERTEX_H
#define VERTEX_H
#include "Vector3.h"

/****************************************************************************/
/*!
\file	Vertex.h
\author Ong Swee Seng
\brief Vertex.h is used to set the color, position and vertex of primitive shapes
*/
/****************************************************************************/

/******************************************************************************/
/*!
		Class Vertex:
\brief	Provides methods to set the color, position and vertex of primitive shapes
*/
/******************************************************************************/


/******************************************************************************/
/*!
\brief
Used to keep track of the position of the parameters 

\param x - X coordinate
\param y - Y coordinate
\param z - Z coordinate
*/
/******************************************************************************/
struct Position
{
	float x, y, z;
	Position(float x = 0, float y = 0, float z = 0) {Set(x, y, z);}
	void Set(float x, float y, float z) {this->x = x; this->y = y; this->z = z;}
};


/******************************************************************************/
/*!
\brief
Used to keep color the primitive shapes

\param r - value of red
\param g - value of green
\param b - value of blue
*/
/******************************************************************************/
struct Color
{
	float r, g, b;
	Color(float r = 1, float g = 1, float b = 1) {Set(r, g, b);}
	void Set(float r, float g, float b) {this->r = r; this->g = g; this->b = b;}
};

/******************************************************************************/
/*!
\brief
Used as a intermediate to access the color, position and normal values
*/
/******************************************************************************/
struct Vertex 
{
	Position pos;
	Color color;
	Vector3 normal;
};

#endif