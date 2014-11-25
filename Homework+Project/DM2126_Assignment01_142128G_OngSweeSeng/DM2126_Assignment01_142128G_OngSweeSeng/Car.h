#pragma once
#include "Vehicle.h"
class CCar : public CVehicle
{
public:
	CCar(void);
	~CCar(void);


	void setEcoFriendly(bool EF);// Mutator

	bool returnEcoFriendly(void) const;//Accessor
	virtual void setVehicleType(string VehicleTypeM);//Mutator

protected:
	bool Eco_Friendly;
	
};

