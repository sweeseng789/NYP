#include "SceneText.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Utility.h"

#include "Application.h"
#include "MeshBuilder.h"

#include "Vertex.h"
#include "LoadTGA.h"

#include"Camera3.h"

SceneText::SceneText()
{
}

SceneText::~SceneText()
{
}

void SceneText::Init()
{
	// Init VBO here

	// Set background color to dark blue
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);

	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Enable back face culling
	glEnable(GL_CULL_FACE);

	//Default to fill mode
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Generate a default VAO for now
	glGenVertexArrays(1, &m_vertexArrayID);
	glBindVertexArray(m_vertexArrayID);
	
	
	//Load vertex and fragment shaders
	//m_programID = LoadShaders( "Shader//Texture.vertexshader", "Shader//Blending.fragmentshader" );
	//m_programID = LoadShaders( "Shader//Texture.vertexshader", "Shader//Texture.fragmentshader" );
	m_programID = LoadShaders( "Shader//Texture.vertexshader", "Shader//MultiLight.fragmentshader");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights"); //in case you missed out practical 7


	// Get a handle for our "colorTexture" uniform
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture");

	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

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


	m_parameters[U_LIGHT1_POSITION] = glGetUniformLocation(m_programID, "lights[1].position_cameraspace");
	m_parameters[U_LIGHT1_COLOR] = glGetUniformLocation(m_programID, "lights[1].color");
	m_parameters[U_LIGHT1_POWER] = glGetUniformLocation(m_programID, "lights[1].power");
	m_parameters[U_LIGHT1_KC] = glGetUniformLocation(m_programID, "lights[1].kC");
	m_parameters[U_LIGHT1_KL] = glGetUniformLocation(m_programID, "lights[1].kL");
	m_parameters[U_LIGHT1_KQ] = glGetUniformLocation(m_programID, "lights[1].kQ");
	m_parameters[U_LIGHTENABLED] = glGetUniformLocation(m_programID, "lightEnabled");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");
	m_parameters[U_LIGHT1_TYPE] = glGetUniformLocation(m_programID, "lights[1].type");
	m_parameters[U_LIGHT1_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[1].spotDirection");
	m_parameters[U_LIGHT1_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[1].cosCutoff");
	m_parameters[U_LIGHT1_COSINNER] = glGetUniformLocation(m_programID, "lights[1].cosInner");
	m_parameters[U_LIGHT1_EXPONENT] = glGetUniformLocation(m_programID, "lights[1].exponent");	 


	glUseProgram(m_programID);

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_NUMLIGHTS], 2);


	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	light[0].type = Light::LIGHT_DIRECTIONAL;
	light[0].position.Set(0, 7.5, 7.8);
	light[0].color.Set(1, 1, 1);
	light[0].power = 1;
	light[0].kC = 1.f;
	light[0].kL = 0.01f;
	light[0].kQ = 0.001f;

	light[1].type = Light::LIGHT_POINT;
	light[1].position.Set(0, 7.5, 7.8);
	light[1].color.Set(1, 1, 1);
	light[1].power = 0;
	light[1].kC = 1.f;
	light[1].kL = 0.01f;
	light[1].kQ = 0.001f;
	light[1].cosCutoff = cos(Math::DegreeToRadian(45));
	light[1].cosInner = cos(Math::DegreeToRadian(30));
	light[1].exponent = 3.f;
	light[1].spotDirection.Set(0.f, 1.f, 0.f);

		// Make sure you pass uniform parameters after glUseProgram()
	glUniform3fv(m_parameters[U_LIGHT0_COLOR], 1, &light[0].color.r);
	glUniform1f(m_parameters[U_LIGHT0_POWER], light[0].power);
	glUniform1f(m_parameters[U_LIGHT0_KC], light[0].kC);
	glUniform1f(m_parameters[U_LIGHT0_KL], light[0].kL);
	glUniform1f(m_parameters[U_LIGHT0_KQ], light[0].kQ);

	glUniform1i(m_parameters[U_LIGHT1_TYPE], light[1].type);
	glUniform3fv(m_parameters[U_LIGHT1_COLOR], 1, &light[1].color.r);
	glUniform1f(m_parameters[U_LIGHT1_POWER], light[1].power);
	glUniform1f(m_parameters[U_LIGHT1_KC], light[1].kC);
	glUniform1f(m_parameters[U_LIGHT1_KL], light[1].kL);
	glUniform1f(m_parameters[U_LIGHT1_KQ], light[1].kQ);
	glUniform1f(m_parameters[U_LIGHT1_COSCUTOFF], light[1].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT1_COSINNER], light[1].cosInner);
	glUniform1f(m_parameters[U_LIGHT1_EXPONENT], light[1].exponent);

	//variable to rotate geometry
	scaleSize = 1000;
	moving = 0;
	FPS = 0;
	rotateRightHand = rotateLeftHand = rotateLeftFeet = rotateRightFeet = 1;
	turnOffLight = false;
	charDirection.x = charDirection.y = charDirection.z = 0;
	nearDoor = false;
	movingDoraemon = 6.2905;
	rotateDoraemon = 180;
	ActivateDoraemon = false;
	moveDoor = 0;

	unsigned ArialFontArray[256] = {
		41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41, 41,	41,	41,	41,	41,	41,	41,	41,	15,	17,	20,	31,	31,						
		49,	37,	11,	18,	18,	21,	32,	15,	18,	15,	15,	31,	31,	31,	31,	31,	31,	31,	31,	31,	31,	15,	15,	32,	32,	32,	31,	56,	37,	37,	40,	40,	37,	34,	43,	40,	15,							
		28,	37,	31,	45,	40,	43,	37,	43,	40,	37,	33,	40,	37,	54,	35,	35,	34,	15,	15,	15,	24,	31,	18,	31,	31,	28,	31,	31,	15,	31,	31,	11,	13,	28,	11,	47,	31,							
		31,	31,	31,	18,	28,	15,	31,	29,	39,	27,	27,	27,	18,	14,	18,	32, 41,	31,	41,	12,	31,	18,	55,	31,	31,	18,	56,	37,	18,	55,	41,	34,	41,	41,	12,	12,	18,							
		18,	19,	31,	55,	16,	55,	28,	18,	52,	41,	27,	37,	15,	17,	31,	31,	31,	31,	14,	31,	18,	41,	20,	31,	32,	18,	41,	30,	22,	30,	18,	18,	18,	32,	30,	18,	18,							
		18,	20,	31,	46,	46,	46,	34,	37,	37,	37,	37,	37,	37,	55,	40,	37,	37,	37,	37,	15,	15,	15,	15,	40,	40,	43,	43,	43,	43,	43,	32,	43,	40,	40,	40,	40,	37,
		37,	34,	31,	31,	31,	31,	31,	31,	49,	28,	31,	31,	31,	31,	15,	15,	15,	15,	31,	31,	31,	31,	31,	31,	31,	30,	34,	31,	31,	31,	31,	28,	31,	28
	};

	//Initialize camera settings
	camera.Init(Vector3(0, 0, 10), Vector3(0, 0, 0), Vector3(0, 1, 0));

	//remove all glGenBuffers, glBindBuffer, glBufferData code
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference", 1000, 1000, 1000);

	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", Color(1, 0, 0), 5);
	meshList[GEO_CUBE1] = MeshBuilder::GenerateCube("cube1", Color(1, 0, 1), 5);

	meshList[GEO_SPHERE] = MeshBuilder::GenerateSphere("Sphere", Color(0.95686274509, 0.86274509803, 0.14901960784), 18, 36, 1.f);
	meshList[GEO_SPHERE]->material.kAmbient.Set(1.0f, 0.90196078431f, 0.17647058823);
	meshList[GEO_SPHERE]->material.kDiffuse.Set(0.f, 1.f, 0.f);
	meshList[GEO_SPHERE]->material.kSpecular.Set(0.95686274509, 0.86274509803, 0.14901960784);
	meshList[GEO_SPHERE]->material.kShininess = 1.f;

	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f);
	meshList[GEO_QUAD]->material.kAmbient.Set(1.0f, 0.90196078431f, 0.17647058823);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.f, 1.f, 0.f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.95686274509, 0.86274509803, 0.14901960784);
	meshList[GEO_QUAD]->material.kShininess = 1.f;
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//color2.tga");

	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//front3.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//back3.tga");

	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//bottom3.tga");

	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//top3.tga");

	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//right3.tga");

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//left3.tga");

	meshList[GEO_EXIA] = MeshBuilder::GenerateQuad("exia", Color(1, 1, 1), 1.f);
	meshList[GEO_EXIA]->textureID = LoadTGA("Image//Exia.tga");

	meshList[GEO_MODEL1] = MeshBuilder::GenerateOBJ("model1", "OBJ//chair.obj");
	meshList[GEO_MODEL1]->textureID = LoadTGA("Image//chair.tga");

	meshList[GEO_MODEL2] = MeshBuilder::GenerateOBJ("model2", "OBJ//dart.obj");
	meshList[GEO_MODEL2]->textureID = LoadTGA("Image//dart.tga");

	meshList[GEO_MODEL3] = MeshBuilder::GenerateOBJ("model3", "OBJ//dartboard.obj");
	meshList[GEO_MODEL3]->textureID = LoadTGA("Image//dartboard.tga");

	meshList[GEO_MODEL4] = MeshBuilder::GenerateOBJ("model4", "OBJ//doorman.obj");
	meshList[GEO_MODEL4]->textureID = LoadTGA("Image//doorman.tga");

	meshList[GEO_MODEL5] = MeshBuilder::GenerateOBJ("model5", "OBJ//shoe.obj");
	meshList[GEO_MODEL5]->textureID = LoadTGA("Image//shoe.tga");

	meshList[GEO_MODEL6] = MeshBuilder::GenerateOBJ("model6", "OBJ//winebottle.obj");
	meshList[GEO_MODEL6]->textureID = LoadTGA("Image//winebottle.tga");

	meshList[GEO_CROSSHAIR] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f);
	meshList[GEO_CROSSHAIR]->textureID = LoadTGA("Image//Crosshair.tga");

	meshList[DoraemonHead] = MeshBuilder::GenerateOBJ("Doraemon Head", "OBJ//DoraemonHead.obj");
	meshList[DoraemonHead]->textureID = LoadTGA("Image//DoraemonHead.tga");

	meshList[DoraemonBell] = MeshBuilder::GenerateOBJ("Doraemon Bell", "OBJ//DoraemonBell.obj");
	meshList[DoraemonBell]->textureID = LoadTGA("Image//DoraemonBell.tga");

	meshList[DoraemonBody] = MeshBuilder::GenerateOBJ("Doraemon Body", "OBJ//DoraemonBody.obj");
	meshList[DoraemonBody]->textureID = LoadTGA("Image//DoraemonBody.tga");

	meshList[DoraemonLeftHand] = MeshBuilder::GenerateOBJ("Doraemon Left Hand", "OBJ//DoraemonLeftHand.obj");
	meshList[DoraemonLeftHand]->textureID = LoadTGA("Image//DoraemonHand.tga");

	meshList[DoraemonRightHand] = MeshBuilder::GenerateOBJ("Doraemon Right Hand", "OBJ//DoraemonRightHand.obj");
	meshList[DoraemonRightHand]->textureID = LoadTGA("Image//DoraemonHand.tga");

	meshList[DoraemonLeftFeet] = MeshBuilder::GenerateOBJ("Doraemon Left Feet", "OBJ//DoraemonLeftLeg.obj");
	meshList[DoraemonLeftFeet]->textureID = LoadTGA("Image//DoraemonHand.tga");

	meshList[DoraemonRightFeet] = MeshBuilder::GenerateOBJ("Doraemon Right Feet", "OBJ//DoraemonRightLeg.obj");
	meshList[DoraemonRightFeet]->textureID = LoadTGA("Image//DoraemonHand.tga");

	meshList[DoraemonRoom] = MeshBuilder::GenerateOBJ("Doraemon room", "OBJ//DoraemonRoom.obj");
	meshList[DoraemonRoom]->textureID = LoadTGA("Image//DoraemonRoom.tga");

	meshList[DoaremonRoomWall] = MeshBuilder::GenerateQuad("DoaremonRoomWall", Color(0, 0, 0), 1.f);
	meshList[DoaremonRoomWall]->textureID = LoadTGA("Image//DoraemonRoomWall.tga");
	meshList[DoaremonRoomWall]->material.kAmbient.Set(0, 0, 0);
	meshList[DoaremonRoomWall]->material.kDiffuse.Set(0.f, 0.f, 0.f);
	meshList[DoaremonRoomWall]->material.kSpecular.Set(0, 0, 0);
	meshList[DoaremonRoomWall]->material.kShininess = 0.5f;

	meshList[DoraemonRoomFloor] = MeshBuilder::GenerateQuad("DoaremonRoomFloor", Color(0, 0, 0), 1.f);
	meshList[DoraemonRoomFloor]->textureID = LoadTGA("Image//DoraemonRoomFloor.tga");
	meshList[DoraemonRoomFloor]->material.kAmbient.Set(0, 0, 0);
	meshList[DoraemonRoomFloor]->material.kDiffuse.Set(0.f, 0.f, 0.f);
	meshList[DoraemonRoomFloor]->material.kSpecular.Set(0, 0, 0);
	meshList[DoraemonRoomFloor]->material.kShininess = 0.5f;

	meshList[DoraemonSecondFloor] = MeshBuilder::GenerateQuad("DoraemonSecondFloor", Color(0, 0, 0), 1.f);
	meshList[DoraemonSecondFloor]->textureID = LoadTGA("Image//WoodenFloor.tga");
	meshList[DoraemonSecondFloor]->material.kAmbient.Set(0, 0, 0);
	meshList[DoraemonSecondFloor]->material.kDiffuse.Set(0.f, 0.f, 0.f);
	meshList[DoraemonSecondFloor]->material.kSpecular.Set(0, 0, 0);
	meshList[DoraemonSecondFloor]->material.kShininess = 0.5f;

	meshList[DoraemonRoomWallWithDoor] = MeshBuilder::GenerateQuad("DoaremonRoomFloor", Color(0, 0, 0), 1.f);
	meshList[DoraemonRoomWallWithDoor]->textureID = LoadTGA("Image//DoraemonRoomWallWithDoor.tga");
	meshList[DoraemonRoomWallWithDoor]->material.kAmbient.Set(0, 0, 0);
	meshList[DoraemonRoomWallWithDoor]->material.kDiffuse.Set(0.f, 0.f, 0.f);
	meshList[DoraemonRoomWallWithDoor]->material.kSpecular.Set(0, 0, 0);
	meshList[DoraemonRoomWallWithDoor]->material.kShininess = 0.5f;

	meshList[DoraemonRoomWallWithWindows] = MeshBuilder::GenerateQuad("DoaremonRoomFloor", Color(0, 0, 0), 1.f);
	meshList[DoraemonRoomWallWithWindows]->textureID = LoadTGA("Image//DoraemonRoomWallWithWindows.tga");
	meshList[DoraemonRoomWallWithWindows]->material.kAmbient.Set(0, 0, 0);
	meshList[DoraemonRoomWallWithWindows]->material.kDiffuse.Set(0, 0, 0);
	meshList[DoraemonRoomWallWithWindows]->material.kSpecular.Set(0, 0, 0);
	meshList[DoraemonRoomWallWithWindows]->material.kShininess = 0.5f;

	meshList[DoraemonDoor] = MeshBuilder::GenerateOBJ("Doraemon door", "OBJ//DoraemonDoor.obj");
	meshList[DoraemonDoor]->textureID = LoadTGA("Image//Door.tga");
	meshList[DoraemonDoor]->material.kAmbient.Set(0, 0, 0);
	meshList[DoraemonDoor]->material.kDiffuse.Set(0, 0, 0);
	meshList[DoraemonDoor]->material.kSpecular.Set(0, 0, 0);
	meshList[DoraemonDoor]->material.kShininess = 0.5f;

	meshList[DoraemonSlidingDoor] = MeshBuilder::GenerateOBJ("Doraemon door", "OBJ//DoraemonSlidingDoor.obj");
	meshList[DoraemonSlidingDoor]->textureID = LoadTGA("Image//DoraemonSlidingDoor.tga");
	meshList[DoraemonSlidingDoor]->material.kAmbient.Set(0, 0, 0);
	meshList[DoraemonSlidingDoor]->material.kDiffuse.Set(0.f, 0.f, 0.f);
	meshList[DoraemonSlidingDoor]->material.kSpecular.Set(0, 0, 0);
	meshList[DoraemonSlidingDoor]->material.kShininess = 0.5f;

	meshList[DoraemonCeiling] = MeshBuilder::GenerateQuad("DOraemon cilling", (0, 0, 0), 1);
	meshList[DoraemonCeiling]->textureID = LoadTGA("Image//Ceiling2.tga");
	meshList[DoraemonCeiling]->material.kAmbient.Set(0, 0, 0);
	meshList[DoraemonCeiling]->material.kDiffuse.Set(0.f, 0.f, 0.f);
	meshList[DoraemonCeiling]->material.kSpecular.Set(0, 0, 0);
	meshList[DoraemonCeiling]->material.kShininess = 0.5f;

	meshList[AnywhereDoor] = MeshBuilder::GenerateOBJ("AnywhereDoor", "OBJ//AnywhereDoor.obj");
	meshList[AnywhereDoor]->textureID = LoadTGA("Image//AnywhereDoor.tga");
	meshList[AnywhereDoor]->material.kAmbient.Set(0, 0, 0);
	meshList[AnywhereDoor]->material.kDiffuse.Set(0.f, 0.f, 0.f);
	meshList[AnywhereDoor]->material.kSpecular.Set(0, 0, 0);
	meshList[AnywhereDoor]->material.kShininess = 0.5f;

	meshList[Clock] = MeshBuilder::GenerateOBJ("DOraemon Clock", "OBJ//Clock.obj");
	meshList[Clock]->textureID = LoadTGA("Image//Clock.tga");
	meshList[Clock]->material.kAmbient.Set(0, 0, 0);
	meshList[Clock]->material.kDiffuse.Set(0.f, 0.f, 0.f);
	meshList[Clock]->material.kSpecular.Set(0, 0, 0);
	meshList[Clock]->material.kShininess = 0.5f;

	meshList[Cupboard] = MeshBuilder::GenerateOBJ("DOraemon Clock", "OBJ//Cupboard.obj");
	meshList[Cupboard]->textureID = LoadTGA("Image//Cupboard.tga");
	meshList[Cupboard]->material.kAmbient.Set(0, 0, 0);
	meshList[Cupboard]->material.kDiffuse.Set(0.f, 0.f, 0.f);
	meshList[Cupboard]->material.kSpecular.Set(0, 0, 0);
	meshList[Cupboard]->material.kShininess = 0.5f;


	meshList[DoraemonLight1] = MeshBuilder::GenerateOBJ("Doraemon light 1", "OBJ//Light1.obj");
	meshList[DoraemonLight1]->textureID = LoadTGA("Image//Light1.tga");

	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//Arial.tga");

	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("Lightball", Color(1, 1 ,1),18, 36, 1.f);

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 5000.f);
	projectionStack.LoadMatrix(projection);
}

static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;

void SceneText::Update(double dt)
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
	int SPEED  = 3;
	int SPEED2 = 12;

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


	if (Application::IsKeyPressed('8'))
		moving -= (float)(10 * dt);
	if (Application::IsKeyPressed('9'))
		moving += (float)(10 * dt);

	if (Application::IsKeyPressed('W'))
	{
		charDirection.x -= cos(Math::DegreeToRadian(moving)) * 10 * dt;
		charDirection.z -= sin(Math::DegreeToRadian(moving)) * 10 * dt;
	}
	if (Application::IsKeyPressed('S'))
	{
		charDirection.x += cos(Math::DegreeToRadian(moving)) * 10 * dt;
		charDirection.z += sin(Math::DegreeToRadian(moving)) * 10 * dt;
	}

	FPS = 1/dt;

	renderFPS = "FPS: " + std::to_string((long double) FPS); 


	static int ROTATELEFTHAND = 1;
	static int ROTATERIGHTHAND = 1;
	static int ROTATELEFTFEET = 1;
	static int ROTATERIGHTFEET = 1;
	static int count, count2;
	static int movement = false;

	if (ActivateDoraemon == true && movingDoraemon != 0)
	{
		if(rotateLeftHand * ROTATELEFTHAND >= 45)
		{
			ROTATELEFTHAND = -ROTATELEFTHAND;
			count++;
		}
		if (rotateRightHand * ROTATERIGHTHAND >= 45)
		{
			ROTATERIGHTHAND = -ROTATERIGHTHAND;
		}
		if (rotateLeftFeet * ROTATELEFTFEET >= 45)
		{
			ROTATELEFTFEET =  -ROTATELEFTFEET;
		}
		if (rotateRightFeet * ROTATERIGHTFEET >= 45)
		{
			ROTATERIGHTFEET =  -ROTATERIGHTFEET;
		}
		if (count >= 1)
		{
			rotateRightHand += (float)(ROTATERIGHTHAND * ROTATE_SPEED * dt * 5);
			rotateRightFeet += (float)(ROTATERIGHTFEET * ROTATE_SPEED * dt * 5);
		}
		rotateLeftHand += (float)(ROTATELEFTHAND * ROTATE_SPEED * dt * 5);
		rotateLeftFeet += (float)(ROTATELEFTFEET * ROTATE_SPEED * dt * 5);
	}
	else//reset
	{
		ROTATERIGHTHAND = ROTATELEFTHAND = rotateLeftHand = rotateRightHand = ROTATELEFTFEET = ROTATERIGHTFEET = rotateLeftFeet = rotateRightFeet = 1;
		count = 0;
	}

	if (Application::IsKeyPressed('T') && turnOffLight == false)
	{
		turnOffLight = true;
	}
	
	if (Application::IsKeyPressed('F') && turnOffLight == true)
	{
		turnOffLight = false;
	}

	if(camera.position.x >= -7 && camera.position.x <= 4.8)
	{
		if (camera.position.z >= -4.4 && camera.position.z <= 0.5)
		{
			camera.HaventOpenDoor = true;
			if (Application::IsKeyPressed('E'))
			{
				ActivateDoraemon = true;
			}
		}
		else
		{
			camera.HaventOpenDoor = false;
		}
	}

	if (ActivateDoraemon == true && movingDoraemon != 0 && moveDoor != -3.5 && rotateDoraemon != 90)
	{
		movingDoraemon -= (float)(ROTATE_SPEED * dt * 0.1);
		if (movingDoraemon <= 0)
		{
			movingDoraemon = 0;
		}
	}
	if (movingDoraemon == 0 && ActivateDoraemon == true && rotateDoraemon != 90 && moveDoor != -3.5)
	{
		rotateDoraemon -= (float)(ROTATE_SPEED * dt * 5);
		if (rotateDoraemon <= 90)
		{
			rotateDoraemon = 90;
		}
	}
	if (movingDoraemon == 0 && ActivateDoraemon == true && rotateDoraemon == 90 && moveDoor != -3.5)
	{
		moveDoor -= (float)(ROTATE_SPEED * dt * 0.1);
		if (moveDoor <= -3.5)
		{
			moveDoor = -3.5;
		}
	}
	if (movingDoraemon == 0 && ActivateDoraemon == true && moveDoor == -3.5 && rotateDoraemon != 1)
	{
		rotateDoraemon -= (float)(ROTATE_SPEED * dt * 5);
		if (rotateDoraemon <= 1)
		{
			rotateDoraemon = 1;
		}
	}
	if (movingDoraemon != -5.5 && ActivateDoraemon == true && moveDoor == -3.5 && rotateDoraemon == 1)
	{
		movingDoraemon -= (float)(ROTATE_SPEED * dt * 0.1);
		if (movingDoraemon <= -5.5)
		{
			movingDoraemon = -5.5;
			//6.2905
		}
	}
	if (movingDoraemon == -5.5 && ActivateDoraemon == true && moveDoor == -3.5 && rotateDoraemon != 180)
	{
		/*rotateDoraemon += (float)(ROTATE_SPEED * dt * 5);
		if (rotateDoraemon >= 180)
		{
			rotateDoraemon = 180;
		}*/
		movingDoraemon = 6.2905;
	rotateDoraemon = 180;
	ActivateDoraemon = false;
	//moveDoor = 0;
	}
	if (ActivateDoraemon == true)
	{
		camera.position.x = 0;
		camera.position.z = 14;
	}
	camera.Update(dt);
	//std::cout << moving << std::endl;
	std::cout << movingDoraemon << std::endl;
}

void SceneText::RenderSkybox()
{
	modelStack.PushMatrix();
	modelStack.Scale(scaleSize, scaleSize, scaleSize);
	modelStack.Translate(0, 0, -0.00169619);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(scaleSize, scaleSize, scaleSize);
	modelStack.Rotate(90, 0, -90, 0);
	modelStack.Translate(-0.49814095  , 0, 0.49649683 + -0.00170516 + -0.0286548);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(scaleSize, scaleSize, scaleSize);
	modelStack.Rotate(90, 0, 180, 0);
	modelStack.Translate(0.498585 , 0.00254769, 0.49649683 + -0.00510058);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 180, 0);
	modelStack.PushMatrix();
	modelStack.Scale(scaleSize, scaleSize, scaleSize);
	modelStack.Translate(-0.0286548, 0, 0.991158 +-0.00594854);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	
	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, 90, 0);

	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 180, 0);
	modelStack.PushMatrix();
	modelStack.Scale(scaleSize, scaleSize, scaleSize);
	modelStack.Rotate(270, 270, 0, 0);
	//modelStack.Translate(0.491462 + 0.00678009, 0, 0.499845 -0.00340081);
	modelStack.Translate(-0.493089, -0.00648329, 0.49309);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(scaleSize, scaleSize, scaleSize);
	modelStack.Rotate(90, 90, 0, 0);
	modelStack.Translate(0.017004, -0.510025 + 0.0135941, 0.503292 + -0.00170143);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();
}

void SceneText::RenderDoraemonRoom()
{
	if (turnOffLight == false)
	{
		modelStack.PushMatrix(); // front
		modelStack.Scale(20, 20, 20);
		RenderMesh(meshList[DoraemonRoomWallWithWindows], false);
		modelStack.PopMatrix(); // front

		modelStack.PushMatrix(); // left
		modelStack.Scale(20, 20, 20);
		modelStack.Rotate(90, 0, 90, 0);
		modelStack.Translate(-0.5, 0, -0.5);
		RenderMesh(meshList[DoaremonRoomWall], false);
		modelStack.PopMatrix(); // left

		modelStack.PushMatrix(); // right
		modelStack.Scale(20, 20, 20);
		modelStack.Rotate(90, 0, 90, 0);
		modelStack.Translate(-0.5, 0, 0.5);
		RenderMesh(meshList[DoaremonRoomWall], false);
		modelStack.PopMatrix(); // right

		modelStack.PushMatrix(); // back
		modelStack.Scale(20, 20, 20);
		modelStack.Translate(0, 0, 1);
		RenderMesh(meshList[DoraemonRoomWallWithDoor], false);
		modelStack.PopMatrix(); // back

		modelStack.PushMatrix(); // bottom
		modelStack.Scale(20, 20, 20);
		modelStack.Rotate(90, 90, 0, 0);
		modelStack.Translate(0, 0.34 + 0.161635, 0.6 + -0.17);
		RenderMesh(meshList[DoraemonRoomFloor], false);
		modelStack.PopMatrix(); // bottom

		modelStack.PushMatrix(); // top
		modelStack.Scale(20, 20, 20);
		modelStack.Rotate(90, 90, 0, 0);
		modelStack.Translate(0, 0.34 + 0.161635, 0.6 + -0.17 + -0.926676);
		RenderMesh(meshList[DoaremonRoomWall], false);
		modelStack.PopMatrix(); // top

		modelStack.PushMatrix();//rotate Door

		modelStack.PushMatrix();
		modelStack.Scale(3, 3, 3);
		modelStack.Translate(0.5, -3.46836, 7.30332 - 0.498328);
		RenderMesh(meshList[DoraemonDoor], false);
		modelStack.PopMatrix();
		modelStack.PopMatrix();// rotate door

		modelStack.PushMatrix(); //rotate bothdoor
		modelStack.Translate(0, 0, 2.38039);
		modelStack.PushMatrix(); // SD1
		modelStack.Scale(2, 4, 3);
		modelStack.Translate(5.33049, -2.6983, 1.9);
		RenderMesh(meshList[DoraemonSlidingDoor], false);
		modelStack.PopMatrix(); // SD1

		modelStack.PushMatrix(); // SD2
		modelStack.Scale(2, 4, 3);
		modelStack.Translate(5.33049 + 0.120509, -2.6983, 1.9 + 2.20991);
		RenderMesh(meshList[DoraemonSlidingDoor], false);
		modelStack.PopMatrix(); // SD2
		modelStack.PopMatrix(); //rotate both door

		modelStack.PushMatrix();
		modelStack.Scale(2, 2, 1);
		modelStack.Translate(-4.14218, -4.14828, 15.8);
		RenderMesh(meshList[Cupboard], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Scale(1.5, 1.5, 1.5);
		modelStack.Translate(0, moveDoor, 3.3 );
		RenderMesh(meshList[AnywhereDoor], false);
		modelStack.PopMatrix();
	}
	else
	{
		modelStack.PushMatrix(); // front
		modelStack.Scale(20, 20, 20);
		RenderMesh(meshList[DoraemonRoomWallWithWindows], true);
		modelStack.PopMatrix(); // front

		modelStack.PushMatrix(); // left
		modelStack.Scale(20, 20, 20);
		modelStack.Rotate(90, 0, 90, 0);
		modelStack.Translate(-0.5, 0, -0.5);
		RenderMesh(meshList[DoaremonRoomWall], true);
		modelStack.PopMatrix(); // left

		modelStack.PushMatrix(); // right
		modelStack.Scale(20, 20, 20);
		modelStack.Rotate(90, 0, 90, 0);
		modelStack.Translate(-0.5, 0, 0.5);
		RenderMesh(meshList[DoaremonRoomWall], true);
		modelStack.PopMatrix(); // right

		modelStack.PushMatrix(); // back
		modelStack.Scale(20, 20, 20);
		modelStack.Translate(0, 0, 1);
		RenderMesh(meshList[DoraemonRoomWallWithDoor], true);
		modelStack.PopMatrix(); // back

		modelStack.PushMatrix(); // bottom
		modelStack.Scale(20, 20, 20);
		modelStack.Rotate(90, 90, 0, 0);
		modelStack.Translate(0, 0.34 + 0.161635, 0.6 + -0.17);
		RenderMesh(meshList[DoraemonRoomFloor], true);
		modelStack.PopMatrix(); // bottom

		modelStack.PushMatrix(); // top
		modelStack.Scale(20, 20, 20);
		modelStack.Rotate(90, 90, 0, 0);
		modelStack.Translate(0, 0.34 + 0.161635, 0.6 + -0.17 + -0.926676);
		RenderMesh(meshList[DoaremonRoomWall], true);
		modelStack.PopMatrix(); // top

		modelStack.PushMatrix();//rotate Door

		modelStack.PushMatrix();
		modelStack.Scale(3, 3, 3);
		modelStack.Translate(0.5, -3.46836, 7.30332 - 0.498328);
		RenderMesh(meshList[DoraemonDoor], true);
		modelStack.PopMatrix();
		modelStack.PopMatrix();// rotate door

		modelStack.PushMatrix(); //rotate bothdoor
		modelStack.Translate(0, 0, 2.38039);
		modelStack.PushMatrix(); // SD1
		modelStack.Scale(2, 4, 3);
		modelStack.Translate(5.33049, -2.6983, 1.9);
		RenderMesh(meshList[DoraemonSlidingDoor], true);
		modelStack.PopMatrix(); // SD1

		modelStack.PushMatrix(); // SD2
		modelStack.Scale(2, 4, 3);
		modelStack.Translate(5.33049 + 0.120509, -2.6983, 1.9 + 2.20991);
		RenderMesh(meshList[DoraemonSlidingDoor], true);
		modelStack.PopMatrix(); // SD2
		modelStack.PopMatrix(); //rotate both door

		modelStack.PushMatrix();
		modelStack.Scale(2, 2, 1);
		modelStack.Translate(-4.14218, -4.14828, 15.8);
		RenderMesh(meshList[Cupboard], true);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Scale(2, 2, 2);
		modelStack.Translate(0, 0, 3.3);
		RenderMesh(meshList[AnywhereDoor], true);
		modelStack.PopMatrix();
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
		characterSpacing.SetToTranslation(i * 0.5f, 0, 0); //1.0f is the spacing of each character, you may change this value
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
		characterSpacing.SetToTranslation(i * 0.5f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	
		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);

	//Add these code just before glEnable(GL_DEPTH_TEST);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();

	glEnable(GL_DEPTH_TEST);
}

void SceneText::RenderDoraemon()
{
	modelStack.PushMatrix();//Doraemon head

	modelStack.Rotate(5, 0, 5, 0);
	RenderMesh(meshList[DoraemonHead], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.02312, 0 ,0);
	RenderMesh(meshList[DoraemonBell], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, -1.129767, 0);
	RenderMesh(meshList[DoraemonBody], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix(); //rotate left hand
	modelStack.Rotate(-rotateLeftHand, 0, rotateLeftHand , 0);
	modelStack.PushMatrix();//Left hand
	modelStack.Translate(0, -1.1050815, 0);
	RenderMesh(meshList[DoraemonLeftHand], false);
	modelStack.PopMatrix();//left hand
	modelStack.PopMatrix(); //rotate left hadn

	modelStack.PushMatrix(); //rotate right hadn
	modelStack.Rotate(rotateRightHand, 0, rotateRightHand, 0);
	modelStack.PushMatrix();//right hand
	modelStack.Translate(0, -1.11358, -1.0931759);
	RenderMesh(meshList[DoraemonRightHand], false);
	modelStack.PopMatrix();//right hand
	modelStack.PopMatrix(); //rotate rigth hand

	modelStack.PushMatrix();
	modelStack.Rotate(-rotateLeftFeet, 0, 0, rotateLeftFeet);
	modelStack.Translate(0, -1.82765, -2.32952);
	RenderMesh(meshList[DoraemonLeftFeet], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(-rotateRightFeet, 0, 0, rotateRightFeet);
	modelStack.Translate(0, -1.82765, -2.32952 + 0.85077);
	RenderMesh(meshList[DoraemonRightFeet], false);
	modelStack.PopMatrix();
}

void SceneText::DoraemonSceondRoom()
{
	modelStack.PushMatrix(); //bottom
	modelStack.Translate(-10.0307, -5.95027, 27 + 1.02014);
	modelStack.PushMatrix();
	modelStack.Scale(40, 20, 20);
	modelStack.Rotate(90, 90, 0, 0);
	RenderMesh(meshList[DoraemonSecondFloor], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();//bottom


	modelStack.PushMatrix(); // right
	modelStack.Scale(20, 20, 22);
	modelStack.Rotate(90, 0, 90, 0);
	modelStack.Translate(-0.5 - 0.781, 0.170052, 0.5);
	RenderMesh(meshList[DoaremonRoomWall], false);
	modelStack.PopMatrix(); // right

	modelStack.PushMatrix(); // right
	modelStack.Scale(25, 20, 20);
	modelStack.Translate(-0.884079, 0, 0.9);
	RenderMesh(meshList[DoaremonRoomWall], false);
	modelStack.PopMatrix(); // right

	modelStack.PushMatrix(); // right
	modelStack.Scale(20, 20, 22);
	modelStack.Rotate(90, 0, 90, 0);
	modelStack.Translate(-0.5 - 0.781, 0.170052, 0.5 - 2.00628);
	RenderMesh(meshList[DoaremonRoomWall], false);
	modelStack.PopMatrix(); // right

	modelStack.PushMatrix(); // right
	modelStack.Scale(50, 20, 20);
	modelStack.Translate(-0.204026, 0, 0.9 + 0.986214);
	RenderMesh(meshList[DoaremonRoomWall], false);
	modelStack.PopMatrix(); // right

	modelStack.PushMatrix();
	modelStack.Translate(-10.0307, -5.95027 + 15.9147, 27 + 1.02014);
	modelStack.PushMatrix();
	modelStack.Scale(40, 20, 20);
	modelStack.Rotate(90, 90, 0, 0);
	RenderMesh(meshList[DoraemonCeiling], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();//clock
	modelStack.Rotate(90, 0, 90, 0);
	modelStack.Translate(-28.0189, 6, 9.69088);
	RenderMesh(meshList[Clock], false);
	modelStack.PopMatrix();

}

void SceneText::Render()
{
	// Render VBO here
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);

	modelStack.LoadIdentity();

	Position lightPosition_cameraspace = viewStack.Top() * light[0].position;
	glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightPosition_cameraspace.x);

	Position lightPosition_cameraspace1 = viewStack.Top() * light[1].position;
	glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace1.x);


	RenderMesh(meshList[GEO_AXES], false);

	modelStack.PushMatrix();
	modelStack.Scale(1,1,1);
	modelStack.Translate(light[0].position.x, light[0].position.y + 2, light[0].position.z);
	RenderMesh(meshList[DoraemonLight1], false);
	modelStack.PopMatrix();

	/*modelStack.PushMatrix();
	modelStack.Scale(3, 3, 3);
	modelStack.Translate(light[1].position.x, light[1].position.y + moving, light[1].position.z);
	RenderMesh(meshList[DoraemonLight1], false);
	modelStack.PopMatrix();*/

	modelStack.PushMatrix();
	modelStack.Translate(camera.World.x, camera.World.y , camera.World.z);

	modelStack.PushMatrix();
	modelStack.Translate(0, 350, 150);
	RenderSkybox();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Scale(10, 10, 10);
	//RenderText(meshList[GEO_TEXT], "Bao Yin", Color(0, 0, 0));
	modelStack.PopMatrix();

	modelStack.PushMatrix(); //whole room with doraemon
	modelStack.Translate(0, -3.23059, 0);

	modelStack.PushMatrix(); //rotateDoraemo
	modelStack.Scale(1.5, 1.5, 1.5);
	modelStack.Rotate(rotateDoraemon, 0, rotateDoraemon, 0);
	modelStack.Translate(movingDoraemon, 0, 0);
	RenderDoraemon();
	modelStack.PopMatrix(); // roatteDoraemon

	modelStack.PushMatrix();
	modelStack.Translate(0, 6.9713 + 0.170095 - 0.679906, -2);
	RenderDoraemonRoom();
	modelStack.PopMatrix();
	modelStack.PopMatrix();//whole room with doraemon

	DoraemonSceondRoom();

	if (camera.edgeOfWorld == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-29.5, 0, 30);
		modelStack.Rotate(90, 0, 90, 0);
		RenderText(meshList[GEO_TEXT], "World Edge Reached", Color(1, 0, 0));
		modelStack.PopMatrix();
	}

	RenderTextOnScreen(meshList[GEO_TEXT], renderFPS, Color(0, 1, 0), 5, 1, 11);

	if (camera.HaventOpenDoor == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "Press E to interact", Color(0.5, 0.5, 0.5), 2, 1, 1);
	}
}

void SceneText::RenderMesh(Mesh *mesh, bool enableLight)
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
		
		(m_parameters[U_LIGHTENABLED], 0);
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


	if(light[1].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(light[1].position.x, light[1].position.y, light[1].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if(light[1].type == Light::LIGHT_SPOT)
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
		Vector3 spotDirection_cameraspace = viewStack.Top() * light[1].spotDirection;
		glUniform3fv(m_parameters[U_LIGHT1_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
	}
	else
	{
		Position lightPosition_cameraspace = viewStack.Top() * light[1].position;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightPosition_cameraspace.x);
	}	

	mesh->Render(); //this line should only be called once 
	
	if(mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

}


void SceneText::Exit()
{
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
