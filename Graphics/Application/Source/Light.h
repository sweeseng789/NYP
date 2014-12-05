#ifndef SCENELIGHT_H
#define SCENELIGHT_H
#include "Mesh.h"
#include "Camera.h"
#include "Camera2.h"

#include "Scene.h"
//#include "Camera.h"
#include "Mesh.h"
#include"MatrixStack.h"

struct Light
{
	Position position;
	Color color;
	float power;
	float kC, kL, kQ;
	//to do: add a constructor
};

#endif