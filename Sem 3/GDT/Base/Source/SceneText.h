#ifndef SCENE_TEXT_H
#define SCENE_TEXT_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Weapon.h"
#include <vector>
#include <string>
#include "Enemy.h"
#include "Ammo.h"
#include "MiniMap.h"

using std::vector;
class SceneText : public Scene
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
		Healthbar,
		AvatarIcon,
		SwordIcon,
		BulletIcon,
		RoundIcon,
		WeaponIcon_Sword,
		WeaponIcon_Pistol,
		WeaponIcon_Sniper,
		WeaponIcon_SMG,
		HudBackground,
		modelHead,
		modelHand,
		modelTorso,
		modelLeg,
		Weapon_SMG,
		Weapon_Pistol,
		Weapon_Sniper,
		Weapon_Sword,
		crosshair,
		NUM_GEOMETRY,
	};
public:
	SceneText();
	~SceneText();


	//======================Getter=========================//
	float calculatingFPS(float dt);
	void PistolBulletFunction(float dt);
	void SniperBulletFunction(float dt);

	//======================Setter========================//
	void SetParameters();
	void view();

	//======================Render========================//
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);
	void RenderMeshIn2D(Mesh *mesh, bool enableLight, Vector3 size, Vector3 translate, bool rotate);
	void RenderSkyPlane(Mesh* mesh, Color color, int slices, float PlanetRadius, float height, float hTile, float vTile);
	void RenderMesh(Mesh *mesh, bool enableLight);
	void RenderSkybox();
	void RenderHUD();
	void RenderEnemyModel();
	void RenderEverything();
	void RenderTerrain();
	void SetHUD(const bool m_bHUDmode);

	//======================Virtual Function========================//
	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	// Update Camera status
	virtual void UpdateCameraStatus (const unsigned char key);
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

	CEnemy enemy;
	CAmmo Pistol, Sniper, SMG, Sword;

	Light lights[2];

	//Polymorphism
	Mesh* meshList[NUM_GEOMETRY];
	CAmmo * temp;
	CMinimap* m_cMinimap;

	//vector
	vector<CAmmo *> PistolBullet;
	vector<CAmmo *> SniperBullet;
	vector<CAmmo *> SMGBullet;
	vector<unsigned char> m_heightMap;

	//Camera3
	Camera3 camera;

	//Bool
	bool bLightEnabled;
};

#endif