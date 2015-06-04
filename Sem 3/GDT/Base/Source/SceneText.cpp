#include "SceneText.h"
#include "GL\glew.h"

#include <sstream>
#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"

#include <irrKlang.h>

#pragma comment (lib, "irrKlang.lib")
using namespace irrklang;

ISoundEngine *sound = createIrrKlangDevice(ESOD_AUTO_DETECT, ESEO_MULTI_THREADED | ESEO_LOAD_PLUGINS | ESEO_USE_3D_BUFFERS);

SceneText::SceneText() :
	m_cMinimap(NULL)
{
}

SceneText::~SceneText()
{
	if (m_cMinimap)
	{
		delete m_cMinimap;
		m_cMinimap = NULL;
	}
}

void SceneText::SetParameters()
{
	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));
	moving = 100;
	rotateAngle = 0;
	rotateAngle2 = 0;
	bLightEnabled = true;
	Pistol.setBulletAndRounds(15, 5, 0.5f, 3.f);
	Sniper.setBulletAndRounds(8, 2, 1.2f, 5.f);
	SMG.setBulletAndRounds(90, 3, 0.2f, 5.f);
	enemyCount = 0;
	enemy.setPos(Vector3(0, 0, 0), Vector3(0, 0, 1));
	restockTime = 10;
	FApos.SetZero();
	restocking = false;
	restockTime = 5.f;
	caught = false;

	//Skybox
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("LEFT", Color(1, 1, 1), 1.f);
	meshList[GEO_LEFT]->textureArray[0] = LoadTGA("Image//left.tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("RIGHT", Color(1, 1, 1), 1.f);
	meshList[GEO_RIGHT]->textureArray[0] = LoadTGA("Image//right.tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("TOP", Color(1, 1, 1), 1.f);
	meshList[GEO_TOP]->textureArray[0] = LoadTGA("Image//top.tga");
	/*meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("BOTTOM", Color(1, 1, 1), 1.f);
	meshList[GEO_BOTTOM]->textureArray[0] = LoadTGA("Image//bottom.tga");*/
	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("FRONT", Color(1, 1, 1), 1.f);
	meshList[GEO_FRONT]->textureArray[0] = LoadTGA("Image//front.tga");
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("BACK", Color(1, 1, 1), 1.f);
	meshList[GEO_BACK]->textureArray[0] = LoadTGA("Image//back.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("BOTTOM", Color(1, 1, 1), 1.f);
	meshList[GEO_BOTTOM]->textureArray[0] = LoadTGA("Image//bottom.tga");
	meshList[GEO_BOTTOM]->textureArray[1] = LoadTGA("Image//Wet Ground.tga");

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
	meshList[Healthbar] = MeshBuilder::GenerateQuad("healthbar", Color(1, 1, 1), 1.f);
	meshList[Healthbar]->textureID = LoadTGA("Image//Healthbar.tga");

	//SKYPLANE
	meshList[GEO_SKYPLANE] = MeshBuilder::GenerateSkyPlane("GEO_SKYPLANE", Color(1, 1, 1), 128, 200.0f, 2000.0f, 1.0f, 1.0f);
	meshList[GEO_SKYPLANE]->textureID = LoadTGA("Image//top.tga");

	//MINIMAP
	m_cMinimap = new CMinimap();
	m_cMinimap->SetBackground(MeshBuilder::GenerateQuad("Crosshair", Color(1, 1, 1), 1.0f));
	m_cMinimap->GetBackground()->textureID = LoadTGA("Image//compass.tga");
	//m_cMinimap->GetBackground()->textureArray[0] = LoadTGA("Image//bottom.tga");
	//m_cMinimap->GetBackground()->textureArray[1] = LoadTGA("Image//Wet Ground.tga");
	m_cMinimap->SetBorder(MeshBuilder::GenerateSphere("Minimap", Color(1, 0, 0), 9, 18, 1.01f));
	m_cMinimap->SetAvatar(MeshBuilder::GenerateMinimapAvatar("MiniMap border", Color(1, 1, 1), 1.f));


	//Animation
	meshList[GEO_SPRITE_ANIMATION] = MeshBuilder::GenerateSpriteAnimation("Dragon", 1, 6);
	meshList[GEO_SPRITE_ANIMATION]->textureArray[0] = LoadTGA("Image//Dragon.tga");
	SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(meshList[GEO_SPRITE_ANIMATION]);

	if (sa)
	{
		sa->m_anim = new Animation();
		sa->m_anim->Set(0, 4, 0, 1.f);
	}

	meshList[GEO_SKYPLANE] = MeshBuilder::GenerateSkyPlane("GEO_SKYPLANE", Color(1, 1, 1), 128, 200.0f, 2000.0f, 1.0f, 1.0f);
	meshList[GEO_SKYPLANE]->textureArray[0] = LoadTGA("Image//top.tga");

	meshList[firstAid] = MeshBuilder::GenerateOBJ("OBJ1", "OBJ//FirstAidbox.obj");
	meshList[firstAid]->textureArray[0] = LoadTGA("Image//FirstAid.tga");
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

	m_programID = LoadShaders("Shader//Fog.vertexshader", "Shader//Fog.fragmentshader");

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


	for (int i = 0; i < NUM_GEOMETRY; ++i)
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
	meshList[GEO_CONE] = MeshBuilder::GenerateCone("cone", Color(0.5f, 1, 0.3f), 36, 10.f, 10.f);
	meshList[GEO_CONE]->material.kDiffuse.Set(0.99f, 0.99f, 0.99f);
	meshList[GEO_CONE]->material.kSpecular.Set(0.f, 0.f, 0.f);

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	SetParameters();
}

CAmmo* SceneText::FetchBullet()
{
	//Reuse bullets that are not active
	for (vector<CAmmo*>::iterator it = bulletList.begin(); it != bulletList.end(); ++it)
	{
		CAmmo * BY = (CAmmo*)*it;
		if (!BY->active)
		{
			BY->active = true;
			return BY;
		}
	}

	//Create new bullet if there are not enough
	for (unsigned i = 0; i < 10; ++i)
	{
		CAmmo *BY = new CAmmo();
		bulletList.push_back(BY);
	}

	CAmmo *BY = bulletList.back();
	BY->active = true;

	return BY;
}

void SceneText::SetHUD(const bool m_bHUDmode)
{
	if (m_bHUDmode)
	{
		glDisable(GL_DEPTH_TEST);
		Mtx44 ortho;
		ortho.SetToOrtho(0, 80, 0, 60, -10, 10);
		projectionStack.PushMatrix();
		projectionStack.LoadMatrix(ortho);
	}
	else
	{
		projectionStack.PopMatrix();
		glEnable(GL_DEPTH_TEST);
	}
}

/******************************************************************************
Update Camera position
******************************************************************************/
void SceneText::UpdateCameraStatus(const unsigned char key)
{
	camera.UpdateStatus(key);
}

void SceneText::BulletUpdate(float dt)
{
	if (restocking == false)
	{
		if (Pistol.getCreateBullet() && weapon.returnPistolConfirmation())
		{
			CAmmo * newAmmo = FetchBullet();
			sound->play3D("../irrKlang/media/Pistol.mp3", vec3df(0, 0, 0), false);
			newAmmo->setDirection(camera.position, camera.direction, Vector3(200.f, 200.f, 200.f), 50, true, 3.f, WEAPON::BULLET_PISTOL);
			camera.target.y += 2 * dt;
		}
		else if (Sniper.getCreateBullet() && weapon.returnSniperConfirmation())
		{
			CAmmo * newAmmo = FetchBullet();
			sound->play3D("../irrKlang/media/Sniper.mp3", vec3df(0, 0, 0), false);
			newAmmo->setDirection(camera.position, camera.direction, Vector3(200.f, 200.f, 200.f), 100, true, 3.f, WEAPON::BULLET_SNIPER);
			camera.target.y += 10 * dt;
		}
		else if (SMG.getCreateBullet() && weapon.returnSMGConfirmation())
		{
			CAmmo * newAmmo = FetchBullet();
			sound->play3D("../irrKlang/media/SMG.mp3", vec3df(0, 0, 0), false);
			newAmmo->setDirection(camera.position, camera.direction, Vector3(200.f, 200.f, 200.f), 25, true, 3.f, WEAPON::BULLET_SMG);
			camera.target.y += dt;
		}
	}


	for (vector<CAmmo*>::iterator it = bulletList.begin(); it != bulletList.end(); ++it)
	{
		CAmmo * BY = (CAmmo*)*it;
		if (BY->active == true)
		{
			BY->lifeTime -= dt;

			if (BY->lifeTime <= 0)
				BY->active = false;

			//Update Bullet Position if it is still active
			BY->bulletPosition.x += (BY->bulletDirection.x * BY->bulletSpeed.x * dt);
			BY->bulletPosition.y += (BY->bulletDirection.y * BY->bulletSpeed.y * dt);
			BY->bulletPosition.z += (BY->bulletDirection.z * BY->bulletSpeed.z * dt);

			for (vector<CEnemy *>::iterator it = enemyList.begin(); it != enemyList.end(); it++)
			{
				CEnemy * E = (CEnemy*)*it;
				if (E->active == true)
				{
					if ((BY->bulletPosition - E->getEnemyPos()).LengthSquared() < 10)
					{
						cout << "Hit" << endl;
						E->minusHealth(BY->damage);
						BY->active = false;
						enemyCount--;
					}
				}
			}
		}
	}
}

void SceneText::reset()
{
	SetParameters();
}

void SceneText::Update(double dt)
{

	if (Application::IsKeyPressed('P'))
	{
		camera.Reset();
		reset();

		for (vector<CAmmo*>::iterator it = bulletList.begin(); it != bulletList.end(); ++it)
		{
			CAmmo *BY = (CAmmo*)*it;

			if (BY->active)
			{
				BY->active = false;
			}
		}

		for (vector<CEnemy*>::iterator it = enemyList.begin(); it != enemyList.end(); ++it)
		{
			CEnemy *E = (CEnemy*)*it;

			if (E->active)
			{
				E->active = false;
			}
		}
	}
	if (moving > 0)
	{
		/*if(Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);
		if(Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
		if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/

		if (Application::IsKeyPressed('5'))
		{
			lights[0].type = Light::LIGHT_POINT;
			glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
		}
		else if (Application::IsKeyPressed('6'))
		{
			lights[0].type = Light::LIGHT_DIRECTIONAL;
			glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
		}
		else if (Application::IsKeyPressed('7'))
		{
			lights[0].type = Light::LIGHT_SPOT;
			glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
		}
		else if (Application::IsKeyPressed('8'))
		{
			bLightEnabled = true;
		}
		else if (Application::IsKeyPressed('9'))
		{
			bLightEnabled = false;
		}

		if (Application::IsKeyPressed('I'))
			lights[0].position.z -= (float)(10.f * dt);
		if (Application::IsKeyPressed('K'))
			lights[0].position.z += (float)(10.f * dt);
		if (Application::IsKeyPressed('J'))
			lights[0].position.x -= (float)(10.f * dt);
		if (Application::IsKeyPressed('L'))
			lights[0].position.x += (float)(10.f * dt);
		if (Application::IsKeyPressed('O'))
			lights[0].position.y -= (float)(10.f * dt);
		if (Application::IsKeyPressed('P'))
			lights[0].position.y += (float)(10.f * dt);

		if (moving > 0)
		{
			camera.Update(dt);
		}
		fps = calculatingFPS((float)dt);

		if (moving < 0)
			moving = 0;
		if (moving > 100)
			moving = 100;

		static CEnemy * newEnemy;
		if (enemyCount < 10)
		{
			newEnemy = new CEnemy;
			float min = Math::RandFloatMinMax(-1000, 1000);
			float max = Math::RandFloatMinMax(-1000, 1000);
			newEnemy->active = true;
			newEnemy->setPos(Vector3(min, 0, max), Vector3(min, 0, max + 1));
			enemyList.push_back(newEnemy);
			enemyCount++;
		}

		static float testing = 0.f;
		for (vector<CEnemy *>::iterator it = enemyList.begin(); it != enemyList.end(); it++)
		{
			CEnemy * E = (CEnemy*)*it;
			if (E->active == true)
			{
				if ((camera.position - E->getEnemyPos()).Length() > 6)
				{
					E->update(dt, camera.position);
					testing += dt;
				}
				else
				{
					if (testing >= 0.02f)
					{
						sound->play3D("../irrKlang/media/Claw.mp3", vec3df(0, 0, 0), false);
						moving -= 10 * dt;
						testing = 0.f;
					}
				}
				if (E->getEnemyHealth() <= 0)
				{
					E->active = false;
					sound->play3D("../irrKlang/media/Death.mp3", vec3df(0, 0, 0), false);
				}
			}
		}

		static float recover = 0.f;
		static float playSoundPU = 0.f;
		if ((FApos - camera.position).Length() < 10)
		{
			if (!Pistol.getReloading() && !Sniper.getReloading() && !SMG.getReloading())
			{
				restocking = true;
				Pistol.reload((float)dt);
				Sniper.reload((float)dt);
				SMG.reload((float)dt);
				restockTime -= dt;
				recover += dt;
				playSoundPU += dt;
				if (recover >= 0.2)
				{
					moving += 5 * dt;
					recover = 0.f;

				}

				if (playSoundPU >= 1)
				{
					sound->play3D("../irrKlang/media/PowerUp.wav", vec3df(0, 0, 0), false);
					playSoundPU = 0.f;
				}
			}
		}
		else
		{
			restocking = false;
		}

		if (restockTime <= 0)
		{
			FApos.x = Math::RandFloatMinMax(-1000, 1000);
			FApos.z = Math::RandFloatMinMax(-1000, 1000);
			restockTime = 10.f;
		}

		//================Minimap==============//
		rotateAngle -= (float)Application::camera_yaw;


		if (weapon.returnSwordConfirmation() == true)
			Sword.update((float)dt, weapon, restocking, moving);
		else if (weapon.returnPistolConfirmation() == true)
			Pistol.update((float)dt, weapon, restocking, moving);
		else if (weapon.returnSniperConfirmation() == true)
			Sniper.update((float)dt, weapon, restocking, moving);
		else
			SMG.update((float)dt, weapon, restocking, moving);

		if (enemy.getEnemyHealth() <= 0)
			enemy.active = false;

		BulletUpdate((float)dt);
		weapon.update(dt);
		enemy.update((float)dt, camera.position);

		SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(meshList[GEO_SPRITE_ANIMATION]);
		if (sa)
		{
			sa->Update(dt);
		}
	}
}

static const float SKYBOXSIZE = 9000.f;

void SceneText::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
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
	if (!mesh || mesh->textureID <= 0)
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
	for (unsigned i = 0; i < text.length(); ++i)
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

void SceneText::RenderMeshIn2D(Mesh *mesh, bool enableLight, Vector3 size, Vector3 translate, bool rotate)
{
	Mtx44 ortho;
	ortho.SetToOrtho(-80, 80, -60, 60, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Scale(size.x, size.y, 0);
	modelStack.Translate(translate.x, translate.y, 0);
	if (rotate)
		modelStack.Rotate(rotateAngle, 0, 0, 1);

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

void SceneText::RenderEnemyMeshIn2D(Mesh *mesh, bool enableLight, Vector3 size, Vector3 translate, bool rotate)
{
	Mtx44 ortho;
	ortho.SetToOrtho(-80, 80, -60, 60, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();

	float translatey = 15;

	if (rotate)
		modelStack.Rotate(-rotateAngle, 0, 0, 1);

	modelStack.Translate(translate.x, translate.y + translatey, 0);

	modelStack.Scale(size.x, size.y, 0);

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

void SceneText::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if (enableLight && bLightEnabled)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);

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
	/*modelStack.PushMatrix();
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
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();*/

	/*modelStack.PushMatrix();
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Translate(0, , -SKYBOXSIZE / 2 + 2.f);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();*/

	modelStack.PushMatrix();
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Translate(0, 0, -10);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();
}

void SceneText::RenderHUD()
{
	RenderMeshIn2D(meshList[AvatarIcon], true, Vector3(13.0f, 13.0f, 0), Vector3(-5.5f, 4.0f, 0), false); //Avatar icon

	RenderMeshIn2D(meshList[HudBackground], true, Vector3(85.0f, 13.0f, 0), Vector3(-0.25f, 4.0f, 0), false);//background

	RenderTextOnScreen(meshList[GEO_TEXT], "Setsuna", Color(1.0f, 1.0f, 1.0f), 3.0f, 9.5f, 55.7f);//Name

	if (weapon.returnSwordConfirmation() == false)
	{
		RenderMeshIn2D(meshList[HudBackground], true, Vector3(20.0f, 5.0f, 0), Vector3(3.49f, -11.5f, 0), false);//background for ready screen
	}

	//===============Weapon Chosen==============//
	RenderMeshIn2D(meshList[HudBackground], true, Vector3(13.0f, 13.0f, 0), Vector3(-4.4f, 2.9f, 0), false);//bakcground for ammo
	RenderMeshIn2D(meshList[HudBackground], true, Vector3(13.0f, 13.0f, 0), Vector3(-4.4f, 1.8f, 0), false);//background for round
	//==============Round============//
	RenderMeshIn2D(meshList[RoundIcon], true, Vector3(13.0f, 13.0f, 0), Vector3(-5.5f, 1.8f, 0), false);//Round icon

	//=====================SWORD=====================//
	if (weapon.returnSwordConfirmation() == true)
	{
		RenderMeshIn2D(meshList[SwordIcon], true, Vector3(13.0f, 13.0f, 0), Vector3(-5.5f, 2.9f, 0), false);//Sword icon

		RenderTextOnScreen(meshList[GEO_TEXT], "--", Color(1.0f, 1.0f, 1.0f), 3.0f, 9.5f, 47.5f);//Sword got no bullet, so i used --

		RenderTextOnScreen(meshList[GEO_TEXT], "--", Color(1.0f, 1.0f, 1.0f), 3.0f, 9.5f, 40.0f);//Sword got no round, so i used --

		RenderMeshIn2D(meshList[WeaponIcon_Sword], true, Vector3(40.5f, 40.5f, 0), Vector3(-0.7f, 0.925f, 0), false);// This is the icon for close ranged weapon

		if (Application::IsKeyPressed('R'))
		{
			RenderMeshIn2D(meshList[HudBackground], true, Vector3(80.0f, 10.0f, 0), Vector3(0.01f, 0.2f, 0), false);//background for reload screen
			RenderTextOnScreen(meshList[GEO_TEXT], "Error", Color(1.0f, 1.0f, 1.0f), 3.0f, 33.5f, 29.5f);
		}
	}//=====================PISTOL=====================//
	else if (weapon.returnPistolConfirmation() == true)//player is using pistol
	{
		RenderMeshIn2D(meshList[BulletIcon], true, Vector3(13.0f, 13.0f, 0), Vector3(-5.5f, 2.9f, 0), false);//Bullet icon

		if (Pistol.getBullet() < 10)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], std::to_string((long long)Pistol.getBullet()), Color(1.0f, 1.0f, 1.0f), 3.0f, 10.8f, 47.5f);
		}
		else
		{
			RenderTextOnScreen(meshList[GEO_TEXT], std::to_string((long long)Pistol.getBullet()), Color(1.0f, 1.0f, 1.0f), 3.0f, 9.5f, 47.5f);
		}

		RenderTextOnScreen(meshList[GEO_TEXT], std::to_string((long long)Pistol.getRounds()), Color(1.0f, 1.0f, 1.0f), 3.0f, 10.8f, 40.0f);

		RenderMeshIn2D(meshList[WeaponIcon_Pistol], true, Vector3(40.5f, 40.5f, 0), Vector3(-0.7f, 0.925f, 0), false);// This is the icon for long ranged weapon

		if (Pistol.getReloading() == true) //reloading
		{
			RenderMeshIn2D(meshList[HudBackground], true, Vector3(80.0f, 10.0f, 0), Vector3(0.01f, 0.2f, 0), false);//background for reload screen
			RenderTextOnScreen(meshList[GEO_TEXT], "Reload in", Color(1.0f, 1.0f, 1.0f), 3.0f, 25.0f, 29.5f);
			RenderTextOnScreen(meshList[GEO_TEXT], std::to_string((long long)Pistol.getReloadTime()), Color(1.0f, 1.0f, 1.0f), 3.0f, 55.0f, 29.5f);
		}

		if (Pistol.getReadyToShoot() == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Ready", Color(1.0f, 1.0f, 1.0f), 2.0f, 70.7f, 0.3f);
		}
	}
	//=====================SNIPER=====================//
	else if (weapon.returnSniperConfirmation() == true)//player is using sniper
	{
		RenderMeshIn2D(meshList[BulletIcon], true, Vector3(13.0f, 13.0f, 0), Vector3(-5.5f, 2.9f, 0), false);//Bullet icon

		RenderTextOnScreen(meshList[GEO_TEXT], std::to_string((long long)Sniper.getBullet()), Color(1.0f, 1.0f, 1.0f), 3.0f, 10.8f, 47.5f);

		RenderTextOnScreen(meshList[GEO_TEXT], std::to_string((long long)Sniper.getRounds()), Color(1.0f, 1.0f, 1.0f), 3.0f, 10.8f, 40.0f);

		RenderMeshIn2D(meshList[WeaponIcon_Sniper], true, Vector3(40.5f, 40.5f, 0), Vector3(-0.7f, 0.925f, 0), false);// This is the icon for logn ranged weapon

		if (Sniper.getReloading() == true)
		{
			RenderMeshIn2D(meshList[HudBackground], true, Vector3(80.0f, 10.0f, 0), Vector3(0.01f, 0.2f, 0), false);//background for reload screen
			RenderTextOnScreen(meshList[GEO_TEXT], "Reload in", Color(1.0f, 1.0f, 1.0f), 3.0f, 25.0f, 29.5f);
			RenderTextOnScreen(meshList[GEO_TEXT], std::to_string((long long)Sniper.getReloadTime()), Color(1.0f, 1.0f, 1.0f), 3.0f, 55.0f, 29.5f);
		}

		if (Sniper.getReadyToShoot() == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Ready", Color(1.0f, 1.0f, 1.0f), 2.0f, 70.7f, 0.3f);
		}
	}
	//=====================SMG=====================//
	else if (weapon.returnSMGConfirmation() == true)//player is using SMG
	{
		RenderMeshIn2D(meshList[BulletIcon], true, Vector3(13.0f, 13.0f, 0), Vector3(-5.5f, 2.9f, 0), false);//Bullet icon

		if (SMG.getBullet() < 10)//Arranging bullet number to middle if it is less than 10
		{
			RenderTextOnScreen(meshList[GEO_TEXT], std::to_string((long long)SMG.getBullet()), Color(1.0f, 1.0f, 1.0f), 3.0f, 10.8f, 47.5f);
		}
		else
		{
			RenderTextOnScreen(meshList[GEO_TEXT], std::to_string((long long)SMG.getBullet()), Color(1.0f, 1.0f, 1.0f), 3.0f, 9.5f, 47.5f);
		}


		RenderTextOnScreen(meshList[GEO_TEXT], std::to_string((long long)SMG.getRounds()), Color(1.0f, 1.0f, 1.0f), 3.0f, 10.8f, 40.0f);

		RenderMeshIn2D(meshList[WeaponIcon_SMG], true, Vector3(40.5f, 40.5f, 0), Vector3(-0.7f, 0.925f, 0), false);// This is the icon for logn ranged weapon

		if (SMG.getReloading() == true)//Reloading
		{
			RenderMeshIn2D(meshList[HudBackground], true, Vector3(80.0f, 10.0f, 0), Vector3(0.01f, 0.2f, 0), false);//background for reload screen
			RenderTextOnScreen(meshList[GEO_TEXT], "Reload in", Color(1.0f, 1.0f, 1.0f), 3.0f, 25.0f, 29.5f);
			RenderTextOnScreen(meshList[GEO_TEXT], std::to_string((long long)SMG.getReloadTime()), Color(1.0f, 1.0f, 1.0f), 3.0f, 55.0f, 29.5f);
		}

		if (SMG.getReadyToShoot() == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Ready", Color(1.0f, 1.0f, 1.0f), 2.0f, 70.7f, 0.3f);
		}
	}

	if (weapon.returnSwordConfirmation() == true)
	{
		RenderMeshIn2D(meshList[Weapon_Sword], false, Vector3(90.f, 90.f, 0), Vector3(0.56f, -0.35f, 0), false);
	}
	if (Pistol.getReloading() == false)
	{
		if (weapon.returnPistolConfirmation() == true && restocking == false)
		{
			modelStack.PushMatrix();
			RenderMeshIn2D(meshList[Weapon_Pistol], false, Vector3(70.f, 70.f, 0), Vector3(0.7f, -0.4f, 0), false);
			modelStack.PopMatrix();
		}
	}
	if (Sniper.getReloading() == false)
	{
		if (weapon.returnSniperConfirmation() == true && restocking == false)
		{
			modelStack.PushMatrix();
			RenderMeshIn2D(meshList[Weapon_Sniper], false, Vector3(70.f, 70.f, 0), Vector3(0.7f, -0.4f, -1), false);
			modelStack.PopMatrix();
		}
	}

	if (restocking == true)
	{
		RenderMeshIn2D(meshList[HudBackground], true, Vector3(80.0f, 10.0f, 0), Vector3(0.01f, 0.2f, 0), false);//background for reload screen
		RenderTextOnScreen(meshList[GEO_TEXT], "Restocking", Color(1.0f, 1.0f, 1.0f), 3.0f, 26.5f, 29.5f);
	}

	//==================CrossHair=============//
	RenderMeshIn2D(meshList[crosshair], true, Vector3(5.0f, 5.0f, 0), Vector3(0, 0, 0), false);

	if (SMG.getReloading() == false)
	{
		if (weapon.returnSMGConfirmation() == true && restocking == false)
		{
			modelStack.PushMatrix();
			RenderMeshIn2D(meshList[Weapon_SMG], false, Vector3(100.f, 100.f, 0), Vector3(0.3f, -0.2f, 0), false);
			modelStack.PopMatrix();
		}
	}
}

void SceneText::RenderEnemyModel(CEnemy * passIn)
{
	modelStack.PushMatrix();
	modelStack.Translate(passIn->getEnemyPos().x, passIn->getEnemyPos().y, passIn->getEnemyPos().z);
	modelStack.Rotate(passIn->getRotateAngle(), 0, 1, 0);
	modelStack.Scale(10, 10, 10);
	RenderMesh(meshList[GEO_SPRITE_ANIMATION], false);
	modelStack.PopMatrix();
}

void SceneText::RenderSkyPlane(Mesh* mesh, Color color, int slices, float PlanetRadius, float height, float hTile, float vTile)
{
	modelStack.PushMatrix();

	modelStack.Translate(0, 1800.f, -0);

	RenderMesh(meshList[GEO_SKYPLANE], false);

	modelStack.PopMatrix();
}

void SceneText::Render()
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

	if (lights[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[0].position.x, lights[0].position.y, lights[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (lights[0].type == Light::LIGHT_SPOT)
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
	if (lights[1].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[1].position.x, lights[1].position.y, lights[1].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (lights[1].type == Light::LIGHT_SPOT)
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

	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_AXES], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(lights[0].position.x, lights[0].position.y, lights[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	for (vector<CAmmo*>::iterator it = bulletList.begin(); it != bulletList.end(); ++it)
	{
		CAmmo *BY = (CAmmo*)*it;

		if (BY->active)
		{
			modelStack.PushMatrix();
			modelStack.Translate(BY->bulletPosition.x + BY->bulletDirection.x * 2, BY->bulletPosition.y + BY->bulletDirection.y * 3, BY->bulletPosition.z + BY->bulletDirection.z * 2);
			modelStack.Scale(0.1, 0.1, 0.1);
			RenderMesh(meshList[GEO_LIGHTBALL], false);
			modelStack.PopMatrix();
		}
	}

	SetHUD(true);

	//On screen text
	std::ostringstream ss;
	ss.precision(5);
	ss << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 6);
	std::ostringstream ss1;
	ss1.precision(4);
	ss1 << "Light(" << lights[0].position.x << ", " << lights[0].position.y << ", " << lights[0].position.z << ")";
	RenderTextOnScreen(meshList[GEO_TEXT], ss1.str(), Color(0, 1, 0), 3, 0, 3);
	RenderTextOnScreen(meshList[GEO_TEXT], "Hello Screen", Color(0, 1, 0), 3, 0, 0);

	//RenderMeshIn2D(m_cMinimap->GetAvatar(), false, Vector3(15.0f, 15.0f, 0), Vector3(0, 0, 0), true);

	//RenderMeshIn2D(m_cMinimap->GetBorder(), false, Vector3(15.0f, 15.0f, 0), Vector3(0, 0, 0), true);

	SetHUD(false);


	//===============HEALTH===========//
	for (unsigned a = 0; a < moving; ++a)//Healthbar
	{
		RenderMeshIn2D(meshList[Healthbar], true, Vector3(0.8f, 2.0f, 0), Vector3(-76.0f + a, 25.0f, 0), false);
	}

	RenderSkyPlane(meshList[GEO_SKYPLANE], Color(1, 1, 1), 128, 200.0f, 1000.0f, 1.0f, 1.0f);
	RenderSkybox(); //RenderSKybox

	if (moving <= 0)
	{
		RenderMeshIn2D(meshList[HudBackground], true, Vector3(115.0f, 25.0f, 0), Vector3(0.1f, 0.f, 0), false);//background for reload screen
		RenderTextOnScreen(meshList[GEO_TEXT], "You Have Died :D", Color(1.0f, 1.0f, 1.0f), 3.0f, 22.5f, 29.5f);
		RenderTextOnScreen(meshList[GEO_TEXT], "Press P to continue", Color(1.0f, 1.0f, 1.0f), 3.0f, 18.5f, 25.5f);
	}

	for (vector<CEnemy *>::iterator it = enemyList.begin(); it != enemyList.end(); it++)
	{
		CEnemy * E = (CEnemy*)*it;
		if (E->active == true)
		{
			RenderEnemyModel(E);
		}
	}
	modelStack.PushMatrix();
	modelStack.Translate(FApos.x, FApos.y - 9, FApos.z);
	modelStack.Scale(2, 2, 2);
	RenderMesh(meshList[firstAid], false);
	modelStack.PopMatrix();
	RenderMeshIn2D(m_cMinimap->GetBackground(), false, Vector3(35.f, 35.0f, 0), Vector3(-1.8, -1.3, 0), true);
	RenderHUD(); //Render HUD
}

void SceneText::Exit()
{
	// Cleanup VBO
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i])
			delete meshList[i];
	}
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}