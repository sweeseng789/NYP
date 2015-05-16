#include "TimeType.h"

int total_input = 0;
CTimeType::CTimeType(void)
{
	hour = minute = start_hour = start_minute = 0;
}


CTimeType::~CTimeType(void)
{
}

//CTimeType CTimeType::operator= (CTimeType * & passIn)
//{
//	if (*this != &passIn)
//	{
//		*this->hour = passIn.hour;
//		*this->minute = passIn.minute;
//	}
//	return *this;
//}

//CTimeType CTimeType::operator++()
//{
//	CTimeType * output = this;
//
//	output.start_hour = this->start_hour += this->hour;
//	output.start_minute = this->start_minute += this->minute;
//
//	return output;
//}

ostream & operator<<(ostream & output, CTimeType & passIn)
{
	output << (passIn.start_hour * 60) + passIn.start_minute << endl;
	return output;
}

istream & operator<<(istream & input, CTimeType & passIn)
{
	return input;
}

void CTimeType::setTime(int hour, int minute, int start_hour, int start_minute, int dayofWeek)
{
	this->hour = hour;
	this->minute = minute;

	this->start_hour = start_hour;
	this->start_minute = start_minute;

	this->dayofWeek = dayofWeek;
}

int CTimeType::getHour()
{
	return this->hour;
}

int CTimeType::getMinute()
{
	return this->minute;
}

int CTimeType::getStartHour()
{
	return this->start_hour;
}

int CTimeType::getStartMin()
{
	return this->start_minute;
}

int CTimeType::getDOW()
{
	return this->dayofWeek;
}