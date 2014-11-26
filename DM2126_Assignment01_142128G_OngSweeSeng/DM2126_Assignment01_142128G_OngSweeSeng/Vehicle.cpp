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


CVehicle::CVehicle(void)
{
}

CVehicle::~CVehicle(void)
{
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

double CVehicle::returnRoadTax() const
{
	return 0;
}

unsigned int CVehicle::returnCount() const
{
	return 0;
}

int CVehicle::returnVyear() const
{
	return Vyear;
}

int CVehicle::returnVmonth() const
{
	return Vmonth;
}

int CVehicle::returnVday() const
{
	return Vday;
}

void CVehicle::setVDate(int VyearM, int VmonthM, int VdayM)
{
	Vyear = VyearM;
	Vmonth = VmonthM;
	Vday = VdayM;
}