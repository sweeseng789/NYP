#pragma once

#include <iostream>
#include <string>
#include <ostream>>
#include <istream>
#include "Day.h"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::istream;
using std::ostream;
using std::string;

class CModule
{
public:
	CModule();
	~CModule();

	friend istream& operator>>(istream& is, CModule* &passIn);

	void setData(const string moduleCode, const int hour, const int min, const int dayOfWeek);
private:
	//String
	string moduleCode;

	//Class
	CDay time;
};

