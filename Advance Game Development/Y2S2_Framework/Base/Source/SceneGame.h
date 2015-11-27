#ifndef SCENE_GAME_H
#define SCENE_GAME_H

#include "Scene.h"
#include "Mtx44.h"
#include "Camera3.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Minimap.h"
#include "GameCharacter\PlayInfo3PV.h"
#include "SceneGraph\SceneNode.h"
#include "Particle.h"
#include "Text.h"
#include "SpatialPartition\SpatialPartition.h"
#include "SpatialPartition\SP_Grid.h"
#include "GameCharacter\AI.h"
#include "GameCharacter\Bullet.h"
#include "Sound\Sound.h"
#include "Projectile\ProjectileManager.h"

#include <map>
#include <unordered_map>
#include <vector>
#include <memory>

const float SKYBOXSIZE = 1000.f;
const int CELL_SIZE = 100;
class SceneGame : public Scene
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
		U_COLOR_TEXTURE,
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
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
		GEO_GRASS_DARKGREEN,
		GEO_GRASS_LIGHTGREEN,
		GEO_OBJECT,
		GEO_TEXT,

		GEO_UNICORN_LEFT_LEG,
		GEO_UNICORN_RIGHT_LEG,

		NUM_GEOMETRY,
	};
	enum SOUND_TYPE
	{
		ST_BEAM_MAGNUM,
		ST_TOTAL
	};

public:
	SceneGame(void);
	SceneGame(const int m_window_width, const int m_window_height);
	~SceneGame(void);

	virtual void Init();
	virtual void InitShaders();
	virtual void InitMesh();
	virtual void Update(double dt);
	// Update Camera status
	virtual void UpdateCameraStatus(const unsigned char key, const bool status = true);

	//Update Avatar Position
	virtual void UpdateAvatarStatus(const unsigned char key, const bool status = true);

	// Update Weapon status
	virtual void UpdateWeaponStatus(const unsigned char key);
	virtual void Render();
	virtual void Exit();

	// Low level render tools
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color);
	void RenderMeshIn2D(Mesh *mesh, bool enableLight, float size=1.0f, float x=0.0f, float y=0.0f, bool rotate=false);
	void RenderMesh(Mesh *mesh, bool enableLight);
	void PreRendering(CTransform* &transform, bool enableLight, Mesh* mesh);
	void PostRendering(Mesh* mesh);
	void UpdateGameplay(const double &dt);
	void UpdateMenu(const double &dt);

	// Render the main components of this scene
	void RenderGUI();
	void RenderMobileObjects();
	void RenderFixedObjects();
	void RenderLights();
	void RenderGround();
	void RenderSkybox();
	void RenderGameplay();
	void RenderMenu();

	//Particle
	std::vector<Particle*> particleList;
	Particle* fetchParticle(Vector3 pos, Vector3 vel, double timeLimit);
	void createParticle(const double &dt);

	CGameObject* fetchGO();
	AI* fetchAI();
	CBullet* fetchBullet();

	//Collision
	void collisionCheck(CGameObject* node1, CGameObject* node2);
	void checkCollision(CGameObject* go, std::vector<CGameObject*>& goToCheck, int startingIndex);
	void Collision_PlayerToAi(AI* ai);
	void shootBullet(const Vector3& pos, const Vector3& direction, const double& timeLimit, bool playerBullet = true);


	//Menu
	void textUpdate();

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

	float fps;

	// Handle to the minimap
	CMinimap* m_cMinimap;

	//Handle to 3rd person view's avatar
	CPlayInfo3PV* m_cAvatar;

	//Scene Graph
	CSceneNode* m_cSceneGraph;

	//Menu
	Vector3 mousePos;
	bool b_pauseGame;
	std::vector<CText *> textList;
	std::string menuChoice;
	bool isMousePressed_Left;

	std::unique_ptr<Grid> m_grid;

	//Spatial Partioning
	CSpatialPartition * m_cSpatialPartition;

	std::vector<CGameObject*> GOList;

	//Projectile
	CProjectileManager* m_cProjectileManager;

	Sound sound;
};

#endif