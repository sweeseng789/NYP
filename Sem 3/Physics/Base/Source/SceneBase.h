#ifndef SCENE_BASE_H
#define SCENE_BASE_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "GameObject.h"
#include <vector>

class SceneBase : public Scene
{
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHTENABLED,
		U_NUMLIGHTS,
		U_LIGHT0_TYPE,
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};
public:
	enum GEOMETRY_TYPE
	{
		Spaceship,
		Spaceship_Thurster,
		SpaceShip_Thurster_back,
		Laser,
		Enemy_Laser,
		Asteroid_Sprite,
		Explosion_Asteroid,
		Bomb,
		Background,
		black_background,
		HUD,
		Enemy,
		heart,
		Missile,
		StartMenu,
		StartTrue,
		ExitTrue,
		ControlTrue,
		GameoverScreen,
		WinScreen,
		ShowControl,
		PowerUp_Ironman,
		Boss,
		Boss_Shield,
		Power_Bar,
		GEO_PLAYER1_TURN,
		GEO_PLAYER2_TURN,
		GEO_POWERBAR_LINE,
		GEO_AXES,
		GEO_TEXT,
		GEO_BALL,
		GEO_BALL2,
		GEO_BALL3,
		GEO_BALL4,
		GEO_BALL5,
		GEO_BALL6,
		GEO_BALL7,
		GEO_BALL8,
		GEO_BALL9,
		GEO_BALL10,
		GEO_BALL11,
		GEO_BALL12,
		GEO_BALL13,
		GEO_BALL14,
		GEO_BALL15,
		GEO_BALL16,
		GEO_CUBE,
		GEO_CUBE2,
		GEO_LINE,
		NUM_GEOMETRY,
	};
public:
	SceneBase();
	~SceneBase();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderGO(GameObject *go);

	GameObject* FetchGO();
protected:
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	Camera camera;

	MS modelStack;
	MS viewStack;
	MS projectionStack;

	Light lights[1];

	bool bLightEnabled;

	float fps;
};

#endif