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

void checkStringForNumber(bool & allNum, string ID)
{
	for (unsigned a = 0; a < ID.size(); ++a)
	{
		if (!isdigit(ID[a]))
		{
			allNum = true;
			break;
		}
		else
			allNum = false;
	}
}

istream & operator>>(istream & input, CData & data)
{
	string name = "";
	int ID = 0;
	bool allNum = false;

	cout << "Please enter your name" << endl;
	cin.ignore();
	getline(input, name);

	//Check if there is more than 32 character, if true then shorten it to 32
	if (name.size() > 32)
		name.resize(32);

	cout << endl;

	cout << "Please enter your ID" << endl;
	cin >> ID;
	//Check if ID contain stuff other than numbers or ID size is more than 5 digit
	//checkStringForNumber(allNum, ID);
	//while (allNum == true /*|| ID.size() > 5*/)
	//{
	//	cout << "Error, please enter the patient's Data again" << endl;
	//	getline(input, ID);
	//	checkStringForNumber(allNum, ID);
	//}

	data.setData(true, name, ID);
	return input;
}

ostream & operator<<(ostream & output, CData & data)
{
	output << "Patient's Name: " << data.getName() << endl;
	output << "Patient's ID: " << data.getID() << endl;

	return output;
}