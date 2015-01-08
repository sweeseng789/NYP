#ifndef SCENELIGHT_H
#define SCENELIGHT_H
#include "Mesh.h"
#include "Camera.h"
#include "Camera2.h"

#include "Scene.h"
//#include "Camera.h"
#include "Mesh.h"
#include"MatrixStack.h"

/******************************************************************************/
/*!
		Class Light:
\brief	Provides methods to setup the light source
*/
/******************************************************************************/

struct Light
{
	Position position;
	Color color;
	float power;
	float kC, kL, kQ;
	//to do: add a constructor

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

#endif