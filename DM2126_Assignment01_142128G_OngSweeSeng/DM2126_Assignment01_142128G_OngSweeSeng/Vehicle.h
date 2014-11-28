#pragma once
#include <iostream>
#include <string>
#include "Date.h"
using std::string;
class CVehicle 
{
public:
	CVehicle(void);
	virtual ~CVehicle(void);
	virtual void printTest(void);
	void setVehicleType(string VehicleTypeM);//Mutator
	void setEngineCapacity(int EngineCapactityM);
	void setLicensePlate(string licensePlateM);
	virtual void calculateRoadTax();
	void setVDate(int VyearM, int VmonthM, int VdayM);
	void setDOR(CDate date);
	/*CVehicle(CDate dorM) : DOR(dorM) 
	{
		Vyear = DOR.returnYear();
		Vmonth = DOR.returnMonth();
		Vday = DOR.returnDay();
		DOR.calcDateDifference();
		age =DOR.returnDateDiff();
	
	}*/

	string returnVehicleType(void) const;//Accessor
	int returnEngineCapacity(void) const;
	string returnLicensePlate(void) const; 
	virtual unsigned int returnCount() const;
	virtual double returnRoadTax(void) const;

	int returnVyear() const;
	int returnVmonth() const;
	int returnVday() const;

protected:
	string VehicleType;
	string LicensePlate;
	int EngineCapacity;
	double AnnualRoadTax;
	CDate DOR;

	int Vyear;
	int Vday;
	int Vmonth;

	int age;
};

