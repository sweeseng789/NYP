#include "SceneText.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>

SceneText::SceneText()
{
}

SceneText::~SceneText()
{
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
	weapon.setWeapon(WeaponIcon_Sword, "Close Range");

	meshList[WeaponIcon_Pistol] = MeshBuilder::GenerateQuad("Weapon Icon Pistol", Color(1, 1, 1), 1.0f);
	meshList[WeaponIcon_Pistol]->textureID = LoadTGA("Image//WeaponIcon_Pistol.tga");
	weapon.setWeapon(WeaponIcon_Pistol, "Long Range");

	meshList[WeaponIcon_Sniper] = MeshBuilder::GenerateQuad("Weapon Icon Sniper", Color(1, 1, 1), 1.0f);
	meshList[WeaponIcon_Sniper]->textureID = LoadTGA("Image//WeaponIcon_Sniper.tga");
	weapon.setWeapon(WeaponIcon_Sniper, "Long Range");

	meshList[WeaponIcon_SMG] = MeshBuilder::GenerateQuad("Weapon Icon SMG", Color(1, 1, 1), 1.0f);
	meshList[WeaponIcon_SMG]->textureID = LoadTGA("Image//WeaponIcon_SMG.tga");
	weapon.setWeapon(WeaponIcon_SMG, "Long Range");

	meshList[Healthbar] = MeshBuilder::GenerateQuad("healthbar", Color(255/253, 255/253, 255/253), 1.f);

	//Variable
	moving = 100;

	// Projection matrix : 45� Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	rotateAngle = 0;

	bLightEnabled = true;
}

void SceneText::Update(double dt)
{
	/*if(Application::IsKeyPressed('1'))
	glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('2'))
	glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if(Application::IsKeyPressed('4'))
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/

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

	rotateAngle += (float)(10 * dt);

	camera.Update(dt);

	fps = (float)(1.f / dt);

	if (Application::IsKeyPressed('9'))
		moving += 1;
	if (Application::IsKeyPressed('8'))
		moving -= 1;

	if (moving < 0)
		moving = 0;
	if (moving > 100)
		moving = 100;

	weapon.update((float)dt);
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

void SceneText::RenderMeshIn2D(Mesh *mesh, bool enableLight, float sizeX, float sizeY, float x, float y)
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
	modelStack.Translate(x, y, 0);

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

	if (weapon.returnSwordConfirmation() == false)
	{
		RenderMeshIn2D(meshList[HudBackground], true, 20.0f, 5.0f, 3.49f, -11.5f);//background for ready screen
	}


	//===============Weapon Chosen==============//
	RenderMeshIn2D(meshList[HudBackground], true, 13.0f, 13.0f, -4.4f, 2.9f);//bakcground for ammo
	RenderMeshIn2D(meshList[HudBackground], true, 13.0f, 13.0f, -4.4f, 1.8f);//background for round
	//==============Round============//
	RenderMeshIn2D(meshList[RoundIcon], true, 13.0f, 13.0f, -5.5f, 1.8f);//Round icon

	//=====================SWORD=====================//
	if (weapon.returnSwordConfirmation() == true)
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
	else if (weapon.returnPistolConfirmation() == true)//player is using pistol
	{
		RenderMeshIn2D(meshList[BulletIcon], true, 13.0f, 13.0f, -5.5f, 2.9f);//Bullet icon

		if (weapon.ammo[1].returnAmmos() < 10)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], to_string((long long)weapon.ammo[1].returnAmmos()), Color(1.0f, 1.0f, 1.0f), 3.0f, 10.8f, 47.5f);
		}
		else
		{
			RenderTextOnScreen(meshList[GEO_TEXT], to_string((long long)weapon.ammo[1].returnAmmos()), Color(1.0f, 1.0f, 1.0f), 3.0f, 9.5f, 47.5f);
		}

		RenderTextOnScreen(meshList[GEO_TEXT], to_string((long long)weapon.ammo[1].returnRounds()), Color(1.0f, 1.0f, 1.0f), 3.0f, 10.8f, 40.0f);

		RenderMeshIn2D(meshList[WeaponIcon_Pistol], true, 40.5f, 40.5f, -0.7f, 0.925f);// This is the icon for long ranged weapon

		if (weapon.ammo[1].returnReloading() == true) //reloading
		{
			RenderMeshIn2D(meshList[HudBackground], true, 80.0f, 10.0f, 0.01f, 0.2f);//background for reload screen
			RenderTextOnScreen(meshList[GEO_TEXT], "Reload in", Color(1.0f, 1.0f, 1.0f), 3.0f, 25.0f, 29.5f);
			RenderTextOnScreen(meshList[GEO_TEXT], to_string((long long)weapon.ammo[1].returnReloadTime_Pistol()), Color(1.0f, 1.0f, 1.0f), 3.0f, 55.0f, 29.5f);
		}

		if (weapon.ammo[1].returnReadyToShootPistol() == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Ready", Color(1.0f, 1.0f, 1.0f), 2.0f, 70.7f, 0.3f);
		}
	}//=====================SNIPER=====================//
	else if (weapon.returnSniperConfirmation() == true)//player is using sniper
	{
		RenderMeshIn2D(meshList[BulletIcon], true, 13.0f, 13.0f, -5.5f, 2.9f);//Bullet icon

		RenderTextOnScreen(meshList[GEO_TEXT], to_string((long long)weapon.ammo[2].returnAmmos()), Color(1.0f, 1.0f, 1.0f), 3.0f, 10.8f, 47.5f);

		RenderTextOnScreen(meshList[GEO_TEXT], to_string((long long)weapon.ammo[2].returnRounds()), Color(1.0f, 1.0f, 1.0f), 3.0f, 10.8f, 40.0f);

		RenderMeshIn2D(meshList[WeaponIcon_Sniper], true, 40.5f, 40.5f, -0.7f, 0.925f);// This is the icon for logn ranged weapon

		if (weapon.ammo[2].returnReloading() == true)
		{
			RenderMeshIn2D(meshList[HudBackground], true, 80.0f, 10.0f, 0.01f, 0.2f);//background for reload screen
			RenderTextOnScreen(meshList[GEO_TEXT], "Reload in", Color(1.0f, 1.0f, 1.0f), 3.0f, 25.0f, 29.5f);
			RenderTextOnScreen(meshList[GEO_TEXT], to_string((long long)weapon.ammo[2].returnReloadTime_Sniper()), Color(1.0f, 1.0f, 1.0f), 3.0f, 55.0f, 29.5f);
		}

		if (weapon.ammo[2].returnReadyToShootSniper() == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Ready", Color(1.0f, 1.0f, 1.0f), 2.0f, 70.7f, 0.3f);
		}
	}//=====================SMG=====================//
	else if (weapon.returnSMGConfirmation() == true)//player is using SMG
	{
		RenderMeshIn2D(meshList[BulletIcon], true, 13.0f, 13.0f, -5.5f, 2.9f);//Bullet icon

		if (weapon.ammo[3].returnAmmos() < 10)//Arranging bullet number to middle if it is less than 10
		{
			RenderTextOnScreen(meshList[GEO_TEXT], to_string((long long)weapon.ammo[3].returnAmmos()), Color(1.0f, 1.0f, 1.0f), 3.0f, 10.8f, 47.5f);
		}
		else
		{	
			RenderTextOnScreen(meshList[GEO_TEXT], to_string((long long)weapon.ammo[3].returnAmmos()), Color(1.0f, 1.0f, 1.0f), 3.0f, 9.5f, 47.5f);
		}


		RenderTextOnScreen(meshList[GEO_TEXT], to_string((long long)weapon.ammo[3].returnRounds()), Color(1.0f, 1.0f, 1.0f), 3.0f, 10.8f, 40.0f);

		RenderMeshIn2D(meshList[WeaponIcon_SMG], true, 40.5f, 40.5f, -0.7f, 0.925f);// This is the icon for logn ranged weapon

		if (weapon.ammo[3].returnReloading() == true)//Reloading
		{
			RenderMeshIn2D(meshList[HudBackground], true, 80.0f, 10.0f, 0.01f, 0.2f);//background for reload screen
			RenderTextOnScreen(meshList[GEO_TEXT], "Reload in", Color(1.0f, 1.0f, 1.0f), 3.0f, 25.0f, 29.5f);
			RenderTextOnScreen(meshList[GEO_TEXT], to_string((long long)weapon.ammo[3].returnReloadTime_SMG()), Color(1.0f, 1.0f, 1.0f), 3.0f, 55.0f, 29.5f);
		}

		if (weapon.ammo[3].returnReadyToShootSMG() == true)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Ready", Color(1.0f, 1.0f, 1.0f), 2.0f, 70.7f, 0.3f);
		}
	}

	//==================CrossHair=============//
	RenderMeshIn2D(meshList[GEO_CROSSHAIR], true, 3.0f, 3.0f, 0 , 0);
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

	RenderMesh(meshList[GEO_AXES], false);

	modelStack.PushMatrix();
	modelStack.Translate(lights[0].position.x, lights[0].position.y, lights[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	RenderSkybox();

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
	modelStack.Translate(20, 0, -20);
	RenderMesh(meshList[GEO_OBJECT], true);
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

	RenderTextOnScreen(meshList[GEO_TEXT], "Hello Screen", Color(0, 1, 0), 3, 0, 0);

	RenderHUD();
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