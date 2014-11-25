#pragma once
#include "Vehicle.h"
class CCar : public CVehicle
{
public:
	CCar(void);
	~CCar(void);
	void printTest(void);

	void setEcoFriendly(bool EF);// Mutator
	void calculateRoadTax();

	bool returnEcoFriendly(void) const;//Accessor
	double returnRoadTax(void) const;


protected:
	bool Eco_Friendly;
	
};

