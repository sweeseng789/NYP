/******************************************************************************/
/*!
\file	StudioProject.h
\author Ong Swee Seng, Lazarus Tan , Princeton Chew , Adela Quek
\par	email: 142128G@mymail.nyp.edu.sg
\brief
Structs
*/
/******************************************************************************/
#ifndef _StudioProject_H
#define _StudioProject_H

#include "Scene.h"
#include "Mtx44.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Utility.h"
#include "Camera3.h"
#include <string>
#include <sstream>
#include "timer.h"
#include  <ctime>
#include <iomanip>
#include <math.h>

#include "Item.h"
#include "Inventory.h"
#include "Character.h"
#include "Guard.h"
#include "Player.h"
#include "Customer.h"
#include "Cashier.h"
#include "CItemInventory.h"
#include "Ai.h"
#include "MenuClass.h"
//Sound Engine
#include <irrKlang.h>

using namespace irrklang;
using std::string;

/******************************************************************************/
/*!
	Struct hitBox:
\brief
Define the Vector3 max and min of the hit box of the object
*/
/******************************************************************************/
struct hitBox
{
	Vector3 max;
	Vector3 min;

	void SetBox(Vector3 a, Vector3 b)
	{
		max = a; 
		min = b;
	}
};

/******************************************************************************/
/*!
	Class StudioProject
\brief
Defines the variables and functions required for the Scene

*/
/******************************************************************************/
class StudioProject: public Scene
{
private:
 //! UNIFORM_TYPE.
/*! Defines variables of uniform_type */
	enum UNIFORM_TYPE
	{
		U_MVP = 0,
		U_MODELVIEW,
		U_MODELVIEW_INVERSE_TRANSPOSE,
		U_MATERIAL_AMBIENT,
		U_MATERIAL_DIFFUSE,
		U_MATERIAL_SPECULAR,
		U_MATERIAL_SHININESS,
		U_LIGHTENABLED,
		U_NUMLIGHTS,

		//Light 1
		U_LIGHT0_POSITION,
		U_LIGHT0_COLOR,
		U_LIGHT0_POWER,
		U_LIGHT0_KC,
		U_LIGHT0_KL,
		U_LIGHT0_KQ,
		U_LIGHT0_TYPE,
		U_LIGHT0_SPOTDIRECTION,
		U_LIGHT0_COSCUTOFF,
		U_LIGHT0_COSINNER,
		U_LIGHT0_EXPONENT,

		//Light2
		U_LIGHT1_POSITION,
		U_LIGHT1_COLOR,
		U_LIGHT1_POWER,
		U_LIGHT1_KC,
		U_LIGHT1_KL,
		U_LIGHT1_KQ,
		U_LIGHT1_TYPE,
		U_LIGHT1_SPOTDIRECTION,
		U_LIGHT1_COSCUTOFF,
		U_LIGHT1_COSINNER,
		U_LIGHT1_EXPONENT,

		//Light 3
		U_LIGHT2_POSITION,
		U_LIGHT2_COLOR,
		U_LIGHT2_POWER,
		U_LIGHT2_KC,
		U_LIGHT2_KL,
		U_LIGHT2_KQ,
		U_LIGHT2_TYPE,
		U_LIGHT2_SPOTDIRECTION,
		U_LIGHT2_COSCUTOFF,
		U_LIGHT2_COSINNER,
		U_LIGHT2_EXPONENT,

		//Light 4
		U_LIGHT3_POSITION,
		U_LIGHT3_COLOR,
		U_LIGHT3_POWER,
		U_LIGHT3_KC,
		U_LIGHT3_KL,
		U_LIGHT3_KQ,
		U_LIGHT3_TYPE,
		U_LIGHT3_SPOTDIRECTION,
		U_LIGHT3_COSCUTOFF,
		U_LIGHT3_COSINNER,
		U_LIGHT3_EXPONENT,

		//Light 5
		U_LIGHT4_POSITION,
		U_LIGHT4_COLOR,
		U_LIGHT4_POWER,
		U_LIGHT4_KC,
		U_LIGHT4_KL,
		U_LIGHT4_KQ,
		U_LIGHT4_TYPE,
		U_LIGHT4_SPOTDIRECTION,
		U_LIGHT4_COSCUTOFF,
		U_LIGHT4_COSINNER,
		U_LIGHT4_EXPONENT,

		//Light 6
		U_LIGHT5_POSITION,
		U_LIGHT5_COLOR,
		U_LIGHT5_POWER,
		U_LIGHT5_KC,
		U_LIGHT5_KL,
		U_LIGHT5_KQ,
		U_LIGHT5_TYPE,
		U_LIGHT5_SPOTDIRECTION,
		U_LIGHT5_COSCUTOFF,
		U_LIGHT5_COSINNER,
		U_LIGHT5_EXPONENT,

		//Lights 7
		U_LIGHT6_POSITION,
		U_LIGHT6_COLOR,
		U_LIGHT6_POWER,
		U_LIGHT6_KC,
		U_LIGHT6_KL,
		U_LIGHT6_KQ,
		U_LIGHT6_TYPE,
		U_LIGHT6_SPOTDIRECTION,
		U_LIGHT6_COSCUTOFF,
		U_LIGHT6_COSINNER,
		U_LIGHT6_EXPONENT,

		//Lights 7
		U_LIGHT7_POSITION,
		U_LIGHT7_COLOR,
		U_LIGHT7_POWER,
		U_LIGHT7_KC,
		U_LIGHT7_KL,
		U_LIGHT7_KQ,
		U_LIGHT7_TYPE,
		U_LIGHT7_SPOTDIRECTION,
		U_LIGHT7_COSCUTOFF,
		U_LIGHT7_COSINNER,
		U_LIGHT7_EXPONENT,

		//add these enum in UNIFORM_TYPE before U_TOTAL
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,

		//Text
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};
 //! GEOMETRY_TYPE.
/*! Defines the different geometries */
	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_LIGHTBALL,
		GEO_LIGHTBALL2,
		GEO_LIGHTBALL3,
		GEO_LIGHTBALL4,
		GEO_LIGHTBALL5,
		GEO_LIGHTBALL6,
		GEO_LIGHTBALL7,
		GEO_LIGHTBALL8,
		GEO_CUBE,
		GEO_CYLINDER,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_FLOOR,
		//==Place New Geometry variable names here==//
		GEO_TEXT,
		GEO_FRONTSKY,	//Front skybox
		GEO_LEFTSKY,	//Left skybox
		GEO_RIGHTSKY,	//Right skybox
		GEO_BACKSKY,	//Back skybox
		GEO_SKY,        //Top of skybox
		GEO_BOTTOMSKY,  //bottom of skybox

		GEO_ROAD,

		GEO_MARKET,
		GEO_CASHIER,
		GEO_CASHREG,
		GEO_COLDFOODSHELF,
		GEO_SHELF,
		GEO_SHELF2,
		GEO_RAIL,
		GEO_DOORLEFT,
		GEO_DOORRIGHT,
		GEO_DUSTBIN,

		GEO_SARDINE_CAN, //food items
		GEO_PEA_N_CARROTS,
		GEO_BAKED_BEANS_CAN,
		GEO_COKE_CAN,
		GEO_DRINKCAN2,
		GEO_PEPSI_CAN,
		GEO_MILOCAN,
		GEO_CEREALBOX1,
		GEO_CEREALBOX2,
		GEO_PIZZABOX,
		GEO_POTATOCHIPS,

		GEO_MONEY,

		modelHead,			//Model Head
		modelTorso,			//Model Torso
		modelRightHand,		//Model Right Hand
		modelLeftHand,		//Model Left Hand
		modelLeftLeg,		//Model Left Leg
		modelRightLeg,		//Model Right Leg
		cashierHead,		//Cashier Head
		cashierTorso,		//Cashier Torso
		cashierRightHand,	//Cashier Right Hand
		cashierLeftHand,	//Cashier Left Hand
		cashierLeftLeg,		//Cashier Left Leg
		cashierRightLeg,	//Cashier Right Leg
		guardHead,			//Guard Head
		guardTorso,			//Guard Torso
		guardRightHand,		//Guard Right Hand
		guardLeftHand,		//Guard Left Hand
		guardLeftLeg,		//Guard Left Leg
		guardRightLeg,		//Guard Right Leg
		customerHead,		//Customer Head
		customerTorso,		//Customer Torso
		customerRightHand,	//Customer Right Hand
		customerLeftHand,	//Customer Left Hand
		customerLeftLeg,	//Customer Left Leg
		customerRightLeg,	//Customer Right Leg

		MENUBACKGROUND,
		MENUARROW,
		PlayGameTrue,
		PlayGameFalse,
		ExitTrue,
		ExitFalse,
		GameOverStateMesh,
		ContorlMesh,
		ControlTrue,
		ControlFalse,
		WinStateMesh,

		itemInventory,		//Item Inventory page
		cart,
		UI_SARDINE_CAN,
		UI_PEA_N_CARROTS,
		UI_BAKED_BEANS_CAN,
		UI_COKE_CAN,
		UI_COKE_ZERO_CAN,
		UI_PEPSI_CAN,
		UI_MILOCAN,
		UI_CEREALBOX1,
		UI_CEREALBOX2,
		UI_PIZZABOX,
		UI_POTATOCHIPS,
		UI_SARDINE_CAN_PAID,
		UI_PEA_N_CARROTS_PAID,
		UI_BAKED_BEANS_CAN_PAID,
		UI_PIZZABOX_PAID,
		UI_POTATOCHIPS_PAID,
		UI_COKE_CAN_PAID,
		UI_PEPSI_CAN_PAID,
		UI_COKE_ZERO_CAN_PAID,
		UI_CEREALBOX1_PAID,
		UI_CEREALBOX2_PAID,
		UI_MILOCAN_PAID,
		NUM_GEOMETRY,
	};
 //! States.
/*! Defines States of guard */
	enum States
	{
		S_IDLE,
		S_ALERT,
		S_MAX,
	};

	//Render
	void RenderSkybox();	//Renders Skybox 
	void RenderSupermarket();	//Renders Supermarket Layout
	void RenderModel();	//Renders Character Model
	void RenderCashier();	//Renders Cashier Model
	void RenderGuard();	//Renders Guard Model
	void RenderCustomer();	//Renders Customer Model
	void RenderItems();	//Renders Items in Supermarket
	void RenderPlayerInfo();	//Renders player's information on screen
	void RenderItemsInfo();	//Renders item's information on screen
	void RenderLevel1Lights();	//Renders lights in level1 of supermarket
	void RenderCheckOutItems(); //Renders Checkout Items
	void RenderTimeAttack(); //Renders everything related to Time Attack mini game
	void RenderGTP(); //Renders everything related to Guess The Price mini game
	void RenderThiefGame();	//Renders everything related to Theif mini game

	//Updates
	void updateTakingItem(); //Updates taking of items from shelf
	void updatePuttingBackItem();	//Updates putting back of items from shelf
	void updateCheckingOut();	//Updates checking out of items
	void updateTimeAttack();	//Updates everything related to Time Attack mini game
	void updateDustBin(); //Updates throwing of item
	void updateDoor(double dt); //Updates opening / closing of door
	void updateAI(double dt); //Updates all AI
	void updateGTP(); //Updates everything related to Guess The Price mini game
	void updateGTPprice(); //Updates Item prices for Guess The Price mini game
	void updateThiefGame();	//Updates everything related to Theif mini game

	void InitOrigPrice(); //Initializes item prices back to normal

	void ResetAll(double dt);

public:
	StudioProject();	//default constructor
	~StudioProject();	//default destructor

	virtual void Init();	//Initializes Scene
	virtual void Update(double dt);	//Updates Scene
	virtual void Render();	//Render Scene
	virtual void Exit();	//Cleaning up
	void InitMesh();	//Initializes Meshes to be used in scene
	void InitVariables();	//Initializes Variables to be used in scene
	void InitShaders();	//Initializes Shaders to be used in scene
	void InitCharacters();	//Initializes Characters to be used in scene

private:
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	double fps;
	string Framerate;
	string camerax;
	string cameray;
	string cameraz;
	string viewx;
	string viewy;
	string viewz;
	float worldsize;
	float roomsize;
	float roomheight;
	float moving;
	bool showInventory;
	bool throwMoney;
	float translateMoneyZ;
	float translateMoneyY;
	StopWatch Timer;
	bool winState;
	Menu menu;
	//==SoundEngine==//
	ISoundEngine* engine;
	ISound* Sound;

	//========MiniGame============//
	//==TimeAttack==//
	bool TimeAttack;
	bool generateList;
	vector<int> TAlist;
	int TAmatchedItems;
	int TAstartedOnce;
	bool isTAwon;
	float TAtime;
	string timeTA;
	float messageTime;

	//==Guess The Price==//
	bool GTP;
	bool isGTPwon;
	int NoOfItemsTaken;
	int GTPstartedOnce;
	string NumItem;
	float totalCost;
	string CostOfItems;

	//==Thief==//
	bool ThiefGame;
	bool isThiefwon;
	int NoOfItemsStolen;
	string NumStolen;

	//=========Character=========//
	bool movingModel;
	float rotateRightArms, rotateLeftArms, rotateLeftLeg, rotateRightLeg;
	float movingCharacterX, movingCharacterZ;
	Vector3 charPosition;
	float playerAngle;
	float angle;

	//========Booleans for objs ======//
	bool Pizza;
	bool Peas;
	bool Milo;
	bool Cereal1;
	bool Cereal2;
	bool Sardine;
	bool Beans;
	bool Lays;
	bool Coke;
	bool CokeZero;
	bool Pepsi;
	string Cash;
	float moveItem;
	bool checkoutCount[12];

	//===Used for Check out===//
	int peaCount;
	int PizzaCount;
	int MiloCount;
	int Cereal1Count;
	int Cereal2Count;
	int SardineCount;
	int BeansCount;
	int LaysCount;
	int CokeCount;
	int CokeZeroCount;
	int PepsiCount;
	vector<CItem> tempCheckOut;
	vector<CItem> paidItems;

	//===Player====//
	CPlayer player;

	//===NPC====//
	CCustomer TAnpc;
	CCustomer Theifnpc;
	CCustomer GTPnpc;

	//===Guard AI===//
	CGuard Guard1;
	CGuard Guard2;

	CCashier Cashier1;
	CCashier Cashier2;
	CCashier Cashier3;

	CCustomer Customer;

	//Security CameraOBJ[3];
	CItemInventory Page;
	Ai Passerby[4];

	//=========Items=========//
	CItem sardineCan,
		PnCCan, 
		BBCan,
		MiloCan, 
		CokeCan,
		PizzaBox,
		CokeZeroCan,
		PepsiCan,
		cerealBox1,
		cerealBox2,
		PotatoChip;

	vector<CItem> Container,
				Container2, 
				Container3,
				Container4, 
				Container5,
				Container6,
				Container7,
				Container8, 
				Container9,
				Container10,
				Container11,
				Container12,
				Container13;

	vector<hitBox> boxContainer, 
				boxContainer2,
				boxContainer3,
				boxContainer4,
				boxContainer5, 
				boxContainer6,
				boxContainer7,
				boxContainer8,
				boxContainer9,
				boxContainer10,
				boxContainer11,
				boxContainer12,
				boxContainer13,
				CashierBox;

	Camera3 camera;

	MS modelStack, viewStack, projectionStack;

	Light lights[8];
	CInventory in;
	void RenderMesh(Mesh *mesh, bool enableLight);


	//Text
	void RenderText(Mesh* mesh, std::string text, Color color);	//Function to render text in world space
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);	//Function to render Text on screen
	void RenderImageOnScreen(Mesh* mesh, Color color, float size, float x, float y);	//Function to render Image on screen
	void RenderMenuOnScreen(Mesh* mesh, Color color, float size, float x, float y);	//Function to render Menu on screen

};


#endif