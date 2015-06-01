#include "Day.h"

unsigned CDay::Mon_hr = 0;
unsigned CDay::Mon_min = 0;
unsigned CDay::Tue_hr = 0;
unsigned CDay::Tue_min = 0;
unsigned CDay::Wed_hr = 0;
unsigned CDay::Wed_min = 0;
unsigned CDay::Thur_hr = 0;
unsigned CDay::Thur_min = 0;
unsigned CDay::Fri_hr = 0;
unsigned CDay::Fri_min = 0;

CDay::CDay()
{
	startTime_hr = 0;
	startTime_min = 0;
	endTime_hr = 0;
	endTime_min = 0;
	dayOfWeek = 0;
}


CDay::~CDay()
{
}

void CDay::setTimeData(const int hour, const int min, const int dayOfWeek)
{
	this->startTime_hr = hour
}
