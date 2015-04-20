/******************************************************************************/
/*!
\file	StudioProject.h
\author Princeton Chew, name, name, name,
\par	email: 141991A@mymail.nyp.edu.sg
\brief
Studio Project Class
*/
/******************************************************************************/
#include "StudioProject.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "Mtx44.h"

#include "Application.h"
#include "MeshBuilder.h"

#include "Vertex.h"
#include "LoadTGA.h"

using std::cout;
using std::cin;
using std::endl;

/******************************************************************************/
/*!
\brief
Default constructor for class
*/
/******************************************************************************/
StudioProject::StudioProject()
{
}
/******************************************************************************/
/*!
\brief
Default destructor for class
*/
/******************************************************************************/
StudioProject::~StudioProject()
{
}
/******************************************************************************/
/*!
\brief
Initializes the Meshes for the scene
*/
/******************************************************************************/
void StudioProject::InitMesh()
{
	//Initialize all meshes to NULL
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		meshList[i] = NULL;
	}
	meshList[GEO_AXES] = MeshBuilder::GenerateAxes("reference",Color(1,1,1),1000, 1000, 1000);
	meshList[GEO_CUBE] = MeshBuilder::GenerateCube("cube",Color(1,1,1), 1);

	/*
	========================Sky Box=====================================
	========================Sky Box=====================================
	========================Sky Box=====================================
	*/
	meshList[GEO_FRONTSKY] = MeshBuilder::GenerateQuad("front", Color(1, 1, 1), 1.f , 1.f);
	meshList[GEO_FRONTSKY]->textureID = LoadTGA("Skybox//pr_ft.tga");

	meshList[GEO_BACKSKY] = MeshBuilder::GenerateQuad("back", Color(1, 1, 1), 1.f , 1.f);
	meshList[GEO_BACKSKY]->textureID = LoadTGA("Skybox//pr_bk.tga");

	meshList[GEO_SKY] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_SKY]->textureID = LoadTGA("Skybox//pr_up.tga");

	meshList[GEO_LEFTSKY] = MeshBuilder::GenerateQuad("left", Color(1, 1, 1), 1.f,1.f);
	meshList[GEO_LEFTSKY]->textureID = LoadTGA("Skybox//pr_rt.tga");

	meshList[GEO_RIGHTSKY] = MeshBuilder::GenerateQuad("right", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_RIGHTSKY]->textureID = LoadTGA("Skybox//pr_lf.tga");

	meshList[GEO_BOTTOMSKY] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_BOTTOMSKY]->textureID = LoadTGA("Skybox//pr_dn.tga");

	//===================FLOOR===========================//
	meshList[GEO_FLOOR] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_FLOOR]->textureID = LoadTGA("Image//road-texture.tga");

	//===============SUPERMARKET RELATED OBJs==========================//

	meshList[GEO_ROAD] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f, 1.f);
	meshList[GEO_ROAD]->textureID = LoadTGA("Image//floor test.tga");

	meshList[GEO_MARKET] = MeshBuilder::GenerateOBJ("Market", "OBJ//market2.obj");
	meshList[GEO_MARKET]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_MARKET]->material.kDiffuse.Set(1.5f, 1.5f,1.5f);
	meshList[GEO_MARKET]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MARKET]->material.kShininess = 8.f;
	meshList[GEO_MARKET] ->textureID = LoadTGA("Image//Supermarket.tga");

	meshList[GEO_CASHIER] = MeshBuilder::GenerateOBJ("Market", "OBJ//Cashier_Counter.obj");
	meshList[GEO_CASHIER]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CASHIER]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_CASHIER]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CASHIER]->material.kShininess = 8.f;
	meshList[GEO_CASHIER] ->textureID = LoadTGA("Image//cashier_counter.tga");

	meshList[GEO_CASHREG] = MeshBuilder::GenerateOBJ("Market", "OBJ//cash-register.obj");
	meshList[GEO_CASHREG]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CASHREG]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_CASHREG]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CASHREG]->material.kShininess = 8.f;
	meshList[GEO_CASHREG] ->textureID = LoadTGA("Image//cashRegisterTexture.tga");

	meshList[GEO_COLDFOODSHELF] = MeshBuilder::GenerateOBJ("Market" , "OBJ//Cold-food-shelf.obj");
	meshList[GEO_COLDFOODSHELF]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_COLDFOODSHELF]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_COLDFOODSHELF]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_COLDFOODSHELF]->material.kShininess = 8.f;
	meshList[GEO_COLDFOODSHELF] ->textureID = LoadTGA("Image//Shelf_Texture.tga");

	meshList[GEO_SHELF] = MeshBuilder::GenerateOBJ("Market" , "OBJ//shelf1.obj");
	meshList[GEO_SHELF]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SHELF]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_SHELF]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SHELF]->material.kShininess = 8.f;
	meshList[GEO_SHELF] ->textureID = LoadTGA("Image//Shelf.tga");

	meshList[GEO_SHELF2] = MeshBuilder::GenerateOBJ("Market" , "OBJ//Shelf2.obj");
	meshList[GEO_SHELF2]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SHELF2]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_SHELF2]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SHELF2]->material.kShininess = 8.f;
	meshList[GEO_SHELF2] ->textureID = LoadTGA("Image//Shelf_Texture2.tga");

	meshList[GEO_RAIL] = MeshBuilder::GenerateOBJ("Railing" , "OBJ//Railing.obj");
	meshList[GEO_RAIL]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_RAIL]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_RAIL]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_RAIL]->material.kShininess = 8.f;
	meshList[GEO_RAIL] ->textureID = LoadTGA("Image//Railing.tga");

	meshList[GEO_DUSTBIN] = MeshBuilder::GenerateOBJ("Dustbin" , "OBJ//dustbin.obj");
	meshList[GEO_DUSTBIN]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_DUSTBIN]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_DUSTBIN]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_DUSTBIN]->material.kShininess = 8.f;
	meshList[GEO_DUSTBIN] ->textureID = LoadTGA("Image//dustbin.tga");

	meshList[GEO_SARDINE_CAN] = MeshBuilder::GenerateOBJ("Railing" , "OBJ//canned-food1.obj");
	meshList[GEO_SARDINE_CAN]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_SARDINE_CAN]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_SARDINE_CAN]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_SARDINE_CAN]->material.kShininess = 8.f;
	meshList[GEO_SARDINE_CAN] ->textureID = LoadTGA("Image//canned_food_1.tga");

	meshList[GEO_BAKED_BEANS_CAN] = MeshBuilder::GenerateOBJ("Baked Beans" , "OBJ//canned-food3.obj");
	meshList[GEO_BAKED_BEANS_CAN]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_BAKED_BEANS_CAN]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_BAKED_BEANS_CAN]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_BAKED_BEANS_CAN]->material.kShininess = 8.f;
	meshList[GEO_BAKED_BEANS_CAN] ->textureID = LoadTGA("Image//canned_food_3.tga");

	meshList[GEO_MILOCAN] = MeshBuilder::GenerateOBJ("Railing" , "OBJ//milocan.obj");
	meshList[GEO_MILOCAN]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_MILOCAN]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_MILOCAN]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MILOCAN]->material.kShininess = 8.f;
	meshList[GEO_MILOCAN] ->textureID = LoadTGA("Image//milocan.tga");

	meshList[GEO_COKE_CAN] = MeshBuilder::GenerateOBJ("Coke" , "OBJ//drink-can1.obj");
	meshList[GEO_COKE_CAN]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_COKE_CAN]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_COKE_CAN]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_COKE_CAN]->material.kShininess = 8.f;
	meshList[GEO_COKE_CAN] ->textureID = LoadTGA("Image//drink_can1.tga");

	meshList[GEO_PEA_N_CARROTS] = MeshBuilder::GenerateOBJ("Railing" , "OBJ//canned-food2.obj");
	meshList[GEO_PEA_N_CARROTS]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_PEA_N_CARROTS]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_PEA_N_CARROTS]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_PEA_N_CARROTS]->material.kShininess = 8.f;
	meshList[GEO_PEA_N_CARROTS] ->textureID = LoadTGA("Image//canned_food_2.tga");

	meshList[GEO_DRINKCAN2] = MeshBuilder::GenerateOBJ("Railing" , "OBJ//drink-can2.obj");
	meshList[GEO_DRINKCAN2]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_DRINKCAN2]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_DRINKCAN2]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_DRINKCAN2]->material.kShininess = 8.f;
	meshList[GEO_DRINKCAN2] ->textureID = LoadTGA("Image//drink_can2.tga");

	meshList[GEO_PEPSI_CAN] = MeshBuilder::GenerateOBJ("Railing" , "OBJ//drink-can3.obj");
	meshList[GEO_PEPSI_CAN]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_PEPSI_CAN]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_PEPSI_CAN]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_PEPSI_CAN]->material.kShininess = 8.f;
	meshList[GEO_PEPSI_CAN] ->textureID = LoadTGA("Image//drink_can3.tga");

	meshList[GEO_CEREALBOX1] = MeshBuilder::GenerateOBJ("Railing" , "OBJ//cereal-box1.obj");
	meshList[GEO_CEREALBOX1]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CEREALBOX1]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_CEREALBOX1]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CEREALBOX1]->material.kShininess = 8.f;
	meshList[GEO_CEREALBOX1] ->textureID = LoadTGA("Image//Cereal-box1.tga");

	meshList[GEO_CEREALBOX2] = MeshBuilder::GenerateOBJ("Railing" , "OBJ//cereal-box2.obj");
	meshList[GEO_CEREALBOX2]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_CEREALBOX2]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_CEREALBOX2]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_CEREALBOX2]->material.kShininess = 8.f;
	meshList[GEO_CEREALBOX2] ->textureID = LoadTGA("Image//cereal_box2.tga");

	meshList[GEO_PIZZABOX] = MeshBuilder::GenerateOBJ("Railing" , "OBJ//frozenpizza.obj");
	meshList[GEO_PIZZABOX]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_PIZZABOX]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_PIZZABOX]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_PIZZABOX]->material.kShininess = 8.f;
	meshList[GEO_PIZZABOX] ->textureID = LoadTGA("Image//frozen_pizza.tga");

	meshList[GEO_MONEY] = MeshBuilder::GenerateOBJ("Market Door Right", "OBJ/dollarbill.obj");
	meshList[GEO_MONEY]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_MONEY]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_MONEY]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MONEY]->material.kShininess = 8.f;
	meshList[GEO_MONEY]->textureID = LoadTGA("Image//dollarbill.tga");

	meshList[GEO_POTATOCHIPS] = MeshBuilder::GenerateOBJ("Railing" , "OBJ//potato-chips.obj");
	meshList[GEO_POTATOCHIPS]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_POTATOCHIPS]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_POTATOCHIPS]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_POTATOCHIPS]->material.kShininess = 8.f;
	meshList[GEO_POTATOCHIPS] ->textureID = LoadTGA("Image//potato_chips.tga");

	meshList[GEO_DOORLEFT] = MeshBuilder::GenerateOBJ("Market door left", "OBJ//MarketDoorLeft.obj");
	meshList[GEO_DOORLEFT]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_DOORLEFT]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_DOORLEFT]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_DOORLEFT]->material.kShininess = 8.f;
	meshList[GEO_DOORLEFT]->textureID = LoadTGA("Image//MarketDoor.tga");

	meshList[GEO_DOORRIGHT] = MeshBuilder::GenerateOBJ("Market Door Right", "OBJ/MarketDoorRight.obj");
	meshList[GEO_DOORRIGHT]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_DOORRIGHT]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_DOORRIGHT]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_DOORRIGHT]->material.kShininess = 8.f;
	meshList[GEO_DOORRIGHT]->textureID = LoadTGA("Image//MarketDoor.tga");

	//meshList[GEO_CANTEST] = MeshBuilder::GenerateQuad("CANTEST", Color(1, 1, 1), 1.f, 1.f);
	//meshList[GEO_CANTEST] ->textureID = LoadTGA("UI sprites//UI-canned_food_1.tga");

	//===============MODEL OBJs==========================//
	meshList[modelHead] = MeshBuilder::GenerateOBJ("Character Head", "OBJ//modelHead.obj");
	meshList[modelHead]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[modelHead]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[modelHead]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[modelHead]->material.kShininess = 8.f;
	meshList[modelHead]->textureID = LoadTGA("Image//modelHead.tga");

	meshList[modelTorso] = MeshBuilder::GenerateOBJ("Character Torso", "OBJ//modelTorso.obj");
	meshList[modelTorso]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[modelTorso]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[modelTorso]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[modelTorso]->material.kShininess = 8.f;
	meshList[modelTorso]->textureID = LoadTGA("Image//modelTorso.tga");

	meshList[modelRightHand] = MeshBuilder::GenerateOBJ("Character Right Hand", "OBJ//modelArm.obj");
	meshList[modelRightHand]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[modelRightHand]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[modelRightHand]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[modelRightHand]->material.kShininess = 8.f;
	meshList[modelRightHand]->textureID = LoadTGA("Image//modelHand.tga");

	meshList[modelLeftHand] = MeshBuilder::GenerateOBJ("Character Left Hand", "OBJ//modelArm.obj");
	meshList[modelLeftHand]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[modelLeftHand]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[modelLeftHand]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[modelLeftHand]->material.kShininess = 8.f;
	meshList[modelLeftHand]->textureID = LoadTGA("Image//modelHand.tga");

	meshList[modelLeftLeg] = MeshBuilder::GenerateOBJ("Character Left Leg", "OBJ//modelLeg.obj");
	meshList[modelLeftLeg]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[modelLeftLeg]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[modelLeftLeg]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[modelLeftLeg]->material.kShininess = 8.f;
	meshList[modelLeftLeg]->textureID = LoadTGA("Image//modelLeg.tga");

	meshList[modelRightLeg] = MeshBuilder::GenerateOBJ("Character Right Leg", "OBJ//modelLeg.obj");
	meshList[modelRightLeg]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[modelRightLeg]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[modelRightLeg]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[modelRightLeg]->material.kShininess = 8.f;
	meshList[modelRightLeg]->textureID = LoadTGA("Image//modelLeg.tga");

	//===============CASHIER OBJs==========================//
	meshList[cashierHead] = MeshBuilder::GenerateOBJ("Cashier Head", "OBJ//cashierHead.obj");
	meshList[cashierHead]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[cashierHead]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[cashierHead]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[cashierHead]->material.kShininess = 8.f;
	meshList[cashierHead]->textureID = LoadTGA("Image//cashierHead.tga");

	meshList[cashierTorso] = MeshBuilder::GenerateOBJ("Cashier Torso", "OBJ//cashierTorso.obj");
	meshList[cashierTorso]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[cashierTorso]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[cashierTorso]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[cashierTorso]->material.kShininess = 8.f;
	meshList[cashierTorso]->textureID = LoadTGA("Image//cashierTorso.tga");

	meshList[cashierRightHand] = MeshBuilder::GenerateOBJ("Cashier Right Hand", "OBJ//cashierHand.obj");
	meshList[cashierRightHand]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[cashierRightHand]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[cashierRightHand]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[cashierRightHand]->material.kShininess = 8.f;
	meshList[cashierRightHand]->textureID = LoadTGA("Image//cashierHand.tga");

	meshList[cashierLeftHand] = MeshBuilder::GenerateOBJ("Cashier Left Hand", "OBJ//cashierHand.obj");
	meshList[cashierLeftHand]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[cashierLeftHand]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[cashierLeftHand]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[cashierLeftHand]->material.kShininess = 8.f;
	meshList[cashierLeftHand]->textureID = LoadTGA("Image//cashierHand.tga");

	meshList[cashierLeftLeg] = MeshBuilder::GenerateOBJ("Cashier Left Leg", "OBJ//cashierLeg.obj");
	meshList[cashierLeftLeg]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[cashierLeftLeg]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[cashierLeftLeg]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[cashierLeftLeg]->material.kShininess = 8.f;
	meshList[cashierLeftLeg]->textureID = LoadTGA("Image//cashierLeg.tga");

	meshList[cashierRightLeg] = MeshBuilder::GenerateOBJ("Cashier Right Leg", "OBJ//cashierLeg.obj");
	meshList[cashierRightLeg]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[cashierRightLeg]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[cashierRightLeg]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[cashierRightLeg]->material.kShininess = 8.f;
	meshList[cashierRightLeg]->textureID = LoadTGA("Image//cashierLeg.tga");

	//===============CUSTOMER OBJs==========================//
	meshList[customerHead] = MeshBuilder::GenerateOBJ("customer Head", "OBJ//cashierHead.obj");
	meshList[customerHead]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[customerHead]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[customerHead]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[customerHead]->material.kShininess = 8.f;
	meshList[customerHead]->textureID = LoadTGA("Image//customerHead.tga");

	meshList[customerTorso] = MeshBuilder::GenerateOBJ("customer Torso", "OBJ//cashierTorso.obj");
	meshList[customerTorso]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[customerTorso]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[customerTorso]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[customerTorso]->material.kShininess = 8.f;
	meshList[customerTorso]->textureID = LoadTGA("Image//customerTorso.tga");

	meshList[customerRightHand] = MeshBuilder::GenerateOBJ("customer Right Hand", "OBJ//cashierHand.obj");
	meshList[customerRightHand]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[customerRightHand]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[customerRightHand]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[customerRightHand]->material.kShininess = 8.f;
	meshList[customerRightHand]->textureID = LoadTGA("Image//customerHand.tga");

	meshList[customerLeftHand] = MeshBuilder::GenerateOBJ("customer Left Hand", "OBJ//cashierHand.obj");
	meshList[customerLeftHand]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[customerLeftHand]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[customerLeftHand]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[customerLeftHand]->material.kShininess = 8.f;
	meshList[customerLeftHand]->textureID = LoadTGA("Image//customerHand.tga");

	meshList[customerLeftLeg] = MeshBuilder::GenerateOBJ("customer Left Leg", "OBJ//cashierLeg.obj");
	meshList[customerLeftLeg]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[customerLeftLeg]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[customerLeftLeg]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[customerLeftLeg]->material.kShininess = 8.f;
	meshList[customerLeftLeg]->textureID = LoadTGA("Image//customerLeg.tga");

	meshList[customerRightLeg] = MeshBuilder::GenerateOBJ("customer Right Leg", "OBJ//cashierLeg.obj");
	meshList[customerRightLeg]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[customerRightLeg]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[customerRightLeg]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[customerRightLeg]->material.kShininess = 8.f;
	meshList[customerRightLeg]->textureID = LoadTGA("Image//customerLeg.tga");

	//=======================Item Inventory Page================//
	meshList[itemInventory] = MeshBuilder::GenerateQuad("item Inventory", Color(1, 1, 1), 1.f , 1.f);
	meshList[itemInventory]->textureID = LoadTGA("UI sprites//UI-inventory.tga");
	Page.SetBackground("Item Inventory background", itemInventory);

	meshList[UI_SARDINE_CAN] = MeshBuilder::GenerateQuad("sardine can", Color(1, 1, 1), 1.f , 1.f);
	meshList[UI_SARDINE_CAN]->textureID = LoadTGA("UI sprites//UI-canned_food_1.tga");
	Page.SetSardine("Sardine Can", UI_SARDINE_CAN);

	meshList[UI_PEA_N_CARROTS] = MeshBuilder::GenerateQuad("peas n carrots can", Color(1, 1, 1), 1.f , 1.f);
	meshList[UI_PEA_N_CARROTS]->textureID = LoadTGA("UI sprites//UI-canned_food_2.tga");
	Page.SetPnc("Peas And Carrots Can", UI_PEA_N_CARROTS);

	meshList[UI_BAKED_BEANS_CAN] = MeshBuilder::GenerateQuad("bakes beans can", Color(1, 1, 1), 1.f , 1.f);
	meshList[UI_BAKED_BEANS_CAN]->textureID = LoadTGA("UI sprites/UI-canned_food_3.tga");
	Page.setBakedBean("Baked Beans Can", UI_BAKED_BEANS_CAN);

	meshList[UI_PIZZABOX] = MeshBuilder::GenerateQuad("pizza box", Color(1, 1, 1), 1.f , 1.f);
	meshList[UI_PIZZABOX]->textureID = LoadTGA("UI sprites/UI-pizza.tga");
	Page.setPizzabox("Frozen Pizza", UI_PIZZABOX);

	meshList[UI_POTATOCHIPS] = MeshBuilder::GenerateQuad("pizza box", Color(1, 1, 1), 1.f , 1.f);
	meshList[UI_POTATOCHIPS]->textureID = LoadTGA("UI sprites/UI-potato_chips.tga");
	Page.setPotatoChip("Lays Potato Chips", UI_POTATOCHIPS);

	meshList[UI_COKE_CAN] = MeshBuilder::GenerateQuad("pizza box", Color(1, 1, 1), 1.f , 1.f);
	meshList[UI_COKE_CAN]->textureID = LoadTGA("UI sprites/UI-drink_can1.tga");
	Page.setCoke("Coke", UI_COKE_CAN);

	meshList[UI_PEPSI_CAN] = MeshBuilder::GenerateQuad("pizza box", Color(1, 1, 1), 1.f , 1.f);
	meshList[UI_PEPSI_CAN]->textureID = LoadTGA("UI sprites/UI-drink_can3.tga");
	Page.setPepsi("Pepsi", UI_PEPSI_CAN);

	meshList[UI_COKE_ZERO_CAN] = MeshBuilder::GenerateQuad("Cokde Zero", Color(1, 1, 1), 1.f , 1.f);
	meshList[UI_COKE_ZERO_CAN]->textureID = LoadTGA("UI sprites/UI-drink_can2.tga");
	Page.setCokeZero("Coke Zero",UI_COKE_ZERO_CAN); 

	meshList[UI_CEREALBOX1] = MeshBuilder::GenerateQuad("pizza box", Color(1, 1, 1), 1.f , 1.f);
	meshList[UI_CEREALBOX1]->textureID = LoadTGA("UI sprites/UI-Cereal-box1.tga");
	Page.setCerealbox1("Bran Buds Cereal", UI_CEREALBOX1);

	meshList[UI_CEREALBOX2] = MeshBuilder::GenerateQuad("pizza box", Color(1, 1, 1), 1.f , 1.f);
	meshList[UI_CEREALBOX2]->textureID = LoadTGA("UI sprites/UI-cereal_box2.tga");
	Page.setCerealbox2("Morning Chips Cereal", UI_CEREALBOX2);

	meshList[UI_MILOCAN] = MeshBuilder::GenerateQuad("pizza box", Color(1, 1, 1), 1.f , 1.f);
	meshList[UI_MILOCAN]->textureID = LoadTGA("UI sprites/UI-milocan.tga");
	Page.setMilo("Milo Can", UI_MILOCAN);

	meshList[UI_SARDINE_CAN_PAID] = MeshBuilder::GenerateQuad("paid sardine can", Color(1, 1, 1), 1.f , 1.f);
	meshList[UI_SARDINE_CAN_PAID]->textureID = LoadTGA("UI sprites/UI-canned_food_1_paid.tga");

	meshList[UI_PEA_N_CARROTS_PAID] = MeshBuilder::GenerateQuad("paid sardine can", Color(1, 1, 1), 1.f , 1.f);
	meshList[UI_PEA_N_CARROTS_PAID]->textureID = LoadTGA("UI sprites/UI-canned_food_2_paid.tga");

	meshList[UI_BAKED_BEANS_CAN_PAID] = MeshBuilder::GenerateQuad("paid sardine can", Color(1, 1, 1), 1.f , 1.f);
	meshList[UI_BAKED_BEANS_CAN_PAID]->textureID = LoadTGA("UI sprites/UI-canned_food_3_paid.tga");

	meshList[UI_PIZZABOX_PAID] = MeshBuilder::GenerateQuad("paid sardine can", Color(1, 1, 1), 1.f , 1.f);
	meshList[UI_PIZZABOX_PAID]->textureID = LoadTGA("UI sprites/UI-pizza_paid.tga");

	meshList[UI_POTATOCHIPS_PAID] = MeshBuilder::GenerateQuad("paid sardine can", Color(1, 1, 1), 1.f , 1.f);
	meshList[UI_POTATOCHIPS_PAID]->textureID = LoadTGA("UI sprites/UI-potato_chips_paid.tga");

	meshList[UI_COKE_CAN_PAID] = MeshBuilder::GenerateQuad("paid sardine can", Color(1, 1, 1), 1.f , 1.f);
	meshList[UI_COKE_CAN_PAID]->textureID = LoadTGA("UI sprites/UI-drink_can1_paid.tga");

	meshList[UI_PEPSI_CAN_PAID] = MeshBuilder::GenerateQuad("paid sardine can", Color(1, 1, 1), 1.f , 1.f);
	meshList[UI_PEPSI_CAN_PAID]->textureID = LoadTGA("UI sprites/UI-drink_can3_paid.tga");

	meshList[UI_COKE_ZERO_CAN_PAID] = MeshBuilder::GenerateQuad("paid sardine can", Color(1, 1, 1), 1.f , 1.f);
	meshList[UI_COKE_ZERO_CAN_PAID]->textureID = LoadTGA("UI sprites/UI-drink_can2_paid.tga");

	meshList[UI_CEREALBOX1_PAID] = MeshBuilder::GenerateQuad("paid sardine can", Color(1, 1, 1), 1.f , 1.f);
	meshList[UI_CEREALBOX1_PAID]->textureID = LoadTGA("UI sprites/UI-Cereal-box1_paid.tga");

	meshList[UI_CEREALBOX2_PAID] = MeshBuilder::GenerateQuad("paid sardine can", Color(1, 1, 1), 1.f , 1.f);
	meshList[UI_CEREALBOX2_PAID]->textureID = LoadTGA("UI sprites/UI-cereal_box2_paid.tga");

	meshList[UI_MILOCAN_PAID] = MeshBuilder::GenerateQuad("paid sardine can", Color(1, 1, 1), 1.f , 1.f);
	meshList[UI_MILOCAN_PAID]->textureID = LoadTGA("UI sprites/UI-milocan_paid.tga");

	meshList[MENUBACKGROUND] = MeshBuilder::GenerateQuad("Menu Background", Color(1, 1, 1), 1.f , 1.f);
	meshList[MENUBACKGROUND]->textureID = LoadTGA("Image//menu.tga");
	menu.SetBackground(MENUBACKGROUND);

	meshList[MENUARROW] = MeshBuilder::GenerateQuad("Menu Arrow", Color(1, 1, 1), 1.f , 1.f);
	meshList[MENUARROW]->textureID = LoadTGA("Image//Arrow.tga");
	menu.SetArrow(MENUARROW);

	meshList[PlayGameTrue] = MeshBuilder::GenerateQuad("Play Game True", Color(1, 1, 1), 1.f , 1.f);
	meshList[PlayGameTrue]->textureID = LoadTGA("Image//PlayGameTrue.tga");
	menu.SetStartGameTrue(PlayGameTrue);

	meshList[PlayGameFalse] = MeshBuilder::GenerateQuad("Play Game False", Color(1, 1, 1), 1.f , 1.f);
	meshList[PlayGameFalse]->textureID = LoadTGA("Image//PlayGameFalse.tga");
	menu.SetStartGameFalse(PlayGameFalse);

	meshList[ExitTrue] = MeshBuilder::GenerateQuad("Play Game True", Color(1, 1, 1), 1.f , 1.f);
	meshList[ExitTrue]->textureID = LoadTGA("Image//ExitTrue.tga");
	menu.SetEndGameTrue(ExitTrue);

	meshList[ExitFalse] = MeshBuilder::GenerateQuad("Play Game False", Color(1, 1, 1), 1.f , 1.f);
	meshList[ExitFalse]->textureID = LoadTGA("Image//ExitFalse.tga");
	menu.SetEndGameFalse(ExitFalse);

	meshList[GameOverStateMesh] = MeshBuilder::GenerateQuad("Game Over Mesh", Color(1, 1, 1), 1.f , 1.f);
	meshList[GameOverStateMesh]->textureID = LoadTGA("Image//GameOver.tga");
	menu.SetGameOverMesh(GameOverStateMesh);

	meshList[ContorlMesh] = MeshBuilder::GenerateQuad("Control Mesh", Color(1, 1, 1), 1.f , 1.f);
	meshList[ContorlMesh]->textureID = LoadTGA("Image//Controls.tga");
	menu.SetControlMesh(ContorlMesh);

	meshList[ControlTrue] = MeshBuilder::GenerateQuad("Control true Mesh", Color(1, 1, 1), 1.f , 1.f);
	meshList[ControlTrue]->textureID = LoadTGA("Image//ControlTrue.tga");
	menu.SetPointControlTrue(ControlTrue);

	meshList[ControlFalse] = MeshBuilder::GenerateQuad("Control false Mesh", Color(1, 1, 1), 1.f , 1.f);
	meshList[ControlFalse]->textureID = LoadTGA("Image//ControlFalse.tga");
	menu.SetPointControlFalse(ControlFalse);

	meshList[WinStateMesh] = MeshBuilder::GenerateQuad("Win Mesh", Color(1, 1, 1), 1.f , 1.f);
	meshList[WinStateMesh]->textureID = LoadTGA("Image//YouWon.tga");
	menu.SetWinMesh(WinStateMesh);

	//meshList[GEO_TOP] = MeshBuilder::GenerateQuad("top", Color(1, 1, 1), 1.f, 1.f);
	//meshList[GEO_TOP]->textureID = LoadTGA("Image//hills_up.tga");

	//meshList[GEO_BOTTOM] = MeshBuilder::GenerateQuad("bottom", Color(1, 1, 1), 1.f, 1.f);
	//meshList[GEO_BOTTOM]->textureID = LoadTGA("Image//road-texture.tga");

	//Light ball
	meshList[GEO_LIGHTBALL] = MeshBuilder::GenerateCube("lightball", Color(1, 1, 1), 5);
	meshList[GEO_LIGHTBALL2] = MeshBuilder::GenerateCube("lightball2", Color(1, 1, 1), 5);
	meshList[GEO_LIGHTBALL3] = MeshBuilder::GenerateCube("lightball3", Color(1, 1, 1), 5);
	meshList[GEO_LIGHTBALL4] = MeshBuilder::GenerateCube("lightball4", Color(1, 1, 1), 5);
	meshList[GEO_LIGHTBALL5] = MeshBuilder::GenerateCube("lightball5", Color(1, 1, 1), 5);
	meshList[GEO_LIGHTBALL6] = MeshBuilder::GenerateCube("lightball6", Color(1, 1, 1), 5);
	meshList[GEO_LIGHTBALL7] = MeshBuilder::GenerateCube("lightball6", Color(1, 1, 1), 5);
	meshList[GEO_LIGHTBALL8] = MeshBuilder::GenerateCube("lightball6", Color(1, 1, 1), 5);
	//Quad texture
	meshList[GEO_QUAD] = MeshBuilder::GenerateQuad("quad", Color(1, 1, 1), 1.f,1.f);
	meshList[GEO_QUAD]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_QUAD]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_QUAD]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_QUAD]->material.kShininess = 8.f;
	meshList[GEO_QUAD]->textureID = LoadTGA("Image//color2.tga");

	//Text Related
	meshList[GEO_TEXT] = MeshBuilder::GenerateText("text", 16, 16);
	meshList[GEO_TEXT]->textureID = LoadTGA("Image//CourierNew.tga");

}
/******************************************************************************/
/*!
\brief
Initializes the Variables to be used in the scene
*/
/******************************************************************************/
void StudioProject::InitVariables()
{
	//Sound Engine
	engine = createIrrKlangDevice();
	if (!engine)
	{
		printf("Could not startup engine\n");
	}
	//variable to rotate geometry
	worldsize = 1000.0f;
	roomsize = 250.0f;
	roomheight = 150.0f;
	fps = 0.0f;
	angle = 3600;
	playerAngle = 0;
	moving = 0;
	showInventory = false;
	//OBJ FOOD BOOLEANS
	Pizza = false;
	Peas = false;
	Milo = false;
	Cereal1 = false;
	Cereal2 = false;
	Sardine = false;
	Beans = false;
	Lays = false;
	Coke = false;
	CokeZero = false;
	Pepsi = false;
	Pizza = false;
	moveItem = 0; // SPEED
	peaCount = 0;
	PizzaCount = 0;
	MiloCount = 0;
	Cereal1Count = 0;
	Cereal2Count = 0;
	SardineCount = 0;
	BeansCount = 0;
	LaysCount = 0;
	CokeCount = 0;
	CokeZeroCount = 0;
	PepsiCount = 0;
	winState = false;

	//==Time Attack==//
	TimeAttack = false;
	generateList = false;
	TAmatchedItems = 0;
	isTAwon = false;
	TAtime = 60.f;
	timeTA = "";
	TAstartedOnce = 0;
	messageTime = 0.f;

	//==Guess The Price==//
	GTP = false;
	isGTPwon = false;
	NoOfItemsTaken = 0;
	totalCost = 0.f;
	GTPstartedOnce = 0;
	NumItem = "";
	CostOfItems = "";

	//==Thief==//
	ThiefGame = false;
	isThiefwon = false;
	NoOfItemsStolen = 0;
	NumStolen = "";


	int a = 0;

	//variable to animate model
	rotateRightArms = rotateLeftArms = rotateRightLeg = rotateLeftLeg = 360;
	charPosition.Set(0.f, 0.f,0.f);
	movingModel = false;
	movingCharacterX = movingCharacterZ = 0;

	Framerate = "FPS: ";

	Cash = "";
	//=========Cashier box===============//
	hitBox checkOut;
	Vector3 cashierMax, cashierMin;
	//First Cashier
	cashierMax.Set(-19.2f,8.f,-11.6f);
	cashierMin.Set(-26.f,4.f,-13.f);
	checkOut.SetBox(cashierMax,cashierMin);
	CashierBox.push_back(checkOut);
	//Middle Cashier
	cashierMax.Set(-19.2f,8.f,7.1f);
	cashierMin.Set(-26.f,4.f,4.8f);
	checkOut.SetBox(cashierMax,cashierMin);
	CashierBox.push_back(checkOut);
	//Last Cashier
	cashierMax.Set(-19.2f,8.f,25.f);
	cashierMin.Set(-26.f,4.f,22.2f);
	checkOut.SetBox(cashierMax,cashierMin);
	CashierBox.push_back(checkOut);

	//===============Sardine Can Variables============//
	Mesh* newMesh;
	newMesh = MeshBuilder::GenerateOBJ("SardineCan" , "OBJ//canned-food1.obj");
	newMesh->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newMesh->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newMesh->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newMesh->material.kShininess = 8.f;
	newMesh->textureID = LoadTGA("Image//canned_food_1.tga");
	hitBox sardineBox;
	for(int i = 0; i < 20;i++)
	{
		Mtx44 newTRS;
		if(i % 5 == 0 && i > 0) //When i mod 5 == 0, it will create a spacing 
		{
			a += 1;
		}
		newTRS.SetToTranslation(10,6.2,-8+i + a);
		sardineCan.SetData("Sardine Can", 3.5f, true, newMesh,GEO_SARDINE_CAN,newTRS, false);
		Container.push_back(sardineCan);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12] + 0.59, newTRS.a[13]+0.7, newTRS.a[14]+0.35);
		Min.Set(-0.59 + newTRS.a[12], -0.7+newTRS.a[13], -0.35+newTRS.a[14]);
		sardineBox.SetBox(Max, Min);
		boxContainer.push_back(sardineBox);
	}
	a = 0; //reset a t 0

	//BACK MIDDLE SHELF Back row
	for(int i = 0; i < 20;i++)
	{
		Mtx44 newTRS;
		if(i % 5 == 0 && i > 0)
		{
			a += 1;
		}
		newTRS.SetToTranslation(12,6.2,-8+i + a);
		sardineCan.SetData("Sardine Can", 3.5f, true, newMesh,GEO_SARDINE_CAN,newTRS,false);
		Container2.push_back(sardineCan);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12] + 0.59, newTRS.a[13]+0.7, newTRS.a[14]+0.35);
		Min.Set(-0.59 + newTRS.a[12], -0.7+newTRS.a[13], -0.35+newTRS.a[14]);
		sardineBox.SetBox(Max, Min);
		boxContainer2.push_back(sardineBox);
	}
	a = 0;

	//===========================SECOND FLOOR BACK================//
	for(int i = 0; i < 65;i++)
	{
		Mtx44 newTRS;
		if(i % 5 == 0 && i > 0) //When i mod 5 == 0, it will create a spacing 
		{
			a += 1;
		}
		if (i % 25 == 0 && i == 25 ||
			i % 40 == 0 && i == 40)
		{
			a += 18;
		}
		newTRS.SetToTranslation(24.5,27.2,-68+i + a);
		sardineCan.SetData("Sardine Can", 3.5f, true, newMesh,GEO_SARDINE_CAN,newTRS,false);
		Container2.push_back(sardineCan);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12] + 1, newTRS.a[13]+0.7, newTRS.a[14]+0.35);
		Min.Set(-1.5 + newTRS.a[12], -0.7+newTRS.a[13], -0.35+newTRS.a[14]);
		sardineBox.SetBox(Max, Min);
		boxContainer2.push_back(sardineBox);
	}
	a = 0;

	//===========================SECOND FLOOR FRONT================//
	for(int i = 0; i < 65;i++)
	{
		Mtx44 newTRS;
		if(i % 5 == 0 && i > 0) //When i mod 5 == 0, it will create a spacing 
		{
			a += 1;
		}
		if (i % 25 == 0 && i == 25 ||
			i % 40 == 0 && i == 40)
		{
			a += 18;
		}
		newTRS.SetToTranslation(21.5,27.2,-68+i + a);
		sardineCan.SetData("Sardine Can", 3.5f, true, newMesh,GEO_SARDINE_CAN,newTRS, false);
		Container.push_back(sardineCan);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12] + 1, newTRS.a[13]+0.7, newTRS.a[14]+0.35);
		Min.Set(-1.5 + newTRS.a[12], -0.7+newTRS.a[13], -0.35+newTRS.a[14]);
		sardineBox.SetBox(Max, Min);
		boxContainer.push_back(sardineBox);
	}
	a = 0; //reset a t 0

	//===========================SECOND FLOOR FRONT 1ST ROW================//
	for(int i = 0; i < 65;i++)
	{
		Mtx44 newTRS;
		if(i % 5 == 0 && i > 0) //When i mod 5 == 0, it will create a spacing 
		{
			a += 1;
		}
		if (i % 25 == 0 && i == 25 ||
			i % 40 == 0 && i == 40)
		{
			a += 18;
		}
		newTRS.SetToTranslation(-16,27.2,-68+i + a);
		sardineCan.SetData("Sardine Can", 3.5f, true, newMesh,GEO_SARDINE_CAN,newTRS, false);
		Container.push_back(sardineCan);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12] + 1, newTRS.a[13]+0.7, newTRS.a[14]+0.35);
		Min.Set(-1.5 + newTRS.a[12], -0.7+newTRS.a[13], -0.35+newTRS.a[14]);
		sardineBox.SetBox(Max, Min);
		boxContainer.push_back(sardineBox);
	}
	a = 0; //reset a t 0

	//===========================SECOND FLOOR BACK 1ST ROW================//
	for(int i = 0; i < 65;i++)
	{
		Mtx44 newTRS;
		if(i % 5 == 0 && i > 0) //When i mod 5 == 0, it will create a spacing 
		{
			a += 1;
		}
		if (i % 25 == 0 && i == 25 ||
			i % 40 == 0 && i == 40)
		{
			a += 18;
		}
		newTRS.SetToTranslation(-13,27.2,-68+i + a);
		sardineCan.SetData("Sardine Can", 3.5f, true, newMesh,GEO_SARDINE_CAN,newTRS, false);
		Container.push_back(sardineCan);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12] + 1, newTRS.a[13]+0.7, newTRS.a[14]+0.35);
		Min.Set(-1.5 + newTRS.a[12], -0.7+newTRS.a[13], -0.35+newTRS.a[14]);
		sardineBox.SetBox(Max, Min);
		boxContainer.push_back(sardineBox);
	}
	a = 0; //reset a t 0

	//===============Pea and Carrots Variables============//
	newMesh = MeshBuilder::GenerateOBJ("Peas and Carrots can" , "OBJ//canned-food2.obj");
	newMesh->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newMesh->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newMesh->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newMesh->material.kShininess = 8.f;
	newMesh->textureID = LoadTGA("Image//canned_food_2.tga");
	hitBox PnC;
	for(int i = 0; i < 20;i++) //first middle shelf
	{
		Mtx44 newTRS;
		if(i % 5 == 0 && i > 0)
		{
			a += 1;
		}
		newTRS.SetToTranslation(10,4.3,-8+i + a);
		PnCCan.SetData("Peas And Carrots Can", 3.5f, true, newMesh,GEO_PEA_N_CARROTS,newTRS,false);
		Container.push_back(PnCCan);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+0.59,newTRS.a[13]+0.7,newTRS.a[14]+0.35);
		Min.Set(-0.59+newTRS.a[12],-0.1+newTRS.a[13],-0.35+newTRS.a[14]);
		PnC.SetBox(Max, Min);
		boxContainer.push_back(PnC);
	}
	a = 0;

	for(int i = 0; i < 20;i++) //BACK MIDDLE SHELF Back row
	{
		Mtx44 newTRS;
		if(i % 5 == 0 && i > 0)
		{
			a += 1;
		}
		newTRS.SetToTranslation(12,4.3,-8+i + a);
		PnCCan.SetData("Peas And Carrots Can", 3.5f, true, newMesh,GEO_PEA_N_CARROTS,newTRS,false);
		Container2.push_back(PnCCan);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+0.59,newTRS.a[13]+0.7,newTRS.a[14]+0.35);
		Min.Set(-0.59+newTRS.a[12],-0.7+newTRS.a[13],-0.35+newTRS.a[14]);
		PnC.SetBox(Max, Min);
		boxContainer2.push_back(PnC);
	}
	a = 0;

	//==========================SECOND FLOOR BACK=================//
	for(int i = 0; i < 65;i++)
	{
		Mtx44 newTRS;
		if(i % 5 == 0 && i > 0) //When i mod 5 == 0, it will create a spacing 
		{
			a += 1;
		}
		if (i % 25 == 0 && i == 25 ||
			i % 40 == 0 && i == 40)
		{
			a += 18;
		}
		newTRS.SetToTranslation(24.5,25.2,-68+i + a);
		PnCCan.SetData("Peas And Carrots Can", 3.5f, true, newMesh,GEO_PEA_N_CARROTS,newTRS,false);
		Container2.push_back(PnCCan);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+1,newTRS.a[13]+0.7,newTRS.a[14]+0.35);
		Min.Set(-1.5+newTRS.a[12],-0.7+newTRS.a[13],-0.35+newTRS.a[14]);
		PnC.SetBox(Max, Min);
		boxContainer2.push_back(PnC);
	}
	a = 0;

	//==========================SECOND FLOOR FRONT=================//
	for(int i = 0; i < 65;i++)
	{
		Mtx44 newTRS;
		if(i % 5 == 0 && i > 0)
		{
			a += 1;
		}
		if (i % 25 == 0 && i == 25 ||
			i % 40 == 0 && i == 40)
		{
			a += 18;
		}
		newTRS.SetToTranslation(21.5,25.2,-68+i + a);
		PnCCan.SetData("Peas And Carrots Can", 3.5f, true, newMesh,GEO_PEA_N_CARROTS,newTRS,false);
		Container.push_back(PnCCan);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+1,newTRS.a[13]+0.7,newTRS.a[14]+0.35);
		Min.Set(-1.5+newTRS.a[12],-0.1+newTRS.a[13],-0.35+newTRS.a[14]);
		PnC.SetBox(Max, Min);
		boxContainer.push_back(PnC);
	}
	a = 0;

	//==========================SECOND FLOOR FRONT 1ST ROW=================//
	for(int i = 0; i < 65;i++)
	{
		Mtx44 newTRS;
		if(i % 5 == 0 && i > 0) //When i mod 5 == 0, it will create a spacing 
		{
			a += 1;
		}
		if (i % 25 == 0 && i == 25 ||
			i % 40 == 0 && i == 40)
		{
			a += 18;
		}
		newTRS.SetToTranslation(-16,25.2,-68+i + a);
		PnCCan.SetData("Peas And Carrots Can", 3.5f, true, newMesh,GEO_PEA_N_CARROTS,newTRS,false);
		Container.push_back(PnCCan);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+1,newTRS.a[13]+0.7,newTRS.a[14]+0.35);
		Min.Set(-1.5+newTRS.a[12],-0.1+newTRS.a[13],-0.35+newTRS.a[14]);
		PnC.SetBox(Max, Min);
		boxContainer.push_back(PnC);
	}
	a = 0;

	//==========================SECOND FLOOR FRONT 1ST ROW=================//
	for(int i = 0; i < 65;i++)
	{
		Mtx44 newTRS;
		if(i % 5 == 0 && i > 0) //When i mod 5 == 0, it will create a spacing 
		{
			a += 1;
		}
		if (i % 25 == 0 && i == 25 ||
			i % 40 == 0 && i == 40)
		{
			a += 18;
		}
		newTRS.SetToTranslation(-13,25.2,-68+i + a);
		PnCCan.SetData("Peas And Carrots Can", 3.5f, true, newMesh,GEO_PEA_N_CARROTS,newTRS,false);
		Container.push_back(PnCCan);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+1,newTRS.a[13]+0.7,newTRS.a[14]+0.35);
		Min.Set(-1.5+newTRS.a[12],-0.1+newTRS.a[13],-0.35+newTRS.a[14]);
		PnC.SetBox(Max, Min);
		boxContainer.push_back(PnC);
	}
	a = 0;

	//===============Baked Beans Variables============//
	newMesh = MeshBuilder::GenerateOBJ("Baked Beans Can" , "OBJ//canned-food3.obj");
	newMesh->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newMesh->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newMesh->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newMesh->material.kShininess = 8.f;
	newMesh->textureID = LoadTGA("Image//canned_food_3.tga");
	hitBox BB;
	for(int i = 0; i < 20;i++)
	{
		Mtx44 newTRS;
		if(i % 5 == 0 && i > 0)
		{
			a += 1;
		}
		newTRS.SetToTranslation(10,2.3,-8+i + a);
		BBCan.SetData("Baked Beans Can", 3.5f, true, newMesh,GEO_BAKED_BEANS_CAN,newTRS,false);
		Container.push_back(BBCan);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+1,newTRS.a[13]+0.7,newTRS.a[14]+0.35);
		Min.Set(-1.5+newTRS.a[12],-0.7+newTRS.a[13],-0.35+newTRS.a[14]);
		BB.SetBox(Max, Min);
		boxContainer.push_back(BB);
	}
	a = 0;

	for(int i = 0; i < 20;i++)
	{
		Mtx44 newTRS;
		if(i % 5 == 0 && i > 0)
		{
			a += 1;
		}
		newTRS.SetToTranslation(12,2.3,-8+i + a);
		BBCan.SetData("Baked Beans Can", 3.5f, true, newMesh,GEO_BAKED_BEANS_CAN,newTRS,false);
		Container2.push_back(BBCan);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+1,newTRS.a[13]+0.7,newTRS.a[14]+0.35);
		Min.Set(-1.5+newTRS.a[12],-0.7+newTRS.a[13],-0.35+newTRS.a[14]);
		BB.SetBox(Max, Min);
		boxContainer2.push_back(BB);
	}
	a = 0;

	//============== SECOND FLOOR BACK================//
	for(int i = 0; i < 65;i++)
	{
		Mtx44 newTRS;
		if(i % 5 == 0 && i > 0) //When i mod 5 == 0, it will create a spacing 
		{
			a += 1;
		}
		if (i % 25 == 0 && i == 25 ||
			i % 40 == 0 && i == 40)
		{
			a += 18;
		}
		newTRS.SetToTranslation(24.5,23.3,-68+i + a);
		BBCan.SetData("Baked Beans Can", 3.5f, true, newMesh,GEO_BAKED_BEANS_CAN,newTRS,false);
		Container2.push_back(BBCan);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+1,newTRS.a[13]+0.7,newTRS.a[14]+0.35);
		Min.Set(-1.5+newTRS.a[12],-0.7+newTRS.a[13],-0.35+newTRS.a[14]);
		BB.SetBox(Max, Min);
		boxContainer2.push_back(BB);
	}
	a = 0;

	//============== SECOND FLOOR FRONT================//
	for(int i = 0; i < 65;i++)
	{
		Mtx44 newTRS;
		if(i % 5 == 0 && i > 0)
		{
			a += 1;
		}
		if (i % 25 == 0 && i == 25 ||
			i % 40 == 0 && i == 40)
		{
			a += 18;
		}
		newTRS.SetToTranslation(21.5,23.3,-68+i + a);
		BBCan.SetData("Baked Beans Can", 3.5f, true, newMesh,GEO_BAKED_BEANS_CAN,newTRS,false);
		Container.push_back(BBCan);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+1,newTRS.a[13]+0.7,newTRS.a[14]+0.35);
		Min.Set(-1.5+newTRS.a[12],-0.7+newTRS.a[13],-0.35+newTRS.a[14]);
		BB.SetBox(Max, Min);
		boxContainer.push_back(BB);
	}
	a = 0;

	//============== SECOND FLOOR FRONT 1ST ROW================//
	for(int i = 0; i < 65;i++)
	{
		Mtx44 newTRS;
		if(i % 5 == 0 && i > 0) //When i mod 5 == 0, it will create a spacing 
		{
			a += 1;
		}
		if (i % 25 == 0 && i == 25 ||
			i % 40 == 0 && i == 40)
		{
			a += 18;
		}
		newTRS.SetToTranslation(-16,23.3,-68+i + a);
		BBCan.SetData("Baked Beans Can", 3.5f, true, newMesh,GEO_BAKED_BEANS_CAN,newTRS,false);
		Container.push_back(BBCan);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+1,newTRS.a[13]+0.7,newTRS.a[14]+0.35);
		Min.Set(-1.5+newTRS.a[12],-0.7+newTRS.a[13],-0.35+newTRS.a[14]);
		BB.SetBox(Max, Min);
		boxContainer.push_back(BB);
	}
	a = 0;

	//============== SECOND FLOOR BACK 1ST ROW================//
	for(int i = 0; i < 65;i++)
	{
		Mtx44 newTRS;
		if(i % 5 == 0 && i > 0) //When i mod 5 == 0, it will create a spacing 
		{
			a += 1;
		}
		if (i % 25 == 0 && i == 25 ||
			i % 40 == 0 && i == 40)
		{
			a += 18;
		}
		newTRS.SetToTranslation(-13,23.3,-68+i + a);
		BBCan.SetData("Baked Beans Can", 3.5f, true, newMesh,GEO_BAKED_BEANS_CAN,newTRS,false);
		Container2.push_back(BBCan);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+1,newTRS.a[13]+0.7,newTRS.a[14]+0.35);
		Min.Set(-1.5+newTRS.a[12],-0.7+newTRS.a[13],-0.35+newTRS.a[14]);
		BB.SetBox(Max, Min);
		boxContainer2.push_back(BB);
	}
	a = 0;

	//===============Coke Can Variables============//
	newMesh = MeshBuilder::GenerateOBJ("Coke" , "OBJ//drink-can1.obj");
	newMesh->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newMesh->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newMesh->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newMesh->material.kShininess = 8.f;
	newMesh ->textureID = LoadTGA("Image//drink_can1.tga");
	hitBox Coke;
	for(int i = 0; i < 100;i++)
	{
		Mtx44 newTRS;
		if(i % 10 == 0 && i > 0)
		{
			a += 4;
		}
		newTRS.SetToTranslation(51.5, 4.69,-74+i + a);
		CokeCan.SetData("Coke", 3.5f, true, newMesh, GEO_COKE_CAN,newTRS,false);
		Container3.push_back(CokeCan);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+1,newTRS.a[13]+0.7,newTRS.a[14]+0.5);
		Min.Set(-1+newTRS.a[12],-0.7+newTRS.a[13],-0.5+newTRS.a[14]);
		Coke.SetBox(Max, Min);
		boxContainer3.push_back(Coke);
	}
	a = 0;

	//===============Frozen Pizza Variables============//
	newMesh = MeshBuilder::GenerateOBJ("Pizza" , "OBJ//frozenpizza.obj");
	newMesh->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newMesh->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newMesh->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newMesh->material.kShininess = 8.f;
	newMesh ->textureID = LoadTGA("Image//frozen_pizza.tga");
	hitBox Pizza;
	for(int i = 0; i < 120; i += 3)
	{
		Mtx44 newTRS;
		if(i % 12 == 0 && i > 0)
		{
			a += 2;
		}
		newTRS.SetToTranslation(51.2, 2.7,-75+i + a);
		PizzaBox.SetData("Frozen Pizza", 3.5f, true, newMesh, GEO_PIZZABOX,newTRS,false);
		Container3.push_back(PizzaBox);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12],newTRS.a[13]+0.8,newTRS.a[14]+1);
		Min.Set(-3+newTRS.a[12],-0.5+newTRS.a[13],-2+newTRS.a[14]);
		Pizza.SetBox(Max, Min);
		boxContainer3.push_back(Pizza);
	}
	a = 0;

	//===========================SECOND FLOOR FRONT MIDDLE ROW BACK================//
	for(int i = 0; i < 108; i += 3)
	{
		Mtx44 newTRS;
		if(i % 12 == 0 && i > 0)
		{
			a += 2;
		}
		newTRS.SetToTranslation(-51.8,23.8,-74.5+i + a);
		PizzaBox.SetData("Frozen Pizza", 3.5f, true, newMesh, GEO_PIZZABOX,newTRS,false);
		Container13.push_back(PizzaBox);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+1,newTRS.a[13]+0.5,newTRS.a[14]+1);
		Min.Set(-1.5+newTRS.a[12],-0.5+newTRS.a[13],-2+newTRS.a[14]);
		Pizza.SetBox(Max, Min);
		boxContainer13.push_back(Pizza);
	}
	a = 0; //reset a t 0

	//===========================SECOND FLOOR FRONT MIDDLE ROW BACK================//
	for(int i = 0; i < 108; i += 3)
	{
		Mtx44 newTRS;
		if(i % 12 == 0 && i > 0)
		{
			a += 2;
		}
		newTRS.SetToTranslation(-51.8,25.5,-74.5+i + a);
		PizzaBox.SetData("Frozen Pizza", 3.5f, true, newMesh, GEO_PIZZABOX,newTRS,false);
		Container13.push_back(PizzaBox);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12] + 1,newTRS.a[13]+0.5,newTRS.a[14]+2);
		Min.Set(-1.5+newTRS.a[12],-0.5+newTRS.a[13],-2+newTRS.a[14]);
		Pizza.SetBox(Max, Min);
		boxContainer13.push_back(Pizza);
	}
	a = 0; //reset a t 0

	//===============Coke Zero Can Variables============//
	newMesh = MeshBuilder::GenerateOBJ("Coke" , "OBJ//drink-can2.obj");
	newMesh->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newMesh->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newMesh->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newMesh->material.kShininess = 8.f;
	newMesh ->textureID = LoadTGA("Image//drink_can2.tga");
	hitBox CokeZero;
	for(int i = 0; i < 50;i++)
	{
		Mtx44 newTRS;
		if(i % 10 == 0 && i > 0)
		{
			a += 4;
		}
		newTRS.SetToTranslation(-33 +i + a, 4.7,-90);
		CokeZeroCan.SetData("Coke Zero", 3.5f, true, newMesh, GEO_DRINKCAN2,newTRS,false);
		Container4.push_back(CokeZeroCan);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+0.59,newTRS.a[13]+0.7,newTRS.a[14]+0.35);
		Min.Set(-0.59+newTRS.a[12],-0.7+newTRS.a[13],-0.35+newTRS.a[14]);
		CokeZero.SetBox(Max, Min);
		boxContainer4.push_back(CokeZero);
	}
	a = 0;

	newMesh = MeshBuilder::GenerateOBJ("Coke" , "OBJ//drink-can3.obj");
	newMesh->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newMesh->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newMesh->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newMesh->material.kShininess = 8.f;
	newMesh ->textureID = LoadTGA("Image//drink_can3.tga");
	hitBox Pepsi;
	for(int i = 0; i < 50;i++)
	{
		Mtx44 newTRS;
		if(i % 10 == 0 && i > 0)
		{
			a += 4;
		}
		newTRS.SetToTranslation(-33 +i + a, 2.8,-90);
		PepsiCan.SetData("Pepsi", 3.5f, true, newMesh, GEO_PEPSI_CAN,newTRS,false);
		Container4.push_back(PepsiCan);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+0.59,newTRS.a[13]+0.7,newTRS.a[14]+0.35);
		Min.Set(-0.59+newTRS.a[12],-0.7+newTRS.a[13],-0.35+newTRS.a[14]);
		Pepsi.SetBox(Max, Min);
		boxContainer4.push_back(Pepsi);
	}
	a = 0;

	//===============Cereal Box 1 Variables============//
	newMesh = MeshBuilder::GenerateOBJ("Cereal Box 1" , "OBJ//cereal-box1.obj");
	newMesh->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newMesh->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newMesh->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newMesh->material.kShininess = 8.f;
	newMesh ->textureID = LoadTGA("Image//Cereal-box1.tga");
	hitBox cereal1;
	for(int i = 0; i < 45;i++)
	{
		Mtx44 newTRS;
		if(i % 5 == 0 && i > 0)
		{
			a += 1;
		}
		newTRS.SetToTranslation(-32 +i + a, 4.3,-56.7);
		cerealBox1.SetData("Bran Buds Cereal", 3.5f, true, newMesh, GEO_CEREALBOX1,newTRS,false);
		Container5.push_back(cerealBox1);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+0.5, newTRS.a[13]+2,newTRS.a[14]+1);
		Min.Set(-0.5+newTRS.a[12],-1+newTRS.a[13],-1+newTRS.a[14]);
		cereal1.SetBox(Max, Min);
		boxContainer5.push_back(cereal1);
	}
	a = 0;

	for(int i = 0; i < 45;i++) // Left shelf Back Row
	{
		Mtx44 newTRS;
		if(i % 5 == 0 && i > 0)
		{
			a += 1;
		}
		newTRS.SetToTranslation(-32 +i + a, 4.3,-59.5);
		cerealBox1.SetData("Bran Buds Cereal", 3.5f, true, newMesh, GEO_CEREALBOX1,newTRS,false);
		Container6.push_back(cerealBox1);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+0.5,newTRS.a[13]+2,newTRS.a[14]+1);
		Min.Set(-0.5+newTRS.a[12],-1+newTRS.a[13],-1+newTRS.a[14]);
		cereal1.SetBox(Max, Min);
		boxContainer6.push_back(cereal1);
	}
	a = 0;

	for(int i = 0; i < 45;i++) // Right shelf Front Row
	{
		Mtx44 newTRS;
		if(i % 5 == 0 && i > 0)
		{
			a += 1;
		}
		newTRS.SetToTranslation(-32 +i + a, 4.3,56.5);
		cerealBox1.SetData("Bran Buds Cereal", 3.5f, true, newMesh, GEO_CEREALBOX1,newTRS,false);
		Container7.push_back(cerealBox1);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+0.5,newTRS.a[13]+2,newTRS.a[14]+1);
		Min.Set(-0.5+newTRS.a[12],-1+newTRS.a[13],-1+newTRS.a[14]);
		cereal1.SetBox(Max, Min);
		boxContainer7.push_back(cereal1);
	}
	a = 0;

	for(int i = 0; i < 45;i++) // Right shelf Back Row
	{
		Mtx44 newTRS;
		if(i % 5 == 0 && i > 0)
		{
			a += 1;
		}
		newTRS.SetToTranslation(-32 +i + a, 4.3,59.5);
		cerealBox1.SetData("Bran Buds Cereal", 3.5f, true, newMesh, GEO_CEREALBOX1,newTRS,false);
		Container8.push_back(cerealBox1);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+0.5,newTRS.a[13]+2,newTRS.a[14]+1);
		Min.Set(-0.5+newTRS.a[12],-1+newTRS.a[13],-1+newTRS.a[14]);
		cereal1.SetBox(Max, Min);
		boxContainer8.push_back(cereal1);
	}
	a = 0;

	//===============Cereal Box 2 Variables============//
	newMesh = MeshBuilder::GenerateOBJ("Cereal Box 2" , "OBJ//cereal-box2.obj");
	newMesh->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newMesh->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newMesh->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newMesh->material.kShininess = 8.f;
	newMesh ->textureID = LoadTGA("Image//cereal_box2.tga");
	hitBox cereal2;
	for(int i = 0; i < 45;i++)
	{
		Mtx44 newTRS;
		if(i % 5 == 0 && i > 0)
		{
			a += 1;
		}
		newTRS.SetToTranslation(-32 +i + a, 2.3f,-56.7f);
		cerealBox2.SetData("Morning Chips Cereal", 3.5f, true, newMesh, GEO_CEREALBOX2,newTRS,false);
		Container5.push_back(cerealBox2);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+0.5,newTRS.a[13]+2,newTRS.a[14]+1);
		Min.Set(-0.5+newTRS.a[12],-1+newTRS.a[13],-1+newTRS.a[14]);
		cereal2.SetBox(Max, Min);
		boxContainer5.push_back(cereal2);
	}
	a = 0;



	for(int i = 0; i < 45;i++)//Left Shwlf Back Row
	{
		Mtx44 newTRS;
		if(i % 5 == 0 && i > 0)
		{
			a += 1;
		}
		newTRS.SetToTranslation(-32 +i + a, 2.3,-59.5);
		cerealBox2.SetData("Morning Chips Cereal", 3.5f, true, newMesh, GEO_CEREALBOX2,newTRS,false);
		Container6.push_back(cerealBox2);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+0.5,newTRS.a[13]+2,newTRS.a[14]+1);
		Min.Set(-0.5+newTRS.a[12],-1+newTRS.a[13],-1+newTRS.a[14]);
		cereal2.SetBox(Max, Min);
		boxContainer6.push_back(cereal2);
	}
	a = 0;

	for(int i = 0; i < 45;i++)//Right Shwlf Back Row
	{
		Mtx44 newTRS;
		if(i % 5 == 0 && i > 0)
		{
			a += 1;
		}
		newTRS.SetToTranslation(-32 +i + a, 2.3,59.5);
		cerealBox2.SetData("Morning Chips Cereal", 3.5f, true, newMesh, GEO_CEREALBOX2,newTRS,false);
		Container8.push_back(cerealBox2);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+0.5,newTRS.a[13]+2,newTRS.a[14]+1);
		Min.Set(-0.5+newTRS.a[12],-1+newTRS.a[13],-1+newTRS.a[14]);
		cereal2.SetBox(Max, Min);
		boxContainer8.push_back(cereal2);
	}
	a = 0;

	for(int i = 0; i < 45;i++)//Right Shwlf Front Row
	{
		Mtx44 newTRS;
		if(i % 5 == 0 && i > 0)
		{
			a += 1;
		}
		newTRS.SetToTranslation(-32 +i + a, 2.3,56.5);
		cerealBox2.SetData("Morning Chips Cereal", 3.5f, true, newMesh, GEO_CEREALBOX2,newTRS,false);
		Container7.push_back(cerealBox2);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+0.5,newTRS.a[13]+0.7,newTRS.a[14]+1);
		Min.Set(-0.5+newTRS.a[12],-0.7+newTRS.a[13],-1+newTRS.a[14]);
		cereal2.SetBox(Max, Min);
		boxContainer7.push_back(cereal2);
	}
	a = 0;

	//===============Potato CHip Variables============//
	newMesh = MeshBuilder::GenerateOBJ("Potato Chip" , "OBJ//potato-chips.obj");
	newMesh->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newMesh->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newMesh->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newMesh->material.kShininess = 8.f;
	newMesh->textureID = LoadTGA("Image//potato_chips.tga");
	hitBox PC;
	for(int i = 0; i < 40;i++) //Potato Top Shelves Left
	{
		Mtx44 newTRS;
		if(i % 10 == 0 && i > 0)
		{
			a += 2;
		}
		newTRS.SetToTranslation(-28.5 +i + a, 5,-35);
		PotatoChip.SetData("Lays Potato Chips", 3.5f, true, newMesh, GEO_POTATOCHIPS,newTRS,false);
		Container9.push_back(PotatoChip);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+0.59,newTRS.a[13]+2,newTRS.a[14]+0.35);
		Min.Set(-0.59+newTRS.a[12],+newTRS.a[13],-0.35+newTRS.a[14]);
		PC.SetBox(Max, Min);
		boxContainer9.push_back(PC);
	}
	a = 0;

	for(int i = 0; i < 40;i++)
	{
		Mtx44 newTRS;
		if(i % 10 == 0 && i > 0) //Potato Bottom Shelves Left
		{
			a += 2;
		}
		newTRS.SetToTranslation(-28.5 +i + a, 2.3,-35);
		PotatoChip.SetData("Lays Potato Chips", 3.5f, true, newMesh, GEO_POTATOCHIPS,newTRS,false);
		Container9.push_back(PotatoChip);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+0.59,newTRS.a[13]+2,newTRS.a[14]+0.35);
		Min.Set(-0.59+newTRS.a[12],+newTRS.a[13],-0.35+newTRS.a[14]);
		PC.SetBox(Max, Min);
		boxContainer9.push_back(PC);
	}
	a = 0;

	for(int i = 0; i < 40;i++) //Potato Top Shelves Right
	{
		Mtx44 newTRS;
		if(i % 10 == 0 && i > 0)
		{
			a += 2;
		}
		newTRS.SetToTranslation(-28.5 +i + a, 5,33);
		PotatoChip.SetData("Lays Potato Chips", 3.5f, true, newMesh, GEO_POTATOCHIPS,newTRS,false);
		Container10.push_back(PotatoChip);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+0.59,newTRS.a[13]+2,newTRS.a[14]+0.35);
		Min.Set(-0.59+newTRS.a[12],+newTRS.a[13],-0.35+newTRS.a[14]);
		PC.SetBox(Max, Min);
		boxContainer10.push_back(PC);
	}
	a = 0;

	for(int i = 0; i < 40;i++) //Potato bottom  Shelves Right
	{
		Mtx44 newTRS;
		if(i % 10 == 0 && i > 0)
		{
			a += 2;
		}
		newTRS.SetToTranslation(-28.5 +i + a, 2.3,33);
		PotatoChip.SetData("Lays Potato Chips", 3.5f, true, newMesh, GEO_POTATOCHIPS,newTRS,false);
		Container10.push_back(PotatoChip);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+0.59,newTRS.a[13]+2,newTRS.a[14]+0.35);
		Min.Set(-0.59+newTRS.a[12],+newTRS.a[13],-0.35+newTRS.a[14]);
		PC.SetBox(Max, Min);
		boxContainer10.push_back(PC);
	}
	a = 0;

	//===========================SECOND FLOOR FRONT MIDDLE ROW================//
	for(int i = 0; i < 50;i++)
	{
		Mtx44 newTRS;
		if(i % 10 == 0 && i > 0 && i != 20 && i != 30) //When i mod 5 == 0, it will create a spacing 
		{
			a += 2;
		}
		if (i % 20 == 0 && i == 20 ||
			i % 30 == 0 && i == 30)
		{
			a += 26;
		}
		newTRS.SetToTranslation(3.2,25.8,-64.8+i + a);
		PotatoChip.SetData("Lays Potato Chips", 3.5f, true, newMesh, GEO_POTATOCHIPS,newTRS,false);
		Container13.push_back(PotatoChip);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+0.59,newTRS.a[13]+2,newTRS.a[14]+0.35);
		Min.Set(-0.59+newTRS.a[12],+newTRS.a[13],-0.35+newTRS.a[14]);
		PC.SetBox(Max, Min);
		boxContainer13.push_back(PC);
	}
	a = 0; //reset a t 0

	//===========================SECOND FLOOR FRONT MIDDLE ROW================//
	for(int i = 0; i < 50;i++)
	{
		Mtx44 newTRS;
		if(i % 10 == 0 && i > 0 && i != 20 && i != 30) //When i mod 5 == 0, it will create a spacing 
		{
			a += 2;
		}
		if (i % 20 == 0 && i == 20 ||
			i % 30 == 0 && i == 30)
		{
			a += 26;
		}
		newTRS.SetToTranslation(3.2,23,-64.8+i + a);
		PotatoChip.SetData("Lays Potato Chips", 3.5f, true, newMesh, GEO_POTATOCHIPS,newTRS,false);
		Container13.push_back(PotatoChip);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+0.59,newTRS.a[13]+2,newTRS.a[14]+0.35);
		Min.Set(-0.59+newTRS.a[12],+newTRS.a[13],-0.35+newTRS.a[14]);
		PC.SetBox(Max, Min);
		boxContainer13.push_back(PC);
	}
	a = 0; //reset a t 0

	//===========================SECOND FLOOR FRONT MIDDLE ROW BACK================//
	for(int i = 0; i < 50;i++)
	{
		Mtx44 newTRS;
		if(i % 10 == 0 && i > 0 && i != 20 && i != 30) //When i mod 5 == 0, it will create a spacing 
		{
			a += 2;
		}
		if (i % 20 == 0 && i == 20 ||
			i % 30 == 0 && i == 30)
		{
			a += 26;
		}
		newTRS.SetToTranslation(5.5,25.8,-64.8+i + a);
		PotatoChip.SetData("Lays Potato Chips", 3.5f, true, newMesh, GEO_POTATOCHIPS,newTRS,false);
		Container13.push_back(PotatoChip);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+0.59,newTRS.a[13]+2,newTRS.a[14]+0.35);
		Min.Set(-0.59+newTRS.a[12],+newTRS.a[13],-0.35+newTRS.a[14]);
		PC.SetBox(Max, Min);
		boxContainer13.push_back(PC);
	}
	a = 0; //reset a t 0

	//===========================SECOND FLOOR FRONT MIDDLE ROW BACK================//
	for(int i = 0; i < 50;i++)
	{
		Mtx44 newTRS;
		if(i % 10 == 0 && i > 0 && i != 20 && i != 30) //When i mod 5 == 0, it will create a spacing 
		{
			a += 2;
		}
		if (i % 20 == 0 && i == 20 ||
			i % 30 == 0 && i == 30)
		{
			a += 26;
		}
		newTRS.SetToTranslation(5.5,23,-64.8+i + a);
		PotatoChip.SetData("Lays Potato Chips", 3.5f, true, newMesh, GEO_POTATOCHIPS,newTRS,false);
		Container13.push_back(PotatoChip);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+0.59,newTRS.a[13]+2,newTRS.a[14]+0.35);
		Min.Set(-0.59+newTRS.a[12],+newTRS.a[13],-0.35+newTRS.a[14]);
		PC.SetBox(Max, Min);
		boxContainer13.push_back(PC);
	}
	a = 0; //reset a t 0

	//===============Milo Cam Variables============//
	newMesh = MeshBuilder::GenerateOBJ("Milo Can" , "OBJ//milocan.obj");
	newMesh->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newMesh->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newMesh->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newMesh->material.kShininess = 8.f;
	newMesh->textureID = LoadTGA("Image//milocan.tga");
	hitBox MC;
	for(int i = 0; i < 54; i += 2) //Milo front Shelves Left
	{
		Mtx44 newTRS;
		if(i % 3 == 0 && i > 0)
		{
			a += 0.5;
		}
		newTRS.SetToTranslation(-32 +i + a, 6.3,-57);
		MiloCan.SetData("Milo Can", 3.5f, true, newMesh, GEO_MILOCAN,newTRS,false);
		Container11.push_back(MiloCan);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+0.59,newTRS.a[13]+2,newTRS.a[14]+1);
		Min.Set(-0.59+newTRS.a[12],+newTRS.a[13],-1+newTRS.a[14]);
		MC.SetBox(Max, Min);
		boxContainer11.push_back(MC);
	}
	a = 0;

	for(int i = 0; i < 54; i += 2) //Milo back Shelves Right
	{
		Mtx44 newTRS;
		if(i % 3 == 0 && i > 0)
		{
			a += 0.5;
		}
		newTRS.SetToTranslation(-32 +i + a, 6.3, 59);
		MiloCan.SetData("Milo Can", 3.5f, true, newMesh, GEO_MILOCAN,newTRS,false);
		Container11.push_back(MiloCan);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+0.59,newTRS.a[13]+2,newTRS.a[14]+1);
		Min.Set(-0.59+newTRS.a[12],+newTRS.a[13],-1+newTRS.a[14]);
		MC.SetBox(Max, Min);
		boxContainer11.push_back(MC);
	}
	a = 0;

	for(int i = 0; i < 54; i += 2) //Milo back Shelves Left
	{
		Mtx44 newTRS;
		if(i % 3 == 0 && i > 0)
		{
			a += 0.5;
		}
		newTRS.SetToTranslation(-32 +i + a, 6.3,-59.3);
		MiloCan.SetData("Milo Can", 3.5f, true, newMesh, GEO_MILOCAN,newTRS,false);
		Container12.push_back(MiloCan);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+0.59,newTRS.a[13]+2,newTRS.a[14]+1);
		Min.Set(-0.59+newTRS.a[12],+newTRS.a[13],-1+newTRS.a[14]);
		MC.SetBox(Max, Min);
		boxContainer12.push_back(MC);
	}
	a = 0;

	for(int i = 0; i < 54; i += 2) //Milo back Shelves Left
	{
		Mtx44 newTRS;
		if(i % 3 == 0 && i > 0)
		{
			a += 0.5;
		}
		newTRS.SetToTranslation(-32 +i + a, 6.3,57);
		MiloCan.SetData("Milo Can", 3.5f, true, newMesh, GEO_MILOCAN,newTRS,false);
		Container12.push_back(MiloCan);
		Vector3 Min, Max;
		Max.Set(newTRS.a[12]+0.59,newTRS.a[13]+2,newTRS.a[14]+1);
		Min.Set(-0.59+newTRS.a[12],+newTRS.a[13],-1+newTRS.a[14]);
		MC.SetBox(Max, Min);
		boxContainer12.push_back(MC);
	}
	a = 0;

	/*meshList[GEO_MILOCAN] = MeshBuilder::GenerateOBJ("Railing" , "OBJ//milocan.obj");
	meshList[GEO_MILOCAN]->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	meshList[GEO_MILOCAN]->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	meshList[GEO_MILOCAN]->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	meshList[GEO_MILOCAN]->material.kShininess = 8.f;
	meshList[GEO_MILOCAN] ->textureID = LoadTGA("Image//milocan.tga");*/

	//variable to animate model
	rotateRightArms = rotateLeftArms = rotateRightLeg = rotateLeftLeg = 360;
	movingModel = false;
	movingCharacterX = movingCharacterZ = 0;
	//===money related variables===//
	translateMoneyZ = 0;
	translateMoneyY = 0;

	Framerate = "FPS: ";
}
/******************************************************************************/
/*!
\brief
Initializes the Shaders for the scene
*/
/******************************************************************************/
void StudioProject::InitShaders()
{
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

	// Light3
	m_parameters[U_LIGHT2_POSITION] = glGetUniformLocation(m_programID, "lights[2].position_cameraspace");
	m_parameters[U_LIGHT2_COLOR] = glGetUniformLocation(m_programID, "lights[2].color");
	m_parameters[U_LIGHT2_POWER] = glGetUniformLocation(m_programID, "lights[2].power");
	m_parameters[U_LIGHT2_KC] = glGetUniformLocation(m_programID, "lights[2].kC");
	m_parameters[U_LIGHT2_KL] = glGetUniformLocation(m_programID, "lights[2].kL");
	m_parameters[U_LIGHT2_KQ] = glGetUniformLocation(m_programID, "lights[2].kQ");
	m_parameters[U_LIGHT2_TYPE] = glGetUniformLocation(m_programID, "lights[2].type");
	m_parameters[U_LIGHT2_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[2].spotDirection");
	m_parameters[U_LIGHT2_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[2].cosCutoff");
	m_parameters[U_LIGHT2_COSINNER] = glGetUniformLocation(m_programID, "lights[2].cosInner");
	m_parameters[U_LIGHT2_EXPONENT] = glGetUniformLocation(m_programID, "lights[2].exponent");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	// Light4
	m_parameters[U_LIGHT3_POSITION] = glGetUniformLocation(m_programID, "lights[3].position_cameraspace");
	m_parameters[U_LIGHT3_COLOR] = glGetUniformLocation(m_programID, "lights[3].color");
	m_parameters[U_LIGHT3_POWER] = glGetUniformLocation(m_programID, "lights[3].power");
	m_parameters[U_LIGHT3_KC] = glGetUniformLocation(m_programID, "lights[3].kC");
	m_parameters[U_LIGHT3_KL] = glGetUniformLocation(m_programID, "lights[3].kL");
	m_parameters[U_LIGHT3_KQ] = glGetUniformLocation(m_programID, "lights[3].kQ");
	m_parameters[U_LIGHT3_TYPE] = glGetUniformLocation(m_programID, "lights[3].type");
	m_parameters[U_LIGHT3_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[3].spotDirection");
	m_parameters[U_LIGHT3_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[3].cosCutoff");
	m_parameters[U_LIGHT3_COSINNER] = glGetUniformLocation(m_programID, "lights[3].cosInner");
	m_parameters[U_LIGHT3_EXPONENT] = glGetUniformLocation(m_programID, "lights[3].exponent");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	// Light5
	m_parameters[U_LIGHT4_POSITION] = glGetUniformLocation(m_programID, "lights[4].position_cameraspace");
	m_parameters[U_LIGHT4_COLOR] = glGetUniformLocation(m_programID, "lights[4].color");
	m_parameters[U_LIGHT4_POWER] = glGetUniformLocation(m_programID, "lights[4].power");
	m_parameters[U_LIGHT4_KC] = glGetUniformLocation(m_programID, "lights[4].kC");
	m_parameters[U_LIGHT4_KL] = glGetUniformLocation(m_programID, "lights[4].kL");
	m_parameters[U_LIGHT4_KQ] = glGetUniformLocation(m_programID, "lights[4].kQ");
	m_parameters[U_LIGHT4_TYPE] = glGetUniformLocation(m_programID, "lights[4].type");
	m_parameters[U_LIGHT4_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[4].spotDirection");
	m_parameters[U_LIGHT4_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[4].cosCutoff");
	m_parameters[U_LIGHT4_COSINNER] = glGetUniformLocation(m_programID, "lights[4].cosInner");
	m_parameters[U_LIGHT4_EXPONENT] = glGetUniformLocation(m_programID, "lights[4].exponent");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	// Light6
	m_parameters[U_LIGHT5_POSITION] = glGetUniformLocation(m_programID, "lights[5].position_cameraspace");
	m_parameters[U_LIGHT5_COLOR] = glGetUniformLocation(m_programID, "lights[5].color");
	m_parameters[U_LIGHT5_POWER] = glGetUniformLocation(m_programID, "lights[5].power");
	m_parameters[U_LIGHT5_KC] = glGetUniformLocation(m_programID, "lights[5].kC");
	m_parameters[U_LIGHT5_KL] = glGetUniformLocation(m_programID, "lights[5].kL");
	m_parameters[U_LIGHT5_KQ] = glGetUniformLocation(m_programID, "lights[5].kQ");
	m_parameters[U_LIGHT5_TYPE] = glGetUniformLocation(m_programID, "lights[5].type");
	m_parameters[U_LIGHT5_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[5].spotDirection");
	m_parameters[U_LIGHT5_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[5].cosCutoff");
	m_parameters[U_LIGHT5_COSINNER] = glGetUniformLocation(m_programID, "lights[5].cosInner");
	m_parameters[U_LIGHT5_EXPONENT] = glGetUniformLocation(m_programID, "lights[5].exponent");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	// Light7
	m_parameters[U_LIGHT6_POSITION] = glGetUniformLocation(m_programID, "lights[6].position_cameraspace");
	m_parameters[U_LIGHT6_COLOR] = glGetUniformLocation(m_programID, "lights[6].color");
	m_parameters[U_LIGHT6_POWER] = glGetUniformLocation(m_programID, "lights[6].power");
	m_parameters[U_LIGHT6_KC] = glGetUniformLocation(m_programID, "lights[6].kC");
	m_parameters[U_LIGHT6_KL] = glGetUniformLocation(m_programID, "lights[6].kL");
	m_parameters[U_LIGHT6_KQ] = glGetUniformLocation(m_programID, "lights[6].kQ");
	m_parameters[U_LIGHT6_TYPE] = glGetUniformLocation(m_programID, "lights[6].type");
	m_parameters[U_LIGHT6_SPOTDIRECTION] = glGetUniformLocation(m_programID, "lights[6].spotDirection");
	m_parameters[U_LIGHT6_COSCUTOFF] = glGetUniformLocation(m_programID, "lights[6].cosCutoff");
	m_parameters[U_LIGHT6_COSINNER] = glGetUniformLocation(m_programID, "lights[6].cosInner");
	m_parameters[U_LIGHT6_EXPONENT] = glGetUniformLocation(m_programID, "lights[6].exponent");
	m_parameters[U_NUMLIGHTS] = glGetUniformLocation(m_programID, "numLights");

	//Text Related
	// Get a handle for our "textColor" uniform
	m_parameters[U_TEXT_ENABLED] = glGetUniformLocation(m_programID, "textEnabled");
	m_parameters[U_TEXT_COLOR] = glGetUniformLocation(m_programID, "textColor");

	glUseProgram(m_programID);

	//Light 1 (BOTTOM CENTER BACK LIGHT )
	lights[0].type = Light::LIGHT_POINT;
	lights[0].position.Set(0,19.5, 0);
	lights[0].color.Set(1, 1, 1);
	lights[0].power = 1;
	lights[0].kC = 1.f;
	lights[0].kL = 0.01f;
	lights[0].kQ = 0.001f;
	lights[0].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[0].cosInner = cos(Math::DegreeToRadian(30));
	lights[0].exponent = 3.f;
	lights[0].spotDirection.Set(0.f, 1.f, 0.f);

	//Light 2 (BOTTOM RIGHT BACK LIGHT)
	lights[1].type = Light::LIGHT_POINT;
	lights[1].position.Set(25,19.5,45);
	lights[1].color.Set(1, 1, 1);
	lights[1].power = 1;
	lights[1].kC = 1.f;
	lights[1].kL = 0.01f;
	lights[1].kQ = 0.001f;
	lights[1].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[1].cosInner = cos(Math::DegreeToRadian(30));
	lights[1].exponent = 3.f;
	lights[1].spotDirection.Set(0.f, 5.f, 0.f);

	//Lights3 (BOTTOM LEFT BACK LIGHT)
	lights[2].type = Light::LIGHT_POINT;
	lights[2].position.Set(25,19.5,-60);
	lights[2].color.Set(1, 1, 1);
	lights[2].power = 1;
	lights[2].kC = 1.f;
	lights[2].kL = 0.01;
	lights[2].kQ = 0.001f;
	lights[2].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[2].cosInner = cos(Math::DegreeToRadian(30));
	lights[2].exponent = 3.f;
	lights[2].spotDirection.Set(1.f, 1.f, 0.f);

	//Lights4 (BOTTOM LEFT FRONT LIGHT)
	lights[3].type = Light::LIGHT_POINT;
	lights[3].position.Set(-25,19.5,-60);
	lights[3].color.Set(1, 1, 1);
	lights[3].power = 1;
	lights[3].kC = 1.f;
	lights[3].kL = 0.01;
	lights[3].kQ = 0.001f;
	lights[3].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[3].cosInner = cos(Math::DegreeToRadian(30));
	lights[3].exponent = 3.f;
	lights[3].spotDirection.Set(1.f, 1.f, 0.f);


	//Lights5 (BOTTOM RIGHT FRONT LIGHT)
	lights[4].type = Light::LIGHT_POINT;
	lights[4].position.Set(-25,19.5,45);
	lights[4].color.Set(1, 1, 1);
	lights[4].power = 1;
	lights[4].kC = 1.f;
	lights[4].kL = 0.01;
	lights[4].kQ = 0.001f;
	lights[4].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[4].cosInner = cos(Math::DegreeToRadian(30));
	lights[4].exponent = 3.f;
	lights[4].spotDirection.Set(1.f, 1.f, 0.f);

	//Lights6 (BOTTOM CENTER FRONT LIGHT)
	lights[5].type = Light::LIGHT_POINT;
	lights[5].position.Set(-135,100, 0);
	lights[5].color.Set(1, 1, 1);
	lights[5].power = 8;
	lights[5].kC = 1.f;
	lights[5].kL = 0.01;
	lights[5].kQ = 0.001f;
	lights[5].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[5].cosInner = cos(Math::DegreeToRadian(30));
	lights[5].exponent = 3.f;
	lights[5].spotDirection.Set(1.f, 1.f, 0.f);

	//Lights7 (TOP CENTER FRONT LIGHT)
	lights[6].type = Light::LIGHT_POINT;
	lights[6].position.Set(4,38, -30);
	lights[6].color.Set(1, 1, 1);
	lights[6].power = 0.2;
	lights[6].kC = 1.f;
	lights[6].kL = 0.01;
	lights[6].kQ = 0.001f;
	lights[6].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[6].cosInner = cos(Math::DegreeToRadian(30));
	lights[6].exponent = 3.f;
	lights[6].spotDirection.Set(1.f, 1.f, 0.f);

	//Lights8 (TOP CENTER  LIGHT)
	lights[7].type = Light::LIGHT_POINT;
	lights[7].position.Set(4,38, -4);
	lights[7].color.Set(1, 1, 1);
	lights[7].power = 0.2;
	lights[7].kC = 1.f;
	lights[7].kL = 0.01;
	lights[7].kQ = 0.001f;
	lights[7].cosCutoff = cos(Math::DegreeToRadian(45));
	lights[7].cosInner = cos(Math::DegreeToRadian(30));
	lights[7].exponent = 3.f;
	lights[7].spotDirection.Set(1.f, 1.f, 0.f);


	// Make sure you pass uniform parameters after glUseProgram()
	glUniform1i(m_parameters[U_NUMLIGHTS], 8);

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

	//Light 3
	glUniform1i(m_parameters[U_LIGHT2_TYPE], lights[2].type);
	glUniform3fv(m_parameters[U_LIGHT2_COLOR], 1, &lights[2].color.r);
	glUniform1f(m_parameters[U_LIGHT2_POWER], lights[2].power);
	glUniform1f(m_parameters[U_LIGHT2_KC], lights[2].kC);
	glUniform1f(m_parameters[U_LIGHT2_KL], lights[2].kL);
	glUniform1f(m_parameters[U_LIGHT2_KQ], lights[2].kQ);
	glUniform1f(m_parameters[U_LIGHT2_COSCUTOFF], lights[2].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT2_COSINNER], lights[2].cosInner);
	glUniform1f(m_parameters[U_LIGHT2_EXPONENT], lights[2].exponent);

	//Light 4
	glUniform1i(m_parameters[U_LIGHT3_TYPE], lights[3].type);
	glUniform3fv(m_parameters[U_LIGHT3_COLOR], 1, &lights[3].color.r);
	glUniform1f(m_parameters[U_LIGHT3_POWER], lights[3].power);
	glUniform1f(m_parameters[U_LIGHT3_KC], lights[3].kC);
	glUniform1f(m_parameters[U_LIGHT3_KL], lights[3].kL);
	glUniform1f(m_parameters[U_LIGHT3_KQ], lights[3].kQ);
	glUniform1f(m_parameters[U_LIGHT3_COSCUTOFF], lights[3].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT3_COSINNER], lights[3].cosInner);
	glUniform1f(m_parameters[U_LIGHT3_EXPONENT], lights[3].exponent);

	//Light 5
	glUniform1i(m_parameters[U_LIGHT4_TYPE], lights[4].type);
	glUniform3fv(m_parameters[U_LIGHT4_COLOR], 1, &lights[4].color.r);
	glUniform1f(m_parameters[U_LIGHT4_POWER], lights[4].power);
	glUniform1f(m_parameters[U_LIGHT4_KC], lights[4].kC);
	glUniform1f(m_parameters[U_LIGHT4_KL], lights[4].kL);
	glUniform1f(m_parameters[U_LIGHT4_KQ], lights[4].kQ);
	glUniform1f(m_parameters[U_LIGHT4_COSCUTOFF], lights[4].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT4_COSINNER], lights[4].cosInner);
	glUniform1f(m_parameters[U_LIGHT4_EXPONENT], lights[4].exponent);

	//Light 6
	glUniform1i(m_parameters[U_LIGHT5_TYPE], lights[5].type);
	glUniform3fv(m_parameters[U_LIGHT5_COLOR], 1, &lights[5].color.r);
	glUniform1f(m_parameters[U_LIGHT5_POWER], lights[5].power);
	glUniform1f(m_parameters[U_LIGHT5_KC], lights[5].kC);
	glUniform1f(m_parameters[U_LIGHT5_KL], lights[5].kL);
	glUniform1f(m_parameters[U_LIGHT5_KQ], lights[5].kQ);
	glUniform1f(m_parameters[U_LIGHT5_COSCUTOFF], lights[5].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT5_COSINNER], lights[5].cosInner);
	glUniform1f(m_parameters[U_LIGHT5_EXPONENT], lights[5].exponent);

	//Light 7
	glUniform1i(m_parameters[U_LIGHT6_TYPE], lights[6].type);
	glUniform3fv(m_parameters[U_LIGHT6_COLOR], 1, &lights[6].color.r);
	glUniform1f(m_parameters[U_LIGHT6_POWER], lights[6].power);
	glUniform1f(m_parameters[U_LIGHT6_KC], lights[6].kC);
	glUniform1f(m_parameters[U_LIGHT6_KL], lights[6].kL);
	glUniform1f(m_parameters[U_LIGHT6_KQ], lights[6].kQ);
	glUniform1f(m_parameters[U_LIGHT6_COSCUTOFF], lights[6].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT6_COSINNER], lights[6].cosInner);
	glUniform1f(m_parameters[U_LIGHT6_EXPONENT], lights[6].exponent);

	//Light 8
	glUniform1i(m_parameters[U_LIGHT7_TYPE], lights[7].type);
	glUniform3fv(m_parameters[U_LIGHT7_COLOR], 1, &lights[7].color.r);
	glUniform1f(m_parameters[U_LIGHT7_POWER], lights[7].power);
	glUniform1f(m_parameters[U_LIGHT7_KC], lights[7].kC);
	glUniform1f(m_parameters[U_LIGHT7_KL], lights[7].kL);
	glUniform1f(m_parameters[U_LIGHT7_KQ], lights[7].kQ);
	glUniform1f(m_parameters[U_LIGHT7_COSCUTOFF], lights[7].cosCutoff);
	glUniform1f(m_parameters[U_LIGHT7_COSINNER], lights[7].cosInner);
	glUniform1f(m_parameters[U_LIGHT7_EXPONENT], lights[7].exponent);



}
/******************************************************************************/
/*!
\brief
Initializes the Characters for the scene
*/
/******************************************************************************/
void StudioProject::InitCharacters()
{
	Mesh* newHead;
	Mesh* newTorso;
	Mesh* newLHand;
	Mesh* newRHand;
	Mesh* newLLeg;
	Mesh* newRLeg;
	Vector3 newPosition;
	newPosition.Set(-152.0f,0.0f,-2.0f);

	/*========================================================================
	PLAYER
	===========================================================================*/

	newHead = MeshBuilder::GenerateOBJ("Character Head", "OBJ//modelHead.obj");
	newHead->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newHead->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newHead->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newHead->material.kShininess = 8.f;
	newHead->textureID = LoadTGA("Image//modelHead.tga");

	newTorso = MeshBuilder::GenerateOBJ("Character Torso", "OBJ//modelTorso.obj");
	newTorso->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newTorso->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newTorso->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newTorso->material.kShininess = 8.f;
	newTorso->textureID = LoadTGA("Image//modelTorso.tga");

	newLHand = MeshBuilder::GenerateOBJ("Character Left Hand", "OBJ//modelArm.obj");
	newLHand->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newLHand->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newLHand->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newLHand->material.kShininess = 8.f;
	newLHand->textureID = LoadTGA("Image//modelHand.tga");

	newRHand = MeshBuilder::GenerateOBJ("Character Right Hand ", "OBJ//modelArm.obj");
	newRHand->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newRHand->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newRHand->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newRHand->material.kShininess = 8.f;
	newRHand->textureID = LoadTGA("Image//modelHand.tga");

	newLLeg = MeshBuilder::GenerateOBJ("Character Left Leg", "OBJ//modelLeg.obj");
	newLLeg->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newLLeg->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newLLeg->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newLLeg->material.kShininess = 8.f;
	newLLeg->textureID = LoadTGA("Image//modelLeg.tga");

	newRLeg = MeshBuilder::GenerateOBJ("Character Right Leg", "OBJ//modelLeg.obj");
	newRLeg->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newRLeg->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newRLeg->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newRLeg->material.kShininess = 8.f;
	newRLeg->textureID = LoadTGA("Image//modelLeg.tga");

	player.setCharacter(newHead,newTorso,newLHand,newRHand,newLLeg,newRLeg,newPosition);
	TAnpc.setCharacter(newHead,newTorso,newLHand,newRHand,newLLeg,newRLeg,newPosition);
	newPosition.Set(-152.0f,0.0f,90.0f);
	Theifnpc.setCharacter(newHead,newTorso,newLHand,newRHand,newLLeg,newRLeg,newPosition);
	newPosition.Set(30.0f,0.0f,90.0f);
	GTPnpc.setCharacter(newHead,newTorso,newLHand,newRHand,newLLeg,newRLeg,newPosition);

	/*========================================================================
	Guard
	===========================================================================*/
	Guard1.SetData(Vector3(-70, 0, -21.5),Vector3(-70, 0, -22.5));

	newHead = MeshBuilder::GenerateOBJ("Guard Head", "OBJ//cashierHead.obj");
	newHead->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newHead->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newHead->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newHead->material.kShininess = 8.f;
	newHead->textureID = LoadTGA("Image//guardHead.tga");

	newTorso = MeshBuilder::GenerateOBJ("Guard Torso", "OBJ//cashierTorso.obj");
	newTorso->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newTorso->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newTorso->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newTorso->material.kShininess = 8.f;
	newTorso->textureID = LoadTGA("Image//guardTorso.tga");

	newLHand = MeshBuilder::GenerateOBJ("guard Left Hand", "OBJ//cashierHand.obj");
	newLHand->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newLHand->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newLHand->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newLHand->material.kShininess = 8.f;
	newLHand->textureID = LoadTGA("Image//guardHand.tga");

	newRHand = MeshBuilder::GenerateOBJ("guard Right Hand ", "OBJ//cashierHand.obj");
	newRHand->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newRHand->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newRHand->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newRHand->material.kShininess = 8.f;
	newRHand->textureID = LoadTGA("Image//guardHand.tga");

	newLLeg = MeshBuilder::GenerateOBJ("guard Left Leg", "OBJ//cashierLeg.obj");
	newLLeg->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newLLeg->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newLLeg->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newLLeg->material.kShininess = 8.f;
	newLLeg->textureID = LoadTGA("Image//guardLeg.tga");

	newRLeg = MeshBuilder::GenerateOBJ("guard Right Leg", "OBJ//cashierLeg.obj");
	newRLeg->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newRLeg->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newRLeg->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newRLeg->material.kShininess = 8.f;
	newRLeg->textureID = LoadTGA("Image//guardLeg.tga");

	Guard1.setCharacter(newHead,newTorso,newLHand,newRHand,newLLeg,newRLeg,newPosition);

	/*========================================================================
	Guard2
	===========================================================================*/
	Guard2.SetData(Vector3(-70, 0, 21.5),Vector3(-70, 0, 20.5));

	newHead = MeshBuilder::GenerateOBJ("Guard Head", "OBJ//cashierHead.obj");
	newHead->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newHead->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newHead->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newHead->material.kShininess = 8.f;
	newHead->textureID = LoadTGA("Image//guardHead.tga");

	newTorso = MeshBuilder::GenerateOBJ("Guard Torso", "OBJ//cashierTorso.obj");
	newTorso->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newTorso->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newTorso->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newTorso->material.kShininess = 8.f;
	newTorso->textureID = LoadTGA("Image//guardTorso.tga");

	newLHand = MeshBuilder::GenerateOBJ("guard Left Hand", "OBJ//cashierHand.obj");
	newLHand->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newLHand->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newLHand->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newLHand->material.kShininess = 8.f;
	newLHand->textureID = LoadTGA("Image//guardHand.tga");

	newRHand = MeshBuilder::GenerateOBJ("guard Right Hand ", "OBJ//cashierHand.obj");
	newRHand->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newRHand->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newRHand->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newRHand->material.kShininess = 8.f;
	newRHand->textureID = LoadTGA("Image//guardHand.tga");

	newLLeg = MeshBuilder::GenerateOBJ("guard Left Leg", "OBJ//cashierLeg.obj");
	newLLeg->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newLLeg->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newLLeg->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newLLeg->material.kShininess = 8.f;
	newLLeg->textureID = LoadTGA("Image//guardLeg.tga");

	newRLeg = MeshBuilder::GenerateOBJ("guard Right Leg", "OBJ//cashierLeg.obj");
	newRLeg->material.kAmbient.Set(0.1f, 0.1f, 0.1f);
	newRLeg->material.kDiffuse.Set(0.9f, 0.9f, 0.9f);
	newRLeg->material.kSpecular.Set(0.5f, 0.5f, 0.5f);
	newRLeg->material.kShininess = 8.f;
	newRLeg->textureID = LoadTGA("Image//guardLeg.tga");

	Guard2.setCharacter(newHead,newTorso,newLHand,newRHand,newLLeg,newRLeg,newPosition);
}

/******************************************************************************/
/*!
\brief
Initializes the required data for the scene
*/
/******************************************************************************/
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

	//Initialize camera settings
	camera.Init(Vector3(-45, 5, 15), Vector3(-45, 5, 13), Vector3(0, 1, 0));

	Passerby[0].SetPasserby(Vector3(0, 0, 3));
	Passerby[1].SetPasserby(Vector3(0, 0, -3));
	Passerby[2].SetPasserby(Vector3(0, 0, 31));

	Mtx44 projection;
	projection.SetToPerspective(45.f, 4.f / 3.f, 0.1f, 10000.f);
	projectionStack.LoadMatrix(projection);

	InitVariables();

	InitCharacters();

	InitShaders();

	InitMesh();

}

/******************************************************************************/
/*!
\brief
Initializes the item prices back to original
*/
/******************************************************************************/
void StudioProject::InitOrigPrice()
{
	float newPrice = 3.5f;
	/*==============================
	Container 1
	=================================*/
	for(int i = 0; i < Container.size();++i)
	{
		Container[i].setPrice(newPrice);
	}

	/*==============================
	Container 2
	=================================*/
	for(int i = 0; i < Container2.size();++i)
	{
		Container2[i].setPrice(newPrice);
	}

	/*==============================
	Container 3
	=================================*/
	for(int i = 0; i < Container3.size();++i)
	{
		Container3[i].setPrice(newPrice);
	}


	/*==============================
	Container 4
	=================================*/
	for(int i = 0; i < Container4.size();++i)
	{
		Container4[i].setPrice(newPrice);
	}

	/*==============================
	Container 5
	=================================*/
	for(int i = 0; i < Container5.size();++i)
	{
		Container5[i].setPrice(newPrice);
	}

	/*==============================
	Container 6
	=================================*/
	for(int i = 0; i < Container6.size();++i)
	{
		Container6[i].setPrice(newPrice);
	}

	/*==============================
	Container 7
	=================================*/
	for(int i = 0; i < Container7.size();++i)
	{
		Container7[i].setPrice(newPrice);
	}

	/*==============================
	Container 8
	=================================*/
	for(int i = 0; i < Container8.size();++i)
	{
		Container8[i].setPrice(newPrice);
	}

	/*==============================
	Container 9
	=================================*/
	for(int i = 0; i < Container9.size();++i)
	{

		Container9[i].setPrice(newPrice);
	}

	/*==============================
	Container 10
	=================================*/
	for(int i = 0; i < Container10.size();++i)
	{
		Container10[i].setPrice(newPrice);
	}

	/*==============================
	Container 11
	=================================*/
	for(int i = 0; i < Container11.size();++i)
	{
		Container11[i].setPrice(newPrice);
	}

	/*==============================
	Container 12
	=================================*/
	for(int i = 0; i < Container12.size();++i)
	{
		Container12[i].setPrice(newPrice);
	}

	/*==============================
	Container 13
	=================================*/
	for(int i = 0; i < Container13.size();++i)
	{
		Container13[i].setPrice(newPrice);
	}
}

//========Variables for use in update====//
bool Closed = true;
bool Opened = false;
bool doorMoving = false;
bool doorStop = true;
bool B_Light = true;
static float ROT_LIMIT = 45.f;
static float SCALE_LIMIT = 5.f;
string result;

float doorTranslate = 0;
//Show Controls
bool isShown = true;

//=====variables to animate model arms===//
int rotatingRightArm = 1;
int rotatingLeftArm = 1;
int rotatingRightLeg = 1;
int rotatingLeftLeg = 1;

//========variables used for debugging purposes==========//
bool collide = false;
bool checking = false;

/******************************************************************************/
/*!
\brief
Updates the Taking of items in the scene

*/
/******************************************************************************/
void StudioProject::updateTakingItem()
{
	/*======================================================================
	TAKING ITEMS FROM SHELF
	=========================================================================*/
	if(checking == false)
	{
		if(Application::IsKeyPressed('E'))
		{
			for(int i = 0; i < boxContainer.size(); ++i) //Container 1
			{
				checking = true;
				//==========Taking Items from shelf=============//
				if(Container[i].getRender() == true)
				{
					if((camera.target.x <= boxContainer[i].max.x) &&
						(camera.target.y <= boxContainer[i].max.y) && 
						(camera.target.z <= boxContainer[i].max.z) &&
						(camera.target.x >= boxContainer[i].min.x) && 
						(camera.target.y >= boxContainer[i].min.y) && 
						(camera.target.z >= boxContainer[i].min.z))
					{
						if(player.getInventory().AddItem(Container[i]) == true)
						{
							Sound = engine->play2D("Sound\\taking-something.wav");
							Container[i].setRender(false);
							break;
						}
					}
				}
			}

			for(int i = 0; i < boxContainer2.size(); ++i)//Container 2
			{
				checking = true;
				//==========Taking Items from shelf=============//
				if(Container2[i].getRender() == true)
				{
					if((camera.target.x <= boxContainer2[i].max.x) && 
						(camera.target.y <= boxContainer2[i].max.y) && 
						(camera.target.z <= boxContainer2[i].max.z) && 
						(camera.target.x >= boxContainer2[i].min.x) && 
						(camera.target.y >= boxContainer2[i].min.y) && 
						(camera.target.z >= boxContainer2[i].min.z))
					{
						if(player.getInventory().AddItem(Container2[i]) == true)
						{
							Sound = engine->play2D("Sound\\taking-something.wav");
							Container2[i].setRender(false);
							break;
						}
					}
				}
			}

			for(int i = 0; i < boxContainer3.size(); ++i) //Container 3
			{
				checking = true;
				//==========Taking Items from shelf=============//
				if(Container3[i].getRender() == true)
				{
					if((camera.target.x <= boxContainer3[i].max.x) && 
						(camera.target.y <= boxContainer3[i].max.y) && 
						(camera.target.z <= boxContainer3[i].max.z) && 
						(camera.target.x >= boxContainer3[i].min.x) && 
						(camera.target.y >= boxContainer3[i].min.y) && 
						(camera.target.z >= boxContainer3[i].min.z))
					{
						if(player.getInventory().AddItem(Container3[i]) == true)
						{
							Sound = engine->play2D("Sound\\taking-something.wav");
							Container3[i].setRender(false);
							break;
						}
					}
				}
			}

			for(int i = 0; i < boxContainer4.size(); ++i) //Container 4
			{
				checking = true;
				//==========Taking Items from shelf=============//
				if(Container4[i].getRender() == true)
				{
					if((camera.target.x <= boxContainer4[i].max.x) && 
						(camera.target.y <= boxContainer4[i].max.y) && 
						(camera.target.z <= boxContainer4[i].max.z) && 
						(camera.target.x >= boxContainer4[i].min.x) && 
						(camera.target.y >= boxContainer4[i].min.y) && 
						(camera.target.z >= boxContainer4[i].min.z))
					{
						if(player.getInventory().AddItem(Container4[i]) == true)
						{
							Sound = engine->play2D("Sound\\taking-something.wav");
							Container4[i].setRender(false);
							break;
						}
					}
				}
			}

			for(int i = 0; i < boxContainer5.size(); ++i) //Container 5
			{
				checking = true;
				//==========Taking Items from shelf=============//
				if(Container5[i].getRender() == true)
				{
					if((camera.target.x <= boxContainer5[i].max.x) && 
						(camera.target.y <= boxContainer5[i].max.y) && 
						(camera.target.z <= boxContainer5[i].max.z) && 
						(camera.target.x >= boxContainer5[i].min.x) && 
						(camera.target.y >= boxContainer5[i].min.y) && 
						(camera.target.z >= boxContainer5[i].min.z))
					{
						if(player.getInventory().AddItem(Container5[i]) == true)
						{
							Sound = engine->play2D("Sound\\taking-something.wav");
							Container5[i].setRender(false);
							break;
						}
					}
				}
			}

			for(int i = 0; i < boxContainer6.size(); ++i) //Container 6
			{
				checking = true;
				//==========Taking Items from shelf=============//
				if(Container6[i].getRender() == true)
				{
					if((camera.target.x <= boxContainer6[i].max.x) && 
						(camera.target.y <= boxContainer6[i].max.y) && 
						(camera.target.z <= boxContainer6[i].max.z) && 
						(camera.target.x >= boxContainer6[i].min.x) && 
						(camera.target.y >= boxContainer6[i].min.y) && 
						(camera.target.z >= boxContainer6[i].min.z))
					{
						if(player.getInventory().AddItem(Container6[i]) == true)
						{
							Sound = engine->play2D("Sound\\taking-something.wav");
							Container6[i].setRender(false);
							break;
						}
					}
				}
			}

			for(int i = 0; i < boxContainer7.size(); ++i) //Container 7
			{
				checking = true;
				//==========Taking Items from shelf=============//
				if(Container7[i].getRender() == true)
				{
					if((camera.target.x <= boxContainer7[i].max.x) && 
						(camera.target.y <= boxContainer7[i].max.y) && 
						(camera.target.z <= boxContainer7[i].max.z) && 
						(camera.target.x >= boxContainer7[i].min.x) && 
						(camera.target.y >= boxContainer7[i].min.y) && 
						(camera.target.z >= boxContainer7[i].min.z))
					{
						if(player.getInventory().AddItem(Container7[i]) == true)
						{
							Sound = engine->play2D("Sound\\taking-something.wav");
							Container7[i].setRender(false);
							break;
						}
					}
				}
			}

			for(int i = 0; i < boxContainer8.size(); ++i) //Container 8
			{
				checking = true;
				//==========Taking Items from shelf=============//
				if(Container8[i].getRender() == true)
				{
					if((camera.target.x <= boxContainer8[i].max.x) && 
						(camera.target.y <= boxContainer8[i].max.y) && 
						(camera.target.z <= boxContainer8[i].max.z) && 
						(camera.target.x >= boxContainer8[i].min.x) && 
						(camera.target.y >= boxContainer8[i].min.y) && 
						(camera.target.z >= boxContainer8[i].min.z))
					{
						if(player.getInventory().AddItem(Container8[i]) == true)
						{
							Sound = engine->play2D("Sound\\taking-something.wav");
							Container8[i].setRender(false);
							break;
						}
					}
				}
			}
			for(int i = 0; i < boxContainer9.size(); ++i) //Container 9
			{
				checking = true;
				//==========Taking Items from shelf=============//
				if(Container9[i].getRender() == true)
				{
					if((camera.target.x <= boxContainer9[i].max.x) && 
						(camera.target.y <= boxContainer9[i].max.y) && 
						(camera.target.z <= boxContainer9[i].max.z) && 
						(camera.target.x >= boxContainer9[i].min.x) && 
						(camera.target.y >= boxContainer9[i].min.y) && 
						(camera.target.z >= boxContainer9[i].min.z))
					{
						if(player.getInventory().AddItem(Container9[i]) == true)
						{
							Sound = engine->play2D("Sound\\taking-something.wav");
							Container9[i].setRender(false);
							break;
						}
					}
				}
			}
			for(int i = 0; i < boxContainer10.size(); ++i) //Container 10
			{
				checking = true;
				//==========Taking Items from shelf=============//
				if(Container10[i].getRender() == true)
				{
					if((camera.target.x <= boxContainer10[i].max.x) && 
						(camera.target.y <= boxContainer10[i].max.y) && 
						(camera.target.z <= boxContainer10[i].max.z) && 
						(camera.target.x >= boxContainer10[i].min.x) && 
						(camera.target.y >= boxContainer10[i].min.y) && 
						(camera.target.z >= boxContainer10[i].min.z))
					{
						if(player.getInventory().AddItem(Container10[i]) == true)
						{
							Sound = engine->play2D("Sound\\taking-something.wav");
							Container10[i].setRender(false);
							break;
						}
					}
				}
			}

			for(int i = 0; i < boxContainer11.size(); ++i) //Container 11
			{
				checking = true;
				//==========Taking Items from shelf=============//
				if(Container11[i].getRender() == true)
				{
					if((camera.target.x <= boxContainer11[i].max.x) && 
						(camera.target.y <= boxContainer11[i].max.y) && 
						(camera.target.z <= boxContainer11[i].max.z) && 
						(camera.target.x >= boxContainer11[i].min.x) && 
						(camera.target.y >= boxContainer11[i].min.y) && 
						(camera.target.z >= boxContainer11[i].min.z))
					{
						if(player.getInventory().AddItem(Container11[i]) == true)
						{
							Sound = engine->play2D("Sound\\taking-something.wav");
							Container11[i].setRender(false);
							break;
						}
					}
				}
			}
			for(int i = 0; i < boxContainer12.size(); ++i) //Container 12
			{
				checking = true;
				//==========Taking Items from shelf=============//
				if(Container12[i].getRender() == true)
				{
					if((camera.target.x <= boxContainer12[i].max.x) && 
						(camera.target.y <= boxContainer12[i].max.y) && 
						(camera.target.z <= boxContainer12[i].max.z) && 
						(camera.target.x >= boxContainer12[i].min.x) && 
						(camera.target.y >= boxContainer12[i].min.y) && 
						(camera.target.z >= boxContainer12[i].min.z))
					{
						if(player.getInventory().AddItem(Container12[i]) == true)
						{
							Sound = engine->play2D("Sound\\taking-something.wav");
							Container12[i].setRender(false);
							break;
						}
					}
				}
			}

			for(int i = 0; i < boxContainer13.size(); ++i) //Container 12
			{
				checking = true;
				//==========Taking Items from shelf=============//
				if(Container13[i].getRender() == true)
				{
					if((camera.target.x <= boxContainer13[i].max.x) && 
						(camera.target.y <= boxContainer13[i].max.y) && 
						(camera.target.z <= boxContainer13[i].max.z) && 
						(camera.target.x >= boxContainer13[i].min.x) && 
						(camera.target.y >= boxContainer13[i].min.y) && 
						(camera.target.z >= boxContainer13[i].min.z))
					{
						if(player.getInventory().AddItem(Container13[i]) == true)
						{
							Sound = engine->play2D("Sound\\taking-something.wav");
							Container13[i].setRender(false);
							break;
						}
					}
				}
			}
			checking = false;
		}
	}
}
/******************************************************************************/
/*!
\brief
Updates the Putting Back of items in the scene

*/
/******************************************************************************/
void StudioProject::updatePuttingBackItem()
{
	/*===================================================================
	PUTTING ITEMS BACK TO SHELF
	======================================================================*/
	if(Application::IsKeyPressed('Q'))
	{
		for(int i = 0; i < boxContainer.size(); ++i)
		{
			//==========Putting items back to shelf=============//
			if(Container[i].getRender() == false)//Container 1
			{
				if((camera.target.x <= boxContainer[i].max.x) && 
					(camera.target.y <= boxContainer[i].max.y) && 
					(camera.target.z <= boxContainer[i].max.z) &&
					(camera.target.x >= boxContainer[i].min.x) && 
					(camera.target.y >= boxContainer[i].min.y) && 
					(camera.target.z >= boxContainer[i].min.z))
				{
					if(player.getInventory().removeItem(Container[i]) == true)
					{
						Sound = engine->play2D("Sound\\taking-something.wav");
						Container[i].setRender(true);
						break;
					}
				}
			}
		}
		for(int i = 0; i < boxContainer2.size(); ++i)//Container 2
		{
			if(Container2[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer2[i].max.x) && 
					(camera.target.y <= boxContainer2[i].max.y) && 
					(camera.target.z <= boxContainer2[i].max.z) &&
					(camera.target.x >= boxContainer2[i].min.x) && 
					(camera.target.y >= boxContainer2[i].min.y) &&
					(camera.target.z >= boxContainer2[i].min.z))
				{
					if(player.getInventory().removeItem(Container2[i]) == true)
					{
						Sound = engine->play2D("Sound\\taking-something.wav");
						Container2[i].setRender(true);
						break;
					}
				}
			}
		}

		for(int i = 0; i < boxContainer3.size(); ++i)//Container 3
		{
			if(Container3[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer3[i].max.x) && 
					(camera.target.y <= boxContainer3[i].max.y) && 
					(camera.target.z <= boxContainer3[i].max.z) &&
					(camera.target.x >= boxContainer3[i].min.x) && 
					(camera.target.y >= boxContainer3[i].min.y) &&
					(camera.target.z >= boxContainer3[i].min.z))
				{
					if(player.getInventory().removeItem(Container3[i]) == true)
					{
						Sound = engine->play2D("Sound\\taking-something.wav");
						Container3[i].setRender(true);
						break;
					}
				}
			}
		}

		for(int i = 0; i < boxContainer4.size(); ++i)
		{
			//==========Putting items back to shelf=============//
			if(Container4[i].getRender() == false)//Container 4
			{
				if((camera.target.x <= boxContainer4[i].max.x) && 
					(camera.target.y <= boxContainer4[i].max.y) && 
					(camera.target.z <= boxContainer4[i].max.z) &&
					(camera.target.x >= boxContainer4[i].min.x) && 
					(camera.target.y >= boxContainer4[i].min.y) && 
					(camera.target.z >= boxContainer4[i].min.z))
				{
					if(player.getInventory().removeItem(Container4[i]) == true)
					{
						Sound = engine->play2D("Sound\\taking-something.wav");
						Container4[i].setRender(true);
						break;
					}
				}
			}
		}
		for(int i = 0; i < boxContainer5.size(); ++i)//Container 5
		{
			if(Container5[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer5[i].max.x) && 
					(camera.target.y <= boxContainer5[i].max.y) && 
					(camera.target.z <= boxContainer5[i].max.z) &&
					(camera.target.x >= boxContainer5[i].min.x) && 
					(camera.target.y >= boxContainer5[i].min.y) &&
					(camera.target.z >= boxContainer5[i].min.z))
				{
					if(player.getInventory().removeItem(Container5[i]) == true)
					{
						Sound = engine->play2D("Sound\\taking-something.wav");
						Container5[i].setRender(true);
						break;
					}
				}
			}
		}

		for(int i = 0; i < boxContainer6.size(); ++i)//Container 6
		{
			if(Container6[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer6[i].max.x) && 
					(camera.target.y <= boxContainer6[i].max.y) && 
					(camera.target.z <= boxContainer6[i].max.z) &&
					(camera.target.x >= boxContainer6[i].min.x) && 
					(camera.target.y >= boxContainer6[i].min.y) &&
					(camera.target.z >= boxContainer6[i].min.z))
				{
					if(player.getInventory().removeItem(Container6[i]) == true)
					{
						Sound = engine->play2D("Sound\\taking-something.wav");
						Container6[i].setRender(true);
						break;
					}
				}
			}
		}
		for(int i = 0; i < boxContainer7.size(); ++i)//Container 7
		{
			if(Container7[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer7[i].max.x) && 
					(camera.target.y <= boxContainer7[i].max.y) && 
					(camera.target.z <= boxContainer7[i].max.z) &&
					(camera.target.x >= boxContainer7[i].min.x) && 
					(camera.target.y >= boxContainer7[i].min.y) &&
					(camera.target.z >= boxContainer7[i].min.z))
				{
					if(player.getInventory().removeItem(Container7[i]) == true)
					{
						Sound = engine->play2D("Sound\\taking-something.wav");
						Container7[i].setRender(true);
						break;
					}
				}
			}
		}

		for(int i = 0; i < boxContainer8.size(); ++i)//Container 8
		{
			if(Container8[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer8[i].max.x) && 
					(camera.target.y <= boxContainer8[i].max.y) && 
					(camera.target.z <= boxContainer8[i].max.z) &&
					(camera.target.x >= boxContainer8[i].min.x) && 
					(camera.target.y >= boxContainer8[i].min.y) &&
					(camera.target.z >= boxContainer8[i].min.z))
				{
					if(player.getInventory().removeItem(Container8[i]) == true)
					{
						Sound = engine->play2D("Sound\\taking-something.wav");
						Container8[i].setRender(true);
						break;
					}
				}
			}
		}
		for(int i = 0; i < boxContainer9.size(); ++i)//Container 9
		{
			if(Container9[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer9[i].max.x) && 
					(camera.target.y <= boxContainer9[i].max.y) && 
					(camera.target.z <= boxContainer9[i].max.z) &&
					(camera.target.x >= boxContainer9[i].min.x) && 
					(camera.target.y >= boxContainer9[i].min.y) &&
					(camera.target.z >= boxContainer9[i].min.z))
				{
					if(player.getInventory().removeItem(Container9[i]) == true)
					{
						Sound = engine->play2D("Sound\\taking-something.wav");
						Container9[i].setRender(true);
						break;
					}
				}
			}
		}
		for(int i = 0; i < boxContainer10.size(); ++i)//Container 10
		{
			if(Container10[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer10[i].max.x) && 
					(camera.target.y <= boxContainer10[i].max.y) && 
					(camera.target.z <= boxContainer10[i].max.z) &&
					(camera.target.x >= boxContainer10[i].min.x) && 
					(camera.target.y >= boxContainer10[i].min.y) &&
					(camera.target.z >= boxContainer10[i].min.z))
				{
					if(player.getInventory().removeItem(Container10[i]) == true)
					{
						Sound = engine->play2D("Sound\\taking-something.wav");
						Container10[i].setRender(true);
						break;
					}
				}
			}
		}
		for(int i = 0; i < boxContainer11.size(); ++i)//Container 11
		{
			if(Container11[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer11[i].max.x) && 
					(camera.target.y <= boxContainer11[i].max.y) && 
					(camera.target.z <= boxContainer11[i].max.z) &&
					(camera.target.x >= boxContainer11[i].min.x) && 
					(camera.target.y >= boxContainer11[i].min.y) &&
					(camera.target.z >= boxContainer11[i].min.z))
				{
					if(player.getInventory().removeItem(Container11[i]) == true)
					{
						Sound = engine->play2D("Sound\\taking-something.wav");
						Container11[i].setRender(true);
						break;
					}
				}
			}
		}
		for(int i = 0; i < boxContainer12.size(); ++i)//Container 12
		{
			if(Container12[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer12[i].max.x) && 
					(camera.target.y <= boxContainer12[i].max.y) && 
					(camera.target.z <= boxContainer12[i].max.z) &&
					(camera.target.x >= boxContainer12[i].min.x) && 
					(camera.target.y >= boxContainer12[i].min.y) &&
					(camera.target.z >= boxContainer12[i].min.z))
				{
					if(player.getInventory().removeItem(Container12[i]) == true)
					{
						Sound = engine->play2D("Sound\\taking-something.wav");
						Container12[i].setRender(true);
						break;
					}
				}
			}
		}

		for(int i = 0; i < boxContainer13.size(); ++i)//Container 13
		{
			if(Container13[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer13[i].max.x) && 
					(camera.target.y <= boxContainer13[i].max.y) && 
					(camera.target.z <= boxContainer13[i].max.z) &&
					(camera.target.x >= boxContainer13[i].min.x) && 
					(camera.target.y >= boxContainer13[i].min.y) &&
					(camera.target.z >= boxContainer13[i].min.z))
				{
					if(player.getInventory().removeItem(Container13[i]) == true)
					{
						Sound = engine->play2D("Sound\\taking-something.wav");
						Container13[i].setRender(true);
						break;
					}
				}
			}
		}
	}
}
/******************************************************************************/
/*!
\brief
Updates the Checking Out of items in the scene

*/
/******************************************************************************/ 
void StudioProject::updateCheckingOut()
{
	/*===============================================================
	CHECKING OUT
	==================================================================*/
	if(Application::IsKeyPressed('E') && (player.getInventory().getNoOfItems() != 0))
	{
		for(int i = 0;i < CashierBox.size();i++)
		{
			if((camera.position.x <= CashierBox[i].max.x) && 
				(camera.position.y <= CashierBox[i].max.y) && 
				(camera.position.z <= CashierBox[i].max.z) &&
				(camera.position.x >= CashierBox[i].min.x) && 
				(camera.position.y >= CashierBox[i].min.y) && 
				(camera.position.z >= CashierBox[i].min.z))
			{
				float cost = 0.f;
				vector<CItem> toDelete;
				//Calculating Cost of items taken by player
				for(int i = 1; i < (player.getInventory().getNoOfItems() + 1); i++)
				{
					if(player.getInventory().getItem(i).getPaid() == false)
					{
						cost += player.getInventory().getItem(i).getPrice();
						tempCheckOut.push_back(player.getInventory().getItem(i));
						paidItems.push_back(player.getInventory().getItem(i));
						toDelete.push_back(player.getInventory().getItem(i));
					}
				}
				//Only if cost is lesser or equal player will be successfully checked out and items removed from invent
				//If there are items that are not paid
				if((cost < player.getMoney()) && toDelete.size() > 0)
				{
					camera.setCheckingOut(true);
					//Removes not paid items
					for(int i = 0; i < toDelete.size(); ++i)
					{
						player.getInventory().removeItem(toDelete[i]);
					}
					float temp = player.getMoney() - cost;
					player.setMoney(temp);
					toDelete.clear();
				}
				else if(cost > player.getMoney())
				{
					tempCheckOut.clear();
					paidItems.clear();
					toDelete.clear();
				}
			}
		}
	}
	for(int i = 0; i < tempCheckOut.size(); i++)
	{
		if(tempCheckOut[i].getobjType() == GEO_PEA_N_CARROTS)
		{
			Peas = true;
			peaCount ++;
		}
		if(tempCheckOut[i].getobjType() == GEO_BAKED_BEANS_CAN)
		{
			Beans = true;
			BeansCount ++;
		}
		if(tempCheckOut[i].getobjType() == GEO_COKE_CAN)
		{
			Coke = true;
			CokeCount ++;
		}
		if(tempCheckOut[i].getobjType() == GEO_DRINKCAN2) // Coke Zero
		{
			CokeZero = true;
			CokeZeroCount ++;
		}
		if(tempCheckOut[i].getobjType() == GEO_PEPSI_CAN)
		{
			Pepsi = true;
			PepsiCount ++;
		}
		if(tempCheckOut[i].getobjType() == GEO_MILOCAN)
		{
			Milo = true;
			MiloCount ++;
		}
		if(tempCheckOut[i].getobjType() == GEO_CEREALBOX1)
		{
			Cereal1 = true;
			Cereal1Count ++;
		}
		if(tempCheckOut[i].getobjType() == GEO_CEREALBOX2)
		{
			Cereal2 = true;
			Cereal2Count ++;
		}
		if(tempCheckOut[i].getobjType() == GEO_PIZZABOX)
		{
			Pizza = true;
			PizzaCount ++;
		}
		if(tempCheckOut[i].getobjType() == GEO_POTATOCHIPS)
		{
			Lays = true;
			LaysCount ++;
		}
		if(tempCheckOut[i].getobjType() == GEO_SARDINE_CAN)
		{
			Sardine = true;
			SardineCount ++;
		}
		if(i == (tempCheckOut.size()-1))
		{
			tempCheckOut.clear();
		}
	}

}
/******************************************************************************/
/*!
\brief
Updates the Time Attack mini game in the scene

*/
/******************************************************************************/
void StudioProject::updateTimeAttack()
{
	if(camera.position.x <= -145 && camera.position.y <= 10 && camera.position.z <= -0.5 &&
		camera.position.x >= -150 && camera.position.y >= 2 && camera.position.z >= -3)
	{
		//Start Time Attack Mini game
		if(Application::IsKeyPressed('E') && TimeAttack == false)
		{
			TimeAttack = true;
			isTAwon = false;
			TAtime = 60.f;
			TAstartedOnce = 0;
			player.setMoney(100.f);
			messageTime = 0.f;
		}
		//End Time Attack Mini game
		if(Application::IsKeyPressed('Q') && TimeAttack == true && TAtime > 0)
		{
			TAmatchedItems = 0;
			//Loop to go through each item in player's inventory
			for(int i = 1; i < player.getInventory().getNoOfItems() + 1;++i)
			{
				//Loop to check each item in player's inventory with list of items required to obtain
				for(int x = 0; x < TAlist.size(); x++)
				{
					//If item is checked out
					if(player.getInventory().getItem(i).getobjType() == TAlist[x] && player.getInventory().getItem(i).getPaid() == true)
					{
						TAlist.erase(TAlist.begin() + x);
						TAmatchedItems++;
					}
				}
			}
			//All Items have been bought
			//Resets variables when win
			if(TAmatchedItems == 6)
			{
				isTAwon = true;
				TimeAttack = false;
				TAlist.clear();
				player.setMoney(50.f);
			}
			//Resets variables when lose
			if(TAmatchedItems != 6)
			{
				isTAwon = false;
				TAstartedOnce++;
				TimeAttack = false;
				TAlist.clear();
				player.setMoney(50.f);
			}
		}
	}
	if(TAtime <= 0)
	{
		isTAwon = false;
		TAstartedOnce++;
		TimeAttack = false;
		TAlist.clear();
		player.setMoney(50.f);
	}
	if(TimeAttack == true)
	{
		//Checks if List is empty
		if(TAlist.size() < 1)
		{
			generateList = true;
		}
	}
	//Generates a List of random numbers that are associated with items for players to obtain
	if(generateList == true)
	{
		//Initializes random seed, to produce a different set of random numbers each run
		srand(time(NULL));
		int temp = 0;
		//GEO_SARDINE_CAN is the first item on the list
		temp = rand() % 11 + GEO_SARDINE_CAN; // First
		TAlist.push_back(temp);
		temp = rand() % 11 + GEO_SARDINE_CAN; // Second
		TAlist.push_back(temp);
		temp = rand() % 11 + GEO_SARDINE_CAN; // Third
		TAlist.push_back(temp);
		temp = rand() % 11 + GEO_SARDINE_CAN; // Fourth
		TAlist.push_back(temp);
		temp = rand() % 11 + GEO_SARDINE_CAN; // Fifth
		TAlist.push_back(temp);
		temp = rand() % 11 + GEO_SARDINE_CAN; // Sixth
		TAlist.push_back(temp);
		//TAlist now holds 6 random integers
		generateList = false;
	}
}
/******************************************************************************/
/*!
\brief
Updates the clearing of inventory

*/
/******************************************************************************/
void StudioProject::updateDustBin()
{
	if(camera.target.x <= -60 && camera.target.y <= 8 && camera.target.z <= -19
		&& camera.target.x >= -63.5 && camera.target.y >= 0 && camera.target.z >= -23)
	{
		if(Application::IsKeyPressed('E'))
		{
			player.getInventory().DeleteAll();
		}
	}
}
/******************************************************************************/
/*!
\brief
Updates the opening and closing of the supermarket door based on delta time

\param dt - delta time
*/
/******************************************************************************/
void StudioProject::updateDoor(double dt)
{
	//============================DOOR===========================//

	if (camera.position.z <= 20.1 && camera.position.z >= -19.7 && camera.position.y >= 2 && camera.position.y <= 10 && camera.position.x <=-41.5 && camera.position.x >= -76.3)
	{

		if(Opened == false &&  Closed == true && doorStop == true)
		{
			Closed = false;
			doorMoving = true;
		}

		if(Closed == false && doorMoving == true)
		{
			
			doorTranslate -=(float)(35*dt);
			if(doorTranslate < -20)
			{
				Sound = engine->play2D("Sound\\doorbell.wav");
				doorMoving = false;
				Opened = true;
				doorStop = true;
				doorTranslate = -20;
			}	

		}
	}
	//This part is for closing of the door
	else
	{
		Opened = false;
		if(Opened == false && Closed == false )
		{
			doorTranslate +=(float)(35*dt);
			if(doorTranslate > 0)
			{
				Closed = true;
				doorTranslate = 0;
			}

		}
	}
	//==============================END OF DOOR ==========================//
}
/******************************************************************************/
/*!
\brief
Updates the AI based on delta time

\param dt - delta time
*/
/******************************************************************************/
void StudioProject::updateAI(double dt)
{
	/*=============================================
	GUARD 1
	===============================================*/
	Guard1.getDifference(camera.position); //Finds difference between guard1 and player
	Guard2.getDifference(camera.position); //Finds difference between guard2 and player

	//Checks if player is outside of supermarket
	if(camera.position.x <= -57)
	{
		for(int i = 1; i <player.getInventory().getNoOfItems() + 1; ++i)
		{
			if(player.getInventory().getItem(i).getPaid() == false)
			{
				Guard1.setState(S_ALERT);
				Guard2.setState(S_ALERT);
				break;
			}
		}
	}
	else
	{
		Guard1.setState(S_IDLE);
		Guard2.setState(S_IDLE);
	}
	Guard1.guardUpdate(dt, camera.position);
	Guard2.guardUpdate(dt, camera.position);
}
/******************************************************************************/
/*!
\brief
Changes all the prices of the items when GTP is started

*/
/******************************************************************************/
void StudioProject::updateGTPprice()
{
	float newPrice;
	srand(time(NULL));
	/*==============================
	Container 1
	=================================*/
	for(int i = 0; i < Container.size();++i)
	{
		newPrice = rand() % 4 + 2;
		Container[i].setPrice(newPrice);
	}

	/*==============================
	Container 2
	=================================*/
	for(int i = 0; i < Container2.size();++i)
	{
		newPrice = rand() % 4 + 2;
		Container2[i].setPrice(newPrice);
	}

	/*==============================
	Container 3
	=================================*/
	for(int i = 0; i < Container3.size();++i)
	{
		newPrice = rand() % 4 + 2;
		Container3[i].setPrice(newPrice);
	}


	/*==============================
	Container 4
	=================================*/
	for(int i = 0; i < Container4.size();++i)
	{
		newPrice = rand() % 4 + 2;
		Container4[i].setPrice(newPrice);
	}

	/*==============================
	Container 5
	=================================*/
	for(int i = 0; i < Container5.size();++i)
	{
		newPrice = rand() % 4 + 2;
		Container5[i].setPrice(newPrice);
	}

	/*==============================
	Container 6
	=================================*/
	for(int i = 0; i < Container6.size();++i)
	{
		newPrice = rand() % 4 + 2;
		Container6[i].setPrice(newPrice);
	}

	/*==============================
	Container 7
	=================================*/
	for(int i = 0; i < Container7.size();++i)
	{
		newPrice = rand() % 4 + 2;
		Container7[i].setPrice(newPrice);
	}

	/*==============================
	Container 8
	=================================*/
	for(int i = 0; i < Container8.size();++i)
	{
		newPrice = rand() % 4 + 2;
		Container8[i].setPrice(newPrice);
	}

	/*==============================
	Container 9
	=================================*/
	for(int i = 0; i < Container9.size();++i)
	{
		newPrice = rand() % 4 + 2;
		Container9[i].setPrice(newPrice);
	}

	/*==============================
	Container 10
	=================================*/
	for(int i = 0; i < Container10.size();++i)
	{
		newPrice = rand() % 4 + 2;
		Container10[i].setPrice(newPrice);
	}

	/*==============================
	Container 11
	=================================*/
	for(int i = 0; i < Container11.size();++i)
	{
		newPrice = rand() % 4 + 2;
		Container11[i].setPrice(newPrice);
	}

	/*==============================
	Container 12
	=================================*/
	for(int i = 0; i < Container12.size();++i)
	{
		newPrice = rand() % 4 + 2;
		Container12[i].setPrice(newPrice);
	}

	/*==============================
	Container 13
	=================================*/
	for(int i = 0; i < Container13.size();++i)
	{
		newPrice = rand() % 4 + 2;
		Container13[i].setPrice(newPrice);
	}
}
/******************************************************************************/
/*!
\brief
Changes the prices of items in the supermarket when Guess The Price mini game
is playing

*/
/******************************************************************************/
void StudioProject::updateGTP()
{
	if(camera.position.x <= 31 && camera.position.y <= 10 && camera.position.z <= 88 &&
		camera.position.x >= 28 && camera.position.y >= 2 && camera.position.z >= 85)
	{
		if(Application::IsKeyPressed('E') && TimeAttack == false && GTP == false)
		{
			updateGTPprice();
			totalCost = 0.f;
			GTP = true;
			player.getInventory().DeleteAll();
			messageTime = 0.f;
			GTPstartedOnce = 0;
			isGTPwon = false;
			NoOfItemsTaken = 0;
		}
		if(Application::IsKeyPressed('Q') && GTP == true)
		{
			//Loop to go through each item in player's inventory
			for(int i = 1; i < player.getInventory().getNoOfItems() + 1;++i)
			{
				//Item must not be checked out
				if(player.getInventory().getItem(i).getPaid() == false)
				{
					totalCost += player.getInventory().getItem(i).getPrice();
					NoOfItemsTaken++;
				}
			}
			//If exceeds 20
			if(totalCost > 20.f)
			{
				isGTPwon = false;
				GTPstartedOnce++;
				player.getInventory().DeleteAll();
				GTP = false;
				InitOrigPrice();
			}
			//If Below 20
			else if(totalCost <= 20.f)
			{
				isGTPwon = true;
				GTP = false;
				player.getInventory().DeleteAll();
				InitOrigPrice();
			}
		}
	}
}
/******************************************************************************/
/*!
\brief
Updates the Theif mini game in the scene

*/
/******************************************************************************/
void StudioProject::updateThiefGame()
{
	if(camera.position.x <= -147 && camera.position.y <= 10 && camera.position.z <= 91 &&
		camera.position.x >= -150 && camera.position.y >= 2 && camera.position.z >= 88.5)
	{
		if(Application::IsKeyPressed('E') && TimeAttack == false && GTP == false && ThiefGame == false)
		{
			isThiefwon = false;
			ThiefGame = true;
			messageTime = 0.f;
			NoOfItemsStolen = 0;
		}
	}
}
/******************************************************************************/
/*!
\brief
Resets all variables to restart the scene

*/
/******************************************************************************/
void StudioProject::ResetAll(double dt)
{
	Guard1.guardUpdate(dt, camera.position);
	Guard2.guardUpdate(dt, camera.position);
	menu.update(dt);
	camera.Update(dt);
	Passerby[0].update(dt, camera.position);
	Passerby[1].update(dt, camera.position);
	Passerby[2].update(dt, camera.position);
	//Page.update(dt);
	angle = 3600;
	playerAngle = 0;
	moving = 0;
	showInventory = false;
	//OBJ FOOD BOOLEANS
	Pizza = false;
	Peas = false;
	Milo = false;
	Cereal1 = false;
	Cereal2 = false;
	Sardine = false;
	Beans = false;
	Lays = false;
	Coke = false;
	CokeZero = false;
	Pepsi = false;
	Pizza = false;
	moveItem = 0; // SPEED
	peaCount = 0;
	PizzaCount = 0;
	MiloCount = 0;
	Cereal1Count = 0;
	Cereal2Count = 0;
	SardineCount = 0;
	BeansCount = 0;
	LaysCount = 0;
	CokeCount = 0;
	CokeZeroCount = 0;
	PepsiCount = 0;
	winState = false;

	//==Time Attack==//
	TimeAttack = false;
	generateList = false;
	TAmatchedItems = 0;
	isTAwon = false;
	TAtime = 60.f;
	timeTA = "";
	TAstartedOnce = 0;
	messageTime = 0.f;
	doorTranslate = 0;
	isShown = true;
	TAlist.clear();

	//==Guess The Price==//
	GTP = false;
	isGTPwon = false;
	NoOfItemsTaken = 0;
	totalCost = 0.f;
	GTPstartedOnce = 0;
	NumItem = "";
	CostOfItems = "";

	//==Theif Game==//
	ThiefGame = false;
	isThiefwon = false;
	NoOfItemsStolen = 0;
	NumStolen = "";


	//==player inventory==//
	player.getInventory().DeleteAll();
	player.setMoney(50.f);

	//==Items reset===//
	float newPrice = 3.5f;
	/*==============================
	Container 1
	=================================*/
	for(int i = 0; i < Container.size();++i)
	{
		Container[i].setRender(true);
	}

	/*==============================
	Container 2
	=================================*/
	for(int i = 0; i < Container2.size();++i)
	{
		Container2[i].setRender(true);
	}

	/*==============================
	Container 3
	=================================*/
	for(int i = 0; i < Container3.size();++i)
	{
		Container3[i].setRender(true);
	}


	/*==============================
	Container 4
	=================================*/
	for(int i = 0; i < Container4.size();++i)
	{
		Container4[i].setRender(true);
	}

	/*==============================
	Container 5
	=================================*/
	for(int i = 0; i < Container5.size();++i)
	{
		Container5[i].setRender(true);
	}

	/*==============================
	Container 6
	=================================*/
	for(int i = 0; i < Container6.size();++i)
	{
		Container6[i].setRender(true);
	}

	/*==============================
	Container 7
	=================================*/
	for(int i = 0; i < Container7.size();++i)
	{
		Container7[i].setRender(true);
	}

	/*==============================
	Container 8
	=================================*/
	for(int i = 0; i < Container8.size();++i)
	{
		Container8[i].setRender(true);
	}

	/*==============================
	Container 9
	=================================*/
	for(int i = 0; i < Container9.size();++i)
	{

		Container9[i].setRender(true);
	}

	/*==============================
	Container 10
	=================================*/
	for(int i = 0; i < Container10.size();++i)
	{
		Container10[i].setRender(true);
	}

	/*==============================
	Container 11
	=================================*/
	for(int i = 0; i < Container11.size();++i)
	{
		Container11[i].setRender(true);
	}

	/*==============================
	Container 12
	=================================*/
	for(int i = 0; i < Container12.size();++i)
	{
		Container12[i].setRender(true);
	}

	/*==============================
	Container 13
	=================================*/
	for(int i = 0; i < Container13.size();++i)
	{
		Container13[i].setRender(true);
	}
}
/******************************************************************************/
/*!
\brief
Updates the scene based on delta time

\param	dt - delta time
*/
/******************************************************************************/
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

	if (menu.getShowMenuStatus() == true)
	{
		menu.update(dt);
	}
	else if (menu.getShowMenuStatus() == false && Guard1.getCatchPlayerState() == false && Guard2.getCatchPlayerState() == false && winState == false)
	{
		/*Sound = engine->play2D("Sound\\magical_moment.mp3");*/
		menu.update(dt);
		camera.showingMenu = false;
		//Speed of by which Item is translated on Checkout
		if(moveItem >= -4.5 && Peas == true)
		{
			moveItem -=(float)(5*dt);
		}
		else if(moveItem >= -4.5 && Beans == true)
		{
			moveItem -=(float)(5*dt);
		}
		else if(moveItem >= -4.5 && Pizza == true)
		{
			moveItem -=(float)(5*dt);
		}
		else if(moveItem >= -4.5 && Milo == true)
		{
			moveItem -=(float)(5*dt);
		}
		else if(moveItem >= -4.5 && Cereal1 == true)
		{
			moveItem -=(float)(5*dt);
		}
		else if(moveItem >= -4.5 && Cereal2 == true)
		{
			moveItem -=(float)(5*dt);
		}
		else if(moveItem >= -4.5 && Sardine == true)
		{
			moveItem -=(float)(5*dt);
		}
		else if(moveItem >= -4.5 && Lays == true)
		{
			moveItem -=(float)(5*dt);
		}
		else if(moveItem >= -4.5 && Coke == true)
		{
			moveItem -=(float)(5*dt);
		}
		else if(moveItem >= -4.5 && CokeZero == true)
		{
			moveItem -=(float)(5*dt);
		}
		else if(moveItem >= -4.5 && Pepsi == true)
		{
			moveItem -=(float)(5*dt);
		}

		//TIME ATTACK TIMER
		if(TimeAttack == true)
		{
			TAtime -= (float)(dt);
		}
		if(isTAwon == true || isGTPwon == true) 
		{
			messageTime +=(float)(dt);
		}
		if(isTAwon == false && TAstartedOnce > 0)
		{
			messageTime +=(float)(dt);
		}
		if(isGTPwon == false && GTPstartedOnce > 0)
		{
			messageTime +=(float)(dt);
		}
		if(isThiefwon == true)
		{
			messageTime +=(float)(dt);
		}
		std::ostringstream ssTAtime;
		ssTAtime.precision(4);
		ssTAtime << TAtime;
		timeTA = ssTAtime.str();

		//Controls whether objects are affected by light or not
		if(Application::IsKeyPressed('5'))
		{
			B_Light = true;
		}
		if(Application::IsKeyPressed('6'))
		{
			B_Light = false;
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

		//===Character Control===//
		static float ROTATE_SPEED = 50.f;
		static int count = 0;

		movingModel= true;

		if (movingModel == true)
		{
			rotateRightArms += (float)(rotatingRightArm * dt * ROTATE_SPEED);
			rotateLeftLeg += (float)(rotatingLeftLeg * dt * ROTATE_SPEED);
			rotateRightLeg -= (float)(rotatingRightLeg * dt * ROTATE_SPEED);

			if (rotateRightArms >= 405)//rotating right arm
			{
				rotatingRightArm = -1;
				count++;
			}
			if(rotateRightArms <= 330)
			{
				rotatingRightArm = 1;
			}

			if (rotateLeftArms >= 405)//rotatin left arm
			{
				rotatingLeftArm = -1;
			}
			if(rotateLeftArms <= 330)
			{
				rotatingLeftArm = 1;
			}

			if (rotateLeftLeg >= 405)//rotatin left leg
			{
				rotatingLeftLeg = -1;
			}
			if(rotateLeftLeg <= 315)
			{
				rotatingLeftLeg = 1;
			}

			if (rotateRightLeg >= 405)//rotatin right leg
			{
				rotatingRightLeg = 1;
			}
			if(rotateRightLeg <= 315)
			{
				rotatingRightLeg = -1;
			}

			if (count >= 1)
			{
				rotateLeftArms += (float)(rotatingLeftArm * dt * ROTATE_SPEED);
			}
		}
		else if (movingModel == false)
		{
			count = 0;
			rotatingRightArm = 1;
			rotatingLeftArm = 1;
			rotatingRightLeg = 1;
			rotatingLeftLeg = 1;
			if (rotateRightArms > 360)//moving back right arm
			{
				rotateRightArms -= (float)(rotatingRightArm * dt * ROTATE_SPEED);
				if (rotateRightArms <= 360)
				{
					rotateRightArms = 360;
				}
			}
			else if (rotateRightArms < 360)
			{
				rotateRightArms += (float)(rotatingRightArm * dt * ROTATE_SPEED);
				if (rotateRightArms >= 360)
				{
					rotateRightArms = 360;
				}
			}

			if (rotateLeftArms > 360)//moving back left arm
			{
				rotateLeftArms -= (float)(rotatingLeftArm * dt * ROTATE_SPEED);
				if (rotateLeftArms <= 360)
				{
					rotateLeftArms = 360;
				}
			}
			else if (rotateLeftArms < 360)
			{
				rotateLeftArms += (float)(rotatingLeftArm * dt * ROTATE_SPEED);
				if (rotateLeftArms >= 360)
				{
					rotateLeftArms = 360;
				}
			}

			if (rotateRightLeg > 360)//moving back right leg
			{
				rotateRightLeg -= (float)(rotatingRightLeg * dt * ROTATE_SPEED);
				if (rotateRightLeg <= 360)
				{
					rotateRightLeg = 360;
				}
			}
			else if (rotateRightLeg < 360)
			{
				rotateRightLeg += (float)(rotatingRightLeg * dt * ROTATE_SPEED);
				if (rotateRightLeg >= 360)
				{
					rotateRightLeg = 360;
				}
			}

			if (rotateLeftLeg > 360)//moving back left arm
			{
				rotateLeftLeg -= (float)(rotatingRightLeg * dt * ROTATE_SPEED);
				if (rotateLeftLeg <= 360)
				{
					rotateLeftLeg = 360;
				}
			}
			else if (rotateLeftLeg < 360)
			{
				rotateLeftLeg += (float)(rotatingLeftLeg * dt * ROTATE_SPEED);
				if (rotateLeftLeg >= 360)
				{
					rotateLeftLeg = 360;
				}
			}
		}
		if (Application::IsKeyPressed('I'))
		{
			angle += 100 * dt;
		}
		if (Application::IsKeyPressed('O'))
		{
			angle -= 100 * dt;
		}
		/*========================================================
		Animation
		===========================================================*/
		updateDoor(dt);

		/*=======================================================
		Interactions
		==========================================================*/
		updateTakingItem();

		updateCheckingOut();

		updatePuttingBackItem();

		updateTimeAttack();

		updateGTP();

		updateThiefGame();

		updateDustBin();

		updateDustBin();
		/*=======================================================
		Artifical Intelligence
		==========================================================*/
		updateAI(dt);

		/*==============================================================
		DEBUGGING PURPOSES
		=================================================================*/

		//====Camera coordinates===//
		std::ostringstream ss;
		fps = 1/dt;
		ss << fps;
		result = ss.str();

		std::ostringstream ss2;
		ss2 << camera.position.x;
		camerax = ss2.str();

		std::ostringstream ss3;
		ss3 << camera.position.y;
		cameray = ss3.str();

		std::ostringstream ss4;
		ss4 << camera.position.z;
		cameraz = ss4.str();

		//====Camera Target======//
		std::ostringstream ss5;
		ss5 << camera.target.x;
		viewx = ss5.str();

		std::ostringstream ss6;
		ss6 << camera.target.y;
		viewy = ss6.str();

		std::ostringstream ss7;
		ss7 <<  camera.target.z;
		viewz = ss7.str();

		//====Player Money===//
		std::ostringstream ss8;
		ss8 <<  player.getMoney();
		Cash = ss8.str();

		//================Item Inventory Image=================//
		static float elapsedTime1 = 0, elapsedTime2 = 0;
		elapsedTime1 = fmod(Timer.getElapsedTime(), 1);

		if (elapsedTime2 <= 0.5)
		{
			elapsedTime2 += elapsedTime1;
		}
		if(Application::IsKeyPressed(VK_TAB) && elapsedTime2 >= 0.5)
		{
			if (showInventory == false)
			{		
				showInventory = true;
			}
			else
			{
				showInventory = false;
			}
			elapsedTime2 -= 0.5;
		}
		//================Testing =================//
		//cout << Container.size() << endl;
		if (Application::IsKeyPressed('M'))
			moving += (float) (10 * dt);
		if (Application::IsKeyPressed('N'))
			moving -= (float) (10 * dt);
		//moving -= (float) (5 * dt);
		//cout<<moving<<endl;
		camera.Update(dt);

		Page.setCPlayer(player);

		Passerby[0].update(dt, camera.position);
		Passerby[0].FindPlayerDistanceDifferencePasserby(camera.position);
		Passerby[1].update(dt, camera.position);
		Passerby[1].FindPlayerDistanceDifferencePasserby(camera.position);
		Passerby[2].update(dt, camera.position);
		Passerby[2].FindPlayerDistanceDifferencePasserby(camera.position);

		if ((camera.position - Passerby[0].getPasserbyPosition()).Length() < 6 ||
			(camera.position - Passerby[1].getPasserby2Position()).Length() < 6 ||
			(camera.position - Passerby[2].getPasserby2Position()).Length() < 6)
		{
			camera.CollisionWithAi = true;
		}

		else if ((camera.position - Passerby[0].getPasserbyPosition()).Length() > 6 ||
			(camera.position - Passerby[1].getPasserby2Position()).Length() > 6 ||
			(camera.position - Passerby[2].getPasserby2Position()).Length() > 6)
		{
			camera.CollisionWithAi = false;
		}
		
		if ((Theifnpc.getPosition() - camera.position).Length() < 6 && Guard1.getState() == 1 ||
			(Theifnpc.getPosition() - camera.position).Length() < 6 && Guard2.getState() == 1)
		{
			winState = true;
		}
	}

	//=====================FOR RESETTING PURPOSE================//
	if (Application::IsKeyPressed('R'))
	{
		ResetAll(dt);
	}
}
/******************************************************************************/
/*!
\brief
Renders the Skybox in the scene
*/
/******************************************************************************/
void StudioProject::RenderSkybox()
{
	//Back
	modelStack.PushMatrix();
	modelStack.Translate(0.f, 0.f, (worldsize/2) - 1);
	modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(worldsize, worldsize, worldsize);
	RenderMesh(meshList[GEO_BACKSKY], false);
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
	RenderMesh(meshList[GEO_FRONTSKY], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//Top
	modelStack.PushMatrix();
	modelStack.Rotate(360,0,1,0);
	modelStack.Translate(0.f, (worldsize/2) - 1, 0.f);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(270, 0, 0, 1);
	modelStack.Scale(worldsize, worldsize, worldsize);
	RenderMesh(meshList[GEO_SKY], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0.f, (-worldsize/2) + 1, 0.f);
	modelStack.Rotate(90,1,0,0);
	modelStack.Scale(worldsize, worldsize, worldsize);
	RenderMesh(meshList[GEO_BOTTOMSKY], false);
	modelStack.PopMatrix();

	//RIGHT
	modelStack.PushMatrix();
	modelStack.Rotate(90,1,0,0);
	modelStack.Translate((worldsize/2) - 1, 0.f, 0.f);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(270, 0, 0, 1);
	modelStack.Scale(worldsize, worldsize, worldsize);
	RenderMesh(meshList[GEO_RIGHTSKY], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	//LEFT
	modelStack.PushMatrix();
	modelStack.Rotate(-90,1,0,0);
	modelStack.PushMatrix();
	modelStack.Translate((-worldsize/2) + 1, 0.f, 0.f);
	modelStack.Rotate(90, 0, 1, 0);
	modelStack.PushMatrix();
	modelStack.Rotate(90, 0, 0, 1);
	modelStack.Scale(worldsize, worldsize, worldsize);
	RenderMesh(meshList[GEO_LEFTSKY], false);
	modelStack.PopMatrix();
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//RenderMesh(meshList[GEO_FLOOR], false);
	modelStack.PopMatrix();
}
/******************************************************************************/
/*!
\brief
Renders the Supermarket layout in the scene
*/
/******************************************************************************/
void StudioProject::RenderSupermarket()
{
	/*===============================================================
	Level 1 Of Supermarket
	================================================================*/

	modelStack.PushMatrix();
	modelStack.Translate(-65, -0.5f, 0);
	modelStack.Rotate(90, 1, 0, 0);
	modelStack.Scale(250,250,250);
	RenderMesh(meshList[GEO_ROAD],false);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	//modelStack.Rotate(180, 0, 1, 0);
	modelStack.Scale(5,5,5);
	RenderMesh(meshList[GEO_MARKET],B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-28, -1, -15);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_CASHIER],B_Light);

	modelStack.PushMatrix();
	modelStack.Translate(0.5, 3.7, 3.5);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(0.8, 0.8, 0.8);
	RenderMesh(meshList[GEO_CASHREG],B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-28, -1, 3);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_CASHIER],B_Light);

	modelStack.PushMatrix();
	modelStack.Translate(0.5, 3.7, 3.5);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(0.8, 0.8, 0.8);
	RenderMesh(meshList[GEO_CASHREG],B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-28, -1, 20);
	modelStack.Rotate(180, 0, 1, 0);
	RenderMesh(meshList[GEO_CASHIER],B_Light);

	modelStack.PushMatrix();
	modelStack.Translate(0.5, 3.7, 3.5);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(0.8, 0.8, 0.8);
	RenderMesh(meshList[GEO_CASHREG],B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-62, 0, -21.4);
	RenderMesh(meshList[GEO_DUSTBIN],B_Light);
	modelStack.PopMatrix();
	//x=-66 y= 4.8 z= -21.4

	//Extreme left cold food shelf
	for(int i = -2; i < 3; ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate(i*14,-1,-91);
		modelStack.Rotate(90,0,-1,0);
		RenderMesh(meshList[GEO_COLDFOODSHELF],B_Light);
		modelStack.PopMatrix();
	}
	//Back of market (Cold food shelf)
	for(int i = -5; i < 5; ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate(51.5,-1,i*14);
		modelStack.Rotate(180,0,-1,0);
		RenderMesh(meshList[GEO_COLDFOODSHELF],B_Light);
		modelStack.PopMatrix();
	}

	//Left side (metal Shelf 2)
	for(int i = -5; i <4; ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate(i*6, -1, -58);
		modelStack.Rotate(90,0,1,0);
		RenderMesh(meshList[GEO_SHELF2],B_Light);
		modelStack.PopMatrix();
	}

	//Left side wooden shelf
	for(int i = -2; i <2; ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate(i*12, -1 , -35);
		RenderMesh(meshList[GEO_SHELF],B_Light);
		modelStack.PopMatrix();
	}


	//Right side (metal Shelf 2)
	for(int i = -5; i <4; ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate(i*6, -1, 58);
		modelStack.Rotate(90,0,1,0);
		RenderMesh(meshList[GEO_SHELF2],B_Light);
		modelStack.PopMatrix();
	}

	//Right side wooden shelf
	for(int i = -2; i <2; ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate(i*12, -1 , 35);
		RenderMesh(meshList[GEO_SHELF],B_Light);
		modelStack.PopMatrix();
	}

	//Middle metal shelf
	for(int i = -1; i<3; ++i)
	{
		modelStack.PushMatrix();
		modelStack.Translate(11, -1, i*6);
		RenderMesh(meshList[GEO_SHELF2],B_Light);
		modelStack.PopMatrix();
	}
	//Right most railing (POV from the entrance)
	modelStack.PushMatrix();
	modelStack.Translate(-21,-1,26);
	RenderMesh(meshList[GEO_RAIL],B_Light);
	modelStack.PopMatrix();

	//middle most railing (POV from the entrance)
	modelStack.PushMatrix();
	modelStack.Translate(-21,-1,8);
	RenderMesh(meshList[GEO_RAIL],B_Light);
	modelStack.PopMatrix();

	//left most railing (POV from the entrance)
	modelStack.PushMatrix();
	modelStack.Translate(-21,-1,1-11);
	RenderMesh(meshList[GEO_RAIL],B_Light);
	modelStack.PopMatrix();

	//=========Rendering of second level ==================//

	//Railings near the escalator 
	for(int x = -2; x < 3; x ++ )
	{
		modelStack.PushMatrix();
		modelStack.Translate(x*9.5,20,61.5);
		RenderMesh(meshList[GEO_RAIL],B_Light);
		modelStack.PopMatrix();
	}

	modelStack.PushMatrix();
	modelStack.Translate(27,20,61.5);
	modelStack.Scale(0.85,1,1);
	RenderMesh(meshList[GEO_RAIL],B_Light);
	modelStack.PopMatrix();

	//Railings across the elevator (2nd floor)
	modelStack.PushMatrix();
	modelStack.Translate(-26.8,20,62.9);
	modelStack.Rotate(90,0,1,0);
	RenderMesh(meshList[GEO_RAIL],B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-26.8,20,71.9);
	modelStack.Rotate(90,0,1,0);
	RenderMesh(meshList[GEO_RAIL],B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-26.8,20,80.9);
	modelStack.Rotate(90,0,1,0);
	RenderMesh(meshList[GEO_RAIL],B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(-26.8,20,89.5);
	modelStack.Rotate(90,0,1,0);
	modelStack.Scale(0.5,1,1);
	RenderMesh(meshList[GEO_RAIL],B_Light);
	modelStack.PopMatrix();

	//=============2nd Floor left row shelf===============//
	for(int x = 2; x < 4; x++)
	{
		//Wooden shelf
		modelStack.PushMatrix();
		modelStack.Translate(5,19.8,x*12);
		modelStack.Rotate(90,0,1,0);
		RenderMesh(meshList[GEO_SHELF],B_Light);
		modelStack.PopMatrix();
	}

	for(int x = 3; x < 8; x++)
	{
		//Metal shelf
		modelStack.PushMatrix();
		modelStack.Translate(-14.5,20,x*6);
		RenderMesh(meshList[GEO_SHELF2],B_Light);
		modelStack.PopMatrix();
	}

	for(int x = 3; x < 8; x++)
	{
		//Metal shelf
		modelStack.PushMatrix();
		modelStack.Translate(23,20,x*6);
		RenderMesh(meshList[GEO_SHELF2],B_Light);
		modelStack.PopMatrix();
	}

	// =========2nd Floor middle row shelf ======== //

	//Wooden shelf
	modelStack.PushMatrix();
	modelStack.Translate(5,19.8,-12);
	modelStack.Rotate(90,0,1,0);
	RenderMesh(meshList[GEO_SHELF],B_Light);
	modelStack.PopMatrix();

	for(int x = -3; x < 0; x++)
	{
		//Metal shelf
		modelStack.PushMatrix();
		modelStack.Translate(-14.5,20,x*6);
		RenderMesh(meshList[GEO_SHELF2],B_Light);
		modelStack.PopMatrix();
	}

	for(int x = -3; x < 0; x++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(23,20,x*6);
		RenderMesh(meshList[GEO_SHELF2],B_Light);
		modelStack.PopMatrix();
	}

	//===============2nd Floor Extreme right row shelf==================//
	for(int x = -5.5; x < -3.5; x++)
	{
		//Wooden shelf
		modelStack.PushMatrix();
		modelStack.Translate(5,19.8,x*12);
		modelStack.Rotate(90,0,1,0);
		RenderMesh(meshList[GEO_SHELF],B_Light);
		modelStack.PopMatrix();
	}

	for(int x = -11; x < -6; x++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-14.5,20,x*6);
		RenderMesh(meshList[GEO_SHELF2],B_Light);
		modelStack.PopMatrix();
	}

	for(int x = -11; x < -6; x++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(23,20,x*6);
		RenderMesh(meshList[GEO_SHELF2],B_Light);
		modelStack.PopMatrix();
	}

	//=======================2nd floor Frozen food shelf====================//
	for(int x = -5; x < 4 ; x++)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-52,20,x*14);
		RenderMesh(meshList[GEO_COLDFOODSHELF],B_Light);
		modelStack.PopMatrix();
	}
}
/******************************************************************************/
/*!
\brief
Render the Items in the Supermarket in the scene
*/
/******************************************************************************/
void StudioProject::RenderItems()
{
	for(int i = 0; i < Container.size(); ++i) //Container 1
	{
		if(Container[i].getRender() == true)
		{
			//========MIDDLE ROW FRONT=========//
			modelStack.PushMatrix();
			modelStack.LoadMatrix(Container[i].getTRS());
			modelStack.Rotate(90,0,1,0);
			RenderMesh(Container[i].getMesh(),B_Light);
			modelStack.PopMatrix(); //pop back to origin
		}
	}
	for(int i = 0; i < Container2.size(); ++i) //Container 2
	{
		if(Container2[i].getRender() == true)
		{
			//========MIDDLE ROW BACK=========//
			modelStack.PushMatrix();
			modelStack.LoadMatrix(Container2[i].getTRS());
			modelStack.Rotate(270,0,1,0);
			RenderMesh(Container2[i].getMesh(),B_Light);
			modelStack.PopMatrix(); //pop back to origin
		}
	}
	for(int i = 0; i < Container2.size(); ++i) //Container 3
	{
		if(Container2[i].getRender() == true)
		{
			//========MIDDLE ROW BACK=========//
			modelStack.PushMatrix();
			modelStack.LoadMatrix(Container2[i].getTRS());
			modelStack.Rotate(270,0,1,0);
			RenderMesh(Container2[i].getMesh(),B_Light);
			modelStack.PopMatrix(); //pop back to origin
		}
	}
	for(int i = 0; i < Container3.size(); ++i) //Container 3
	{
		if(Container3[i].getRender() == true)
		{
			//========MIDDLE ROW BACK=========//
			modelStack.PushMatrix();
			modelStack.LoadMatrix(Container3[i].getTRS());
			modelStack.Rotate(270,0,1,0);
			RenderMesh(Container3[i].getMesh(),B_Light);
			modelStack.PopMatrix(); //pop back to origin
		}
	}
	for(int i = 0; i < Container4.size(); ++i) //Container 4
	{
		if(Container4[i].getRender() == true)
		{
			//========MIDDLE ROW BACK=========//
			modelStack.PushMatrix();
			modelStack.LoadMatrix(Container4[i].getTRS());
			modelStack.Rotate(270,0,1,0);
			RenderMesh(Container4[i].getMesh(),B_Light);
			modelStack.PopMatrix(); //pop back to origin
		}
	}
	for(int i = 0; i < Container5.size(); ++i) //Container 5
	{
		if(Container5[i].getRender() == true)
		{
			//========MIDDLE ROW BACK=========//
			modelStack.PushMatrix();
			modelStack.LoadMatrix(Container5[i].getTRS());
			modelStack.Rotate(180,0,1,0);
			RenderMesh(Container5[i].getMesh(),B_Light);
			modelStack.PopMatrix(); //pop back to origin
		}
	}
	for(int i = 0; i < Container6.size(); ++i) //Container 6
	{
		if(Container6[i].getRender() == true)
		{
			//========MIDDLE ROW BACK=========//
			modelStack.PushMatrix();
			modelStack.LoadMatrix(Container6[i].getTRS());
			//modelStack.Rotate(270,0,1,0);
			RenderMesh(Container6[i].getMesh(),B_Light);
			modelStack.PopMatrix(); //pop back to origin
		}
	}

	for(int i = 0; i < Container7.size(); ++i) //Container 7
	{
		if(Container7[i].getRender() == true)
		{
			//========MIDDLE ROW BACK=========//
			modelStack.PushMatrix();
			modelStack.LoadMatrix(Container7[i].getTRS());
			//modelStack.Rotate(270,0,1,0);
			RenderMesh(Container7[i].getMesh(),B_Light);
			modelStack.PopMatrix(); //pop back to origin
		}
	}

	for(int i = 0; i < Container8.size(); ++i) //Container 8
	{
		if(Container8[i].getRender() == true)
		{
			//========MIDDLE ROW BACK=========//
			modelStack.PushMatrix();
			modelStack.LoadMatrix(Container8[i].getTRS());
			modelStack.Rotate(180,0,1,0);
			RenderMesh(Container8[i].getMesh(),B_Light);
			modelStack.PopMatrix(); //pop back to origin
		}
	}
	for(int i = 0; i < Container9.size(); ++i) //Container 9
	{
		if(Container9[i].getRender() == true)
		{
			//========MIDDLE ROW BACK=========//
			modelStack.PushMatrix();
			modelStack.LoadMatrix(Container9[i].getTRS());
			modelStack.Rotate(180,0,1,0);
			RenderMesh(Container9[i].getMesh(),B_Light);
			modelStack.PopMatrix(); //pop back to origin
		}
	}
	for(int i = 0; i < Container10.size(); ++i) //Container 10
	{
		if(Container10[i].getRender() == true)
		{
			//========MIDDLE ROW BACK=========//
			modelStack.PushMatrix();
			modelStack.LoadMatrix(Container10[i].getTRS());
			modelStack.Rotate(180,0,1,0);
			RenderMesh(Container10[i].getMesh(),B_Light);
			modelStack.PopMatrix(); //pop back to origin
		}
	}
	for(int i = 0; i < Container11.size(); ++i) //Container 11
	{
		if(Container11[i].getRender() == true)
		{
			//========MIDDLE ROW BACK=========//
			modelStack.PushMatrix();
			modelStack.LoadMatrix(Container11[i].getTRS());
			modelStack.Rotate(180,0,1,0);
			RenderMesh(Container11[i].getMesh(),B_Light);
			modelStack.PopMatrix(); //pop back to origin
		}
	}
	for(int i = 0; i < Container12.size(); ++i) //Container 12
	{
		if(Container12[i].getRender() == true)
		{
			//========MIDDLE ROW BACK=========//
			modelStack.PushMatrix();
			modelStack.LoadMatrix(Container12[i].getTRS());
			//modelStack.Rotate(180,0,1,0);
			RenderMesh(Container12[i].getMesh(),B_Light);
			modelStack.PopMatrix(); //pop back to origin
		}
	}

	for(int i = 0; i < Container13.size(); ++i) //Container 13
	{
		if(Container13[i].getRender() == true)
		{
			//========MIDDLE ROW BACK=========//
			modelStack.PushMatrix();
			modelStack.LoadMatrix(Container13[i].getTRS());
			modelStack.Rotate(90,0,1,0);
			RenderMesh(Container13[i].getMesh(),B_Light);
			modelStack.PopMatrix(); //pop back to origin
		}
	}
	//Camera target
	/*modelStack.PushMatrix();
	modelStack.Translate(camera.target.x,camera.target.y, camera.target.z);
	modelStack.Rotate(90,0,1,0);
	modelStack.Scale(0.5,0.5,0.5);
	RenderMesh(meshList[GEO_AXES],false);
	modelStack.PopMatrix();*/

	//modelStack.PushMatrix();
	//modelStack.Translate(0, 0, 6);
	//modelStack.Scale(2, 2, 2);
	//RenderMesh(meshList[GEO_COKE_CAN],B_Light);// Coke
	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//modelStack.Translate(0, 0, 5);
	//RenderMesh(meshList[GEO_DRINKCAN2],B_Light); 
	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	////modelStack.Translate(8, 0, 0);
	//modelStack.Translate(0, 0, 6);
	//modelStack.Scale(2, 2, 2);
	//RenderMesh(meshList[GEO_PEPSI_CAN],B_Light); // Pepsi
	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//modelStack.Translate(0, 0, 4);
	//modelStack.Rotate(90,0,1,0);
	//modelStack.Scale(2, 2, 2);
	//RenderMesh(meshList[GEO_CEREALBOX1],B_Light);
	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//modelStack.Translate(0, 0, 10);
	//modelStack.Rotate(-90,0,1,0);
	//modelStack.Scale(1.2, 1.2, 1.2);
	//RenderMesh(meshList[GEO_CEREALBOX2],B_Light);
	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//modelStack.Translate(0, 0, -2);
	//modelStack.Rotate(-90,0,1,0);
	//RenderMesh(meshList[GEO_PIZZABOX],B_Light);
	//modelStack.PopMatrix();

	//modelStack.PushMatrix();
	//modelStack.Translate(0, 0, -4);
	//modelStack.Rotate(-90,0,1,0);
	//RenderMesh(meshList[GEO_POTATOCHIPS],B_Light);
	//modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(camera.target.x + 0.67, camera.target.y+ translateMoneyY, camera.target.z + translateMoneyZ);
	modelStack.Rotate(45, 1, 0, 0);
	modelStack.Scale(0.3, 0.3, 0.3);
	//RenderMesh(meshList[GEO_MONEY],B_Light);
	modelStack.PopMatrix();

}
/******************************************************************************/
/*!
\brief
Renders the Character model in the scene
*/
/******************************************************************************/
void StudioProject::RenderModel()
{
	/*=============================================
	Time Attack NPC
	===============================================*/
	modelStack.PushMatrix();
	modelStack.Translate(TAnpc.getPosition().x,TAnpc.getPosition().y,TAnpc.getPosition().z);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(1.2, 1.2, 1.2);

	modelStack.PushMatrix();
	modelStack.Translate(0, 3.6, 0);
	RenderMesh(TAnpc.getHead(), B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 1.5, 0);
	RenderMesh(TAnpc.getTorso(), B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 3 + 0.2, 0);
	//modelStack.Rotate(1+ rotateRightArms, 1+rotateRightArms, 0, 0);
	modelStack.Translate(-0.8, -1.5 + 0.2, 0);
	RenderMesh(TAnpc.getRHand(), B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 3 + 0.2, 0);
//	modelStack.Rotate(1 + rotateLeftArms, 1 + rotateLeftArms, 0, 0);
	modelStack.Translate(0.8, -1.5 + 0.2, 0);
	RenderMesh(TAnpc.getLHand(), B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0.4, 0);
	modelStack.PushMatrix();
	modelStack.Translate(0.3, 1, 0);
	//modelStack.Rotate(1+ rotateLeftLeg, 1+ rotateLeftLeg, 0, 0);
	modelStack.Translate(0, -1.4, 0);
	RenderMesh(TAnpc.getLLeg(), B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0.4, 0);
	modelStack.PushMatrix();
	modelStack.Translate(-0.3, 1, 0);
	//modelStack.Rotate(1+ rotateRightLeg, 1+rotateRightLeg, 0, 0);
	modelStack.Translate(0, -1.4, 0);
	RenderMesh(TAnpc.getRLeg(), B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(0.5, 0.5, 0.5);
	modelStack.Rotate(180, 0, 180, 0);
	modelStack.Translate(-2, 10, 0);
	RenderText(meshList[GEO_TEXT], "Time Attack", Color(0, 0, 1));
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	/*===============================================
	Thief NPC
	===================================================*/
	modelStack.PushMatrix();
	modelStack.Translate(Theifnpc.getPosition().x,Theifnpc.getPosition().y,Theifnpc.getPosition().z);
	modelStack.Rotate(-90, 0, 1, 0);
	modelStack.Scale(1.2, 1.2, 1.2);

	modelStack.PushMatrix();
	modelStack.Translate(0, 3.6, 0);
	RenderMesh(Theifnpc.getHead(), B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 1.5, 0);
	RenderMesh(Theifnpc.getTorso(), B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 3 + 0.2, 0);
	//modelStack.Rotate(1+ rotateRightArms, 1+rotateRightArms, 0, 0);
	modelStack.Translate(-0.8, -1.5 + 0.2, 0);
	RenderMesh(Theifnpc.getRHand(), B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 3 + 0.2, 0);
	//modelStack.Rotate(1 + rotateLeftArms, 1 + rotateLeftArms, 0, 0);
	modelStack.Translate(0.8, -1.5 + 0.2, 0);
	RenderMesh(Theifnpc.getLHand(), B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0.4, 0);
	modelStack.PushMatrix();
	modelStack.Translate(0.3, 1, 0);
	//modelStack.Rotate(1+ rotateLeftLeg, 1+ rotateLeftLeg, 0, 0);
	modelStack.Translate(0, -1.4, 0);
	RenderMesh(Theifnpc.getLLeg(), B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0.4, 0);
	modelStack.PushMatrix();
	modelStack.Translate(-0.3, 1, 0);
	//modelStack.Rotate(1+ rotateRightLeg, 1+rotateRightLeg, 0, 0);
	modelStack.Translate(0, -1.4, 0);
	RenderMesh(Theifnpc.getRLeg(), B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(0.5, 0.5, 0.5);
	modelStack.Rotate(180, 0, 180, 0);
	modelStack.Translate(-5, 10, 0);
	RenderText(meshList[GEO_TEXT], "Theif Master", Color(0, 0, 1));
	modelStack.PopMatrix();

	modelStack.PopMatrix();

	/*===========================================
	Guess The Price NPC
	=============================================*/
	modelStack.PushMatrix();
	modelStack.Translate(GTPnpc.getPosition().x,GTPnpc.getPosition().y,GTPnpc.getPosition().z);
	modelStack.Rotate(0, 0, 1, 0);
	modelStack.Scale(1.2, 1.2, 1.2);

	modelStack.PushMatrix();
	modelStack.Translate(0, 3.6, 0);
	RenderMesh(GTPnpc.getHead(), B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 1.5, 0);
	RenderMesh(GTPnpc.getTorso(), B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 3 + 0.2, 0);
	//modelStack.Rotate(1+ rotateRightArms, 1+rotateRightArms, 0, 0);
	modelStack.Translate(-0.8, -1.5 + 0.2, 0);
	RenderMesh(GTPnpc.getRHand(), B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 3 + 0.2, 0);
	//modelStack.Rotate(1 + rotateLeftArms, 1 + rotateLeftArms, 0, 0);
	modelStack.Translate(0.8, -1.5 + 0.2, 0);
	RenderMesh(GTPnpc.getLHand(), B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0.4, 0);
	modelStack.PushMatrix();
	modelStack.Translate(0.3, 1, 0);
	//modelStack.Rotate(1+ rotateLeftLeg, 1+ rotateLeftLeg, 0, 0);
	modelStack.Translate(0, -1.4, 0);
	RenderMesh(GTPnpc.getLLeg(), B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0.4, 0);
	modelStack.PushMatrix();
	modelStack.Translate(-0.3, 1, 0);
	//modelStack.Rotate(1+ rotateRightLeg, 1+rotateRightLeg, 0, 0);
	modelStack.Translate(0, -1.4, 0);
	RenderMesh(GTPnpc.getRLeg(), B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Scale(0.5, 0.5, 0.5);
	modelStack.Rotate(180, 0, 180, 0);
	modelStack.Translate(-6, 10, 0);
	RenderText(meshList[GEO_TEXT], "Guess The Price", Color(0, 0, 1));
	modelStack.PopMatrix();

	modelStack.PopMatrix();
}
/******************************************************************************/
/*!
\brief
Renders the Cashier model in the scene
*/
/******************************************************************************/
void StudioProject::RenderCashier()
{
	modelStack.PushMatrix();
	modelStack.Translate(charPosition.x, 0, charPosition.z);
	modelStack.Rotate(angle, 0, angle, 1);

	modelStack.PushMatrix();
	modelStack.Translate(0, -2.285f, 0);
	RenderMesh(meshList[cashierHead], B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 1.5f, 0);
	RenderMesh(meshList[cashierTorso], B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 3.f + 0.2f, 0);
	//modelStack.Rotate(1+ rotateRightArms, 1+rotateRightArms, 0, 0);
	modelStack.Translate(-0.8f, -1.5f + 0.2f, 0);
	RenderMesh(meshList[cashierRightHand], B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 3.f + 0.2f, 0);
	//modelStack.Rotate(1 + rotateLeftArms, 1 + rotateLeftArms, 0, 0);
	modelStack.Translate(0.8f, -1.5f + 0.2f, 0);
	RenderMesh(meshList[cashierLeftHand], B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0.4f, 0);
	modelStack.PushMatrix();
	modelStack.Translate(0.3f, 1, 0);
	//modelStack.Rotate(1+ rotateLeftLeg, 1+ rotateLeftLeg, 0, 0);
	modelStack.Translate(0, -1.4f, 0);
	RenderMesh(meshList[cashierLeftLeg], B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0.4f, 0);
	modelStack.PushMatrix();
	modelStack.Translate(-0.3f, 1, 0);
	//modelStack.Rotate(1+ rotateRightLeg, 1+rotateRightLeg, 0, 0);
	modelStack.Translate(0, -1.4f, 0);
	RenderMesh(meshList[cashierRightLeg], B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix(); //Notation
	modelStack.Scale(0.5f, 0.5f, 0.5f);
	modelStack.Rotate(180, 0, 180, 0);
	modelStack.Translate(-3.f, 10.f, 0);
	RenderText(meshList[GEO_TEXT], "Cashier", Color(0, 0, 1));
	modelStack.PopMatrix();

	modelStack.PopMatrix();
}
/******************************************************************************/
/*!
\brief
Renders the Guard model in the scene
*/
/******************************************************************************/
void StudioProject::RenderGuard()
{
	/*======================================================
	GUARD 1
	========================================================*/
	modelStack.PushMatrix();
	modelStack.Translate(Guard1.getGuardPosition().x, 0, Guard1.getGuardPosition().z);
	if(Guard1.getState() == 1)
	{
		modelStack.Rotate(Guard1.getDerivedAngle(), 0, 1, 0);
	}
	modelStack.Scale(1.2f, 1.2f, 1.2f);

	modelStack.PushMatrix();
	modelStack.Translate(0, -2.285f, 0);
	RenderMesh(Guard1.getHead(), B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 1.5f, 0);
	RenderMesh(Guard1.getTorso(), B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 3 + 0.2f, 0);
	if (Guard1.getState() == 1)
	{
		modelStack.Rotate(1+ rotateRightArms, 1+rotateRightArms, 0, 0);
	}
	modelStack.Translate(-0.8f, -1.5f + 0.2f, 0);
	RenderMesh(Guard1.getRHand(), B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 3.f + 0.2f, 0);
	if (Guard1.getState() == 1)
	{
		modelStack.Rotate(1 + rotateLeftArms, 1 + rotateLeftArms, 0, 0);
	}
	modelStack.Translate(0.8f, -1.5f + 0.2f, 0);
	RenderMesh(Guard1.getLHand(), B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0.4f, 0);
	modelStack.PushMatrix();
	modelStack.Translate(0.3f, 1, 0);
	if (Guard1.getState() == 1)
	{
		modelStack.Rotate(1+ rotateLeftLeg, 1+ rotateLeftLeg, 0, 0);
	}
	modelStack.Translate(0, -1.4f, 0);
	RenderMesh(Guard1.getLLeg(), B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0.4f, 0);
	modelStack.PushMatrix();
	modelStack.Translate(-0.3f, 1, 0);
	if (Guard1.getState() == 1)
	{
		modelStack.Rotate(1+ rotateRightLeg, 1+rotateRightLeg, 0, 0);
	}
	modelStack.Translate(0, -1.4f, 0);
	RenderMesh(Guard1.getRLeg(), B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix(); //Notation
	modelStack.Scale(0.5f, 0.5f, 0.5f);
	modelStack.Rotate(180, 0, 180, 0);
	modelStack.Translate(-2, 10, 0);
	RenderText(meshList[GEO_TEXT], "Guard", Color(0, 0, 1));
	modelStack.PopMatrix();

	modelStack.PopMatrix();


	/*======================================================
	GUARD 2
	========================================================*/
	modelStack.PushMatrix();
	modelStack.Translate(Guard2.getGuardPosition().x, 0, Guard2.getGuardPosition().z);
	if(Guard1.getState() == 1)
	{
		modelStack.Rotate(Guard2.getDerivedAngle(), 0, 1, 0);
	}
	modelStack.Scale(1.2f, 1.2f, 1.2f);

	modelStack.PushMatrix();
	modelStack.Translate(0, -2.285f, 0);
	RenderMesh(Guard2.getHead(), B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 1.5f, 0);
	RenderMesh(Guard2.getTorso(), B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 3.f + 0.2f, 0);
	if (Guard2.getState() == 1)
	{
		modelStack.Rotate(1+ rotateRightArms, 1+rotateRightArms, 0, 0);
	}
	modelStack.Translate(-0.8f, -1.5f + 0.2f, 0);
	RenderMesh(Guard2.getRHand(), B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 3.f + 0.2f, 0);
	if (Guard2.getState() == 1)
	{
		modelStack.Rotate(1 + rotateLeftArms, 1 + rotateLeftArms, 0, 0);
	}
	modelStack.Translate(0.8f, -1.5f + 0.2f, 0);
	RenderMesh(Guard2.getLHand(), B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0.4f, 0);
	modelStack.PushMatrix();
	modelStack.Translate(0.3f, 1, 0);
	if (Guard2.getState() == 1)
	{
		modelStack.Rotate(1+ rotateLeftLeg, 1+ rotateLeftLeg, 0, 0);
	}
	modelStack.Translate(0, -1.4f, 0);
	RenderMesh(Guard2.getLLeg(), B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0.4f, 0);
	modelStack.PushMatrix();
	modelStack.Translate(-0.3f, 1, 0);
	if (Guard2.getState() == 1)
	{
		modelStack.Rotate(1+ rotateRightLeg, 1+rotateRightLeg, 0, 0);
	}
	modelStack.Translate(0, -1.4f, 0);
	RenderMesh(Guard2.getRLeg(), B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix(); //Notation
	modelStack.Scale(0.5f, 0.5f, 0.5f);
	modelStack.Rotate(180, 0, 180, 0);
	modelStack.Translate(-2, 10, 0);
	RenderText(meshList[GEO_TEXT], "Guard", Color(0, 0, 1));
	modelStack.PopMatrix();

	modelStack.PopMatrix();
}
/******************************************************************************/
/*!
\brief
Renders the Customer model in the scene
*/
/******************************************************************************/
void StudioProject::RenderCustomer()
{
	modelStack.PushMatrix();
	modelStack.Translate(charPosition.x, 0, charPosition.z);
	modelStack.Rotate(angle, 0, angle, 1);

	modelStack.PushMatrix();
	modelStack.Translate(0, -2.285f, 0);
	RenderMesh(meshList[customerHead], B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 1.5f, 0);
	RenderMesh(meshList[customerTorso], B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 3.f + 0.2f, 0);
	modelStack.Rotate(1+ rotateRightArms, 1+rotateRightArms, 0, 0);
	modelStack.Translate(-0.8f, -1.5f + 0.2f, 0);
	RenderMesh(meshList[customerRightHand], B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 3.f + 0.2f, 0);
	modelStack.Rotate(1 + rotateLeftArms, 1 + rotateLeftArms, 0, 0);
	modelStack.Translate(0.8f, -1.5f + 0.2f, 0);
	RenderMesh(meshList[customerLeftHand], B_Light);
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0.4f, 0);
	modelStack.PushMatrix();
	modelStack.Translate(0.3f, 1, 0);
	modelStack.Rotate(1+ rotateLeftLeg, 1+ rotateLeftLeg, 0, 0);
	modelStack.Translate(0, -1.4f, 0);
	RenderMesh(meshList[customerLeftLeg], B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix();
	modelStack.Translate(0, 0.4f, 0);
	modelStack.PushMatrix();
	modelStack.Translate(-0.3f, 1, 0);
	modelStack.Rotate(1+ rotateRightLeg, 1+rotateRightLeg, 0, 0);
	modelStack.Translate(0, -1.4f, 0);
	RenderMesh(meshList[customerRightLeg], B_Light);
	modelStack.PopMatrix();
	modelStack.PopMatrix();

	modelStack.PushMatrix(); //Notation
	modelStack.Scale(0.5f, 0.5f, 0.5f);
	modelStack.Rotate(180, 0, 180, 0);
	modelStack.Translate(-3.f, 10.f, 0);
	RenderText(meshList[GEO_TEXT], "Customer", Color(0, 0, 1));
	modelStack.PopMatrix();

	modelStack.PopMatrix();
}
/******************************************************************************/
/*!
\brief
Renders the Player Information on the screen
*/
/******************************************************************************/
void StudioProject::RenderPlayerInfo()
{
	RenderTextOnScreen(meshList[GEO_TEXT],"Money: " + Cash, Color(0, 0, 1), 3.f, 1.f, 18.f);
}
/******************************************************************************/
/*!
\brief
Renders the Lights in Level 1 of the Supermarket in the scene
*/
/******************************************************************************/
void StudioProject::RenderLevel1Lights()
{
	//=====Lights for first floor====//

	//Right back Lightball
	modelStack.PushMatrix();
	modelStack.Translate(lights[1].position.x, lights[1].position.y, lights[1].position.z);
	modelStack.Scale(3.f,0.5f,8.f);
	RenderMesh(meshList[GEO_LIGHTBALL2], false);
	modelStack.PopMatrix();

	//Center back Lightball
	modelStack.PushMatrix();
	modelStack.Translate(lights[0].position.x, lights[0].position.y, lights[0].position.z);
	modelStack.Scale(3.f,0.5f,8.f);
	RenderMesh(meshList[GEO_LIGHTBALL], false);
	modelStack.PopMatrix();

	//Left back Lightball
	modelStack.PushMatrix();
	modelStack.Translate(lights[2].position.x, lights[2].position.y, lights[2].position.z);
	modelStack.Scale(3.f,0.5f,8.f);
	RenderMesh(meshList[GEO_LIGHTBALL3], false);
	modelStack.PopMatrix();

	//Left back Lightball
	modelStack.PushMatrix();
	modelStack.Translate(lights[3].position.x, lights[3].position.y, lights[3].position.z);
	modelStack.Scale(3.f,0.5f,8.f);
	RenderMesh(meshList[GEO_LIGHTBALL4], false);
	modelStack.PopMatrix();

	//Left back Lightball
	modelStack.PushMatrix();
	modelStack.Translate(lights[4].position.x, lights[4].position.y, lights[4].position.z);
	modelStack.Scale(3,0.5,8);
	RenderMesh(meshList[GEO_LIGHTBALL5], false);
	modelStack.PopMatrix();

	////Left back Lightball
	//modelStack.PushMatrix();
	//modelStack.Translate(lights[5].position.x, lights[5].position.y, lights[5].position.z);
	//modelStack.Scale(3,0.5,8);
	//RenderMesh(meshList[GEO_LIGHTBALL6], false);
	//modelStack.PopMatrix();

	//Left back Lightball
	modelStack.PushMatrix();
	modelStack.Translate(lights[6].position.x, lights[6].position.y, lights[6].position.z);
	modelStack.Scale(3,0.5,8);
	RenderMesh(meshList[GEO_LIGHTBALL7], false);
	modelStack.PopMatrix();

	//Left back Lightball
	modelStack.PushMatrix();
	modelStack.Translate(lights[7].position.x, lights[7].position.y, lights[7].position.z);
	modelStack.Scale(3,0.5,8);
	RenderMesh(meshList[GEO_LIGHTBALL8], false);
	modelStack.PopMatrix();
}
/******************************************************************************/
/*!
\brief
Renders the Item Information on the screen
*/
/******************************************************************************/
void StudioProject::RenderItemsInfo()
{
	if(GTP == false)
	{
		/*=====================================================
		CONTAINER 1
		========================================================*/
		for(int i = 0; i < boxContainer.size(); ++i) //Container 1
		{
			if(Container[i].getRender() == true)
			{
				if((camera.target.x <= boxContainer[i].max.x) &&
					(camera.target.y <= boxContainer[i].max.y) && 
					(camera.target.z <= boxContainer[i].max.z) &&
					(camera.target.x >= boxContainer[i].min.x) && 
					(camera.target.y >= boxContainer[i].min.y) && 
					(camera.target.z >= boxContainer[i].min.z))
				{
					std::ostringstream ssPrice;
					ssPrice <<  Container[i].getPrice();
					string price = ssPrice.str();

					RenderTextOnScreen(meshList[GEO_TEXT],"Name:" + Container[i].getName(), Color(1, 1, 1), 2, 13.55, 14);
					RenderTextOnScreen(meshList[GEO_TEXT],"Price:" + price, Color(1, 1, 1), 2, 13.55, 13);
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Take", Color(1, 1, 1), 2, 13.55, 12);
				}
			}
			if(Container[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer[i].max.x) &&
					(camera.target.y <= boxContainer[i].max.y) && 
					(camera.target.z <= boxContainer[i].max.z) &&
					(camera.target.x >= boxContainer[i].min.x) && 
					(camera.target.y >= boxContainer[i].min.y) && 
					(camera.target.z >= boxContainer[i].min.z))
				{
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'Q' to Return", Color(1, 1, 1), 2, 13.55, 14);
				}
			}
		}
		/*=====================================================
		CONTAINER 2
		========================================================*/
		for(int i = 0; i < boxContainer2.size(); ++i) //Container 2
		{
			if(Container2[i].getRender() == true)
			{
				if((camera.target.x <= boxContainer2[i].max.x) &&
					(camera.target.y <= boxContainer2[i].max.y) && 
					(camera.target.z <= boxContainer2[i].max.z) &&
					(camera.target.x >= boxContainer2[i].min.x) && 
					(camera.target.y >= boxContainer2[i].min.y) && 
					(camera.target.z >= boxContainer2[i].min.z))
				{
					std::ostringstream ssPrice;
					ssPrice <<  Container2[i].getPrice();
					string price = ssPrice.str();

					RenderTextOnScreen(meshList[GEO_TEXT],"Name:" + Container2[i].getName(), Color(1, 1, 1), 2, 13.55, 14);
					RenderTextOnScreen(meshList[GEO_TEXT],"Price:" + price, Color(1, 1, 1), 2, 13.55, 13);
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Take", Color(1, 1, 1), 2, 13.55, 12);
				}
			}
			if(Container2[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer2[i].max.x) &&
					(camera.target.y <= boxContainer2[i].max.y) && 
					(camera.target.z <= boxContainer2[i].max.z) &&
					(camera.target.x >= boxContainer2[i].min.x) && 
					(camera.target.y >= boxContainer2[i].min.y) && 
					(camera.target.z >= boxContainer2[i].min.z))
				{
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'Q' to Return", Color(1, 1, 1), 2, 13.55, 14);
				}
			}
		}

		/*=====================================================
		CONTAINER 3
		========================================================*/
		for(int i = 0; i < boxContainer3.size(); ++i) //Container 3
		{
			if(Container3[i].getRender() == true)
			{
				if((camera.target.x <= boxContainer3[i].max.x) &&
					(camera.target.y <= boxContainer3[i].max.y) && 
					(camera.target.z <= boxContainer3[i].max.z) &&
					(camera.target.x >= boxContainer3[i].min.x) && 
					(camera.target.y >= boxContainer3[i].min.y) && 
					(camera.target.z >= boxContainer3[i].min.z))
				{
					std::ostringstream ssPrice;
					ssPrice <<  Container3[i].getPrice();
					string price = ssPrice.str();

					RenderTextOnScreen(meshList[GEO_TEXT],"Name:" + Container3[i].getName(), Color(1, 1, 1), 2, 13.55, 14);
					RenderTextOnScreen(meshList[GEO_TEXT],"Price:" + price, Color(1, 1, 1), 2, 13.55, 13);
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Take", Color(1, 1, 1), 2, 13.55, 12);
				}
			}
			if(Container3[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer3[i].max.x) &&
					(camera.target.y <= boxContainer3[i].max.y) && 
					(camera.target.z <= boxContainer3[i].max.z) &&
					(camera.target.x >= boxContainer3[i].min.x) && 
					(camera.target.y >= boxContainer3[i].min.y) && 
					(camera.target.z >= boxContainer3[i].min.z))
				{
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'Q' to Return", Color(1, 1, 1), 2, 13.55, 14);
				}
			}
		}
		/*=====================================================
		CONTAINER 4
		========================================================*/
		for(int i = 0; i < boxContainer4.size(); ++i) //Container 4
		{
			if(Container4[i].getRender() == true)
			{
				if((camera.target.x <= boxContainer4[i].max.x) &&
					(camera.target.y <= boxContainer4[i].max.y) && 
					(camera.target.z <= boxContainer4[i].max.z) &&
					(camera.target.x >= boxContainer4[i].min.x) && 
					(camera.target.y >= boxContainer4[i].min.y) && 
					(camera.target.z >= boxContainer4[i].min.z))
				{
					std::ostringstream ssPrice;
					ssPrice <<  Container4[i].getPrice();
					string price = ssPrice.str();

					RenderTextOnScreen(meshList[GEO_TEXT],"Name:" + Container4[i].getName(), Color(1, 1, 1), 2, 13.55, 14);
					RenderTextOnScreen(meshList[GEO_TEXT],"Price:" + price, Color(1, 1, 1), 2, 13.55, 13);
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Take", Color(1, 1, 1), 2, 13.55, 12);
				}
			}
			if(Container4[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer4[i].max.x) &&
					(camera.target.y <= boxContainer4[i].max.y) && 
					(camera.target.z <= boxContainer4[i].max.z) &&
					(camera.target.x >= boxContainer4[i].min.x) && 
					(camera.target.y >= boxContainer4[i].min.y) && 
					(camera.target.z >= boxContainer4[i].min.z))
				{
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'Q' to Return", Color(1, 1, 1), 2, 13.55, 14);
				}
			}
		}
		/*=====================================================
		CONTAINER 5
		========================================================*/
		for(int i = 0; i < boxContainer5.size(); ++i) //Container 5
		{
			if(Container5[i].getRender() == true)
			{
				if((camera.target.x <= boxContainer5[i].max.x) &&
					(camera.target.y <= boxContainer5[i].max.y) && 
					(camera.target.z <= boxContainer5[i].max.z) &&
					(camera.target.x >= boxContainer5[i].min.x) && 
					(camera.target.y >= boxContainer5[i].min.y) && 
					(camera.target.z >= boxContainer5[i].min.z))
				{
					std::ostringstream ssPrice;
					ssPrice <<  Container5[i].getPrice();
					string price = ssPrice.str();

					RenderTextOnScreen(meshList[GEO_TEXT],"Name:" + Container5[i].getName(), Color(1, 1, 1), 2, 13.55, 14);
					RenderTextOnScreen(meshList[GEO_TEXT],"Price:" + price, Color(1, 1, 1), 2, 13.55, 13);
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Take", Color(1, 1, 1), 2, 13.55, 12);
				}
			}
			if(Container5[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer5[i].max.x) &&
					(camera.target.y <= boxContainer5[i].max.y) && 
					(camera.target.z <= boxContainer5[i].max.z) &&
					(camera.target.x >= boxContainer5[i].min.x) && 
					(camera.target.y >= boxContainer5[i].min.y) && 
					(camera.target.z >= boxContainer5[i].min.z))
				{
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'Q' to Return", Color(1, 1, 1), 2, 13.55, 14);
				}
			}
		}
		/*=====================================================
		CONTAINER 6
		========================================================*/
		for(int i = 0; i < boxContainer6.size(); ++i) //Container 6
		{
			if(Container6[i].getRender() == true)
			{
				if((camera.target.x <= boxContainer6[i].max.x) &&
					(camera.target.y <= boxContainer6[i].max.y) && 
					(camera.target.z <= boxContainer6[i].max.z) &&
					(camera.target.x >= boxContainer6[i].min.x) && 
					(camera.target.y >= boxContainer6[i].min.y) && 
					(camera.target.z >= boxContainer6[i].min.z))
				{
					std::ostringstream ssPrice;
					ssPrice <<  Container6[i].getPrice();
					string price = ssPrice.str();

					RenderTextOnScreen(meshList[GEO_TEXT],"Name:" + Container6[i].getName(), Color(1, 1, 1), 2, 13.55, 14);
					RenderTextOnScreen(meshList[GEO_TEXT],"Price:" + price, Color(1, 1, 1), 2, 13.55, 13);
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Take", Color(1, 1, 1), 2, 13.55, 12);
				}
			}
			if(Container6[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer6[i].max.x) &&
					(camera.target.y <= boxContainer6[i].max.y) && 
					(camera.target.z <= boxContainer6[i].max.z) &&
					(camera.target.x >= boxContainer6[i].min.x) && 
					(camera.target.y >= boxContainer6[i].min.y) && 
					(camera.target.z >= boxContainer6[i].min.z))
				{
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'Q' to Return", Color(1, 1, 1), 2, 13.55, 14);
				}
			}
		}

		/*=====================================================
		CONTAINER 7
		========================================================*/
		for(int i = 0; i < boxContainer7.size(); ++i) //Container 7
		{
			if(Container7[i].getRender() == true)
			{
				if((camera.target.x <= boxContainer7[i].max.x) &&
					(camera.target.y <= boxContainer7[i].max.y) && 
					(camera.target.z <= boxContainer7[i].max.z) &&
					(camera.target.x >= boxContainer7[i].min.x) && 
					(camera.target.y >= boxContainer7[i].min.y) && 
					(camera.target.z >= boxContainer7[i].min.z))
				{
					std::ostringstream ssPrice;
					ssPrice <<  Container7[i].getPrice();
					string price = ssPrice.str();

					RenderTextOnScreen(meshList[GEO_TEXT],"Name:" + Container7[i].getName(), Color(1, 1, 1), 2, 13.55, 14);
					RenderTextOnScreen(meshList[GEO_TEXT],"Price:" + price, Color(1, 1, 1), 2, 13.55, 13);
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Take", Color(1, 1, 1), 2, 13.55, 12);
				}
			}
			if(Container7[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer7[i].max.x) &&
					(camera.target.y <= boxContainer7[i].max.y) && 
					(camera.target.z <= boxContainer7[i].max.z) &&
					(camera.target.x >= boxContainer7[i].min.x) && 
					(camera.target.y >= boxContainer7[i].min.y) && 
					(camera.target.z >= boxContainer7[i].min.z))
				{
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'Q' to Return", Color(1, 1, 1), 2, 13.55, 14);
				}
			}
		}
		/*=====================================================
		CONTAINER 8
		========================================================*/
		for(int i = 0; i < boxContainer8.size(); ++i) //Container 8
		{
			if(Container8[i].getRender() == true)
			{
				if((camera.target.x <= boxContainer8[i].max.x) &&
					(camera.target.y <= boxContainer8[i].max.y) && 
					(camera.target.z <= boxContainer8[i].max.z) &&
					(camera.target.x >= boxContainer8[i].min.x) && 
					(camera.target.y >= boxContainer8[i].min.y) && 
					(camera.target.z >= boxContainer8[i].min.z))
				{
					std::ostringstream ssPrice;
					ssPrice <<  Container8[i].getPrice();
					string price = ssPrice.str();

					RenderTextOnScreen(meshList[GEO_TEXT],"Name:" + Container8[i].getName(), Color(1, 1, 1), 2, 13.55, 14);
					RenderTextOnScreen(meshList[GEO_TEXT],"Price:" + price, Color(1, 1, 1), 2, 13.55, 13);
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Take", Color(1, 1, 1), 2, 13.55, 12);
				}
			}
			if(Container8[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer8[i].max.x) &&
					(camera.target.y <= boxContainer8[i].max.y) && 
					(camera.target.z <= boxContainer8[i].max.z) &&
					(camera.target.x >= boxContainer8[i].min.x) && 
					(camera.target.y >= boxContainer8[i].min.y) && 
					(camera.target.z >= boxContainer8[i].min.z))
				{
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'Q' to Return", Color(1, 1, 1), 2, 13.55, 14);
				}
			}
		}
		/*=====================================================
		CONTAINER 9
		========================================================*/
		for(int i = 0; i < boxContainer9.size(); ++i) //Container 9
		{
			if(Container9[i].getRender() == true)
			{
				if((camera.target.x <= boxContainer9[i].max.x) &&
					(camera.target.y <= boxContainer9[i].max.y) && 
					(camera.target.z <= boxContainer9[i].max.z) &&
					(camera.target.x >= boxContainer9[i].min.x) && 
					(camera.target.y >= boxContainer9[i].min.y) && 
					(camera.target.z >= boxContainer9[i].min.z))
				{
					std::ostringstream ssPrice;
					ssPrice <<  Container9[i].getPrice();
					string price = ssPrice.str();

					RenderTextOnScreen(meshList[GEO_TEXT],"Name:" + Container9[i].getName(), Color(1, 1, 1), 2, 13.55, 14);
					RenderTextOnScreen(meshList[GEO_TEXT],"Price:" + price, Color(1, 1, 1), 2, 13.55, 13);
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Take", Color(1, 1, 1), 2, 13.55, 12);
				}
			}
			if(Container9[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer9[i].max.x) &&
					(camera.target.y <= boxContainer9[i].max.y) && 
					(camera.target.z <= boxContainer9[i].max.z) &&
					(camera.target.x >= boxContainer9[i].min.x) && 
					(camera.target.y >= boxContainer9[i].min.y) && 
					(camera.target.z >= boxContainer9[i].min.z))
				{
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'Q' to Return", Color(1, 1, 1), 2, 13.55, 14);
				}
			}
		}

		/*=====================================================
		CONTAINER 10
		========================================================*/
		for(int i = 0; i < boxContainer10.size(); ++i) //Container 10
		{
			if(Container10[i].getRender() == true)
			{
				if((camera.target.x <= boxContainer10[i].max.x) &&
					(camera.target.y <= boxContainer10[i].max.y) && 
					(camera.target.z <= boxContainer10[i].max.z) &&
					(camera.target.x >= boxContainer10[i].min.x) && 
					(camera.target.y >= boxContainer10[i].min.y) && 
					(camera.target.z >= boxContainer10[i].min.z))
				{
					std::ostringstream ssPrice;
					ssPrice <<  Container10[i].getPrice();
					string price = ssPrice.str();

					RenderTextOnScreen(meshList[GEO_TEXT],"Name:" + Container10[i].getName(), Color(1, 1, 1), 2, 13.55, 14);
					RenderTextOnScreen(meshList[GEO_TEXT],"Price:" + price, Color(1, 1, 1), 2, 13.55, 13);
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Take", Color(1, 1, 1), 2, 13.55, 12);
				}
			}
			if(Container10[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer10[i].max.x) &&
					(camera.target.y <= boxContainer10[i].max.y) && 
					(camera.target.z <= boxContainer10[i].max.z) &&
					(camera.target.x >= boxContainer10[i].min.x) && 
					(camera.target.y >= boxContainer10[i].min.y) && 
					(camera.target.z >= boxContainer10[i].min.z))
				{
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'Q' to Return", Color(1, 1, 1), 2, 13.55, 14);
				}
			}
		}

		/*=====================================================
		CONTAINER 11
		========================================================*/
		for(int i = 0; i < boxContainer11.size(); ++i) //Container 11
		{
			if(Container11[i].getRender() == true)
			{
				if((camera.target.x <= boxContainer11[i].max.x) &&
					(camera.target.y <= boxContainer11[i].max.y) && 
					(camera.target.z <= boxContainer11[i].max.z) &&
					(camera.target.x >= boxContainer11[i].min.x) && 
					(camera.target.y >= boxContainer11[i].min.y) && 
					(camera.target.z >= boxContainer11[i].min.z))
				{
					std::ostringstream ssPrice;
					ssPrice <<  Container11[i].getPrice();
					string price = ssPrice.str();

					RenderTextOnScreen(meshList[GEO_TEXT],"Name:" + Container11[i].getName(), Color(1, 1, 1), 2, 13.55, 14);
					RenderTextOnScreen(meshList[GEO_TEXT],"Price:" + price, Color(1, 1, 1), 2, 13.55, 13);
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Take", Color(1, 1, 1), 2, 13.55, 12);
				}
			}
			if(Container11[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer11[i].max.x) &&
					(camera.target.y <= boxContainer11[i].max.y) && 
					(camera.target.z <= boxContainer11[i].max.z) &&
					(camera.target.x >= boxContainer11[i].min.x) && 
					(camera.target.y >= boxContainer11[i].min.y) && 
					(camera.target.z >= boxContainer11[i].min.z))
				{
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'Q' to Return", Color(1, 1, 1), 2, 13.55, 14);
				}
			}
		}
		/*=====================================================
		CONTAINER 12
		========================================================*/
		for(int i = 0; i < boxContainer12.size(); ++i) //Container 12
		{
			if(Container12[i].getRender() == true)
			{
				if((camera.target.x <= boxContainer12[i].max.x) &&
					(camera.target.y <= boxContainer12[i].max.y) && 
					(camera.target.z <= boxContainer12[i].max.z) &&
					(camera.target.x >= boxContainer12[i].min.x) && 
					(camera.target.y >= boxContainer12[i].min.y) && 
					(camera.target.z >= boxContainer12[i].min.z))
				{
					std::ostringstream ssPrice;
					ssPrice <<  Container12[i].getPrice();
					string price = ssPrice.str();

					RenderTextOnScreen(meshList[GEO_TEXT],"Name:" + Container12[i].getName(), Color(1, 1, 1), 2, 13.55, 14);
					RenderTextOnScreen(meshList[GEO_TEXT],"Price:" + price, Color(1, 1, 1), 2, 13.55, 13);
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Take", Color(1, 1, 1), 2, 13.55, 12);
				}
			}
			if(Container12[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer12[i].max.x) &&
					(camera.target.y <= boxContainer12[i].max.y) && 
					(camera.target.z <= boxContainer12[i].max.z) &&
					(camera.target.x >= boxContainer12[i].min.x) && 
					(camera.target.y >= boxContainer12[i].min.y) && 
					(camera.target.z >= boxContainer12[i].min.z))
				{
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'Q' to Return", Color(1, 1, 1), 2, 13.55, 14);
				}
			}
		}
		/*=====================================================
		CONTAINER 13
		========================================================*/
		for(int i = 0; i < boxContainer13.size(); ++i) //Container 12
		{
			if(Container13[i].getRender() == true)
			{
				if((camera.target.x <= boxContainer13[i].max.x) &&
					(camera.target.y <= boxContainer13[i].max.y) && 
					(camera.target.z <= boxContainer13[i].max.z) &&
					(camera.target.x >= boxContainer13[i].min.x) && 
					(camera.target.y >= boxContainer13[i].min.y) && 
					(camera.target.z >= boxContainer13[i].min.z))
				{
					std::ostringstream ssPrice;
					ssPrice <<  Container13[i].getPrice();
					string price = ssPrice.str();

					RenderTextOnScreen(meshList[GEO_TEXT],"Name:" + Container13[i].getName(), Color(1, 1, 1), 2, 13.55, 14);
					RenderTextOnScreen(meshList[GEO_TEXT],"Price:" + price, Color(1, 1, 1), 2, 13.55, 13);
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Take", Color(1, 1, 1), 2, 13.55, 12);
				}
			}
			if(Container13[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer13[i].max.x) &&
					(camera.target.y <= boxContainer13[i].max.y) && 
					(camera.target.z <= boxContainer13[i].max.z) &&
					(camera.target.x >= boxContainer13[i].min.x) && 
					(camera.target.y >= boxContainer13[i].min.y) && 
					(camera.target.z >= boxContainer13[i].min.z))
				{
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'Q' to Return", Color(1, 1, 1), 2, 13.55, 14);
				}
			}
		}
	}
	else if(GTP == true)
	{
		/*=====================================================
		CONTAINER 1
		========================================================*/
		for(int i = 0; i < boxContainer.size(); ++i) //Container 1
		{
			if(Container[i].getRender() == true)
			{
				if((camera.target.x <= boxContainer[i].max.x) &&
					(camera.target.y <= boxContainer[i].max.y) && 
					(camera.target.z <= boxContainer[i].max.z) &&
					(camera.target.x >= boxContainer[i].min.x) && 
					(camera.target.y >= boxContainer[i].min.y) && 
					(camera.target.z >= boxContainer[i].min.z))
				{
					std::ostringstream ssPrice;
					ssPrice <<  Container[i].getPrice();
					string price = ssPrice.str();

					RenderTextOnScreen(meshList[GEO_TEXT],"Name:" + Container[i].getName(), Color(1, 1, 1), 2, 13.55, 14);
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Take", Color(1, 1, 1), 2, 13.55, 12);
				}
			}
			if(Container[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer[i].max.x) &&
					(camera.target.y <= boxContainer[i].max.y) && 
					(camera.target.z <= boxContainer[i].max.z) &&
					(camera.target.x >= boxContainer[i].min.x) && 
					(camera.target.y >= boxContainer[i].min.y) && 
					(camera.target.z >= boxContainer[i].min.z))
				{
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'Q' to Return", Color(1, 1, 1), 2, 13.55, 14);
				}
			}
		}
		/*=====================================================
		CONTAINER 2
		========================================================*/
		for(int i = 0; i < boxContainer2.size(); ++i) //Container 2
		{
			if(Container2[i].getRender() == true)
			{
				if((camera.target.x <= boxContainer2[i].max.x) &&
					(camera.target.y <= boxContainer2[i].max.y) && 
					(camera.target.z <= boxContainer2[i].max.z) &&
					(camera.target.x >= boxContainer2[i].min.x) && 
					(camera.target.y >= boxContainer2[i].min.y) && 
					(camera.target.z >= boxContainer2[i].min.z))
				{
					std::ostringstream ssPrice;
					ssPrice <<  Container2[i].getPrice();
					string price = ssPrice.str();

					RenderTextOnScreen(meshList[GEO_TEXT],"Name:" + Container2[i].getName(), Color(1, 1, 1), 2, 13.55, 14);
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Take", Color(1, 1, 1), 2, 13.55, 12);
				}
			}
			if(Container2[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer2[i].max.x) &&
					(camera.target.y <= boxContainer2[i].max.y) && 
					(camera.target.z <= boxContainer2[i].max.z) &&
					(camera.target.x >= boxContainer2[i].min.x) && 
					(camera.target.y >= boxContainer2[i].min.y) && 
					(camera.target.z >= boxContainer2[i].min.z))
				{
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'Q' to Return", Color(1, 1, 1), 2, 13.55, 14);
				}
			}
		}

		/*=====================================================
		CONTAINER 3
		========================================================*/
		for(int i = 0; i < boxContainer3.size(); ++i) //Container 3
		{
			if(Container3[i].getRender() == true)
			{
				if((camera.target.x <= boxContainer3[i].max.x) &&
					(camera.target.y <= boxContainer3[i].max.y) && 
					(camera.target.z <= boxContainer3[i].max.z) &&
					(camera.target.x >= boxContainer3[i].min.x) && 
					(camera.target.y >= boxContainer3[i].min.y) && 
					(camera.target.z >= boxContainer3[i].min.z))
				{
					std::ostringstream ssPrice;
					ssPrice <<  Container3[i].getPrice();
					string price = ssPrice.str();

					RenderTextOnScreen(meshList[GEO_TEXT],"Name:" + Container3[i].getName(), Color(1, 1, 1), 2, 13.55, 14);
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Take", Color(1, 1, 1), 2, 13.55, 12);
				}
			}
			if(Container3[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer3[i].max.x) &&
					(camera.target.y <= boxContainer3[i].max.y) && 
					(camera.target.z <= boxContainer3[i].max.z) &&
					(camera.target.x >= boxContainer3[i].min.x) && 
					(camera.target.y >= boxContainer3[i].min.y) && 
					(camera.target.z >= boxContainer3[i].min.z))
				{
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'Q' to Return", Color(1, 1, 1), 2, 13.55, 14);
				}
			}
		}
		/*=====================================================
		CONTAINER 4
		========================================================*/
		for(int i = 0; i < boxContainer4.size(); ++i) //Container 4
		{
			if(Container4[i].getRender() == true)
			{
				if((camera.target.x <= boxContainer4[i].max.x) &&
					(camera.target.y <= boxContainer4[i].max.y) && 
					(camera.target.z <= boxContainer4[i].max.z) &&
					(camera.target.x >= boxContainer4[i].min.x) && 
					(camera.target.y >= boxContainer4[i].min.y) && 
					(camera.target.z >= boxContainer4[i].min.z))
				{
					std::ostringstream ssPrice;
					ssPrice <<  Container4[i].getPrice();
					string price = ssPrice.str();

					RenderTextOnScreen(meshList[GEO_TEXT],"Name:" + Container4[i].getName(), Color(1, 1, 1), 2, 13.55, 14);
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Take", Color(1, 1, 1), 2, 13.55, 12);
				}
			}
			if(Container4[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer4[i].max.x) &&
					(camera.target.y <= boxContainer4[i].max.y) && 
					(camera.target.z <= boxContainer4[i].max.z) &&
					(camera.target.x >= boxContainer4[i].min.x) && 
					(camera.target.y >= boxContainer4[i].min.y) && 
					(camera.target.z >= boxContainer4[i].min.z))
				{
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'Q' to Return", Color(1, 1, 1), 2, 13.55, 14);
				}
			}
		}
		/*=====================================================
		CONTAINER 5
		========================================================*/
		for(int i = 0; i < boxContainer5.size(); ++i) //Container 5
		{
			if(Container5[i].getRender() == true)
			{
				if((camera.target.x <= boxContainer5[i].max.x) &&
					(camera.target.y <= boxContainer5[i].max.y) && 
					(camera.target.z <= boxContainer5[i].max.z) &&
					(camera.target.x >= boxContainer5[i].min.x) && 
					(camera.target.y >= boxContainer5[i].min.y) && 
					(camera.target.z >= boxContainer5[i].min.z))
				{
					std::ostringstream ssPrice;
					ssPrice <<  Container5[i].getPrice();
					string price = ssPrice.str();

					RenderTextOnScreen(meshList[GEO_TEXT],"Name:" + Container5[i].getName(), Color(1, 1, 1), 2, 13.55, 14);
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Take", Color(1, 1, 1), 2, 13.55, 12);
				}
			}
			if(Container5[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer5[i].max.x) &&
					(camera.target.y <= boxContainer5[i].max.y) && 
					(camera.target.z <= boxContainer5[i].max.z) &&
					(camera.target.x >= boxContainer5[i].min.x) && 
					(camera.target.y >= boxContainer5[i].min.y) && 
					(camera.target.z >= boxContainer5[i].min.z))
				{
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'Q' to Return", Color(1, 1, 1), 2, 13.55, 14);
				}
			}
		}
		/*=====================================================
		CONTAINER 6
		========================================================*/
		for(int i = 0; i < boxContainer6.size(); ++i) //Container 6
		{
			if(Container6[i].getRender() == true)
			{
				if((camera.target.x <= boxContainer6[i].max.x) &&
					(camera.target.y <= boxContainer6[i].max.y) && 
					(camera.target.z <= boxContainer6[i].max.z) &&
					(camera.target.x >= boxContainer6[i].min.x) && 
					(camera.target.y >= boxContainer6[i].min.y) && 
					(camera.target.z >= boxContainer6[i].min.z))
				{
					std::ostringstream ssPrice;
					ssPrice <<  Container6[i].getPrice();
					string price = ssPrice.str();

					RenderTextOnScreen(meshList[GEO_TEXT],"Name:" + Container6[i].getName(), Color(1, 1, 1), 2, 13.55, 14);
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Take", Color(1, 1, 1), 2, 13.55, 12);
				}
			}
			if(Container6[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer6[i].max.x) &&
					(camera.target.y <= boxContainer6[i].max.y) && 
					(camera.target.z <= boxContainer6[i].max.z) &&
					(camera.target.x >= boxContainer6[i].min.x) && 
					(camera.target.y >= boxContainer6[i].min.y) && 
					(camera.target.z >= boxContainer6[i].min.z))
				{
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'Q' to Return", Color(1, 1, 1), 2, 13.55, 14);
				}
			}
		}

		/*=====================================================
		CONTAINER 7
		========================================================*/
		for(int i = 0; i < boxContainer7.size(); ++i) //Container 7
		{
			if(Container7[i].getRender() == true)
			{
				if((camera.target.x <= boxContainer7[i].max.x) &&
					(camera.target.y <= boxContainer7[i].max.y) && 
					(camera.target.z <= boxContainer7[i].max.z) &&
					(camera.target.x >= boxContainer7[i].min.x) && 
					(camera.target.y >= boxContainer7[i].min.y) && 
					(camera.target.z >= boxContainer7[i].min.z))
				{
					std::ostringstream ssPrice;
					ssPrice <<  Container7[i].getPrice();
					string price = ssPrice.str();

					RenderTextOnScreen(meshList[GEO_TEXT],"Name:" + Container7[i].getName(), Color(1, 1, 1), 2, 13.55, 14);
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Take", Color(1, 1, 1), 2, 13.55, 12);
				}
			}
			if(Container7[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer7[i].max.x) &&
					(camera.target.y <= boxContainer7[i].max.y) && 
					(camera.target.z <= boxContainer7[i].max.z) &&
					(camera.target.x >= boxContainer7[i].min.x) && 
					(camera.target.y >= boxContainer7[i].min.y) && 
					(camera.target.z >= boxContainer7[i].min.z))
				{
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'Q' to Return", Color(1, 1, 1), 2, 13.55, 14);
				}
			}
		}
		/*=====================================================
		CONTAINER 8
		========================================================*/
		for(int i = 0; i < boxContainer8.size(); ++i) //Container 8
		{
			if(Container8[i].getRender() == true)
			{
				if((camera.target.x <= boxContainer8[i].max.x) &&
					(camera.target.y <= boxContainer8[i].max.y) && 
					(camera.target.z <= boxContainer8[i].max.z) &&
					(camera.target.x >= boxContainer8[i].min.x) && 
					(camera.target.y >= boxContainer8[i].min.y) && 
					(camera.target.z >= boxContainer8[i].min.z))
				{
					std::ostringstream ssPrice;
					ssPrice <<  Container8[i].getPrice();
					string price = ssPrice.str();

					RenderTextOnScreen(meshList[GEO_TEXT],"Name:" + Container8[i].getName(), Color(1, 1, 1), 2, 13.55, 14);
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Take", Color(1, 1, 1), 2, 13.55, 12);
				}
			}
			if(Container8[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer8[i].max.x) &&
					(camera.target.y <= boxContainer8[i].max.y) && 
					(camera.target.z <= boxContainer8[i].max.z) &&
					(camera.target.x >= boxContainer8[i].min.x) && 
					(camera.target.y >= boxContainer8[i].min.y) && 
					(camera.target.z >= boxContainer8[i].min.z))
				{
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'Q' to Return", Color(1, 1, 1), 2, 13.55, 14);
				}
			}
		}
		/*=====================================================
		CONTAINER 9
		========================================================*/
		for(int i = 0; i < boxContainer9.size(); ++i) //Container 9
		{
			if(Container9[i].getRender() == true)
			{
				if((camera.target.x <= boxContainer9[i].max.x) &&
					(camera.target.y <= boxContainer9[i].max.y) && 
					(camera.target.z <= boxContainer9[i].max.z) &&
					(camera.target.x >= boxContainer9[i].min.x) && 
					(camera.target.y >= boxContainer9[i].min.y) && 
					(camera.target.z >= boxContainer9[i].min.z))
				{
					std::ostringstream ssPrice;
					ssPrice <<  Container9[i].getPrice();
					string price = ssPrice.str();

					RenderTextOnScreen(meshList[GEO_TEXT],"Name:" + Container9[i].getName(), Color(1, 1, 1), 2, 13.55, 14);
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Take", Color(1, 1, 1), 2, 13.55, 12);
				}
			}
			if(Container9[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer9[i].max.x) &&
					(camera.target.y <= boxContainer9[i].max.y) && 
					(camera.target.z <= boxContainer9[i].max.z) &&
					(camera.target.x >= boxContainer9[i].min.x) && 
					(camera.target.y >= boxContainer9[i].min.y) && 
					(camera.target.z >= boxContainer9[i].min.z))
				{
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'Q' to Return", Color(1, 1, 1), 2, 13.55, 14);
				}
			}
		}

		/*=====================================================
		CONTAINER 10
		========================================================*/
		for(int i = 0; i < boxContainer10.size(); ++i) //Container 10
		{
			if(Container10[i].getRender() == true)
			{
				if((camera.target.x <= boxContainer10[i].max.x) &&
					(camera.target.y <= boxContainer10[i].max.y) && 
					(camera.target.z <= boxContainer10[i].max.z) &&
					(camera.target.x >= boxContainer10[i].min.x) && 
					(camera.target.y >= boxContainer10[i].min.y) && 
					(camera.target.z >= boxContainer10[i].min.z))
				{
					std::ostringstream ssPrice;
					ssPrice <<  Container10[i].getPrice();
					string price = ssPrice.str();

					RenderTextOnScreen(meshList[GEO_TEXT],"Name:" + Container10[i].getName(), Color(1, 1, 1), 2, 13.55, 14);
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Take", Color(1, 1, 1), 2, 13.55, 12);
				}
			}
			if(Container10[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer10[i].max.x) &&
					(camera.target.y <= boxContainer10[i].max.y) && 
					(camera.target.z <= boxContainer10[i].max.z) &&
					(camera.target.x >= boxContainer10[i].min.x) && 
					(camera.target.y >= boxContainer10[i].min.y) && 
					(camera.target.z >= boxContainer10[i].min.z))
				{
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'Q' to Return", Color(1, 1, 1), 2, 13.55, 14);
				}
			}
		}

		/*=====================================================
		CONTAINER 11
		========================================================*/
		for(int i = 0; i < boxContainer11.size(); ++i) //Container 11
		{
			if(Container11[i].getRender() == true)
			{
				if((camera.target.x <= boxContainer11[i].max.x) &&
					(camera.target.y <= boxContainer11[i].max.y) && 
					(camera.target.z <= boxContainer11[i].max.z) &&
					(camera.target.x >= boxContainer11[i].min.x) && 
					(camera.target.y >= boxContainer11[i].min.y) && 
					(camera.target.z >= boxContainer11[i].min.z))
				{
					std::ostringstream ssPrice;
					ssPrice <<  Container11[i].getPrice();
					string price = ssPrice.str();

					RenderTextOnScreen(meshList[GEO_TEXT],"Name:" + Container11[i].getName(), Color(1, 1, 1), 2, 13.55, 14);
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Take", Color(1, 1, 1), 2, 13.55, 12);
				}
			}
			if(Container11[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer11[i].max.x) &&
					(camera.target.y <= boxContainer11[i].max.y) && 
					(camera.target.z <= boxContainer11[i].max.z) &&
					(camera.target.x >= boxContainer11[i].min.x) && 
					(camera.target.y >= boxContainer11[i].min.y) && 
					(camera.target.z >= boxContainer11[i].min.z))
				{
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'Q' to Return", Color(1, 1, 1), 2, 13.55, 14);
				}
			}
		}
		/*=====================================================
		CONTAINER 12
		========================================================*/
		for(int i = 0; i < boxContainer12.size(); ++i) //Container 12
		{
			if(Container12[i].getRender() == true)
			{
				if((camera.target.x <= boxContainer12[i].max.x) &&
					(camera.target.y <= boxContainer12[i].max.y) && 
					(camera.target.z <= boxContainer12[i].max.z) &&
					(camera.target.x >= boxContainer12[i].min.x) && 
					(camera.target.y >= boxContainer12[i].min.y) && 
					(camera.target.z >= boxContainer12[i].min.z))
				{
					std::ostringstream ssPrice;
					ssPrice <<  Container12[i].getPrice();
					string price = ssPrice.str();

					RenderTextOnScreen(meshList[GEO_TEXT],"Name:" + Container12[i].getName(), Color(1, 1, 1), 2, 13.55, 14);
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Take", Color(1, 1, 1), 2, 13.55, 12);
				}
			}
			if(Container12[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer12[i].max.x) &&
					(camera.target.y <= boxContainer12[i].max.y) && 
					(camera.target.z <= boxContainer12[i].max.z) &&
					(camera.target.x >= boxContainer12[i].min.x) && 
					(camera.target.y >= boxContainer12[i].min.y) && 
					(camera.target.z >= boxContainer12[i].min.z))
				{
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'Q' to Return", Color(1, 1, 1), 2, 13.55, 14);
				}
			}
		}
		/*=====================================================
		CONTAINER 13
		========================================================*/
		for(int i = 0; i < boxContainer13.size(); ++i) //Container 12
		{
			if(Container13[i].getRender() == true)
			{
				if((camera.target.x <= boxContainer13[i].max.x) &&
					(camera.target.y <= boxContainer13[i].max.y) && 
					(camera.target.z <= boxContainer13[i].max.z) &&
					(camera.target.x >= boxContainer13[i].min.x) && 
					(camera.target.y >= boxContainer13[i].min.y) && 
					(camera.target.z >= boxContainer13[i].min.z))
				{
					std::ostringstream ssPrice;
					ssPrice <<  Container13[i].getPrice();
					string price = ssPrice.str();

					RenderTextOnScreen(meshList[GEO_TEXT],"Name:" + Container13[i].getName(), Color(1, 1, 1), 2, 13.55, 14);
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Take", Color(1, 1, 1), 2, 13.55, 12);
				}
			}
			if(Container13[i].getRender() == false)
			{
				if((camera.target.x <= boxContainer13[i].max.x) &&
					(camera.target.y <= boxContainer13[i].max.y) && 
					(camera.target.z <= boxContainer13[i].max.z) &&
					(camera.target.x >= boxContainer13[i].min.x) && 
					(camera.target.y >= boxContainer13[i].min.y) && 
					(camera.target.z >= boxContainer13[i].min.z))
				{
					RenderTextOnScreen(meshList[GEO_TEXT],"Press 'Q' to Return", Color(1, 1, 1), 2, 13.55, 14);
				}
			}
		}
	}
	/*==============================================================
	CHECKING OUT
	=================================================================*/
	for(int i = 0;i < CashierBox.size();i++)
	{
		if((camera.position.x <= CashierBox[i].max.x) && 
			(camera.position.y <= CashierBox[i].max.y) && 
			(camera.position.z <= CashierBox[i].max.z) &&
			(camera.position.x >= CashierBox[i].min.x) && 
			(camera.position.y >= CashierBox[i].min.y) && 
			(camera.position.z >= CashierBox[i].min.z))
		{
			RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Check Out", Color(1, 1, 1), 2, 13.55, 14);
		}
	}
	/*===========================================================================
	DUST BIN
	==============================================================================*/
	if(camera.target.x <= -60 && camera.target.y <= 8 && camera.target.z <= -19
		&& camera.target.x >= -63.5 && camera.target.y >= 0 && camera.target.z >= -23)
	{
		RenderTextOnScreen(meshList[GEO_TEXT],"Press 'E' to Clear Inventory", Color(1, 1, 1), 2, 10, 14);
	}
}
/******************************************************************************/
/*!
\brief
Renders the Items being Checked Out in the scene
*/
/******************************************************************************/
void StudioProject::RenderCheckOutItems()
{
	//Used for rendering Objs on cashier table//
	//Extreme left cashier
	if(camera.position.z >= -13 && camera.position.z <= -11.6 && camera.position.y >=4 && camera.position.y <= 10 && camera.position.x >= -26.f && camera.position.x <= -19.2) //Extreme left cashier
	{
		if(Peas == true ) // Peas and Cans
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,-15);
			RenderMesh(meshList[GEO_PEA_N_CARROTS], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5 && peaCount != 0)
			{
				moveItem = 0;
				peaCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_PEA_N_CARROTS)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			else if (peaCount == 0 )
			{
				Peas = false;
			}

		}
		if(Sardine == true && Peas == false) //GEO_SARDINE_CAN
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,-15);
			RenderMesh(meshList[GEO_SARDINE_CAN], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5 && SardineCount != 0)
			{
				moveItem = 0;
				SardineCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_SARDINE_CAN)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (SardineCount == 0)
			{
				Sardine = false;
			}

		}
		if(Beans == true && Sardine == false && Peas == false) //GEO_BAKED_BEANS_CAN,
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,-15);
			RenderMesh(meshList[GEO_BAKED_BEANS_CAN], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5 && BeansCount != 0)
			{
				moveItem = 0;
				BeansCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_BAKED_BEANS_CAN)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (BeansCount == 0)
			{
				Beans = false;
			}

		}
		if(Coke == true && Beans == false && Sardine == false && Peas == false) //GEO_COKE_CAN,
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,-16);
			RenderMesh(meshList[GEO_COKE_CAN], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5 && CokeCount != 0)
			{
				moveItem = 0;
				CokeCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_COKE_CAN)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (CokeCount == 0)
			{
				Coke = false;
			}

		}

		if(CokeZero == true && Coke == false && Beans == false && Sardine == false && Peas == false) //Coke zero (Can2)
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,-15);
			RenderMesh(meshList[GEO_DRINKCAN2], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5  && CokeZeroCount != 0)
			{
				moveItem = 0;
				CokeZeroCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_DRINKCAN2)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (CokeZeroCount == 0)
			{
				CokeZero = false;
			}
		}

		if(Pepsi == true && CokeZero == false && Coke == false && Beans == false && Sardine == false && Peas == false) //Coke zero (Can2)
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,-15);
			RenderMesh(meshList[GEO_PEPSI_CAN], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5  && PepsiCount != 0)
			{
				moveItem = 0;
				PepsiCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_PEPSI_CAN)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (PepsiCount == 0)
			{
				Pepsi = false;
			}
		}



		if(Milo == true && Pepsi == false && CokeZero == false && Coke == false && Beans == false && Sardine == false && Peas == false) //Milo
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,-15);
			RenderMesh(meshList[GEO_MILOCAN], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5  && MiloCount != 0)
			{
				moveItem = 0;
				MiloCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_MILOCAN)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (MiloCount == 0)
			{
				Milo = false;
			}

		}
		if(Cereal1 == true && Milo == false && Pepsi == false && CokeZero == false && Coke == false && Beans == false && Sardine == false && Peas == false) //Cereal 1
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,-15);
			RenderMesh(meshList[GEO_CEREALBOX1], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5  && Cereal1Count != 0)
			{
				moveItem = 0;
				Cereal1Count --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_CEREALBOX1)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (Cereal1Count == 0)
			{
				Cereal1 = false;
			}

		}

		if(Cereal2 == true && Cereal1 == false && Milo == false && Pepsi == false && CokeZero == false && Coke == false && Beans == false && Sardine == false && Peas == false) //Cereal2
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,-15);
			RenderMesh(meshList[GEO_CEREALBOX2], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5  && Cereal2Count != 0)
			{
				moveItem = 0;
				Cereal2Count --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_CEREALBOX2)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (Cereal2Count == 0)
			{
				Cereal2 = false;
			}

		}

		if(Pizza == true && Cereal2 == false && Cereal1 == false && Milo == false && Pepsi == false && CokeZero == false && Coke == false && Beans == false && Sardine == false && Peas == false) //Cereal2
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,-15);
			RenderMesh(meshList[GEO_PIZZABOX], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5  && PizzaCount != 0)
			{
				moveItem = 0;
				PizzaCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_PIZZABOX)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (PizzaCount == 0)
			{
				Pizza = false;
			}

		}
		if(Lays == true && Pizza == false && Cereal2 == false && Cereal1 == false && Milo == false && Pepsi == false && CokeZero == false && Coke == false && Beans == false && Sardine == false && Peas == false) //Lays
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,-15);
			RenderMesh(meshList[GEO_POTATOCHIPS], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5  && LaysCount != 0)
			{
				moveItem = 0;
				LaysCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_POTATOCHIPS)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (LaysCount == 0)
			{
				Lays = false;
			}
		}

	}
	// =============Middle cashier===================//
	if(camera.position.z >= 4.8 && camera.position.z <= 7.1 && camera.position.y >=4 && camera.position.y <= 10 && camera.position.x >= -26 && camera.position.x <= -19.2) 
	{
		if(Peas == true ) // Peas and Cans
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,2.8);
			RenderMesh(meshList[GEO_PEA_N_CARROTS], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5 && peaCount != 0)
			{
				moveItem = 0;
				peaCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_PEA_N_CARROTS)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			else if (peaCount == 0 )
			{
				Peas = false;
			}

		}
		if(Sardine == true && Peas == false) //GEO_SARDINE_CAN
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,2.8);
			RenderMesh(meshList[GEO_SARDINE_CAN], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5 && SardineCount != 0)
			{
				moveItem = 0;
				SardineCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_SARDINE_CAN)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (SardineCount == 0)
			{
				Sardine = false;
			}

		}
		if(Beans == true && Sardine == false && Peas == false) //GEO_BAKED_BEANS_CAN,
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,2.8);
			RenderMesh(meshList[GEO_BAKED_BEANS_CAN], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5 && BeansCount != 0)
			{
				moveItem = 0;
				BeansCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_BAKED_BEANS_CAN)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (BeansCount == 0)
			{
				Beans = false;
			}

		}
		if(Coke == true && Beans == false && Sardine == false && Peas == false) //GEO_COKE_CAN,
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,2.8);
			RenderMesh(meshList[GEO_COKE_CAN], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5 && CokeCount != 0)
			{
				moveItem = 0;
				CokeCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_COKE_CAN)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (CokeCount == 0)
			{
				Coke = false;
			}

		}

		if(CokeZero == true && Coke == false && Beans == false && Sardine == false && Peas == false) //Coke zero (Can2)
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,2.8);
			RenderMesh(meshList[GEO_DRINKCAN2], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5  && CokeZeroCount != 0)
			{
				moveItem = 0;
				CokeZeroCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_DRINKCAN2)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (CokeZeroCount == 0)
			{
				CokeZero = false;
			}
		}

		if(Pepsi == true && CokeZero == false && Coke == false && Beans == false && Sardine == false && Peas == false) //Coke zero (Can2)
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,2.8);
			RenderMesh(meshList[GEO_PEPSI_CAN], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5  && PepsiCount != 0)
			{
				moveItem = 0;
				PepsiCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_PEPSI_CAN)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (PepsiCount == 0)
			{
				Pepsi = false;
			}
		}

		if(Milo == true && Pepsi == false && CokeZero == false && Coke == false && Beans == false && Sardine == false && Peas == false) //Milo
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,2.8);
			RenderMesh(meshList[GEO_MILOCAN], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5  && MiloCount != 0)
			{
				moveItem = 0;
				MiloCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_MILOCAN)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (MiloCount == 0)
			{
				Milo = false;
			}

		}
		if(Cereal1 == true && Milo == false && Pepsi == false && CokeZero == false && Coke == false && Beans == false && Sardine == false && Peas == false) //Cereal 1
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,2.8);
			RenderMesh(meshList[GEO_CEREALBOX1], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5  && Cereal1Count != 0)
			{
				moveItem = 0;
				Cereal1Count --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_CEREALBOX1)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (Cereal1Count == 0)
			{
				Cereal1 = false;
			}

		}

		if(Cereal2 == true && Cereal1 == false && Milo == false && Pepsi == false && CokeZero == false && Coke == false && Beans == false && Sardine == false && Peas == false) //Cereal2
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,2.8);
			RenderMesh(meshList[GEO_CEREALBOX2], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5  && Cereal2Count != 0)
			{
				moveItem = 0;
				Cereal2Count --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_CEREALBOX2)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (Cereal2Count == 0)
			{
				Cereal2 = false;
			}

		}

		if(Pizza == true && Cereal2 == false && Cereal1 == false && Milo == false && Pepsi == false && CokeZero == false && Coke == false && Beans == false && Sardine == false && Peas == false) //Cereal2
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,2.8);
			RenderMesh(meshList[GEO_PIZZABOX], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5  && PizzaCount != 0)
			{
				moveItem = 0;
				PizzaCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_PIZZABOX)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (PizzaCount == 0)
			{
				Pizza = false;
			}

		}
		if(Lays == true && Pizza == false && Cereal2 == false && Cereal1 == false && Milo == false && Pepsi == false && CokeZero == false && Coke == false && Beans == false && Sardine == false && Peas == false) //Lays
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,2.8);
			RenderMesh(meshList[GEO_POTATOCHIPS], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5  && LaysCount != 0)
			{
				moveItem = 0;
				LaysCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_POTATOCHIPS)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (LaysCount == 0)
			{
				Lays = false;
			}
		}
	}

	//Extreme right cashier
	if(camera.position.z >= 22.2 && camera.position.z <= 25.f && camera.position.y >=4 && camera.position.y <= 10 && camera.position.x >= -26.f && camera.position.x <= -19.2)
	{
		if(Peas == true ) // Peas and Cans
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,19.9);
			RenderMesh(meshList[GEO_PEA_N_CARROTS], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5 && peaCount != 0)
			{
				moveItem = 0;
				peaCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_PEA_N_CARROTS)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}

			}
			else if (peaCount == 0 )
			{
				Peas = false;
			}

		}
		if(Sardine == true && Peas == false) //GEO_SARDINE_CAN
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,19.9);
			RenderMesh(meshList[GEO_SARDINE_CAN], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5 && SardineCount != 0)
			{
				moveItem = 0;
				SardineCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_SARDINE_CAN)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (SardineCount == 0)
			{
				Sardine = false;
			}

		}
		if(Beans == true && Sardine == false && Peas == false) //GEO_BAKED_BEANS_CAN,
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,19.9);
			RenderMesh(meshList[GEO_BAKED_BEANS_CAN], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5 && BeansCount != 0)
			{
				moveItem = 0;
				BeansCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_BAKED_BEANS_CAN)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (BeansCount == 0)
			{
				Beans = false;
			}

		}
		if(Coke == true && Beans == false && Sardine == false && Peas == false) //GEO_COKE_CAN,
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,19.9);
			RenderMesh(meshList[GEO_COKE_CAN], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5 && CokeCount != 0)
			{
				moveItem = 0;
				CokeCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_COKE_CAN)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (CokeCount == 0)
			{
				Coke = false;
			}

		}

		if(CokeZero == true && Coke == false && Beans == false && Sardine == false && Peas == false) //Coke zero (Can2)
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,19.9);
			RenderMesh(meshList[GEO_DRINKCAN2], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5  && CokeZeroCount != 0)
			{
				moveItem = 0;
				CokeZeroCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_DRINKCAN2)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (CokeZeroCount == 0)
			{
				CokeZero = false;
			}
		}
		//Pepsi
		if(Pepsi == true && CokeZero == false && Coke == false && Beans == false && Sardine == false && Peas == false) //Coke zero (Can2)
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,19.9);
			RenderMesh(meshList[GEO_PEPSI_CAN], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5  && PepsiCount != 0)
			{
				moveItem = 0;
				PepsiCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_PEPSI_CAN)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (PepsiCount == 0)
			{
				Pepsi = false;
			}
		}


		//Milo
		if(Milo == true && Pepsi == false && CokeZero == false && Coke == false && Beans == false && Sardine == false && Peas == false) //Milo
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,19.9);
			RenderMesh(meshList[GEO_MILOCAN], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5  && MiloCount != 0)
			{
				moveItem = 0;
				MiloCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_MILOCAN)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (MiloCount == 0)
			{
				Milo = false;
			}

		}
		//Cereal 1
		if(Cereal1 == true && Milo == false && Pepsi == false && CokeZero == false && Coke == false && Beans == false && Sardine == false && Peas == false) //Cereal 1
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,19.9);
			RenderMesh(meshList[GEO_CEREALBOX1], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5  && Cereal1Count != 0)
			{
				moveItem = 0;
				Cereal1Count --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_CEREALBOX1)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (Cereal1Count == 0)
			{
				Cereal1 = false;
			}

		}
		//Cereal 2
		if(Cereal2 == true && Cereal1 == false && Milo == false && Pepsi == false && CokeZero == false && Coke == false && Beans == false && Sardine == false && Peas == false) //Cereal2
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,19.9);
			RenderMesh(meshList[GEO_CEREALBOX2], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5  && Cereal2Count != 0)
			{
				moveItem = 0;
				Cereal2Count --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_CEREALBOX2)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (Cereal2Count == 0)
			{
				Cereal2 = false;
			}

		}
		//Pizza
		if(Pizza == true && Cereal2 == false && Cereal1 == false && Milo == false && Pepsi == false && CokeZero == false && Coke == false && Beans == false && Sardine == false && Peas == false) //Cereal2
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,19.9);
			RenderMesh(meshList[GEO_PIZZABOX], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5  && PizzaCount != 0)
			{
				moveItem = 0;
				PizzaCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_PIZZABOX)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (PizzaCount == 0)
			{
				Pizza = false;
			}

		}
		//Lays
		if(Lays == true && Pizza == false && Cereal2 == false && Cereal1 == false && Milo == false && Pepsi == false && CokeZero == false && Coke == false && Beans == false && Sardine == false && Peas == false) //Lays
		{
			modelStack.PushMatrix();
			modelStack.Translate(-20+moveItem,2.8,19.9);
			RenderMesh(meshList[GEO_POTATOCHIPS], false);
			modelStack.PopMatrix();

			if(moveItem <= -4.5  && LaysCount != 0)
			{
				moveItem = 0;
				LaysCount --;
				Sound = engine->play2D("Sound\\CheckoutBeep.wav");
				for(int i = 0;i < paidItems.size();++i)
				{
					if(paidItems[i].getobjType() == GEO_POTATOCHIPS)
					{
						paidItems[i].setPaid(true);
						player.getInventory().AddItem(paidItems[i]);
						paidItems.erase(paidItems.begin()+i); //Erases item once added into invent
						break;
					}
				}
			}
			if (LaysCount == 0)
			{
				Lays = false;
			}
		}
	}
	if(peaCount == PizzaCount == MiloCount == Cereal1Count == Cereal2Count == SardineCount == BeansCount == LaysCount == CokeCount == CokeZeroCount == PepsiCount == 0)
	{
		camera.setCheckingOut(false);
	}
}
/******************************************************************************/
/*!
\brief
Renders the Information related to Time Attack in the scene
*/
/******************************************************************************/
void StudioProject::RenderTimeAttack()
{
	//If list is generated
	if(generateList == false && TAlist.size() > 1)
	{
		/*==========================================================================================
		RENDERING OF LIST OF ITEMS
		============================================================================================*/
		int ListHeight = 28;
		int ListX = 24;
		int size = 2;
		int ListNo = 1;
		string ListNum;

		//Renders list of items based on the numbers contained in TAlist
		RenderTextOnScreen(meshList[GEO_TEXT],"List Of Items:", Color(1, 1,1 ), size, ListX, 29);
		for(int i = 0;i < TAlist.size(); i++)
		{
			std::ostringstream ListPos;
			ListPos << ListNo;
			ListNum = ListPos.str();
			if(TAlist.at(i) == GEO_SARDINE_CAN)
			{
				RenderTextOnScreen(meshList[GEO_TEXT], ListNum + ". Sardine Can", Color(1, 1, 1), size, ListX, ListHeight);
			}
			else if(TAlist.at(i) == GEO_PEA_N_CARROTS)
			{
				RenderTextOnScreen(meshList[GEO_TEXT],ListNum + ". Peas & Carrot", Color(1, 1, 1), size, ListX, ListHeight);
			}
			else if(TAlist.at(i) == GEO_BAKED_BEANS_CAN)
			{
				RenderTextOnScreen(meshList[GEO_TEXT],ListNum + ". Baked Beans", Color(1, 1, 1), size, ListX, ListHeight);
			}
			else if(TAlist.at(i) == GEO_COKE_CAN)
			{
				RenderTextOnScreen(meshList[GEO_TEXT],ListNum + ". Can of Coke", Color(1, 1, 1), size, ListX, ListHeight);
			}
			else if(TAlist.at(i) == GEO_DRINKCAN2)
			{
				RenderTextOnScreen(meshList[GEO_TEXT],ListNum + ". Coke Zero", Color(1, 1, 1), size, ListX, ListHeight);
			}
			else if(TAlist.at(i) == GEO_PEPSI_CAN)
			{
				RenderTextOnScreen(meshList[GEO_TEXT],ListNum + ". Can of Pepsi", Color(1, 1, 1), size, ListX, ListHeight);
			}
			else if(TAlist.at(i) == GEO_MILOCAN)
			{
				RenderTextOnScreen(meshList[GEO_TEXT],ListNum + ". Can of Milo", Color(1, 1, 1), size, ListX, ListHeight);
			}
			else if(TAlist.at(i) == GEO_CEREALBOX1)
			{
				RenderTextOnScreen(meshList[GEO_TEXT],ListNum + ". Bran Buds", Color(1, 1, 1), size, ListX, ListHeight);
			}
			else if(TAlist.at(i) == GEO_CEREALBOX2)
			{
				RenderTextOnScreen(meshList[GEO_TEXT],ListNum + ". Morning Chips", Color(1, 1, 1), size, ListX, ListHeight);
			}
			else if(TAlist.at(i) == GEO_PIZZABOX)
			{
				RenderTextOnScreen(meshList[GEO_TEXT],ListNum + ". Frozen Pizza", Color(1, 1, 1), size, ListX, ListHeight);
			}
			else if(TAlist.at(i) == GEO_POTATOCHIPS)
			{
				RenderTextOnScreen(meshList[GEO_TEXT],ListNum + ". Lays Chips", Color(1, 1, 1), size, ListX, ListHeight);
			}
			ListHeight--;
			ListNo++;
		}
	}
	//===Rendering of Timer===//
	if(TimeAttack == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT],timeTA, Color(1, 1,1 ), 2, 15, 29);
	}
	//if TA is won, renders winning message
	if(isTAwon == true && messageTime <= 3)
	{
		RenderTextOnScreen(meshList[GEO_TEXT],"Congratulations", Color(1, 1, 1), 3, 10, 10);
	}
	//if TA is lost, renders losing message
	if(isTAwon == false && TAstartedOnce > 0 && messageTime <= 3)
	{
		RenderTextOnScreen(meshList[GEO_TEXT],"You Lose", Color(1, 1, 1), 3, 10, 10);
	}
}
/******************************************************************************/
/*!
\brief
Renders the Information related to Guess The Price in the scene
*/
/******************************************************************************/
void StudioProject::RenderGTP()
{
	if(GTP == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT],"Guess The Price", Color(0, 1, 0), 3, 6, 19);
	}
	//if TA is won, renders winning message
	if(isGTPwon == true && messageTime <= 3)
	{
		std::ostringstream ssNoOfItem;
		ssNoOfItem << NoOfItemsTaken;
		NumItem = ssNoOfItem.str();

		std::ostringstream ssTotalPrice;
		ssTotalPrice << totalCost;
		CostOfItems = ssTotalPrice.str();

		RenderTextOnScreen(meshList[GEO_TEXT],"Congratulations", Color(0, 1, 0), 3, 10, 10);
		RenderTextOnScreen(meshList[GEO_TEXT],"You Have Taken: " + NumItem, Color(0, 1, 0), 3, 10, 9);
		RenderTextOnScreen(meshList[GEO_TEXT],"Total Cost: " + CostOfItems, Color(0, 1, 0), 3, 10, 8);

	}
	//if GTP is lost, renders losing message
	if(isGTPwon == false && GTPstartedOnce > 0 && messageTime <= 3)
	{
		std::ostringstream ssTotalPrice;
		ssTotalPrice << totalCost;
		CostOfItems = ssTotalPrice.str();

		RenderTextOnScreen(meshList[GEO_TEXT],"You Lose", Color(1, 0, 0), 3, 10, 10);
		RenderTextOnScreen(meshList[GEO_TEXT],"Total Cost: " + CostOfItems, Color(1, 0, 0), 3, 10, 9);
	}
}
/******************************************************************************/
/*!
\brief
Renders the Information related to Theif mini game in the scene
*/
/******************************************************************************/
void StudioProject::RenderThiefGame()
{
	if(ThiefGame == true)
	{
		RenderTextOnScreen(meshList[GEO_TEXT],"Steal Items", Color(0, 1, 0), 3, 6, 19);
	}
	//if TA is won, renders winning message
	if(isThiefwon == true && messageTime <= 3)
	{
		std::ostringstream ssNoOfItemStolen;
		ssNoOfItemStolen << NoOfItemsStolen;
		NumStolen = ssNoOfItemStolen.str();

		RenderTextOnScreen(meshList[GEO_TEXT],"Congratulations", Color(0, 1, 0), 3, 10, 10);
		RenderTextOnScreen(meshList[GEO_TEXT],"You Have Stolen: " + NumStolen, Color(0, 1, 0), 3, 10, 9);
	}
}
/******************************************************************************/
/*!
\brief
Renders everything in the scene
*/
/******************************************************************************/
void StudioProject::Render()
{
	//clear depth and color buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Temp variables
	Mtx44 MVP;

	viewStack.LoadIdentity();
	viewStack.LookAt(camera.position.x, camera.position.y, camera.position.z, camera.target.x, camera.target.y, camera.target.z, camera.up.x, camera.up.y, camera.up.z);
	modelStack.LoadIdentity();

	//======================Renderin of Menu===================//
	if (menu.getShowMenuStatus() == true)
	{
		RenderMenuOnScreen(meshList[MENUBACKGROUND], Color(1, 1, 1), 1, 1, 1);
		if (menu.getShowContorlStatus() == false)
		{
			RenderTextOnScreen(meshList[GEO_TEXT], "Press UP or DOWN for navigation", Color(1, 1, 1), 2, 1, 2);
			RenderTextOnScreen(meshList[GEO_TEXT], "Press ENTER to enter input", Color(1, 1, 1), 2, 1, 1);
		}
	}
	else if (menu.getShowMenuStatus() == false && Guard1.getCatchPlayerState() == false && Guard2.getCatchPlayerState() == false && winState == false)
	{

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

		//Light 3
		if(lights[2].type == Light::LIGHT_DIRECTIONAL)
		{
			Vector3 lightDir(lights[2].position.x, lights[2].position.y, lights[2].position.z);
			Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
			glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightDirection_cameraspace.x);
		}
		else if(lights[2].type == Light::LIGHT_SPOT)
		{
			Position lightPosition_cameraspace = viewStack.Top() * lights[2].position;
			glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightPosition_cameraspace.x);
			Vector3 spotDirection_cameraspace = viewStack.Top() * lights[2].spotDirection;
			glUniform3fv(m_parameters[U_LIGHT2_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
		}
		else
		{
			Position lightPosition_cameraspace = viewStack.Top() * lights[2].position;
			glUniform3fv(m_parameters[U_LIGHT2_POSITION], 1, &lightPosition_cameraspace.x);
		}

		//Light 4
		if(lights[3].type == Light::LIGHT_DIRECTIONAL)
		{
			Vector3 lightDir(lights[3].position.x, lights[3].position.y, lights[3].position.z);
			Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
			glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightDirection_cameraspace.x);
		}
		else if(lights[3].type == Light::LIGHT_SPOT)
		{
			Position lightPosition_cameraspace = viewStack.Top() * lights[3].position;
			glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightPosition_cameraspace.x);
			Vector3 spotDirection_cameraspace = viewStack.Top() * lights[3].spotDirection;
			glUniform3fv(m_parameters[U_LIGHT3_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
		}
		else
		{ 
			Position lightPosition_cameraspace = viewStack.Top() * lights[3].position;
			glUniform3fv(m_parameters[U_LIGHT3_POSITION], 1, &lightPosition_cameraspace.x);
		}

		//Light 5
		if(lights[4].type == Light::LIGHT_DIRECTIONAL)
		{
			Vector3 lightDir(lights[4].position.x, lights[4].position.y, lights[4].position.z);
			Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
			glUniform3fv(m_parameters[U_LIGHT4_POSITION], 1, &lightDirection_cameraspace.x);
		}
		else if(lights[4].type == Light::LIGHT_SPOT)
		{
			Position lightPosition_cameraspace = viewStack.Top() * lights[4].position;
			glUniform3fv(m_parameters[U_LIGHT4_POSITION], 1, &lightPosition_cameraspace.x);
			Vector3 spotDirection_cameraspace = viewStack.Top() * lights[4].spotDirection;
			glUniform3fv(m_parameters[U_LIGHT4_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
		}
		else
		{
			Position lightPosition_cameraspace = viewStack.Top() * lights[4].position;
			glUniform3fv(m_parameters[U_LIGHT4_POSITION], 1, &lightPosition_cameraspace.x);
		}

		//Light 6 (Middle front (Bottom))
		if(lights[5].type == Light::LIGHT_DIRECTIONAL)
		{
			Vector3 lightDir(lights[5].position.x, lights[5].position.y, lights[5].position.z);
			Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
			glUniform3fv(m_parameters[U_LIGHT5_POSITION], 1, &lightDirection_cameraspace.x);
		}
		else if(lights[5].type == Light::LIGHT_SPOT)
		{
			Position lightPosition_cameraspace = viewStack.Top() * lights[5].position;
			glUniform3fv(m_parameters[U_LIGHT4_POSITION], 1, &lightPosition_cameraspace.x);
			Vector3 spotDirection_cameraspace = viewStack.Top() * lights[5].spotDirection;
			glUniform3fv(m_parameters[U_LIGHT5_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
		}
		else
		{
			Position lightPosition_cameraspace = viewStack.Top() * lights[5].position;
			glUniform3fv(m_parameters[U_LIGHT5_POSITION], 1, &lightPosition_cameraspace.x);
		}

		//Light 7 (Middle front (2nd floor))
		if(lights[6].type == Light::LIGHT_DIRECTIONAL)
		{
			Vector3 lightDir(lights[6].position.x, lights[6].position.y, lights[6].position.z);
			Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
			glUniform3fv(m_parameters[U_LIGHT6_POSITION], 1, &lightDirection_cameraspace.x);
		}
		else if(lights[6].type == Light::LIGHT_SPOT)
		{
			Position lightPosition_cameraspace = viewStack.Top() * lights[6].position;
			glUniform3fv(m_parameters[U_LIGHT6_POSITION], 1, &lightPosition_cameraspace.x);
			Vector3 spotDirection_cameraspace = viewStack.Top() * lights[6].spotDirection;
			glUniform3fv(m_parameters[U_LIGHT6_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
		}
		else
		{
			Position lightPosition_cameraspace = viewStack.Top() * lights[6].position;
			glUniform3fv(m_parameters[U_LIGHT6_POSITION], 1, &lightPosition_cameraspace.x);
		}

		//Light 8 (Middle front (2nd floor))
		if(lights[7].type == Light::LIGHT_DIRECTIONAL)
		{
			Vector3 lightDir(lights[7].position.x, lights[7].position.y, lights[7].position.z);
			Vector3 lightDirection_cameraspace = viewStack.Top() * lightDir;
			glUniform3fv(m_parameters[U_LIGHT7_POSITION], 1, &lightDirection_cameraspace.x);
		}
		else if(lights[7].type == Light::LIGHT_SPOT)
		{
			Position lightPosition_cameraspace = viewStack.Top() * lights[7].position;
			glUniform3fv(m_parameters[U_LIGHT7_POSITION], 1, &lightPosition_cameraspace.x);
			Vector3 spotDirection_cameraspace = viewStack.Top() * lights[7].spotDirection;
			glUniform3fv(m_parameters[U_LIGHT7_SPOTDIRECTION], 1, &spotDirection_cameraspace.x);
		}
		else
		{
			Position lightPosition_cameraspace = viewStack.Top() * lights[7].position;
			glUniform3fv(m_parameters[U_LIGHT7_POSITION], 1, &lightPosition_cameraspace.x);
		}

		//===Rendering Level 1 Lights
		RenderLevel1Lights();

		MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
		glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);
		RenderMesh(meshList[GEO_AXES], false);

		//Rendering skybox
		modelStack.PushMatrix();
		modelStack.Translate(camera.position.x, camera.position.y, camera.position.z);
		modelStack.Rotate(180, 0, 1, 0);
		RenderSkybox();
		modelStack.PopMatrix();

		//Rendering of supermarket scene
		modelStack.PushMatrix();
		RenderSupermarket();
		RenderItems();
		modelStack.PopMatrix();


		//Rendering of CharacterModel
		modelStack.PushMatrix();
		RenderModel();
		modelStack.PopMatrix();

		//Rendering of CashierModel
		modelStack.PushMatrix(); //Moving of cashier
		modelStack.Translate(-24, 0, 17);
		modelStack.Rotate(90,0,1,0);
		modelStack.PushMatrix();
		modelStack.Scale(1.2, 1.2, 1.2);
		modelStack.Rotate(90, 0, 90, 0);
		RenderCashier();
		modelStack.PopMatrix();
		modelStack.PopMatrix();

		//Rendering of CashierModel
		modelStack.PushMatrix(); //Moving of cashier
		modelStack.Translate(-24, 0, 0);
		modelStack.Rotate(90,0,1,0);
		modelStack.PushMatrix();
		modelStack.Scale(1.2, 1.2, 1.2);
		modelStack.Rotate(90, 0, 90, 0);
		RenderCashier();
		modelStack.PopMatrix();
		modelStack.PopMatrix();

		//Rendering of CashierModel
		modelStack.PushMatrix(); //Moving of cashier
		modelStack.Translate(-24, 0, -18);
		modelStack.Rotate(90,0,1,0);
		modelStack.PushMatrix();
		modelStack.Scale(1.2, 1.2, 1.2);
		modelStack.Rotate(90, 0, 90, 0);
		RenderCashier();
		modelStack.PopMatrix();
		modelStack.PopMatrix();

		//Rendering of GuardModel
		modelStack.PushMatrix();
		RenderGuard();
		modelStack.PopMatrix();

		//Rendering of CustomerModel1
		modelStack.PushMatrix(); //Moving of customer
		modelStack.Translate(Passerby[0].getPasserbyPosition().x, 0, Passerby[0].getPasserbyPosition().z);
		modelStack.PushMatrix();
		modelStack.Scale(1.2, 1.2, 1.2);
		modelStack.Rotate(Passerby[0].getPasserbyAngle(), 0, 1, 0);
		RenderCustomer();
		modelStack.PopMatrix();
		modelStack.PopMatrix();

		//Rendering of CustomerModel2
		modelStack.PushMatrix(); //Moving of customer
		modelStack.Translate(Passerby[1].getPasserby2Position().x, 0, Passerby[1].getPasserby2Position().z);
		modelStack.PushMatrix();
		modelStack.Scale(1.2, 1.2, 1.2);
		modelStack.Rotate(Passerby[1].getPasserbyAngle2(), 0, 1, 0);
		RenderCustomer();
		modelStack.PopMatrix();
		modelStack.PopMatrix();

		//Rendering of CustomerModel3
		modelStack.PushMatrix(); //Moving of customer
		modelStack.Translate(Passerby[2].getPasserby3Position().x, Passerby[2].getPasserby3Position().y, Passerby[2].getPasserby3Position().z);
		modelStack.PushMatrix();
		modelStack.Scale(1.2, 1.2, 1.2);
		modelStack.Rotate(Passerby[2].getPasserbyAngle3(), 0, 1, 0);
		RenderCustomer();
		modelStack.PopMatrix();
		modelStack.PopMatrix();

		//=======DOORS=====//
		//LEFTDOOR
		modelStack.PushMatrix();
		modelStack.Translate(-55.75,0.15,doorTranslate);
		modelStack.Scale(5,5,5);

		RenderMesh(meshList[GEO_DOORLEFT],B_Light);
		modelStack.PopMatrix();


		//RIGHTDOOR
		modelStack.PushMatrix();
		modelStack.Translate(-56,0,-doorTranslate);
		modelStack.Scale(5,5,5);
		RenderMesh(meshList[GEO_DOORRIGHT],B_Light);
		modelStack.PopMatrix();

		//Rendering of itempage
		if (showInventory == true)
		{
			RenderImageOnScreen(meshList[itemInventory], Color(1, 1, 1), 100, 1, 1);
		}
		/*=====================================================
		Rendering of Information for player
		=======================================================*/
		RenderPlayerInfo();
		RenderItemsInfo();

		//============DEBUGGING PURPOSES====================//

		RenderTextOnScreen(meshList[GEO_TEXT],"+", Color(0, 0, 0), 3, 13.55, 10);

		//==Controls==//
		if(isShown == true)
		{
			//============DEBUGGING PURPOSES====================//
			RenderTextOnScreen(meshList[GEO_TEXT], Framerate + result, Color(0, 1, 0), 3, 1, 2);
			RenderTextOnScreen(meshList[GEO_TEXT],"x: " + camerax, Color(0, 1, 0), 3, 1, 3);
			RenderTextOnScreen(meshList[GEO_TEXT],"y: " + cameray, Color(0, 1, 0), 3, 1, 4);
			RenderTextOnScreen(meshList[GEO_TEXT],"z: " + cameraz, Color(0, 1, 0), 3, 1, 5);
		}

		RenderCheckOutItems();

		RenderTimeAttack();

		RenderGTP();

		RenderThiefGame();
	}
	else if (menu.getShowMenuStatus() == false && Guard1.getCatchPlayerState() == true ||
		menu.getShowMenuStatus() == false && Guard2.getCatchPlayerState() == true)
	{
		RenderMenuOnScreen(meshList[MENUBACKGROUND], Color(1, 1, 1), 1, 1, 1);
	}

	if (winState == true)
	{
		RenderMenuOnScreen(meshList[MENUBACKGROUND], Color(1, 1, 1), 1, 1, 1);
	}
}
/******************************************************************************/
/*!
\brief
Renders the different kind of meshes and light

\param	mesh - address for different meshes
\param	enableLight - boolean for light
*/
/******************************************************************************/
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
/******************************************************************************/
/*!
\brief
Renders Text in World Space

\param	mesh - address for different meshes
\param	text - text to be rendered
\param	color - color of text
*/
/******************************************************************************/
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
/******************************************************************************/
/*!
\brief
Renders Images on screen

\param	mesh - address for different meshes
\param	color - color of image
\param	size - size of image
\param	x - x coordinate of image on screen
\param	y - y coordinate of image on screen
*/
/******************************************************************************/
void StudioProject::RenderImageOnScreen(Mesh* mesh, Color color, float size, float x, float y)
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

	//for(unsigned i = 0; i < text.length(); ++i)
	//{
	//	Mtx44 characterSpacing;
	//	characterSpacing.SetToTranslation(i * 1.0f, 0, 0); //1.0f is the spacing of each character, you may change this value
	//	Mtx44 MVP = projectionStack.Top() * viewStack.Top() * modelStack.Top();
	//	glUniformMatrix4fv(m_parameters[U_MVP], 1, GL_FALSE, &MVP.a[0]);

	//	mesh->Render((unsigned)text[i] * 6, 6);
	//}
	modelStack.PushMatrix();
	modelStack.Translate(-0.6, -0.6,0);
	modelStack.Scale(0.8, 0.8, 0.8);
	RenderMesh(meshList[itemInventory], false);
	modelStack.PopMatrix();

	if (Page.getItemsTaken1() == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-0.91f, -0.95f, 0);
		modelStack.Scale(0.07f, 0.07f, 0.07f);
		if (player.getInventory().getItem(1).getName() == Page.getSardineName() 
			&& player.getInventory().getItem(1).getPaid() == false)
		{
			RenderMesh(meshList[Page.getSardineMesh()], false);
		}
		if (player.getInventory().getItem(1).getName() == Page.getPncName() 
			&& player.getInventory().getItem(1).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPncMesh()], false);
		}
		if (player.getInventory().getItem(1).getName() == Page.getBakedBeanName() 
			&& player.getInventory().getItem(1).getPaid() == false)
		{
			RenderMesh(meshList[Page.getBakedBeanMesh()], false);
		}
		if (player.getInventory().getItem(1).getName() == Page.getPizzaboxName()
			&& player.getInventory().getItem(1).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPizzaboxMesh()], false);
		}
		if (player.getInventory().getItem(1).getName() == Page.getCerealbox1Name()
			&& player.getInventory().getItem(1).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCerealbox1Mesh()], false);
		}
		if (player.getInventory().getItem(1).getName() == Page.getCerealbox2Name()
			&& player.getInventory().getItem(1).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCerealbox2Mesh()], false);
		}
		if (player.getInventory().getItem(1).getName() == Page.getPotatoChipName()
			&& player.getInventory().getItem(1).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPotatoChipMesh()], false);
		}
		if (player.getInventory().getItem(1).getName() == Page.getCokeName()
			&& player.getInventory().getItem(1).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCokeMesh()], false);
		}
		if (player.getInventory().getItem(1).getName() == Page.getCokeZeroName()
			&& player.getInventory().getItem(1).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCokeZeroMesh()], false);
		}
		if (player.getInventory().getItem(1).getName() == Page.getPepsiName()
			&& player.getInventory().getItem(1).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPepsiMesh()], false);
		}
		if (player.getInventory().getItem(1).getName() == Page.getMiloName()
			&& player.getInventory().getItem(1).getPaid() == false)
		{
			RenderMesh(meshList[Page.getMiloMesh()], false);
		}
		modelStack.PopMatrix();
	}

	if (Page.getItemsTaken2() == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-0.84, -0.95, 0);
		modelStack.Scale(0.07, 0.07, 0.07);
		if (player.getInventory().getItem(2).getName() == Page.getSardineName() 
			&& player.getInventory().getItem(2).getPaid() == false)
		{
			RenderMesh(meshList[Page.getSardineMesh()], false);
		}
		if (player.getInventory().getItem(2).getName() == Page.getPncName()
			&& player.getInventory().getItem(2).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPncMesh()], false);
		}
		if (player.getInventory().getItem(2).getName() == Page.getBakedBeanName()
			&& player.getInventory().getItem(2).getPaid() == false)
		{
			RenderMesh(meshList[Page.getBakedBeanMesh()], false);
		}
		if (player.getInventory().getItem(2).getName() == Page.getPizzaboxName()
			&& player.getInventory().getItem(2).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPizzaboxMesh()], false);
		}
		if (player.getInventory().getItem(2).getName() == Page.getCerealbox1Name()
			&& player.getInventory().getItem(2).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCerealbox1Mesh()], false);
		}
		if (player.getInventory().getItem(2).getName() == Page.getCerealbox2Name()
			&& player.getInventory().getItem(2).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCerealbox2Mesh()], false);
		}
		if (player.getInventory().getItem(2).getName() == Page.getPotatoChipName()
			&& player.getInventory().getItem(2).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPotatoChipMesh()], false);
		}
		if (player.getInventory().getItem(2).getName() == Page.getCokeName()
			&& player.getInventory().getItem(2).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCokeMesh()], false);
		}
		if (player.getInventory().getItem(2).getName() == Page.getCokeZeroName()
			&& player.getInventory().getItem(2).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCokeZeroMesh()], false);
		}
		if (player.getInventory().getItem(2).getName() == Page.getPepsiName()
			&& player.getInventory().getItem(2).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPepsiMesh()], false);
		}
		if (player.getInventory().getItem(2).getName() == Page.getMiloName()
			&& player.getInventory().getItem(2).getPaid() == false)
		{
			RenderMesh(meshList[Page.getMiloMesh()], false);
		}
		modelStack.PopMatrix();
	}

	if (Page.getItemsTaken3() == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-0.77, -0.95, 0);
		modelStack.Scale(0.07, 0.07, 0.07);
		if (player.getInventory().getItem(3).getName() == Page.getSardineName()
			&& player.getInventory().getItem(3).getPaid() == false)
		{
			RenderMesh(meshList[Page.getSardineMesh()], false);
		}
		if (player.getInventory().getItem(3).getName() == Page.getPncName()
			&& player.getInventory().getItem(3).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPncMesh()], false);
		}
		if (player.getInventory().getItem(3).getName() == Page.getBakedBeanName()
			&& player.getInventory().getItem(3).getPaid() == false)
		{
			RenderMesh(meshList[Page.getBakedBeanMesh()], false);
		}
		if (player.getInventory().getItem(3).getName() == Page.getPizzaboxName()
			&& player.getInventory().getItem(3).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPizzaboxMesh()], false);
		}
		if (player.getInventory().getItem(3).getName() == Page.getCerealbox1Name()
			&& player.getInventory().getItem(3).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCerealbox1Mesh()], false);
		}
		if (player.getInventory().getItem(3).getName() == Page.getCerealbox2Name()
			&& player.getInventory().getItem(3).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCerealbox2Mesh()], false);
		}
		if (player.getInventory().getItem(3).getName() == Page.getPotatoChipName()
			&& player.getInventory().getItem(3).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPotatoChipMesh()], false);
		}
		if (player.getInventory().getItem(3).getName() == Page.getCokeName()
			&& player.getInventory().getItem(3).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCokeMesh()], false);
		}
		if (player.getInventory().getItem(3).getName() == Page.getCokeZeroName()
			&& player.getInventory().getItem(3).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCokeZeroMesh()], false);
		}
		if (player.getInventory().getItem(3).getName() == Page.getPepsiName()
			&& player.getInventory().getItem(3).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPepsiMesh()], false);
		}
		if (player.getInventory().getItem(3).getName() == Page.getMiloName()
			&& player.getInventory().getItem(3).getPaid() == false)
		{
			RenderMesh(meshList[Page.getMiloMesh()], false);
		}
		modelStack.PopMatrix();
	}
	if (Page.getItemsTaken4() == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-0.70, -0.95, 0);
		modelStack.Scale(0.07, 0.07, 0.07);
		if (player.getInventory().getItem(4).getName() == Page.getSardineName()
			&& player.getInventory().getItem(4).getPaid() == false)
		{
			RenderMesh(meshList[Page.getSardineMesh()], false);
		}
		if (player.getInventory().getItem(4).getName() == Page.getPncName()
			&& player.getInventory().getItem(4).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPncMesh()], false);
		}
		if (player.getInventory().getItem(4).getName() == Page.getBakedBeanName()
			&& player.getInventory().getItem(4).getPaid() == false)
		{
			RenderMesh(meshList[Page.getBakedBeanMesh()], false);
		}
		if (player.getInventory().getItem(4).getName() == Page.getPizzaboxName()
			&& player.getInventory().getItem(4).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPizzaboxMesh()], false);
		}
		if (player.getInventory().getItem(4).getName() == Page.getCerealbox1Name()
			&& player.getInventory().getItem(4).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCerealbox1Mesh()], false);
		}
		if (player.getInventory().getItem(4).getName() == Page.getCerealbox2Name()
			&& player.getInventory().getItem(4).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCerealbox2Mesh()], false);
		}
		if (player.getInventory().getItem(4).getName() == Page.getPotatoChipName()
			&& player.getInventory().getItem(4).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPotatoChipMesh()], false);
		}
		if (player.getInventory().getItem(4).getName() == Page.getCokeName()
			&& player.getInventory().getItem(4).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCokeMesh()], false);
		}
		if (player.getInventory().getItem(4).getName() == Page.getCokeZeroName()
			&& player.getInventory().getItem(4).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCokeZeroMesh()], false);
		}
		if (player.getInventory().getItem(4).getName() == Page.getPepsiName()
			&& player.getInventory().getItem(4).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPepsiMesh()], false);
		}
		if (player.getInventory().getItem(4).getName() == Page.getMiloName()
			&& player.getInventory().getItem(4).getPaid() == false)
		{
			RenderMesh(meshList[Page.getMiloMesh()], false);
		}
		modelStack.PopMatrix();
	}

	if (Page.getItemsTaken5() == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-0.63, -0.95, 0);
		modelStack.Scale(0.07, 0.07, 0.07);
		if (player.getInventory().getItem(5).getName() == Page.getSardineName()
			&& player.getInventory().getItem(5).getPaid() == false)
		{
			RenderMesh(meshList[Page.getSardineMesh()], false);
		}
		if (player.getInventory().getItem(5).getName() == Page.getPncName()
			&& player.getInventory().getItem(5).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPncMesh()], false);
		}
		if (player.getInventory().getItem(5).getName() == Page.getBakedBeanName()
			&& player.getInventory().getItem(5).getPaid() == false)
		{
			RenderMesh(meshList[Page.getBakedBeanMesh()], false);
		}
		if (player.getInventory().getItem(5).getName() == Page.getPizzaboxName()
			&& player.getInventory().getItem(5).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPizzaboxMesh()], false);
		}
		if (player.getInventory().getItem(5).getName() == Page.getCerealbox1Name()
			&& player.getInventory().getItem(5).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCerealbox1Mesh()], false);
		}
		if (player.getInventory().getItem(5).getName() == Page.getCerealbox2Name()
			&& player.getInventory().getItem(5).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCerealbox2Mesh()], false);
		}
		if (player.getInventory().getItem(5).getName() == Page.getPotatoChipName()
			&& player.getInventory().getItem(5).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPotatoChipMesh()], false);
		}
		if (player.getInventory().getItem(5).getName() == Page.getCokeName()
			&& player.getInventory().getItem(5).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCokeMesh()], false);
		}
		if (player.getInventory().getItem(5).getName() == Page.getCokeZeroName()
			&& player.getInventory().getItem(5).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCokeZeroMesh()], false);
		}
		if (player.getInventory().getItem(5).getName() == Page.getPepsiName()
			&& player.getInventory().getItem(5).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPepsiMesh()], false);
		}
		if (player.getInventory().getItem(5).getName() == Page.getMiloName()
			&& player.getInventory().getItem(5).getPaid() == false)
		{
			RenderMesh(meshList[Page.getMiloMesh()], false);
		}
		modelStack.PopMatrix();
	}

	if (Page.getItemsTaken6() == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-0.56, -0.95, 0);
		modelStack.Scale(0.07, 0.07, 0.07);
		if (player.getInventory().getItem(6).getName() == Page.getSardineName()
			&& player.getInventory().getItem(6).getPaid() == false)
		{
			RenderMesh(meshList[Page.getSardineMesh()], false);
		}
		if (player.getInventory().getItem(6).getName() == Page.getPncName()
			&& player.getInventory().getItem(6).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPncMesh()], false);
		}
		if (player.getInventory().getItem(6).getName() == Page.getBakedBeanName()
			&& player.getInventory().getItem(6).getPaid() == false)
		{
			RenderMesh(meshList[Page.getBakedBeanMesh()], false);
		}
		if (player.getInventory().getItem(6).getName() == Page.getPizzaboxName()
			&& player.getInventory().getItem(6).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPizzaboxMesh()], false);
		}
		if (player.getInventory().getItem(6).getName() == Page.getCerealbox1Name()
			&& player.getInventory().getItem(6).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCerealbox1Mesh()], false);
		}
		if (player.getInventory().getItem(6).getName() == Page.getCerealbox2Name()
			&& player.getInventory().getItem(6).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCerealbox2Mesh()], false);
		}
		if (player.getInventory().getItem(6).getName() == Page.getPotatoChipName()
			&& player.getInventory().getItem(6).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPotatoChipMesh()], false);
		}
		if (player.getInventory().getItem(6).getName() == Page.getCokeName()
			&& player.getInventory().getItem(6).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCokeMesh()], false);
		}
		if (player.getInventory().getItem(6).getName() == Page.getCokeZeroName()
			&& player.getInventory().getItem(6).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCokeZeroMesh()], false);
		}
		if (player.getInventory().getItem(6).getName() == Page.getPepsiName()
			&& player.getInventory().getItem(6).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPepsiMesh()], false);
		}
		if (player.getInventory().getItem(6).getName() == Page.getMiloName()
			&& player.getInventory().getItem(6).getPaid() == false)
		{
			RenderMesh(meshList[Page.getMiloMesh()], false);
		}
		modelStack.PopMatrix();
	}

	if (Page.getItemsTaken7() == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-0.495, -0.95, 0);
		modelStack.Scale(0.07, 0.07, 0.07);
		if (player.getInventory().getItem(7).getName() == Page.getSardineName()
			&& player.getInventory().getItem(7).getPaid() == false)
		{
			RenderMesh(meshList[Page.getSardineMesh()], false);
		}
		if (player.getInventory().getItem(7).getName() == Page.getPncName()
			&& player.getInventory().getItem(7).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPncMesh()], false);
		}
		if (player.getInventory().getItem(7).getName() == Page.getBakedBeanName()
			&& player.getInventory().getItem(7).getPaid() == false)
		{
			RenderMesh(meshList[Page.getBakedBeanMesh()], false);
		}
		if (player.getInventory().getItem(7).getName() == Page.getPizzaboxName()
			&& player.getInventory().getItem(7).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPizzaboxMesh()], false);
		}
		if (player.getInventory().getItem(7).getName() == Page.getCerealbox1Name()
			&& player.getInventory().getItem(7).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCerealbox1Mesh()], false);
		}
		if (player.getInventory().getItem(7).getName() == Page.getCerealbox2Name()
			&& player.getInventory().getItem(7).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCerealbox2Mesh()], false);
		}
		if (player.getInventory().getItem(7).getName() == Page.getPotatoChipName()
			&& player.getInventory().getItem(7).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPotatoChipMesh()], false);
		}
		if (player.getInventory().getItem(7).getName() == Page.getCokeName()
			&& player.getInventory().getItem(7).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCokeMesh()], false);
		}
		if (player.getInventory().getItem(7).getName() == Page.getCokeZeroName()
			&& player.getInventory().getItem(7).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCokeZeroMesh()], false);
		}
		if (player.getInventory().getItem(7).getName() == Page.getPepsiName()
			&& player.getInventory().getItem(7).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPepsiMesh()], false);
		}
		if (player.getInventory().getItem(7).getName() == Page.getMiloName()
			&& player.getInventory().getItem(7).getPaid() == false)
		{
			RenderMesh(meshList[Page.getMiloMesh()], false);
		}
		modelStack.PopMatrix();
	}

	if (Page.getItemsTaken8() == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-0.425, -0.95, 0);
		modelStack.Scale(0.07, 0.07, 0.07);
		if (player.getInventory().getItem(8).getName() == Page.getSardineName()
			&& player.getInventory().getItem(8).getPaid() == false)
		{
			RenderMesh(meshList[Page.getSardineMesh()], false);
		}
		if (player.getInventory().getItem(8).getName() == Page.getPncName()
			&& player.getInventory().getItem(8).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPncMesh()], false);
		}
		if (player.getInventory().getItem(8).getName() == Page.getBakedBeanName()
			&& player.getInventory().getItem(8).getPaid() == false)
		{
			RenderMesh(meshList[Page.getBakedBeanMesh()], false);
		}
		if (player.getInventory().getItem(8).getName() == Page.getPizzaboxName()
			&& player.getInventory().getItem(8).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPizzaboxMesh()], false);
		}
		if (player.getInventory().getItem(8).getName() == Page.getCerealbox1Name()
			&& player.getInventory().getItem(8).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCerealbox1Mesh()], false);
		}
		if (player.getInventory().getItem(8).getName() == Page.getCerealbox2Name()
			&& player.getInventory().getItem(8).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCerealbox2Mesh()], false);
		}
		if (player.getInventory().getItem(8).getName() == Page.getPotatoChipName()
			&& player.getInventory().getItem(8).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPotatoChipMesh()], false);
		}
		if (player.getInventory().getItem(8).getName() == Page.getCokeName()
			&& player.getInventory().getItem(8).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCokeMesh()], false);
		}
		if (player.getInventory().getItem(8).getName() == Page.getCokeZeroName()
			&& player.getInventory().getItem(8).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCokeZeroMesh()], false);
		}
		if (player.getInventory().getItem(8).getName() == Page.getPepsiName()
			&& player.getInventory().getItem(8).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPepsiMesh()], false);
		}
		if (player.getInventory().getItem(8).getName() == Page.getMiloName()
			&& player.getInventory().getItem(8).getPaid() == false)
		{
			RenderMesh(meshList[Page.getMiloMesh()], false);
		}
		modelStack.PopMatrix();
	}

	if (Page.getItemsTaken9() == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-0.36, -0.95, 0);
		modelStack.Scale(0.07, 0.07, 0.07);
		if (player.getInventory().getItem(9).getName() == Page.getSardineName()
			&& player.getInventory().getItem(9).getPaid() == false)
		{
			RenderMesh(meshList[Page.getSardineMesh()], false);
		}
		if (player.getInventory().getItem(9).getName() == Page.getPncName()
			&& player.getInventory().getItem(9).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPncMesh()], false);
		}
		if (player.getInventory().getItem(9).getName() == Page.getBakedBeanName()
			&& player.getInventory().getItem(9).getPaid() == false)
		{
			RenderMesh(meshList[Page.getBakedBeanMesh()], false);
		}
		if (player.getInventory().getItem(9).getName() == Page.getPizzaboxName()
			&& player.getInventory().getItem(9).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPizzaboxMesh()], false);
		}
		if (player.getInventory().getItem(9).getName() == Page.getCerealbox1Name()
			&& player.getInventory().getItem(9).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCerealbox1Mesh()], false);
		}
		if (player.getInventory().getItem(9).getName() == Page.getCerealbox2Name()
			&& player.getInventory().getItem(9).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCerealbox2Mesh()], false);
		}
		if (player.getInventory().getItem(9).getName() == Page.getPotatoChipName()
			&& player.getInventory().getItem(9).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPotatoChipMesh()], false);
		}
		if (player.getInventory().getItem(9).getName() == Page.getCokeName()
			&& player.getInventory().getItem(9).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCokeMesh()], false);
		}
		if (player.getInventory().getItem(9).getName() == Page.getCokeZeroName()
			&& player.getInventory().getItem(9).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCokeZeroMesh()], false);
		}
		if (player.getInventory().getItem(9).getName() == Page.getPepsiName()
			&& player.getInventory().getItem(9).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPepsiMesh()], false);
		}
		if (player.getInventory().getItem(9).getName() == Page.getMiloName()
			&& player.getInventory().getItem(9).getPaid() == false)
		{
			RenderMesh(meshList[Page.getMiloMesh()], false);
		}
		modelStack.PopMatrix();
	}

	if (Page.getItemsTaken10() == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-0.29, -0.95, 0);
		modelStack.Scale(0.07, 0.07, 0.07);
		if (player.getInventory().getItem(10).getName() == Page.getSardineName()
			&& player.getInventory().getItem(10).getPaid() == false)
		{
			RenderMesh(meshList[Page.getSardineMesh()], false);
		}
		if (player.getInventory().getItem(10).getName() == Page.getPncName()
			&& player.getInventory().getItem(10).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPncMesh()], false);
		}
		if (player.getInventory().getItem(10).getName() == Page.getBakedBeanName()
			&& player.getInventory().getItem(10).getPaid() == false)
		{
			RenderMesh(meshList[Page.getBakedBeanMesh()], false);
		}
		if (player.getInventory().getItem(10).getName() == Page.getPizzaboxName()
			&& player.getInventory().getItem(10).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPizzaboxMesh()], false);
		}
		if (player.getInventory().getItem(10).getName() == Page.getCerealbox1Name()
			&& player.getInventory().getItem(10).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCerealbox1Mesh()], false);
		}
		if (player.getInventory().getItem(10).getName() == Page.getCerealbox2Name()
			&& player.getInventory().getItem(10).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCerealbox2Mesh()], false);
		}
		if (player.getInventory().getItem(10).getName() == Page.getPotatoChipName()
			&& player.getInventory().getItem(10).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPotatoChipMesh()], false);
		}
		if (player.getInventory().getItem(10).getName() == Page.getCokeName()
			&& player.getInventory().getItem(10).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCokeMesh()], false);
		}
		if (player.getInventory().getItem(10).getName() == Page.getCokeZeroName()
			&& player.getInventory().getItem(10).getPaid() == false)
		{
			RenderMesh(meshList[Page.getCokeZeroMesh()], false);
		}
		if (player.getInventory().getItem(10).getName() == Page.getPepsiName()
			&& player.getInventory().getItem(10).getPaid() == false)
		{
			RenderMesh(meshList[Page.getPepsiMesh()], false);
		}
		if (player.getInventory().getItem(10).getName() == Page.getMiloName()
			&& player.getInventory().getItem(10).getPaid() == false)
		{
			RenderMesh(meshList[Page.getMiloMesh()], false);
		}
		modelStack.PopMatrix();
	}


	//=======Rendering paid sprites=======//
	if (Page.getItemsTaken1() == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-0.91, -0.95, 0);
		modelStack.Scale(0.07, 0.07, 0.07);
		if (player.getInventory().getItem(1).getName() == Page.getSardineName() 
			&& player.getInventory().getItem(1).getPaid() == true)
		{
			RenderMesh(meshList[UI_SARDINE_CAN_PAID], false);
		}
		if (player.getInventory().getItem(1).getName() == Page.getPncName() 
			&& player.getInventory().getItem(1).getPaid() == true)
		{
			RenderMesh(meshList[UI_PEA_N_CARROTS_PAID], false);
		}
		if (player.getInventory().getItem(1).getName() == Page.getBakedBeanName() 
			&& player.getInventory().getItem(1).getPaid() == true)
		{
			RenderMesh(meshList[UI_BAKED_BEANS_CAN_PAID], false);
		}
		if (player.getInventory().getItem(1).getName() == Page.getPizzaboxName()
			&& player.getInventory().getItem(1).getPaid() == true)
		{
			RenderMesh(meshList[UI_PIZZABOX_PAID], false);
		}
		if (player.getInventory().getItem(1).getName() == Page.getCerealbox1Name()
			&& player.getInventory().getItem(1).getPaid() == true)
		{
			RenderMesh(meshList[UI_CEREALBOX1_PAID], false);
		}
		if (player.getInventory().getItem(1).getName() == Page.getCerealbox2Name()
			&& player.getInventory().getItem(1).getPaid() == true)
		{
			RenderMesh(meshList[UI_CEREALBOX2_PAID], false);
		}
		if (player.getInventory().getItem(1).getName() == Page.getPotatoChipName()
			&& player.getInventory().getItem(1).getPaid() == true)
		{
			RenderMesh(meshList[UI_POTATOCHIPS_PAID], false);
		}
		if (player.getInventory().getItem(1).getName() == Page.getCokeName()
			&& player.getInventory().getItem(1).getPaid() == true)
		{
			RenderMesh(meshList[UI_COKE_CAN_PAID], false);
		}
		if (player.getInventory().getItem(1).getName() == Page.getCokeZeroName()
			&& player.getInventory().getItem(1).getPaid() == true)
		{
			RenderMesh(meshList[UI_COKE_ZERO_CAN_PAID], false);
		}
		if (player.getInventory().getItem(1).getName() == Page.getPepsiName()
			&& player.getInventory().getItem(1).getPaid() == true)
		{
			RenderMesh(meshList[UI_PEPSI_CAN_PAID], false);
		}
		if (player.getInventory().getItem(1).getName() == Page.getMiloName()
			&& player.getInventory().getItem(1).getPaid() == true)
		{
			RenderMesh(meshList[UI_MILOCAN_PAID], false);
		}
		modelStack.PopMatrix();
	}

	if (Page.getItemsTaken2() == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-0.84, -0.95, 0);
		modelStack.Scale(0.07, 0.07, 0.07);
		if (player.getInventory().getItem(2).getName() == Page.getSardineName() 
			&& player.getInventory().getItem(2).getPaid() == true)
		{
			RenderMesh(meshList[UI_SARDINE_CAN_PAID], false);
		}
		if (player.getInventory().getItem(2).getName() == Page.getPncName()
			&& player.getInventory().getItem(2).getPaid() == true)
		{
			RenderMesh(meshList[UI_PEA_N_CARROTS_PAID], false);
		}
		if (player.getInventory().getItem(2).getName() == Page.getBakedBeanName()
			&& player.getInventory().getItem(2).getPaid() == true)
		{
			RenderMesh(meshList[UI_BAKED_BEANS_CAN_PAID], false);
		}
		if (player.getInventory().getItem(2).getName() == Page.getPizzaboxName()
			&& player.getInventory().getItem(2).getPaid() == true)
		{
			RenderMesh(meshList[UI_PIZZABOX_PAID], false);
		}
		if (player.getInventory().getItem(2).getName() == Page.getCerealbox1Name()
			&& player.getInventory().getItem(2).getPaid() == true)
		{
			RenderMesh(meshList[UI_CEREALBOX1_PAID], false);
		}
		if (player.getInventory().getItem(2).getName() == Page.getCerealbox2Name()
			&& player.getInventory().getItem(2).getPaid() == true)
		{
			RenderMesh(meshList[UI_CEREALBOX2_PAID], false);
		}
		if (player.getInventory().getItem(2).getName() == Page.getPotatoChipName()
			&& player.getInventory().getItem(2).getPaid() == true)
		{
			RenderMesh(meshList[UI_POTATOCHIPS_PAID], false);
		}
		if (player.getInventory().getItem(2).getName() == Page.getCokeName()
			&& player.getInventory().getItem(2).getPaid() == true)
		{
			RenderMesh(meshList[UI_COKE_CAN_PAID], false);
		}
		if (player.getInventory().getItem(2).getName() == Page.getCokeZeroName()
			&& player.getInventory().getItem(2).getPaid() == true)
		{
			RenderMesh(meshList[UI_COKE_ZERO_CAN_PAID], false);
		}
		if (player.getInventory().getItem(2).getName() == Page.getPepsiName()
			&& player.getInventory().getItem(2).getPaid() == true)
		{
			RenderMesh(meshList[UI_PEPSI_CAN_PAID], false);
		}
		if (player.getInventory().getItem(2).getName() == Page.getMiloName()
			&& player.getInventory().getItem(2).getPaid() == true)
		{
			RenderMesh(meshList[UI_MILOCAN_PAID], false);
		}
		modelStack.PopMatrix();
	}

	if (Page.getItemsTaken3() == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-0.77, -0.95, 0);
		modelStack.Scale(0.07, 0.07, 0.07);
		if (player.getInventory().getItem(3).getName() == Page.getSardineName()
			&& player.getInventory().getItem(3).getPaid() == true)
		{
			RenderMesh(meshList[UI_SARDINE_CAN_PAID], false);
		}
		if (player.getInventory().getItem(3).getName() == Page.getPncName()
			&& player.getInventory().getItem(3).getPaid() == true)
		{
			RenderMesh(meshList[UI_PEA_N_CARROTS_PAID], false);
		}
		if (player.getInventory().getItem(3).getName() == Page.getBakedBeanName()
			&& player.getInventory().getItem(3).getPaid() == true)
		{
			RenderMesh(meshList[UI_BAKED_BEANS_CAN_PAID], false);
		}
		if (player.getInventory().getItem(3).getName() == Page.getPizzaboxName()
			&& player.getInventory().getItem(3).getPaid() == true)
		{
			RenderMesh(meshList[UI_PIZZABOX_PAID], false);
		}
		if (player.getInventory().getItem(3).getName() == Page.getCerealbox1Name()
			&& player.getInventory().getItem(3).getPaid() == true)
		{
			RenderMesh(meshList[UI_CEREALBOX1_PAID], false);
		}
		if (player.getInventory().getItem(3).getName() == Page.getCerealbox2Name()
			&& player.getInventory().getItem(3).getPaid() == true)
		{
			RenderMesh(meshList[UI_CEREALBOX2_PAID], false);
		}
		if (player.getInventory().getItem(3).getName() == Page.getPotatoChipName()
			&& player.getInventory().getItem(3).getPaid() == true)
		{
			RenderMesh(meshList[UI_POTATOCHIPS_PAID], false);
		}
		if (player.getInventory().getItem(3).getName() == Page.getCokeName()
			&& player.getInventory().getItem(3).getPaid() == true)
		{
			RenderMesh(meshList[UI_COKE_CAN_PAID], false);
		}
		if (player.getInventory().getItem(3).getName() == Page.getCokeZeroName()
			&& player.getInventory().getItem(3).getPaid() == true)
		{
			RenderMesh(meshList[UI_COKE_ZERO_CAN_PAID], false);
		}
		if (player.getInventory().getItem(3).getName() == Page.getPepsiName()
			&& player.getInventory().getItem(3).getPaid() == true)
		{
			RenderMesh(meshList[UI_PEPSI_CAN_PAID], false);
		}
		if (player.getInventory().getItem(3).getName() == Page.getMiloName()
			&& player.getInventory().getItem(3).getPaid() == true)
		{
			RenderMesh(meshList[UI_MILOCAN_PAID], false);
		}
		modelStack.PopMatrix();
	}
	if (Page.getItemsTaken4() == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-0.70, -0.95, 0);
		modelStack.Scale(0.07, 0.07, 0.07);
		if (player.getInventory().getItem(4).getName() == Page.getSardineName()
			&& player.getInventory().getItem(4).getPaid() == true)
		{
			RenderMesh(meshList[UI_SARDINE_CAN_PAID], false);
		}
		if (player.getInventory().getItem(4).getName() == Page.getPncName()
			&& player.getInventory().getItem(4).getPaid() == true)
		{
			RenderMesh(meshList[UI_PEA_N_CARROTS_PAID], false);
		}
		if (player.getInventory().getItem(4).getName() == Page.getBakedBeanName()
			&& player.getInventory().getItem(4).getPaid() == true)
		{
			RenderMesh(meshList[UI_BAKED_BEANS_CAN_PAID], false);
		}
		if (player.getInventory().getItem(4).getName() == Page.getPizzaboxName()
			&& player.getInventory().getItem(4).getPaid() == true)
		{
			RenderMesh(meshList[UI_PIZZABOX_PAID], false);
		}
		if (player.getInventory().getItem(4).getName() == Page.getCerealbox1Name()
			&& player.getInventory().getItem(4).getPaid() == true)
		{
			RenderMesh(meshList[UI_CEREALBOX1_PAID], false);
		}
		if (player.getInventory().getItem(4).getName() == Page.getCerealbox2Name()
			&& player.getInventory().getItem(4).getPaid() == true)
		{
			RenderMesh(meshList[UI_CEREALBOX2_PAID], false);
		}
		if (player.getInventory().getItem(4).getName() == Page.getPotatoChipName()
			&& player.getInventory().getItem(4).getPaid() == true)
		{
			RenderMesh(meshList[UI_POTATOCHIPS_PAID], false);
		}
		if (player.getInventory().getItem(4).getName() == Page.getCokeName()
			&& player.getInventory().getItem(4).getPaid() == true)
		{
			RenderMesh(meshList[UI_COKE_CAN_PAID], false);
		}
		if (player.getInventory().getItem(4).getName() == Page.getCokeZeroName()
			&& player.getInventory().getItem(4).getPaid() == true)
		{
			RenderMesh(meshList[UI_COKE_ZERO_CAN_PAID], false);
		}
		if (player.getInventory().getItem(4).getName() == Page.getPepsiName()
			&& player.getInventory().getItem(4).getPaid() == true)
		{
			RenderMesh(meshList[UI_PEPSI_CAN_PAID], false);
		}
		if (player.getInventory().getItem(4).getName() == Page.getMiloName()
			&& player.getInventory().getItem(4).getPaid() == true)
		{
			RenderMesh(meshList[UI_MILOCAN_PAID], false);
		}
		modelStack.PopMatrix();
	}

	if (Page.getItemsTaken5() == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-0.63, -0.95, 0);
		modelStack.Scale(0.07, 0.07, 0.07);
		if (player.getInventory().getItem(5).getName() == Page.getSardineName()
			&& player.getInventory().getItem(5).getPaid() == true)
		{
			RenderMesh(meshList[UI_SARDINE_CAN_PAID], false);
		}
		if (player.getInventory().getItem(5).getName() == Page.getPncName()
			&& player.getInventory().getItem(5).getPaid() == true)
		{
			RenderMesh(meshList[UI_PEA_N_CARROTS_PAID], false);
		}
		if (player.getInventory().getItem(5).getName() == Page.getBakedBeanName()
			&& player.getInventory().getItem(5).getPaid() == true)
		{
			RenderMesh(meshList[UI_BAKED_BEANS_CAN_PAID], false);
		}
		if (player.getInventory().getItem(5).getName() == Page.getPizzaboxName()
			&& player.getInventory().getItem(5).getPaid() == true)
		{
			RenderMesh(meshList[UI_PIZZABOX_PAID], false);
		}
		if (player.getInventory().getItem(5).getName() == Page.getCerealbox1Name()
			&& player.getInventory().getItem(5).getPaid() == true)
		{
			RenderMesh(meshList[UI_CEREALBOX1_PAID], false);
		}
		if (player.getInventory().getItem(5).getName() == Page.getCerealbox2Name()
			&& player.getInventory().getItem(5).getPaid() == true)
		{
			RenderMesh(meshList[UI_CEREALBOX2_PAID], false);
		}
		if (player.getInventory().getItem(5).getName() == Page.getPotatoChipName()
			&& player.getInventory().getItem(5).getPaid() == true)
		{
			RenderMesh(meshList[UI_POTATOCHIPS_PAID], false);
		}
		if (player.getInventory().getItem(5).getName() == Page.getCokeName()
			&& player.getInventory().getItem(5).getPaid() == true)
		{
			RenderMesh(meshList[UI_COKE_CAN_PAID], false);
		}
		if (player.getInventory().getItem(5).getName() == Page.getCokeZeroName()
			&& player.getInventory().getItem(5).getPaid() == true)
		{
			RenderMesh(meshList[UI_COKE_ZERO_CAN_PAID], false);
		}
		if (player.getInventory().getItem(5).getName() == Page.getPepsiName()
			&& player.getInventory().getItem(5).getPaid() == true)
		{
			RenderMesh(meshList[UI_PEPSI_CAN_PAID], false);
		}
		if (player.getInventory().getItem(5).getName() == Page.getMiloName()
			&& player.getInventory().getItem(5).getPaid() == true)
		{
			RenderMesh(meshList[UI_MILOCAN_PAID], false);
		}
		modelStack.PopMatrix();
	}

	if (Page.getItemsTaken6() == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-0.56, -0.95, 0);
		modelStack.Scale(0.07, 0.07, 0.07);
		if (player.getInventory().getItem(6).getName() == Page.getSardineName()
			&& player.getInventory().getItem(6).getPaid() == true)
		{
			RenderMesh(meshList[UI_SARDINE_CAN_PAID], false);
		}
		if (player.getInventory().getItem(6).getName() == Page.getPncName()
			&& player.getInventory().getItem(6).getPaid() == true)
		{
			RenderMesh(meshList[UI_PEA_N_CARROTS_PAID], false);
		}
		if (player.getInventory().getItem(6).getName() == Page.getBakedBeanName()
			&& player.getInventory().getItem(6).getPaid() == true)
		{
			RenderMesh(meshList[UI_BAKED_BEANS_CAN_PAID], false);
		}
		if (player.getInventory().getItem(6).getName() == Page.getPizzaboxName()
			&& player.getInventory().getItem(6).getPaid() == true)
		{
			RenderMesh(meshList[UI_PIZZABOX_PAID], false);
		}
		if (player.getInventory().getItem(6).getName() == Page.getCerealbox1Name()
			&& player.getInventory().getItem(6).getPaid() == true)
		{
			RenderMesh(meshList[UI_CEREALBOX1_PAID], false);
		}
		if (player.getInventory().getItem(6).getName() == Page.getCerealbox2Name()
			&& player.getInventory().getItem(6).getPaid() == true)
		{
			RenderMesh(meshList[UI_CEREALBOX2_PAID], false);
		}
		if (player.getInventory().getItem(6).getName() == Page.getPotatoChipName()
			&& player.getInventory().getItem(6).getPaid() == true)
		{
			RenderMesh(meshList[UI_POTATOCHIPS_PAID], false);
		}
		if (player.getInventory().getItem(6).getName() == Page.getCokeName()
			&& player.getInventory().getItem(6).getPaid() == true)
		{
			RenderMesh(meshList[UI_COKE_CAN_PAID], false);
		}
		if (player.getInventory().getItem(6).getName() == Page.getCokeZeroName()
			&& player.getInventory().getItem(6).getPaid() == true)
		{
			RenderMesh(meshList[UI_COKE_ZERO_CAN_PAID], false);
		}
		if (player.getInventory().getItem(6).getName() == Page.getPepsiName()
			&& player.getInventory().getItem(6).getPaid() == true)
		{
			RenderMesh(meshList[UI_PEPSI_CAN_PAID], false);
		}
		if (player.getInventory().getItem(6).getName() == Page.getMiloName()
			&& player.getInventory().getItem(6).getPaid() == true)
		{
			RenderMesh(meshList[UI_MILOCAN_PAID], false);
		}
		modelStack.PopMatrix();
	}

	if (Page.getItemsTaken7() == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-0.495, -0.95, 0);
		modelStack.Scale(0.07, 0.07, 0.07);
		if (player.getInventory().getItem(7).getName() == Page.getSardineName()
			&& player.getInventory().getItem(7).getPaid() == true)
		{
			RenderMesh(meshList[UI_SARDINE_CAN_PAID], false);
		}
		if (player.getInventory().getItem(7).getName() == Page.getPncName()
			&& player.getInventory().getItem(7).getPaid() == true)
		{
			RenderMesh(meshList[UI_PEA_N_CARROTS_PAID], false);
		}
		if (player.getInventory().getItem(7).getName() == Page.getBakedBeanName()
			&& player.getInventory().getItem(7).getPaid() == true)
		{
			RenderMesh(meshList[UI_BAKED_BEANS_CAN_PAID], false);
		}
		if (player.getInventory().getItem(7).getName() == Page.getPizzaboxName()
			&& player.getInventory().getItem(7).getPaid() == true)
		{
			RenderMesh(meshList[UI_PIZZABOX_PAID], false);
		}
		if (player.getInventory().getItem(7).getName() == Page.getCerealbox1Name()
			&& player.getInventory().getItem(7).getPaid() == true)
		{
			RenderMesh(meshList[UI_CEREALBOX1_PAID], false);
		}
		if (player.getInventory().getItem(7).getName() == Page.getCerealbox2Name()
			&& player.getInventory().getItem(7).getPaid() == true)
		{
			RenderMesh(meshList[UI_CEREALBOX2_PAID], false);
		}
		if (player.getInventory().getItem(7).getName() == Page.getPotatoChipName()
			&& player.getInventory().getItem(7).getPaid() == true)
		{
			RenderMesh(meshList[UI_POTATOCHIPS_PAID], false);
		}
		if (player.getInventory().getItem(7).getName() == Page.getCokeName()
			&& player.getInventory().getItem(7).getPaid() == true)
		{
			RenderMesh(meshList[UI_COKE_CAN_PAID], false);
		}
		if (player.getInventory().getItem(7).getName() == Page.getCokeZeroName()
			&& player.getInventory().getItem(7).getPaid() == true)
		{
			RenderMesh(meshList[UI_COKE_ZERO_CAN_PAID], false);
		}
		if (player.getInventory().getItem(7).getName() == Page.getPepsiName()
			&& player.getInventory().getItem(7).getPaid() == true)
		{
			RenderMesh(meshList[UI_PEPSI_CAN_PAID], false);
		}
		if (player.getInventory().getItem(7).getName() == Page.getMiloName()
			&& player.getInventory().getItem(7).getPaid() == true)
		{
			RenderMesh(meshList[UI_MILOCAN_PAID], false);
		}
		modelStack.PopMatrix();
	}

	if (Page.getItemsTaken8() == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-0.425, -0.95, 0);
		modelStack.Scale(0.07, 0.07, 0.07);
		if (player.getInventory().getItem(8).getName() == Page.getSardineName()
			&& player.getInventory().getItem(8).getPaid() == true)
		{
			RenderMesh(meshList[UI_SARDINE_CAN_PAID], false);
		}
		if (player.getInventory().getItem(8).getName() == Page.getPncName()
			&& player.getInventory().getItem(8).getPaid() == true)
		{
			RenderMesh(meshList[UI_PEA_N_CARROTS_PAID], false);
		}
		if (player.getInventory().getItem(8).getName() == Page.getBakedBeanName()
			&& player.getInventory().getItem(8).getPaid() == true)
		{
			RenderMesh(meshList[UI_BAKED_BEANS_CAN_PAID], false);
		}
		if (player.getInventory().getItem(8).getName() == Page.getPizzaboxName()
			&& player.getInventory().getItem(8).getPaid() == true)
		{
			RenderMesh(meshList[UI_PIZZABOX_PAID], false);
		}
		if (player.getInventory().getItem(8).getName() == Page.getCerealbox1Name()
			&& player.getInventory().getItem(8).getPaid() == true)
		{
			RenderMesh(meshList[UI_CEREALBOX1_PAID], false);
		}
		if (player.getInventory().getItem(8).getName() == Page.getCerealbox2Name()
			&& player.getInventory().getItem(8).getPaid() == true)
		{
			RenderMesh(meshList[UI_CEREALBOX2_PAID], false);
		}
		if (player.getInventory().getItem(8).getName() == Page.getPotatoChipName()
			&& player.getInventory().getItem(8).getPaid() == true)
		{
			RenderMesh(meshList[UI_POTATOCHIPS_PAID], false);
		}
		if (player.getInventory().getItem(8).getName() == Page.getCokeName()
			&& player.getInventory().getItem(8).getPaid() == true)
		{
			RenderMesh(meshList[UI_COKE_CAN_PAID], false);

		}
		if (player.getInventory().getItem(8).getName() == Page.getCokeZeroName()
			&& player.getInventory().getItem(8).getPaid() == true)
		{
			RenderMesh(meshList[UI_COKE_ZERO_CAN_PAID], false);
		}
		if (player.getInventory().getItem(8).getName() == Page.getPepsiName()
			&& player.getInventory().getItem(8).getPaid() == true)
		{
			RenderMesh(meshList[UI_PEPSI_CAN_PAID], false);
		}
		if (player.getInventory().getItem(8).getName() == Page.getMiloName()
			&& player.getInventory().getItem(8).getPaid() == true)
		{
			RenderMesh(meshList[UI_MILOCAN_PAID], false);
		}
		modelStack.PopMatrix();
	}

	if (Page.getItemsTaken9() == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-0.36, -0.95, 0);
		modelStack.Scale(0.07, 0.07, 0.07);
		if (player.getInventory().getItem(9).getName() == Page.getSardineName()
			&& player.getInventory().getItem(9).getPaid() == true)
		{
			RenderMesh(meshList[UI_SARDINE_CAN_PAID], false);
		}
		if (player.getInventory().getItem(9).getName() == Page.getPncName()
			&& player.getInventory().getItem(9).getPaid() == true)
		{
			RenderMesh(meshList[UI_PEA_N_CARROTS_PAID], false);
		}
		if (player.getInventory().getItem(9).getName() == Page.getBakedBeanName()
			&& player.getInventory().getItem(9).getPaid() == true)
		{
			RenderMesh(meshList[UI_BAKED_BEANS_CAN_PAID], false);
		}
		if (player.getInventory().getItem(9).getName() == Page.getPizzaboxName()
			&& player.getInventory().getItem(9).getPaid() == true)
		{
			RenderMesh(meshList[UI_PIZZABOX_PAID], false);
		}
		if (player.getInventory().getItem(9).getName() == Page.getCerealbox1Name()
			&& player.getInventory().getItem(9).getPaid() == true)
		{
			RenderMesh(meshList[UI_CEREALBOX1_PAID], false);
		}
		if (player.getInventory().getItem(9).getName() == Page.getCerealbox2Name()
			&& player.getInventory().getItem(9).getPaid() == true)
		{
			RenderMesh(meshList[UI_CEREALBOX2_PAID], false);
		}
		if (player.getInventory().getItem(9).getName() == Page.getPotatoChipName()
			&& player.getInventory().getItem(9).getPaid() == true)
		{
			RenderMesh(meshList[UI_POTATOCHIPS_PAID], false);
		}
		if (player.getInventory().getItem(9).getName() == Page.getCokeName()
			&& player.getInventory().getItem(9).getPaid() == true)
		{
			RenderMesh(meshList[UI_COKE_CAN_PAID], false);
		}
		if (player.getInventory().getItem(9).getName() == Page.getCokeZeroName()
			&& player.getInventory().getItem(9).getPaid() == true)
		{
			RenderMesh(meshList[UI_COKE_ZERO_CAN_PAID], false);
		}
		if (player.getInventory().getItem(9).getName() == Page.getPepsiName()
			&& player.getInventory().getItem(9).getPaid() == true)
		{
			RenderMesh(meshList[UI_PEPSI_CAN_PAID], false);
		}
		if (player.getInventory().getItem(9).getName() == Page.getMiloName()
			&& player.getInventory().getItem(9).getPaid() == true)
		{
			RenderMesh(meshList[UI_MILOCAN_PAID], false);
		}
		modelStack.PopMatrix();
	}

	if (Page.getItemsTaken10() == true)
	{
		modelStack.PushMatrix();
		modelStack.Translate(-0.29, -0.95, 0);
		modelStack.Scale(0.07, 0.07, 0.07);
		if (player.getInventory().getItem(10).getName() == Page.getSardineName()
			&& player.getInventory().getItem(10).getPaid() == true)
		{
			RenderMesh(meshList[UI_SARDINE_CAN_PAID], false);
		}
		if (player.getInventory().getItem(10).getName() == Page.getPncName()
			&& player.getInventory().getItem(10).getPaid() == true)
		{
			RenderMesh(meshList[UI_PEA_N_CARROTS_PAID], false);
		}
		if (player.getInventory().getItem(10).getName() == Page.getBakedBeanName()
			&& player.getInventory().getItem(10).getPaid() == true)
		{
			RenderMesh(meshList[UI_BAKED_BEANS_CAN_PAID], false);
		}
		if (player.getInventory().getItem(10).getName() == Page.getPizzaboxName()
			&& player.getInventory().getItem(10).getPaid() == true)
		{
			RenderMesh(meshList[UI_PIZZABOX_PAID], false);
		}
		if (player.getInventory().getItem(10).getName() == Page.getCerealbox1Name()
			&& player.getInventory().getItem(10).getPaid() == true)
		{
			RenderMesh(meshList[UI_CEREALBOX1_PAID], false);
		}
		if (player.getInventory().getItem(10).getName() == Page.getCerealbox2Name()
			&& player.getInventory().getItem(10).getPaid() == true)
		{
			RenderMesh(meshList[UI_CEREALBOX2_PAID], false);
		}
		if (player.getInventory().getItem(10).getName() == Page.getPotatoChipName()
			&& player.getInventory().getItem(10).getPaid() == true)
		{
			RenderMesh(meshList[UI_POTATOCHIPS_PAID], false);
		}
		if (player.getInventory().getItem(10).getName() == Page.getCokeName()
			&& player.getInventory().getItem(10).getPaid() == true)
		{
			RenderMesh(meshList[UI_COKE_CAN_PAID], false);
		}
		if (player.getInventory().getItem(10).getName() == Page.getCokeZeroName()
			&& player.getInventory().getItem(10).getPaid() == true)
		{
			RenderMesh(meshList[UI_COKE_ZERO_CAN_PAID], false);
		}
		if (player.getInventory().getItem(10).getName() == Page.getPepsiName()
			&& player.getInventory().getItem(10).getPaid() == true)
		{
			RenderMesh(meshList[UI_PEPSI_CAN_PAID], false);
		}
		if (player.getInventory().getItem(10).getName() == Page.getMiloName()
			&& player.getInventory().getItem(10).getPaid() == true)
		{
			RenderMesh(meshList[UI_MILOCAN_PAID], false);
		}
		modelStack.PopMatrix();
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}

void StudioProject::RenderMenuOnScreen(Mesh* mesh, Color color, float size, float x, float y)
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

	if (menu.getShowMenuStatus() == true ||
		menu.getShowMenuStatus() == false && Guard1.getCatchPlayerState() == true ||
		menu.getShowMenuStatus() == false && Guard2.getCatchPlayerState() == true ||
		winState == true)
	{
		modelStack.PushMatrix();
		modelStack.Scale(120, 120, 120);
		modelStack.Translate(0.2, 0, 0);
		RenderMesh(meshList[menu.getBackgroundMesh()], false);
		modelStack.PopMatrix();
		if (winState == true)
		{
			modelStack.PushMatrix();
			modelStack.Scale(50, 50, 0);
			modelStack.Translate(0.78, 0.7, 0);
			RenderMesh(meshList[menu.getWinMesh()], false);
			modelStack.PopMatrix();
			RenderTextOnScreen(meshList[GEO_TEXT], "Press R to go back to menu", Color(1,1,1), 3, 1, 1);
		}
	}

	if (menu.getShowMenuStatus() == true && menu.getShowContorlStatus() == false)
	{
		modelStack.PushMatrix();
		modelStack.Scale(3, 3, 3);
		if (menu.getPointToGame() == true && menu.getPointToExit() == false && menu.getPointToContorl() == false) //Play Game
		{
			modelStack.Translate(7.8, 11.7, 0);//11.7 for PLay Game 9.7 for exit
		}
		else if (menu.getPointToGame() == false && menu.getPointToExit() == false && menu.getPointToContorl() == true)//Contorl
		{
			modelStack.Translate(7.8, 9.7, 0);
		}
		else if (menu.getPointToGame() == false && menu.getPointToExit() == true && menu.getPointToContorl() == false)//End Game
		{
			modelStack.Translate(7.8, 7.6, 0);
		}
		RenderMesh(meshList[menu.getArrowMesh()], false);
		modelStack.PopMatrix();

		modelStack.PushMatrix();
		modelStack.Scale(25, 25, 0);
		modelStack.Translate(1.5, 1.4, 0);
		//=============================When pointing at Play game render red================//
		if (menu.getPointToGame() == true && menu.getPointToExit() == false && menu.getPointToContorl() == false)
		{
			RenderMesh(meshList[menu.getStartGameTrueMesh()], false);
		}//=============================When not point at Play game render white================//
		else if (menu.getPointToGame() == false && menu.getPointToExit() == true && menu.getPointToContorl() == false ||
			menu.getPointToGame() == false && menu.getPointToExit() == false && menu.getPointToContorl() == true)
		{
			RenderMesh(meshList[menu.getStartGameFalseMesh()], false);
		}
		modelStack.PopMatrix();


		modelStack.PushMatrix();
		modelStack.Scale(20, 20, 0);
		modelStack.Translate(1.86, 1.45, 0);
		//=============================When pointing at contorl render red================//
		if (menu.getPointToGame() == false && menu.getPointToExit() == false && menu.getPointToContorl() == true)
		{
			RenderMesh(meshList[menu.getControlTrueMesh()], false);
		}//=============================When not pointing at contorl render white================//
		else if (menu.getPointToGame() == false && menu.getPointToExit() == true && menu.getPointToContorl() == false ||
			menu.getPointToGame() == true && menu.getPointToExit() == false && menu.getPointToContorl() == false)
		{
			RenderMesh(meshList[menu.getControlFalseMesh()], false);
		}
		modelStack.PopMatrix();


		modelStack.PushMatrix();
		modelStack.Scale(25, 25, 0);
		modelStack.Translate(1.5, 0.9, 0);
		//=============================When pointing at exit render red================//
		if (menu.getPointToGame() == false && menu.getPointToExit() == true && menu.getPointToContorl() == false)
		{
			RenderMesh(meshList[menu.getEndGameTrueMesh()], false);
		}//=============================When not pointing at exit render white================//
		else if (menu.getPointToGame() == false && menu.getPointToExit() == false && menu.getPointToContorl() == true ||
			menu.getPointToGame() == true && menu.getPointToExit() == false && menu.getPointToContorl() == false)
		{
			RenderMesh(meshList[menu.getEndGameFalseMesh()], false);
		}
		modelStack.PopMatrix();
	}

	if (menu.getShowContorlStatus() == true)
	{
		modelStack.PushMatrix();
		modelStack.Scale(70, 70, 0);
		modelStack.Translate(0.6, 0.4, 0);
		RenderMesh(meshList[menu.getControlMesh()], false);
		modelStack.PopMatrix();
		RenderTextOnScreen(meshList[GEO_TEXT], "Press R to go back to menu", Color(1,1,1), 3, 1, 1);
	}

	if (Guard1.getCatchPlayerState() == true && menu.getShowMenuStatus() == false ||
		Guard2.getCatchPlayerState() == true && menu.getShowMenuStatus() == false)
	{
		modelStack.PushMatrix();
		modelStack.Scale(50, 50, 0);
		modelStack.Translate(0.78, 0.7, 0);
		RenderMesh(meshList[menu.getGameOverMesh()], false);
		modelStack.PopMatrix();

		RenderTextOnScreen(meshList[GEO_TEXT], "Press R to go back to menu", Color(1,1,1), 3, 1, 1);
	}

	glBindTexture(GL_TEXTURE_2D, 0);
	glUniform1i(m_parameters[U_TEXT_ENABLED], 0);
	projectionStack.PopMatrix();
	viewStack.PopMatrix();
	modelStack.PopMatrix();
	glEnable(GL_DEPTH_TEST);
}
/******************************************************************************/
/*!
\brief
Renders Text on screen

\param	mesh - address for different meshes
\param	text - text to be rendered
\param	color - color of text
\param	size - size of text
\param	x - x coordinate of image on screen
\param	y - y coordinate of image on screen
*/
/******************************************************************************/
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
/******************************************************************************/
/*!
\brief
Cleans up the necessary variables
*/
/******************************************************************************/
void StudioProject::Exit()
{
	engine->drop();
	// Cleanup here
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if(meshList[i] != NULL)
			delete meshList[i];
	}
	glDeleteVertexArrays(1, &m_vertexArrayID);
	glDeleteProgram(m_programID);
}
