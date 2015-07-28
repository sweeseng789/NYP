#include "Data.h"




CData::CData(): taken(false), name(""), ID(0)
{
}


CData::~CData()
{
}

void CData::setData(bool taken, string name, int ID)
{
	this->taken = taken;
	this->name = name;
	this->ID = ID;
}

void CData::resetData()
{
	taken = false;
	name = "";
	ID = 0;
}

bool CData::getTaken()
{
	return taken;
}

string CData::getName()
{
	return name;
}

int CData::getID()
{
	return ID;
}

//bool checkStringForNumber(string ID)
//{
//	for (unsigned a = 0; a < ID.size(); ++a)
//	{
//		if (!isdigit(ID[a]))
//			return true;
//		else
//			return false;
//	}
//}
//
//istream & operator>>(istream & input, CData & data)
//{
//	string name = "";
//	int ID = 0;
//	string IDtoCheck = "";
//	bool allNum = false;
//
//	cout << "Please enter your name" << endl;
//	cin.ignore();
//	getline(input, name);
//
//	//Check if there is more than 32 character, if true then shorten it to 32
//	if (name.size() > 32)
//		name.resize(32);
//
//	cout << endl;
//
//	cout << "Please enter your ID" << endl;
//	getline(input, IDtoCheck);
//
//	try{
//		//Check if ID contain stuff other than numbers or ID size is more than 5 digit
//		if (checkStringForNumber(IDtoCheck) || IDtoCheck.size() > 5)
//			throw CUI(CUI::INVALID);
//		else
//			throw CUI(CUI::VALID);
//	}
//	catch (CUI ui)
//	{
//		if (ui.getType() == CUI::VALID)
//		{
//			ID = stoi(IDtoCheck);
//			data.setData(true, name, ID);
//		}
//		else
//		{
//			cout << "Error, please try again later" << endl;
//		}
//	}
//	return input;
//}

ostream & operator<<(ostream & output, CData & data)
{
	output << "Patient's Name: " << data.getName() << endl;
	output << "Patient's ID: " << data.getID() << endl;

	return output;
}