/******************************************************************************/
/*!
\file	Item.h
\author Princeton Chew
\par	email: 141991A@mymail.nyp.edu.sg
\brief
Item Class
*/
/******************************************************************************/
#include "Item.h"

/******************************************************************************/
/*!
\brief
Default constructor for class
*/
/******************************************************************************/
CItem::CItem(void)
{
	name = "undefined";
	price = 0.0f;
	isRender = true;
	meshPtr = (NULL);
	objType = 0;
	TRS.SetToIdentity();
	isPaid = false;
}

/******************************************************************************/
/*!
\brief
Default destructor for class
*/
/******************************************************************************/
CItem::~CItem(void)
{
}

/******************************************************************************/
/*!
\brief
Sets all item data

\param a - String name of item
\param b - Float price of item
\param d - Bool render status of item
\param e - Pointer mesh of item
\param f - Int object type of item
\param g - Mtx44 position of item
\param h - Bool paid status of item
*/
/******************************************************************************/
void CItem::SetData(string a, float b, bool d, Mesh* e,int f,Mtx44 g,bool h)
{
	name = a;
	
	price = b;
	
	isRender = d;

	meshPtr = e;

	objType = f;

	TRS = g;
	
	isPaid = h;
}
/******************************************************************************/
/*!
\brief
Set the paid status of item

\param b - Bool status of paid 
*/
/******************************************************************************/
void CItem::setPaid(bool b)
{
	isPaid = b;
}
/******************************************************************************/
/*!
\brief
Set the price status of item

\param a - float price of item
*/
/******************************************************************************/
void CItem::setPrice(float a)
{
	price = a;
}
/******************************************************************************/
/*!
\brief
Get the name of item 

\return String storing name of item
*/
/******************************************************************************/
string CItem::getName(void)
{
	return name;
}
/******************************************************************************/
/*!
\brief
Get the price of item 

\return Float storing price of item
*/
/******************************************************************************/
float CItem::getPrice(void)
{
	return price;
}
/******************************************************************************/
/*!
\brief
Get the render status of item 

\return Bool storing render status of item
*/
/******************************************************************************/
bool CItem::getRender(void)
{
	return isRender;
}
/******************************************************************************/
/*!
\brief
Get the Mesh of item 

\return Pointer storing mesh of item
*/
/******************************************************************************/
Mesh* CItem::getMesh(void)
{
	return meshPtr;
}
/******************************************************************************/
/*!
\brief
Get the Object type of item 

\return Int storing object type of item
*/
/******************************************************************************/
int CItem::getobjType(void)
{
	return objType;
}
/******************************************************************************/
/*!
\brief
Sets render status of item

\param a - Bool of render status of item
*/
/******************************************************************************/
void CItem::setRender(bool a)
{
	isRender = a;
}
/******************************************************************************/
/*!
\brief
Sets Translation, rotation, scale of item

\return Mtx44 storing translation,rotation,scale of item
*/
/******************************************************************************/
Mtx44 CItem::getTRS(void)
{
	return TRS;
}
/******************************************************************************/
/*!
\brief
Get paid status of item

\return Bool storing paid status of item
*/
/******************************************************************************/
bool CItem::getPaid(void)
{
	return isPaid;
}
