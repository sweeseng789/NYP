#include "Scene5.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

Scene5::Scene5()
{
}

Scene5::~Scene5()
{
}

void Scene5::Init()
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
	
	//Load vertex and fragment shaders
	m_programID = LoadShaders( "Shader//TransformVertexShader.vertexshader", "Shader//SimpleFragmentShader.fragmentshader" );
	// Use our shader
	glUseProgram(m_programID);
	// Get a handle for our "MVP" uniform
	m_parameters[U_MVP] = glGetUniformLocation(m_programID, "MVP");
	
	//variable to rotate geometry
	rotateAngle = 0;
	rotateSun = 0;
	rotateEarth = 0;
	rotateMars = 0;
	rotateJupiter = 0;
	rotateSaturn = 0;

	//Initialize camera settings
	camera.Init(Vector3(40, 30, 30), Vector3(0, 0, 0), Vector3(0, 1, 0));

	//remove all glGenBuffers, glBindBuffer, glBufferData code
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);
	//meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", 1, 1);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 0, 0), 5);
	meshList[GEO_RING] = MeshBuilder::GenerateRing("ring", Color(0, 1, 1), 36, 1.f, 0.5f);
	meshList[GEO_SUN] = MeshBuilder::GenerateSphere("Sun", Color(1, 1, 0), 18, 36, 1.f);
	meshList[GEO_MERCURY] = MeshBuilder::GenerateSphere("Mercury", Color(0.50196078431, 0.50196078431, 0.50196078431), 18, 36, 1.f);
	meshList[GEO_EARTH] = MeshBuilder::GenerateSphere("Earth", Color(0.2, 0.6, 1), 18, 36, 1.f);
	meshList[GEO_EARTH_MOON] = MeshBuilder::GenerateSphere("Earth moon", Color(0.75294117647, 0.75294117647, 0.75294117647), 18, 36, 1.f);
	meshList[GEO_VENUS] = MeshBuilder::GenerateSphere("Venus", Color(1, 0.50196078431, 0), 18, 36, 1.f);
	meshList[GEO_MARS] = MeshBuilder::GenerateSphere("Mars", Color(0.6, 0.29803921568, 0), 18, 36, 1.f);
	meshList[GEO_JUPITER] = MeshBuilder::GenerateSphere("Jupiter", Color(0.2, 0.09803921568, 0), 18, 36, 1.f);
	meshList[GEO_SATURN] = MeshBuilder::GenerateSphere("Jupiter", Color(0.2, 0.09803921568, 0), 18, 36, 1.f);
	meshList[GEO_SATURN_RING] = MeshBuilder::GenerateRing("ring", Color(0, 1, 1), 36, 1.f, 0.5f);
	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);
}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

void Scene5::Update(double dt)
{
	if(Application::IsKeyPressed('1')) //enable back face culling
		glEnable(GL_CULL_FACE);
	if(Application::IsKeyPressed('2')) //disable back face culling
		glDisable(GL_CULL_FACE);
	if(Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); //default fill mode
	if(Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); //wireframe mode

	rotateAngle += (float)(100 * dt);
	rotateSun += (float)(10 * dt);
	rotateEarth += (float)(50 * dt);
	rotateMars += (float)(40 * dt);
	rotateJupiter += (float)(60 * dt);
	rotateSaturn += (float)(55 * dt);

	camera.Update(dt);
}

void Scene5::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Temp variables
	Mtx44 translate, rotate, scale;
	Mtx44 MVP;

	//These will be replaced by matrix stack soon
	Mtx44 model;
	Mtx44 view;
	Mtx44 projection;

	//Set all matrices to identity
	translate.SetToIdentity();
	rotate.SetToIdentity();
	scale.SetToIdentity();
	model.SetToIdentity();

	//Set view matrix using camera settings
	view.SetToLookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
					);

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);

	modelStack.LoadIdentity();
	//Set projection matrix to perspective mode
	projection.SetToPerspective(100.0f, 10.0f / 2.0f, 0.1f, 1000.0f); //FOV, Aspect Ratio, Near plane, Far plane
	
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP

	meshList[GEO_AXES]->Render();

	modelStack.PushMatrix();// push sun
	modelStack.Rotate(rotateSun, 0 ,1, 0);
	modelStack.Scale(10, 10, 10);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP
	meshList[GEO_SUN]->Render();

	modelStack.PopMatrix(); //pop sun

	modelStack.PushMatrix();// push mercury
	modelStack.Translate(0,0,0);
	modelStack.Rotate(rotateAngle, -rotateAngle ,-rotateAngle, 0);
	modelStack.Scale(1.5, 1.5, 1.5);
	modelStack.Translate(6,0,6);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP
	meshList[GEO_MERCURY]->Render();
	modelStack.PopMatrix(); //pop mercury

	modelStack.PushMatrix();// push Venus
	modelStack.Translate(0,0,0);
	modelStack.Rotate(rotateAngle, -rotateAngle ,0, 0);
	modelStack.Scale(1.5, 1.5, 1.5);
	modelStack.Translate(0	,0,8);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP
	meshList[GEO_VENUS]->Render();
	modelStack.PopMatrix(); //pop Venus

	modelStack.PushMatrix();// push earth
	modelStack.Translate(0,0,0);
	modelStack.Rotate(rotateEarth, 0 , 1, 0);
	modelStack.Scale(2.6, 2.6, 2.6);
	modelStack.Translate(6,0,6);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP
	meshList[GEO_EARTH]->Render();
	modelStack.PopMatrix(); //pop earth

	modelStack.PushMatrix();// push earth moon

	modelStack.Translate(0,0,0);
	modelStack.Rotate(rotateEarth, 0 , 1, 0);

	modelStack.Translate(4,0,4);

	modelStack.Translate(12,0,12);
	modelStack.Rotate(-rotateAngle, 0 , 1, 0);
	modelStack.Scale(0.5, 0.5, 0.5);
	modelStack.Translate(-10,0,-10);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP
	meshList[GEO_EARTH_MOON]->Render();
	modelStack.PopMatrix(); //pop earth moon

	modelStack.PushMatrix();// push mars
	modelStack.Translate(0,0,0);
	modelStack.Rotate(rotateMars, 0 , 1, 0);
	modelStack.Scale(1, 1, 1);
	modelStack.Translate(25,0,25);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP
	meshList[GEO_MARS]->Render();
	modelStack.PopMatrix(); //pop mars

	modelStack.PushMatrix();// push Jupiter
	modelStack.Translate(0,0,0);
	modelStack.Rotate(rotateJupiter, 0 , 1, 0);
	modelStack.Scale(5, 5, 5);
	modelStack.Translate(8,0,8);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP
	meshList[GEO_JUPITER]->Render();
	modelStack.PopMatrix(); //pop Jupiter

	modelStack.PushMatrix();// push Saturn
	modelStack.Translate(0,0,0);
	modelStack.Rotate(rotateSaturn, 0 , 1, 0);
	modelStack.Scale(5, 5, 5);
	modelStack.Translate(12,0,12);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP
	meshList[GEO_SATURN]->Render();
	modelStack.PopMatrix(); //pop Saturn


	modelStack.PushMatrix();// push Saturn rinf
	modelStack.Translate(0,0,0);
	modelStack.Rotate(rotateSaturn, 0 , 1, 0);
	modelStack.Scale(12, 12, 12);
	modelStack.Translate(5,0,5);
	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]); //update the shader with new MVP
	meshList[GEO_SATURN_RING]->Render();
	modelStack.PopMatrix(); //pop Saturn ring

}

void Scene5::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
