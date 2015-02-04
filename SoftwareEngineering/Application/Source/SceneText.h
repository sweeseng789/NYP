#ifndef SCENE_TEXT_H
#define SCENE_TEXT_H

#include "Mesh.h"
//#include "Camera.h"
//#include "Camera2.h"
#include "Camera3.h"
#include "Light.h"
#include "Scene.h"

#include "Mesh.h"
#include"MatrixStack.h"
#include "Utility.h"

class SceneText : public Scene
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

		GEO_MODEL1,
		GEO_MODEL2,
		GEO_MODEL3,
		GEO_MODEL4,
		GEO_MODEL5,
		GEO_MODEL6,
		GEO_MODEL7,

		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,

		GEO_CROSSHAIR,

		GEO_EXIA,
		DoraemonHead,
		DoraemonBell,
		DoraemonBody,
		DoraemonRightHand,
		DoraemonLeftHand,
		DoraemonRightFeet,
		DoraemonLeftFeet,
		DoraemonRoom,
		DoraemonRoomFloor,
		DoaremonRoomWall,
		DoraemonRoomWallWithDoor,
		DoraemonDoor,
		DoraemonLight1,

		GEO_TEXT,
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
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,

		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHTENABLED,

		U_LIGHT1_TYPE,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,
		U_NUMLIGHTS, //in case you missed out practical 7
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,

		U_TEXT_ENABLED,
		U_TEXT_COLOR,

		U_TOTAL,
	};
public:
	SceneText();
	~SceneText();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
private:

	void RenderMesh(Mesh *mesh, bool enableLight);
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];
	
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

	void RenderSkybox();
	void RenderDoraemonRoom();
	int scaleSize;
	float FPS;
	float moving;
	std::string renderFPS;
	unsigned ArialFontArray[256];

	float rotateRightHand;
	float rotateLeftHand;
	float rotateRightFeet;
	float rotateLeftFeet;

	Camera3 camera;

	Light light[8];

	MS modelStack, viewStack, projectionStack;
};

#endif