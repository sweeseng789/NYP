#include <iostream>
#include <vector>
#include <string>
#include "Module.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::getline;

//Parameters

//Int
int mon_hour = 0;
int mon_min = 0;
int tue_hour = 0;
int tue_min = 0;
int wed_hour = 0;
int wed_min = 0;
int thur_hour = 0;
int thur_min = 0;
int fri_hour = 0;
int fri_min = 0;
int day = 1;
int input_hour = 0;
int input_min = 0;
int input_total = 0;
int freeTime = 0;
int hourToSet = 0;
int minToSet = 0;
int choice1 = 0;
int choice2 = 0;

//Bool
bool MonEntered = false;
bool TueEntered = false;
bool WedEntered = false;
bool ThurEntered = false;
bool FriEntered = false;

//String
string newCode = "";

CModule * newModule;
vector<CModule *> Timetable;

void printMon()
{
	if (MonEntered == true)
	{
		for (unsigned a = 0; a < Timetable.size(); ++a)
		{
			if (Timetable[a]->getDuration().getDOW() == 1)
			{
				cout << Timetable[a];
			}
			cout << endl;
		}
	}
	else
	{
		cout << "No Data for Monday is entered" << endl;
	}
}
void printTue()
{
	if (TueEntered == true)
	{
		for (unsigned a = 0; a < Timetable.size(); ++a)
		{
			if (Timetable[a]->getDuration().getDOW() == 2)
			{
				cout << Timetable[a];
			}
			cout << endl;
		}
	}
	else
	{
		cout << "No data for Tuesday is entered" << endl;
	}
}
void printWed()
{
	if (WedEntered == true)
	{
		for (unsigned a = 0; a < Timetable.size(); ++a)
		{
			if (Timetable[a]->getDuration().getDOW() == 3)
			{
				cout << Timetable[a];
			}
			cout << endl;
		}
	}
	else
	{
		cout << "No data for Wednesday is entered" << endl;
	}
}
void printThur()
{
	if (ThurEntered == true)
	{
		for (unsigned a = 0; a < Timetable.size(); ++a)
		{
			if (Timetable[a]->getDuration().getDOW() == 4)
			{
				cout << Timetable[a];;
			}
			cout << endl;
		}
	}
	else
	{
		cout << "No data for Thursday is entered" << endl;
	}
}
void printFri()
{
	if (FriEntered == true)
	{
		for (unsigned a = 0; a < Timetable.size(); ++a)
		{
			if (Timetable[a]->getDuration().getDOW() == 5)
			{
				cout << Timetable[a];;
			}
			cout << endl;
		}
	}
	else
	{
		cout << "No data for Friday is entered" << endl;
	}
}
void DetermineDay()
{
	//Determining the Day
	if ((mon_hour * 60) + mon_min != 540)
	{
		day = 1;
	}
	else if ((mon_hour * 60) + mon_min == 540 &&
		(tue_hour * 60) + tue_min != 540)
	{
		day = 2;
	}
	else if ((mon_hour * 60) + mon_min == 540 &&
		(tue_hour * 60) + tue_min == 540 &&
		(wed_hour * 60) + wed_min != 540)
	{
		day = 3;
	}
	else if ((mon_hour * 60) + mon_min == 540 &&
		(tue_hour * 60) + tue_min == 540 &&
		(wed_hour * 60) + wed_min == 540 &&
		(thur_hour * 60) + thur_min != 540)
	{
		day = 4;
	}
	else
	{
		day = 5;
	}
}

void input_mon()
{
	day = 1;

	mon_hour += input_hour;
	mon_min += input_min;

	hourToSet = mon_hour;
	minToSet = mon_min;

	MonEntered = true;
}
void input_tue()
{
	day = 2;

	tue_hour += input_hour;
	tue_min += input_min;

	hourToSet = tue_hour;
	minToSet = tue_min;

	TueEntered = true;
}
void input_wed()
{
	day = 3;

	wed_hour += input_hour;
	wed_min += input_min;

	hourToSet = wed_hour;
	minToSet = wed_min;

	WedEntered = true;
}
void input_thur()
{
	day = 4;

	thur_hour += input_hour;
	thur_min += input_min;

	hourToSet = thur_hour;
	minToSet = thur_min;

	ThurEntered = true;
}
void input_fri()
{
	day = 5;

	fri_hour += input_hour;
	fri_min += input_min;

	hourToSet = fri_hour;
	minToSet = fri_min;

	FriEntered = true;
}

void AddTime()
{
	cout << "Please enter your Module Code" << endl;
	cin.ignore();
	getline(cin, newCode);

	cout << "Please enter the duration(Hour)" << endl;
	cin >> input_hour;

	cout << "Please enter the duration(Minute)" << endl;
	cin >> input_min;
}

//Get Start time(hr:min)
//pass in Duration(hr:min)
void main()
{
	while(true)
	{
		cout << "Please enter your choice \n1)Add data \n2)Check Timetable \n3)Exit" << endl;
		cin >> choice1;

		if (choice1 == 1)
		{
			DetermineDay();

			AddTime();

			//Converting input to min
			input_total = (input_hour * 60) + input_min;

			//Input time is more than 9 hrs which will not fit into any timetable at all
			while(input_total > 540)
			{
				cout << "Error, please enter again" << endl << endl;
				AddTime();

			}

			//After i set all parameters, i change the new start timing accordingly
			switch(day)
			{
			case(1):

				freeTime = 540 - (mon_hour * 60) + mon_min;

				//InputTime is more than freeTime
				if (input_total > freeTime)
				{
					cout << "Timing exceeded, it will be moved to the next day" << endl;
					input_tue();
				}
				else
				{
					input_mon();
				}
				break;

			case(2):
				freeTime = 540 - (tue_hour * 60) + tue_min;

				if (input_total > freeTime)
				{
					cout << "Timing exceeded, it will be moved to the next day" << endl;
					input_wed();
				}
				else
				{
					input_tue();
				}
				break;

			case(3):
				freeTime = 540 - (wed_hour * 60) + wed_min;

				//InputTime is more than freeTime
				if (input_total > freeTime)
				{
					cout << "Timing exceeded, it will be moved to the next day" << endl;
					input_thur();
				}
				else
				{
					input_wed();
				}
				break;

			case(4):
				freeTime = 540 - (thur_hour * 60) + thur_min;

				//InputTime is more than freeTime
				if (input_total > freeTime)
				{
					cout << "Timing exceeded, it will be moved to the next day" << endl;
					input_fri();
				}
				else
				{
					input_thur();
				}
				break;

			case(5):
				freeTime = 540 - (fri_hour * 60) + fri_min;

				//InputTime is more than freeTime
				if (input_total > freeTime)
				{
					cout << "Error, please enter again" << endl << endl;
					AddTime();
				}
				else
				{
					input_fri();
				}
				break;
			}

			//Overload and set all the parameters
			newModule = new CModule(newCode, hourToSet, minToSet, input_hour, input_min, day);
			Timetable.push_back(newModule);
		}
		else if (choice1 == 2)
		{
			cout << "Please enter your choice \n1)Monday \n2)Tuesday \n3)Wednesday \n4)Thursday \n5)Friday \n6)All" << endl;
			cin >> choice2;

			switch(choice2)
			{
			case(1):
				printMon();
				break;

			case(2):
				printTue();
				break;

			case(3):
				printWed();
				break;

			case(4):
				printThur();
				break;

			case(5):
				printFri();
				break;

			case(6):
				printMon();
				printTue();
				printWed();
				printThur();
				printFri();
				break;
			}
		}
		else
		{
			break;
		}

		system("pause");
	}
}