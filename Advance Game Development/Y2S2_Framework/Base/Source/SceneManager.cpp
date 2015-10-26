#include "SceneManager.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>

CSceneManager::CSceneManager(void)
	: m_cMinimap(NULL)
	, m_window_width(800)
	, m_window_height(600)
{
}

CSceneManager::CSceneManager(const int m_window_width, const int m_window_height)
	: m_cMinimap(NULL),
	m_cAvatar(NULL)
{
	this->m_window_width = m_window_width;
	this->m_window_height = m_window_height;
}

CSceneManager::~CSceneManager(void)
{
	if (m_cAvatar)
	{
		delete m_cAvatar;
		m_cAvatar = NULL;
	}

	if (m_cMinimap)
	{
		delete m_cMinimap;
		m_cMinimap = NULL;
	}
}

void CSceneManager::Init()
{
	// Blue background
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

	m_programID = LoadShaders( "Shader//Texture.vertexshader", "Shader//Text.fragmentshader" );
	
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
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
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

	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));

	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference");//, 1000, 1000, 1000);
	meshList[GEO_CROSSHAIR] = MeshBuilder::GenerateCrossHair("crosshair");
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);
	//meshList[GEO_OBJECT] = MeshBuilder::GenerateOBJ("OBJ1", "OBJ//Unicorn_Arm.obj");//MeshBuilder::GenerateCube("cube", 1);
	//meshList[GEO_OBJECT]->textureID = LoadTGA("Image//Unicorn_Gundam//Unicorn_Arm.tga");
	meshList[GEO_RING] = MeshBuilder::GenerateRing("ring", Color(1, 0, 1), 36, 1, 0.5f);
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 0, 0), 18, 36, 1.f);
	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("sphere", Color(0.43921568627, 0.74117647058, 0.81960784313), 18, 36, 10.f);
	//meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", 1, 1, 1);
	//meshList[GEO_TORUS] = MeshBuilder::GenerateCylinder("torus", 36, 36, 5, 1);
	meshList[GEO_CONE] = MeshBuilder::GenerateCone("cone", Color(0.5f, 1, 0.3f), 36, 10.f, 10.f);
	meshList[GEO_CONE]->material.kDiffuse.Set(0.99f, 0.99f, 0.99f);
	meshList[GEO_CONE]->material.kSpecular.Set(0.f, 0.f, 0.f);
	
	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("LEFT", Color(1, 1, 1), 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//left.tga");
	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("RIGHT", Color(1, 1, 1), 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//right.tga");
	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("TOP", Color(1, 1, 1), 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//top.tga");
	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("BOTTOM", Color(1, 1, 1), 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//bottom.tga");
	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("FRONT", Color(1, 1, 1), 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//front.tga");
	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("BACK", Color(1, 1, 1), 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//back.tga");

	// Load the ground mesh and texture
	meshList[GEO_GRASS_DARKGREEN] = MeshBuilder::GenerateQuad("GRASS_DARKGREEN", Color(1, 1, 1), 1.f);
	meshList[GEO_GRASS_DARKGREEN]->textureID = LoadTGA("Image//grass_darkgreen.tga");
	meshList[GEO_GRASS_LIGHTGREEN] = MeshBuilder::GenerateQuad("GEO_GRASS_LIGHTGREEN", Color(1, 1, 1), 1.f);
	meshList[GEO_GRASS_LIGHTGREEN]->textureID = LoadTGA("Image//grass_lightgreen.tga");

	// Load the texture for minimap
	m_cMinimap = new CMinimap();
	m_cMinimap->SetBackground(MeshBuilder::GenerateMinimap("MINIMAP", Color(1, 1, 1), 1.f));
	m_cMinimap->GetBackground()->textureID = LoadTGA("Image//grass_darkgreen.tga");
	m_cMinimap->SetBorder( MeshBuilder::GenerateMinimapBorder("MINIMAPBORDER", Color(1, 1, 0), 1.f) );
	m_cMinimap->SetAvatar( MeshBuilder::GenerateMinimapAvatar("MINIMAPAVATAR", Color(1, 1, 0), 1.f) );

	//Unicorn Gundam
	meshList[GEO_UNICORN_LEFT_LEG] = MeshBuilder::GenerateOBJ("OBJ1", "OBJ//Unicorn_Shield.obj");//MeshBuilder::GenerateCube("cube", 1);
	meshList[GEO_UNICORN_LEFT_LEG]->textureID = LoadTGA("Image//Unicorn_Gundam//Unicorn_Shield.tga");

	meshList[GEO_UNICORN_RIGHT_LEG] = MeshBuilder::GenerateOBJ("OBJ1", "OBJ//Unicorn_Leg.obj");//MeshBuilder::GenerateCube("cube", 1);
	meshList[GEO_UNICORN_RIGHT_LEG]->textureID = LoadTGA("Image//Unicorn_Gundam//Unicorn_LegRight.tga");

	//Initialise and load a model
	m_cAvatar = new CPlayInfo3PV();
	//m_cAvatar->SetModel(MeshBuilder::GenerateCone("cone", Color(0.5f, 1, 0.3f), 36, 10.f, 10.f));
	m_cAvatar->head = MeshBuilder::GenerateOBJ("OBJ1", "OBJ//Unicorn_Head.obj");//MeshBuilder::GenerateCube("cube", 1);
	m_cAvatar->head->textureID = LoadTGA("Image//Unicorn_Gundam//Unicorn_Head.tga");

	m_cAvatar->torso = MeshBuilder::GenerateOBJ("OBJ1", "OBJ//Unicorn_Torso.obj");//MeshBuilder::GenerateCube("cube", 1);
	m_cAvatar->torso->textureID = LoadTGA("Image//Unicorn_Gundam//Unicorn_Torso.tga");

	m_cAvatar->leftArm = MeshBuilder::GenerateOBJ("OBJ1", "OBJ//Unicorn_Arm.obj");//MeshBuilder::GenerateCube("cube", 1);
	m_cAvatar->leftArm->textureID = LoadTGA("Image//Unicorn_Gundam//Unicorn_ArmLeft.tga");

	m_cAvatar->rightArm = MeshBuilder::GenerateOBJ("OBJ1", "OBJ//Unicorn_Arm.obj");//MeshBuilder::GenerateCube("cube", 1);
	m_cAvatar->rightArm->textureID = LoadTGA("Image//Unicorn_Gundam//Unicorn_ArmRight.tga");

	m_cAvatar->leftLeg = MeshBuilder::GenerateOBJ("OBJ1", "OBJ//Unicorn_Leg.obj");//MeshBuilder::GenerateCube("cube", 1);
	m_cAvatar->leftLeg->textureID = LoadTGA("Image//Unicorn_Gundam//Unicorn_LegLeft.tga");

	m_cAvatar->rightLeg = MeshBuilder::GenerateOBJ("OBJ1", "OBJ//Unicorn_Leg.obj");//MeshBuilder::GenerateCube("cube", 1);
	m_cAvatar->rightLeg->textureID = LoadTGA("Image//Unicorn_Gundam//Unicorn_LegRight.tga");

	m_cAvatar->rifle = MeshBuilder::GenerateOBJ("Beam Magnum", "OBJ//Beam_Magnum.obj");
	m_cAvatar->rifle->textureID = LoadTGA("Image//Unicorn_Gundam//Beam_Magnum.tga");

	m_cAvatar->shield = MeshBuilder::GenerateOBJ("OBJ1", "OBJ//Unicorn_Shield.obj");//MeshBuilder::GenerateCube("cube", 1);
	m_cAvatar->shield->textureID = LoadTGA("Image//Unicorn_Gundam//Unicorn_Shield.tga");

	m_cAvatar->saber = MeshBuilder::GenerateOBJ("OBJ1", "OBJ//Beam_Saber.obj");//MeshBuilder::GenerateCube("cube", 1);
	m_cAvatar->saber->textureID = LoadTGA("Image//Unicorn_Gundam//Beam_Saber.tga");

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);
	
	rotateAngle = 0;

	bLightEnabled = true;
}

void CSceneManager::createParticle(const double &dt)
{
	if (Application::IsKeyPressed(VK_SPACE))
	{
		//Creating thruster effect when using exhaust
		Vector3 right = camera.direction.Cross(camera.up);
		Vector3 pos = m_cAvatar->GetPosition();
		static double timeLimit = 0.1;

		//Top left thruster
		Vector3 topLeft_pos = pos;
		topLeft_pos.y += 20;
		topLeft_pos.x -= camera.direction.x * 5 + right.x * 4.2;
		topLeft_pos.z -= camera.direction.z * 5 + right.z * 4.2;

		Vector3 topLeft_vel;
		topLeft_vel.x = Math::RandFloatMinMax(-right.x * 2, -right.x * 10);
		topLeft_vel.z = Math::RandFloatMinMax(-right.z * 2, -right.z * 10);
		topLeft_vel.y = Math::RandFloatMinMax(-2, -5);

		Particle* topLeft = fetchParticle(topLeft_pos, topLeft_vel, timeLimit);


		//Top right thruster
		Vector3 topRight_pos = pos;
		topRight_pos.y += 20;
		topRight_pos.x -= camera.direction.x * 5 - right.x * 4.2;
		topRight_pos.z -= camera.direction.z * 5 - right.z * 4.2;

		Vector3 topRight_vel;
		topRight_vel.x = Math::RandFloatMinMax(right.x * 2, right.x * 10);
		topRight_vel.z = Math::RandFloatMinMax(right.z * 2, right.z * 10);
		topRight_vel.y = Math::RandFloatMinMax(-2, -5);

		Particle* topRight = fetchParticle(topRight_pos, topRight_vel, timeLimit);

		//Bottom left thruster
		Vector3 bottomLeft_pos = pos;
		bottomLeft_pos.y += 10;
		bottomLeft_pos.x -= camera.direction.x * 3 + right.x * 4.2;
		bottomLeft_pos.z -= camera.direction.z * 3 + right.z * 4.2;

		Vector3 bottomLeft_vel;
		bottomLeft_vel.x = Math::RandFloatMinMax(-camera.direction.x * 5, -camera.direction.x * 10);
		bottomLeft_vel.z = Math::RandFloatMinMax(-camera.direction.z * 5, -camera.direction.z * 10);
		bottomLeft_vel.y = Math::RandFloatMinMax(-2, -5);

		Particle* bottomLeft = fetchParticle(bottomLeft_pos, bottomLeft_vel, timeLimit);

		//Bottom right thruster
		Vector3 bottomRight_pos = pos;
		bottomRight_pos.y += 10;
		bottomRight_pos.x -= camera.direction.x * 3 - right.x * 4.2;
		bottomRight_pos.z -= camera.direction.z * 3 - right.z * 4.2;

		Vector3 bottomRight_vel;
		bottomRight_vel.x = Math::RandFloatMinMax(-camera.direction.x * 10, -camera.direction.x * 15);
		bottomRight_vel.z = Math::RandFloatMinMax(-camera.direction.z * 10, -camera.direction.z * 15);
		bottomRight_vel.y = Math::RandFloatMinMax(-2, -5);

		Particle* bottomRight = fetchParticle(bottomRight_pos, bottomRight_vel, timeLimit);
	}
}

void CSceneManager::Update(double dt)
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

	rotateAngle -= Application::camera_yaw;// += (float)(10 * dt);

	m_cAvatar->Update(dt, camera);
	camera.UpdatePosition(m_cAvatar->GetPosition(), m_cAvatar->GetDirection(), dt);
	//camera.Update(dt);

	for (std::vector<Particle*>::iterator it = particleList.begin(); it != particleList.end(); ++it)
	{
		Particle* particle = static_cast<Particle*>(*it);

		if (particle->getActive())
		{
			particle->update(dt);
		}
	}

	if (!m_cAvatar->getVel().IsZero() || Application::IsKeyPressed(VK_SPACE))
	{
		rotateAngle = camera.getAngleAroundObj();
	}

	fps = (float)(1.f / dt);
	createParticle(dt);
}

/********************************************************************************
 Update Camera position
 ********************************************************************************/
void CSceneManager::UpdateCameraStatus(const unsigned char key, const bool status)
{
	camera.UpdateStatus(key, status);
}

/********************************************************************************
Update Avatar position
********************************************************************************/
void CSceneManager::UpdateAvatarStatus(const unsigned char key, const bool status)
{
	m_cAvatar->UpdateMovement(key, status);
}

/********************************************************************************
 Update Weapon status
 ********************************************************************************/
void CSceneManager::UpdateWeaponStatus(const unsigned char key)
{
	if (key == WA_FIRE)
	{
		// Add a bullet object which starts at the camera position and moves in the camera's direction
	}
}

/********************************************************************************
 Render text onto the screen with reference position in the middle of the image
 ********************************************************************************/
void CSceneManager::RenderText(Mesh* mesh, std::string text, Color color)
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
		characterSpacing.SetToTranslation(i * 0.8f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

/********************************************************************************
 Render text onto the screen
 ********************************************************************************/
void CSceneManager::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
{
	if(!mesh || mesh->textureID <= 0)
		return;
	
	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	//ortho.SetToOrtho(0, m_window_width, 0, m_window_height, -10, 10);
	ortho.SetToOrtho(0, m_window_width, 0, m_window_height, -10, 10);
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
					characterSpacing.SetToTranslation( (i*0.5f) + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
					Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
					glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	
					mesh->Render((unsigned)text[i] * 6, 6);
				}
				glBindTexture(GL_TEXTURE_2D, 0);
				glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
			modelStack.PopMatrix();
		viewStack.PopMatrix();
	projectionStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

/********************************************************************************
 Render a mesh in 2D
 ********************************************************************************/
void CSceneManager::RenderMeshIn2D(Mesh *mesh, bool enableLight, float size, float x, float y, bool rotate)
{
	Mtx44 ortho;
	ortho.SetToOrtho(-80, 80, -60, 60, -10, 10);
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
				if(mesh->textureID > 0)
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
				}
       
			modelStack.PopMatrix();
		viewStack.PopMatrix();
	projectionStack.PopMatrix();

}

/********************************************************************************
 Render a mesh
 ********************************************************************************/
void CSceneManager::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;
	
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if(enableLight && bLightEnabled)
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
	if(mesh->textureID > 0)
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
	}
}

/********************************************************************************
 Render mobile objects
 ********************************************************************************/
void CSceneManager::RenderGUI()
{
	// Render the crosshair
	//RenderMeshIn2D(meshList[GEO_CROSSHAIR], false, 10.0f);

	// Render the crosshair
	// Note that Ortho is set to this size -> 	ortho.SetToOrtho(-80, 80, -60, 60, -10, 10);
	RenderMeshIn2D( m_cMinimap->GetAvatar(), false, 20.0f, 68, -48, true);
	RenderMeshIn2D( m_cMinimap->GetBorder(), false, 20.0f, 68, -48);
	RenderMeshIn2D( m_cMinimap->GetBackground(), false, 20.0f, 68, -48);

	//On screen text
	std::ostringstream ss;
	ss.precision(5);
	ss << "FPS: " << fps;
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 30, 0, 6);

	RenderTextOnScreen(meshList[GEO_TEXT], "Hello Screen", Color(0, 1, 0), 3, 0, 0);
}

/********************************************************************************
 Render mobile objects
 ********************************************************************************/
void CSceneManager::RenderMobileObjects()
{
	// Render LightBall
	modelStack.PushMatrix();
	modelStack.Translate(lights[0].position.x, lights[0].position.y, lights[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//modelStack.Translate(m_cAvatar->GetPosition().x, m_cAvatar->GetPosition().y, m_cAvatar->GetPosition().z);
	////modelStack.Rotate(camera.getAngleAroundObj(), 0, 1, 0);
	//modelStack.Scale(10, 10, 10);
	//RenderMesh(meshList[GEO_UNICORN_LEFT_LEG], false);
	//modelStack.PopMatrix();

	for (std::vector<Particle*>::iterator it = particleList.begin(); it != particleList.end(); ++it)
	{
		Particle* particle = static_cast<Particle*>(*it);

		if (particle->getActive())
		{
			modelStack.PushMatrix();
			modelStack.Translate(particle->getPos().x, particle->getPos().y, particle->getPos().z);
			modelStack.Scale(particle->getScale(), particle->getScale(), particle->getScale());
			RenderMesh(meshList[GEO_SPHERE], false);
			modelStack.PopMatrix();
		}
	}

	//Render Character
	modelStack.PushMatrix();
	modelStack.Translate(m_cAvatar->GetPosition().x, m_cAvatar->GetPosition().y, m_cAvatar->GetPosition().z);
	modelStack.Rotate(rotateAngle, 0, 1, 0);
	modelStack.Scale(10, 10, 10);

	//Head
	modelStack.PushMatrix();
	modelStack.Translate(0, 3, 0);
	RenderMesh(m_cAvatar->head, false);
	modelStack.PopMatrix();

	//Torso
	modelStack.PushMatrix();
	modelStack.Translate(0, 1.61, 0);
	RenderMesh(m_cAvatar->torso, false);
	modelStack.PopMatrix();

	static float Leg_offset = 0.33;
	static float Arm_offset = 0.98;

	//Left Arm
	modelStack.PushMatrix();
	modelStack.Translate(Arm_offset, 1.61, 0);
	modelStack.Translate(0, 0.5, 0);
	modelStack.Rotate(m_cAvatar->animation.vel_LeftArm, 1, 0, 0);
	modelStack.Translate(0, -0.5, 0);

	//Shield
	modelStack.PushMatrix();
	modelStack.Translate(0.4, 0, 0);
	RenderMesh(m_cAvatar->shield, false);
	modelStack.PopMatrix();

	RenderMesh(m_cAvatar->leftArm, false);
	modelStack.PopMatrix();

	//Right Arm
	modelStack.PushMatrix();
	modelStack.Translate(-Arm_offset, 1.61, 0);
	modelStack.Translate(0, 0.5, 0);
	modelStack.Rotate(m_cAvatar->animation.vel_RightArm, 1, 0, 0);
	modelStack.Translate(0, -0.5, 0);
	
	//Weapon
	modelStack.PushMatrix();
	modelStack.Translate(0.2, -1.5, 0.4);
	modelStack.Rotate(90, 1, 0, 0);
	RenderMesh(m_cAvatar->rifle, false);
	modelStack.PopMatrix();


	RenderMesh(m_cAvatar->rightArm, false);
	modelStack.PopMatrix();

	//Left Leg
	modelStack.PushMatrix();
	modelStack.Translate(Leg_offset, 0, 0);
	modelStack.Translate(0, 1, 0);
	modelStack.Rotate(m_cAvatar->animation.vel_LeftLeg, 1, 0, 0);
	modelStack.Translate(0, -1, 0);
	RenderMesh(m_cAvatar->leftLeg, false);
	modelStack.PopMatrix();

	//Right Leg
	modelStack.PushMatrix();
	modelStack.Translate(-Leg_offset, 0, 0);
	modelStack.Translate(0, 1, 0);
	modelStack.Rotate(m_cAvatar->animation.vel_RightLeg, 1, 0, 0);
	modelStack.Translate(0, -1, 0);
	RenderMesh(m_cAvatar->rightLeg, false);
	modelStack.PopMatrix();

	//Mounting Weapon

	//Left Beam Saber
	modelStack.PushMatrix();
	modelStack.Translate(0.3, 2.68, -0.62);
	RenderMesh(m_cAvatar->saber, false);
	modelStack.PopMatrix();

	//Right Beam Saber
	modelStack.PushMatrix();
	modelStack.Translate(-0.3, 2.68, -0.62);
	RenderMesh(m_cAvatar->saber, false);
	modelStack.PopMatrix();

	modelStack.PopMatrix();
}

/********************************************************************************
 Render the lights in this scene
 ********************************************************************************/
void CSceneManager::RenderFixedObjects()
{
	RenderMesh(meshList[GEO_AXES], false);


	modelStack.PushMatrix();
	modelStack.Scale(10, 10, 10);
	//RenderText(meshList[GEO_TEXT], "Hello World", Color(0, 1, 0));
	RenderText(meshList[GEO_TEXT], "DM2240 AGDEV", Color(0, 1, 0));
	modelStack.PopMatrix();
}

/********************************************************************************
 Render the lights in this scene
 ********************************************************************************/
void CSceneManager::RenderLights()
{
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
}

/********************************************************************************
 Render the ground in this scene
 ********************************************************************************/
void CSceneManager::RenderGround()
{
	modelStack.PushMatrix();
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Translate(0, 0, -10);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Scale(100.0f, 100.0f, 100.0f);

	for (int x=0; x<10; x++)
	{
		for (int z=0; z<10; z++)
		{
			modelStack.PushMatrix();
			modelStack.Translate(x-5.0f, z-5.0f, 0.0f);
			if ( ((x*9+z) % 2) == 0)
				RenderMesh(meshList[GEO_GRASS_DARKGREEN], false);
			else
				RenderMesh(meshList[GEO_GRASS_LIGHTGREEN], false);
			modelStack.PopMatrix();
		}
	}
	modelStack.PopMatrix();
}

/********************************************************************************
 Render the skybox in this scene
 ********************************************************************************/
void CSceneManager::RenderSkybox()
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
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Translate(0, 0, -SKYBOXSIZE / 2 + 2.f);
	modelStack.Rotate(-90, 0, 0, 1);
	modelStack.Scale(SKYBOXSIZE, SKYBOXSIZE, SKYBOXSIZE);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();
}

Particle * CSceneManager::fetchParticle(Vector3 pos, Vector3 vel, double timeLimit)
{
	for (std::vector<Particle*>::iterator it = particleList.begin(); it != particleList.end(); it++)
	{
		Particle* particle = static_cast<Particle*>(*it);

		if (!particle->getActive())
		{
			particle->restartParticles(pos, vel, timeLimit);
			return particle;
		}
	}

	for (unsigned a = 0; a < 10; ++a)
	{
		Particle* particle = new Particle();
		particleList.push_back(particle);
	}

	Particle* particle = particleList.back();
	particle->restartParticles(pos, vel, timeLimit);

	return particle;
}

/********************************************************************************
 Render this scene
 ********************************************************************************/
void CSceneManager::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);
	
	// Set up the view
	viewStack.LoadIdentity();
	viewStack.LookAt(	camera.position.x, camera.position.y, camera.position.z,
						camera.target.x, camera.target.y, camera.target.z,
						camera.up.x, camera.up.y, camera.up.z );

	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	RenderLights();
	RenderGround();
	RenderSkybox();
	RenderFixedObjects();
	RenderMobileObjects();

	RenderGUI();
}

/********************************************************************************
 Exit process for this scene
 ********************************************************************************/
void CSceneManager::Exit()
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
