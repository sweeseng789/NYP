#pragma once
#include <iostream>
#include <ostream>
#include <istream>
#include <string>
#include <vector>
#include "TimeType.h"

using std::cout;
using std::endl;
using std::cin;
using std::getline;
using std::ostream;
using std::istream;
using std::string;
using std::vector;

class CModule
{
public:
	CModule(void);
	~CModule(void);
	CModule(string moduleCode, int start_hour, int start_min, int d_hour, int d_min, int dayofWeek);

	//Operator overload
	bool operator ! () const;
	friend ostream & operator<<(ostream & output, CModule* & passIn);
	friend istream & operator>>(istream & input, CModule* & passIn);

	int getDay();
	CTimeType getDuration();
private:
	string moduleCode;
	CTimeType duration;

	//Int
	int day;
};

