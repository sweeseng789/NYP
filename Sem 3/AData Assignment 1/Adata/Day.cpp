#include "Day.h"


CDay::CDay(void)
{
	this->dayOfWeek = 0;
	this->start_hr = 0;
	this->start_min = 0;
	this->hour = 0;
	this->min = 0;
}

CDay::~CDay(void)
{
}

int CDay::getHour()
{
	return this->hour;
}

int CDay::getMin()
{
	return this->min;
}

int CDay::getSHour()
{
	return this->start_hr;
}

int CDay::getSMin()
{
	return this->start_min;
}


void CDay::setTime(int start_hour, int start_min, int hour, int min, int dayofWeek)
{
	this->start_hr = start_hour;
	this->start_min = start_min;
	this->hour = hour;
	this->min = min;
	this->dayOfWeek = dayOfWeek;
}