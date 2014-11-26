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

unsigned int CBus::count = 0;
CBus::CBus(void)
{
	count ++;
	cout << "CBus created" << endl;
}


CBus::~CBus(void)
{
	count --;
	cout << "CBus deleted" << endl;
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
	cout << CBus::returnVyear() << '/' << CBus::returnVmonth() << '/' << CBus::returnVday() << endl;
	cout << CBus::returnEngineCapacity() << endl;
	cout << CBus::returnSeatingCapacity() << endl;
	cout << CBus::returnCount() << "bus count" << endl;
}

void CBus::calculateRoadTax()
{
	if (age < 5 && SeatingCapacity < 40)
	{
		AnnualRoadTax = (1 * CBus::returnEngineCapacity());
	}
	else if (age < 5 && SeatingCapacity >= 40)
	{
		AnnualRoadTax = (1 * CBus::returnEngineCapacity()) * 2;
	}
	else if (age >= 5 && SeatingCapacity < 40)
	{
		AnnualRoadTax = (1 * CBus::returnEngineCapacity()) * 1.2;
	}
	else if (age >= 5 && SeatingCapacity >= 40)
	{
		AnnualRoadTax = (1 * CBus::returnEngineCapacity()) * 1.2 * 2;
	}
}

double CBus::returnRoadTax() const
{
	return AnnualRoadTax;
}
unsigned int CBus::returnCount() const
{
	return count;
}
