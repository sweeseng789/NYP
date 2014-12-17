#ifndef SCENELIGHT_H
#define SCENELIGHT_H
#include "Mesh.h"
#include "Camera.h"
#include "Camera2.h"

#include "Scene.h"
//#include "Camera.h"
#include "Mesh.h"
#include"MatrixStack.h"

/****************************************************************************/
/*!
\file Light.h
\author Ong Swee Seng
\brief Light.h is used to setup the light source
*/
/****************************************************************************/

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
};

#endif