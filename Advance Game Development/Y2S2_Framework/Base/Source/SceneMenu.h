#ifndef SCENE_MENU_H
#define SCENE_MENU_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Minimap.h"
#include "GameCharacter\PlayInfo3PV.h"
#include "Particle.h"
#include "Text.h"
#include <vector>

class SceneMenu : public Scene
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
		GEO_CROSSHAIR,
		GEO_LIGHTBALL,
		GEO_TEXT,
		GEO_WALLPAPER,
		GEO_LOGO,

		NUM_GEOMETRY,
	};

	enum MENU_STATE
	{
		E_MENU,
		E_OPTION,
		E_M_TOTAL
	};

public:
	SceneMenu(void);
	SceneMenu(const int m_window_width, const int m_window_height);
	~SceneMenu(void);

	virtual void Init();
	virtual void InitShaders();
	virtual void InitMesh();
	virtual void Update(double dt);
	// Update Camera status
	virtual void UpdateCameraStatus(const unsigned char key, const bool status = true);

	// Update Weapon status
	virtual void UpdateWeaponStatus(const unsigned char key);
	virtual void Render();
	virtual void Exit();

	// Low level render tools
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color);
	void RenderMeshIn2D(Mesh *mesh, bool enableLight, float size = 1.0f, float x = 0.0f, float y = 0.0f, bool rotate = false);
	void RenderMesh(Mesh *mesh, bool enableLight);
	void PreRendering(CTransform* &transform, bool enableLight, Mesh* mesh);
	void PostRendering(Mesh* mesh);

	// Render the main components of this scene
	void RenderGUI();
	void RenderMobileObjects();
	void RenderFixedObjects();
	void RenderLights();
	void RenderGround();
	void RenderSkybox();
	void RenderCharacter();

	//Particle
	std::vector<Particle*> particleList;
	Particle* fetchParticle(Vector3 pos, Vector3 vel, double timeLimit);

	enum WEAPON_ACTION
	{
		WA_NIL = 0,
		WA_FIRE,
		WA_RELOAD,
		WA_CHANGEWEAPON,
		WA_TOTAL,
	};

private:
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	// Handler to the camera
	Camera3 camera;

	// Rotation angle for use with the model stack
	float rotateAngle;

	// Matrices for Model, View and Projection stack
	MS modelStack;
	MS viewStack;
	MS projectionStack;

	// Window size
	int m_window_width;
	int m_window_height;

	Light lights[2];
	bool bLightEnabled;

	//Mouse
	Vector3 mousePos;

	//Text
	std::vector<CText *> textList;

	//Menu
	MENU_STATE currentMenuState;
	MENU_STATE previousMenuState;
	Vector3 v3_MenuPos[E_M_TOTAL];
	Vector3 v3_MenuCam;
	std::string menuChoice;
	bool isMousePressed_Left;

	//Avatar
	CPlayInfo3PV* m_cAvatar;

	float fps;
};

#endif