#ifndef LIGHT_H
#define LIGHT_H

#include "Mesh.h"
#include "Camera2.h"
#include "Light.h"
#include "Scene.h"

#include "Mesh.h"
#include"MatrixStack.h"
#include "Utility.h"

/******************************************************************************/
/*!
		Class SceneLight:
\brief	Provides methods to create variables and functions to use for modelling
*/
/******************************************************************************/

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
		GEO_REALPIKACHUSPHERE,
		GEO_BACKSTRIP,
		GEO_TAILBROWN,
		GEO_TAILYELLOW,

		GEO_POKEBALLRED,
		GEO_POKEBALLBLACK,
		GEO_POKEBALLBLACK2,
		GEO_POKEBALLWHITE,
		GEO_POKEBALLWHITE2,

		GEO_TESTING,
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

		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_NUMLIGHTS,

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
	void PikachuEyes();
	void PikachuNose();
	void PikachuMouth();

	void PikachuBody(); //Finally

	void PikachuLeftHands();
	void PikachuRightHands();

	void PikachuLeftFeet();
	void PikachuRightFeet();

	void PikachuBackstrip();

	void PikachuTail();

	void RenderPikachu();

	void PokeBallTop();
	void PokeballBottom();

	void RenderPokeball();

	void debugPrint();
private:

	void RenderMesh(Mesh *mesh, bool enableLight);
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	float rotateLeftFeet;
	float rotateRightFeet;
	float rotateLefthand;
	float rotateMars;
	float rotateJupiter;	
	float rotateTail;

	float speed;
	float angle;
	Camera2 camera;

	Vector3 charPosition;
	Vector3 charDirection; //might be useful i think

	Mtx44 doingSomething;

	Vector3 PokeballPosition;
	Light light[1];

	MS modelStack, viewStack, projectionStack;
};

#endif