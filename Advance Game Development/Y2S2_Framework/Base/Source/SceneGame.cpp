#include "SceneGame.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>
#include <irrKlang.h>

SceneGame::SceneGame(void)
	: m_cMinimap(NULL)
	, m_window_width(800)
	, m_window_height(600)
	, m_cSceneGraph(NULL)
	, m_cSpatialPartition(NULL)
{
}

SceneGame::SceneGame(const int m_window_width, const int m_window_height)
	: m_cMinimap(NULL)
	,m_cAvatar(NULL)
	, m_cSceneGraph(NULL)
	, m_cSpatialPartition(NULL)
{
	this->m_window_width = m_window_width;
	this->m_window_height = m_window_height;
}

SceneGame::~SceneGame(void)
{
	if (m_cSceneGraph)
	{
		delete m_cSceneGraph;
		m_cSceneGraph = NULL;
	}

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

	/*if (m_cSpatialPartition)
	{
		delete m_cSpatialPartition;
		m_cSpatialPartition = NULL;
	}*/
}

void SceneGame::InitShaders()
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

	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");

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
}

void SceneGame::InitMesh()
{
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_RAY] = MeshBuilder::GenerateRay("Ray", 10.f);
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference");//, 1000, 1000, 1000);
	//meshList[GEO_CROSSHAIR] = MeshBuilder::GenerateCrossHair("crosshair");
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f);
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);
	//meshList[GEO_OBJECT] = MeshBuilder::GenerateOBJ("OBJ1", "OBJ//Unicorn_Arm.obj");//MeshBuilder::GenerateCube("cube", 1);
	//meshList[GEO_OBJECT]->textureID = LoadTGA("Image//Unicorn_Gundam//Unicorn_Arm.tga");
	meshList[GEO_RING] = MeshBuilder::GenerateRing("ring", Color(1, 0, 1), 36, 1, 0.5f);
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 0, 0), 18, 36, 10.f);
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
	m_cMinimap->SetBorder(MeshBuilder::GenerateMinimapBorder("MINIMAPBORDER", Color(1, 1, 0), 1.f));
	m_cMinimap->SetAvatar(MeshBuilder::GenerateMinimapAvatar("MINIMAPAVATAR", Color(1, 1, 0), 1.f));

	meshList[GEO_CROSSHAIR] = MeshBuilder::GenerateQuad("Crosshair", Color(0, 0, 0), 1);
	meshList[GEO_CROSSHAIR]->textureID = LoadTGA("Image//Crosshair.tga");

	meshList[GEO_TERRAIN] = MeshBuilder::GenerateTerrain("Terrain", "Image//Terrain//terrain.raw", m_heightMap);
}

void SceneGame::Init()
{
	InitShaders();

	InitMesh();

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);
	
	heightMapScale.Set(2000.f, 350.f, 2000.f);

	rotateAngle = 0;

	bLightEnabled = true;

	b_pauseGame = false;
	mousePos.SetZero();
	menuChoice = "";
	isMousePressed_Left = false;
	m_cAvatar = new CPlayInfo3PV();

	m_cSpatialPartition = new CSpatialPartition();
	m_cSpatialPartition->Init(100, 100, 3, 3);
	for (int i = 0; i < m_cSpatialPartition->GetxNumOfGrid(); i++)
	{
		for (unsigned j = 0; j < m_cSpatialPartition->GetyNumOfGrid(); j++)
		{
			m_cSpatialPartition->SetGridMesh(i, j, MeshBuilder::GenerateQuad("Gridmesh", Color(1.f / i, 1.f / j, 1.f / (i * j)), 100.f));
		}
	}

	//m_cSpatialPartition->AddObject(m_cAvatar->avatarInfo);

	m_grid = std::make_unique<Grid>(1000, 1000, CELL_SIZE);
	//m_grid->addNode(Vector3(0, 0, 0), m_cAvatar->getNode());

	CText * text = new CText();
	text = new CText();
	text->setPos(Vector3(Application::getWindow_Width() * 0.22f, Application::getWindow_Height() * 0.5f, 0.1f));
	text->setScale(Vector3(35, 35, 35));
	text->setText("Return To Menu");
	textList.push_back(text);

	text = new CText();
	text->setPos(Vector3(Application::getWindow_Width() * 0.22f, Application::getWindow_Height() * 0.5f - 60, 0.1f));
	text->setScale(Vector3(35, 35, 35));
	text->setText("Exit");
	textList.push_back(text);

	AI* ai = new AI(Vector3(0, 0, 200));
	GOList.push_back(ai);

	ai = new AI(Vector3(200, 0, 200));
	GOList.push_back(ai);
}

void SceneGame::Update(double dt)
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

	static float variable = 0.0;
	static double angle = 0.0;
	variable += 100 *dt;
	if (variable > 360)
	{
		variable -= 360;
	}


	fps = (float)(1.f / dt);

	static double d_buttonTimeLimit = 0.5;
	static double d_buttonCurrentTime = 0;

	if (d_buttonCurrentTime < d_buttonTimeLimit)
	{
		d_buttonCurrentTime += dt;
	}
	else
	{
		if (Application::IsKeyPressed(VK_ESCAPE))
		{
			if (!b_pauseGame)
			{
				Application::activateMouse(false);
			}
			else
			{
				Application::activateMouse(true);
			}

			b_pauseGame = !b_pauseGame;
			d_buttonCurrentTime = 0;
		}
	}

	if (!b_pauseGame)
	{
		UpdateGameplay(dt);
	}
	else
	{
		UpdateMenu(dt);
	}
}

/********************************************************************************
 Render text onto the screen with reference position in the middle of the image
 ********************************************************************************/
void SceneGame::RenderText(Mesh* mesh, std::string text, Color color)
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
void SceneGame::RenderTextOnScreen(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	//ortho.SetToOrtho(0, m_window_width, 0, m_window_height, -10, 10);
	ortho.SetToOrtho(0, Application::getWindow_Width(), 0, Application::getWindow_Height(), -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	/*projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(pos.x, pos.y, 0);
	modelStack.Scale(scale.x, scale.y, scale.z);*/

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
		characterSpacing.SetToTranslation(i * 0.6f, 0.f, 0); //1.0f is the spacing of each character, you may change this value
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

/********************************************************************************
 Render a mesh in 2D
 ********************************************************************************/
void SceneGame::RenderMeshIn2D(Mesh *mesh, bool enableLight, float size, float x, float y, bool rotate)
{
	Mtx44 ortho;
	ortho.SetToOrtho(-80, 80, -60, 60, -10, 10);
	projectionStack.PushMatrix();
		projectionStack.LoadMatrix(ortho);
		viewStack.PushMatrix();
			viewStack.LoadIdentity();
			modelStack.PushMatrix();
				//modelStack.LoadIdentity();
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

void SceneGame::PreRendering(CTransform* &transform, bool enableLight, Mesh* mesh)
{
	double angle;
	Vector3 translate, scale, rotate, rotate_Offset;

	transform->GetTranslation(translate.x, translate.y, translate.z);
	transform->GetScale(scale.x, scale.y, scale.z);
	transform->GetRotation2(angle, rotate.x, rotate.y, rotate.z, rotate_Offset.x, rotate_Offset.y, rotate_Offset.z);
	std::vector<CTransform::ORIENTATION> rotateList = transform->getOrientation();

	modelStack.PushMatrix();
	modelStack.Translate(translate.x, translate.y, translate.z);

	if (!rotateList.empty())
	{
		for (std::vector<CTransform::ORIENTATION>::iterator it = rotateList.begin(); it != rotateList.end(); ++it)
		{
			CTransform::ORIENTATION rotateInfo = static_cast<CTransform::ORIENTATION>(*it);
			modelStack.Rotate(rotateInfo.angle, rotateInfo.rotateDir.x, rotateInfo.rotateDir.y, rotateInfo.rotateDir.z);
		}
	}

	if (angle != NULL)
	{
		if (!rotate_Offset.IsZero())
		{
			modelStack.Translate(rotate_Offset.x, rotate_Offset.y, rotate_Offset.z);
		}

		modelStack.Rotate(angle, rotate.x, rotate.y, rotate.z);

		if (!rotate_Offset.IsZero())
		{
			modelStack.Translate(-rotate_Offset.x, -rotate_Offset.y, -rotate_Offset.z);
		}
	}
	modelStack.Scale(scale.x, scale.y, scale.z);

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
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}

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

	modelStack.PopMatrix();
}

void SceneGame::PostRendering(Mesh * mesh)
{
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}


/********************************************************************************
 Render a mesh
 ********************************************************************************/
void SceneGame::RenderMesh(Mesh *mesh, bool enableLight)
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
void SceneGame::RenderMobileObjects()
{
	// Render LightBall
	modelStack.PushMatrix();
	modelStack.Translate(lights[0].position.x, lights[0].position.y, lights[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	/*for (std::vector<Particle*>::iterator it = particleList.begin(); it != particleList.end(); ++it)
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
	}*/


	if (b_pauseGame) 
	{
		RenderMenu();
	}
	else
	{
		RenderGameplay();
	}
}

/********************************************************************************
 Render the lights in this scene
 ********************************************************************************/
void SceneGame::RenderFixedObjects()
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
void SceneGame::RenderLights()
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
void SceneGame::RenderGround()
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
void SceneGame::RenderSkybox()
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

/********************************************************************************
 Render this scene
 ********************************************************************************/
void SceneGame::Render()
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
void SceneGame::Exit()
{
	// Cleanup VBO
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if(meshList[i])
			delete meshList[i];
	}

	while(textList.size() > 0)
	{
		CText *text = textList.back();
		delete text;
		textList.pop_back();
	}


	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}

//void SceneGame::generateParticle(const double &dt)
//{
	//if (Application::IsKeyPressed(VK_SPACE))
	//{
	//	//Creating thruster effect when using exhaust
	//	Vector3 right = camera.direction.Cross(camera.up);
	//	Vector3 pos = m_cAvatar->getPos();
	//	static double timeLimit = 0.1;

	//	//Top left thruster
	//	Vector3 topLeft_pos = pos;
	//	topLeft_pos.y += 20;
	//	topLeft_pos.x -= camera.direction.x * 5 + right.x * 4.2;
	//	topLeft_pos.z -= camera.direction.z * 5 + right.z * 4.2;

	//	Vector3 topLeft_vel;
	//	topLeft_vel.x = Math::RandFloatMinMax(-right.x * 2, -right.x * 10);
	//	topLeft_vel.z = Math::RandFloatMinMax(-right.z * 2, -right.z * 10);
	//	topLeft_vel.y = Math::RandFloatMinMax(-2, -5);

	//	Particle* topLeft = fetchParticle(topLeft_pos, topLeft_vel, timeLimit);


	//	//Top right thruster
	//	Vector3 topRight_pos = pos;
	//	topRight_pos.y += 20;
	//	topRight_pos.x -= camera.direction.x * 5 - right.x * 4.2;
	//	topRight_pos.z -= camera.direction.z * 5 - right.z * 4.2;

	//	Vector3 topRight_vel;
	//	topRight_vel.x = Math::RandFloatMinMax(right.x * 2, right.x * 10);
	//	topRight_vel.z = Math::RandFloatMinMax(right.z * 2, right.z * 10);
	//	topRight_vel.y = Math::RandFloatMinMax(-2, -5);

	//	Particle* topRight = fetchParticle(topRight_pos, topRight_vel, timeLimit);

	//	//Bottom left thruster
	//	Vector3 bottomLeft_pos = pos;
	//	bottomLeft_pos.y += 10;
	//	bottomLeft_pos.x -= camera.direction.x * 3 + right.x * 4.2;
	//	bottomLeft_pos.z -= camera.direction.z * 3 + right.z * 4.2;

	//	Vector3 bottomLeft_vel;
	//	bottomLeft_vel.x = Math::RandFloatMinMax(-camera.direction.x * 5, -camera.direction.x * 10);
	//	bottomLeft_vel.z = Math::RandFloatMinMax(-camera.direction.z * 5, -camera.direction.z * 10);
	//	bottomLeft_vel.y = Math::RandFloatMinMax(-2, -5);

	//	Particle* bottomLeft = fetchParticle(bottomLeft_pos, bottomLeft_vel, timeLimit);

	//	//Bottom right thruster
	//	Vector3 bottomRight_pos = pos;
	//	bottomRight_pos.y += 10;
	//	bottomRight_pos.x -= camera.direction.x * 3 - right.x * 4.2;
	//	bottomRight_pos.z -= camera.direction.z * 3 - right.z * 4.2;

	//	Vector3 bottomRight_vel;
	//	bottomRight_vel.x = Math::RandFloatMinMax(-camera.direction.x * 10, -camera.direction.x * 15);
	//	bottomRight_vel.z = Math::RandFloatMinMax(-camera.direction.z * 10, -camera.direction.z * 15);
	//	bottomRight_vel.y = Math::RandFloatMinMax(-2, -5);

	//	Particle* bottomRight = fetchParticle(bottomRight_pos, bottomRight_vel, timeLimit);
	//}
//}

void SceneGame::UpdateGameplay(const double &dt)
{
	//m_cSpatialPartition->Update(m_cAvatar->GetPosition());
	//m_cSpatialPartition->TestingSomething(m_cAvatar->GetPosition());

	/*for (std::vector<Particle*>::iterator it = particleList.begin(); it != particleList.end(); ++it)
	{
		Particle* particle = static_cast<Particle*>(*it);

		if (particle->getActive())
		{
			particle->update(dt);
		}
	}*/

	static double shootTime_Right = 0.0, shootTime_Left = 0.0;
	static double shootTimeLimit_Right = 0.5, shootTimeLimit_Left = 0.15;

	if (shootTime_Right < shootTimeLimit_Right)
		shootTime_Right += dt;

	if (shootTime_Left < shootTimeLimit_Left)
		shootTime_Left += dt;

	if (m_cAvatar->isAttackMode())
	{
		if (Application::IsMousePressed(0))
		{
			if (camera.isLookingRight())
			{
				if (shootTime_Right >= shootTimeLimit_Right)
				{
					Sound::playBeamMagnum();
					Vector3 bulletOffset = m_cAvatar->getPos() + (camera.getRight() * 7) + Vector3(0, 25, 0);
					shootBullet(bulletOffset, camera.direction , 5);
					shootTime_Right = 0.0;
				}
			}
			else
			{
				if (shootTime_Left >= shootTimeLimit_Left)
				{
					Vector3 bulletOffset_Top = m_cAvatar->getPos() + (-camera.getRight() * 10) + Vector3(0, 25, 0);
					Vector3 DirOffset_Top = camera.direction;
					DirOffset_Top.x += Math::RandFloatMinMax(-camera.getRight().x * 0.05, camera.getRight().x * 0.05);
					DirOffset_Top.y += Math::RandFloatMinMax(-camera.getRight().y * 0.05, camera.getRight().y * 0.05);
					DirOffset_Top.z += Math::RandFloatMinMax(-camera.getRight().z * 0.05, camera.getRight().z * 0.05);
					shootBullet(bulletOffset_Top, DirOffset_Top, 5);

					Vector3 bulletOffset_Bottom = m_cAvatar->getPos() + (-camera.getRight() * 10) + Vector3(0, 15, 0);
					Vector3 DirOffset_Bottom = camera.direction;
					DirOffset_Bottom.x += Math::RandFloatMinMax(-camera.getRight().x * 0.05, camera.getRight().x * 0.05);
					DirOffset_Bottom.y += Math::RandFloatMinMax(-camera.getRight().y * 0.05, camera.getRight().y * 0.05);
					DirOffset_Bottom.z += Math::RandFloatMinMax(-camera.getRight().z * 0.05, camera.getRight().z * 0.05);
					shootBullet(bulletOffset_Bottom, DirOffset_Bottom, 5);
					shootTime_Left = 0.0;
				}
			}
		}
	}

	PlayerUpdate(dt);
	GridUpdate(dt);
	ParticleUpdate(dt);
}

void SceneGame::shootBullet(const Vector3& pos, const Vector3& direction, const double& timeLimit, bool playerBullet)
{
	CBullet* bullet = fetchBullet();
	if (bullet != NULL)
	{
		bullet->setActive(true);
		bullet->setPos(pos);
		bullet->setDirection(direction);
		bullet->setTimeLimit(timeLimit);
		bullet->setDisplayBullet(false);
	}
}

void SceneGame::textUpdate()
{
	if (!isMousePressed_Left && Application::IsMousePressed(0))
	{
		isMousePressed_Left = true;
	}

	for (std::vector<CText*>::iterator it = textList.begin(); it != textList.end(); ++it)
	{
		CText* text = static_cast<CText*>(*it);

		Vector3 offset = Vector3(0, 0, 0);

		Vector3 topLeft = text->getPos() + Vector3(text->getText().length() * text->getScale().x - text->getScale().x, text->getScale().y, 0) + offset;
		Vector3 bottomRight = text->getPos() + Vector3(-text->getScale().x * 0.5f, -(text->getScale().y * 0.4f), 0) + offset;

		if (SSDLC::intersect2D(topLeft, bottomRight, mousePos))
		{
			text->setColorToOnClick();

			if (isMousePressed_Left && !Application::IsMousePressed(0))
			{
				menuChoice = text->getText();
				isMousePressed_Left = false;
			}
			else
			{
				menuChoice = "";
			}
		}
		else
		{
			text->setColorToNotOnClick();
		}
	}
}

void SceneGame::UpdateMenu(const double &dt)
{
	float x, y;
	Application::GetMousePos(x, y);
	mousePos.x = x / Application::getWindow_Width() * Application::getWindow_Width() + 0;
	mousePos.y = (Application::getWindow_Height() - y) / Application::getWindow_Height() * Application::getWindow_Height() + 0;

	textUpdate();

	if (menuChoice != "")
	{
		if (menuChoice == "Return To Menu")
		{
			Application::b_BacktoMenu = true;
		}
		else if (menuChoice == "Exit")
		{
			Application::quitGame();
		}
	}
}

CBullet* SceneGame::fetchBullet()
{
	for (CGameObject* go : GOList)
	{
		CBullet* bullet = dynamic_cast<CBullet*>(go);
		if (bullet != NULL)
		{
			if (!bullet->getActive())
			{
				return bullet;
			}
		}
	}

	for (unsigned a = 0; a < 10; ++a)
	{
		CBullet* newBullet = new CBullet();
		GOList.push_back(newBullet);
	}

	CBullet* bullet = dynamic_cast<CBullet*>(GOList.back());
	if (bullet != NULL)
	{
		return bullet;
	}

	return NULL;
}

AI* SceneGame::fetchAI()
{
	for (CGameObject* go : GOList)
	{
		AI* ai = dynamic_cast<AI*>(go);
		if (ai != NULL)
		{
			if (!ai->getActive())
			{
				return ai;
			}
		}
	}

	for (unsigned a = 0; a < 10; ++a)
	{
		AI* ai = new AI();
		GOList.push_back(ai);
	}

	AI* ai = dynamic_cast<AI*>(GOList.back());
	if (ai != NULL)
	{
		return ai;
	}

	return NULL;
}

Particle* SceneGame::fetchParticle()
{
	for (Particle* particle : particleList)
	{
		if (!particle->getActive())
		{
			return particle;
		}
	}

	for (unsigned a = 0; a < 10; ++a)
	{
		Particle* particle = new Particle();
		particleList.push_back(particle);
	}

	return particleList.back();
}


/********************************************************************************
Render mobile objects
********************************************************************************/
void SceneGame::RenderGUI()
{
	// Render the crosshair
	modelStack.PushMatrix();
	//modelStack.Translate(-1.5, -1.5, 0);
	RenderMeshIn2D(meshList[GEO_CROSSHAIR], false, 10.0f);
	modelStack.PopMatrix();

	// Render the crosshair
	// Note that Ortho is set to this size -> 	ortho.SetToOrtho(-80, 80, -60, 60, -10, 10);
	RenderMeshIn2D(m_cMinimap->GetAvatar(), false, 20.0f, 68, -48, true);
	RenderMeshIn2D(m_cMinimap->GetBorder(), false, 20.0f, 68, -48);
	RenderMeshIn2D(m_cMinimap->GetBackground(), false, 20.0f, 68, -48);


	//On screen text
	std::ostringstream ss;
	ss.precision(5);
	ss << "FPS: " << fps;

	modelStack.PushMatrix();
	modelStack.Translate(15, 15, 0);
	modelStack.Scale(30, 30, 30);
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0));
	modelStack.PopMatrix();
}

void SceneGame::RenderMenu()
{
	for (std::vector<CText *>::iterator it = textList.begin(); it != textList.end(); ++it)
	{
		CText* text = static_cast<CText*>(*it);

		modelStack.PushMatrix();
		modelStack.Translate(0, 0, 0);
		modelStack.Translate(text->getPos().x, text->getPos().y, text->getPos().z);
		modelStack.Scale(text->getScale().x, text->getScale().y, text->getScale().z);
		RenderTextOnScreen(meshList[GEO_TEXT], text->getText(), text->getColor());
		modelStack.PopMatrix();
	}
}

void SceneGame::RenderGameplay()
{
	//Render Terrain
	RenderTerrain();

	//Render Character
	modelStack.PushMatrix();
	modelStack.Translate(m_cAvatar->getPos().x, m_cAvatar->getPos().y, m_cAvatar->getPos().z);
	modelStack.Rotate(rotateAngle, 0, 1, 0);
	m_cAvatar->getNode()->Draw(this);
	modelStack.PopMatrix();

	//Render GameObject
	for (std::vector<CGameObject*>::iterator it = GOList.begin(); it != GOList.end(); ++it)
	{
		CGameObject* go = static_cast<CGameObject*>(*it);

		if (go->getActive() && dynamic_cast<CPlayInfo3PV*>(*it) == NULL)
		{
			modelStack.PushMatrix();
			modelStack.Translate(go->getPos().x, go->getPos().y, go->getPos().z);
			go->getNode()->Draw(this);
			modelStack.PopMatrix();
		}
	}

	//Render Particle
	for (Particle* particle : particleList)
	{
		if (particle->getActive())
		{
			modelStack.PushMatrix();
			modelStack.Translate(particle->getPos().x, particle->getPos().y, particle->getPos().z);
			modelStack.Scale(particle->getScale().x, particle->getScale().y, particle->getScale().z);
			RenderMesh(particle->getParticle(), false);
			modelStack.PopMatrix();
		}
	}
}

void SceneGame::checkCollision(CGameObject* go, std::vector<CGameObject*>& goToCheck, int startingIndex)
{
	for (unsigned a = 0; a < goToCheck.size(); ++a)
	{
		if (go != goToCheck[a])
		{
			//Always ensure player is the first parameters
			if (goToCheck[a]->isPlayer() || goToCheck[a]->isPlayerBullet())
			{
				CGameObject* temp = goToCheck[a];
				goToCheck[a] = go;
				go = temp;
			} 

			collisionCheck(go, goToCheck[a]);
		}
	}
}

void SceneGame::collisionCheck(CGameObject* go1, CGameObject* go2)
{
	if (go1->isPlayer() && go2->isEnemy())
	{
		AI * ai = dynamic_cast<AI*>(go2);
		Collision_PlayerToAi(ai);
	}
	else if (go1->isPlayerBullet() && go2->isEnemy())
	{
		std::unordered_map<int, std::string> nodeList = go2->getNodeList();

		for (std::unordered_map<int, std::string>::iterator it = nodeList.begin(); it != nodeList.end(); ++it)
		{
			CSceneNode* node = go2->getSceneGraph()->GetNode(it->first);
			if (node != NULL)
			{
				Vector3 topLeft(0, 0, 0), bottomRight(0, 0, 0), Position(0, 0, 0);
				Position = go2->getPos() + node->getTransform()->GetTranslation();

				if (it->second == "Head")
				{
					topLeft = Position + Vector3(8, 7, 8);
					bottomRight = Position - Vector3(8, 7, 8);
				}
				else if (it->second == "Torso")
				{
					topLeft = Position + Vector3(7, 6, 7);
					bottomRight = Position - Vector3(7, 10, 7);
				}

				else if (it->second == "LeftArm" || it->second == "RightArm")
				{
					topLeft = Position + Vector3(6, 6, 6);
					bottomRight = Position - Vector3(6, 10, 6);
				}
				else if (it->second == "LeftLeg" || it->second == "RightLeg")
				{
					topLeft = Position + Vector3(6, 8, 6);
					bottomRight = Position - Vector3(6, 8, 6);
					bottomRight.y = 0;
				}

				if (!Position.IsZero() && !bottomRight.IsZero() && !topLeft.IsZero())
				{
					/*if (SSDLC::intersect(topLeft, bottomRight, go1->getPos()))
					{
						go1->setActive(false);
						cout << it->second << std::endl;
					}*/
					if (SSDLC::intersect_LineAABB(go1->getPos(), go1->getDirection(), topLeft, bottomRight))
					{
						go1->setActive(false);
						cout << it->second << std::endl;
					}
				}
			}
		}
	}
}

void SceneGame::Collision_PlayerToAi(AI* ai)
{

}

/********************************************************************************
Update Camera position
********************************************************************************/
void SceneGame::UpdateCameraStatus(const unsigned char key, const bool status)
{
	camera.UpdateStatus(key, status);
}

/********************************************************************************
Update Avatar position
********************************************************************************/
void SceneGame::UpdateAvatarStatus(const unsigned char key, const bool status)
{
	m_cAvatar->UpdateMovement(key, status);
}

/********************************************************************************
Update Weapon status
********************************************************************************/
void SceneGame::UpdateWeaponStatus(const unsigned char key)
{
	if (key == WA_FIRE)
	{
		// Add a bullet object which starts at the camera position and moves in the camera's direction
		//m_cProjectileManager->AddProjectile(camera.position, camera.direction, 50.f);
	}
	else if (key == WA_FIRE_SECONDARY)
	{
		//m_cProjectileManager->AddRayProjectile(camera.position, camera.direction, 50.f);
	}
}

void SceneGame::RenderTerrain()
{
	modelStack.PushMatrix();
	modelStack.Translate(heightMapScale.x * 0.5, 0, heightMapScale.z * 0.5);
	modelStack.Scale(heightMapScale.x, heightMapScale.y, heightMapScale.z);
	RenderMesh(meshList[GEO_TERRAIN], false);
	modelStack.PopMatrix();
}

void SceneGame::PlayerUpdate(const double& dt)
{
	if (!m_cAvatar->getVel().IsZero() || Application::IsKeyPressed(VK_SPACE) || m_cAvatar->isAttackMode())
	{
		rotateAngle = camera.getAngleAroundObj();
	}

	//Creating Thruster Particles
	if (Application::IsKeyPressed(VK_SPACE))
	{
		Vector3 right = camera.getRight();

		//Top left thruster
		Vector3 topLeft_pos = m_cAvatar->getPos();
		topLeft_pos.y += 20;
		topLeft_pos.x -= camera.direction.x * 5 + right.x * 4.2;
		topLeft_pos.z -= camera.direction.z * 5 + right.z * 4.2;
		Vector3 topLeft_vel;
		topLeft_vel.x = Math::RandFloatMinMax(-right.x * 20, -right.x * 100);
		topLeft_vel.z = Math::RandFloatMinMax(-right.z * 20, -right.z * 100);
		topLeft_vel.y = Math::RandFloatMinMax(-2, -5);
		generateParticle(dt, topLeft_pos, topLeft_vel, 0.15, Particle::e_BLUE);


		//Top right thruster
		Vector3 topRight_pos = m_cAvatar->getPos();
		topRight_pos.y += 20;
		topRight_pos.x -= camera.direction.x * 5 - right.x * 4.2;
		topRight_pos.z -= camera.direction.z * 5 - right.z * 4.2;
		Vector3 topRight_vel;
		topRight_vel.x = Math::RandFloatMinMax(right.x * 20, right.x * 100);
		topRight_vel.z = Math::RandFloatMinMax(right.z * 20, right.z * 100);
		topRight_vel.y = Math::RandFloatMinMax(-2, -5);
		generateParticle(dt, topRight_pos, topRight_vel, 0.15, Particle::e_BLUE);

		//Bottom left thruster
		Vector3 bottomLeft_pos = m_cAvatar->getPos();
		bottomLeft_pos.y += 10;
		bottomLeft_pos.x -= camera.direction.x * 3 + right.x * 4.2;
		bottomLeft_pos.z -= camera.direction.z * 3 + right.z * 4.2;
		Vector3 bottomLeft_vel;
		bottomLeft_vel.x = Math::RandFloatMinMax(-camera.direction.x * 50, -camera.direction.x * 100);
		bottomLeft_vel.z = Math::RandFloatMinMax(-camera.direction.z * 50, -camera.direction.z * 100);
		bottomLeft_vel.y = Math::RandFloatMinMax(-2, -5);
		generateParticle(dt, bottomLeft_pos, bottomLeft_vel, 0.15, Particle::e_BLUE);

		//Bottom right thruster
		Vector3 bottomRight_pos = m_cAvatar->getPos();
		bottomRight_pos.y += 10;
		bottomRight_pos.x -= camera.direction.x * 3 - right.x * 4.2;
		bottomRight_pos.z -= camera.direction.z * 3 - right.z * 4.2;
		Vector3 bottomRight_vel;
		bottomRight_vel.x = Math::RandFloatMinMax(-camera.direction.x * 50, -camera.direction.x * 100);
		bottomRight_vel.z = Math::RandFloatMinMax(-camera.direction.z * 50, -camera.direction.z * 100);
		bottomRight_vel.y = Math::RandFloatMinMax(-2, -5);
		generateParticle(dt, bottomRight_pos, bottomRight_vel, 0.15, Particle::e_BLUE);
	}

	//Player Update
	Vector3 temp = m_cAvatar->getPos();
	temp.x -= heightMapScale.x * 0.5;
	temp.z -= heightMapScale.z * 0.5;
	float tempY = heightMapScale.y * ReadHeightMap(m_heightMap, temp.x / heightMapScale.x, temp.z / heightMapScale.z) + 20.f;
	m_cAvatar->Update(dt, camera, tempY);

	//Camera Update
	camera.UpdatePosition(m_cAvatar->getPos(), m_cAvatar->getDirection(), dt);
}

void SceneGame::GridUpdate(const double& dt)
{
	//Clear the list
	m_grid->clearList();
	for (std::vector<CGameObject*>::iterator it = GOList.begin(); it != GOList.end(); ++it)
	{
		CGameObject* go = static_cast<CGameObject*>(*it);
		if (go->getActive())
		{
			//Check if the node is in a different grid
			//Cause crashes if i keep removing specifically one node
			//Cell* newCell = m_grid->getCell(go->getPos());
			//if (newCell != go->getNode()->ownerCell)
			//{
			//	m_grid->removeGOFromCell(go);
			//	m_grid->addNode(go);
			//}

			//Repopulating the list
			m_grid->addNode(go);

			//Terrain Update
			Vector3 temp = go->getPos();
			temp.x -= heightMapScale.x * 0.5;
			temp.z -= heightMapScale.z * 0.5;
			float tempY = heightMapScale.y * ReadHeightMap(m_heightMap, temp.x / heightMapScale.x, temp.z / heightMapScale.z);

			//Bullet Update
			CBullet* bullet = dynamic_cast<CBullet*>(*it);
			if (bullet != NULL)
			{
				bullet->Update(dt);

				if (bullet->getPos().y <= tempY)
				{
					for (unsigned a = 0; a < 5; ++a)
					{
						Vector3 pos = bullet->getPos() + -(bullet->getDirection() * 50);
						Vector3 direction = -bullet->getDirection();
						direction.x += Math::RandFloatMinMax(-direction.x * 200, direction.x * 200);
						direction.y += Math::RandFloatMinMax(20, 100);
						direction.z += Math::RandFloatMinMax(-direction.z * 200, direction.z * 200);

						generateParticle(dt, pos, direction, 2, Particle::e_YELLOW);
					}
					bullet->setActive(false);
				}
			}

			//Ai Update
			AI* ai = dynamic_cast<AI*>(*it);
			if (ai != NULL)
			{
				ai->Update(dt, m_cAvatar->getPos(), tempY + 14);
			}
		}
	}

	//Grid updates
	for (unsigned a = 0; a < m_grid->m_cells.size(); ++a)
	{
		int x = a % m_grid->m_numXCells;
		int z = a / m_grid->m_numXCells;

		Cell& cell = m_grid->m_cells[a];

		//Loop thought everything in a cell
		for (unsigned i = 0; i < cell.GOList.size(); ++i)
		{
			CGameObject* go = cell.GOList[i];

			if (go->getActive())
			{
				checkCollision(go, cell.GOList, i + 1);

				//Update Collision with neighbout cells
				if (x > 0)
				{
					//Left Cell
					checkCollision(go, m_grid->getCell(x - 1, z)->GOList, 0);

					if (z > 0)
					{
						//Top Left Cell
						checkCollision(go, m_grid->getCell(x - 1, z - 1)->GOList, 0);
					}

					//Bottom Left Cell
					if (z < m_grid->m_numZCells - 1)
					{
						checkCollision(go, m_grid->getCell(x - 1, z + 1)->GOList, 0);
					}
				}

				//Up cell
				if (z > 0)
				{
					checkCollision(go, m_grid->getCell(x, z - 1)->GOList, 0);
				}
			}
		}
	}
}

void SceneGame::generateParticle(const double &dt, Vector3 pos, Vector3 direction, double timeLimit, Particle::COLORS color)
{
	Particle* particle = fetchParticle();
	particle->restartParticles(pos, direction, timeLimit, color);
}

void SceneGame::ParticleUpdate(const double& dt)
{
	for (Particle* particle : particleList)
	{
		if (particle->getActive())
		{
			particle->update(dt);
		}
	}
}