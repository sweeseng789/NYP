#ifndef SCENE_4_H
#define SCENE_4_H

#include "Scene.h"
#include "Camera.h"
#include "Mesh.h"
#include"MatrixStack.h"

class Scene4 : public Scene
{
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_TOTAL,
	};
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_CUBE,
		GEO_SPHERE,
		GEO_RING,
		GEO_SUN,
		GEO_MERCURY,
		GEO_VENUS,
		GEO_EARTH,
		GEO_EARTH_MOON,
		GEO_MARS,
		GEO_JUPITER,
		GEO_SATURN,
		GEO_SATURN_RING,
		NUM_GEOMETRY,
	};
public:
	Scene4();
	~Scene4();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	float rotateAngle;
	float rotateSun;
	float rotateEarth;
	float rotateMars;
	float rotateJupiter;
	float rotateTail;
	Camera camera;

	MS modelStack, viewStack, projectionStack;
};

#endif