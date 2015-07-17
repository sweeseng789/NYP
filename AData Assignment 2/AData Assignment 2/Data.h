#pragma once
#include <iostream>
#include <string>
#include <istream>
#include <ostream>

using std::cout;
using std::cin;
using std::endl;
using std::getline;
using std::stoi;
using std::string;
using std::istream;
using std::ostream;

class CData
{
public:
	CData();
	~CData();

	//Setter
	void setData(bool taken, string name, int ID);
	void resetData();

	//Getter
	bool getTaken();
	string getName();
	int getID();

	//Overator Overload
	friend istream& operator>>(istream &input, CData &data);
	friend ostream& operator<<(ostream &output, CData &data);

private:
	bool taken;
	string name;
	int ID;
};

