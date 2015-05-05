/******************************************************************************/
/*!
\file	Inventory.cpp
\author Princeton Chew
\par	email: 141991A@mymail.nyp.edu.sg
\brief
Inventory Class
*/
/******************************************************************************/
#include "Inventory.h"

/******************************************************************************/
/*!
\brief
Default constructor for class
*/
/******************************************************************************/
CInventory::CInventory(void)
{
}

/******************************************************************************/
/*!
\brief
Default destructor for class
*/
/******************************************************************************/
CInventory::~CInventory(void)
{
}

/******************************************************************************/
/*!
\brief
Add Item into inventory

\param temp - CItem to be added into inventory

\return Bool if item is added or not
*/
/******************************************************************************/
bool CInventory::AddItem(CItem temp)
{
	if(Inventory.size() < 10)
	{
		Inventory.push_back(temp);
		return true;
	}
	else
	{
		return false;
	}
}

/******************************************************************************/
/*!
\brief
Get Item from inventory

\param pos - Position of item in inventory vector

\return CItem of item at that position in vector
*/
/******************************************************************************/
CItem CInventory::getItem(int pos)
{
	pos = pos - 1;
	if(pos < Inventory.size())
	{
		return Inventory[pos];
	}
}

/******************************************************************************/
/*!
\brief
Get Number of items in inventory

\return Int of number of items
*/
/******************************************************************************/
int CInventory::getNoOfItems(void)
{
	return Inventory.size();
}

/******************************************************************************/
/*!
\brief
Remove item from inventory based on position

\param pos - position of item in vector
*/
/******************************************************************************/
void CInventory::removeItem(int pos)
{
	pos = pos - 1;
	if( pos <= Inventory.size())
	{
		Inventory.erase(Inventory.begin()+pos);
	}
}

/******************************************************************************/
/*!
\brief
Remove item from inventory based on item passed in

\param temp - CItem

\return Bool if item removed or not
*/
/******************************************************************************/
bool CInventory::removeItem(CItem temp)
{
	for(int i = 0; i < Inventory.size(); ++i)
	{
		if(Inventory[i].getobjType() == temp.getobjType() && Inventory[i].getPaid() == temp.getPaid())
		{
			Inventory.erase(Inventory.begin()+i);
			return true;
		}
	}
	return false;
}

/******************************************************************************/
/*!
\brief
Remove all items from inventory

*/
/******************************************************************************/
void CInventory::DeleteAll(void)
{
	Inventory.clear();
}