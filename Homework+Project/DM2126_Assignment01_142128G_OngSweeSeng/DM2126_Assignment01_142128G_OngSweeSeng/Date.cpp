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