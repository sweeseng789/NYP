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


CCar::CCar(void)
{

}


CCar::~CCar(void)
{
}



void CCar::setEcoFriendly(bool EF)
{
	Eco_Friendly = EF;
}

bool CCar::returnEcoFriendly() const
{
	return Eco_Friendly;
}

void CCar::setVehicleType(string VehicleTypeM)
{
	VehicleType = VehicleTypeM;
}