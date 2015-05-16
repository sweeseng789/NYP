#pragma once
#include <iostream>
#include <ostream>
#include <istream>

using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::istream;

class CTimeType
{
public:
	CTimeType(void);
	~CTimeType(void);
	CTimeType operator++();
	CTimeType operator=(CTimeType & passIn);
	friend istream & operator>>(istream & input, CTimeType & passIn);
	friend ostream & operator<<(ostream & output, CTimeType & passIn);

	void setTime(int hour, int minute, int start_hour, int start_minute, int dayofWeek);
	int returnDuration();
	int getHour();
	int getMinute();
	int getStartHour();
	int getStartMin();
	int getDOW();

private:
	int dayofWeek;
	int hour;
	int minute;
	int start_hour;
	int start_minute;
};

