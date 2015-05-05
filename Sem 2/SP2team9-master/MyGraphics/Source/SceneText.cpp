#include "SceneText.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

#include "Vertex.h"
#include "LoadTGA.h"

SceneText::SceneText()
{
}

SceneText::~SceneText()
{
}

void SceneText::Init()
{
	// Set background color to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);
	//Enable back face culling
	glEnable(GL_CULL_FACE);
	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	
	//Load vertex and fragment shaders
	//m_programID = LoadShaders( "Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader" );
	//m_programID = LoadShaders( "Shader//Texture.vertexshader", "Shader//Texture.fragmentshader" );
	//m_programID = LoadShaders( "Shader//Texture.vertexshader", "Shader//Blending.fragmentshader" );
	// Use our shader

	
	//variable to rotate geometry
	rotateAngle = 0;

	fps = 0.0f;

	Framerate = "FPS: ";
	//Initialize camera settings
	camera.Init(Vector3(0, 0, 60), Vector3(0, 0, 0), Vector3(0, 1, 0));
	
	//Initialize all meshes to NULL
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference",Color(1,1,1),1000, 1000, 1000);

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 10000.f);
	projectionStack.LoadMatrix(projection);

	m_programID = LoadShaders( "Shader//Texture.vertexshader", "Shader//Text.fragmentshader" );
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	// Light 1
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHT0_TYPE] = glGetUniformLocation(m_programID, "lights[0].type");
	m_parameters[U_LIGHT0_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[0].spotDirection");
	m_parameters[U_LIGHT0_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[0].cosCutoff");
	m_parameters[U_LIGHT0_COSINNER] = glGetUniformLocation(m_programID, "lights[0].cosInner");
	m_parameters[U_LIGHT0_EXPONENT] = glGetUniformLocation(m_programID, "lights[0].exponent");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	// Light2
	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	//Text Related
	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	glUseProgram(m_programID);

	//Light 1
	lights[0].type = Light::LIGHT_SPOT;
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

	//Light 2
	lights[1].type = Light::LIGHT_SPOT;
	lights[1].position.Set(5, 20, 0);
	lights[1].color.Set(1, 1, 1);
	lights[1].power = 1;
	lights[1].kC = 1.f;
	lights[1].kL = 0.01f;
	lights[1].kQ = 0.001f;
	lights[1].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[1].cosInner = cos(Math::DegreeToRadian(30));
	lights[1].exponent = 3.f;
	lights[1].spotDirection.Set(0.f, 1.f, 0.f);

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_NUMLIGHTS], 2);

	//Light 1
	glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &lights[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], lights[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], lights[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], lights[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], lights[0].kQ);
	glUniform1f(m_parameters[U_LIGHT0_COSCUTOFF], lights[0].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT0_COSINNER], lights[0].cosInner);
	glUniform1f(m_parameters[U_LIGHT0_EXPONENT], lights[0].exponent);

	//Light 2
	glUniform1i(m_parameters[U_LIGHT1_TYPE], lights[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &lights[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], lights[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], lights[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], lights[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], lights[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], lights[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], lights[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], lights[1].exponent);

	//Sky Box
	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//front.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//back.tga");

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//left.tga");

	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//right.tga");

	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//top.tga");

	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//bottom.tga");

	//Mario
	meshList[GEO_MARIO] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_MARIO]->textureID = LoadTGA("Image//Mario3.tga");

	//Light ball
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 1, 1), 10, 10, 1);

	meshList[GEO_LIGHTBALL2] = MeshBuilder::GenerateSphere("lightball2", Color(1, 1, 1), 10, 10, 1);

	//Quad texture
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f,1.f);
	meshList[GEO_QUAD]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_QUAD]->material.kShininess = 8.f;
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//color2.tga");

	//Model 1
	meshList[GEO_MODEL1] = MeshBuilder::GenerateOBJ("model1", "OBJ//chair.obj");
	meshList[GEO_MODEL1]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_MODEL1]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_MODEL1]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MODEL1]->material.kShininess = 8.f;
	meshList[GEO_MODEL1]->textureID = LoadTGA("Image//chair.tga");

	//Model 2
	meshList[GEO_MODEL2] = MeshBuilder::GenerateOBJ("model2", "OBJ//doorman.obj");
	meshList[GEO_MODEL2]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_MODEL2]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_MODEL2]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MODEL2]->material.kShininess = 8.f;
	meshList[GEO_MODEL2]->textureID = LoadTGA("Image//doorman.tga");

	
	//Model 3
	meshList[GEO_MODEL3] = MeshBuilder::GenerateOBJ("model3", "OBJ//dartboard.obj");
	meshList[GEO_MODEL3]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_MODEL3]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_MODEL3]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MODEL3]->material.kShininess = 8.f;
	meshList[GEO_MODEL3]->textureID = LoadTGA("Image//dartboard.tga");

	//Model 4
	meshList[GEO_MODEL4] = MeshBuilder::GenerateOBJ("model4", "OBJ//dart.obj");
	meshList[GEO_MODEL4]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_MODEL4]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_MODEL4]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MODEL4]->material.kShininess = 8.f;
	meshList[GEO_MODEL4]->textureID = LoadTGA("Image//dart.tga");

	//Model 5
	meshList[GEO_MODEL5] = MeshBuilder::GenerateOBJ("model4", "OBJ//winebottle.obj");
	meshList[GEO_MODEL5]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_MODEL5]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_MODEL5]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MODEL5]->material.kShininess = 8.f;
	meshList[GEO_MODEL5]->textureID = LoadTGA("Image//winebottle.tga");

	//Model 6
	meshList[GEO_MODEL6] = MeshBuilder::GenerateOBJ("model4", "OBJ//shoe.obj");
	meshList[GEO_MODEL6]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_MODEL6]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_MODEL6]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MODEL6]->material.kShininess = 8.f;
	meshList[GEO_MODEL6]->textureID = LoadTGA("Image//shoe.tga");

	//Text Related
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//calibri.tga");

}

bool B_Light5 = true;
static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;
string result;

void SceneText::Update(double dt)
{
	float LSPEED = 10.f;
	
	if(Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	//Light1
	if(Application::IsKeyPressed('I'))
		lights[0].position.z -= (float)(LSPEED * dt);
	if(Application::IsKeyPressed('K'))
		lights[0].position.z += (float)(LSPEED * dt);
	if(Application::IsKeyPressed('J'))
		lights[0].position.x -= (float)(LSPEED * dt);
	if(Application::IsKeyPressed('L'))
		lights[0].position.x += (float)(LSPEED * dt);
	if(Application::IsKeyPressed('O'))
		lights[0].position.y -= (float)(LSPEED * dt);
	if(Application::IsKeyPressed('P'))
		lights[0].position.y += (float)(LSPEED * dt);

	//Light2
	if(Application::IsKeyPressed('T'))
		lights[1].position.z -= (float)(LSPEED * dt);
	if(Application::IsKeyPressed('G'))
		lights[1].position.z += (float)(LSPEED * dt);
	if(Application::IsKeyPressed('F'))
		lights[1].position.x -= (float)(LSPEED * dt);
	if(Application::IsKeyPressed('H'))
		lights[1].position.x += (float)(LSPEED * dt);
	if(Application::IsKeyPressed('Y'))
		lights[1].position.y -= (float)(LSPEED * dt);
	if(Application::IsKeyPressed('U'))
		lights[1].position.y += (float)(LSPEED * dt);

	if(Application::IsKeyPressed('5'))
	{
		B_Light5 = true;
	}
	if(Application::IsKeyPressed('6'))
	{
		B_Light5 = false;
	}

	rotateAngle += (float)(10 * dt);

	//Light 1
	if(Application::IsKeyPressed('Z'))
	{
		lights[0].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}
	else if(Application::IsKeyPressed('X'))
	{
		lights[0].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}
	else if(Application::IsKeyPressed('C'))
	{
		lights[0].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}

	//Light 2
	if(Application::IsKeyPressed('Q'))
	{
		lights[1].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT1_TYPE], lights[1].type);
	}
	else if(Application::IsKeyPressed('E'))
	{
		lights[1].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT1_TYPE], lights[1].type);
	}
	else if(Application::IsKeyPressed('R'))
	{
		lights[1].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT1_TYPE], lights[1].type);
	}

	std::ostringstream ss;
	fps = 1/dt;
	ss << fps;
	result = ss.str();
	camera.Update(dt);
}

void SceneText::RenderSkybox()
{
	//Front
	modelStack.PushMatrix();
	modelStack.Translate(0.f, 0.f, 500.f);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1000.f, 1000.f, 1000.f);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	//Back
	modelStack.PushMatrix();
	modelStack.Translate(0.f, 0.f, -500.f);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(-180, 1, 0, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(-180, 0, 0, 1);
	modelStack.Scale(1000.f, 1000.f, 1000.f);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Top
	modelStack.PushMatrix();
	modelStack.Translate(0.f, 500.f, 0.f);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(270, 0, 0, 1);
	modelStack.Scale(1000.f, 1000.f, 1000.f);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Bottom
	modelStack.PushMatrix();
	modelStack.Translate(0.f, -500.f, 0.f);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(1000.f, 1000.f, 1000.f);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Left
	modelStack.PushMatrix();
	modelStack.Translate(500.f, 0.f, 0.f);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(-180, 0, 1, 0);
	modelStack.Scale(1000.f, 1000.f, 1000.f);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Right
	modelStack.PushMatrix();
	modelStack.Translate(-500.f, 0.f, 0.f);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(1000.f, 1000.f, 1000.f);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void SceneText::Render()
{
	//clear depth and color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Temp variables
	Mtx44 MVP;

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);
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

	//Light2
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
	//Texture

	modelStack.PushMatrix();
	modelStack.Translate(lights[1].position.x, lights[1].position.y, lights[1].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL2], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(lights[0].position.x, lights[0].position.y, lights[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-20.f, 0.f, -20.f);
	modelStack.Scale(10.f, 10.f, 10.f);
	modelStack.PopMatrix();

	//modelStack.PushMatrix();

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	RenderMesh(meshList[GEO_AXES], false);

	//Rendering skybox
	RenderSkybox();

	//Render Mario
	modelStack.PushMatrix();
	modelStack.Translate(0.f, 0.f, 0.f);
	modelStack.Rotate(0, 1, 0, 0);
	modelStack.Scale(50.f, 50.f, 50.f);
	//RenderMesh(meshList[GEO_MARIO], false);
	modelStack.PopMatrix();

	////Render Model 1
	//modelStack.PushMatrix();
	//modelStack.Translate(0.f, 0.f, 0.f);
	//modelStack.Rotate(0, 1, 0, 0);
	//modelStack.Scale(1.f, 1.f, 1.f);
	////RenderMesh(meshList[GEO_MODEL1], B_Light5);
	//modelStack.PopMatrix();

	////Render Model 2
	//modelStack.PushMatrix();
	//modelStack.Translate(0.f, 0.f, 0.f);
	//modelStack.Rotate(0, 1, 0, 0);
	//modelStack.Scale(3.f, 3.f, 3.f);
	////RenderMesh(meshList[GEO_MODEL2], B_Light5);
	//modelStack.PopMatrix();

	////Render Model 3
	//modelStack.PushMatrix();
	//modelStack.Translate(0.f, 0.f, 0.f);
	//modelStack.Rotate(0, 1, 0, 0);
	//modelStack.Scale(3.f, 3.f, 3.f);
	////RenderMesh(meshList[GEO_MODEL3], B_Light5);
	//modelStack.PopMatrix();

	////Render Model 4
	//modelStack.PushMatrix();
	//modelStack.Translate(0.f, 0.f, -20.f);
	//modelStack.Rotate(0, 1, 0, 0);
	//modelStack.Scale(3.f, 3.f, 3.f);
	//RenderMesh(meshList[GEO_MODEL4], B_Light5);
	//modelStack.PopMatrix();

	////Render Model 5
	//modelStack.PushMatrix();
	//modelStack.Translate(0.f, 0.f, 20.f);
	//modelStack.Rotate(0, 1, 0, 0);
	//modelStack.Scale(3.f, 3.f, 3.f);
	//RenderMesh(meshList[GEO_MODEL5], B_Light5);
	//modelStack.PopMatrix();

	////Render Model 6
	//modelStack.PushMatrix();
	//modelStack.Translate(20.f, 20.f, 0.f);
	//modelStack.Rotate(0, 1, 0, 0);
	//modelStack.Scale(5.f, 5.f, 5.f);
	//RenderMesh(meshList[GEO_MODEL6], B_Light5);
	//modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.f, 0.f, 0.f);
	modelStack.Rotate(0, 1, 0, 0);
	modelStack.Scale(10.f, 10.f, 10.f);
	RenderText(meshList[GEO_TEXT], "Hello World", Color(0, 1, 0));
	modelStack.PopMatrix();

	RenderTextOnScreen(meshList[GEO_TEXT], "Hello Screen", Color(0, 1, 0), 3, 1, 1);
	RenderTextOnScreen(meshList[GEO_TEXT], Framerate + result, Color(0, 1, 0), 3, 1, 2);
}

void SceneText::RenderMesh(Mesh *mesh, bool enableLight)
{
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
	if(enableLight)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
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

	mesh->Render(); //this line should only be called once 
	if(mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

void SceneText::RenderText(Mesh* mesh, std::string text, Color color)
{
	if(!mesh || mesh->textureID <= 0) //Proper error check
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
	if(!mesh || mesh->textureID <= 0) //Proper error check
		return;
	
	glDisable(GL_DEPTH_TEST);
	//Add these code just after glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	ortho.SetToOrtho(0, 80, 0, 60, -10, 10); //size of screen UI
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity(); //No need camera for ortho mode
	modelStack.PushMatrix();
	modelStack.LoadIdentity(); //Reset modelStack
	modelStack.Scale(size, size, size);
	modelStack.Translate(x, y, 0);

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
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void SceneText::Exit()
{
	// Cleanup here
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if(meshList[i] != NULL)
			delete meshList[i];
	}
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
