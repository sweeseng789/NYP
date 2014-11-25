#pragma once
#include <iostream>
#include <string>
#include "Date.h"
using std::string;
class CVehicle : public CDate
{
public:
	CVehicle(void);
	~CVehicle(void);
	void printTest(void);

	virtual void setVehicleType(string VehicleTypeM);//Mutator
	void setEngineCapacity(int EngineCapactityM);
	void setLicensePlate(string licensePlateM);

	string returnVehicleType(void) const;//Accessor
	int returnEngineCapacity(void) const;
	string returnLicensePlate(void) const; 

	int age;
	unsigned int count;

	int AnnualRoadTax;
protected:
	string VehicleType;
	string LicensePlate;
	int EngineCapacity;
};

