#pragma once
#ifndef SCENE_SANDBOX_H
#define SCENE_SANDBOX_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include <vector>
#include <string>
#include "Collision.h"
#include "Map.h"
#include "Bullet.h"
#include "Hero.h"
#include "Enemy.h"

using std::vector;
using std::cout;
using std::endl;
class SceneSandBox : public Scene
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
		U_LIGHT1_TYPE,
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,

		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE_ENABLED1,
		U_COLOR_TEXTURE,
		U_COLOR_TEXTURE1,

		U_COLOR_FOG,
		U_COLOR_FOG2,
		U_COLOR_FOG3,
		U_START_FOG,
		U_END_FOG,
		U_DENSITY_FOG,
		U_TYPE_FOG,
		U_ENABLE_FOG,

		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_TERRAIN,
		GEO_CROSSHAIR,
		GEO_LIGHTBALL,
		GEO_SPHERE,
		GEO_SPHERE2,
		GEO_SPHERE3,
		GEO_SPHERE4,
		GEO_SPHERE5,
		GEO_SPHERE6,
		GEO_SPHERE7,
		GEO_SPHERE8,
		GEO_SPHERE9,
		GEO_QUAD,
		GEO_CUBE,
		GEO_RING,
		GEO_CONE,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_OBJECT,
		GEO_SKYPLANE,
		GEO_TEXT,
		GEO_SPRITE_ANIMATION,
		GEO_BACKGROUND,
		GEO_TILEGROUND,
		GEO_TILEHERO,
		GEO_TILETREE,
		GEO_TILESTRUCTURE,
		GEO_TILEHERO_FRAME0,
		GEO_TILEHERO_FRAME1,
		GEO_TILEHERO_FRAME2,
		GEO_TILEHERO_FRAME3,
		GEO_HERO_DEFAULT,
		GEO_HERO_SHOOT,
		GEO_HERO_WALK_FRAME01,
		GEO_HERO_WALK_FRAME02,
		GEO_HERO_WALK_FRAME03,
		GEO_HERO_WALK_FRAME04,
		GEO_HERO_WALK_FRAME05,
		GEO_HERO_WALK_FRAME06,
		GEO_HERO_WALK_FRAME07,
		GEO_HERO_WALK_FRAME08,
		GEO_HERO_WALK_FRAME09,
		GEO_HERO_WALK_FRAME10,
		GEO_HERO_JUMP,
		GEO_HERO_LAND,
		GEO_HERO_DEFAULT_INVERSE,
		GEO_HERO_SHOOT_INVERSE,
		GEO_HERO_WALK_FRAME01_INVERSE,
		GEO_HERO_WALK_FRAME02_INVERSE,
		GEO_HERO_WALK_FRAME03_INVERSE,
		GEO_HERO_WALK_FRAME04_INVERSE,
		GEO_HERO_WALK_FRAME05_INVERSE,
		GEO_HERO_WALK_FRAME06_INVERSE,
		GEO_HERO_WALK_FRAME07_INVERSE,
		GEO_HERO_WALK_FRAME08_INVERSE,
		GEO_HERO_WALK_FRAME09_INVERSE,
		GEO_HERO_WALK_FRAME10_INVERSE,
		GEO_HERO_JUMP_INVERSE,
		GEO_HERO_LAND_INVERSE,
		GEO_HERO_BULLET,
		GEO_ENEMY_DEFAULT,
		GEO_TILE_KILLZONE,
		GEO_TILE_SAFEZONE,
		NUM_GEOMETRY,
	};
public:
	SceneSandBox();
	~SceneSandBox();


	//======================Getter=========================//
	float calculatingFPS(float dt);

	//======================Setter========================//
	void SetParameters();
	void SetMesh();

	//======================Methods for hero========================//
	void constrainHero(const int leftBorder, const int rightBorder, const int topBorder, const int bottomBorder, float timeDiff);

	//======================Render========================//
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshIn2D(Mesh *mesh, bool enableLight, float sizeX = 1.0f, float sizeY = 1.0f, float x = 0.0f, float y = 0.0f, float z = 0.0f);
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderBackground();
	void Render2DMesh(Mesh *mesh, const bool enableLight, const float size = 1.0f, const float x = 0.f, const float y = 0.f, const bool rotate = false);
	CBullet* fetchBullet();
	void RenderHero();

	//======================Virtual Function========================//
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	// Update Camera status
	virtual void UpdateCameraStatus(const unsigned char key);
private:

	//Int
	unsigned m_vertexArrayID;
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	//Float
	float rotateAngle, rotateAngle2;
	float fps;

	//Double
	double moving;
	double m_dElapsedTime;
	double m_dAccumulatedTime_RenderScene;
	double m_dAccumulatedTime_RenderText;

	//Class
	MS modelStack;
	MS viewStack;
	MS projectionStack;
	Light lights[2];

	//Polymorphism
	Mesh* meshList[NUM_GEOMETRY];

	//vector
	vector<unsigned char> m_heightMap;
	vector<CBullet *> bulletList;
	vector<CEnemy *> enemyList;

	//Vector3
	Vector3 mapPos;
	Vector3 leonPos;
	Vector3 cubePos;

	//Camera3
	Camera3 camera;

	//Bool
	bool bLightEnabled;

	//Fog
	Color fogColor;
	float fogStart;
	float fogEnd;
	float fogDensity;
	int fogType;
	bool fogEnabled;

	//Patricles
	float mSpeed;
	int OBJCount;
	Vector3 gravity;

	//Map
	CMap * m_cMap;
	void RenderTileMap();

	//Code for Smooth scroling
	int mapOffSet_x, mapOffset_y;
	int tileOffSet_x, tileOffset_y;
	int mapFineOffSet_x, mapFineOffset_y;

	//Code for Parallax Scrolling
	CMap * m_cRearMap;
	void RenderRearTileMap();
	int rearWallOffset_x, rearWallOffset_y;
	int rearWallTileOffset_x, rearWallTileOffset_y;
	int rearWallFineOffset_x, rearWallFineOffset_y;

	//Hero Info
	CHero hero;
	bool bulletshot;
	CEnemy *enemy;
};

#endif