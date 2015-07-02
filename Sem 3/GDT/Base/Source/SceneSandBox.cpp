#include "SceneSandBox.h"
#include "GL\glew.h"

#include <sstream>
#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"

SceneSandBox::SceneSandBox():
	m_cMap(NULL),
	hero_InMidAir_Up(false),
	hero_InMidAir_Down(false),
	jumpspeed(0),
	mapOffSet_x(0),
	mapOffset_y(0),
	tileOffSet_x(0),
	tileOffset_y(0),
	mapFineOffSet_x(0), 
	mapFineOffset_y(0)
{
}

SceneSandBox::~SceneSandBox()
{
	/*if (camera2 != NULL)
	{
	delete camera2;
	camera2 = NULL;
	}*/
	if (m_cMap)
	{
		delete m_cMap;
		m_cMap = NULL;
	}
}

void SceneSandBox::SetMesh()
{
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
	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(0, 0, 0), 18, 36, 1.f);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(0.5, 0.5, 0.5), 1);
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

	meshList[GEO_TERRAIN] = MeshBuilder::GenerateTerrain("Terrain", "Image//terrain.raw", m_heightMap);
	meshList[GEO_TERRAIN]->textureArray[0] = LoadTGA("Image//bottom.tga");
	meshList[GEO_TERRAIN]->textureArray[1] = LoadTGA("Image//Wet Ground.tga");

	meshList[GEO_TREE] = MeshBuilder::GenerateOBJ("Tree", "OBj//tree.obj");
	meshList[GEO_TREE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_TREE]->material.kDiffuse.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_TREE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_TREE]->material.kShininess = 10.f;
	meshList[GEO_TREE]->textureArray[0] = LoadTGA("Image//tree.tga");

	meshList[GEO_CHURCH] = MeshBuilder::GenerateOBJ("Tree", "OBj//church.obj");
	meshList[GEO_CHURCH]->textureArray[0] = LoadTGA("Image//church.tga");

	meshList[GEO_SPRITE_ANIMATION] = MeshBuilder::GenerateSpriteAnimation("cat", 1, 6);
	meshList[GEO_SPRITE_ANIMATION]->textureArray[0] = LoadTGA("Image//leon.tga");
	SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(meshList[GEO_SPRITE_ANIMATION]);

	if (sa)
	{
		sa->m_anim = new Animation();
		sa->m_anim->Set(0, 4, 0, 1.f);
	}

	meshList[Soccer] = MeshBuilder::GenerateSpriteAnimation("Soccer", 6, 7);
	meshList[Soccer]->textureArray[0] = LoadTGA("Image//soccer.tga");
	SpriteAnimation *sa2 = dynamic_cast<SpriteAnimation*>(meshList[Soccer]);

	if (sa2)
	{
		sa2->m_anim = new Animation();
		sa2->m_anim->Set(0, 30, 0, 0.2f);
	}

	meshList[GEO_SKYPLANE] = MeshBuilder::GenerateSkyPlane("GEO_SKYPLANE", Color(1, 1, 1), 128, 200.0f, 2000.0f, 1.0f, 1.0f);
	meshList[GEO_SKYPLANE]->textureArray[0] = LoadTGA("Image//top2.tga");

	meshList[BulletIcon] = MeshBuilder::GenerateQuad("Bullet Icon", Color(1, 1, 1), 1.0f);
	meshList[BulletIcon]->textureArray[0] = LoadTGA("Image//GGOGun.tga");

	meshList[GEO_BACKGROUND] = MeshBuilder::Generate2DMesh("GEO_BACKGROUND", Color(1, 1, 1), 0.0f, 0.0f, 800.0f, 600.0f);
	meshList[GEO_BACKGROUND]->textureID = LoadTGA("Image//sky.tga");

	meshList[GEO_TILEGROUND] = MeshBuilder::Generate2DMesh("GEO_TILEGROUND", Color(1, 1, 1), 0.0f, 0.0f, 25.f, 25.f);
	meshList[GEO_TILEGROUND]->textureID = LoadTGA("Image//tile1_ground.tga");

	meshList[GEO_TILEHERO] = MeshBuilder::Generate2DMesh("tile2_hero", Color(1, 1, 1), 0.0f, 0.0f, 25.f, 25.f);
	meshList[GEO_TILEHERO]->textureID = LoadTGA("Image//marioalpha.tga");

	meshList[GEO_TILETREE] = MeshBuilder::Generate2DMesh("GEO_TILETREE", Color(1, 1, 1), 0.0f, 0.0f, 25.0f, 25.0f);
	meshList[GEO_TILETREE]->textureID = LoadTGA("Image//tile3_tree.tga");

	//Initalise the new tile map
	m_cMap = new CMap();
	m_cMap->Init(600, 800, 24, 32, 600, 1600);
	m_cMap->LoadMap("Image//MapDesign.csv");

	meshList[crosshair] = MeshBuilder::Generate2DMesh("Crosshair", Color(1, 1, 1), 0.f, 0.f, 5.f, 5.f);
	meshList[crosshair]->textureID = LoadTGA("Image//Crosshair 3.tga");
}

void SceneSandBox::SetParameters()
{

	mSpeed = 1.f;
	OBJCount = 0;
	gravity = Vector3(0, -9.8f, 0);


	HeroPos.x = 50;
	HeroPos.y = 575 -  100;
}

float SceneSandBox::calculatingFPS(float dt)
{
	return (float)(1.f / dt);
}

void SceneSandBox::Init()
{
	// Black background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	glEnable(GL_CULL_FACE);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_SAMPLE_ALPHA_TO_COVERAGE);

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

	fogColor = (1.f, 0.f, 0.f);
	fogStart = 10.f;
	fogEnd = 1000.f;
	fogDensity = 10.f;
	fogType = 0;
	fogEnabled = 0;//Enable

	glUniform3fv(m_parameters[U_COLOR_FOG], 1, &fogColor.r);
	glUniform3fv(m_parameters[U_COLOR_FOG2], 1, &fogColor.g);
	glUniform3fv(m_parameters[U_COLOR_FOG3], 1, &fogColor.b);
	glUniform1f(m_parameters[U_START_FOG], fogStart);
	glUniform1f(m_parameters[U_END_FOG], fogEnd);
	glUniform1f(m_parameters[U_DENSITY_FOG], fogDensity);
	glUniform1f(m_parameters[U_TYPE_FOG], fogType);
	glUniform1f(m_parameters[U_ENABLE_FOG], fogEnabled);

	camera.Init(Vector3(-104, 110, -433), Vector3(-104, 110, 0), Vector3(0, 1, 0));

	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}

	SetMesh();
	SetParameters();

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	rotateAngle = rotateAngle2 = 0;

	bLightEnabled = true;
}

Particle* SceneSandBox::fetchOBJ()
{
	for (std::vector<Particle *>::iterator it = ParticleList.begin(); it != ParticleList.end(); ++it)
	{
		Particle *p = (Particle *)*it;
		if (!p->active)
		{
			p->active = true;
			//++m_objectCount;
			return p;
		}
	}
	for (unsigned i = 0; i < 10; ++i)
	{
		for (unsigned a = 0; a < 2000; a++)
		{
			float X = Math::RandFloatMinMax(-1000, 1000);
			float Z = Math::RandFloatMinMax(-1000, 1000);
			Vector3 vel;
			vel.x = Math::RandFloatMinMax(-10, 10);
			vel.y = Math::RandFloatMinMax(-10, 10);
			vel.z = Math::RandFloatMinMax(-10, 10);
			Material newMaterial;
			newMaterial.kAmbient.Set(0.1f, 0.1f, 0.1f);
			newMaterial.kDiffuse.Set(0.5f, 0.5f, 0.5f);
			newMaterial.kSpecular.Set(0.5f, 0.5f, 0.5f);
			newMaterial.kShininess = 10.f;
			float mass = Math::RandFloatMinMax(0, 10);

			Particle * particle = new Particle(Vector3(X, 320, Z), vel, 10, true, newMaterial, mass);
			ParticleList.push_back(particle);
		}
	}
	Particle *p = ParticleList.back();
	p->active = true;
	//++m_objectCount;
	return p;
}

/******************************************************************************
Update Camera position
******************************************************************************/
void SceneSandBox::UpdateCameraStatus(const unsigned char key)
{
	camera.UpdateStatus(key);
}

void SceneSandBox::Update(double dt)
{
	if (Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

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
		//bLightEnabled = true;
		fogColor.r += 1;
	}
	else if (Application::IsKeyPressed('9'))
	{
		//bLightEnabled = false;
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

	if (Application::IsKeyPressed('9'))
	{
		mSpeed = Math::Max(0.f, mSpeed - 0.1f);
	}
	if (Application::IsKeyPressed('0'))
	{
		mSpeed += 0.1f;
	}
	dt *= mSpeed;

	SpriteAnimation *sa = dynamic_cast<SpriteAnimation*>(meshList[GEO_SPRITE_ANIMATION]);

	if (sa)
	{
		sa->Update(dt);
	}

	SpriteAnimation *sa2 = dynamic_cast<SpriteAnimation*>(meshList[Soccer]);

	if (sa2)
	{
		sa2->Update(dt);
	}

	/*static Vector3 HM;
	HM.Set(camera.position.x, camera.position.y, camera.position.z);
	HM.y = 350.f * ReadHeightMap(m_heightMap, HM.x / 2000.f, HM.z / 2000.f) + 10.f;
	camera.position.y = HM.y;
	camera.target.y += HM.y - camera.position.y;*/

	leonPos.y = 350.f * ReadHeightMap(m_heightMap, leonPos.x / 2000.f, leonPos.z / 2000.f) + 5.f;
	cubePos.y = 350.f * ReadHeightMap(m_heightMap, cubePos.x / 2000.f, cubePos.z / 2000.f) + 5.f;

	if (leonPos.z < -100)
	{
		leonPos.z += 10 * dt;
	}
	else
	{
		leonPos.z = -400;
	}


	static float tempY = 0.f;
	tempY = 350.f * ReadHeightMap(m_heightMap, camera.position.x / 2000.f, camera.position.z / 2000.f) + 10.f;
	camera.tempY = tempY;
	if (!camera.getJumpStatus())
	{
		static float diff = 0.f;
		diff = tempY - camera.position.y;
		camera.position.y += diff * dt * 20;
		camera.target.y += diff * dt * 20;
	}

	/*camera.position.x = cubePos.x - cos(Application::camera_yaw) * cos(Application::camera_pitch) * 3;
	camera.position.y = cubePos.y + sin(Application::camera_pitch) * 10;
	camera.position.z = cubePos.z - sin(Application::camera_yaw) * cos(Application::camera_pitch) * 3;
	camera.target = cubePos;*/

	for (vector<Particle*>::iterator it = ParticleList.begin(); it != ParticleList.end(); it++)
	{
		Particle * particle = (Particle*)*it;
		if (particle->active == true)
		{
			particle->update(dt);
		}
	}

	if (Application::IsKeyPressed('W'))
		HeroMoveUpDown(true, 1.f);
	if (Application::IsKeyPressed('S'))
		HeroMoveUpDown(false, 1.f);
	if (Application::IsKeyPressed('A'))
		HeroMoveLeftRIght(true, 1.f);
	if (Application::IsKeyPressed('D'))
		HeroMoveLeftRIght(false, 1.f);
	if (Application::IsKeyPressed(' '))
		HeroJump();

	HeroUpdate();
}

static const float SKYBOXSIZE = 1000.f;

void SceneSandBox::RenderText(Mesh* mesh, std::string text, Color color)
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

void SceneSandBox::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

void SceneSandBox::RenderMeshIn2D(Mesh *mesh, bool enableLight, float sizeX, float sizeY, float x, float y, float z)
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

	//Mtx44 MVP, modelview, modelView_inverse_transpose;

	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);

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


void SceneSandBox::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
	if (enableLight && bLightEnabled)
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
	///*if(mesh->textureID > 0)
	//{
	//	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	//	glActiveTexture(GL_TEXTURE0);
	//	glBindTexture(GL_TEXTURE_2D, mesh->textureID);
	//	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	//}
	//else
	//{
	//	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 0);
	//}
	//mesh->Render();
	//if(mesh->textureID > 0)
	//{
	//	glBindTexture(GL_TEXTURE_2D, 0);
	//}*/
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

void SceneSandBox::RenderSkybox()
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

void SceneSandBox::view()
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

void SceneSandBox::RenderSkyPlane(Mesh* mesh, Color color, int slices, float PlanetRadius, float height, float hTile, float vTile)
{
	modelStack.PushMatrix();

	modelStack.Translate(500.f, 1800.f, -500.f);

	//modelStack.Scale(0.9, 0.9, 0.9);

	RenderMesh(meshList[GEO_SKYPLANE], false);

	modelStack.PopMatrix();
}

void SceneSandBox::RenderTerrain()
{
	Vector3 pos;
	modelStack.PushMatrix();
	modelStack.Scale(2000.0f, 350.f, 2000.f);
	RenderMesh(meshList[GEO_TERRAIN], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(mapPos.x + 5.f, mapPos.y + 2.f, mapPos.z);
	RenderMesh(meshList[GEO_CUBE], false);
	modelStack.PopMatrix();
}

void SceneSandBox::Render2DMesh(Mesh *mesh, bool enableLight, float size, float x, float y, bool rotate)
{
	Mtx44 ortho;
	ortho.SetToOrtho(0, 800, 0, 600, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);
	if (rotate)
		modelStack.Rotate(rotateAngle, 0, 0, 1);

	Mtx44 MVP, modelView, modelView_inverse_transpose;
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	/*Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	modelView = viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);*/


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

void SceneSandBox::RenderBackground()
{
	Render2DMesh(meshList[GEO_BACKGROUND], false, 1.0f);
}

void SceneSandBox::RenderTileMap()
{
	//If i want to centralise the character, i can play around here
	int m = 0;
	mapFineOffSet_x = mapOffSet_x % m_cMap->GetTileSize();
	for (int i = 0; i < m_cMap->GetNumOfTiles_Height(); i++)
	{
		for (int k = 0; k < m_cMap->GetNumOfTiles_Width() + 1; k++)
		{
			m = tileOffSet_x + k;
			// If we have reached the right side of the Map, then do not display the extra column of tiles.
			if ((tileOffSet_x + k) >= m_cMap->getNumOfTiles_MapWidth())
				break;
			if (m_cMap->theScreenMap[i][m] == 1)
			{
				Render2DMesh(meshList[GEO_TILEGROUND], false, 1.0f, k*m_cMap->GetTileSize() - mapFineOffSet_x, 575 - i*m_cMap->GetTileSize());
			}
			else if (m_cMap->theScreenMap[i][m] == 2)
			{
				Render2DMesh(meshList[GEO_TILETREE], false, 1.0f, k*m_cMap->GetTileSize() - mapFineOffSet_x, 575 - i*m_cMap->GetTileSize());
			}
		}
	}

	Render2DMesh(meshList[GEO_TILEHERO], false, 1.0f, HeroPos.x, 575 - HeroPos.y);
}

/********************************************************************************
Hero Update
********************************************************************************/
void SceneSandBox::HeroUpdate()
{
	// Update Hero's info
	if (hero_InMidAir_Up == false && hero_InMidAir_Down == false)
	{
		//Don't Jump

		//int checkPosition_X = (int)floor((float)mapOffSet_x + HeroPos.x / m_cMap->GetTileSize());
		int checkPosition_X = (int)((mapOffSet_x + HeroPos.x) / m_cMap->GetTileSize());
		int checkPosition_Y = (int)ceil(((float)HeroPos.y + m_cMap->GetTileSize()) / m_cMap->GetTileSize());
		if (m_cMap->theScreenMap[checkPosition_Y][checkPosition_X] != 1)
		{
			hero_InMidAir_Up = false;
			hero_InMidAir_Down = true;
			jumpspeed = 10;
		}
	}
	else if (hero_InMidAir_Up == true && hero_InMidAir_Down == false)
	{
		// Check if the hero can move up into mid air...
		//int checkPosition_X = (int)ceil((float)mapOffSet_x + HeroPos.x / m_cMap->GetTileSize());
		int checkPosition_X = (int)((mapOffSet_x + HeroPos.x) / m_cMap->GetTileSize());
		int checkPosition_Y = (int)floor(((float)HeroPos.y - jumpspeed) / m_cMap->GetTileSize());
		if (m_cMap->theScreenMap[checkPosition_Y][checkPosition_X + 1] == 1 || m_cMap->theScreenMap[checkPosition_Y][checkPosition_X] == 1)
		{
			HeroPos.y = (checkPosition_Y + 1) * m_cMap->GetTileSize();
			hero_InMidAir_Up = false;
			jumpspeed = 0;
		}
		else
		{
			HeroPos.y -= jumpspeed;
			jumpspeed -= 1;
			if (jumpspeed == 0)
			{
				hero_InMidAir_Up = false;
				hero_InMidAir_Down = true;
			}
		}
	}
	else if (hero_InMidAir_Up == false && hero_InMidAir_Down == true)
	{
		//int checkPosition_X = (int)ceil(((float)mapOffSet_x + HeroPos.x / m_cMap->GetTileSize()));
		int checkPosition_X = (int)((mapOffSet_x + HeroPos.x) / m_cMap->GetTileSize());
		int checkPosition_Y = (int)ceil(((float)HeroPos.y + jumpspeed) / m_cMap->GetTileSize());
		if (m_cMap->theScreenMap[checkPosition_Y][checkPosition_X] == 1 || m_cMap->theScreenMap[checkPosition_Y][checkPosition_X + 1] == 1)
		{
			// Since the new position does not allow the hero to move into, then go back to the old position
			HeroPos.y = (checkPosition_Y - 1) * m_cMap->GetTileSize();
			hero_InMidAir_Down = false;
			jumpspeed = 0;
		}
		else
		{
			HeroPos.y += jumpspeed;
			jumpspeed += 1;
		}
	}

	constrainHero(25, 750, 25, 575, 1.f);
	tileOffSet_x = (int)(mapOffSet_x / m_cMap->GetTileSize());
	if (tileOffSet_x + m_cMap->GetNumOfTiles_Width() > m_cMap->getNumOfTiles_MapWidth())
		tileOffSet_x = m_cMap->getNumOfTiles_MapWidth() - m_cMap->GetNumOfTiles_Width();
}

/********************************************************************************
Hero Jump
********************************************************************************/
void SceneSandBox::HeroJump()
{
	if (hero_InMidAir_Up == false && hero_InMidAir_Down == false)
	{
		hero_InMidAir_Up = true;
		jumpspeed = 15;
	}
}

/********************************************************************************
Hero Move Up Down
********************************************************************************/
void SceneSandBox::HeroMoveUpDown(const bool mode, const float timeDiff)
{
	if (mode)
	{
		//Going Up
		//HeroPos.y = HeroPos.y - (int)(5.0f * timeDiff);
	}
	else
	{
		//Going Down
		//HeroPos.y = HeroPos.y + (int)(5.0f * timeDiff);
	}
}

/********************************************************************************
Hero Move Left Right
********************************************************************************/
void SceneSandBox::HeroMoveLeftRIght(const bool mode, const float timeDiff)
{
	int checkPosition_X = (int)ceil(((float)HeroPos.x / m_cMap->GetTileSize()));
	int checkPosition_Y = (int)ceil(((float)HeroPos.y + jumpspeed) / m_cMap->GetTileSize());

	if (mode)
	{
		if (m_cMap->theScreenMap[checkPosition_Y][checkPosition_X - 1] != 1)
			HeroPos.x = HeroPos.x - (int)(5.0f * timeDiff);
	}
	else
	{
		if (m_cMap->theScreenMap[checkPosition_Y][checkPosition_X] != 1)
			HeroPos.x = HeroPos.x + (int)(5.0f * timeDiff);
	}
}

void SceneSandBox::constrainHero(const int leftBorder, const int rightBorder, const int topBorder, const int bottomBorder, float timeDiff)
{
	if (HeroPos.x < leftBorder)
	{
		HeroPos.x = leftBorder;
		mapOffSet_x = mapOffSet_x - (int)(5.f * timeDiff);
		if (mapOffSet_x < 0)
			mapOffSet_x = 0;
	}
	else if (HeroPos.x > rightBorder)
	{
		HeroPos.x = rightBorder;
		mapOffSet_x = mapOffSet_x + (int)(5.f * timeDiff);
		if (mapOffSet_x > 800)
			mapOffSet_x = 800;
	}

	if (HeroPos.y < topBorder)
	{
		HeroPos.y = topBorder;
	}
	else if (HeroPos.y > bottomBorder)
	{
		HeroPos.y = bottomBorder;
	}
}


void SceneSandBox::Render()
{
	view();

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


	//Render Tile map
	RenderTileMap();
	//Render background image
	RenderBackground();

	//On screen text
	std::ostringstream ss;
	ss.precision(5);
	ss << "tileOffset_x: " << tileOffSet_x;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 0, 6);

	std::ostringstream ss1;
	ss1.precision(5);
	ss1 << "mapOffset_x: " << mapOffSet_x;
	RenderTextOnScreen(meshList[GEO_TEXT], ss1.str(), Color(0, 1, 0), 3, 0, 3);
	

	//==============Testing===============//
}

void SceneSandBox::Exit()
{
	// Cleanup VBO
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i])
			delete meshList[i];
	}

	while (!OBJList.empty())
	{
		COBJ* obj = OBJList.back();
		delete obj;
		OBJList.pop_back();
	}
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}