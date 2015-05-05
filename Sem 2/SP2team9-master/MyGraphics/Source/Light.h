/******************************************************************************/
/*!
\file	Light.h
\author Princeton Chew
\par	email: 141991A@mymail.nyp.edu.sg
\brief
Struct Light
*/
/******************************************************************************/
#ifndef LIGHT_H
#define LIGHT_H

#include "Vertex.h"
/******************************************************************************/
/*!
	Struct hitBox:
\brief
Defines the color, position , power.
*/
/******************************************************************************/
struct Light
{

	Position position;
	Color color;
	float power;
	float kC, kL, kQ;

	Light()
	{
	}

	enum LIGHT_TYPE
	{
		LIGHT_POINT = 0,
		LIGHT_DIRECTIONAL,
		LIGHT_SPOT,
	};
	LIGHT_TYPE type;

	Vector3 spotDirection;
	float cosCutoff;
	float cosInner;
	float exponent;
};



#endif LIGHT_H