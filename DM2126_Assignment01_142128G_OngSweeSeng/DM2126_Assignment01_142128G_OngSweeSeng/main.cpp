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
	CVehicle * sizeOfVehicleC[100];
	CVehicle * sizeOfVehicleB[100];
	int totalcount;
	int carTotalTax = 0;
	int busTotalTax = 0;

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

			CDate testing(stoi(something[2]), stoi(something[3]), stoi(something[4]));
			CVehicle setDate(testing);
			a ->setVDate(stoi(something[2]), stoi(something[3]), stoi(something[4]));

			getline(openFile, something[5], ',');
			a ->setEngineCapacity(stoi(something[5]));

			getline(openFile, something[6]);
			int boolean = stoi(something[6]);
			((CCar *) a)->setEcoFriendly(boolean);
				
			sizeOfVehicleC[((CCar *)a) ->returnCountC()] = a;

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

			CDate testing(stoi(something[2]), stoi(something[3]), stoi(something[4]));
			CVehicle setDate(testing);
			a ->setVDate(stoi(something[2]), stoi(something[3]), stoi(something[4]));

			getline(openFile, something[5], ',');
			a ->setEngineCapacity(stoi(something[5]));

			getline(openFile, something[6]);
			((CBus *) a)->setSeatingCapacity(stoi(something[6]));

			sizeOfVehicleB[((CBus *)a) ->returnCountB()] = a;

		}
	}
	openFile.close();

	totalcount = ((CBus *) a) ->returnCountB() + ((CCar *) a) ->returnCountC();

	cout << "1) The total amount of cars on the road is:" << totalcount << endl;
	cout << endl;

	cout << "2) Printing of all car and bus details" << endl;
	//car
	for (int b = 1; b <= ((CCar *) a) ->returnCountC(); b++)
	{
		cout << sizeOfVehicleC[b]->returnVehicleType() << ' ' << b << endl;
		cout << "License plate:" << ' ' << sizeOfVehicleC[b] ->returnLicensePlate() << endl;
		cout << "DOR:" << ' ' << sizeOfVehicleC[b] ->returnVyear() <<'/' << sizeOfVehicleC[b] ->returnVmonth() << '/' << sizeOfVehicleC[b] ->returnVday() << endl;
		cout << "Engine Capacity:" << ' ' << sizeOfVehicleC[b] ->returnEngineCapacity() << endl;
		cout << "Eco-Friendly:" << ' ' << boolalpha << ((CCar *) sizeOfVehicleC[b]) ->returnEcoFriendly() << endl;
		cout << endl;
	}
	//bus
	for (int b = 1; b <= ((CBus *) a) ->returnCountB(); b++)
	{
		cout << sizeOfVehicleB[b]->returnVehicleType() << ' ' << b << endl;
		cout << "License plate:" << ' ' << sizeOfVehicleB[b] ->returnLicensePlate() << endl;
		cout << "DOR:" << ' ' << sizeOfVehicleB[b] ->returnVyear() <<'/' << sizeOfVehicleB[b] ->returnVmonth() << '/' << sizeOfVehicleB[b] ->returnVday() << endl;
		cout << "Engine Capacity:" << ' ' << sizeOfVehicleB[b] ->returnEngineCapacity() << endl;
		cout << "Seating Capacity:" << ' ' << ((CBus *) sizeOfVehicleB[b]) ->returnSeatingCapacity() << endl;
		cout << endl;
	}

	cout << "3) Print out all bus that are eco-frindly or not eco-friendly" << endl;
	//car
	cout << "Eco-friendly car" << endl;
	for (int b = 1; b <= ((CCar *) a) ->returnCountC(); b++)
	{
		if (((CCar *) sizeOfVehicleC[b]) ->returnEcoFriendly() == true)
		{
			cout << sizeOfVehicleC[b]->returnVehicleType() << ' ' << b << endl;
			cout << "License plate:" << ' ' << sizeOfVehicleC[b] ->returnLicensePlate() << endl;
			cout << "DOR:" << ' ' << sizeOfVehicleC[b] ->returnVyear() <<'/' << sizeOfVehicleC[b] ->returnVmonth() << '/' << sizeOfVehicleC[b] ->returnVday() << endl;
			cout << "Engine Capacity:" << ' ' << sizeOfVehicleC[b] ->returnEngineCapacity() << endl;
			cout << "Eco-Friendly:" << ' ' << boolalpha << ((CCar *) sizeOfVehicleC[b]) ->returnEcoFriendly() << endl;
			cout << endl;
		}
	}
	cout << "Not eco-friendly car" << endl;
	for (int b = 1; b <= ((CCar *) a) ->returnCountC(); b++)
	{
		if (((CCar *) sizeOfVehicleC[b]) ->returnEcoFriendly() == false)
		{
			cout << sizeOfVehicleC[b]->returnVehicleType() << ' ' << b << endl;
			cout << "License plate:" << ' ' << sizeOfVehicleC[b] ->returnLicensePlate() << endl;
			cout << "DOR:" << ' ' << sizeOfVehicleC[b] ->returnVyear() <<'/' << sizeOfVehicleC[b] ->returnVmonth() << '/' << sizeOfVehicleC[b] ->returnVday() << endl;
			cout << "Engine Capacity:" << ' ' << sizeOfVehicleC[b] ->returnEngineCapacity() << endl;
			cout << "Eco-Friendly:" << ' ' << boolalpha << ((CCar *) sizeOfVehicleC[b]) ->returnEcoFriendly() << endl;
			cout << endl;
		}
	}

	//Bus
	cout << "Bus above or equal 40 seating capacity " << endl;
	for (int b = 1; b <= ((CBus *) a) ->returnCountB(); b++)
	{
		if (((CBus *) sizeOfVehicleB[b]) ->returnSeatingCapacity() >= 40)
		{
			cout << sizeOfVehicleB[b]->returnVehicleType() << ' ' << b << endl;
			cout << "License plate:" << ' ' << sizeOfVehicleB[b] ->returnLicensePlate() << endl;
			cout << "DOR:" << ' ' << sizeOfVehicleB[b] ->returnVyear() <<'/' << sizeOfVehicleB[b] ->returnVmonth() << '/' << sizeOfVehicleB[b] ->returnVday() << endl;
			cout << "Engine Capacity:" << ' ' << sizeOfVehicleB[b] ->returnEngineCapacity() << endl;
			cout << "Seating Capacity:" << ' ' << ((CBus *) sizeOfVehicleB[b]) ->returnSeatingCapacity() << endl;
			cout << endl;
		}
	}

	cout << "Bus below 40 seating capacity " << endl;
	for (int b = 1; b <= ((CBus *) a) ->returnCountB(); b++)
	{
		if (((CBus *) sizeOfVehicleB[b]) ->returnSeatingCapacity() < 40)
		{
			cout << sizeOfVehicleB[b]->returnVehicleType() << ' ' << b << endl;
			cout << "License plate:" << ' ' << sizeOfVehicleB[b] ->returnLicensePlate() << endl;
			cout << "DOR:" << ' ' << sizeOfVehicleB[b] ->returnVyear() <<'/' << sizeOfVehicleB[b] ->returnVmonth() << '/' << sizeOfVehicleB[b] ->returnVday() << endl;
			cout << "Engine Capacity:" << ' ' << sizeOfVehicleB[b] ->returnEngineCapacity() << endl;
			cout << "Seating Capacity:" << ' ' << ((CBus *) sizeOfVehicleB[b]) ->returnSeatingCapacity() << endl;
			cout << endl;
		}
	}


	cout << "5) Calculate road tax" << endl;
	//car
	for (int b = 1; b <= ((CCar *) a) ->returnCountC(); b++)
	{
		
		sizeOfVehicleC[b] ->calculateRoadTax();
		cout << sizeOfVehicleC[b]->returnVehicleType() << ' ' << b << " need to pay $" << ((CCar *) sizeOfVehicleC[b]) ->returnRoadTax() << " as road tax" << endl;
		carTotalTax += ((CCar *) sizeOfVehicleC[b]) ->returnRoadTax();
		cout << endl;
	}

	//bus
	for (int b = 1; b <= ((CBus *) a) ->returnCountB(); b++)
	{
		sizeOfVehicleB[b] ->calculateRoadTax();
		cout << sizeOfVehicleB[b]->returnVehicleType() << ' ' << b << " need to pay $" << ((CBus *) sizeOfVehicleB[b]) ->returnRoadTax() << " as road tax" << endl;
		busTotalTax += ((CBus *) sizeOfVehicleB[b]) ->returnRoadTax();
		cout << endl;
	}

	cout << "6) Calaulate total road tax for cars/buses" << endl;
	cout << "Total road tax for cars is:" << "$" << carTotalTax << endl;
	cout << "Total road tax for buses is:" << "$" << busTotalTax << endl;
	cout << "Total road tax for buses and car is:" << "$" << carTotalTax + busTotalTax << endl;

	for (int b = 1; b <= ((CCar *) a) ->returnCountC(); b++) //Delete Car data
	{
		delete sizeOfVehicleC[b];
	}

	for (int b = 1; b <= ((CBus *) a) ->returnCountB(); b++) //Delete bus Data
	{
		delete sizeOfVehicleB[b];
	}
}