#ifndef LIGHT_H
#define LIGHT_H

#include "Mesh.h"
//#include "Camera.h"
#include "Camera2.h"
#include "Light.h"
#include "Scene.h"

#include "Mesh.h"
#include"MatrixStack.h"
#include "Utility.h"

class SceneLight : public Scene
{

	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_CUBE,
		GEO_CUBE1,
		GEO_CUBE2,
		GEO_SPHERE,
		GEO_RING,
		GEO_LIGHTBALL,
		GEO_CYLINDER,
		GEO_CONEYellow,
		GEO_CONEBlack,
		GEO_PIKACHUEYES,
		GOE_PIKACHUEYESWHITE,
		GEO_PIKACHUHEADPARTS,
		GEO_PIKACHUHEADPARTS3,
		GEO_PIKACHUNOSE,
		GEO_PIKACHUBROWN,
		GEO_PIKACHUSPHEREYELLOW,
		GEO_BALL1,
		GEO_BALL2,
		GEO_BALL3,
		GEO_BALL4,
		GEO_BALL5,
		GEO_BALL6,
		GEO_BALL7,
		GEO_BALL8,
		GEO_BALL9,
		NUM_GEOMETRY,
	};

	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHTENABLED,
		U_TOTAL,
	};
public:
	SceneLight();
	~SceneLight();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderBody();
	void RenderLimb();
	void RenderRobot();

	void PikachuLeftEars();
	void PikachuRightEars();
	void PikachuHead();
	void PikachuRightEyes();
	void PikachuNose();
	void PikachuMouth();
private:

	void RenderMesh(Mesh *mesh, bool enableLight);
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	float rotateAngle;
	float rotateSun;
	float rotateEarth;
	float rotateMars;
	float rotateJupiter;
	float rotateSaturn;
	Camera2 camera;

	Light light[1];

	MS modelStack, viewStack, projectionStack;
};

#endif