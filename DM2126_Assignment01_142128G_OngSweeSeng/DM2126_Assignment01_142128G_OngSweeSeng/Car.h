#pragma once
#include "Vehicle.h"
#include <string>

using std::string;
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
	unsigned int returnCount() const;


protected:
	static unsigned int count;
	bool Eco_Friendly;
	
};

