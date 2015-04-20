#include "StudioProject.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

#include "Vertex.h"
#include "LoadTGA.h"

StudioProject::StudioProject()
{
}

StudioProject::~StudioProject()
{
}

void StudioProject::Init()
{
	// Set background color to black
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	//Enable depth buffer and depth testing
	glEnable(GL_DEPTH_TEST);
	//Enable back face culling
	glDisable(GL_CULL_FACE);
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
	worldsize = 1000.0f;
	roomsize = 250.0f;
	roomheight = 150.0f;
	fps = 0.0f;

	//variable to animate metaknight
	rotateAngle = 0;
	rotateRightFeet = -90;
	rotateLeftFeet = 90;
	rotateLeftArm = 0;
	rotateRightArm = 0;
	translateRightFeet = -0.2f;
	translateLeftFeet = -0.2f;
	rotateWings = 0.0f;
	translateHead = -20.0f;
	translateBody = 0.0f;
	rotateDirection = 0.0f;
	scaleShock = 0.3f;
	translateShock = 1.0f;
	scaleShock2 = 0.1f;
	translateShock2 = 1.0f;

	//variable to animate wardrobe
	translateThird = 95;
	translateSecond = 50;
	translateFirst = 5.f;
	isOpen = false;

	//variable to animate window
	rotateWindowML = 0;
	rotateWindowM = 0;
	rotateWindowR = 0;

	Framerate = "FPS: ";
	//Initialize camera settings
	camera.Init(Vector3(0, 30, 60), Vector3(0, 0, 0), Vector3(0, 1, 0));

	//Initialize all meshes to NULL
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference",Color(1,1,1),1000, 1000, 1000);

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 10000.f);
	projectionStack.LoadMatrix(projection);

	m_programID = LoadShaders( "Shader//Texture.vertexshader", "Shader//MultiLight.fragmentshader");
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
	lights[0].type = Light::LIGHT_POINT;
	lights[0].position.Set(0, 135, 0);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 20;
	lights[0].kC = 1.f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.001f;
	lights[0].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0].cosInner = cos(Math::DegreeToRadian(30));
	lights[0].exponent = 3.f;
	lights[0].spotDirection.Set(0.f, 1.f, 0.f);

	//Light 2
	lights[1].type = Light::LIGHT_DIRECTIONAL;
	lights[1].position.Set(-450, 200, 120);
	lights[1].color.Set(1, 1, 1);
	lights[1].power = 0.5f;
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

	/*
	========================Sky Box=====================================
	========================Sky Box=====================================
	========================Sky Box=====================================
	*/
	meshList[GEO_FRONT] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//hills_ft.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//hills_bk.tga");

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//hills_rt.tga");

	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//hills_lf.tga");

	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//hills_up.tga");

	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//hills_dn.tga");

	/*
	========================Room Box=====================================
	========================Room Box=====================================
	========================Room Box=====================================
	*/

	meshList[GEO_RFRONT] = MeshBuilder::GenerateQuad("rfront", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_RFRONT]->textureID = LoadTGA("Image//top2.tga");

	meshList[GEO_RBACK] = MeshBuilder::GenerateQuad("rback", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_RBACK]->textureID = LoadTGA("Image//top2.tga");

	meshList[GEO_RLEFT] = MeshBuilder::GenerateQuad("rleft", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_RLEFT]->textureID = LoadTGA("Image//top2.tga");

	meshList[GEO_RRIGHT] = MeshBuilder::GenerateQuad("rright", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_RRIGHT]->textureID = LoadTGA("Image//top2.tga");

	meshList[GEO_RTOP] = MeshBuilder::GenerateQuad("rtop", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_RTOP]->textureID = LoadTGA("Image//top2.tga");

	meshList[GEO_RBOTTOM] = MeshBuilder::GenerateQuad("rbottom", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_RBOTTOM]->textureID = LoadTGA("Image//bottom2.tga");

	//====================META KNIGHT RELATED============================//
	//====================META KNIGHT RELATED============================//
	//====================META KNIGHT RELATED============================//
	//=========================Head=====================
	meshList[GEO_HEAD] = MeshBuilder::GenerateSphere("Head",Color(0.094f, 0.133f, 0.404f), 18, 36, 1.f);
	meshList[GEO_HEAD]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HEAD]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_HEAD]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HEAD]->material.kShininess = 8.f;

	//==========================Mask=======================
	meshList[GEO_MASK] = MeshBuilder::GenerateHemiSphere("Mask",Color(0.835f, 0.784f, 0.820f), 18, 36, 1.f);
	meshList[GEO_MASK]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MASK]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_MASK]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MASK]->material.kShininess = 8.f;


	//=========================Mask 2==========================
	meshList[GEO_MASK2] = MeshBuilder::GenerateSphere("Mask2",Color(0.835f, 0.784f, 0.820f), 18, 36, 1.f);
	meshList[GEO_MASK2]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MASK2]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_MASK2]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MASK2]->material.kShininess = 8.f;

	//========================Eye============================
	meshList[GEO_EYE] = MeshBuilder::GenerateSphere("Eye",Color(0.996f, 0.980f, 0.004f), 18, 36, 1.f);
	meshList[GEO_EYE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_EYE]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_EYE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_EYE]->material.kShininess = 8.f;

	//=======================Feet============================
	meshList[GEO_FEET] = MeshBuilder::GenerateHemiSphere("Feet",Color(0.482f, 0.227f, 0.478f), 18, 36, 1.f);
	meshList[GEO_FEET]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_FEET]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_FEET]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_FEET]->material.kShininess = 8.f;

	//=======================Shoulder Pad===========================
	meshList[GEO_SHOULDER] = MeshBuilder::GenerateSphere("Shoulder",Color(0.729f, 0.694f, 0.871f), 18, 36, 1.f);
	meshList[GEO_SHOULDER]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SHOULDER]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_SHOULDER]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SHOULDER]->material.kShininess = 8.f;

	//===================Shoulder Ring===============================
	meshList[GEO_SHOULDERRING] = MeshBuilder::GenerateSphere("ShoulderRing",Color(0.537f, 0.431f, 0.161f), 18, 36, 1.f);
	meshList[GEO_SHOULDERRING]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SHOULDERRING]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_SHOULDERRING]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SHOULDERRING]->material.kShininess = 8.f;

	//====================Wings Base======================================
	meshList[GEO_WINGBASE] = MeshBuilder::GenerateCylinder("WingBase",Color(0.204f, 0.188f, 0.333f), 18, 36, 1.f, 1.f);
	meshList[GEO_WINGBASE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_WINGBASE]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_WINGBASE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_WINGBASE]->material.kShininess = 8.f;

	//=======================Wing Sphere==========================
	meshList[GEO_WINGSPHERE] = MeshBuilder::GenerateSphere("WingSphere",Color(0.204f, 0.188f, 0.333f), 18, 36, 1.f);
	meshList[GEO_WINGSPHERE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_WINGSPHERE]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_WINGSPHERE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_WINGSPHERE]->material.kShininess = 8.f;

	//=====================Wing Spike================================
	meshList[GEO_WINGSPIKE] = MeshBuilder::GenerateCone("WingSpike",Color(0.835f, 0.784f, 0.820f), 18, 36, 1.f, 1.f);
	meshList[GEO_WINGSPIKE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_WINGSPIKE]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_WINGSPIKE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_WINGSPIKE]->material.kShininess = 8.f;

	//======================Wing Skele======================
	meshList[GEO_WINGSKELE] = MeshBuilder::GenerateCone("WingSkele",Color(0.204f, 0.188f, 0.333f), 18, 36, 1.f, 1.f);
	meshList[GEO_WINGSKELE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_WINGSKELE]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_WINGSKELE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_WINGSKELE]->material.kShininess = 8.f;

	//====================Wing Content=========================
	meshList[GEO_WINGCONTENT] = MeshBuilder::GenerateQuad("WingContent", Color(0.561f, 0.522f, 0.753f), 1,1);
	meshList[GEO_WINGCONTENT]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_WINGCONTENT]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_WINGCONTENT]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_WINGCONTENT]->material.kShininess = 8.f;

	//=====================Hands===========================
	meshList[GEO_HAND] = MeshBuilder::GenerateSphere("Hand",Color(0.835f, 0.784f, 0.820f), 18, 36, 1.f);
	meshList[GEO_HAND]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HAND]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_HAND]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_HAND]->material.kShininess = 8.f;

	//====================Sword Handle=========================
	meshList[GEO_SWORDHANDLE] = MeshBuilder::GenerateCylinder("SwordHandle",Color(0.655f, 0.561f, 0.122f), 18, 36, 1.f, 1.f);
	meshList[GEO_SWORDHANDLE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SWORDHANDLE]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_SWORDHANDLE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SWORDHANDLE]->material.kShininess = 8.f;

	//====================BTM Sword Sphere==========================
	meshList[GEO_SWORDSPHERE] = MeshBuilder::GenerateSphere("BtmSwordSphere",Color(0.620f, 0.482f, 0.149f), 18, 36, 1.f);
	meshList[GEO_SWORDSPHERE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SWORDSPHERE]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_SWORDSPHERE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SWORDSPHERE]->material.kShininess = 8.f;

	//=============================Top Sword Sphere================================
	meshList[GEO_SWORDSPHERE2] = MeshBuilder::GenerateSphere("TopSwordSphere",Color(0.835f, 0.761f, 0.318f), 18, 36, 1.f);
	meshList[GEO_SWORDSPHERE2]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SWORDSPHERE2]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_SWORDSPHERE2]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SWORDSPHERE2]->material.kShininess = 8.f;

	//==========================Sword Hilt=====================================
	meshList[GEO_SWORDHILT] = MeshBuilder::GenerateCone("SwordHilt",Color(0.835f, 0.761f, 0.318f), 18, 36, 1.f, 1.f);
	meshList[GEO_SWORDHILT]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SWORDHILT]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_SWORDHILT]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SWORDHILT]->material.kShininess = 8.f;

	//========================Sword Blade=====================================
	meshList[GEO_SWORDBLADE] = MeshBuilder::GenerateHemiSphere("SwordBlade",Color(1.0f, 0.988f, 0.616f), 18, 36, 1.f);
	meshList[GEO_SWORDBLADE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SWORDBLADE]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_SWORDBLADE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SWORDBLADE]->material.kShininess = 8.f;

	//========================Shock wave=====================================
	meshList[GEO_SHOCKWAVE] = MeshBuilder::GenerateQuad("ShockWave", Color(1.0f, 0.988f, 0.616f), 1,1);
	meshList[GEO_SHOCKWAVE]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_SHOCKWAVE]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_SHOCKWAVE]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_SHOCKWAVE]->material.kShininess = 8.f;

	//========================Shock wave2=====================================
	meshList[GEO_SHOCKWAVE2] = MeshBuilder::GenerateTorus("ShockWave2", Color(1.0f, 0.5f, 0.0f), 0.5,3);
	meshList[GEO_SHOCKWAVE2]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_SHOCKWAVE2]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_SHOCKWAVE2]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_SHOCKWAVE2]->material.kShininess = 8.f;

	//=====================Top Part of Mask================================
	meshList[GEO_TOPPART] = MeshBuilder::GenerateTopPart("TopMask",Color(1.0f, 1.0f, 1.0f), 36, 1.f);
	meshList[GEO_TOPPART]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_TOPPART]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_TOPPART]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_TOPPART]->material.kShininess = 8.f;

	//=====================Btm Part of Mask================================
	meshList[GEO_BTMPART] = MeshBuilder::GenerateBtmPart("BtmMask",Color(1.f, 1.f, 1.f), 36, 1.f);
	meshList[GEO_BTMPART]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BTMPART]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BTMPART]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BTMPART]->material.kShininess = 8.f;

	//================================Mask Cover===================================
	meshList[GEO_COVER] = MeshBuilder::GenerateMask("MaskCover", Color(0.602f, 0.602f, 0.602f), 0.5,3);
	meshList[GEO_COVER]->material.kAmbient.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_COVER]->material.kDiffuse.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_COVER]->material.kSpecular.Set(0.8f, 0.8f, 0.8f);
	meshList[GEO_COVER]->material.kShininess = 8.f;

	//==========================Mask Spike=====================================
	meshList[GEO_MASKSPIKE] = MeshBuilder::GenerateCone("MaskSpike",Color(0.602f, 0.602f, 0.602f), 4, 36, 1.f, 1.f);
	meshList[GEO_MASKSPIKE]->material.kAmbient.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MASKSPIKE]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_MASKSPIKE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MASKSPIKE]->material.kShininess = 8.f;

	//====================END META KNIGHT RELATED============================//
	//====================END META KNIGHT RELATED============================//

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

	//===============OBJ in Room Related=====================//
	//===============OBJ in Room Related=====================//
	//===============OBJ in Room Related=====================//

	//==Sofa==//
	meshList[GEO_SOFA] = MeshBuilder::GenerateOBJ("sofa", "OBJ//Sofa.obj");
	meshList[GEO_SOFA]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SOFA]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_SOFA]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SOFA]->material.kShininess = 8.f;
	meshList[GEO_SOFA]->textureID = LoadTGA("Image//Sofa_texture.tga");

	//==Wardrobe==//
	meshList[GEO_WARDROBE] = MeshBuilder::GenerateOBJ("wardrobe", "OBJ//Wardrobe.obj");
	meshList[GEO_WARDROBE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_WARDROBE]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_WARDROBE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_WARDROBE]->material.kShininess = 8.f;
	meshList[GEO_WARDROBE]->textureID = LoadTGA("Image//Wardrobe_texture.tga");

	//==Table==//
	meshList[GEO_TABLE] = MeshBuilder::GenerateOBJ("table", "OBJ//Table.obj");
	meshList[GEO_TABLE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_TABLE]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_TABLE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_TABLE]->material.kShininess = 8.f;
	meshList[GEO_TABLE]->textureID = LoadTGA("Image//Table_texture.tga");

	//==Border==//
	meshList[GEO_BORDER] = MeshBuilder::GenerateOBJ("border", "OBJ//Border.obj");
	meshList[GEO_BORDER]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BORDER]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BORDER]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BORDER]->material.kShininess = 8.f;
	meshList[GEO_BORDER]->textureID = LoadTGA("Image//Border_texture.tga");

	//==Door==//
	meshList[GEO_DOOR] = MeshBuilder::GenerateOBJ("door", "OBJ//Door.obj");
	meshList[GEO_DOOR]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_DOOR]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_DOOR]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_DOOR]->material.kShininess = 8.f;
	meshList[GEO_DOOR]->textureID = LoadTGA("Image//Door_texture.tga");

	//==Work Table==//
	meshList[GEO_WORK_TABLE] = MeshBuilder::GenerateOBJ("work_table", "OBJ//Work_Table.obj");
	meshList[GEO_WORK_TABLE]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_WORK_TABLE]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_WORK_TABLE]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_WORK_TABLE]->material.kShininess = 8.f;
	meshList[GEO_WORK_TABLE]->textureID = LoadTGA("Image//Work_table_texture.tga");

	//==Bed==//
	meshList[GEO_BED] = MeshBuilder::GenerateOBJ("bed", "OBJ//Bed.obj");
	meshList[GEO_BED]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BED]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BED]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BED]->material.kShininess = 8.f;
	meshList[GEO_BED]->textureID = LoadTGA("Image//bed_texture.tga");

	//==Bed Shelf==//
	meshList[GEO_BED_SHELF] = MeshBuilder::GenerateOBJ("bed_shelf", "OBJ//Bed_shelf.obj");
	meshList[GEO_BED_SHELF]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BED_SHELF]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BED_SHELF]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BED_SHELF]->material.kShininess = 8.f;
	meshList[GEO_BED_SHELF]->textureID = LoadTGA("Image//Bed_shelf_texture.tga");

	//==Chair==//
	meshList[GEO_CHAIR] = MeshBuilder::GenerateOBJ("chair", "OBJ//Chair.obj");
	meshList[GEO_CHAIR]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CHAIR]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_CHAIR]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CHAIR]->material.kShininess = 8.f;
	meshList[GEO_CHAIR]->textureID = LoadTGA("Image//Chair_texture.tga");

	//==Wardrobe Panels==//
	meshList[GEO_WARDROBE_PANEL] = MeshBuilder::GenerateOBJ("Wardrobe_panel", "OBJ//Wardrobe_panel.obj");
	meshList[GEO_WARDROBE_PANEL]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_WARDROBE_PANEL]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_WARDROBE_PANEL]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_WARDROBE_PANEL]->material.kShininess = 8.f;
	meshList[GEO_WARDROBE_PANEL]->textureID = LoadTGA("Image//Wardrobe_panel_texture.tga");

	//==Window==//
	meshList[GEO_WINDOW] = MeshBuilder::GenerateOBJ("Window", "OBJ//Window.obj");
	meshList[GEO_WINDOW]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_WINDOW]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_WINDOW]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_WINDOW]->material.kShininess = 8.f;
	meshList[GEO_WINDOW]->textureID = LoadTGA("Image//Border_texture.tga");

	//==Ceiling==//
	meshList[GEO_CEILING] = MeshBuilder::GenerateOBJ("ceilinglight", "OBJ//Ceiling_light.obj");
	meshList[GEO_CEILING]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CEILING]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_CEILING]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CEILING]->material.kShininess = 8.f;
	meshList[GEO_CEILING]->textureID = LoadTGA("Image//Ceiling_light_texture.tga");

	//==TV==//
	meshList[GEO_TV] = MeshBuilder::GenerateOBJ("TV", "OBJ//Tv.obj");
	meshList[GEO_TV]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_TV]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_TV]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_TV]->material.kShininess = 8.f;
	meshList[GEO_TV]->textureID = LoadTGA("Image//Tele_texture.tga");

	//Text Related
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//CourierNew.tga");
}

bool B_Light = true;
static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;
string result;

//=======META KNIGHT RELATED VARIABLES===========//
int changeRightFeet = 0;
int changeLeftFeet = 0;
int Landing = 0;
bool bShock = false;
bool bShock2 = false;
bool bSkillZ = false;
bool bSkillX = false;

int Moving = 10;

int rotateDir = 1;	 //Rotation direction for feet
int rotateDirHandL = 1; //Rotation direction for Left hand
int rotateDirHandR = 1; //Rotation direction for Right Hand
int rotateDirWings = 1;	//Rotation direction for Wings
int rotateFace = 1;	//Rotation direction for face
int translateHeadDir = 1; //translate direction for head

//============WARDROBE RELATED VARIABLES========//
bool isOpen = false;
bool isClose = false;
bool wMoving = false;

//Show Controls
bool isShown = true;

void StudioProject::Update(double dt)
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

	if(Application::IsKeyPressed('5'))
	{
		B_Light = true;
	}
	if(Application::IsKeyPressed('6'))
	{
		B_Light = false;
	}

	rotateAngle += (float)(10 * dt);

	skyBox.x = camera.position.x - (worldsize/2);
	skyBox.y = camera.position.y - (worldsize/2);
	skyBox.z = camera.position.z - (worldsize/2);

	//Reseting back to original position
	if(Application::IsKeyPressed('R'))
	{
		rotateDir = 1;
		rotateDirHandL = 1;
		rotateDirHandR = 1;
		rotateDirWings = 1;
		rotateFace = 1;

	}
	//===========WardRobe Animation==========//
	//Right to Left
	//Opening
	if(camera.position.x <= 125 && camera.position.z <= -30 && camera.position.x >= 80)
	{
		if(Application::IsKeyPressed('E') && wMoving == false && translateThird > 90)
		{
			isOpen = true;
			Moving = true;
		}
	}
	//Closing
	if(camera.position.x <= 25 && camera.position.z <= -30 && camera.position.x >= -15)
	{
		if(Application::IsKeyPressed('E')&& wMoving == false && translateSecond <= 4)
		{
			isClose = true;
			wMoving = true;
		}
	}
	//To Open
	if(isOpen == true)
	{
		translateThird -= (float)(50*dt);
		if(translateThird <= 50)
		{
			translateSecond -= (float)(50*dt);
		}
		if(translateSecond <= 4)
		{
			isOpen = false;
			wMoving = false;
		}
	}
	// To close
	if(isClose == true)
	{
		translateThird += (float)(50*dt);
		if(translateThird >= 50)
		{
			translateSecond += (float)(50*dt);
		}
		if(translateSecond >= 50)
		{
			isClose = false;
			wMoving = false;
		}
	}

	//=======Window==========//
	if(camera.position.x <= -78 && camera.position.x >= -92 && camera.position.z >= -1 && camera.position.z <= 17)
	{
		//Opening
		if(Application::IsKeyPressed('E') && rotateWindowML < 90)
		{
			rotateWindowML += (float)(50*dt);
			rotateWindowM -= (float)(50*dt);
		}
		//Closing
		if(Application::IsKeyPressed('Q') && rotateWindowML >= 0)
		{
			rotateWindowML -= (float)(50*dt);
			rotateWindowM += (float)(50*dt);
		}
	}

	//===Controls===//

	if(Application::IsKeyPressed('I'))
	{
		isShown = true;
	}

	if(Application::IsKeyPressed('O'))
	{
		isShown = false;
	}
	
	//====Camera===//
	std::ostringstream ss;
	fps = 1/dt;
	ss << fps;
	result = ss.str();

	std::ostringstream ss2;
	ss2 <<camera.position.x;
	camerax = ss2.str();

	std::ostringstream ss3;
	ss3 << camera.position.y;
	cameray = ss3.str();

	std::ostringstream ss4;
	ss4 << camera.position.z;
	cameraz = ss4.str();
	camera.Update(dt);
}

void StudioProject::RenderMetaKnight()
{
	//Head
	modelStack.PushMatrix();
	modelStack.Translate(-80.0f, 18.f, 90.0f);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.Scale(12.f, 12.f, 10.f);
	RenderMesh(meshList[GEO_HEAD], B_Light);

	//HEAD > Right Eye
	modelStack.PushMatrix();
	modelStack.Translate(0.4f, 0.1f, 0.9f);
	modelStack.Rotate(0, 1, 0, 0);
	modelStack.Scale(0.1f, 0.2f, 0.1f);
	RenderMesh(meshList[GEO_EYE], B_Light);
	modelStack.PopMatrix();

	//HEAD > Left Eye
	modelStack.PushMatrix();
	modelStack.Translate(-0.4f, 0.1f, 0.9f);
	modelStack.Rotate(0, 1, 0, 0);
	modelStack.Scale(0.1f, 0.2f, 0.1f);
	RenderMesh(meshList[GEO_EYE], B_Light);
	modelStack.PopMatrix();


	//=========================MASK=======================================//
	//=========================MASK=======================================//
	//=========================MASK=======================================//
	//=========================MASK=======================================//

	//HEAD > Mask 2
	modelStack.PushMatrix();
	modelStack.Translate(0.f, 0.f, 0.57f);
	modelStack.Rotate(0, 1, 0, 0);
	modelStack.PushMatrix();
	modelStack.Scale(0.9f, 0.9f, 0.1f);
	RenderMesh(meshList[GEO_MASK2], B_Light);
	modelStack.PopMatrix(); //pops scale

	//Mask 2 > Top Part of Mask frontside
	modelStack.PushMatrix();
	modelStack.Translate(0.02f, 0.08f, 0.46f);
	modelStack.PushMatrix();
	modelStack.Rotate(-90, 1, 0, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(-22, 0, 1, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(-180, 0, 0, 1);
	modelStack.PushMatrix();
	modelStack.Rotate(-40, 0, 1, 0);
	modelStack.Scale(0.56f, 0.5f, 0.5f);
	RenderMesh(meshList[GEO_TOPPART], B_Light);
	modelStack.PopMatrix(); // pop rotation
	modelStack.PopMatrix(); // pop rotation
	modelStack.PopMatrix(); // pop rotation
	modelStack.PopMatrix(); // pop rotation
	modelStack.PopMatrix();

	//Mask 2 > Btm Part of Mask frontside
	modelStack.PushMatrix();
	modelStack.Translate(0.0f, -0.08f, 0.46f);
	modelStack.PushMatrix();
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(10, 0, 1, 0);
	modelStack.Scale(0.58f, 0.3f, 0.58f);
	RenderMesh(meshList[GEO_BTMPART], B_Light);
	modelStack.PopMatrix(); // pop rotation
	modelStack.PopMatrix(); // pop rotation
	modelStack.PopMatrix(); // Mask 2

	//Mask 2 > Mask Cover
	modelStack.PushMatrix();
	modelStack.Translate(0.0f, 0.0f, 0.0f);
	modelStack.Rotate(0, 1, 0, 0);
	modelStack.Scale(0.6f, 0.6f, 1.2f);
	RenderMesh(meshList[GEO_COVER], B_Light);
	modelStack.PopMatrix(); // Mask 2

	// Mask 2 > Left outer spike
	modelStack.PushMatrix();
	modelStack.Translate(-0.5f, 0.65f, 0.2f);
	modelStack.Rotate(120, 1, 0, 0);
	modelStack.Scale(0.1f, 0.4f, 0.1f);
	RenderMesh(meshList[GEO_MASKSPIKE], B_Light);
	modelStack.PopMatrix(); // Mask 2

	//Mask 2 > Left Inner Spike
	modelStack.PushMatrix();
	modelStack.Translate(-0.3f, 0.75f, 0.2f);
	modelStack.Rotate(120, 1, 0, 0);
	modelStack.Scale(0.1f, 0.4f, 0.1f);
	RenderMesh(meshList[GEO_MASKSPIKE], B_Light);
	modelStack.PopMatrix(); // Mask 2

	//Mask 2 > Right Inner Spike
	modelStack.PushMatrix();
	modelStack.Translate(0.3f, 0.75f, 0.2f);
	modelStack.Rotate(120, 1, 0, 0);
	modelStack.Scale(0.1f, 0.4f, 0.1f);
	RenderMesh(meshList[GEO_MASKSPIKE], B_Light);
	modelStack.PopMatrix(); // Mask 2

	//Mask 2 > Right Outer Spike
	modelStack.PushMatrix();
	modelStack.Translate(0.5f, 0.65f, 0.2f);
	modelStack.Rotate(120, 1, 0, 0);
	modelStack.Scale(0.1f, 0.4f, 0.1f);
	RenderMesh(meshList[GEO_MASKSPIKE], B_Light);
	modelStack.PopMatrix(); // Mask 2
	modelStack.PopMatrix(); // Head

	//=========================MASK=======================================//
	//=========================MASK=======================================//
	//=========================MASK=======================================//
	//=========================MASK=======================================//

	//HEAD > Right Feet
	modelStack.PushMatrix();
	modelStack.Translate(0.4f, -1.4f, translateRightFeet);
	modelStack.Rotate(rotateRightFeet, 1, 0, 0);
	modelStack.Scale(0.4f, 0.6f, 0.6f);
	RenderMesh(meshList[GEO_FEET], B_Light);
	modelStack.PopMatrix();

	//HEAD > Left Feet
	modelStack.PushMatrix();
	modelStack.Translate(-0.4f, -1.4f, translateLeftFeet);
	modelStack.Rotate(-rotateLeftFeet, 1, 0, 0);
	modelStack.Scale(0.4f, 0.6f, 0.6f);
	RenderMesh(meshList[GEO_FEET], B_Light);
	modelStack.PopMatrix();

}

void StudioProject::RenderWings()
{
	//===============================RIGHT WING========================================//
	//===============================RIGHT WING========================================//
	//===============================RIGHT WING========================================//

	//Head > Base for Right Wing
	modelStack.PushMatrix();
	modelStack.Translate(0.f, 0.f, 0.f);
	modelStack.Rotate(rotateWings, 0, 0, 1);
	modelStack.Scale(1.f, 1.f, 1.f);
	RenderMesh(meshList[GEO_HEAD], B_Light);

	//Base for Right Wing> Right Wing Skele
	modelStack.PushMatrix();
	modelStack.Translate(0.5f, 0.6f, -0.7f);
	modelStack.Rotate(-45, 0, 1, 1);
	modelStack.Scale(0.1f, 1.6f, 0.1f);
	RenderMesh(meshList[GEO_WINGBASE], B_Light);
	modelStack.PopMatrix();

	// Base for Right Wing > Right Mid Wing Sphere
	modelStack.PushMatrix();
	modelStack.Translate(0.97f, 1.4f, -0.55f);
	modelStack.Rotate(-85, 0, 0, 1);
	modelStack.Scale(0.1f, 0.1f, 0.1f);
	RenderMesh(meshList[GEO_WINGSPHERE], B_Light);

	//Mid Wing Sphere  > Part 2 Skele
	modelStack.PushMatrix();
	modelStack.Translate(0.0f, 6.1f, 0.0f);
	modelStack.Rotate(-55, 0, 1, 0);
	modelStack.Scale(1.0f, 15.0f, 1.0f);
	RenderMesh(meshList[GEO_WINGBASE], B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Base for Right Wing > Middle Right Wing Spike
	modelStack.PushMatrix();
	modelStack.Translate(0.75f, 1.6f, -0.55f);
	modelStack.Rotate(45, 0, 0, 1);
	modelStack.Scale(0.09f, 0.5f, 0.09f);
	RenderMesh(meshList[GEO_WINGSPIKE], B_Light);
	modelStack.PopMatrix();

	//Base for Right Wing > Right Outer Wing Sphere
	modelStack.PushMatrix();
	modelStack.Translate(2.4f, 1.53f, -0.55f);
	modelStack.Rotate(0, 0, 0, 1);
	modelStack.Scale(0.1f, 0.1f, 0.1f);
	RenderMesh(meshList[GEO_WINGSPHERE], B_Light);

	//Right Outer Wing Sphere > Outer Wing Skele
	modelStack.PushMatrix();
	modelStack.Translate(6.1f, -5.2f, 0.0f);
	modelStack.Rotate(-130, 0, 0, 1);
	modelStack.Scale(1.f, 15.f, 1.0f);
	RenderMesh(meshList[GEO_WINGSKELE], B_Light);
	modelStack.PopMatrix();

	//Right Outer Wing Sphere > Middle Wing Skele
	modelStack.PushMatrix();
	modelStack.Translate(-4.3f, -7.5f, 0.0f);
	modelStack.Rotate(-150, 0, 0, 1);
	modelStack.Scale(1.f, 15.f, 1.0f);
	RenderMesh(meshList[GEO_WINGSKELE], B_Light);
	modelStack.PopMatrix();

	//Right Outer Wing Sphere > Inner Wing Skele
	modelStack.PushMatrix();
	modelStack.Translate(-11.3f, -8.7f, 0.0f);
	modelStack.Rotate(-160, 0, 0, 1);
	modelStack.Scale(1.f, 15.f, 1.0f);
	RenderMesh(meshList[GEO_WINGSKELE], B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Base for Right Wing > Outer Right Wing Spike
	modelStack.PushMatrix();
	modelStack.Translate(2.6f, 1.7f, -0.55f);
	modelStack.Rotate(-45, 0, 0, 1);
	modelStack.Scale(0.09f, 0.5f, 0.09f);
	RenderMesh(meshList[GEO_WINGSPIKE], B_Light);
	modelStack.PopMatrix();

	//Base for Right Wing > Right Inner Wing Content Front Side
	modelStack.PushMatrix();
	modelStack.Translate(0.8f, 0.6f, -0.65f);
	modelStack.Rotate(5, 1, 0, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(-10,0,1,0);
	modelStack.PushMatrix();
	modelStack.Rotate(-30, 0, 0, 1);
	modelStack.Scale(0.65f, 1.4f, 0.65f);
	RenderMesh(meshList[GEO_WINGCONTENT], B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Base for Right Wing > Right Middle Wing Content Front Side
	modelStack.PushMatrix();
	modelStack.Translate(1.7f, 1.0f, -0.55f);
	modelStack.Rotate(-85, 0, 0, 1);
	modelStack.Scale(0.9f, 1.4f, 0.9f);
	RenderMesh(meshList[GEO_WINGCONTENT], B_Light);
	modelStack.PopMatrix();

	//Base for Right Wing > Right Outer Wing Content Front Side
	modelStack.PushMatrix();
	modelStack.Translate(2.4f, 1.1f, -0.55f);
	modelStack.Rotate(48, 0, 0, 1);
	modelStack.Scale(0.7f, 0.7f, 0.7f);
	RenderMesh(meshList[GEO_WINGCONTENT], B_Light);
	modelStack.PopMatrix();

	modelStack.PopMatrix();// Back to Head

	//===============================LEFT WING========================================//
	//===============================LEFT WING========================================//
	//===============================LEFT WING========================================//

	//Head > Base for Left Wing
	modelStack.PushMatrix();
	modelStack.Translate(0.f, 0.f, 0.f);
	modelStack.Rotate(-rotateWings, 0, 0, 1);
	modelStack.Scale(1.f, 1.f, 1.f);
	RenderMesh(meshList[GEO_HEAD], B_Light);

	//Base for Left Wing > Left Wing Skele
	modelStack.PushMatrix();
	modelStack.Translate(-0.5f, 0.6f, -0.7f);
	modelStack.Rotate(45, 0, 1, 1);
	modelStack.Scale(0.1f, 1.6f, 0.1f);
	RenderMesh(meshList[GEO_WINGBASE], B_Light);
	modelStack.PopMatrix();

	// Base for Left Wing >  Left Mid Wing Sphere
	modelStack.PushMatrix();
	modelStack.Translate(-0.97f, 1.4f, -0.55f);
	modelStack.Rotate(85, 0, 0, 1);
	modelStack.Scale(0.1f, 0.1f, 0.1f);
	RenderMesh(meshList[GEO_WINGSPHERE], B_Light);

	//Mid Wing Sphere  > Part 2 Skele
	modelStack.PushMatrix();
	modelStack.Translate(0.0f, 6.1f, 0.0f);
	modelStack.Rotate(-45, 0, 1, 0);
	modelStack.Scale(1.0f, 15.0f, 1.0f);
	RenderMesh(meshList[GEO_WINGBASE], B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Base for Left Wing > Left Wing Spike
	modelStack.PushMatrix();
	modelStack.Translate(-0.75f, 1.6f, -0.55f);
	modelStack.Rotate(-45, 0, 0, 1);
	modelStack.Scale(0.09f, 0.5f, 0.09f);
	RenderMesh(meshList[GEO_WINGSPIKE], B_Light);
	modelStack.PopMatrix();

	//Base for Left Wing > Left Outer Wing Sphere
	modelStack.PushMatrix();
	modelStack.Translate(-2.4f, 1.53f, -0.55f);
	modelStack.Rotate(0, 0, 0, 1);
	modelStack.Scale(0.1f, 0.1f, 0.1f);
	RenderMesh(meshList[GEO_WINGSPHERE], B_Light);

	//Left Outer Wing Sphere > Left Outer Wing Skele
	modelStack.PushMatrix();
	modelStack.Translate(-6.1f, -5.2f, 0.0f);
	modelStack.Rotate(130, 0, 0, 1);
	modelStack.Scale(1.f, 15.f, 1.0f);
	RenderMesh(meshList[GEO_WINGSKELE], B_Light);
	modelStack.PopMatrix();

	//Left Outer Wing Sphere > Left Middle Wing Skele
	modelStack.PushMatrix();
	modelStack.Translate(4.3f, -7.5f, 0.0f);
	modelStack.Rotate(150, 0, 0, 1);
	modelStack.Scale(1.f, 15.f, 1.0f);
	RenderMesh(meshList[GEO_WINGSKELE], B_Light);
	modelStack.PopMatrix();

	//Left Outer Wing Sphere > Left Inner Wing Skele
	modelStack.PushMatrix();
	modelStack.Translate(11.3f, -8.7f, 0.0f);
	modelStack.Rotate(160, 0, 0, 1);
	modelStack.Scale(1.f, 15.f, 1.0f);
	RenderMesh(meshList[GEO_WINGSKELE], B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Base for Left Wing > Outer Left Wing Spike
	modelStack.PushMatrix();
	modelStack.Translate(-2.6f, 1.7f, -0.55f);
	modelStack.Rotate(45, 0, 0, 1);
	modelStack.Scale(0.09f, 0.5f, 0.09f);
	RenderMesh(meshList[GEO_WINGSPIKE], B_Light);
	modelStack.PopMatrix();

	//Base for Left Wing > Left Inner Wing Content Front Side
	modelStack.PushMatrix();
	modelStack.Translate(-0.8f, 0.6f, -0.65f);
	modelStack.Rotate(5, 1, 0, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(10,0,1,0);
	modelStack.PushMatrix();
	modelStack.Rotate(30, 0, 0, 1);
	modelStack.Scale(0.65f, 1.4f, 0.65f);
	RenderMesh(meshList[GEO_WINGCONTENT], B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Base for Left Wing > Left Middle Wing Content Front Side
	modelStack.PushMatrix();
	modelStack.Translate(-1.7f, 1.0f, -0.55f);
	modelStack.Rotate(85, 0, 0, 1);
	modelStack.Scale(0.9f, 1.4f, 0.9f);
	RenderMesh(meshList[GEO_WINGCONTENT], B_Light);
	modelStack.PopMatrix();

	//Base for Left Wing > Left Outer Wing Content Front Side
	modelStack.PushMatrix();
	modelStack.Translate(-2.4f, 1.1f, -0.55f);
	modelStack.Rotate(-48, 0, 0, 1);
	modelStack.Scale(0.7f, 0.7f, 0.7f);
	RenderMesh(meshList[GEO_WINGCONTENT], B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix(); // Back to Head
}

void StudioProject::RenderArms()
{
	//HEAD > Right Shoulder pad
	modelStack.PushMatrix();
	modelStack.Translate(1.0f, 0.f, 0.1f);
	modelStack.Rotate(rotateRightArm, 1, 0, 0);
	modelStack.Scale(0.35f, 0.35f, 0.35f);
	RenderMesh(meshList[GEO_SHOULDER], B_Light);

	//Right Shoulder pad > Ring
	modelStack.PushMatrix();
	modelStack.Translate(0.5f, -0.6f, 0.0f);
	modelStack.Rotate(35, 0, 0, 1);
	modelStack.Scale(0.8f, 0.2f, 0.8f);
	RenderMesh(meshList[GEO_SHOULDERRING], B_Light);
	modelStack.PopMatrix();

	//Right Shoulder pad > Hand
	modelStack.PushMatrix();
	modelStack.Translate(0.6f, -0.85f, 0.0f);
	modelStack.Rotate(0, 0, 0, 1);
	modelStack.Scale(0.7f, 0.8f, 0.7f);
	RenderMesh(meshList[GEO_HAND], B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//HEAD > Left Shoulder pad
	modelStack.PushMatrix();
	modelStack.Translate(-1.0f, 0.f, 0.1f);
	modelStack.Rotate(-rotateLeftArm, 1, 0, 0);
	modelStack.Scale(0.35f, 0.35f, 0.35f);
	RenderMesh(meshList[GEO_SHOULDER], B_Light);

	//Left Shoulder pad > Ring
	modelStack.PushMatrix();
	modelStack.Translate(-0.5f, -0.6f, 0.0f);
	modelStack.Rotate(-35, 0, 0, 1);
	modelStack.Scale(0.8f, 0.2f, 0.8f);
	RenderMesh(meshList[GEO_SHOULDERRING], B_Light);
	modelStack.PopMatrix();

	//Left Shoulder pad >  Hand
	modelStack.PushMatrix();
	modelStack.Translate(-0.6f, -0.85f, 0.0f);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(0.7f, 0.8f, 0.7f);
	RenderMesh(meshList[GEO_HAND], B_Light);
}

void StudioProject::RenderSword()
{
	//Hand > Sword Handle
	modelStack.PushMatrix();
	modelStack.Translate(-1.9f, -55.f, 0.f);
	modelStack.PushMatrix();
	modelStack.Rotate(80, 1, 0, 0);
	modelStack.PushMatrix();
	modelStack.Scale(0.25f, 2.2f, 0.25f);
	RenderMesh(meshList[GEO_SWORDHANDLE], B_Light);
	modelStack.PopMatrix(); //Pop sword hilt rotation
	modelStack.PopMatrix(); // Pop sword hilt scaling

	//Handle > Btm Sword Sphere
	modelStack.PushMatrix();
	modelStack.Translate(0.0f, -0.15f, -0.8f);
	modelStack.Rotate(0, 1, 0, 0);
	modelStack.Scale(0.4f, 0.3f, 0.4f);
	RenderMesh(meshList[GEO_SWORDSPHERE], B_Light);
	modelStack.PopMatrix(); // to Handle

	//Handle > Top Sword Sphere
	modelStack.PushMatrix();
	modelStack.Translate(0.0f, 0.25f, 1.5f);
	modelStack.Rotate(0, 1, 0, 0);
	modelStack.Scale(0.5f, 0.4f, 0.5f);
	RenderMesh(meshList[GEO_SWORDSPHERE2], B_Light);

	//Top Sword Sphere > Right Part Hilt
	modelStack.PushMatrix();
	modelStack.Translate(0.0f, 1.7f, 0.0f);
	modelStack.Rotate(0, 0, 0, 1);
	modelStack.Scale(0.8f, 2.7f, 0.8f);
	RenderMesh(meshList[GEO_SWORDHILT], B_Light);
	modelStack.PopMatrix(); // To Sphere

	//Top Sword Sphere > Left Part Hilt
	modelStack.PushMatrix();
	modelStack.Translate(0.0f, -1.7f, 0.0f);
	modelStack.Rotate(180, 0, 0, 1);
	modelStack.Scale(0.8f, 2.7f, 0.8f);
	RenderMesh(meshList[GEO_SWORDHILT], B_Light);
	modelStack.PopMatrix(); // To Sphere

	//=================Blade=========================//
	//=================Blade=========================//
	//=================Blade=========================//
	//=================Blade=========================//

	//Top Sword Sphere >  Sword Blade
	modelStack.PushMatrix();
	modelStack.Translate(0.0f, 0.0f, 0.0f);
	modelStack.PushMatrix();
	modelStack.Rotate(-10, 1, 0, 0);
	modelStack.PushMatrix();
	modelStack.Scale(0.5f, 1.9f, 17.0f);
	RenderMesh(meshList[GEO_SWORDBLADE], B_Light);
	modelStack.PopMatrix();//pop Scaling
	modelStack.PopMatrix();//pop rotation

	modelStack.PopMatrix(); // To Blade
	modelStack.PopMatrix(); // To Sphere

	modelStack.PopMatrix(); //To Handle
	modelStack.PopMatrix(); // To Hand

	modelStack.PopMatrix(); // Back to Shoulder Pad
	//============Shock Wave======================//
	//============Shock Wave======================//
	//============Shock Wave======================//

	//Top Sword Sphere >  Shockwave
	modelStack.PushMatrix();
	modelStack.Translate(-1.2f, -0.3f, translateShock);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(0.3f, scaleShock, 17.0f);
	if(bShock == true)
	{
		RenderMesh(meshList[GEO_SHOCKWAVE], B_Light);
	}
	modelStack.PopMatrix(); // Back to Sphere

	//Top Sword Sphere >  Shockwave
	modelStack.PushMatrix();
	modelStack.Translate(-1.2f, -0.3f, translateShock2);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(scaleShock2, scaleShock2, scaleShock2);
	if(bShock2 == true)
	{
		RenderMesh(meshList[GEO_SHOCKWAVE2], B_Light);
	}
	modelStack.PopMatrix(); // Back to Sphere
	modelStack.PopMatrix(); // Back to Head
}

void StudioProject::RenderSkybox()
{
	//Back
	modelStack.PushMatrix();
	modelStack.Translate(0.f, 0.f, (worldsize/2) - 1);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(worldsize, worldsize, worldsize);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();

	//Front
	modelStack.PushMatrix();
	modelStack.Translate(0.f, 0.f, (-worldsize/2) + 1);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(-180, 1, 0, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(-180, 0, 0, 1);
	modelStack.Scale(worldsize, worldsize, worldsize);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Top
	modelStack.PushMatrix();
	modelStack.Translate(0.f, (worldsize/2) - 1, 0.f);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(270, 0, 0, 1);
	modelStack.Scale(worldsize, worldsize, worldsize);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Bottom
	modelStack.PushMatrix();
	modelStack.Translate(0.f, (-worldsize/2) + 1, 0.f);
	modelStack.Rotate(90,1,0,0);
	modelStack.Scale(worldsize, worldsize, worldsize);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();

	//RIGHT
	modelStack.PushMatrix();
	modelStack.Translate((worldsize/2) - 1, 0.f, 0.f);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(-180, 0, 1, 0);
	modelStack.Scale(worldsize, worldsize, worldsize);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//LEFT
	modelStack.PushMatrix();
	modelStack.Translate((-worldsize/2) + 1, 0.f, 0.f);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(worldsize, worldsize, worldsize);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void StudioProject::RenderRoom()
{
	//Back
	modelStack.PushMatrix();
	modelStack.Translate(0.f,(roomheight/2)-10, roomsize/2);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(roomsize, roomheight, roomsize);
	RenderMesh(meshList[GEO_RBACK], false);
	modelStack.PopMatrix();

	//Front
	modelStack.PushMatrix();
	modelStack.Translate(0.f, (roomheight/2)-10, -roomsize/2);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(-180, 1, 0, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(-180, 0, 0, 1);
	modelStack.Scale(roomsize, roomheight, roomsize);
	RenderMesh(meshList[GEO_RFRONT], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Top
	modelStack.PushMatrix();
	modelStack.Translate(0.f, (roomsize/2) + 15, 0.f);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(270, 0, 0, 1);
	modelStack.Scale(roomsize, roomsize, roomsize);
	RenderMesh(meshList[GEO_RTOP], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Bottom
	modelStack.PushMatrix();
	modelStack.Translate(0.f, -10, 0.f);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Scale(roomsize, roomsize, roomsize);
	RenderMesh(meshList[GEO_RBOTTOM], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//RIGHT
	modelStack.PushMatrix();
	modelStack.Translate(roomsize/2, (roomheight/2)-10, 0.f);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(-180, 0, 1, 0);
	modelStack.Scale(roomsize, roomheight, roomsize);
	RenderMesh(meshList[GEO_RRIGHT], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//LEFT
	modelStack.PushMatrix();
	modelStack.Translate(-roomsize/2, (roomheight/2)-10, 0.f);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(roomsize, roomheight, roomsize);
	RenderMesh(meshList[GEO_RLEFT], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
}

void StudioProject::RenderRoomContents()
{
	//Sofa
	modelStack.PushMatrix();
	modelStack.Translate(110.f, -10.f, 80.f);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(10.f, 10.f, 10.f);
	RenderMesh(meshList[GEO_SOFA], B_Light);
	modelStack.PopMatrix();

	//Wardrobe
	modelStack.PushMatrix();
	modelStack.Translate(50.f, 28.1f, -124.f);
	modelStack.Rotate(0, 1, 0, 0);
	modelStack.Scale(10.f, 12.f, 10.f);
	RenderMesh(meshList[GEO_WARDROBE], B_Light);
	modelStack.PopMatrix();

	//Border
	modelStack.PushMatrix();
	modelStack.Translate(5.f, 14.3f, 79.5f);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(7.5f, 8.f, 5.f);
	RenderMesh(meshList[GEO_BORDER], B_Light);
	modelStack.PopMatrix();

	//Wardrobe Panels
	//First
	modelStack.PushMatrix();
	modelStack.Translate(5.f, 28.1f, -87.5f);
	modelStack.Rotate(0, 1, 0, 0);
	modelStack.Scale(10.f, 12.f, 10.f);
	RenderMesh(meshList[GEO_WARDROBE_PANEL], B_Light);
	modelStack.PopMatrix();

	//Second
	modelStack.PushMatrix();
	modelStack.Translate(translateSecond, 28.1f, -86.5f);
	modelStack.Rotate(0, 1, 0, 0);
	modelStack.Scale(10.f, 12.f, 10.f);
	RenderMesh(meshList[GEO_WARDROBE_PANEL], B_Light);
	modelStack.PopMatrix();

	//Third
	modelStack.PushMatrix();
	modelStack.Translate(translateThird, 28.1f, -85.5f);
	modelStack.Rotate(0, 1, 0, 0);
	modelStack.Scale(10.f, 12.f, 10.f);
	RenderMesh(meshList[GEO_WARDROBE_PANEL], B_Light);
	modelStack.PopMatrix();
	//END

	//Table
	modelStack.PushMatrix();
	modelStack.Translate(65.f, -5.f, 80.f);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10.f, 10.f, 10.f);
	RenderMesh(meshList[GEO_TABLE], B_Light);
	modelStack.PopMatrix();

	//Work Table
	modelStack.PushMatrix();
	modelStack.Translate(-74.4f, 19.f, -105.f);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(11.3f, 11.f, 11.f);
	RenderMesh(meshList[GEO_WORK_TABLE], B_Light);
	modelStack.PopMatrix();

	//Chair
	modelStack.PushMatrix();
	modelStack.Translate(-74.45, 5.6f, -80.f);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(9.f, 9.f, 9.f);
	RenderMesh(meshList[GEO_CHAIR], B_Light);
	modelStack.PopMatrix();

	//Bed
	modelStack.PushMatrix();
	modelStack.Translate(-80.f, -0.3f, 85.f);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(12.f, 12.f, 12.f);
	RenderMesh(meshList[GEO_BED], B_Light);
	modelStack.PopMatrix();

	//Door
	modelStack.PushMatrix();
	modelStack.Translate(127.f, 18.7f, -60.f);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(10.f, 10.f, 7.f);
	RenderMesh(meshList[GEO_DOOR], B_Light);
	modelStack.PopMatrix();

	//Bed Shelf
	modelStack.PushMatrix();
	modelStack.Translate(-38.f, 4.2f, 123.5f);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(8.f, 8.f, 8.f);
	RenderMesh(meshList[GEO_BED_SHELF], B_Light);
	modelStack.PopMatrix();

	//============Window========//
	//============Window========//
	//============Window========//
	//Most Left
	modelStack.PushMatrix();
	modelStack.Translate(-123.f, 36.5f, 35.5f);
	modelStack.Rotate(180, 1, 0, 0);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(rotateWindowML, 0, 1, 0);
	modelStack.Scale(8.3f, 7.f, 8.f);
	modelStack.PushMatrix();
	modelStack.Translate(-1.6f, 0.f, 0.f);
	RenderMesh(meshList[GEO_WINDOW], B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Middle
	modelStack.PushMatrix();
	modelStack.Translate(-123.f, 36.5f, -18.3f);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Rotate(-rotateWindowM, 0, 1, 0);
	modelStack.Scale(8.3f, 7.f, 8.f);
	modelStack.PushMatrix();
	modelStack.Translate(-1.5f, 0.f, 0.0f);
	RenderMesh(meshList[GEO_WINDOW], B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Right
	modelStack.PushMatrix();
	modelStack.Translate(-123.f, 36.5f, -34.f);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(8.3f, 7.f, 8.f);
	RenderMesh(meshList[GEO_WINDOW], B_Light);
	modelStack.PopMatrix();
	//End 

	//Ceiling light
	modelStack.PushMatrix();
	modelStack.Translate(0.f, roomheight -12, 0.f);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10.f, 6.f, 10.f);
	RenderMesh(meshList[GEO_CEILING], B_Light);
	modelStack.PopMatrix();

	//TV
	modelStack.PushMatrix();
	modelStack.Translate(13.f, 17.5f, 80.f);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.Scale(10.f, 10.f, 10.f);
	RenderMesh(meshList[GEO_TV], B_Light);
	modelStack.PopMatrix();
}

void StudioProject::Render()
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

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	RenderMesh(meshList[GEO_AXES], false);

	//Rendering skybox
	modelStack.PushMatrix();
	modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);
	RenderSkybox();
	modelStack.PopMatrix();
	//Rendering Room
	RenderRoom();

	//Rendering Room Contents
	RenderRoomContents();

	//======META KNIGHT RELATED RENDERING====//
	RenderMetaKnight();
	RenderArms();
	RenderSword();


	//=====Text Related Rendering============//
	//RenderTextOnScreen(meshList[GEO_TEXT], Framerate + result, Color(0, 1, 0), 3, 1, 2);
	//RenderTextOnScreen(meshList[GEO_TEXT], camerax, Color(0, 1, 0), 3, 1, 3);
	//RenderTextOnScreen(meshList[GEO_TEXT], cameray, Color(0, 1, 0), 3, 1, 4);
	//RenderTextOnScreen(meshList[GEO_TEXT], cameraz, Color(0, 1, 0), 3, 1, 5);
	
	//==Controls==//
	if(isShown == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "WASD to Move", Color(0, 0 ,0), 2, 1, 29);
		RenderTextOnScreen(meshList[GEO_TEXT], "Arrow Keys to View", Color(0, 0, 0), 2, 1, 28);
		RenderTextOnScreen(meshList[GEO_TEXT], "'E' to Interact", Color(0, 0, 0), 2, 1, 27);
		RenderTextOnScreen(meshList[GEO_TEXT], "'I' to Reopen", Color(0, 0, 0), 2, 1, 26);
		RenderTextOnScreen(meshList[GEO_TEXT], "'O' to Close", Color(0, 0, 0), 2, 1, 25);
	}

	//===Wardrobe===//
	if((camera.position.x <= 125 && camera.position.z <= -30 && camera.position.x >= 80 && translateThird > 90) ||(camera.position.x <= 25 && camera.position.z <= -30 && camera.position.x >= -15 && translateSecond <= 4) )
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "'E' to interact", Color(1, 1, 1), 3, 8, 7);
	}

	//====Window===//
	if(camera.position.x <= -78 && camera.position.x >= -92 && camera.position.z >= -1 && camera.position.z <= 17)
	{
		RenderTextOnScreen(meshList[GEO_TEXT], "'E' to open", Color(1, 1, 1), 3, 8, 7);
		RenderTextOnScreen(meshList[GEO_TEXT], "'Q' to Close", Color(1, 1, 1), 3, 8, 6);
	}
}

void StudioProject::RenderMesh(Mesh *mesh, bool enableLight)
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

void StudioProject::RenderText(Mesh* mesh, std::string text, Color color)
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

void StudioProject::RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y)
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

void StudioProject::Exit()
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
