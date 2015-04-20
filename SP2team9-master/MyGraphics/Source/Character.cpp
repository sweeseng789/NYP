/******************************************************************************/
/*!
\file	Character.cpp
\author Princeton Chew
\par	email: 141991A@mymail.nyp.edu.sg
\brief
Character Class
*/
/******************************************************************************/

#include "Character.h"

/******************************************************************************/
/*!
\brief
Default constructor for class
*/
/******************************************************************************/
CCharacter::CCharacter(void)
{
	HeadPtr = (NULL);
	TorsoPtr = (NULL);
	leftHandPtr = (NULL);
	rightHandPtr = (NULL);
	leftLegPtr = (NULL);
	rightLegPtr = (NULL);

	position.Set(0.0f,0.0f,0.0f);
}

/******************************************************************************/
/*!
\brief
Default destructor for class
*/
/******************************************************************************/
CCharacter::~CCharacter(void)
{
}

/******************************************************************************/
/*!
\brief
Set meshes for character

\param head - mesh pointer of head of character
\param torso - mesh pointer of torso of character
\param Lhand - mesh pointer of left hand of character
\param Rhand - mesh pointer of right hand of character
\param Lleg - mesh pointer of left leg of character
\param Rleg - mesh pointer of right leg of character
\param pos - Vector3 position of character
*/
/******************************************************************************/
void CCharacter::setCharacter(Mesh* head, Mesh* torso, Mesh* Lhand, Mesh* Rhand, Mesh* Lleg, Mesh* Rleg,Vector3 pos)
{
	HeadPtr = head;
	TorsoPtr = torso;
	leftHandPtr = Lhand;
	rightHandPtr = Rhand;
	leftLegPtr = Lleg;
	rightLegPtr = Rleg;
	position = pos;
}
/******************************************************************************/
/*!
\brief
Set character's position

\param x - x coordinate position of character
\param y - y coordinate position of character
\param z - z coordinate position of character
*/
/******************************************************************************/
void CCharacter::setPosition(float x,float y,float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

/******************************************************************************/
/*!
\brief
Returns character's head mesh

\return Pointer to mesh storing mesh of character's head
*/
/******************************************************************************/
Mesh* CCharacter::getHead(void)
{
	return HeadPtr;
}

/******************************************************************************/
/*!
\brief
Returns character's torso mesh

\return Pointer to mesh storing mesh of character's torso
*/
/******************************************************************************/
Mesh* CCharacter::getTorso(void)
{
	return TorsoPtr;
}

/******************************************************************************/
/*!
\brief
Returns character's left hand mesh

\return Pointer to mesh storing mesh of character's left hand
*/
/******************************************************************************/
Mesh* CCharacter::getLHand(void)
{
	return leftHandPtr;
}

/******************************************************************************/
/*!
\brief
Returns character's right hand mesh

\return Pointer to mesh storing mesh of character's right hand
*/
/******************************************************************************/
Mesh* CCharacter::getRHand(void)
{
	return rightHandPtr;
}

/******************************************************************************/
/*!
\brief
Returns character's left leg mesh

\return Pointer to mesh storing mesh of character's left leg
*/
/******************************************************************************/
Mesh* CCharacter::getLLeg(void)
{
	return leftLegPtr;
}
/******************************************************************************/
/*!
\brief
Returns character's right leg mesh

\return Pointer to mesh storing mesh of character's right leg
*/
/******************************************************************************/
Mesh* CCharacter::getRLeg(void)
{
	return rightLegPtr;
}

/******************************************************************************/
/*!
\brief
Returns character's position

\return Vector3 storing character's position
*/
/******************************************************************************/
Vector3 CCharacter::getPosition(void)
{
	return position;
}