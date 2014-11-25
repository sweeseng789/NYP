#pragma once
#include <iostream>
#include <string>
#include "Date.h"
using std::string;
class CVehicle : public CDate
{
private:
	static unsigned int count;
public:
	CVehicle(void);
	virtual ~CVehicle(void);
	virtual void printTest(void);

	void setVehicleType(string VehicleTypeM);//Mutator
	void setEngineCapacity(int EngineCapactityM);
	void setLicensePlate(string licensePlateM);
	virtual void calculateRoadTax();

	string returnVehicleType(void) const;//Accessor
	int returnEngineCapacity(void) const;
	string returnLicensePlate(void) const; 
	unsigned int returnCount() const;
	virtual double returnRoadTax(void) const;

protected:
	string VehicleType;
	string LicensePlate;
	int EngineCapacity;
	double AnnualRoadTax;
};

