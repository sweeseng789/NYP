#include <iostream>
#include <fstream>
#include <string>
#include "Car.h"
#include "Date.h"
#include "Vehicle.h"
#include "Bus.h"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::ofstream;
using std::string;


CDate::CDate(void)
{
	year = 0;
	month = 0;
	day = 0;
}

CDate::CDate(int yearM, int monthM, int dayD)
{
	year = yearM;
	month = monthM;
	day = dayD;
}

CDate::~CDate(void)
{
}

void CDate::printData()
{
	cout << year << '/' << month << '/' << day << endl;
}
/*void CDate::setDate(int yearM, int monthM, int dayM)
{
	year = yearM;
	month = monthM;
	day = dayM;
}*/

void CDate::calcDateDifference() 
{
	if (year < 2014)
	{
		dateDiff = 2014 - year;
	}
	else if (year == 2014)
	{
		dateDiff = 0;
	}

	if (month <= 11)
	{
		dateDiff += 0;
	}
	else if (month > 11)
	{
		dateDiff += 1;
	}
}

int CDate::returnYear() const
{
	return year;
}

int CDate::returnDay() const
{
	return day;
}

int CDate::returnMonth() const
{
	return month;
}

int CDate::returnDateDiff() const
{
	return dateDiff;
}