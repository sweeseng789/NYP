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
	void DetermineDay();
	void updateTiming_Mon(CModule* passIn);
	void updateTiming_Tue(CModule* passIn);
	void updateTiming_Wed(CModule* passIn);
	void updateTiming_Thur(CModule* passIn);
	void updateTiming_Fri(CModule* passIn);
	CTimeType getDuration();

	static int mon_hour;
	static int mon_min;
	static int tue_hour;
	static int tue_min;
	static int wed_hour;
	static int wed_min;
	static int thur_hour;
	static int thur_min;
	static int fri_hour;
	static int fri_min;
	static int day2;
	static int input_hour;
	static int input_min;
	static int input_total;
	static int freeTime;
	static int hourToSet;
	static int minToSet;
	static string newCode;
private:
	string moduleCode;
	CTimeType duration;

	//Int
	int day;
};

