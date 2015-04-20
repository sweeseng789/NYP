/******************************************************************************/
/*!
\file	Item.h
\author Princeton Chew
\par	email: 141991A@mymail.nyp.edu.sg
\brief
Item Class
*/
/******************************************************************************/
#pragma once
#include <string>
#include "Vector3.h"
#include "Mesh.h"
#include "Mtx44.h"

using std::string;

/******************************************************************************/
/*!
	Class CItem
\brief
Defines the variables and functions required for the Items

*/
/******************************************************************************/
class CItem
{
public:
	CItem(void);	//constructor
	~CItem(void);	//destructor

	void SetData(string a, float b, bool d, Mesh* e,int f,Mtx44 g,bool h);	//Set all data
	
	void setRender(bool a);	//Set render status
	void setPaid(bool b);	//Set paid status
	void setPrice(float a);	//Set price
	string getName(void);	//Set name
	float getPrice(void);	//Get price
	bool getRender(void);	//Get render status
	Mesh* getMesh(void);	//Get Mesh
	int getobjType(void);	//Get object type
	Mtx44 getTRS(void);	//Get TRS
	bool getPaid(void);	//Get paid status 

private:
	Mesh* meshPtr;
	string name;
	float price;
	bool isRender;
	int objType;
	Mtx44 TRS;
	bool isPaid;
};

