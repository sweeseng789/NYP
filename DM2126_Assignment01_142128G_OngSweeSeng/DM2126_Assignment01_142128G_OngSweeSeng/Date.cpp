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


CDate::~CDate(void)
{
}

void CDate::setDate(int yearM, int monthM, int dayM)
{
	year = yearM;
	month = monthM;
	day = dayM;
}

void CDate::calcDateDifference() 
{
	if (year > 2014)
	{
		yearD = year - 2014;
	}
	else if (year < 2014)
	{
		yearD = 2014 - year;
	}
	else
	{
		yearD = 0;
	}

	if (month > 11)
	{
		monthD = month - 11;
	}
	else if (month < 11)
	{
		monthD = 11 - month;
	}
	else
	{
		monthD = 0;
	}

	if (day > 1)
	{
		dayD = day - 1;
	}
	else if (day < 1)
	{
		dayD = 1 - day;
	}
	else
	{
		dayD = 0;
	}

	age = yearD;
}

int CDate::returnYear() const
{
	return year;
}

int CDate::returnMonth() const
{
	return month;
}

int CDate::returnDay() const
{
	return day;
}
