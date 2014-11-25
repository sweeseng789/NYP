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

unsigned int CVehicle::count = 0;

CVehicle::CVehicle(void)
{
	count++;
}


CVehicle::~CVehicle(void)
{
	count--;
	cout << "delete" << endl;
}

void CVehicle::setVehicleType(string VehicleTypeM)
{
	VehicleType = VehicleTypeM;
}

void CVehicle::setEngineCapacity(int setEngineCapacityM)
{
	EngineCapacity = setEngineCapacityM;
}

void CVehicle::setLicensePlate(string LicensePlateM)
{
	LicensePlate = LicensePlateM;
}

string CVehicle::returnVehicleType() const
{
	return VehicleType;
}
string CVehicle::returnLicensePlate() const
{
	return LicensePlate;
}

int CVehicle::returnEngineCapacity() const
{
	return EngineCapacity;
}

void CVehicle::printTest(void)
{
	cout << "Undefined" << endl;
}

void CVehicle::calculateRoadTax(void)
{
	cout << "Undefined" << endl;
}

unsigned int CVehicle::returnCount() const
{
	return count;
}

double CVehicle::returnRoadTax() const
{
	return 0;
}