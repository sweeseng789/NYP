#ifndef _Assignment3_H
#define _Assignment3_H

#include "Scene.h"
#include "Mtx44.h"
#include "Mesh.h"
#include "MatrixStack.h"
#include "Light.h"
#include "Utility.h"
#include "Camera3.h"
#include <string>
#include <sstream>

using std::string;

class Assignment3: public Scene
{
private:
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
		//add these enum in UNIFORM_TYPE before U_TOTAL
		U_COLOR_TEXTURE_ENABLED,
		U_COLOR_TEXTURE,

		//Text
		U_TEXT_ENABLED,
		U_TEXT_COLOR,
		U_TOTAL,
	};


	enum GEOMETRY_TYPE
	{
		GEO_AXES,
		GEO_QUAD,
		GEO_LIGHTBALL,
		GEO_LIGHTBALL2,
		GEO_CYLINDER,
		GEO_LEFT,
		GEO_RIGHT,
		GEO_TOP,
		GEO_BOTTOM,
		GEO_FRONT,
		GEO_BACK,
		GEO_RTOP,
		GEO_RBOTTOM,
		GEO_RFRONT,
		GEO_RBACK,
		GEO_RLEFT,
		GEO_RRIGHT,
		GEO_MARIO,
		GEO_MODEL1,
		//=================Room OBJ Related====================//
		GEO_SOFA,
		GEO_WARDROBE,
		GEO_TABLE,
		GEO_BORDER,
		GEO_DOOR,
		GEO_WORK_TABLE,
		GEO_BED,
		GEO_BED_SHELF,
		GEO_WARDROBE_PANEL,
		GEO_CHAIR,
		GEO_WINDOW,
		GEO_CEILING,
		GEO_TV,

		//==========META KNIGHT RELATED==================//
		GEO_HEAD,
		GEO_EYE,
		GEO_MASK,
		GEO_MASK2,
		GEO_FEET,
		GEO_TORUS,

		//Arms related
		GEO_HAND,
		GEO_SHOULDER,
		GEO_SHOULDERRING,

		//Wings Related
		GEO_WINGBASE,
		GEO_WINGSPHERE,
		GEO_WINGSPIKE,
		GEO_WINGSKELE,
		GEO_WINGCONTENT,

		//Sword related
		GEO_SWORDHANDLE,
		GEO_SWORDSPHERE,
		GEO_SWORDSPHERE2,
		GEO_SWORDHILT,
		GEO_SWORDBLADE,
		GEO_SHOCKWAVE,
		GEO_SHOCKWAVE2,

		//Mask related
		GEO_COVER,
		GEO_TOPPART,
		GEO_BTMPART,
		GEO_MASKSPIKE,
		GEO_TEXT,
		NUM_GEOMETRY,
	};

	void RenderSkybox();
	void RenderRoom();
	void RenderRoomContents();

public:
	Assignment3();
	~Assignment3();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	//===META KNIGHT RELATED===//
	void RenderMetaKnight();
	void RenderWings();
	void RenderArms();
	void RenderSword();

	//==Collision Checking==//

private:
	unsigned m_vertexArrayID;
	Mesh* meshList[NUM_GEOMETRY];
	unsigned m_programID;
	unsigned m_parameters[U_TOTAL];

	float rotateAngle;
	double fps;
	string Framerate;
	string camerax;
	string cameray;
	string cameraz;
	float worldsize;
	float roomsize;
	float roomheight;

	Vector3 skyBox;

	//===========META KNIGHT RELATED==================//
	//===========META KNIGHT RELATED==================//
	Mtx44 mkRotate;
	Vector3 mkPos;
	//Direction face
	float rotateDirection;
	
	//Feet rotation / translation
	float rotateRightFeet;
	float rotateLeftFeet;
	float translateRightFeet;
	float translateLeftFeet;
	float translateBody;

	//Arms rotation / translation
	float rotateRightArm;
	float rotateLeftArm;

	//Wings rotation / translation
	float rotateWings;
	float translateHead;

	//Sword Skill 
	float scaleShock;
	float translateShock;
	float scaleShock2;
	float translateShock2;
	
	//=====WARDROBE RELATED====//
	float translateThird;
	float translateSecond;
	float translateFirst;
	bool isOpen;
	bool isClose;

	//=====WINDOW RELATED====//
	float rotateWindowML;
	float rotateWindowM;
	float rotateWindowR;

	Camera3 camera;

	MS modelStack, viewStack, projectionStack;

	Light lights[2];

	void RenderMesh(Mesh *mesh, bool enableLight);

	//Text
	void RenderText(Mesh* mesh, std::string text, Color color);
	void RenderTextOnScreen(Mesh* mesh, std::string text, Color color, float size, float x, float y);

};

#endif