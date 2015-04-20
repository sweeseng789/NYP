/******************************************************************************/
/*!
\file	Character.h
\author Princeton Chew
\par	email: 141991A@mymail.nyp.edu.sg
\brief
Character Class
*/
/******************************************************************************/
#pragma once
#include "Vector3.h"
#include "Mesh.h"

/******************************************************************************/
/*!
	Class CCharacter
\brief
Defines the variables and functions required for the characters

*/
/******************************************************************************/
class CCharacter
{
public:
	CCharacter(void);	//constructor
	~CCharacter(void);	//destructor

	void setCharacter(Mesh* head, Mesh* torso, Mesh* Lhand, Mesh* Rhand, Mesh* Lleg, Mesh* Rleg,Vector3 pos);	//Set all character's data
	void setPosition(float x, float y, float z); // Set character's position

	Mesh* getHead(void);
	Mesh* getTorso(void);
	Mesh* getLHand(void);
	Mesh* getRHand(void);
	Mesh* getLLeg(void);
	Mesh* getRLeg(void);
	Vector3 getPosition(void);

	Mesh* HeadPtr;
	Mesh* TorsoPtr;
	Mesh* leftHandPtr;
	Mesh* rightHandPtr;
	Mesh* leftLegPtr;
	Mesh* rightLegPtr;

	Vector3 position;
};

