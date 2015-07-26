#include "SceneBase.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>

SceneBase::SceneBase()
{
}

SceneBase::~SceneBase()
{
}

void SceneBase::Init()
{
	// Black background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
	// Enable depth test
	//glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 
	
	glEnable(GL_CULL_FACE);
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);

	m_programID = LoadShaders( "Shader//comg.vertexshader", "Shader//comg.fragmentshader" );
	
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
	
	glUniform1i(m_parameters[U_NUMLIGHTS], 0);
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

	camera.Init(Vector3(0, 0, 1), Vector3(0, 0, 0), Vector3(0, 1, 0));

	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	meshList[GEO_LINE] = MeshBuilder::GenerateLine("reference", Color(0, 1, 0), 100);
	meshList[GEO_POWERBAR_LINE] = MeshBuilder::GenerateLine("reference", Color(1, 1, 1), 4);
	meshList[GEO_BALL] = MeshBuilder::GenerateSphere("ball", Color(1, 0, 0), 10, 10, 1.f);
	meshList[GEO_BALL2] = MeshBuilder::GenerateSphere("ball", Color(1, 1, 0), 10, 10, 1.f);
	meshList[GEO_BALL3] = MeshBuilder::GenerateSphere("ball", Color(1, 0, 1), 10, 10, 1.f);
	meshList[GEO_BALL4] = MeshBuilder::GenerateSphere("ball", Color(0, 1,0), 10, 10, 1.f);
	meshList[GEO_BALL5] = MeshBuilder::GenerateSphere("ball", Color(1, 1, 0), 10, 10, 1.f);
	meshList[GEO_BALL6] = MeshBuilder::GenerateSphere("ball", Color(0, 1, 1), 10, 10, 1.f);
	meshList[GEO_BALL7] = MeshBuilder::GenerateSphere("ball", Color(0, 0, 1), 10, 10, 1.f);
	meshList[GEO_BALL8] = MeshBuilder::GenerateSphere("ball", Color(1, 1, 1), 10, 10, 1.f);
	meshList[GEO_BALL9] = MeshBuilder::GenerateSphere("ball", Color(1, 1, 1), 10, 10, 1.f);
	meshList[GEO_BALL10] = MeshBuilder::GenerateSphere("ball", Color(1, 1, 1), 10, 10, 1.f);
	meshList[GEO_BALL11] = MeshBuilder::GenerateSphere("ball", Color(1, 1, 1), 10, 10, 1.f);
	meshList[GEO_BALL12] = MeshBuilder::GenerateSphere("ball", Color(1, 1, 1), 10, 10, 1.f);
	meshList[GEO_BALL13] = MeshBuilder::GenerateSphere("ball", Color(1, 1, 1), 10, 10, 1.f);
	meshList[GEO_BALL14] = MeshBuilder::GenerateSphere("ball", Color(1, 1, 1), 10, 10, 1.f);
	meshList[GEO_BALL15] = MeshBuilder::GenerateSphere("ball", Color(1, 1, 1), 10, 10, 1.f);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(0.48235294117, 0.26274509803, 0.21176470588), 1.f);
	meshList[GEO_CUBE2] = MeshBuilder::GenerateCube("cube", Color(0.32156862745, 0.32156862745, 0.32156862745), 1.f);
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);

	meshList[Power_Bar] = MeshBuilder::GenerateQuad("Gameover screen", Color(1, 1, 1), 1);
	meshList[Power_Bar]->textureID = LoadTGA("Image//Phyics//Power Bar.tga");

	meshList[GEO_PLAYER1_TURN] = MeshBuilder::GenerateQuad("Gameover screen", Color(1, 1, 1), 1);
	meshList[GEO_PLAYER1_TURN]->textureID = LoadTGA("Image//Phyics//Player1Turn.tga");

	meshList[GEO_PLAYER2_TURN] = MeshBuilder::GenerateQuad("Gameover screen", Color(1, 1, 1), 1);
	meshList[GEO_PLAYER2_TURN]->textureID = LoadTGA("Image//Phyics//Player2Turn.tga");


	meshList[Spaceship] = MeshBuilder::GenerateQuad("Spaceship", Color(1, 1, 1), 1);
	meshList[Spaceship]->textureID = LoadTGA("Image//Spaceship.tga");

	meshList[Spaceship_Thurster] = MeshBuilder::GenerateQuad("Spaceship forward thruster", Color(1, 1, 1), 1);
	meshList[Spaceship_Thurster]->textureID = LoadTGA("Image//Spaceship_Thurster.tga");

	meshList[SpaceShip_Thurster_back] = MeshBuilder::GenerateQuad("Spaceship backward thruster", Color(1, 1, 1), 1);
	meshList[SpaceShip_Thurster_back]->textureID = LoadTGA("Image//Spaceship_Thurster_back.tga");

	meshList[Laser] = MeshBuilder::GenerateQuad("Spaceship Laser Sprite", Color(1, 1, 1), 1);
	meshList[Laser]->textureID = LoadTGA("Image//Laser_Sprite.tga");

	meshList[Asteroid_Sprite] = MeshBuilder::GenerateQuad("Asteroid Sprite", Color(1, 1, 1), 1);
	meshList[Asteroid_Sprite]->textureID = LoadTGA("Image//Asteroid_Sprite.tga");

	meshList[Background] = MeshBuilder::GenerateQuad("Background", Color(1, 1, 1), 1);
	meshList[Background]->textureID = LoadTGA("Image//Background.tga");

	meshList[Explosion_Asteroid] = MeshBuilder::GenerateQuad("Explosion for Asteroid", Color(1, 1, 1), 1);
	meshList[Explosion_Asteroid]->textureID = LoadTGA("Image//Explosion.tga");

	meshList[Bomb] = MeshBuilder::GenerateQuad("Landmine", Color(1, 1, 1), 1);
	meshList[Bomb]->textureID = LoadTGA("Image//Landmine.tga");

	meshList[HUD] = MeshBuilder::GenerateQuad("HUD", Color(1, 1, 1), 1);
	meshList[HUD]->textureID = LoadTGA("Image//HUD.tga");

	meshList[Enemy] = MeshBuilder::GenerateQuad("Enemy", Color(1, 1, 1), 1);
	meshList[Enemy]->textureID = LoadTGA("Image//Enemy_Ship.tga");

	meshList[Enemy_Laser] = MeshBuilder::GenerateQuad("Enemy Laser", Color(1, 1, 1), 1);
	meshList[Enemy_Laser]->textureID = LoadTGA("Image//Enemy_Laser_Sprite.tga");

	meshList[black_background] = MeshBuilder::GenerateQuad("Black Background", Color(1, 1, 1), 1);
	meshList[black_background]->textureID = LoadTGA("Image//black_background.tga");

	meshList[heart] = MeshBuilder::GenerateQuad("Heart", Color(1, 1, 1), 1);
	meshList[heart]->textureID = LoadTGA("Image//heart.tga");

	meshList[Missile] = MeshBuilder::GenerateQuad("Missile", Color(1, 1, 1), 1);
	meshList[Missile]->textureID = LoadTGA("Image//Missile.tga");

	meshList[PowerUp_Ironman] = MeshBuilder::GenerateQuad("Ironman", Color(1, 1, 1), 1);
	meshList[PowerUp_Ironman]->textureID = LoadTGA("Image//Ironman.tga");

	meshList[Boss] = MeshBuilder::GenerateQuad("Boss", Color(1, 1, 1), 1);
	meshList[Boss]->textureID = LoadTGA("Image//Boss.tga");

	meshList[Boss_Shield] = MeshBuilder::GenerateQuad("Boss with Shield", Color(1, 1, 1), 1);
	meshList[Boss_Shield]->textureID = LoadTGA("Image//Boss_Shield.tga");

	meshList[StartMenu] = MeshBuilder::GenerateQuad("Main menu screen", Color(1, 1, 1), 1);
	meshList[StartMenu]->textureID = LoadTGA("Image//MenuTGA//StartScreen.tga");

	meshList[StartTrue] = MeshBuilder::GenerateQuad("Start is true", Color(1, 1, 1), 1);
	meshList[StartTrue]->textureID = LoadTGA("Image//MenuTGA//StartTrue.tga");

	meshList[ControlTrue] = MeshBuilder::GenerateQuad("Control is true", Color(1, 1, 1), 1);
	meshList[ControlTrue]->textureID = LoadTGA("Image//MenuTGA//ControlTrue.tga");

	meshList[ExitTrue] = MeshBuilder::GenerateQuad("Exit is true", Color(1, 1, 1), 1);
	meshList[ExitTrue]->textureID = LoadTGA("Image//MenuTGA//ExitTrue.tga");

	meshList[ShowControl] = MeshBuilder::GenerateQuad("Show Control is true", Color(1, 1, 1), 1);
	meshList[ShowControl]->textureID = LoadTGA("Image//MenuTGA//ControlScreen.tga");

	meshList[GameoverScreen] = MeshBuilder::GenerateQuad("Gameover screen", Color(1, 1, 1), 1);
	meshList[GameoverScreen]->textureID = LoadTGA("Image//MenuTGA//Gameover.tga");

	meshList[WinScreen] = MeshBuilder::GenerateQuad("Gameover screen", Color(1, 1, 1), 1);
	meshList[WinScreen]->textureID = LoadTGA("Image//MenuTGA//Win.tga");

	bLightEnabled = false;
}

void SceneBase::Update(double dt)
{
	//Keyboard Section
	if(Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	fps = (float)(1.f / dt);

	if (Application::IsKeyPressed('W'))
	{
		//If i press W, render the thruster
		meshList[Spaceship]->textureID = LoadTGA("Image//Spaceship_Thurster.tga");
	}
	else if (Application::IsKeyPressed('S'))
	{
		//If i press S, render the thruster
		meshList[Spaceship]->textureID = LoadTGA("Image//Spaceship_Thurster_back.tga");
	}
	else
	{
		meshList[Spaceship]->textureID = LoadTGA("Image//Spaceship.tga");
	}
}

void SceneBase::RenderText(Mesh* mesh, std::string text, Color color)
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

void SceneBase::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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
		characterSpacing.SetToTranslation(i * 0.6f + 0.5f, 0.5f, 0); //1.0f is the spacing of each character, you may change this value
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

void SceneBase::RenderMesh(Mesh *mesh, bool enableLight)
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

void SceneBase::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void SceneBase::Exit()
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
