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
using std::ifstream;
using std::string;
using std::stoi;
using std::istringstream;
using std::boolalpha;
int main()
{
	CVehicle * a;
	string something[7];

	ifstream openFile("BY.txt");
	while (openFile.good())
	{
		getline (openFile, something[0], ',');
		if (something[0] == "car")
		{
			a = new CCar();

			a ->setVehicleType(something[0]);

			getline(openFile, something[1], ',');
			something[1].erase(0, 1);
			a->setLicensePlate(something[1]);

			getline(openFile, something[2], ',');

			getline(openFile, something[3], ',');

			getline(openFile, something[4], ',');
			a ->setDate(stoi(something[2]), stoi(something[3]), stoi(something[4]));

			getline(openFile, something[5], ',');
			a ->setEngineCapacity(stoi(something[5]));

			getline(openFile, something[6]);
			int boolean = stoi(something[6]);
			((CCar *) a)->setEcoFriendly(boolean);

			a ->calcDateDifference();
			a ->calculateRoadTax();
			cout << a->returnVehicleType() << ' ' << a->returnCount() << " need to pay " << "$" << a->returnRoadTax() << " as annual road tax" << endl;

		}
		else if (something[0] == "bus")
		{
			a = new CBus();
			a ->setVehicleType(something[0]);

			getline(openFile, something[1], ',');
			something[1].erase(0, 1);
			a->setLicensePlate(something[1]);

			getline(openFile, something[2], ',');

			getline(openFile, something[3], ',');

			getline(openFile, something[4], ',');

			a ->setDate(stoi(something[2]), stoi(something[3]), stoi(something[4]));

			getline(openFile, something[5], ',');
			a ->setEngineCapacity(stoi(something[5]));

			getline(openFile, something[6]);
			((CBus *) a)->setSeatingCapacity(stoi(something[6]));

			a ->calcDateDifference();
			a ->calculateRoadTax();
			cout << a->returnVehicleType() << ' ' << a->returnCount() << " need to pay " << "$" << a->returnRoadTax() << " as annual road tax" << endl;

		}
	}
	openFile.close();
	delete a;
}