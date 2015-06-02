#pragma once

#include <iostream>
#include <ostream>
#include <istream>
#include <string>
#include "Day.h"

using std::cin;
using std::cout;
using std::endl;
using std::istream;
using std::ostream;
using std::string;

class CModule
{
public:
	CModule(void);
	~CModule(void);

	void determineDay();
	void setData(string moduleCode, int start_hour, int start_min, int hour, int min, int dayofWeek);
	bool getFull();

	static int mon_hr;
	static int tue_hr;
	static int wed_hr;
	static int thur_hr;
	static int fri_hr;
	static int mon_min;
	static int tue_min;
	static int wed_min;
	static int thur_min;
	static int fri_min;
	CDay day;

	bool operator! () const;
	friend istream& operator>>(istream& input, CModule* passIn);
	friend ostream& operator<<(ostream& output, CModule* passIn);
private:
	string newCode;
	static bool full;
};

