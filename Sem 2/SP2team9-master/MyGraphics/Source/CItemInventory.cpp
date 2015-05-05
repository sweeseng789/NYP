/******************************************************************************/
/*!
\file	Character.cpp
\author Princeton Chew
\par	email: 141991A@mymail.nyp.edu.sg
\brief
Character Class
*/
/******************************************************************************/

#include "CItemInventory.h"

/******************************************************************************/
/*!
\brief
Default constructor for class initializes all possible items
*/
/******************************************************************************/
CItemInventory::CItemInventory(void)
{	
	//Initalize all int to 0
	backgroundObj = 
	sardineObj = 
	PncObj = 
	BakedBeanObj = 
	PizzaboxObj = 
	Cereal1Obj = 
	Cereal2Obj =
	PotatoChipObj =
	CokeObj =
	PepsiObj =
	CokeZeroObj =
	MiloObj = 0;

	background =
	sardine =
	Pnc =
	BakedBean =
	Pizzabox =
	CerealBox1 =
	CerealBox2 =
	PototoChip =
	Coke =
	Pepsi =
	CokeZero = 
	Milo = "";

	for (int a = 0; a < 12; a++)
	{
		ItemsTaken[a] = false;
	}
}

CItemInventory::~CItemInventory(void)
{
}
/******************************************************************************/
/*!
\brief
Used for storing enum postion for background for item inventory bar
*/
/******************************************************************************/
void CItemInventory::SetBackground(string newName, int newObj)
{
	backgroundObj = newObj;
	background = newName;
}
/******************************************************************************/
/*!
\brief
Return background obj
*/
/******************************************************************************/
int CItemInventory::getBackgroundMesh()
{
	return backgroundObj;
}
/******************************************************************************/
/*!
\brief
Sets/Creates the sardine obj
*/
/******************************************************************************/
void CItemInventory::SetSardine(string newName, int newObj)
{
	sardineObj = newObj;
	sardine = newName;
}
/******************************************************************************/
/*!
\brief
returns the sardine obj
*/
/******************************************************************************/
int CItemInventory::getSardineMesh()
{
	return sardineObj;
}
/******************************************************************************/
/*!
\brief
returns the sardine name
*/
/******************************************************************************/
string CItemInventory::getSardineName()
{
	return sardine;
}
/******************************************************************************/
/*!
\brief
Sets/Creates the Peas and cans
*/
/******************************************************************************/
void CItemInventory::SetPnc(string newName, int newObj)
{
	PncObj = newObj;
	Pnc = newName;
}
/******************************************************************************/
/*!
\brief
returns the Peas and can obj
*/
/******************************************************************************/
int CItemInventory::getPncMesh()
{
	return PncObj;
}
/******************************************************************************/
/*!
\brief
returns the Peas and cans name (string)
*/
/******************************************************************************/
string CItemInventory::getPncName()
{
	return Pnc;
}
/******************************************************************************/
/*!
\brief
Sets/Creates the Baked beans obj
*/
/******************************************************************************/
void CItemInventory::setBakedBean(string newName, int newObj)
{
	BakedBeanObj = newObj;
	BakedBean = newName;
}
/******************************************************************************/
/*!
\brief
returns the baked bean obj
*/
/******************************************************************************/
int CItemInventory::getBakedBeanMesh()
{
	return BakedBeanObj;
}
/******************************************************************************/
/*!
\brief
returns the Baked bean name
*/
/******************************************************************************/
string CItemInventory::getBakedBeanName()
{
	return BakedBean;
}
/******************************************************************************/
/*!
\brief
Sets/Creates the Pizza box obj
*/
/******************************************************************************/
void CItemInventory::setPizzabox(string newName, int newObj)
{
	PizzaboxObj = newObj;
	Pizzabox = newName;
}
/******************************************************************************/
/*!
\brief
returns the Pizza box obj
*/
/******************************************************************************/
int CItemInventory::getPizzaboxMesh()
{
	return PizzaboxObj;
}
/******************************************************************************/
/*!
\brief
returns the Pizzabox name
*/
/******************************************************************************/
string CItemInventory::getPizzaboxName()
{
	return Pizzabox;
}
/******************************************************************************/
/*!
\brief
Sets/Creates the Cereal box obj
*/
/******************************************************************************/
void CItemInventory::setCerealbox1(string newName, int newObj)
{
	Cereal1Obj = newObj;
	CerealBox1 = newName;
}
/******************************************************************************/
/*!
\brief
returns the Cereal box obj name
*/
/******************************************************************************/
int CItemInventory::getCerealbox1Mesh()
{
	return Cereal1Obj;
}
/******************************************************************************/
/*!
\brief
returns the Cereal box name
*/
/******************************************************************************/
string CItemInventory::getCerealbox1Name()
{
	return CerealBox1;
}
/******************************************************************************/
/*!
\brief
Sets/Creates the Cerealbox2 obj
*/
/******************************************************************************/
void CItemInventory::setCerealbox2(string newName, int newObj)
{
	Cereal2Obj = newObj;
	CerealBox2 = newName;
}
/******************************************************************************/
/*!
\brief
returns the Cereal box obj
*/
/******************************************************************************/
int CItemInventory::getCerealbox2Mesh()
{
	return Cereal2Obj;
}
/******************************************************************************/
/*!
\brief
returns the Cereal box name
*/
/******************************************************************************/
string CItemInventory::getCerealbox2Name()
{
	return CerealBox2;
}
/******************************************************************************/
/*!
\brief
Sets/Creates the potato chips 
*/
/******************************************************************************/
void CItemInventory::setPotatoChip(string newName, int newObj)
{
	PotatoChipObj = newObj;
	PototoChip = newName;
}
/******************************************************************************/
/*!
\brief
returns the Potato chip obj
*/
/******************************************************************************/
int CItemInventory::getPotatoChipMesh()
{
	return PotatoChipObj;
}
/******************************************************************************/
/*!
\brief
returns the Potato chip name
*/
/******************************************************************************/
string CItemInventory::getPotatoChipName()
{
	return PototoChip;
}
/******************************************************************************/
/*!
\brief
Sets/Creates the Coke 
*/
/******************************************************************************/
void CItemInventory::setCoke(string newName, int newObj)
{
	CokeObj = newObj;
	Coke = newName;
}
/******************************************************************************/
/*!
\brief
returns the Coke obj
*/
/******************************************************************************/
int CItemInventory::getCokeMesh()
{
	return CokeObj;
}
/******************************************************************************/
/*!
\brief
returns the Coke name
*/
/******************************************************************************/
string CItemInventory::getCokeName()
{
	return Coke;
}
/******************************************************************************/
/*!
\brief
Sets/Creates the coke zero obj
*/
/******************************************************************************/
void CItemInventory::setCokeZero(string newName, int newObj)
{
	CokeZeroObj = newObj;
	CokeZero = newName;
}
/******************************************************************************/
/*!
\brief
returns the Coke zero obj
*/
/******************************************************************************/
int CItemInventory::getCokeZeroMesh()
{
	return CokeZeroObj;
}
/******************************************************************************/
/*!
\brief
returns the Coke zero name
*/
/******************************************************************************/
string CItemInventory::getCokeZeroName()
{
	return CokeZero;
}
/******************************************************************************/
/*!
\brief
Sets/Creates the Pepsi obj
*/
/******************************************************************************/
void CItemInventory::setPepsi(string newName, int newObj)
{
	PepsiObj = newObj;
	Pepsi = newName;
}
/******************************************************************************/
/*!
\brief
returns the pepsi obj
*/
/******************************************************************************/
int CItemInventory::getPepsiMesh()
{
	return PepsiObj;
}
/******************************************************************************/
/*!
\brief
returns the pepsi name
*/
/******************************************************************************/
string CItemInventory::getPepsiName()
{
	return Pepsi;
}
/******************************************************************************/
/*!
\brief
Sets/Creates the Milo obj
*/
/******************************************************************************/
void CItemInventory::setMilo(string newName, int newObj)
{
	MiloObj = newObj;
	Milo = newName;
}
/******************************************************************************/
/*!
\brief
returns the Milo obj
*/
/******************************************************************************/
int CItemInventory::getMiloMesh()
{
	return MiloObj;
}
/******************************************************************************/
/*!
\brief
returns the Milo name
*/
/******************************************************************************/
string CItemInventory::getMiloName()
{
	return Milo;
}
/******************************************************************************/
/*!
\brief
Acts as a inventory checker. And checks if the bag position is filled or not
*/
/******************************************************************************/
void CItemInventory::setCPlayer(CPlayer player)
{
	if (player.getInventory().getNoOfItems() == 1)
	{
		ItemsTaken[1] = true;
	}
	else if (player.getInventory().getNoOfItems() < 1)
	{
		ItemsTaken[1] = false;
	}

	if (player.getInventory().getNoOfItems() == 2)
	{
		ItemsTaken[2] = true;
	}
	else if (player.getInventory().getNoOfItems() < 2)
	{
		ItemsTaken[2] = false;
	}

	if (player.getInventory().getNoOfItems() == 3)
	{
		ItemsTaken[3] = true;
	}
	else if (player.getInventory().getNoOfItems() < 3)
	{
		ItemsTaken[3] = false;
	}

	if (player.getInventory().getNoOfItems() == 4)
	{
		ItemsTaken[4] = true;
	}
	else if (player.getInventory().getNoOfItems() < 4)
	{
		ItemsTaken[4] = false;
	}

	if (player.getInventory().getNoOfItems() == 5)
	{
		ItemsTaken[5] = true;
	}
	else if (player.getInventory().getNoOfItems() < 5)
	{
		ItemsTaken[5] = false;
	}

	if (player.getInventory().getNoOfItems() == 6)
	{
		ItemsTaken[6] = true;
	}
	else if (player.getInventory().getNoOfItems() < 6)
	{
		ItemsTaken[6] = false;
	}

	if (player.getInventory().getNoOfItems() == 7)
	{
		ItemsTaken[7] = true;
	}
	else if (player.getInventory().getNoOfItems() < 7)
	{
		ItemsTaken[7] = false;
	}

	if (player.getInventory().getNoOfItems() == 8)
	{
		ItemsTaken[8] = true;
	}
	else if (player.getInventory().getNoOfItems() < 8)
	{
		ItemsTaken[8] = false;
	}

	if (player.getInventory().getNoOfItems() == 9)
	{
		ItemsTaken[9] = true;
	}
	else if (player.getInventory().getNoOfItems() < 9)
	{
		ItemsTaken[9] = false;
	}

	if (player.getInventory().getNoOfItems() == 10)
	{
		ItemsTaken[10] = true;
	}
	else if (player.getInventory().getNoOfItems() < 10 )
	{
		ItemsTaken[10] = false;
	}
}
/******************************************************************************/
/*!
\brief
Returns if player has taken 1 item
*/
/******************************************************************************/
bool CItemInventory::getItemsTaken1()
{
	return ItemsTaken[1];
}
/******************************************************************************/
/*!
\brief
Returns if player has taken 2 item
*/
/******************************************************************************/
bool CItemInventory::getItemsTaken2()
{
	return ItemsTaken[2];
}
/******************************************************************************/
/*!
\brief
Returns if player has taken 3 item
*/
/******************************************************************************/
bool CItemInventory::getItemsTaken3()
{
	return ItemsTaken[3];
}
/******************************************************************************/
/*!
\brief
Returns if player has taken 4 item
*/
/******************************************************************************/
bool CItemInventory::getItemsTaken4()
{
	return ItemsTaken[4];
}
/******************************************************************************/
/*!
\brief
Returns if player has taken 5 item
*/
/******************************************************************************/
bool CItemInventory::getItemsTaken5()
{
	return ItemsTaken[5];
}
/******************************************************************************/
/*!
\brief
Returns if player has taken 6 item
*/
/******************************************************************************/
bool CItemInventory::getItemsTaken6()
{
	return ItemsTaken[6];
}
/******************************************************************************/
/*!
\brief
Returns if player has taken 7 item
*/
/******************************************************************************/
bool CItemInventory::getItemsTaken7()
{
	return ItemsTaken[7];
}
/******************************************************************************/
/*!
\brief
Returns if player has taken 8 item
*/
/******************************************************************************/
bool CItemInventory::getItemsTaken8()
{
	return ItemsTaken[8];
}
/******************************************************************************/
/*!
\brief
Returns if player has taken 9 item
*/
/******************************************************************************/
bool CItemInventory::getItemsTaken9()
{
	return ItemsTaken[9];
}
/******************************************************************************/
/*!
\brief
Returns if player has taken 10 item
*/
/******************************************************************************/
bool CItemInventory::getItemsTaken10()
{
	return ItemsTaken[10];
}