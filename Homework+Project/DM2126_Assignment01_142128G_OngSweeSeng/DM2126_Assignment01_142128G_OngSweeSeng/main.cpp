#include <iostream>
#include <fstream>
#include <string>
#include "Car.h"
#include "Date.h"
#include "Vehicle.h"
#include "Bus.h"
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::ifstream;
using std::string;
using std::vector;
using std::stoi;
using std::istringstream;
using std::boolalpha;
int main()
{
	vector<CVehicle *> a;
	string something[8];

	ifstream openFile("BY.txt");
	while (openFile.good())
	{
		a.push_back( new CCar() );
		a.resize(a.size() + 1);
		getline(openFile, something[1], ',');
		//a[a.size()  -1].setVehicleType(something[1]);
		a[a.size() - 1]->setVehicleType(something[1]);
		/*getline(openFile, something[2], ',');
		something[2].erase(0, 1);
		a[a.size() - 1]->setLicensePlate(something[2]);

		getline(openFile, something[3], ',');

		getline(openFile, something[4], ',');

		getline(openFile, something[5], ',');
		a[a.size() - 1]->setDate(stoi(something[3]), stoi(something[4]), stoi(something[5]));

		getline(openFile, something[6], ',');
		a[a.size() - 1]->setEngineCapacity(stoi(something[6]));

		getline(openFile, something[7]);
		int boolean = stoi(something[7]);
		a[a.size() - 1]->setEcoFriendly(boolean);

		a[a.size() - 1]->printTest();*/
	}
	openFile.close();
}