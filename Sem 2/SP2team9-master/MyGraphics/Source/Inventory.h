/******************************************************************************/
/*!
\file	Inventory.h
\author Princeton Chew
\par	email: 141991A@mymail.nyp.edu.sg
\brief
Inventory Class
*/
/******************************************************************************/
#pragma once
#include <string>
#include <vector>
#include "Item.h"
#include <iostream>

using std::string;
using std::vector;

/******************************************************************************/
/*!
	Class CInventory
\brief
Defines the variables and functions required for the Inventory

*/
/******************************************************************************/
class CInventory
{
public:
	CInventory(void);	//Constructor
	~CInventory(void);	//Destructor

	bool AddItem(CItem temp);	//Add item to inventory
	CItem getItem(int pos);	//Get Item from inventory
	int getNoOfItems(void);	//Get number of items
	void DeleteAll(void);	//Delete inventory
	void removeItem(int pos);	//remove item from inventory based on position
	bool removeItem(CItem temp);	//remove item from inventory based on item passed in

private:
	vector<CItem> Inventory;	//Vector to store item
};

