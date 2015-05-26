#include "SceneText.h"
#include "GL\glew.h"

#include <sstream>
#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include "PistolClass.h"
#include "SniperClass.h"
#include "SMGClass.h"

SceneText::SceneText()
{
}

SceneText::~SceneText()
{
	/*if (camera2 != NULL)
	{
		delete camera2;
		camera2 = NULL;
	}*/
}

void SceneText::SetParameters()
{
	moving = 0;
	Pistol.SetBulletandRounds_Pistol(15, 5);
	Sniper.SetBulletandRounds_Sniper(8, 2);
	SMG.SetBulletandRounds_SMG(30, 3);
	mapPos = Vector3(0, 0, 0);
}

float SceneText::calculatingFPS(float dt)
{
	return (float)(1.f / dt);
}

void SceneText::Init()
{
	// Black background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 

	glEnable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	m_programID = LoadShaders( "Shader//Fog.vertexshader", "Shader//Fog.fragmentshader" );

	// Get a handle for our uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	//m_parameters[U_MODEL] = glGetUniformLocation(m_programID, "M");
	//m_parameters[U_VIEW] = glGetUniformLocation(m_programID, "V");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");
	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled[0]");
	m_parameters[U_COLOR_TEXTURE_ENABLED1] = glGetUniformLocation(m_programID, "colorTextureEnabled[1]");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture[0]");
	m_parameters[U_COLOR_TEXTURE1] = glGetUniformLocation(m_programID, "colorTexture[1]");

	m_parameters[U_COLOR_FOG] = glGetUniformLocation(m_programID, "fogParam.color");
	m_parameters[U_START_FOG] = glGetUniformLocation(m_programID, "fogParam.start");
	m_parameters[U_END_FOG] = glGetUniformLocation(m_programID, "fogParam.end");
	m_parameters[U_DENSITY_FOG] = glGetUniformLocation(m_programID, "fogParam.density");
	m_parameters[U_TYPE_FOG] = glGetUniformLocation(m_programID, "fogParam.type");
	m_parameters[U_ENABLE_FOG] = glGetUniformLocation(m_programID, "fogParam.enabled");

	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	// Use our shader
	glUseProgram(m_programID);

	lights[0].type = Light::LIGHT_DIRECTIONAL;
	lights[0].position.Set(0, 20, 0);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 1;
	lights[0].kC = 1.f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.001f;
	lights[0].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0].cosInner = cos(Math::DegreeToRadian(30));
	lights[0].exponent = 3.f;
	lights[0].spotDirection.Set(0.f, 1.f, 0.f);

	lights[1].type = Light::LIGHT_DIRECTIONAL;
	lights[1].position.Set(1, 1, 0);
	lights[1].color.Set(1, 1, 0.5f);
	lights[1].power = 0.4f;
	//lights[1].kC = 1.f;
	//lights[1].kL = 0.01f;
	//lights[1].kQ = 0.001f;
	//lights[1].cosCutoff = cos(Math::DegreeToRadian(45));
	//lights[1].cosInner = cos(Math::DegreeToRadian(30));
	//lights[1].exponent = 3.f;
	//lights[1].spotDirection.Set(0.f, 1.f, 0.f);

	glUniform1i(m_parameters[U_NUMLIGHTS], 1);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &lights[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], lights[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], lights[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], lights[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], lights[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], lights[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], lights[0].exponent);

	glUniform1i(m_parameters[U_LIGHT1_TYPE], lights[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &lights[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], lights[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], lights[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], lights[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], lights[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], lights[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], lights[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], lights[1].exponent);

	fogColor = (0.5f, 0.5f, 0.5f);
	fogStart = 10.f;
	fogEnd = 1000.f;
	fogDensity = 0.005f;
	fogType = 0;
	fogEnabled = 1;//Enable

	glUniform3fv(m_parameters[U_COLOR_FOG], 1, &fogColor.r);
	glUniform1f(m_parameters[U_START_FOG], fogStart);
	glUniform1f(m_parameters[U_END_FOG], fogEnd);
	glUniform1f(m_parameters[U_DENSITY_FOG], fogDensity);
	glUniform1f(m_parameters[U_TYPE_FOG], fogType);
	glUniform1f(m_parameters[U_ENABLE_FOG], 1);

	camera.Init(Vector3(0, 110, 10), Vector3(0, 110, 0), Vector3(0, 1, 0));

	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_CROSSHAIR] = MeshBuilder::GenerateCrossHair("Crosshair", 1.0f, 1.0f, 0.0f, 1.0f);
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);
	meshList[GEO_OBJECT] = MeshBuilder::GenerateOBJ("OBJ1", "OBJ//chair.obj");//MeshBuilder::GenerateCube("cube", 1);
	meshList[GEO_OBJECT]->textureID = LoadTGA("Image//chair.tga");
	meshList[GEO_RING] = MeshBuilder::GenerateRing("ring", Color(1, 0, 1), 36, 1, 0.5f);
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 18, 36, 1.f);
	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(1, 0, 0), 18, 36, 10.f);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 0, 1), 1);
	//meshList[GEO_TORUS] = MeshBuilder::GenerateCylinder("torus", 36, 36, 5, 1);
	meshList[GEO_CONE] = MeshBuilder::GenerateCone("cone", Color(0.5f, 1, 0.3f), 36, 10.f, 10.f);
	meshList[GEO_CONE]->material.kDiffuse.Set(0.99f, 0.99f, 0.99f);
	meshList[GEO_CONE]->material.kSpecular.Set(0.f, 0.f, 0.f);

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("LEFT", Color(1, 1, 1), 1.f);
	meshList[GEO_LEFT]->textureArray[0] = LoadTGA("Image//left.tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("RIGHT", Color(1, 1, 1), 1.f);
	meshList[GEO_RIGHT]->textureArray[0] = LoadTGA("Image//right.tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("TOP", Color(1, 1, 1), 1.f);
	meshList[GEO_TOP]->textureArray[0] = LoadTGA("Image//top.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("BOTTOM", Color(1, 1, 1), 1.f);
	meshList[GEO_BOTTOM]->textureArray[0] = LoadTGA("Image//bottom.tga");
	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("FRONT", Color(1, 1, 1), 1.f);
	meshList[GEO_FRONT]->textureArray[0] = LoadTGA("Image//front.tga");
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("BACK", Color(1, 1, 1), 1.f);
	meshList[GEO_BACK]->textureArray[0] = LoadTGA("Image//back.tga");

	meshList[GEO_TERRAIN] = MeshBuilder::GenerateTerrain("Terrain", "Image//heightmap.raw", m_heightMap);
	meshList[GEO_TERRAIN]->textureArray[0] = LoadTGA("Image//bottom.tga");
	meshList[GEO_TERRAIN]->textureArray[1] = LoadTGA("Image//Wet Ground.tga");

	meshList[GEO_SPRITE_ANIMATION] = MeshBuilder::GenerateSpriteAnimation("cat", 1, 6);
	meshList[GEO_SPRITE_ANIMATION]->textureArray[0] = LoadTGA("Image//cat.tga");
	SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(meshList[GEO_SPRITE_ANIMATION]);

	if (sa)
	{
		sa->m_anim = new Animation();
		sa->m_anim->Set(0, 4, 0, 1.f);
	}

	meshList[AvatarIcon] = MeshBuilder::GenerateQuad("Avatar Icon", Color(1, 1, 1), 1.0f);
	meshList[AvatarIcon]->textureID = LoadTGA("Image//GGOHead.tga");

	meshList[HudBackground] = MeshBuilder::GenerateQuad("Hud background", Color(1, 1, 1), 1.0f);
	meshList[HudBackground]->textureID = LoadTGA("Image//HudBackground.tga");

	meshList[BulletIcon] = MeshBuilder::GenerateQuad("Bullet Icon", Color(1, 1, 1), 1.0f);
	meshList[BulletIcon]->textureID = LoadTGA("Image//GGOGun.tga");

	meshList[SwordIcon] = MeshBuilder::GenerateQuad("Sword Icon", Color(1, 1, 1), 1.0f);
	meshList[SwordIcon]->textureID = LoadTGA("Image//GGOSword.tga");

	meshList[RoundIcon] = MeshBuilder::GenerateQuad("Round Icon", Color(1, 1, 1), 1.0f);
	meshList[RoundIcon]->textureID = LoadTGA("Image//GGORound.tga");

	meshList[WeaponIcon_Sword] = MeshBuilder::GenerateQuad("Weapon Icon Sword", Color(1, 1, 1), 1.0f);
	meshList[WeaponIcon_Sword]->textureID = LoadTGA("Image//WeaponIcon_Sword.tga");

	meshList[WeaponIcon_Pistol] = MeshBuilder::GenerateQuad("Weapon Icon Pistol", Color(1, 1, 1), 1.0f);
	meshList[WeaponIcon_Pistol]->textureID = LoadTGA("Image//WeaponIcon_Pistol.tga");

	meshList[WeaponIcon_Sniper] = MeshBuilder::GenerateQuad("Weapon Icon Sniper", Color(1, 1, 1), 1.0f);
	meshList[WeaponIcon_Sniper]->textureID = LoadTGA("Image//WeaponIcon_Sniper.tga");

	meshList[WeaponIcon_SMG] = MeshBuilder::GenerateQuad("Weapon Icon SMG", Color(1, 1, 1), 1.0f);
	meshList[WeaponIcon_SMG]->textureID = LoadTGA("Image//WeaponIcon_SMG.tga");

	meshList[Weapon_SMG] = MeshBuilder::GenerateQuad("Weapon SMG", Color(1, 1, 1), 1.0f);
	meshList[Weapon_SMG]->textureID = LoadTGA("Image//SMG_Weapon_Sprite.tga");

	meshList[Weapon_Pistol] = MeshBuilder::GenerateQuad("Weapon Pistol", Color(1, 1, 1), 1.0f);
	meshList[Weapon_Pistol]->textureID = LoadTGA("Image//Pistol_Weapon_Sprite.tga");

	meshList[Weapon_Sniper] = MeshBuilder::GenerateQuad("Weapon Sniper", Color(1, 1, 1), 1.0f);
	meshList[Weapon_Sniper]->textureID = LoadTGA("Image//Sniper_Weapon_Sprite.tga");

	meshList[Weapon_Sword] = MeshBuilder::GenerateQuad("Weapon Sword", Color(1, 1, 1), 1.0f);
	meshList[Weapon_Sword]->textureID = LoadTGA("Image//Sprite_Image_Sword.tga");

	meshList[crosshair] = MeshBuilder::GenerateQuad("Crosshair", Color(1, 1, 1), 1.0f);
	meshList[crosshair]->textureID = LoadTGA("Image//Crosshair 3.tga");

	meshList[Healthbar] = MeshBuilder::GenerateQuad("healthbar", Color(255/253, 255/253, 255/253), 1.f);

	//==================MODEL==================//
	meshList[modelHead] = MeshBuilder::GenerateOBJ("Enemy Head", "OBJ//modelHead.obj");
	meshList[modelHead]->textureArray[0] = LoadTGA("Image//modelHead.tga");

	meshList[modelHand] = MeshBuilder::GenerateOBJ("Enemy Hand", "OBJ//modelHand.obj");
	meshList[modelHand]->textureArray[0] = LoadTGA("Image//modelHand.tga");

	meshList[modelTorso] = MeshBuilder::GenerateOBJ("Enemy Torso", "OBJ//modelTorso.obj");
	meshList[modelTorso]->textureArray[0] = LoadTGA("Image//modelTorso.tga");

	meshList[modelLeg] = MeshBuilder::GenerateOBJ("Enemy Leg", "OBJ//modelLeg.obj");
	meshList[modelLeg]->textureArray[0] = LoadTGA("Image//modelLeg.tga");

	meshList[GEO_SKYPLANE] = MeshBuilder::GenerateSkyPlane("GEO_SKYPLANE", Color(1, 1, 1), 128, 200.0f, 2000.0f, 1.0f, 1.0f);
	meshList[GEO_SKYPLANE]->textureArray[0] = LoadTGA("Image//top.tga"); 

	SetParameters();

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	rotateAngle= rotateAngle2 = 0;

	bLightEnabled = true;
}

/******************************************************************************
Update Camera position
******************************************************************************/
void SceneText::UpdateCameraStatus(const unsigned char key)
{
	camera.UpdateStatus(key);
}

void SceneText::PistolBulletFunction(float dt)
{
	//=========================Pistol Bullet============================//
	if (Pistol.returnCreateBullet_Pistol() == true)
	{
		this->temp = new PistolClass(camera.position, camera.direction, Vector3(0.1f, 0.1f, 0.1f));
		this->PistolBullet.push_back(temp);
	}

	if (PistolBullet.empty() == false)
	{
		for (unsigned a = 0; a < PistolBullet.size(); ++a)
		{
			//Update
			((PistolClass*)PistolBullet[a])->bulletUpdate(dt);
			cout << ((PistolClass*)PistolBullet[a])->bulletPosition << endl;
			//Delete
			if (//Head
				((PistolClass*)PistolBullet[a])->bulletPosition.x < enemy.returnEnemyHeadHitboxMax().x &&
				((PistolClass*)PistolBullet[a])->bulletPosition.x > enemy.returnEnemyHeadHitboxMin().x &&
				((PistolClass*)PistolBullet[a])->bulletPosition.y < enemy.returnEnemyHeadHitboxMax().y &&
				((PistolClass*)PistolBullet[a])->bulletPosition.y > enemy.returnEnemyHeadHitboxMin().y &&
				((PistolClass*)PistolBullet[a])->bulletPosition.z < enemy.returnEnemyHeadHitboxMax().z &&
				((PistolClass*)PistolBullet[a])->bulletPosition.z > enemy.returnEnemyHeadHitboxMin().z)
			{
				if (enemy.returnRenderHead() == true)
				{
					cout << "Hit Head" <<endl;
					enemy.MinusEnemyHeadHealth(((PistolClass*)PistolBullet[a])->returnHeadDamage());
					PistolBullet.erase(PistolBullet.begin() + a);
				}
			}
			else if (((PistolClass*)PistolBullet[a])->bulletPosition.x < enemy.returnEnemyTorsoHitboxMax().x &&
					((PistolClass*)PistolBullet[a])->bulletPosition.x > enemy.returnEnemyTorsoHitboxMin().x &&
					((PistolClass*)PistolBullet[a])->bulletPosition.y < enemy.returnEnemyTorsoHitboxMax().y &&
					((PistolClass*)PistolBullet[a])->bulletPosition.y > enemy.returnEnemyTorsoHitboxMin().y &&
					((PistolClass*)PistolBullet[a])->bulletPosition.z < enemy.returnEnemyTorsoHitboxMax().z &&
					((PistolClass*)PistolBullet[a])->bulletPosition.z > enemy.returnEnemyTorsoHitboxMin().z)
			{
				cout << "Hit Torso" <<endl;
				enemy.MinusEnemyTorsoHealth(((PistolClass*)PistolBullet[a])->returnTorsoDamage());
				PistolBullet.erase(PistolBullet.begin() + a);
			}
			else if(((PistolClass*)PistolBullet[a])->bulletPosition.x < enemy.returnEnemyRightHandHitboxMax().x &&
					((PistolClass*)PistolBullet[a])->bulletPosition.x > enemy.returnEnemyRightHandHitboxMin().x &&
					((PistolClass*)PistolBullet[a])->bulletPosition.y < enemy.returnEnemyRightHandHitboxMax().y &&
					((PistolClass*)PistolBullet[a])->bulletPosition.y > enemy.returnEnemyRightHandHitboxMin().y &&
					((PistolClass*)PistolBullet[a])->bulletPosition.z < enemy.returnEnemyRightHandHitboxMax().z &&
					((PistolClass*)PistolBullet[a])->bulletPosition.z > enemy.returnEnemyRightHandHitboxMin().z)
			{
				if (enemy.returnRenderRightArm() == true)
				{
					cout << "Hit Right Arm" <<endl;
					enemy.MinusEnemyRightArmHealth(((PistolClass*)PistolBullet[a])->returnArmDamage());
					PistolBullet.erase(PistolBullet.begin() + a);
				}
			}
			else if (((PistolClass*)PistolBullet[a])->bulletPosition.x < enemy.returnEnemyLeftHandHitboxMax().x &&
					((PistolClass*)PistolBullet[a])->bulletPosition.x > enemy.returnEnemyLeftHandHitboxMin().x &&
					((PistolClass*)PistolBullet[a])->bulletPosition.y < enemy.returnEnemyLeftHandHitboxMax().y &&
					((PistolClass*)PistolBullet[a])->bulletPosition.y > enemy.returnEnemyLeftHandHitboxMin().y &&
					((PistolClass*)PistolBullet[a])->bulletPosition.z < enemy.returnEnemyLeftHandHitboxMax().z &&
					((PistolClass*)PistolBullet[a])->bulletPosition.z > enemy.returnEnemyLeftHandHitboxMin().z)
			{
				if (enemy.returnRenderLeftArm() == true)
				{
					cout << "Hit Left Arm" <<endl;
					enemy.MinusEnemyLeftArmHealth(((PistolClass*)PistolBullet[a])->returnArmDamage());
					PistolBullet.erase(PistolBullet.begin() + a);
				}
			}
		}
	}
}

void SceneText::SniperBulletFunction(float dt)
{
	//=========================Sniper Bullet============================//
	if (Sniper.returnCreateBullet_Sniper() == true)
	{
		this->temp = new SniperClass(camera.position, camera.direction, Vector3(8.f, 8.f, 8.f));
		this->SniperBullet.push_back(temp);
	}

	if (SniperBullet.empty() == false)
	{
		for (unsigned a = 0; a < SniperBullet.size(); ++a)
		{
			//Update
			((SniperClass*)SniperBullet[a])->bulletUpdate(dt);
			//Delete
			if (//Head
				((SniperClass*)SniperBullet[a])->bulletPosition.x < enemy.returnEnemyHeadHitboxMax().x &&
				((SniperClass*)SniperBullet[a])->bulletPosition.x > enemy.returnEnemyHeadHitboxMin().x &&
				((SniperClass*)SniperBullet[a])->bulletPosition.y < enemy.returnEnemyHeadHitboxMax().y &&
				((SniperClass*)SniperBullet[a])->bulletPosition.y > enemy.returnEnemyHeadHitboxMin().y &&
				((SniperClass*)SniperBullet[a])->bulletPosition.z < enemy.returnEnemyHeadHitboxMax().z &&
				((SniperClass*)SniperBullet[a])->bulletPosition.z > enemy.returnEnemyHeadHitboxMin().z)
			{
				if (enemy.returnRenderHead() == true)
				{
					cout << "Hit Head" <<endl;
					enemy.MinusEnemyHeadHealth(((SniperClass*)SniperBullet[a])->returnHeadDamage());
					SniperBullet.erase(SniperBullet.begin() + a);
				}
			}
			else if (((SniperClass*)SniperBullet[a])->bulletPosition.x < enemy.returnEnemyTorsoHitboxMax().x &&
					((SniperClass*)SniperBullet[a])->bulletPosition.x > enemy.returnEnemyTorsoHitboxMin().x &&
					((SniperClass*)SniperBullet[a])->bulletPosition.y < enemy.returnEnemyTorsoHitboxMax().y &&
					((SniperClass*)SniperBullet[a])->bulletPosition.y > enemy.returnEnemyTorsoHitboxMin().y &&
					((SniperClass*)SniperBullet[a])->bulletPosition.z < enemy.returnEnemyTorsoHitboxMax().z &&
					((SniperClass*)SniperBullet[a])->bulletPosition.z > enemy.returnEnemyTorsoHitboxMin().z)
			{
				cout << "Hit Torso" <<endl;
				enemy.MinusEnemyTorsoHealth(((SniperClass*)SniperBullet[a])->returnTorsoDamage());
				SniperBullet.erase(SniperBullet.begin() + a);
			}
			else if(((SniperClass*)SniperBullet[a])->bulletPosition.x < enemy.returnEnemyRightHandHitboxMax().x &&
					((SniperClass*)SniperBullet[a])->bulletPosition.x > enemy.returnEnemyRightHandHitboxMin().x &&
					((SniperClass*)SniperBullet[a])->bulletPosition.y < enemy.returnEnemyRightHandHitboxMax().y &&
					((SniperClass*)SniperBullet[a])->bulletPosition.y > enemy.returnEnemyRightHandHitboxMin().y &&
					((SniperClass*)SniperBullet[a])->bulletPosition.z < enemy.returnEnemyRightHandHitboxMax().z &&
					((SniperClass*)SniperBullet[a])->bulletPosition.z > enemy.returnEnemyRightHandHitboxMin().z)
			{
				if (enemy.returnRenderRightArm() == true)
				{
					cout << "Hit Right Arm" <<endl;
					enemy.MinusEnemyRightArmHealth(((SniperClass*)SniperBullet[a])->returnArmDamage());
					SniperBullet.erase(SniperBullet.begin() + a);
				}
			}
			else if (((SniperClass*)SniperBullet[a])->bulletPosition.x < enemy.returnEnemyLeftHandHitboxMax().x &&
					((SniperClass*)SniperBullet[a])->bulletPosition.x > enemy.returnEnemyLeftHandHitboxMin().x &&
					((SniperClass*)SniperBullet[a])->bulletPosition.y < enemy.returnEnemyLeftHandHitboxMax().y &&
					((SniperClass*)SniperBullet[a])->bulletPosition.y > enemy.returnEnemyLeftHandHitboxMin().y &&
					((SniperClass*)SniperBullet[a])->bulletPosition.z < enemy.returnEnemyLeftHandHitboxMax().z &&
					((SniperClass*)SniperBullet[a])->bulletPosition.z > enemy.returnEnemyLeftHandHitboxMin().z)
			{
				if (enemy.returnRenderLeftArm() == true)
				{
					cout << "Hit Left Arm" <<endl;
					enemy.MinusEnemyLeftArmHealth(((SniperClass*)SniperBullet[a])->returnArmDamage());
					SniperBullet.erase(SniperBullet.begin() + a);
				}
			}
		}
	}
}

void SceneText::Update(double dt)
{
	if(Application::IsKeyPressed('1'))
	glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('2'))
	glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if(Application::IsKeyPressed('4'))
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if(Application::IsKeyPressed('5'))
	{
		lights[0].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}
	else if(Application::IsKeyPressed('6'))
	{
		lights[0].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}
	else if(Application::IsKeyPressed('7'))
	{
		lights[0].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}
	else if(Application::IsKeyPressed('8'))
	{
		bLightEnabled = true;
	}
	else if(Application::IsKeyPressed('9'))
	{
		bLightEnabled = false;
	}

	if(Application::IsKeyPressed('I'))
		lights[0].position.z -= (float)(10.f * dt);
	if(Application::IsKeyPressed('K'))
		lights[0].position.z += (float)(10.f * dt);
	if(Application::IsKeyPressed('J'))
		lights[0].position.x -= (float)(10.f * dt);
	if(Application::IsKeyPressed('L'))
		lights[0].position.x += (float)(10.f * dt);
	if(Application::IsKeyPressed('O'))
		lights[0].position.y -= (float)(10.f * dt);
	if(Application::IsKeyPressed('P'))
		lights[0].position.y += (float)(10.f * dt);


	camera.Update(dt);
	fps = calculatingFPS((float)dt);

	/*if (moving < 0)
	moving = 0;
	if (moving > 100)
	moving = 100;*/

	if (Application::IsKeyPressed(VK_LEFT))
		rotateAngle += (float)(200 * dt);
	if (Application::IsKeyPressed(VK_RIGHT))
		rotateAngle -= (float)(200 * dt);
	if (Application::IsKeyPressed(VK_UP))
		rotateAngle2 += (float)(200.0f * dt);
	if (Application::IsKeyPressed(VK_DOWN))
		rotateAngle2 -= (float)(200.0f * dt);

	Sword.ChooseWeaponUpdate();
	Pistol.ChooseWeaponUpdate();
	Sniper.ChooseWeaponUpdate();
	SMG.ChooseWeaponUpdate();

	if (Sword.returnSwordConfirmation() == true)
	{
		Sword.update((float)dt);
	}
	if (Pistol.returnPistolConfirmation() == true)
	{
		Pistol.update((float)dt);
	}
	if (Sniper.returnSniperConfirmation() == true)
	{
		Sniper.update((float)dt);
	}
	if (SMG.returnSMGConfirmation() == true)
	{
		SMG.update((float)dt);
	}

	enemy.update((float)dt);
	//cout << enemy.returnEnemyHealth() << endl;
	PistolBulletFunction((float)dt);

	SniperBulletFunction((float)dt);

	//=========================SMG Bullet============================//
	if (SMG.returnCreateBullet_SMG() == true)
	{
		this->temp = new SMGClass(camera.position, camera.direction, Vector3(5.f, 5.f, 5.f));
		this->SMGBullet.push_back(temp);
	}

	if (SMGBullet.empty() == false)
	{
		for (unsigned a = 0; a < SMGBullet.size(); ++a)
		{
			//Update
			((SMGClass*)SMGBullet[a])->bulletUpdate((float)dt);

			//Delete
			if (((SMGClass*)SMGBullet[a])->bulletPosition.z < -10)
			{
				SMGBullet.erase(SMGBullet.begin() + a);
			}
		}
	}
	//mapPos.Set(-20, 0, -20);

	if (Application::IsKeyPressed('9'))
	{
	//	mapPos.z += 5 * dt;
		mapPos.x += 5 * dt;
	}
	if (Application::IsKeyPressed('8'))
	{
		//mapPos.z -= 5 * dt;
		mapPos.x -= 5 * dt;
	}

	mapPos.y = 350.f * ReadHeightMap(m_heightMap, mapPos.x / 4000.f, mapPos.z / 4000.f);

	SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(meshList[GEO_SPRITE_ANIMATION]);

	if (sa)
	{
		sa->Update(dt);
	}
}

static const float SKYBOXSIZE = 1000.f;

void SceneText::RenderText(Mesh* mesh, std::string text, Color color)
{
	if(!mesh || mesh->textureID <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

void SceneText::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if(!mesh || mesh->textureID <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for(unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 1.0f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void SceneText::RenderMeshIn2D(Mesh *mesh, bool enableLight, float sizeX, float sizeY, float x, float y, float z)
{
	Mtx44 ortho;
	ortho.SetToOrtho(-80, 80, -60, 60, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Scale(sizeX, sizeY, sizeX);
	modelStack.Translate(x, y, z);

	Mtx44 MVP, modelview, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	if (mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}

	mesh->Render();
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();
}
/*
MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
modelView = viewStack.Top() * modelStack.Top(); // Week 6
glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
if(enableLight && bLightEnabled)
{
	glUniform1i(m_parameters[U_LIGHTENABLED], 1);
	modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1,
		GL_FALSE, &modelView_inverse_transpose.a[0]);*/


void SceneText::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if(enableLight && bLightEnabled)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		//modelView = viewStack.Top() * modelStack.Top();
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		/*glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);*/
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView_inverse_transpose.a[0]);

		//load material
		glUniform3fv(m_parameters[U_MATERIAL_AMBIENT], 1, &mesh->material.kAmbient.r);
		glUniform3fv(m_parameters[U_MATERIAL_DIFFUSE], 1, &mesh->material.kDiffuse.r);
		glUniform3fv(m_parameters[U_MATERIAL_SPECULAR], 1, &mesh->material.kSpecular.r);
		glUniform1f(m_parameters[U_MATERIAL_SHININESS], mesh->material.kShininess);
	}
	else
	{	
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}
	/*if(mesh->textureID > 0)
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID);
		glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	}
	else
	{
		glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	}
	mesh->Render();
	if(mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}*/
	for (unsigned a = 0; a < 2; ++a)
	{
		if (mesh->textureArray[a] > 0)
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + a], 1);
		}
		else
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + a], 0);
		}

		glActiveTexture(GL_TEXTURE0 + a);
		glBindTexture(GL_TEXTURE_2D, mesh->textureArray[a]);
		glUniform1i(m_parameters[U_COLOR_TEXTURE + a], a);
	}
	mesh->Render();

	glBindTexture(GL_TEXTURE_2D, 0);
}

void SceneText::RenderSkybox()
{
	//left
	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	//RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();
}

void SceneText::RenderHUD()
{

	//===============HEALTH===========//
	for (unsigned a = 0; a < moving; ++a)//Healthbar
	{
		RenderMeshIn2D(meshList[Healthbar], true, 0.8f, 2.0f, -76.0f + a, 25.0f);
	}

	RenderMeshIn2D(meshList[AvatarIcon], true, 13.0f, 13.0f, -5.5f, 4.0f); //Avatar icon

	RenderMeshIn2D(meshList[HudBackground], true, 85.0f, 13.0f, -0.25f, 4.0f);//background

	RenderTextOnScreen(meshList[GEO_TEXT], "Setsuna", Color(1.0f, 1.0f, 1.0f), 3.0f, 9.5f, 55.7f);//Name

	if (Sword.returnSwordConfirmation() == false)
	{
		RenderMeshIn2D(meshList[HudBackground], true, 20.0f, 5.0f, 3.49f, -11.5f);//background for ready screen
	}

	//===============Weapon Chosen==============//
	RenderMeshIn2D(meshList[HudBackground], true, 13.0f, 13.0f, -4.4f, 2.9f);//bakcground for ammo
	RenderMeshIn2D(meshList[HudBackground], true, 13.0f, 13.0f, -4.4f, 1.8f);//background for round
	//==============Round============//
	RenderMeshIn2D(meshList[RoundIcon], true, 13.0f, 13.0f, -5.5f, 1.8f);//Round icon

	//=====================SWORD=====================//
	if (Sword.returnSwordConfirmation() == true)
	{
		RenderMeshIn2D(meshList[SwordIcon], true, 13.0f, 13.0f, -5.5f, 2.9f);//Sword icon

		RenderTextOnScreen(meshList[GEO_TEXT], "--", Color(1.0f, 1.0f, 1.0f), 3.0f, 9.5f, 47.5f);//Sword got no bullet, so i used --

		RenderTextOnScreen(meshList[GEO_TEXT], "--", Color(1.0f, 1.0f, 1.0f), 3.0f, 9.5f, 40.0f);//Sword got no round, so i used --

		RenderMeshIn2D(meshList[WeaponIcon_Sword], true, 40.5f, 40.5f, -0.7f, 0.925f);// This is the icon for close ranged weapon

		if (Application::IsKeyPressed('R'))
		{
			RenderMeshIn2D(meshList[HudBackground], true, 80.0f, 10.0f, 0.01f, 0.2f);//background for reload screen
			RenderTextOnScreen(meshList[GEO_TEXT], "Error", Color(1.0f, 1.0f, 1.0f), 3.0f, 33.5f, 29.5f);
		}
	}//=====================PISTOL=====================//
	if (Pistol.returnPistolConfirmation() == true)//player is using pistol
	{
		RenderMeshIn2D(meshList[BulletIcon], true, 13.0f, 13.0f, -5.5f, 2.9f);//Bullet icon

		if (Pistol.returnBullet_Pistol() < 10)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], std::to_string((long long)Pistol.returnBullet_Pistol()), Color(1.0f, 1.0f, 1.0f), 3.0f, 10.8f, 47.5f);
		}
		else
		{
			RenderTextOnScreen(meshList[GEO_TEXT], std::to_string((long long)Pistol.returnBullet_Pistol()), Color(1.0f, 1.0f, 1.0f), 3.0f, 9.5f, 47.5f);
		}

		RenderTextOnScreen(meshList[GEO_TEXT], std::to_string((long long)Pistol.returnRounds_Pistol()), Color(1.0f, 1.0f, 1.0f), 3.0f, 10.8f, 40.0f);

		RenderMeshIn2D(meshList[WeaponIcon_Pistol], true, 40.5f, 40.5f, -0.7f, 0.925f);// This is the icon for long ranged weapon

		if (Pistol.returnReloading() == true) //reloading
		{
			RenderMeshIn2D(meshList[HudBackground], true, 80.0f, 10.0f, 0.01f, 0.2f);//background for reload screen
			RenderTextOnScreen(meshList[GEO_TEXT], "Reload in", Color(1.0f, 1.0f, 1.0f), 3.0f, 25.0f, 29.5f);
			RenderTextOnScreen(meshList[GEO_TEXT], std::to_string((long long)Pistol.returnReloadTime_Pistol()), Color(1.0f, 1.0f, 1.0f), 3.0f, 55.0f, 29.5f);
		}

		if (Pistol.returnReadyToShootPistol() == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Ready", Color(1.0f, 1.0f, 1.0f), 2.0f, 70.7f, 0.3f);
		}
	}//=====================SNIPER=====================//
	else if (Sniper.returnSniperConfirmation() == true)//player is using sniper
	{
		RenderMeshIn2D(meshList[BulletIcon], true, 13.0f, 13.0f, -5.5f, 2.9f);//Bullet icon

		RenderTextOnScreen(meshList[GEO_TEXT], std::to_string((long long)Sniper.returnBullet_Sniper()), Color(1.0f, 1.0f, 1.0f), 3.0f, 10.8f, 47.5f);

		RenderTextOnScreen(meshList[GEO_TEXT], std::to_string((long long)Sniper.returnRounds_Sniper()), Color(1.0f, 1.0f, 1.0f), 3.0f, 10.8f, 40.0f);

		RenderMeshIn2D(meshList[WeaponIcon_Sniper], true, 40.5f, 40.5f, -0.7f, 0.925f);// This is the icon for logn ranged weapon

		if (Sniper.returnReloading() == true)
		{
			RenderMeshIn2D(meshList[HudBackground], true, 80.0f, 10.0f, 0.01f, 0.2f);//background for reload screen
			RenderTextOnScreen(meshList[GEO_TEXT], "Reload in", Color(1.0f, 1.0f, 1.0f), 3.0f, 25.0f, 29.5f);
			RenderTextOnScreen(meshList[GEO_TEXT], std::to_string((long long)Sniper.returnReloadTime_Sniper()), Color(1.0f, 1.0f, 1.0f), 3.0f, 55.0f, 29.5f);
		}
		/*else
		{
			modelStack.PushMatrix();
			RenderMeshIn2D(meshList[Weapon_Sniper], false, 70.f, 70.f, 0.7f, -0.4f);
			modelStack.PopMatrix();
		}*/

		if (Sniper.returnReadyToShootSniper() == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Ready", Color(1.0f, 1.0f, 1.0f), 2.0f, 70.7f, 0.3f);
		}
	}//=====================SMG=====================//
	else if (SMG.returnSMGConfirmation() == true)//player is using SMG
	{
		RenderMeshIn2D(meshList[BulletIcon], true, 13.0f, 13.0f, -5.5f, 2.9f);//Bullet icon

		if (SMG.returnBullet_SMG() < 10)//Arranging bullet number to middle if it is less than 10
		{
			RenderTextOnScreen(meshList[GEO_TEXT], std::to_string((long long)SMG.returnBullet_SMG()), Color(1.0f, 1.0f, 1.0f), 3.0f, 10.8f, 47.5f);
		}
		else
		{	
			RenderTextOnScreen(meshList[GEO_TEXT], std::to_string((long long)SMG.returnBullet_SMG()), Color(1.0f, 1.0f, 1.0f), 3.0f, 9.5f, 47.5f);
		}


		RenderTextOnScreen(meshList[GEO_TEXT], std::to_string((long long)SMG.returnRounds_SMG()), Color(1.0f, 1.0f, 1.0f), 3.0f, 10.8f, 40.0f);

		RenderMeshIn2D(meshList[WeaponIcon_SMG], true, 40.5f, 40.5f, -0.7f, 0.925f);// This is the icon for logn ranged weapon

		if (SMG.returnReloading() == true)//Reloading
		{
			RenderMeshIn2D(meshList[HudBackground], true, 80.0f, 10.0f, 0.01f, 0.2f);//background for reload screen
			RenderTextOnScreen(meshList[GEO_TEXT], "Reload in", Color(1.0f, 1.0f, 1.0f), 3.0f, 25.0f, 29.5f);
			RenderTextOnScreen(meshList[GEO_TEXT], std::to_string((long long)SMG.returnReloadTime_SMG()), Color(1.0f, 1.0f, 1.0f), 3.0f, 55.0f, 29.5f);
		}
	/*	else
		{
			modelStack.PushMatrix();
			RenderMeshIn2D(meshList[Weapon_SMG], false, 100.f, 100.f, 0.3f, -0.2f);
			modelStack.PopMatrix();
		}*/

		if (SMG.returnReadyToShootSMG() == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Ready", Color(1.0f, 1.0f, 1.0f), 2.0f, 70.7f, 0.3f);
		}
	}

	if (Sword.returnSwordConfirmation() == true)
	{
		RenderMeshIn2D(meshList[Weapon_Sword], false, 90.f, 90.f, 0.56f, -0.35f);
	}
	if (Pistol.returnReloading() == false)
	{
		if (Pistol.returnPistolConfirmation() == true)
		{
			modelStack.PushMatrix();
			RenderMeshIn2D(meshList[Weapon_Pistol], false, 70.f, 70.f, 0.7f, -0.4f);
			modelStack.PopMatrix();
		}
	}
	if (Sniper.returnReloading() == false)
	{
		if (Sniper.returnSniperConfirmation() == true)
		{
			modelStack.PushMatrix();
			RenderMeshIn2D(meshList[Weapon_Sniper], false, 70.f, 70.f, 0.7f, -0.4f);
			modelStack.PopMatrix();
		}
	}
	//==================CrossHair=============//
	RenderMeshIn2D(meshList[crosshair], true, 5.0f, 5.0f, 0 , 0);

	if (SMG.returnReloading() == false)
	{
		if (SMG.returnSMGConfirmation() == true)
		{
			modelStack.PushMatrix();
			RenderMeshIn2D(meshList[Weapon_SMG], false, 100.f, 100.f, 0.3f, -0.2f);
			modelStack.PopMatrix();
		}
	}


	
}

void SceneText::RenderEnemyModel()
{
	if (enemy.returnAliveState() == true)
	{
		if (enemy.returnRenderHead() == true)
		{
			//Head
			modelStack.PushMatrix();
			modelStack.Translate(enemy.returnEnemyHeadPosition().x,
				enemy.returnEnemyHeadPosition().y, 
				enemy.returnEnemyHeadPosition().z);
			RenderMesh(meshList[modelHead], false);
			modelStack.PopMatrix();
		}

		//Torso
		modelStack.PushMatrix();
		modelStack.Translate(enemy.returnEnemyTorsoPosition().x,
			enemy.returnEnemyTorsoPosition().y,
			enemy.returnEnemyTorsoPosition().z);
		RenderMesh(meshList[modelTorso], false);
		modelStack.PopMatrix();

		if (enemy.returnRenderLeftArm() == true)
		{
			//Left Arm
			modelStack.PushMatrix();
			modelStack.Translate(enemy.returnEnemyLeftHandPosition().x,
				enemy.returnEnemyLeftHandPosition().y,
				enemy.returnEnemyLeftHandPosition().z);
			RenderMesh(meshList[modelHand], false);
			modelStack.PopMatrix();
		}

		if (enemy.returnRenderRightArm() == true)
		{
			//Right Arm
			modelStack.PushMatrix();
			modelStack.Translate(enemy.returnEnemyRightHandPosition().x,
				enemy.returnEnemyRightHandPosition().y,
				enemy.returnEnemyRightHandPosition().z);
			RenderMesh(meshList[modelHand], false);
			modelStack.PopMatrix();
		}

		//Left Leg
		modelStack.PushMatrix();
		modelStack.Translate(enemy.returnEnemyLeftLegPosition().x,
							 enemy.returnEnemyLeftLegPosition().y,
							 enemy.returnEnemyLeftLegPosition().z);
		RenderMesh(meshList[modelLeg], false);
		modelStack.PopMatrix();

		//Right Leg
		modelStack.PushMatrix();
		modelStack.Translate(0.34f, -1.5f, 0.f);
		RenderMesh(meshList[modelLeg], false);
		modelStack.PopMatrix();
	}
}

void SceneText::view()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
		);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();
}

void SceneText::RenderSkyPlane(Mesh* mesh, Color color, int slices, float PlanetRadius, float height, float hTile, float vTile)
{
	modelStack.PushMatrix();

	modelStack.Translate(500.f, 1800.f, -500.f);

	//modelStack.Scale(0.9, 0.9, 0.9);

	RenderMesh(meshList[GEO_SKYPLANE], false);

	modelStack.PopMatrix();
}

void SceneText::RenderTerrain()
{
	Vector3 pos;
	pos.Set(-20, 0, -20);
	pos.y = 350.f * ReadHeightMap(m_heightMap, pos.x / 4000.f, pos.z / 4000.f);
	modelStack.PushMatrix();
	modelStack.Scale(2000.0f, 350.f, 2000.f);
	RenderMesh(meshList[GEO_TERRAIN], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(mapPos.x + 5.f, mapPos.y + 2.f, mapPos.z);
	RenderMesh(meshList[GEO_CUBE], false);
	modelStack.PopMatrix();
}

void SceneText::Render()
{
	view();

	if(lights[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[0].position.x, lights[0].position.y, lights[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if(lights[0].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[0].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT0_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[0].position;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);
	}
	if(lights[1].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[1].position.x, lights[1].position.y, lights[1].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if(lights[1].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * lights[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * lights[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
	}

	modelStack.PushMatrix();//Use this method to give the illusion that the bug is not there
	if (camera.currentlyFalling == false && camera.currentlyJumping == false && camera.pressedSpace == false)
	{
		modelStack.Translate(0, camera.position.y, 0);
	}
	RenderMesh(meshList[GEO_AXES], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(lights[0].position.x, lights[0].position.y, lights[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	//RenderSkybox();

	// perspective;
	////perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	//projectionStack.LoadMatrix(perspective);
	//viewStack.LoadIdentity();
	//
	//modelStack.PushMatrix();
	////modelStack.Translate(20, 0, -20);
	////modelStack.Scale(0.1f, 0.1f, 0.1f);
	//modelStack.Scale(50, 50, 50);
	////RenderMesh(meshList[GEO_QUAD], false);
	//RenderText(meshList[GEO_TEXT], "HelloWorld", Color(0, 1, 0));
	//modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-20, 0, -20);
	RenderMesh(meshList[GEO_OBJECT], false);
	modelStack.PopMatrix();

	


	modelStack.PushMatrix();
	modelStack.Scale(10, 10, 10);
	//RenderText(meshList[GEO_TEXT], "Hello World", Color(0, 1, 0));
	RenderText(meshList[GEO_TEXT], "Hello World", Color(0, 1, 0));
	modelStack.PopMatrix();

	//On screen text
	std::ostringstream ss;
	ss.precision(5);
	ss << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 6);

	std::ostringstream ss1;
	ss1.precision(4);
	ss1 << "Light(" << lights[0].position.x << ", " << lights[0].position.y << ", " << lights[0].position.z << ")";
	RenderTextOnScreen(meshList[GEO_TEXT], ss1.str(), Color(0, 1, 0), 3, 0, 3);

	//RenderTextOnScreen(meshList[GEO_TEXT], "Hello Screen", Color(0, 1, 0), 3, 0, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Translate(enemy.returnEnemyPosition().x, -2 + enemy.returnEnemyPosition().y, enemy.returnEnemyPosition().z);
	//RenderEnemyModel();
	modelStack.PopMatrix();

	RenderTerrain();
	RenderSkyPlane(meshList[GEO_SKYPLANE],Color (1,1,1), 128, 200.0f, 1000.0f, 1.0f, 1.0f);

	modelStack.PushMatrix();
	//modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_SPRITE_ANIMATION], false);
	modelStack.PopMatrix();

	//==============Testing===============//
	//modelStack.PushMatrix();//Left right
	//modelStack.Translate(camera.direction.x, camera.direction.y, camera.direction.z);
	//modelStack.Rotate(rotateAngle, 0, 1, 0);
	//modelStack.Translate(0, 0, -4);

	//RenderMesh(meshList[GEO_CUBE], true);
	//modelStack.PopMatrix();
}

void SceneText::Exit()
{
	// Cleanup VBO
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if(meshList[i])
			delete meshList[i];
	}
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}