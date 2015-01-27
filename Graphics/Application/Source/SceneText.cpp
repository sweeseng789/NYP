#include "SceneText.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"
#include "Utility.h"

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
	m_programID = LoadShaders( "Shader//Texture.vertexshader", "Shader//Blending.fragmentshader" );
	m_programID = LoadShaders( "Shader//Texture.vertexshader", "Shader//Texture.fragmentshader" );
	m_programID = LoadShaders( "Shader//Texture.vertexshader", "Shader//Text.fragmentshader" );
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

	glUseProgram(m_programID);

	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_NUMLIGHTS], 1);


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
	scaleSize = 1000;
	moving = 0;
	FPS = 0;

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
	camera.Init(Vector3(0, 0, 50), Vector3(0, 0, 0), Vector3(0, 1, 0));

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
	meshList[GEO_FRONT]->textureID = LoadTGA("Image//front.tga");

	meshList[GEO_BACK] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f);
	meshList[GEO_BACK]->textureID = LoadTGA("Image//back.tga");

	meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f);
	meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//bottom.tga");

	meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f);
	meshList[GEO_TOP]->textureID = LoadTGA("Image//top.tga");

	meshList[GEO_RIGHT] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f);
	meshList[GEO_RIGHT]->textureID = LoadTGA("Image//right.tga");

	meshList[GEO_LEFT] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f);
	meshList[GEO_LEFT]->textureID = LoadTGA("Image//left.tga");

	meshList[GEO_EXIA] = MeshBuilder::GenerateQuad("exia", Color(1, 1, 1), 1.f);
	meshList[GEO_EXIA]->textureID = LoadTGA("Image//Exia.tga");

	/*meshList[GEO_MODEL1] = MeshBuilder::GenerateOBJ("model1", "OBJ//chair.obj");
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

	meshList[GEO_CHAIRSS] = MeshBuilder::GenerateOBJ("model6", "OBJ//ChairSS.obj");
	meshList[GEO_CHAIRSS]->textureID = LoadTGA("Image//ChairSS.tga");*/

	meshList[GEO_CROSSHAIR] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f);
	meshList[GEO_CROSSHAIR]->textureID = LoadTGA("Image//Crosshair.tga");

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

	if (Application::IsKeyPressed('9'))
		moving += (float)(1000 * dt);
	if (Application::IsKeyPressed('8'))
		moving -= (float)(1000 * dt);

	FPS = 1/dt;

	renderFPS = "FPS: " + std::to_string((long double) FPS); 



	camera.Update(dt);
}

void SceneText::RenderSkybox()
{
	modelStack.PushMatrix();
	modelStack.Scale(scaleSize, scaleSize, scaleSize);
	RenderMesh(meshList[GEO_FRONT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(scaleSize, scaleSize, scaleSize);
	modelStack.Rotate(90, 0, -90, 0);
	modelStack.Translate(-0.49814095, 0, 0.49649683);
	RenderMesh(meshList[GEO_LEFT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(scaleSize, scaleSize, scaleSize);
	modelStack.Rotate(90, 0, 180, 0);
	modelStack.Translate(0.498585 , 0, 0.49649683);
	RenderMesh(meshList[GEO_RIGHT], false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(180, 0, 180, 0);
	modelStack.PushMatrix();
	modelStack.Scale(scaleSize, scaleSize, scaleSize);
	modelStack.Translate(0, 0, 0.991158);
	RenderMesh(meshList[GEO_BACK], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();


	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, 90, 0);
	modelStack.PushMatrix();
	modelStack.Scale(scaleSize, scaleSize, scaleSize);
	modelStack.Rotate(270, 270, 0, 0);
	modelStack.Translate(0.491462 + 0.00678009, 0, 0.499845 -0.00340081);
	RenderMesh(meshList[GEO_TOP], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//modelStack.Scale(scaleSize, scaleSize, scaleSize);
	//modelStack.Rotate(90, 90, 0, 0);
	//modelStack.Translate(0, moving, 0.503292);
	//RenderMesh(meshList[GEO_BOTTOM], false);
	//modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, 90, 0);
	modelStack.PushMatrix();
	modelStack.Scale(scaleSize, scaleSize, scaleSize);
	modelStack.Rotate(270, 270, 0, 0);
	modelStack.Translate(0.49824209, 0, -0.49644419);
	RenderMesh(meshList[GEO_BOTTOM], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
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

void SceneText::Render()
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
	modelStack.Scale(20, 20 ,20);
	modelStack.Translate(0, 0, 100);
	RenderSkybox();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//scale, translate, rotate
	modelStack.Scale(10, 10, 10);
	//RenderText(meshList[GEO_TEXT], "Bao Yin", Color(0, 0, 0));
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	RenderMesh(meshList[GEO_CROSSHAIR], false);
	modelStack.PopMatrix();

	RenderTextOnScreen(meshList[GEO_TEXT], renderFPS, Color(0, 1, 0), 5, 1, 1);
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
