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


CBus::CBus(void)
{
}


CBus::~CBus(void)
{
}


void CBus ::setSeatingCapacity(int SeatingCapacityM)
{
	SeatingCapacity = SeatingCapacityM;
}

int CBus::returnSeatingCapacity() const
{
	return SeatingCapacity;
}

void CBus::printTest(void)
{
	cout << CBus::returnVehicleType() << endl;
	cout << CBus::returnLicensePlate() << endl;
	cout << CBus::returnYear() << '/' << CBus::returnMonth() << '/' << CBus::returnDay() << endl;
	cout << CBus::returnEngineCapacity() << endl;
	cout << CBus::returnSeatingCapacity() << endl;
	cout << CBus::returnCount() << "count" << endl;
}

void CBus::calculateRoadTax()
{
	if (age < 5 && SeatingCapacity < 40)
	{
		AnnualRoadTax = 1;
	}
	else if (age < 5 && SeatingCapacity >= 40)
	{
		AnnualRoadTax = 1 * 2;
	}
	else if (age >= 5 && SeatingCapacity < 40)
	{
		AnnualRoadTax = 1 * 1.2;
	}
	else if (age >= 5 && SeatingCapacity >= 40)
	{
		AnnualRoadTax = 1 * 1.2 * 2;
	}
}

double CBus::returnRoadTax() const
{
	return AnnualRoadTax;
}