/****************************************************************************/
/*!
\file GameOfLife.cpp
\author Ong Swee Seng
\brief GameOfLife.cpp is used to set, render and update geometries with parameters.
*/
/****************************************************************************/

#include "GameOfLife.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Utility.h"

#include "Application.h"
#include "MeshBuilder.h"


GameOfLife::GameOfLife()
{
}

GameOfLife::~GameOfLife()
{
}

void GameOfLife::Init()
{
	// Init VBO here
	
	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	
	/*//Load vertex and fragment shaders
	m_programID = LoadShaders( "Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader" );
	// Use our shader
	glUseProgram(m_programID);
	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");*/
	m_programID = LoadShaders( "Shader//Shading.vertexshader", "Shader//Shading.fragmentshader" );
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	m_parameters[U_MODELVIEW] = glGetUniformLocation(m_programID, "MV");
	m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE] = glGetUniformLocation(m_programID, "MV_inverse_transpose");
	m_parameters[U_MATERIAL_AMBIENT] = glGetUniformLocation(m_programID, "material.kAmbient");
	m_parameters[U_MATERIAL_DIFFUSE] = glGetUniformLocation(m_programID, "material.kDiffuse");
	m_parameters[U_MATERIAL_SPECULAR] = glGetUniformLocation(m_programID, "material.kSpecular");
	m_parameters[U_MATERIAL_SHININESS] = glGetUniformLocation(m_programID, "material.kShininess");
	m_parameters[U_LIGHT0_POSITION] = glGetUniformLocation(m_programID, "lights[0].position_cameraspace");
	m_parameters[U_LIGHT0_COLOR] = glGetUniformLocation(m_programID, "lights[0].color");
	m_parameters[U_LIGHT0_POWER] = glGetUniformLocation(m_programID, "lights[0].power");
	m_parameters[U_LIGHT0_KC] = glGetUniformLocation(m_programID, "lights[0].kC");
	m_parameters[U_LIGHT0_KL] = glGetUniformLocation(m_programID, "lights[0].kL");
	m_parameters[U_LIGHT0_KQ] = glGetUniformLocation(m_programID, "lights[0].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	glUseProgram(m_programID);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	//Initialize camera settings
	camera.Init(Vector3(40, 30, 30), Vector3(0, 0, 0), Vector3(0, 1, 0));

	//remove all glGenBuffers, glBindBuffer, glBufferData code
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	
	//meshList[GEO_CYLINDER] = MeshBuilder::GenerateCylinder("Cylinder", Color(0.95686274509, 0.86274509803, 0.14901960784), 18, 36, 1.f);
	meshList[GEO_CUBE1] = MeshBuilder::GenerateCube("cube1", Color(1, 0, 1), 5);
	/*//meshList[GEO_RING] = MeshBuilder::GenerateRing("ring", Color(0, 1, 1), 36, 1.f, 0.5f);
	meshList[GEO_SUN] = MeshBuilder::GenerateSphere("Sun", Color(1, 1, 0), 18, 36, 1.f);
	meshList[GEO_MERCURY] = MeshBuilder::GenerateSphere("Mercury", Color(0.50196078431, 0.50196078431, 0.50196078431), 18, 36, 1.f);
	meshList[GEO_EARTH] = MeshBuilder::GenerateSphere("Earth", Color(0.2, 0.6, 1), 18, 36, 1.f);
	meshList[GEO_EARTH_MOON] = MeshBuilder::GenerateSphere("Earth moon", Color(0.75294117647, 0.75294117647, 0.75294117647), 18, 36, 1.f);
	meshList[GEO_VENUS] = MeshBuilder::GenerateSphere("Venus", Color(1, 0.50196078431, 0), 18, 36, 1.f);
	meshList[GEO_MARS] = MeshBuilder::GenerateSphere("Mars", Color(0.6, 0.29803921568, 0), 18, 36, 1.f);
	meshList[GEO_JUPITER] = MeshBuilder::GenerateSphere("Jupiter", Color(0.2, 0.09803921568, 0), 18, 36, 1.f);
	meshList[GEO_SATURN] = MeshBuilder::GenerateSphere("Jupiter", Color(0.2, 0.09803921568, 0), 18, 36, 1.f);
	meshList[GEO_SATURN_RING] = MeshBuilder::GenerateRing("ring", Color(0, 1, 1), 36, 1.f, 0.5f);*/


	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("Sphere", Color(0.95686274509, 0.86274509803, 0.14901960784), 18, 36, 1.f);
	meshList[GEO_SPHERE]->material.kAmbient.Set(1.0f, 0.90196078431f, 0.17647058823);
	meshList[GEO_SPHERE]->material.kDiffuse.Set(0.f, 1.f, 0.f);
	meshList[GEO_SPHERE]->material.kSpecular.Set(0.95686274509, 0.86274509803, 0.14901960784);
	meshList[GEO_SPHERE]->material.kShininess = 1.f;

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("Floor", Color (0, 1, 1), 1);
	meshList[GEO_QUAD]->material.kAmbient.Set(0.00392156862f, 0.45490196078f, 0.06666666666f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.f, 1.f, 0.f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.f, 0.f, 1.f);
	meshList[GEO_QUAD]->material.kShininess = 1.f;

	meshList[GEO_CONEYellow] = MeshBuilder::GenerateCone("Cone", Color(0.95686274509, 0.86274509803, 0.14901960784), 18, 36, 1.f);
	meshList[GEO_CONEYellow]->material.kAmbient.Set(1.0f, 0.90196078431f, 0.17647058823);
	meshList[GEO_CONEYellow]->material.kDiffuse.Set(0.f, 1.f, 0.f);
	meshList[GEO_CONEYellow]->material.kSpecular.Set(1.0f, 0.90196078431f, 0.17647058823);
	meshList[GEO_CONEYellow]->material.kShininess = 1.f;

	meshList[GEO_CONEBlack] = MeshBuilder::GenerateCone("Cone", Color(0, 0, 0), 18, 36, 1.f);
	meshList[GEO_CONEBlack]->material.kAmbient.Set(0.f, 0.f, 0.f);
	meshList[GEO_CONEBlack]->material.kDiffuse.Set(0.f, 0.f, 0.f);
	meshList[GEO_CONEBlack]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_CONEBlack]->material.kShininess = 1.f;

	meshList[GOE_PIKACHUEYESWHITE] = MeshBuilder::GenerateHemisphere("eyes white", Color(1, 1, 1), 18, 36, 1.f);
	meshList[GOE_PIKACHUEYESWHITE]->material.kAmbient.Set(1.f, 1.f, 1.f);
	meshList[GOE_PIKACHUEYESWHITE]->material.kDiffuse.Set(0.f, 0.f, 0.f);
	meshList[GOE_PIKACHUEYESWHITE]->material.kSpecular.Set(1.f, 1.f, 1.f);
	meshList[GOE_PIKACHUEYESWHITE]->material.kShininess = 1.f;

	meshList[GEO_PIKACHUEYES] = MeshBuilder::GenerateSphere("eyes black", Color(0, 0, 0), 18, 36, 1.f);
	meshList[GEO_PIKACHUEYES]->material.kAmbient.Set(0, 0, 0);
	meshList[GEO_PIKACHUEYES]->material.kDiffuse.Set(0.f, 1.f, 0.f);
	meshList[GEO_PIKACHUEYES]->material.kSpecular.Set(0, 0, 0);
	meshList[GEO_PIKACHUEYES]->material.kShininess = 1.f;

	meshList[GEO_PIKACHUHEADPARTS] = MeshBuilder::GenerateHemisphere("head parts", Color(0.95686274509, 0.86274509803, 0.14901960784), 18, 36, 1.f);
	meshList[GEO_PIKACHUHEADPARTS]->material.kAmbient.Set(1.0f, 0.90196078431f, 0.17647058823);
	meshList[GEO_PIKACHUHEADPARTS]->material.kDiffuse.Set(0.f, 1.f, 0.f);
	meshList[GEO_PIKACHUHEADPARTS]->material.kSpecular.Set(0.95686274509, 0.86274509803, 0.14901960784);
	meshList[GEO_PIKACHUHEADPARTS]->material.kShininess = 1.f;
	
	meshList[GEO_PIKACHUHEADPARTS3] = MeshBuilder::GenerateSphere("Cheeks", Color(0.90588235294, 0.29019607843, 0.27058823529), 18, 36, 1.f);
	meshList[GEO_PIKACHUHEADPARTS3]->material.kAmbient.Set(0.84705882352f, 0.41176470588f, 0.43529411764f);
	meshList[GEO_PIKACHUHEADPARTS3]->material.kDiffuse.Set(0.f, 1.f, 0.f);
	meshList[GEO_PIKACHUHEADPARTS3]->material.kSpecular.Set(0.84705882352f, 0.41176470588f, 0.43529411764f);
	meshList[GEO_PIKACHUHEADPARTS3]->material.kShininess = 1.f;

	meshList[GEO_PIKACHUNOSE] = MeshBuilder::GenerateSphere("nose", Color(0, 0, 0), 18, 36, 1.f);
	meshList[GEO_PIKACHUNOSE]->material.kAmbient.Set(0.f, 0.f, 0.f);
	meshList[GEO_PIKACHUNOSE]->material.kDiffuse.Set(0.f, 0.f, 0.f);
	meshList[GEO_PIKACHUNOSE]->material.kSpecular.Set(0.f, 0.f, 0.f);
	meshList[GEO_PIKACHUNOSE]->material.kShininess = 1.f;


	meshList[GEO_PIKACHUBROWN] = MeshBuilder::GenerateSphere("mouth", Color(0.36078431372, 0.21176470588, 0.07450980392), 18, 36, 1.f);
	meshList[GEO_PIKACHUBROWN]->material.kAmbient.Set(0.36078431372, 0.21176470588, 0.07450980392);
	meshList[GEO_PIKACHUBROWN]->material.kDiffuse.Set(0.f, 0.f, 0.f);
	meshList[GEO_PIKACHUBROWN]->material.kSpecular.Set(0.36078431372, 0.21176470588, 0.07450980392);
	meshList[GEO_PIKACHUBROWN]->material.kShininess = 1.f;

	meshList[GEO_PIKACHUSPHEREYELLOW] = MeshBuilder::GenerateHemisphere("mouth", Color(0.95686274509, 0.86274509803, 0.14901960784), 18, 36, 1.f);
	meshList[GEO_PIKACHUSPHEREYELLOW]->material.kAmbient.Set(1.0f, 0.90196078431f, 0.17647058823);
	meshList[GEO_PIKACHUSPHEREYELLOW]->material.kDiffuse.Set(0.f, 1.f, 0.f);
	meshList[GEO_PIKACHUSPHEREYELLOW]->material.kSpecular.Set(0.95686274509, 0.86274509803, 0.14901960784);
	meshList[GEO_PIKACHUSPHEREYELLOW]->material.kShininess = 1.f;

	meshList[GEO_REALPIKACHUSPHERE] = MeshBuilder::GenerateSphere("mouth", Color(0.95686274509, 0.86274509803, 0.14901960784), 18, 36, 1.f);
	meshList[GEO_REALPIKACHUSPHERE]->material.kAmbient.Set(1.0f, 0.90196078431f, 0.17647058823);
	meshList[GEO_REALPIKACHUSPHERE]->material.kDiffuse.Set(0.f, 1.f, 0.f);
	meshList[GEO_REALPIKACHUSPHERE]->material.kSpecular.Set(0.95686274509, 0.86274509803, 0.14901960784);
	meshList[GEO_REALPIKACHUSPHERE]->material.kShininess = 1.f;

	
	meshList[GEO_BACKSTRIP] = MeshBuilder::GenerateSphere("mouth", Color(1, 1, 1), 18, 36, 1.f);
	meshList[GEO_BACKSTRIP]->material.kAmbient.Set(0.36078431372f, 0.21176470588f, 0.07450980392f);
	meshList[GEO_BACKSTRIP]->material.kDiffuse.Set(0.36078431372f, 0.21176470588f, 0.07450980392f);
	meshList[GEO_BACKSTRIP]->material.kSpecular.Set(0.36078431372f, 0.21176470588f, 0.07450980392f);
	meshList[GEO_BACKSTRIP]->material.kShininess = 1.f;
	
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(0.36078431372, 0.21176470588, 0.07450980392), 5);
	meshList[GEO_CUBE]->material.kAmbient.Set(0.36078431372, 0.21176470588, 0.07450980392);
	meshList[GEO_CUBE]->material.kDiffuse.Set(0.f, 1.f, 0.f);
	meshList[GEO_CUBE]->material.kSpecular.Set(0.36078431372, 0.21176470588, 0.07450980392);
	meshList[GEO_CUBE]->material.kShininess = 1.f;

	meshList[GEO_TAILYELLOW] = MeshBuilder::GenerateCube("cube", Color(0.95686274509, 0.86274509803, 0.14901960784), 5);
	meshList[GEO_TAILYELLOW]->material.kAmbient.Set(1.0f, 0.90196078431f, 0.17647058823);
	meshList[GEO_TAILYELLOW]->material.kDiffuse.Set(0.f, 1.f, 0.f);
	meshList[GEO_TAILYELLOW]->material.kSpecular.Set(0.95686274509, 0.86274509803, 0.14901960784);
	meshList[GEO_TAILYELLOW]->material.kShininess = 1.f;
	
	meshList[GEO_TAILBROWN] = MeshBuilder::GenerateTriangle("cube", Color(0.36078431372, 0.21176470588, 0.07450980392), 5);
	meshList[GEO_TAILBROWN]->material.kAmbient.Set(0.36078431372, 0.21176470588, 0.07450980392);
	meshList[GEO_TAILBROWN]->material.kDiffuse.Set(0.f, 1.f, 0.f);
	meshList[GEO_TAILBROWN]->material.kSpecular.Set(0.36078431372, 0.21176470588, 0.07450980392);
	meshList[GEO_TAILBROWN]->material.kShininess = 1.f;

	meshList[GEO_POKEBALLRED] = MeshBuilder::GenerateHemisphere("pokeball red", Color(0.94117647058, 0, 0), 18, 36, 1.f);
	meshList[GEO_POKEBALLRED]->material.kAmbient.Set(1.0f, 0, 0);
	meshList[GEO_POKEBALLRED]->material.kDiffuse.Set(0.f, 1.f, 0.f);
	meshList[GEO_POKEBALLRED]->material.kSpecular.Set(1, 1, 1);
	meshList[GEO_POKEBALLRED]->material.kShininess = 2.f;

	meshList[GEO_POKEBALLBLACK] = MeshBuilder::GenerateCylinder("pokeball black", Color(0, 0, 0), 18, 36, 1.f, 1, 5);
	meshList[GEO_POKEBALLBLACK]->material.kAmbient.Set(1.0f, 0, 0);
	meshList[GEO_POKEBALLBLACK]->material.kDiffuse.Set(0.f, 1.f, 0.f);
	meshList[GEO_POKEBALLBLACK]->material.kSpecular.Set(0, 0, 0);
	meshList[GEO_POKEBALLBLACK]->material.kShininess = 2.f;

	meshList[GEO_POKEBALLBLACK2] = MeshBuilder::GenerateCircle("pokeball black", Color(0, 0, 0), 360, 1);
	meshList[GEO_POKEBALLBLACK2]->material.kAmbient.Set(1.0f, 0, 0);
	meshList[GEO_POKEBALLBLACK2]->material.kDiffuse.Set(1.f, 1.f, 0.f);
	meshList[GEO_POKEBALLBLACK2]->material.kSpecular.Set(0, 0, 0);
	meshList[GEO_POKEBALLBLACK2]->material.kShininess = 2.f;

	meshList[GEO_POKEBALLWHITE] = MeshBuilder::GenerateCircle("pokeball white", Color(1, 1, 1), 360, 1);
	meshList[GEO_POKEBALLWHITE]->material.kAmbient.Set(1, 1, 1);
	meshList[GEO_POKEBALLWHITE]->material.kDiffuse.Set(1, 1, 1);
	meshList[GEO_POKEBALLWHITE]->material.kSpecular.Set(1, 1, 1);
	meshList[GEO_POKEBALLWHITE]->material.kShininess = 2;

	meshList[GEO_POKEBALLWHITE2] = MeshBuilder::GenerateHemisphere("pokeball white", Color(1, 1, 1),  18, 36, 1.f);
	meshList[GEO_POKEBALLWHITE2]->material.kAmbient.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_POKEBALLWHITE2]->material.kDiffuse.Set(1.f, 0.f, 0.f);
	meshList[GEO_POKEBALLWHITE2]->material.kSpecular.Set(1.0f, 1.0f, 1.0f);
	meshList[GEO_POKEBALLWHITE2]->material.kShininess = 2.f;

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("Lightball", Color(1, 1 ,1),18, 36, 1.f);

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);
}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

void GameOfLife::Update(double dt)
{
	if(Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	int LSPEED = 100;
	int ROTATE_SPEED = 10;

	camera.Update(dt);
}

void GameOfLife::Render()

{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);

	modelStack.LoadIdentity();
	

	//Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	//glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);


	RenderMesh(meshList[GEO_AXES], false);
}

void GameOfLife::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
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
	mesh->Render();
}


void GameOfLife::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
