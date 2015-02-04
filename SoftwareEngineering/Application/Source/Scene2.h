#ifndef SCENE_2_H
#define SCENE_2_H

#include "Scene.h"
#include "Mtx44.h"

class Scene2 : public Scene
{
public:
	Scene2();
	~Scene2();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	enum GEOMETRY_TYPE
	{
		TRIANGLE = 0,
		STAR,
		SQUARE,
		OCTAGON,
		NUM_GEOMETRY,
	};

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_TOTAL,
	};

	unsigned m_parameters[U_TOTAL];

	float rotateAngle;
	float translateX;
	float scaleAll;
	float rotateAngle2;
	float randomiser;

private:
	unsigned m_vertexArrayID;
	unsigned m_vertexBuffer[NUM_GEOMETRY];
	unsigned m_colorBuffer[NUM_GEOMETRY];
	unsigned m_programID;
};

#endif