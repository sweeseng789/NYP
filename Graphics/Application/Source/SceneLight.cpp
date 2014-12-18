/****************************************************************************/
/*!
\file SceneLight.cpp
\author Ong Swee Seng
\brief SceneLight.cpp is used to set, render and update geometries with parameters.
*/
/****************************************************************************/

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
	rotateLeftFeet = 0;
	rotateRightFeet = 0;
	rotateLefthand = 1;
	rotateMars = 0;
	rotateJupiter = 1;
	rotateTail = 0;

	/*charPosition.x = 36000;
	charPosition.z = 1;
	charPosition.y = 0;*/
	//charPosition(36000, 0, 1);


	/*charDirection.x = charPosition.z = 0;
	charDirection.y = 1;*/
	//charPositon(0, 1, 0);

	speed = 0.1;
	angle = 3600;

	PokeballPosition.x  = PokeballPosition.z = 30;
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
	meshList[GEO_BACKSTRIP]->material.kDiffuse.Set(0.f, 1.f, 0.f);
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

	static int LeftFeet = 1;
	static int RightFeet = 1;

	static int Lefthand = 1;

	static int pokeball = 1;

	static int count = 1;
	static bool pressing;
	static bool pressedLeftHand;

	static bool left = false;
	static int right = false;

	/****************************************************************************/
	/*!
	\brief
	If user pressed spacebar, the left feet will move first. If the left feet have reached 30 degree
	it will increment a count. For the right feet if count is more than zero, it would then start
	moving also, this is used to create a walking animation without both feet moving simultaneously 
	*/
	/****************************************************************************/
	if (Application::IsKeyPressed('W') || Application::IsKeyPressed('S'))
	{
		pressing = true;
	}
	else
	{
		pressing = false;
	}

	if(pressing == true)
	{
		if (rotateLeftFeet * LeftFeet > 30)
		{
			LeftFeet = -LeftFeet;
			count ++;
		}

		if (rotateRightFeet * RightFeet > 30)
		{
			RightFeet = -RightFeet;
		}
	
		if (count > 1)
		{
			rotateRightFeet += (float)(RightFeet * ROTATE_SPEED * dt * 5);
		}
	
		rotateLeftFeet += (float)(LeftFeet * ROTATE_SPEED * dt * 5);
	}
	else if (pressing = false)
	{
		count = 0;                                
	}
	
	/****************************************************************************/
	/*!
	\brief
	This is used to rotate the tail, when it reached 20 degree, it would then become a minus variable and minus off
	the total value to create a recuring rotating tail
	*/
	/****************************************************************************/
	rotateLefthand += (float)(Lefthand * ROTATE_SPEED * dt * 5);
	if (rotateLefthand * Lefthand > 20)
	{
		Lefthand = -Lefthand;
	}

	if (Application::IsKeyPressed('2'))
	{
		rotateTail += (float)(pokeball * ROTATE_SPEED * dt * 5);
	}
	if (rotateTail > 45)
	{
		rotateTail = -rotateTail;
	}


	/****************************************************************************/
	/*!
	\brief
	when player pressed W or S, Pikachu will move in their current angle
	to rotate or change the angle, user will have to press A or D
	*/
	/****************************************************************************/
	
	if (Application::IsKeyPressed('W'))
	{
		charPosition.z += cos(Math::DegreeToRadian(angle)) * 10 * dt;
		charPosition.x += sin(Math::DegreeToRadian(angle)) * 10 * dt;
	}
	if (Application::IsKeyPressed('S'))
	{
		charPosition.z -= cos(Math::DegreeToRadian(angle)) * 10 * dt;
		charPosition.x -= sin(Math::DegreeToRadian(angle)) * 10 * dt;
	}
	if (Application::IsKeyPressed('A'))
	{
		angle += 100 * dt;
	}
	if (Application::IsKeyPressed('D'))
	{
		angle -= 100 * dt;
	}
	/****************************************************************************/
	/*!
	\brief
	When players pressed the button for the pokeball, if the position of the pokeball is more than the position of pikachu 
	it will keep minusing off the value till it reaches pikachu
	*/
	/****************************************************************************/
	if (Application::IsKeyPressed('9'))
	{
		if(PokeballPosition.z > charPosition.z)
		{
			PokeballPosition.z -= 0.1;
			PokeballPosition.x -= 0.1;
		}
	}	
	/*if (rotateLefthand * Lefthand < 0)
	{
		Lefthand = 0;
	}*/
	//rotateRightFeet += (float)(50 * dt);
	/*rotateLeftFeet += (float)(100 * dt);*/

	//Scaling Pikachu
	/////////////////////////////////////////////////////////////////////////////////left button
	//if(Application::IsKeyPressed(VK_LBUTTON))
	//{
	//	left = true;
	//}

	///*if (left == true)
	//{
	//	
	//}*/
	//
	//if (left == true)
	//{
	//	rotateJupiter -= (float)(dt);
	//	if (Application::IsKeyPressed(VK_RBUTTON))
	//	{
	//		right = false;
	//	}
	//}

	//if (rotateJupiter < 0.472949 && left == true)
	//{
	//	rotateJupiter = 0.472948;
	//	left = false;
	//}
	/////////////////////////////////////////////////////////////////////////////////Right button
	//if(Application::IsKeyPressed(VK_RBUTTON))
	//{
	//	right = true;
	//}

	///*if(right == true)
	//{
	//	
	//}*/

	//if (right == true)
	//{
	//	rotateJupiter += (float)(dt);
	//	if (Application::IsKeyPressed(VK_LBUTTON))
	//	{
	//		left == false;
	//	}
	//}

	//if (rotateJupiter > 1 && right == true)
	//{
	//	rotateJupiter = 1;
	//	right = false;
	//}
	camera.Update(dt);
}



/****************************************************************************/
/*!
\brief
PikachuLeftEars nad PikachuRightEars are both functions used to create the ears of Pikachu and then it will be called in PikachuHead
\param
2 Cone for each function
Total 4 cones
Shape Variable: GEO_CONEYellow and GEO_CONEBlack
*/
/****************************************************************************/
void SceneLight::PikachuLeftEars()
{
	modelStack.PushMatrix();//Pikachu yelow ears
	modelStack.Scale(0.05, 0.5, 0.03);
	modelStack.Rotate(4, 1, 1, 1);
	modelStack.Translate(-35, 7, 0);
	RenderMesh(meshList[GEO_CONEYellow], true);

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

	modelStack.PushMatrix(); //left black ear
	modelStack.Scale(0.5, 0.5, 0.51);
	modelStack.Translate(0, 21, 0);
	RenderMesh(meshList[GEO_CONEBlack], true);

	modelStack.PopMatrix(); //black ears
	modelStack.PopMatrix();//Yellow ears
}

/****************************************************************************/
/*!
\brief
PikachuEyes is a function used to create the eyes of Pikachu and then it will be called in PikachuHead
\param
2 Sphere scaled to near flat shape
Shape Variable: GEO_PIKACHUEYES and GOE_PIKACHUEYESWHITE
*/
/****************************************************************************/
void SceneLight::PikachuEyes()
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

/****************************************************************************/
/*!
\brief
PikachuNose and Pikachu Mouth are both function used to create the nose and mouth of Pikachu respectively and then it will be called in PikachuHead
\param
2 HemiSphere scaled differently
Shape Variable: GEO_PIKACHUNOSE and GEO_PIKACHUBROWN
*/
/****************************************************************************/
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


/****************************************************************************/
/*!
\brief
PikachuHead is a fucntion call where i combine all the parts of Pikachu's head in a single function call.
\param
Shape Variable: GEO_PIKACHUHEADPARTS, GEO_PIKACHUHEADPARTS3
Function called: PikachuRightEars, PikachuLeftEars, PikachuEyes, PikachuMonth, PikachuNose
*/
/****************************************************************************/
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
	PikachuEyes();
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

/****************************************************************************/
/*!
\brief
PikachuBody is a function used to create the body of Pikachu and then it will be called in RenderPikachu
\param
2 HemiSphere
Shpaes Variable: GEO_PIKACHUHEADPARTS
*/
/****************************************************************************/
void SceneLight::PikachuBody()
{
	modelStack.PushMatrix(); //body as a whole
	modelStack.Scale(2, 2, 2);
	modelStack.Translate(0, -2.5, -0.2);
	modelStack.PushMatrix(); //front
	modelStack.Scale(2, 2.5, 1.5);
	modelStack.Rotate(90, 90, 0, 1);
	RenderMesh(meshList[GEO_PIKACHUHEADPARTS], true);

	modelStack.PushMatrix();//back
	modelStack.Rotate(180, 180, 0, 1);
	RenderMesh(meshList[GEO_PIKACHUHEADPARTS], true);
	modelStack.PopMatrix();//back
	modelStack.PopMatrix();//front

	modelStack.PushMatrix(); //leg left
	modelStack.Scale(1.15, 1.9, 1.1);
	modelStack.Rotate(180, 180, 0, 1);
	modelStack.Translate(-0.6, 0.4, 0);
	RenderMesh(meshList[GEO_PIKACHUHEADPARTS], true);
	
	modelStack.PushMatrix();
	modelStack.Translate(1.2, 0, 0);
	RenderMesh(meshList[GEO_PIKACHUHEADPARTS], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix(); //leg left


	modelStack.PopMatrix(); //body as a whole

}


/****************************************************************************/
/*!
\brief
PikachuLeftFeet and PikachuRightFeet are both function used to create the feet of pikachu respectively before being callled in RenderPikachu
\param
1 Sphere scaled
3 Hemisphere scaled for the lines
Shpaes Variable: GEO_SPHERE, GEO_PIKACHUEYES
*/
/****************************************************************************/
void SceneLight::PikachuLeftFeet()
{
	modelStack.PushMatrix();//feet as a whole
	modelStack.Rotate(rotateLeftFeet, -rotateLeftFeet, 0, 1);
	modelStack.Translate(-0.1, 0, 0);

	modelStack.PushMatrix();//feet back left
	modelStack.Scale(0.4, 0.2, 1.1);
	modelStack.Rotate(270, 270, 0, 1);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();//feet back left

	modelStack.PushMatrix();//middle line
	modelStack.Scale(0.1, 0.189, 1);
	modelStack.Translate(0, 0, .12);
	RenderMesh(meshList[GEO_PIKACHUEYES], true);

	modelStack.PushMatrix();//left line
	modelStack.Translate(-1, 0, -0.05);
	RenderMesh(meshList[GEO_PIKACHUEYES], true);
	modelStack.PopMatrix();//left line

	modelStack.PushMatrix();
	modelStack.Translate(1, 0, -0.05);
	RenderMesh(meshList[GEO_PIKACHUEYES], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();//middle line

	modelStack.PopMatrix(); //feet as a whole
}
void SceneLight::PikachuRightFeet()
{
	modelStack.PushMatrix();//feet as a whole
	modelStack.Rotate(rotateRightFeet, -rotateRightFeet, 0, 1);
	modelStack.Translate(1.1, 0, 0);

	modelStack.PushMatrix();//feet back left
	modelStack.Scale(0.4, 0.2, 1.1);
	modelStack.Rotate(270, 270, 0, 1);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();//feet back left

	modelStack.PushMatrix();//middle line
	modelStack.Scale(0.1, 0.189, 1);
	modelStack.Translate(0, 0, .12);
	RenderMesh(meshList[GEO_PIKACHUEYES], true);

	modelStack.PushMatrix();//left line
	modelStack.Translate(-1, 0, -0.05);
	RenderMesh(meshList[GEO_PIKACHUEYES], true);
	modelStack.PopMatrix();//left line

	modelStack.PushMatrix();
	modelStack.Translate(1, 0, -0.05);
	RenderMesh(meshList[GEO_PIKACHUEYES], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();//middle line

	modelStack.PopMatrix(); //feet as a whole
}


/****************************************************************************/
/*!
\brief
PikachuLeftHands and PikachuRightHands are both function used to create the hands of pikachu respectively before being callled in RenderPikachu
\param
1 Sphere scaled
3 Hemisphere scaled for the lines
Shpaes Variable: GEO_SPHERE, GEO_PIKACHUEYES
*/
/****************************************************************************/
void SceneLight::PikachuLeftHands()
{
	modelStack.PushMatrix();
	modelStack.Rotate(85, 80, 60, 65);

	modelStack.PushMatrix();//hand back left
	modelStack.Scale(0.4, 0.2, 1.1);
	modelStack.Rotate(270, 270, 0, 1);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();//feet back left

	modelStack.PushMatrix();//middle line
	modelStack.Scale(0.1, 0.189, 1);
	modelStack.Translate(0, 0, .12);
	RenderMesh(meshList[GEO_PIKACHUEYES], true);

	modelStack.PushMatrix();//left line
	modelStack.Translate(-1, 0, -0.05);
	RenderMesh(meshList[GEO_PIKACHUEYES], true);
	modelStack.PopMatrix();//left line

	modelStack.PushMatrix();
	modelStack.Translate(1, 0, -0.05);
	RenderMesh(meshList[GEO_PIKACHUEYES], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();//middle line

	modelStack.PopMatrix(); //hnad as a whole
}
void SceneLight::PikachuRightHands()
{
	modelStack.PushMatrix();
	modelStack.Rotate(85, 50, -60, -65);

	modelStack.PushMatrix();//hand back rigth
	modelStack.Scale(0.4, 0.2, 1.1);
	modelStack.Rotate(270, 270, 0, 1);
	RenderMesh(meshList[GEO_SPHERE], true);
	modelStack.PopMatrix();//hand back right

	modelStack.PushMatrix();//middle line
	modelStack.Scale(0.1, 0.189, 1);
	modelStack.Translate(0, 0, .12);
	RenderMesh(meshList[GEO_PIKACHUEYES], true);

	modelStack.PushMatrix();//left line
	modelStack.Translate(-1, 0, -0.05);
	RenderMesh(meshList[GEO_PIKACHUEYES], true);
	modelStack.PopMatrix();//left line

	modelStack.PushMatrix();
	modelStack.Translate(1, 0, -0.05);
	RenderMesh(meshList[GEO_PIKACHUEYES], true);
	modelStack.PopMatrix();

	modelStack.PopMatrix();//middle line

	modelStack.PopMatrix(); //hnad as a whole
}


/****************************************************************************/
/*!
\brief
PikachuBackstrip is a function used to create the back strip of pikachu before being callled in RenderPikachu
\param
2 Sphere scaled
Shpaes Variable: GEO_BACKSTRIP
*/
/****************************************************************************/
void SceneLight::PikachuBackstrip()
{
	modelStack.PushMatrix(); //strip 1
	modelStack.Scale(1.7, 0.5, 0.3);
	modelStack.Translate(0, -10, -10.5);
	RenderMesh(meshList[GEO_BACKSTRIP], true);

	modelStack.PushMatrix();// strip 2
	modelStack.Translate(0, -2, 0);
	RenderMesh(meshList[GEO_BACKSTRIP], true);

	modelStack.PopMatrix();//strip 2

	modelStack.PopMatrix();//strip 1
}

/****************************************************************************/
/*!
\brief
PikachuTail is a function used to create the tail of pikachu before being callled in RenderPikachu
\param
12 Triangles
5 Squares
Shpaes Variable: GEO_CUBE, GEO_TAILYELLOW, GEO_TAILBROWN
*/
/****************************************************************************/
void SceneLight::PikachuTail()
{

	modelStack.PushMatrix(); //tail as a whole
	modelStack.Rotate(30, -30, 0, 1);

	modelStack.PushMatrix(); //tail base
	modelStack.Scale(0.5, 1, 0.05);
	RenderMesh(meshList[GEO_CUBE], true);

	modelStack.PushMatrix();//tail part 2
	modelStack.Scale(0.98, 0.9, 0.9);
	modelStack.Translate(0, 0.5, 0);
	RenderMesh(meshList[GEO_TAILYELLOW], true);

	modelStack.PopMatrix();//tail part 2

	modelStack.PopMatrix();//tail base
	
	modelStack.PushMatrix();//part 3 as a whole
	modelStack.Translate(0.3, 1.2, 0);

	modelStack.PushMatrix();//tail patt 3
	modelStack.Rotate(30, 0, 0, 30);
	modelStack.Scale(1.5 , 0.7, 0.04);
	RenderMesh(meshList[GEO_TAILYELLOW], true);
	modelStack.PopMatrix();// tail part 3

	modelStack.PopMatrix();//part 3 as a whole

	modelStack.PushMatrix();//part 4 as a whole
	modelStack.Translate(0.3, 2, 0);

	modelStack.PushMatrix();//tail patt 4
	modelStack.Rotate(120, 0, 0, 120);
	modelStack.Scale(1.7 , 0.7, 0.04);
	RenderMesh(meshList[GEO_TAILYELLOW], true);
	modelStack.PopMatrix();// tail part 4

	modelStack.PopMatrix();//part 4 as a whole

	modelStack.PushMatrix();//part 5 as a whole
	modelStack.Translate(0.45, 3, 0);

	modelStack.PushMatrix();//tail patt 5
	modelStack.Rotate(35, 0, 0, 35);
	modelStack.Scale(2 , 1, 0.04);
	RenderMesh(meshList[GEO_TAILYELLOW], true);
	modelStack.PopMatrix();// tail part 5

	modelStack.PopMatrix();//part 5 as a whole


	//////////////////////////////////////////////////////////
	modelStack.PushMatrix();//first left triangle p1
	modelStack.Scale(0.1, 0.3, 1);
	modelStack.Translate(-2, 2.15, 0.028);
	RenderMesh(meshList[GEO_TAILBROWN], true);

	modelStack.PushMatrix(); //first left triangle p2
	modelStack.Rotate(180, 0, 180, 1);
	modelStack.Translate(-0.97, 0, 0);
	RenderMesh(meshList[GEO_TAILBROWN], true);

	modelStack.PushMatrix();//first right triangle p2
	modelStack.Translate(-3, 0, 0);
	RenderMesh(meshList[GEO_TAILBROWN], true);
	modelStack.PopMatrix();//first right triangle p2

	modelStack.PushMatrix(); //first middle triangle p2
	modelStack.Translate(-1.5,0 ,0);
	RenderMesh(meshList[GEO_TAILBROWN], true);
	modelStack.PopMatrix(); //first middle triangle p2

	modelStack.PopMatrix(); //first left triangle p2

	modelStack.PushMatrix();//first middle triangle p1
	modelStack.Translate(1.5, 0, 0);
	RenderMesh(meshList[GEO_TAILBROWN], true);
	modelStack.PopMatrix();//first middle triangle p1

	modelStack.PushMatrix(); //first right triangle p1
	modelStack.Translate(3, 0, 0);
	RenderMesh(meshList[GEO_TAILBROWN], true);
	modelStack.PopMatrix(); //first right triangle p1

	modelStack.PopMatrix();//first left triangle p1

	//////////////////////////////////////////////////////

	modelStack.PushMatrix();//back tail strip
	modelStack.Translate(0, 0, -0.06);

	modelStack.PushMatrix();//second left triangle p1
	modelStack.Scale(0.1, 0.3, 1);
	modelStack.Translate(-2, 2.15, 0.028);
	RenderMesh(meshList[GEO_TAILBROWN], true);

	modelStack.PushMatrix(); //second left triangle p2
	modelStack.Rotate(180, 0, 180, 1);
	modelStack.Translate(-0.97, 0, 0);
	RenderMesh(meshList[GEO_TAILBROWN], true);

	modelStack.PushMatrix();//second right triangle p2
	modelStack.Translate(-3, 0, 0);
	RenderMesh(meshList[GEO_TAILBROWN], true);
	modelStack.PopMatrix();//second right triangle p2

	modelStack.PushMatrix(); //second middle triangle p2
	modelStack.Translate(-1.5,0 ,0);
	RenderMesh(meshList[GEO_TAILBROWN], true);
	modelStack.PopMatrix(); //second middle triangle p2

	modelStack.PopMatrix(); //second left triangle p2

	modelStack.PushMatrix();//second middle triangle p1
	modelStack.Translate(1.5, 0, 0);
	RenderMesh(meshList[GEO_TAILBROWN], true);
	modelStack.PopMatrix();//second middle triangle p1

	modelStack.PushMatrix(); //second right triangle p1
	modelStack.Translate(3, 0, 0);
	RenderMesh(meshList[GEO_TAILBROWN], true);
	modelStack.PopMatrix(); //second right triangle p1

	modelStack.PopMatrix();//second left triangle p1

	modelStack.PopMatrix(); // back strip


	modelStack.PopMatrix();//tail as a whole
}

/****************************************************************************/
/*!
\brief
RenderPikachu is a function used to accomdate all the other Pikachu's parts that i have created before it it called in render so as to keep the code clean
\param
Functions Called: PikachuHead, PikachuBody, PikachuLeftFeet, PikachuRightFeet, PikachuLeftHands, PikachuRightHands, PikachuBackstrip, PikachuTail
*/
/****************************************************************************/
void SceneLight::RenderPikachu()
{
	modelStack.PushMatrix(); //ppikachu as a whole
	//modelStack.Translate(0, charPosition.y, charPosition.z);
	//modelStack.Rotate(charDirection.y, 0, charDirection.y, 1);
	modelStack.Translate(charPosition.x, 0, charPosition.z);
	modelStack.Rotate(angle, 0, angle, 1);

	modelStack.PushMatrix();
	modelStack.Scale(rotateJupiter, rotateJupiter, rotateJupiter);
	PikachuHead();
	PikachuBody();

	modelStack.PushMatrix(); //Feet
	modelStack.Scale(2.6, 2.7, 2.6);
	modelStack.Translate(-0.5, -3.85, 0.2);
	PikachuLeftFeet();
	PikachuRightFeet();
	modelStack.PopMatrix(); //feet

	modelStack.PopMatrix(); 
	

	modelStack.PushMatrix(); //left hadn
	modelStack.Scale(2, 2, 2);
	modelStack.Translate(-0.7, -2, 1);
	PikachuLeftHands();

	modelStack.PushMatrix(); //right hand
	modelStack.Translate(1.5, 0, 0);
	PikachuRightHands();
	modelStack.PopMatrix(); //right hand

	modelStack.PopMatrix(); //left hand

	modelStack.PushMatrix();
	modelStack.Translate(0, 1.5, 0);
	PikachuBackstrip();//backstrip
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Scale(4, 4, 4);
	modelStack.Translate(0, -5, 0);
	modelStack.Rotate(rotateLefthand, 0, 0, rotateLefthand);
	modelStack.Translate(0, 5, 0);
	modelStack.Translate(0.5, -1.5, -0.7);
	PikachuTail();//Tail
	modelStack.PopMatrix();


	modelStack.PopMatrix();//pikachu as a whole
}

/****************************************************************************/
/*!
\brief
PokeBallTop is a function used to create the top part of the pokeball
\param
Shapes Variable: GEO_POKEBALLRED, GEO_POKEBALLBLACK, GEO_POKEBALLBLACK2, GEO_POKEBALLWHITE
*/
/****************************************************************************/
void SceneLight::PokeBallTop()
{
	modelStack.PushMatrix(); //pokeball red
	modelStack.Scale(0.99, 0.99, 0.99);
	RenderMesh(meshList[GEO_POKEBALLRED], true);
	modelStack.PopMatrix(); // pokeball red

	modelStack.PushMatrix();//pokeball black as a whole
	modelStack.Translate(0, 0.08, 0);

	modelStack.PushMatrix();//pokeball ring top
	modelStack.Scale(0.2, 0.1, 0.2);
	modelStack.Translate(0, 0.2, 0);
	RenderMesh(meshList[GEO_POKEBALLBLACK], true);
	modelStack.PopMatrix();//pokeball ring top

	modelStack.PushMatrix();//pokeball button base
	modelStack.Scale(0.2, 0.2, 0.2);
	modelStack.Rotate(90, 90, 0, 1);
	modelStack.Translate(0, 5, 0.25);
	RenderMesh(meshList[GEO_POKEBALLBLACK2], true);

	modelStack.PushMatrix(); //pokeball button 2nd button
	modelStack.Scale(0.5, 0.5, 0.5);
	modelStack.Translate(0, 0.1, 0);
	RenderMesh(meshList[GEO_POKEBALLWHITE], true);
	modelStack.PopMatrix(); //pokeball button 2nd button
	modelStack.PopMatrix();//pokeball black as a whole

	modelStack.PopMatrix();//pokeball button base
}

/****************************************************************************/
/*!
\brief
PokeballBottom is a function used to create the bottom part of the pokeball
\param
Shapes Variable: GEO_POKEBALLWHITE2 and GEO_POKEBALLBLACK
*/
/****************************************************************************/
void SceneLight::PokeballBottom()
{
	modelStack.PushMatrix(); //pokeball white
	modelStack.Scale(0.99, 0.99, 0.99);
	modelStack.Rotate(180,180, 0, 1);
	RenderMesh(meshList[GEO_POKEBALLWHITE2], true);
	modelStack.PopMatrix(); // pokeball white

	modelStack.PushMatrix();//pokeball ring top
	modelStack.Scale(0.2, 0.1, 0.2);
	modelStack.Translate(0, 0.2, 0);
	RenderMesh(meshList[GEO_POKEBALLBLACK], true);
	modelStack.PopMatrix();//pokeball ring top
}

/****************************************************************************/
/*!
\brief
RenderPokeball is a function used to accomdate all the other Pokeball's parts that i have created before it it called in render so as to keep the code clean
\param
Functions Called: PokeBallTop and PokeballBottom
\param
rotateTail is used to rotate the tail to a certain angle
*/
/****************************************************************************/
void SceneLight::RenderPokeball()
{
	modelStack.PushMatrix();
	modelStack.Translate(0, 0.05, -1);
	modelStack.Rotate(rotateTail, -rotateTail, 0 ,1);
	modelStack.PushMatrix();
	modelStack.Translate(0, -0.05, 1);
	PokeBallTop();
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	PokeballBottom();
}


void SceneLight::debugPrint()
{
	std::cout << rotateLefthand << std::endl;
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

	//modelStack.PushMatrix();
	//modelStack.Scale(10000, 10000, 10000);
	//modelStack.Rotate(90, -90, 0, 1);
	//modelStack.Translate(0, 0, -0.02);
	//RenderMesh(meshList[GEO_QUAD], true);
	//modelStack.PopMatrix();

	RenderPikachu();
	
	modelStack.PushMatrix();
	modelStack.Translate(PokeballPosition.x, PokeballPosition.y, PokeballPosition.z);
	RenderPokeball();
	modelStack.PopMatrix();

	/*modelStack.PushMatrix();
	RenderMesh(meshList[GEO_CUBE], true);
	modelStack.PopMatrix();*/
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
