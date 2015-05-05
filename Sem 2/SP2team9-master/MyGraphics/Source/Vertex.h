/******************************************************************************/
/*!
\file	Vertex.h
\author Ong Swee Seng, Lazarus Tan , Princeton Chew , Adela Quek
\par	email: 142128G@mymail.nyp.edu.sg
\brief
Struct Position,Color,TexCoord
*/
/******************************************************************************/
#ifndef _VERTEX_H
#define _VERTEX_H

#include "Vector3.h"
/******************************************************************************/
/*!
		Struct position:
\brief	Provides position of vectors
*/
/******************************************************************************/
struct Position
{
	float x, y, z;
	Position(float x = 0, float y = 0, float z = 0) {Set(x, y, z);}
	void Set(float x, float y, float z) {this->x = x; this->y = y; this->z =z; }
};
/******************************************************************************/
/*!
		Struct Color:
\brief	Provides Color numbers (eg: 255,255,255)
*/
/******************************************************************************/
struct Color
{
	float r, g, b;
	Color(float r = 1, float g = 1, float b = 1) {Set(r, g, b); }
	void Set(float r, float g, float b) {this->r = r; this->g = g; this->b = b;}
};
/******************************************************************************/
/*!
		Struct TexCoord:
\brief	Provides coordinates for textures
*/
/******************************************************************************/
struct TexCoord
{
	float u, v;
	TexCoord(float u = 0, float v = 0) {Set(u, v);}
	void Set(float u, float v) {this->u = u; this->v = v;}
};
/******************************************************************************/
/*!
		Struct Vertex:
\brief	Sets name for calling 
*/
/******************************************************************************/
struct Vertex
{
	Position pos;
	Color color;
	Vector3 normal;
	TexCoord texCoord;
};

#endif _VERTEX_H