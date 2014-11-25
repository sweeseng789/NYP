#pragma once
#include "Vehicle.h"
class CBus : public CVehicle
{
public:
	CBus(void);
	~CBus(void);
	void printTest(void);

	void setSeatingCapacity(int SeatingCapacityM);
	void calculateRoadTax();

	int returnSeatingCapacity () const;
	double returnRoadTax(void) const;
protected:
	int SeatingCapacity;
private:
	
};

