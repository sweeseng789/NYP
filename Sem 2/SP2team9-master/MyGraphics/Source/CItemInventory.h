/******************************************************************************/
/*!
\file	CItemInventory.h
\author Ong Swee Seng
\par	email: 141991A@mymail.nyp.edu.sg
\brief
CItemInventory Class
*/
/******************************************************************************/
#pragma once
#include <string>
#include "Vector3.h"
#include "Mesh.h"
#include "Mtx44.h"
#include "Player.h"
#include "MatrixStack.h"

using std::string;
/******************************************************************************/
/*!
	Class CItemInventory
\brief
Defines the variables and functions required for the CItemInventory

*/
/******************************************************************************/
class CItemInventory
{
public:
	CItemInventory(void);
	~CItemInventory(void);

	void SetBackground(string newName, int newObj);
	void SetSardine(string newName, int newObj);
	void SetPnc(string newName, int newObj);
	void setBakedBean(string newName, int newObj);
	void setPizzabox(string newName, int newObj);
	void setCerealbox1(string newName, int newObj);
	void setCerealbox2(string newName, int newObj);
	void setPotatoChip(string newName, int newObj);
	void setCoke(string newName, int newObj);
	void setPepsi(string newName, int newObj);
	void setCokeZero(string newName, int newObj);
	void setMilo(string newName, int newObj);
	void setCPlayer(CPlayer);

	int getBackgroundMesh();
	int getSardineMesh();
	int getPncMesh();
	int getBakedBeanMesh();
	int getPizzaboxMesh();
	int getCerealbox1Mesh();
	int getCerealbox2Mesh();
	int getPotatoChipMesh();
	int getCokeMesh();
	int getPepsiMesh();
	int getCokeZeroMesh();
	int getMiloMesh();

	string getSardineName();
	string getPncName();
	string getBakedBeanName();
	string getPizzaboxName();
	string getCerealbox1Name();
	string getCerealbox2Name();
	string getPotatoChipName();
	string getCokeName();
	string getPepsiName();
	string getCokeZeroName();
	string getMiloName();

	CPlayer testing();
	bool getItemsTaken1(),
		getItemsTaken2(),
		getItemsTaken3(),
		getItemsTaken4(),
		getItemsTaken5(),
		getItemsTaken6(),
		getItemsTaken7(),
		getItemsTaken8(),
		getItemsTaken9(),
		getItemsTaken10();

private:
	int backgroundObj, 
		sardineObj,
		PncObj,
		BakedBeanObj,
		PizzaboxObj,
		Cereal1Obj,
		Cereal2Obj,
		PotatoChipObj,
		CokeObj,
		PepsiObj,
		CokeZeroObj,
		MiloObj;

	string background,
			sardine,
			Pnc,
			BakedBean,
			Pizzabox,
			CerealBox1,
			CerealBox2,
			PototoChip,
			Coke,
			Pepsi,
			CokeZero,
			Milo;
	bool ItemsTaken[12];
};

