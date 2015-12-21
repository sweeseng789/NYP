#include "SceneMenu.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>

SceneMenu::SceneMenu(void):
	m_window_width(800)
	, m_window_height(600)
{
}

SceneMenu::SceneMenu(const int m_window_width, const int m_window_height) :
	m_cAvatar(NULL),
	textList(NULL)
{
	this->m_window_width = m_window_width;
	this->m_window_height = m_window_height;
}

SceneMenu::~SceneMenu(void)
{
	if (m_cAvatar)
	{
		delete m_cAvatar;
		m_cAvatar = NULL;
	}
}


void SceneMenu::InitShaders()
{
	// Blue background
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

	m_programID = LoadShaders("Shader//Texture.vertexshader", "Shader//Text.fragmentshader");

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
	m_parameters[U_COLOR_TEXTURE_ENABLED] = glGetUniformLocation(m_programID, "colorTextureEnabled[0]");
	m_parameters[U_COLOR_TEXTURE_ENABLED1] = glGetUniformLocation(m_programID, "colorTextureEnabled[1]");
	m_parameters[U_COLOR_TEXTURE] = glGetUniformLocation(m_programID, "colorTexture[0]");
	m_parameters[U_COLOR_TEXTURE1] = glGetUniformLocation(m_programID, "colorTexture[1]");
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
}

void SceneMenu::InitMesh()
{
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference");//, 1000, 1000, 1000);
	meshList[GEO_CROSSHAIR] = MeshBuilder::GenerateCrossHair("crosshair");
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID[0] = LoadTGA("Image//calibri.tga");
	meshList[GEO_TEXT]->material.kAmbient.Set(1, 0, 0);
	//meshList[GEO_OBJECT] = MeshBuilder::GenerateOBJ("OBJ1", "OBJ//Unicorn_Arm.obj");//MeshBuilder::GenerateCube("cube", 1);
	//meshList[GEO_OBJECT]->textureID = LoadTGA("Image//Unicorn_Gundam//Unicorn_Arm.tga");
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateSphere("lightball", Color(1, 0, 0), 18, 36, 1.f);
	//meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube", 1, 1, 1);
	//meshList[GEO_TORUS] = MeshBuilder::GenerateCylinder("torus", 36, 36, 5, 1);
	meshList[GEO_WALLPAPER] = MeshBuilder::GenerateQuad("Wallpaper", Color(1, 1, 1), 1.f);
	meshList[GEO_WALLPAPER]->textureID[0] = LoadTGA("Image//Wallpaper//Background.tga");

	meshList[GEO_LOGO] = MeshBuilder::GenerateQuad("Wallpaper", Color(1, 1, 1), 1.f);
	meshList[GEO_LOGO]->textureID[0] = LoadTGA("Image//Wallpaper//GundamUnicorn_Logo.tga");
}

void SceneMenu::Init()
{
	InitShaders();

	InitMesh();

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 1000 units
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	rotateAngle = 0;

	mousePos.SetZero();

	bLightEnabled = true;

	m_cAvatar = new CPlayInfo3PV();
	m_cAvatar->setPos(Vector3(15, -15, -70));

	currentMenuState = E_MENU;
	previousMenuState = currentMenuState;
	menuChoice = "";
	isMousePressed_Left = false;

	v3_MenuCam.SetZero();

	v3_MenuPos[E_MENU].Set(10, 10, 0);
	v3_MenuPos[E_OPTION].Set(60, 60, 0);


	CText * text;
	text = new CText();
	text->setPos(Vector3(Application::getWindow_Width() * 0.22f, Application::getWindow_Height() * 0.5f, 0.1f));
	text->setScale(Vector3(35, 35, 35));
	text->setText("Play");
	text->setGamestate(E_MENU);
	textList.push_back(text);

	text = new CText();
	text->setPos(Vector3(Application::getWindow_Width() * 0.22f, Application::getWindow_Height() * 0.5f - 60, 0.1f));
	text->setScale(Vector3(35, 35, 35));
	text->setText("Option");
	text->setGamestate(E_MENU);
	textList.push_back(text);

	text = new CText();
	text->setPos(Vector3(Application::getWindow_Width() * 0.22f, Application::getWindow_Height() * 0.5f - 120, 0.1f));
	text->setScale(Vector3(35, 35, 35));
	text->setText("Exit");
	text->setGamestate(E_MENU);
	textList.push_back(text);

	text = new CText();
	text->setPos(Vector3(Application::getWindow_Width() * 0.22f, Application::getWindow_Height() * 0.5f, 0.1f));
	text->setScale(Vector3(35, 35, 35));
	text->setText("Toggle Fullscreen");
	text->setGamestate(E_OPTION);
	textList.push_back(text);

	text = new CText();
	text->setPos(Vector3(Application::getWindow_Width() * 0.22f, Application::getWindow_Height() * 0.5f - 60, 0.1f));
	text->setScale(Vector3(35, 35, 35));
	text->setText("Back");
	text->setGamestate(E_OPTION);
	textList.push_back(text);

	Application::activateMouse(false);
}

void SceneMenu::Update(double dt)
{
	if (Application::IsKeyPressed('1'))
		glEnable(GL_CULL_FACE);
	if (Application::IsKeyPressed('2'))
		glDisable(GL_CULL_FACE);
	if (Application::IsKeyPressed('3'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	if (Application::IsKeyPressed('4'))
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if (Application::IsKeyPressed('5'))
	{
		lights[0].type = Light::LIGHT_POINT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}
	else if (Application::IsKeyPressed('6'))
	{
		lights[0].type = Light::LIGHT_DIRECTIONAL;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}
	else if (Application::IsKeyPressed('7'))
	{
		lights[0].type = Light::LIGHT_SPOT;
		glUniform1i(m_parameters[U_LIGHT0_TYPE], lights[0].type);
	}
	else if (Application::IsKeyPressed('8'))
	{
		bLightEnabled = true;
	}
	else if (Application::IsKeyPressed('9'))
	{
		bLightEnabled = false;
	}

	if (Application::IsKeyPressed('I'))
		lights[0].position.z -= (float)(10.f * dt);
	if (Application::IsKeyPressed('K'))
		lights[0].position.z += (float)(10.f * dt);
	if (Application::IsKeyPressed('J'))
		lights[0].position.x -= (float)(10.f * dt);
	if (Application::IsKeyPressed('L'))
		lights[0].position.x += (float)(10.f * dt);
	if (Application::IsKeyPressed('O'))
		lights[0].position.y -= (float)(10.f * dt);
	if (Application::IsKeyPressed('P'))
		lights[0].position.y += (float)(10.f * dt);
	
	fps = (float)(1.f / dt);

	rotateAngle += 50 * dt;

	if (rotateAngle > 360)
	{
		rotateAngle -= 360;
	}

	double x, y;
	Application::GetMousePos(x, y);
	mousePos.x = x / Application::getWindow_Width() * Application::getWindow_Width() + v3_MenuCam.x;
	mousePos.y = (Application::getWindow_Height() - y) / Application::getWindow_Height() * Application::getWindow_Height() + v3_MenuCam.y;

	for (std::vector<CText*>::iterator it = textList.begin(); it != textList.end(); ++it)
	{
		CText* text = static_cast<CText*>(*it);

		if (text->getGameState() == currentMenuState)
		{
			Vector3 offset = v3_MenuPos[currentMenuState];
		
			Vector3 topLeft = text->getPos() + Vector3(text->getText().length() * text->getScale().x - text->getScale().x, text->getScale().y, 0) + offset;
			Vector3 bottomRight = text->getPos() + Vector3(-text->getScale().x * 0.5f, -(text->getScale().y * 0.4f), 0) + offset;

			if (SSDLC::intersect2D(topLeft, bottomRight, mousePos))
			{
				text->setColorToOnClick();

				if (Application::IsMousePressed(0))
				{
					menuChoice = text->getText();
				}
				else
				{
					menuChoice = "";
				}
			}
			else
			{
				text->setColorToNotOnClick();
			}
		}
	}

	if (menuChoice != "")
	{
		if (menuChoice == "Play")
		{
			Application::b_startGame = true;
		}
		else if (menuChoice == "Option")
		{
			currentMenuState = E_OPTION;
		}
		else if (menuChoice == "Exit")
		{
			Application::quitGame();
		}
		else if (menuChoice == "Toggle Fullscreen")
		{
			Application::fullscreenToggle();
		}
		else if (menuChoice == "Back")
		{
			currentMenuState = E_MENU;
		}
	}
}

/********************************************************************************
Update Camera position
********************************************************************************/
void SceneMenu::UpdateCameraStatus(const unsigned char key, const bool status)
{
	camera.UpdateStatus(key, status);
}

/********************************************************************************
Update Weapon status
********************************************************************************/
void SceneMenu::UpdateWeaponStatus(const unsigned char key)
{
	if (key == WA_FIRE)
	{
		// Add a bullet object which starts at the camera position and moves in the camera's direction
	}
}

/********************************************************************************
Render text onto the screen with reference position in the middle of the image
********************************************************************************/
void SceneMenu::RenderText(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID[0] <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID[0]);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.8f, 0, 0); //1.0f is the spacing of each character, you may change this value
		Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top() * characterSpacing;
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

		mesh->Render((unsigned)text[i] * 6, 6);
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	glEnable(GL_DEPTH_TEST);
}

/********************************************************************************
Render text onto the screen
********************************************************************************/
void SceneMenu::RenderTextOnScreen(Mesh* mesh, std::string text, Color color)
{
	if (!mesh || mesh->textureID[0] <= 0)
		return;

	glDisable(GL_DEPTH_TEST);
	Mtx44 ortho;
	//ortho.SetToOrtho(0, m_window_width, 0, m_window_height, -10, 10);
	ortho.SetToOrtho(0, Application::getWindow_Width(), 0, Application::getWindow_Height(), -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	/*projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(pos.x, pos.y, 0);
	modelStack.Scale(scale.x, scale.y, scale.z);*/

	glUniform1i(m_parameters[U_TEXT_ENABLED], 1);
	glUniform3fv(m_parameters[U_TEXT_COLOR], 1, &color.r);
	glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED], 1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, mesh->textureID[0]);
	glUniform1i(m_parameters[U_COLOR_TEXTURE], 0);
	for (unsigned i = 0; i < text.length(); ++i)
	{
		Mtx44 characterSpacing;
		characterSpacing.SetToTranslation(i * 0.6f, 0.f, 0); //1.0f is the spacing of each character, you may change this value
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

/********************************************************************************
Render a mesh in 2D
********************************************************************************/
void SceneMenu::RenderMeshIn2D(Mesh *mesh, bool enableLight, float size, float x, float y, bool rotate)
{
	Mtx44 ortho;
	ortho.SetToOrtho(-80, 80, -60, 60, -10, 10);
	projectionStack.PushMatrix();
	projectionStack.LoadMatrix(ortho);
	viewStack.PushMatrix();
	viewStack.LoadIdentity();
	modelStack.PushMatrix();
	modelStack.LoadIdentity();
	modelStack.Translate(x, y, 0);
	modelStack.Scale(size, size, size);
	if (rotate)
		modelStack.Rotate(rotateAngle, 0, 0, 1);

	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	for (unsigned a = 0; a < 2; ++a)
	{
		if (mesh->textureID[a] > 0)
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + a], 1);
		}
		else
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + a], 0);
		}

		glActiveTexture(GL_TEXTURE0 + a);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID[a]);
		glUniform1i(m_parameters[U_COLOR_TEXTURE + a], a);
	}
	mesh->Render();
	//if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	modelStack.PopMatrix();
	viewStack.PopMatrix();
	projectionStack.PopMatrix();

}

void SceneMenu::PreRendering(CTransform* &transform, bool enableLight, Mesh* mesh)
{
	double angle;
	Vector3 translate, scale, rotate, rotate_Offset;

	transform->GetTranslation(translate.x, translate.y, translate.z);
	transform->GetScale(scale.x, scale.y, scale.z);
	//transform->GetRotation(angle, rotate.x, rotate.y, rotate.z);
	transform->GetRotation2(angle, rotate.x, rotate.y, rotate.z, rotate_Offset.x, rotate_Offset.y, rotate_Offset.z);
	std::vector<CTransform::ORIENTATION> rotateList = transform->getOrientation();

	modelStack.PushMatrix();
	modelStack.Translate(translate.x, translate.y, translate.z);

	if (!rotateList.empty())
	{
		for (std::vector<CTransform::ORIENTATION>::iterator it = rotateList.begin(); it != rotateList.end(); ++it)
		{
			CTransform::ORIENTATION rotateInfo = static_cast<CTransform::ORIENTATION>(*it);
			modelStack.Rotate(rotateInfo.angle, rotateInfo.rotateDir.x, rotateInfo.rotateDir.y, rotateInfo.rotateDir.z);
		}
	}

	if (angle != NULL)
	{
		if (!rotate_Offset.IsZero())
		{
			modelStack.Translate(rotate_Offset.x, rotate_Offset.y, rotate_Offset.z);
		}

		modelStack.Rotate(angle, rotate.x, rotate.y, rotate.z);

		if (!rotate_Offset.IsZero())
		{
			modelStack.Translate(-rotate_Offset.x, -rotate_Offset.y, -rotate_Offset.z);
		}
	}
	modelStack.Scale(scale.x, scale.y, scale.z);

	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	if (enableLight && bLightEnabled)
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 1);
		modelView = viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW], 1, GL_FALSE, &modelView.a[0]);
		modelView_inverse_transpose = modelView.GetInverse().GetTranspose();
		glUniformMatrix4fv(m_parameters[U_MODELVIEW_INVERSE_TRANSPOSE], 1, GL_FALSE, &modelView.a[0]);
	}
	else
	{
		glUniform1i(m_parameters[U_LIGHTENABLED], 0);
	}

	for (unsigned a = 0; a < 2; ++a)
	{
		if (mesh->textureID[a] > 0)
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + a], 1);
		}
		else
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + a], 0);
		}

		glActiveTexture(GL_TEXTURE0 + a);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID[a]);
		glUniform1i(m_parameters[U_COLOR_TEXTURE + a], a);
	}

	modelStack.PopMatrix();
}

void SceneMenu::PostRendering(Mesh * mesh)
{
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

/********************************************************************************
Render a mesh
********************************************************************************/
void SceneMenu::RenderMesh(Mesh *mesh, bool enableLight)
{
	Mtx44 MVP, modelView, modelView_inverse_transpose;

	MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
	if (enableLight && bLightEnabled)
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

	for (unsigned a = 0; a < 2; ++a)
	{
		if (mesh->textureID[a] > 0)
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + a], 1);
		}
		else
		{
			glUniform1i(m_parameters[U_COLOR_TEXTURE_ENABLED + a], 0);
		}

		glActiveTexture(GL_TEXTURE0 + a);
		glBindTexture(GL_TEXTURE_2D, mesh->textureID[a]);
		glUniform1i(m_parameters[U_COLOR_TEXTURE + a], a);
	}

	mesh->Render();
	if (mesh->textureID > 0)
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

/********************************************************************************
Render mobile objects
********************************************************************************/
void SceneMenu::RenderGUI()
{
	//On screen text
	std::ostringstream ss;
	ss.precision(5);
	ss << "FPS: " << fps;

	modelStack.PushMatrix();
	modelStack.Translate(15, 15, 0);
	modelStack.Scale(30, 30, 30);
	RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0));
	modelStack.PopMatrix();
}

void SceneMenu::RenderCharacter()
{
	//Unicorn Gundam
	//Render Character
	modelStack.PushMatrix();
	modelStack.Translate(m_cAvatar->getPos().x, m_cAvatar->getPos().y, m_cAvatar->getPos().z);
	modelStack.Rotate(rotateAngle, 0, 1, 0);
	m_cAvatar->getNode()->Draw(this);
	modelStack.PopMatrix();
}

/********************************************************************************
Render mobile objects
********************************************************************************/
void SceneMenu::RenderMobileObjects()
{
	//Text
	for (std::vector<CText*>::iterator it = textList.begin(); it != textList.end(); ++it)
	{
		CText* text = static_cast<CText*>(*it);

		if (text->getGameState() == currentMenuState)
		{
			modelStack.PushMatrix();
			modelStack.Translate(v3_MenuPos[currentMenuState].x, v3_MenuPos[currentMenuState].y, v3_MenuPos[currentMenuState].z);
			modelStack.Translate(text->getPos().x, text->getPos().y, text->getPos().z);
			modelStack.Scale(text->getScale().x, text->getScale().y, text->getScale().z);
			RenderTextOnScreen(meshList[GEO_TEXT], text->getText(), text->getColor());
			modelStack.PopMatrix();
		}
	}
}

/********************************************************************************
Render the lights in this scene
********************************************************************************/
void SceneMenu::RenderFixedObjects()
{
}

/********************************************************************************
Render the lights in this scene
********************************************************************************/
void SceneMenu::RenderLights()
{
	if (lights[0].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[0].position.x, lights[0].position.y, lights[0].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT0_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (lights[0].type == Light::LIGHT_SPOT)
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
	if (lights[1].type == Light::LIGHT_DIRECTIONAL)
	{
		Vector3 lightDir(lights[1].position.x, lights[1].position.y, lights[1].position.z);
		Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
		glUniform3fv(m_parameters[U_LIGHT1_POSITION], 1, &lightDirection_cameraspace.x);
	}
	else if (lights[1].type == Light::LIGHT_SPOT)
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
}


/********************************************************************************
Render this scene
********************************************************************************/
void SceneMenu::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Mtx44 perspective;
	perspective.SetToPerspective(45.0f, 4.0f / 3.0f, 0.1f, 10000.0f);
	//perspective.SetToOrtho(-80, 80, -60, 60, -1000, 1000);
	projectionStack.LoadMatrix(perspective);

	// Set up the view
	viewStack.LoadIdentity();
	viewStack.LookAt(v3_MenuCam.x, v3_MenuCam.y, v3_MenuCam.z,
		v3_MenuCam.x, v3_MenuCam.y, -100.f,
		camera.up.x, camera.up.y, camera.up.z);

	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	RenderCharacter();

	//Wallpaper
	modelStack.PushMatrix();
	modelStack.Translate(0, 0, -90);
	modelStack.Scale(100, 125, 0);
	RenderMesh(meshList[GEO_WALLPAPER], false);
	modelStack.PopMatrix();

	//Logo
	modelStack.PushMatrix();
	modelStack.Translate(-5, 5, -20);
	modelStack.Scale(10, 12, 0);
	RenderMesh(meshList[GEO_LOGO], false);
	modelStack.PopMatrix();

	RenderLights();
	RenderFixedObjects();
	RenderMobileObjects();

	RenderGUI();
}

/********************************************************************************
Exit process for this scene
********************************************************************************/
void SceneMenu::Exit()
{
	// Cleanup VBO
	for (int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if (meshList[i])
			delete meshList[i];
	}

	while (textList.size() > 0)
	{
		CText* text = textList.back();
		delete text;
		textList.pop_back();
	}

	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}
