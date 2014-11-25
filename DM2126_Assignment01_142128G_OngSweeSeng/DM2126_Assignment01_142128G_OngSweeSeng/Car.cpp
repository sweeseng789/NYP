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


CCar::CCar(void)
{
}


CCar::~CCar(void)
{
}



void CCar::setEcoFriendly(bool EF)
{

	Eco_Friendly = EF;
	
}

bool CCar::returnEcoFriendly() const
{
	return Eco_Friendly;
}


void CCar::printTest(void)
{
	cout << CCar::returnVehicleType() << endl;
	cout << CCar::returnLicensePlate() << endl;
	cout << CCar::returnYear() << '/' << CCar::returnMonth() << '/' << CCar::returnDay() << endl;
	cout << CCar::returnEngineCapacity() << endl;
	cout << CCar::returnEcoFriendly() << endl;
	cout << CCar::returnCount() << "count" << endl;
}

void CCar::calculateRoadTax(void)
{
	if(age < 5 && EngineCapacity < 1600 && Eco_Friendly == false)
	{
		AnnualRoadTax = 1;
	}
	else if(age < 5 && EngineCapacity < 1600 && Eco_Friendly == true)
	{
		AnnualRoadTax = 1 * 0.8;
	}
	else if (age < 5 && EngineCapacity >= 1600 && Eco_Friendly == false)
	{
		AnnualRoadTax = 1 * 2;
	}
	else if(age < 5 && EngineCapacity >= 1600 && Eco_Friendly == true)
	{
		AnnualRoadTax = 1 * 2 * 0.8;
	}
	else if(age >= 5 && EngineCapacity < 1600 && Eco_Friendly == false)
	{
		AnnualRoadTax = 1 * 1.2;
	}
	else if (age >= 5 && EngineCapacity < 1600 && Eco_Friendly == true)
	{
		AnnualRoadTax = 1 * 1.2 * 0.8;
	}
	else if(age >= 5 && EngineCapacity >= 1600 && Eco_Friendly == false)
	{
		AnnualRoadTax = 1 * 1.2 * 2;
	}
	else if (age >= 5 && EngineCapacity >= 1600 && Eco_Friendly == true)
	{
		AnnualRoadTax = 1 * 1.2 * 2 * 0.8;
	}
}

double CCar::returnRoadTax() const
{
	return AnnualRoadTax;
}