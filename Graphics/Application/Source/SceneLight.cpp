#include "SceneLight.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Utility.h"

#include "Application.h"
#include "MeshBuilder.h"


SceneLight::SceneLight()
{
}

SceneLight::~SceneLight()
{
}

void SceneLight::Init()
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
	light[0].position.Set(0, 10, 0);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1; //0 will shut off lighting
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;

		// Make sure you pass uniform parameters after glUseProgram()
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);


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
	
	meshList[GEO_CYLINDER] = MeshBuilder::GenerateCylinder("Cylinder", Color(0.95686274509, 0.86274509803, 0.14901960784), 18, 36, 1.f);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 0, 0), 5);
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


	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("Sun", Color(0, 1, 1), 18, 36, 1.f);
	meshList[GEO_SPHERE]->material.kAmbient.Set(1.f, 0.f, 0.f);
	meshList[GEO_SPHERE]->material.kDiffuse.Set(0.f, 1.f, 0.f);
	meshList[GEO_SPHERE]->material.kSpecular.Set(0.f, 0.f, 1.f);
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

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("Lightball", Color(1, 1 ,1),18, 36, 1.f);


	meshList[GEO_BALL1] = MeshBuilder::GenerateSphere("Ball 1", Color(1, 0, 0), 18, 36, 1.f);
	meshList[GEO_BALL1]->material.kAmbient.Set(1, 0, 0);
	meshList[GEO_BALL1]->material.kDiffuse.Set(0.f, 1.f, 0.f);
	meshList[GEO_BALL1]->material.kSpecular.Set(0.f, 0.f, 1.f);
	meshList[GEO_BALL1]->material.kShininess = 1.f;

	meshList[GEO_BALL2] = MeshBuilder::GenerateSphere("Ball 2", Color(1, 1, 0), 18, 36, 1.f);
	meshList[GEO_BALL2]->material.kAmbient.Set(1, 1, 0);
	meshList[GEO_BALL2]->material.kDiffuse.Set(0.f, 1.f, 0.f);
	meshList[GEO_BALL2]->material.kSpecular.Set(0.f, 0.f, 1.f);
	meshList[GEO_BALL2]->material.kShininess = 1.f;

	meshList[GEO_BALL3] = MeshBuilder::GenerateSphere("ball 3", Color(1, 1, 1), 18, 36, 1.f);
	meshList[GEO_BALL3]->material.kAmbient.Set(1, 1, 1);
	meshList[GEO_BALL3]->material.kDiffuse.Set(0.f, 1.f, 0.f);
	meshList[GEO_BALL3]->material.kSpecular.Set(0.f, 0.f, 1.f);
	meshList[GEO_BALL3]->material.kShininess = 1.f;

	meshList[GEO_BALL4] = MeshBuilder::GenerateSphere("Ball 4", Color(0.8, 0.8, 0.8), 18, 36, 1.f);
	meshList[GEO_BALL4]->material.kAmbient.Set(0.8, 0.8, 0.8);
	meshList[GEO_BALL4]->material.kDiffuse.Set(0.f, 1.f, 0.f);
	meshList[GEO_BALL4]->material.kSpecular.Set(0.f, 0.f, 1.f);
	meshList[GEO_BALL4]->material.kShininess = 1.f;

	meshList[GEO_BALL5] = MeshBuilder::GenerateSphere("Ball 5", Color(0.6, 0.6, 0.6), 18, 36, 1.f);
	meshList[GEO_BALL5]->material.kAmbient.Set(0.6, 0.6, 0.6);
	meshList[GEO_BALL5]->material.kDiffuse.Set(0.f, 1.f, 0.f);
	meshList[GEO_BALL5]->material.kSpecular.Set(0.f, 0.f, 1.f);
	meshList[GEO_BALL5]->material.kShininess = 1.f;

	meshList[GEO_BALL6] = MeshBuilder::GenerateSphere("Ball 6", Color(0.3, 0.5, 1), 18, 36, 1.f);
	meshList[GEO_BALL6]->material.kAmbient.Set(0.3, 0.5, 1);
	meshList[GEO_BALL6]->material.kDiffuse.Set(0.f, 1.f, 0.f);
	meshList[GEO_BALL6]->material.kSpecular.Set(0.f, 0.f, 1.f);
	meshList[GEO_BALL6]->material.kShininess = 1.f;

	meshList[GEO_BALL7] = MeshBuilder::GenerateSphere("Ball 7", Color(1, 0, 1), 18, 36, 1.f);
	meshList[GEO_BALL7]->material.kAmbient.Set(1.f, 0.f, 1.f);
	meshList[GEO_BALL7]->material.kDiffuse.Set(0.f, 1.f, 0.f);
	meshList[GEO_BALL7]->material.kSpecular.Set(0.f, 0.f, 1.f);
	meshList[GEO_BALL7]->material.kShininess = 1.f;

	meshList[GEO_BALL8] = MeshBuilder::GenerateSphere("Ball 8", Color(0, 0, 0), 18, 36, 1.f);
	meshList[GEO_BALL8]->material.kAmbient.Set(0.f, 0.f, 0.f);
	meshList[GEO_BALL8]->material.kDiffuse.Set(0.f, 1.f, 0.f);
	meshList[GEO_BALL8]->material.kSpecular.Set(0.f, 0.f, 1.f);
	meshList[GEO_BALL8]->material.kShininess = 1.f;

	meshList[GEO_BALL9] = MeshBuilder::GenerateSphere("Ball 9", Color(0.5, 0.5, 0.5), 18, 36, 1.f);
	meshList[GEO_BALL9]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BALL9]->material.kDiffuse.Set(0.f, 1.f, 0.f);
	meshList[GEO_BALL9]->material.kSpecular.Set(0.f, 0.f, 1.f);
	meshList[GEO_BALL9]->material.kShininess = 1.f;


	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 1000.f);
	projectionStack.LoadMatrix(projection);
}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

void SceneLight::Update(double dt)
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

	if(Application::IsKeyPressed('I'))
		light[0].position.z -= (float)(LSPEED * dt);
	if(Application::IsKeyPressed('K'))
		light[0].position.z += (float)(LSPEED * dt);
	if(Application::IsKeyPressed('J'))
		light[0].position.x -= (float)(LSPEED * dt);
	if(Application::IsKeyPressed('L'))
		light[0].position.x += (float)(LSPEED * dt);
	if(Application::IsKeyPressed('O'))
		light[0].position.y -= (float)(LSPEED * dt);
	if(Application::IsKeyPressed('P'))
		light[0].position.y += (float)(LSPEED * dt);

	static int rotateDir = 1;
	/*if (rotateAngle * rotateDir > 30)
		rotateDir = -rotateDir;
	rotateAngle += (float)(rotateDir * ROTATE_SPEED * dt);*/

	rotateAngle += (float)(100 * dt);
	camera.Update(dt);
}

void SceneLight::RenderBody()
{
	modelStack.PushMatrix();
	modelStack.Scale(30, 25, 10);
	//modelStack.Translate(0, -7.5, 0);
	RenderMesh(meshList[GEO_CUBE], false);
	modelStack.PopMatrix();
}

void SceneLight::RenderLimb()
{
	modelStack.PushMatrix();
	modelStack.Scale(10, 20, 10);
	//modelStack.Translate(0, -7.5, 0);
	RenderMesh(meshList[GEO_CUBE1], false);
	modelStack.PopMatrix();
}

void SceneLight::RenderRobot()
{
	modelStack.PushMatrix();
	RenderBody();
	modelStack.PushMatrix(); // right upper arm
	modelStack.Translate(20, 0 , 0);
	modelStack.Rotate(rotateAngle, 1, 0, 0);
	RenderLimb();
	modelStack.PushMatrix(); //rigth lower arm
	modelStack.Translate(0, -20, 0);
	modelStack.Rotate(-30 + rotateAngle, 1, 0, 0);
	RenderLimb();
	modelStack.PopMatrix(); //right lower arm
	modelStack.PopMatrix();//right upper arm


	modelStack.PushMatrix(); // left upper arm
	modelStack.Translate(-20, 0 , 0);
	modelStack.Rotate(rotateAngle, 1, 0, 0);
	RenderLimb();
	modelStack.PushMatrix(); //left lower arm
	modelStack.Translate(0, -20, 0);
	modelStack.Rotate(-30 + rotateAngle, 1, 0, 0);
	RenderLimb();
	modelStack.PopMatrix(); //left lower arm
	modelStack.PopMatrix();//left upper arm


	modelStack.PopMatrix();
}

void SceneLight::PikachuLeftEars()
{
	modelStack.PushMatrix();//Pikachu yelow ears
	modelStack.Scale(0.05, 0.5, 0.03);
	modelStack.Rotate(4, 1, 1, 1);
	modelStack.Translate(-35, 7, 0);
	RenderMesh(meshList[GEO_CONEYellow], true);
	std::cout << rotateAngle << std::endl;

	modelStack.PushMatrix(); //left black ear
	modelStack.Scale(0.51, 0.5, 0.51);
	modelStack.Translate(0, 21, 0);
	RenderMesh(meshList[GEO_CONEBlack], true);

	modelStack.PopMatrix(); //black ears
	modelStack.PopMatrix();//Yellow ears
}

void SceneLight::PikachuRightEars()
{
	modelStack.PushMatrix();//Pikachu yelow ears
	modelStack.Scale(0.05, 0.5, 0.03);
	modelStack.Rotate(-5, 1, 0, 1);
	modelStack.Translate(40, 12, -60);
	RenderMesh(meshList[GEO_CONEYellow], true);
	std::cout << rotateAngle << std::endl;

	modelStack.PushMatrix(); //left black ear
	modelStack.Scale(0.5, 0.5, 0.51);
	modelStack.Translate(0, 21, 0);
	RenderMesh(meshList[GEO_CONEBlack], true);

	modelStack.PopMatrix(); //black ears
	modelStack.PopMatrix();//Yellow ears
}

void SceneLight::PikachuRightEyes()
{
	modelStack.PushMatrix();
	modelStack.Scale(1, 1, 0.3);
	modelStack.Rotate(90, 90, 0, 1);

	RenderMesh(meshList[GEO_PIKACHUEYES], true);

	modelStack.PushMatrix();
	modelStack.Translate(-3, 0, 0);
	RenderMesh(meshList[GEO_PIKACHUEYES], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(0.4, 0.4, 0.4);
	modelStack.Rotate(10, 0, -45, 90);

	modelStack.PushMatrix();
	modelStack.Scale(1, 1, 0.3);
	modelStack.Rotate(90, 90, 0, 1);
	modelStack.Translate(-0.8, 1.4, -1);
	RenderMesh(meshList[GOE_PIKACHUEYESWHITE], true);
	
	
	modelStack.PushMatrix();
	modelStack.Translate(-5.5, 1.5, -1);
	RenderMesh(meshList[GOE_PIKACHUEYESWHITE], true);
	
	modelStack.PopMatrix();
	
	modelStack.PopMatrix();
	
	modelStack.PopMatrix();
}

void SceneLight::PikachuNose()
{
	modelStack.PushMatrix();
	modelStack.Scale(0.5, 0.3, 0.3);
	RenderMesh(meshList[GEO_PIKACHUNOSE], true);
	modelStack.PopMatrix();
}

void SceneLight::PikachuMouth()
{
	modelStack.PushMatrix();
	modelStack.Scale(0.5, 0.5, 0.2);
	modelStack.Translate(0, -0.1, 0.2);
	RenderMesh(meshList[GEO_PIKACHUBROWN], true);
	modelStack.PopMatrix();
}

void SceneLight::PikachuHead()
{
	modelStack.PushMatrix();
	modelStack.Rotate(-50, 0, 0, 50);
	modelStack.Translate(-2, 0, 0);
	PikachuRightEars();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(15, 0, 0, 1);
	modelStack.Translate(0, -0.5, -2);
	PikachuLeftEars();
	modelStack.PopMatrix();

	modelStack.PushMatrix(); //head parts back
	modelStack.Scale(4.5, 4.5, 4.5);
	modelStack.Rotate(90, -100, 0 ,1);
	modelStack.Translate(0, 0, 0.2);
	RenderMesh(meshList[GEO_PIKACHUHEADPARTS], true);
	modelStack.PopMatrix();//head parts back

	modelStack.PushMatrix(); //head parts middle
	modelStack.Scale(4.5, 4.5,2);
	modelStack.Rotate(90, 10, 0 ,1);
	modelStack.Translate(0, -0.22, -0.2);
	RenderMesh(meshList[GEO_PIKACHUHEADPARTS], true);
	modelStack.PopMatrix();//head parts middle

	modelStack.PushMatrix();//lower
	modelStack.Scale(1, 1, 0.8);

	modelStack.PushMatrix(); //head parts jaw
	modelStack.Scale(4.5, 4.5, 4.3);
	modelStack.Rotate(180, -190, 0 ,1);
	modelStack.Translate(0, -0.2, 0);
	RenderMesh(meshList[GEO_PIKACHUHEADPARTS], true);
	modelStack.PopMatrix();//head parts jaw

	modelStack.PushMatrix(); //head parts nose
	modelStack.Scale(4.5, 2,4.3);
	modelStack.Translate(0, 0.3, 0);
	RenderMesh(meshList[GEO_PIKACHUHEADPARTS], true);
	modelStack.PopMatrix();//head parts nose
	modelStack.PopMatrix();

	modelStack.PushMatrix();//push cheek as a whole
	modelStack.Scale(0.6, 0.6, 0.6);

	modelStack.PushMatrix(); //head parts cheek
	modelStack.Scale(2.3, 2.3, 2.3);
	modelStack.Translate(-2.3, -0.1, 0.5);
	RenderMesh(meshList[GEO_PIKACHUHEADPARTS3], true);

	modelStack.PushMatrix(); //head parts cheek

	modelStack.Translate(4.7, 0, -0.2);
	RenderMesh(meshList[GEO_PIKACHUHEADPARTS3], true);

	modelStack.PopMatrix();
	modelStack.PopMatrix();//head parts cheek
	modelStack.PopMatrix(); //pop cheek as a whole

	

	modelStack.PushMatrix();
	modelStack.Rotate(10, -10, 0, 1);
	modelStack.Translate(1.5, 3, 1.6);
	PikachuRightEyes();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 1, 3.3);
	PikachuNose();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0, 3.3);
	PikachuMouth();
	modelStack.PopMatrix();
}

void SceneLight::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);

	modelStack.LoadIdentity();
	

	Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);


	RenderMesh(meshList[GEO_AXES], false);
	
	modelStack.PushMatrix();
	modelStack.Scale(1,1,1);
	modelStack.Translate(light[0].position.x, light[0].position.y + 2, light[0].position.z);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(10000, 10000, 10000);
	modelStack.Rotate(90, -90, 0, 1);
	modelStack.Translate(0, 0, -0.02);
	RenderMesh(meshList[GEO_QUAD], true);
	modelStack.PopMatrix();

	/*modelstack.pushmatrix();
	pikachuhead();
	modelstack.popmatrix();*/

	modelStack.PushMatrix();
	modelStack.Rotate(rotateAngle, 0, rotateAngle, 1);

	modelStack.PushMatrix();//ball 1
	modelStack.Scale(5, 5, 5);
	modelStack.Translate(-2, 0, 2.5);
	RenderMesh(meshList[GEO_BALL1], true);

	modelStack.PushMatrix(); //ball 2
	modelStack.Translate(0, 0, -2);
	RenderMesh(meshList[GEO_BALL2], true);

	modelStack.PushMatrix(); //ball 3
	modelStack.Translate(0, 0, -2);
	RenderMesh(meshList[GEO_BALL3], true);
	modelStack.PopMatrix(); //ball 3

	modelStack.PopMatrix(); //ball2

	modelStack.PopMatrix();//ball 1


	modelStack.PushMatrix();//ball 4
	modelStack.Scale(5, 5, 5);
	modelStack.Translate(0, 0, 2.5);
	RenderMesh(meshList[GEO_BALL4], true);

	modelStack.PushMatrix(); //ball 5
	modelStack.Translate(0, 0, -2);
	RenderMesh(meshList[GEO_BALL5], true);

	modelStack.PushMatrix(); //ball 6
	modelStack.Translate(0, 0, -2);
	RenderMesh(meshList[GEO_BALL6], true);
	modelStack.PopMatrix(); //ball 6

	modelStack.PopMatrix(); //ball5

	modelStack.PopMatrix();//ball 4

	modelStack.PushMatrix();//ball 7
	modelStack.Scale(5, 5, 5);
	modelStack.Translate(2, 0, 2.5);
	RenderMesh(meshList[GEO_BALL7], true);

	modelStack.PushMatrix(); //ball 8
	modelStack.Translate(0, 0, -2);
	RenderMesh(meshList[GEO_BALL8], true);

	modelStack.PushMatrix(); //ball 9
	modelStack.Translate(0, 0, -2);
	RenderMesh(meshList[GEO_BALL9], true);
	modelStack.PopMatrix(); //ball 9

	modelStack.PopMatrix(); //ball8

	modelStack.PopMatrix();//ball 7


	modelStack.PopMatrix();

}

void SceneLight::RenderMesh(Mesh *mesh, bool enableLight)
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


void SceneLight::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
