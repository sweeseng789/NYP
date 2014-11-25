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
	cout << CVehicle::returnVehicleType() << endl;
	cout << CVehicle::returnLicensePlate() << endl;
	cout << CDate::returnYear() << '/' << CDate::returnMonth() << '/' << CDate::returnDay() << endl;
	cout << CVehicle::returnEngineCapacity() << endl;
	cout << &CCar::returnEcoFriendly << endl;
	cout << endl;
}