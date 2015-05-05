#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include "Module.h"
#include "ModuleTime.h"
#include "ModuleInfo.h"


using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::istream;
using std::vector; 
using std::stoi;
using std::to_string;

//Variables
CModuleTime mTime;
CModuleInfo mInfo;
CModule newEntry;
vector<CModule> Monday, Tuesday, Wednesday, Thursday, Friday;
int choice = -1;
int choice2 = -1;
int choice3 = -1;
unsigned totalTime_min;
string data[9] = {"01", "02", "03", "04", "05", "06", "07", "08", "09"};
string zero = "00";

void ErrorCheckingForInput()
{
	cout << "Error, timing exceeded!" << endl;
	cout << "Please enter again" << endl;
	cin >> mTime;
}
void AddNewDataToMonday()
{
	if (!Monday.empty())
	{
		static unsigned hour = 17 - Monday[Monday.size() - 1].returnModuleEndTime_Hour();
		static unsigned minute = 60 - Monday[Monday.size() - 1].returnModuleEndTime_Minute();
		totalTime_min = (hour * 60) + minute;
		cout << totalTime_min << endl;
		if (totalTime_min > 540)
		{
			ErrorCheckingForInput();
		}
	}
	else
	{
		totalTime_min = (mTime.returnHour() * 60) + mTime.returnMinute();//Converting everything to min
		if(totalTime_min > 540)
		{
			ErrorCheckingForInput();
		}
	}

	newEntry.setParameters(mTime.returnHour(), mTime.returnMinute(), mInfo.returnModuleCode(), mInfo.returnModuleName());
	Monday.push_back(newEntry);
	if (Monday.size() > 1)
	{
		Monday[Monday.size() - 1].setModuleStartTime_Hour(Monday[Monday.size() - 2].returnModuleEndTime_Hour());
		Monday[Monday.size() - 1].setModuleStartTime_Minute(Monday[Monday.size() - 2].returnModuleEndTime_Minute());
	}

	Monday[Monday.size() - 1].setModuleEndTime_Hour(Monday[Monday.size() - 1].returnModuleStartTime_Hour() + Monday[Monday.size() - 1].returnHour());
	Monday[Monday.size() - 1].setModuleEndTime_Minute(Monday[Monday.size() - 1].returnModuleStartTime_Minute() + Monday[Monday.size() - 1].returnMinute());
}
void AddNewDataToTuesday()
{
	if (!Tuesday.empty())
	{
		static unsigned hour = 17 - Tuesday[Tuesday.size() - 1].returnModuleEndTime_Hour();
		static unsigned minute = 60 - Tuesday[Tuesday.size() - 1].returnModuleEndTime_Minute();
		totalTime_min = (hour * 60) + minute;
		cout << totalTime_min << endl;
		if (totalTime_min > 540)
		{
			ErrorCheckingForInput();
		}
	}
	else
	{
		totalTime_min = (mTime.returnHour() * 60) + mTime.returnMinute();//Converting everything to min
		if(totalTime_min > 540)
		{
			ErrorCheckingForInput();
		}
	}

	newEntry.setParameters(mTime.returnHour(), mTime.returnMinute(), mInfo.returnModuleCode(), mInfo.returnModuleName());
	Tuesday.push_back(newEntry);
	if (Tuesday.size() > 1)
	{
		Tuesday[Tuesday.size() - 1].setModuleStartTime_Hour(Tuesday[Tuesday.size() - 2].returnModuleEndTime_Hour());
		Tuesday[Tuesday.size() - 1].setModuleStartTime_Minute(Tuesday[Tuesday.size() - 2].returnModuleEndTime_Minute());
	}

	Tuesday[Tuesday.size() - 1].setModuleEndTime_Hour(Tuesday[Tuesday.size() - 1].returnModuleStartTime_Hour() + Tuesday[Tuesday.size() - 1].returnHour());
	Tuesday[Tuesday.size() - 1].setModuleEndTime_Minute(Tuesday[Tuesday.size() - 1].returnModuleStartTime_Minute() + Tuesday[Tuesday.size() - 1].returnMinute());
}
void AddNewDataToWednesday()
{
	if (!Wednesday.empty())
	{
		static unsigned hour = 17 - Wednesday[Wednesday.size() - 1].returnModuleEndTime_Hour();
		static unsigned minute = 60 - Wednesday[Wednesday.size() - 1].returnModuleEndTime_Minute();
		totalTime_min = (hour * 60) + minute;
		cout << totalTime_min << endl;
		if (totalTime_min > 540)
		{
			ErrorCheckingForInput();
		}
	}
	else
	{
		totalTime_min = (mTime.returnHour() * 60) + mTime.returnMinute();//Converting everything to min
		if(totalTime_min > 540)
		{
			ErrorCheckingForInput();
		}
	}

	newEntry.setParameters(mTime.returnHour(), mTime.returnMinute(), mInfo.returnModuleCode(), mInfo.returnModuleName());
	Wednesday.push_back(newEntry);
	if (Wednesday.size() > 1)
	{
		Wednesday[Wednesday.size() - 1].setModuleStartTime_Hour(Wednesday[Wednesday.size() - 2].returnModuleEndTime_Hour());
		Wednesday[Wednesday.size() - 1].setModuleStartTime_Minute(Wednesday[Wednesday.size() - 2].returnModuleEndTime_Minute());
	}

	Wednesday[Wednesday.size() - 1].setModuleEndTime_Hour(Wednesday[Wednesday.size() - 1].returnModuleStartTime_Hour() + Wednesday[Wednesday.size() - 1].returnHour());
	Wednesday[Wednesday.size() - 1].setModuleEndTime_Minute(Wednesday[Wednesday.size() - 1].returnModuleStartTime_Minute() + Wednesday[Wednesday.size() - 1].returnMinute());
}
void AddNewDataToThursday()
{
	if (!Thursday.empty())
	{
		static unsigned hour = 17 - Thursday[Wednesday.size() - 1].returnModuleEndTime_Hour();
		static unsigned minute = 60 - Thursday[Wednesday.size() - 1].returnModuleEndTime_Minute();
		totalTime_min = (hour * 60) + minute;
		cout << totalTime_min << endl;
		if (totalTime_min > 540)
		{
			ErrorCheckingForInput();
		}
	}
	else
	{
		totalTime_min = (mTime.returnHour() * 60) + mTime.returnMinute();//Converting everything to min
		if(totalTime_min > 540)
		{
			ErrorCheckingForInput();
		}
	}

	newEntry.setParameters(mTime.returnHour(), mTime.returnMinute(), mInfo.returnModuleCode(), mInfo.returnModuleName());
	Thursday.push_back(newEntry);
	if (Thursday.size() > 1)
	{
		Thursday[Thursday.size() - 1].setModuleStartTime_Hour(Thursday[Thursday.size() - 2].returnModuleEndTime_Hour());
		Thursday[Thursday.size() - 1].setModuleStartTime_Minute(Thursday[Thursday.size() - 2].returnModuleEndTime_Minute());
	}

	Thursday[Thursday.size() - 1].setModuleEndTime_Hour(Thursday[Tuesday.size() - 1].returnModuleStartTime_Hour() + Thursday[Thursday.size() - 1].returnHour());
	Thursday[Thursday.size() - 1].setModuleEndTime_Minute(Thursday[Tuesday.size() - 1].returnModuleStartTime_Minute() + Thursday[Thursday.size() - 1].returnMinute());
}
void AddNewDataToFriday()
{
	if (!Friday.empty())
	{
		static unsigned hour = 17 - Friday[Friday.size() - 1].returnModuleEndTime_Hour();
		static unsigned minute = 60 - Friday[Friday.size() - 1].returnModuleEndTime_Minute();
		totalTime_min = (hour * 60) + minute;
		cout << totalTime_min << endl;
		if (totalTime_min > 540)
		{
			ErrorCheckingForInput();
		}
	}
	else
	{
		totalTime_min = (mTime.returnHour() * 60) + mTime.returnMinute();//Converting everything to min
		if(totalTime_min > 540)
		{
			ErrorCheckingForInput();
		}
	}

	newEntry.setParameters(mTime.returnHour(), mTime.returnMinute(), mInfo.returnModuleCode(), mInfo.returnModuleName());
	Friday.push_back(newEntry);
	if (Friday.size() > 1)
	{
		Friday[Thursday.size() - 1].setModuleStartTime_Hour(Friday[Friday.size() - 2].returnModuleEndTime_Hour());
		Friday[Thursday.size() - 1].setModuleStartTime_Minute(Friday[Friday.size() - 2].returnModuleEndTime_Minute());
	}

	Friday[Friday.size() - 1].setModuleEndTime_Hour(Friday[Friday.size() - 1].returnModuleStartTime_Hour() + Friday[Friday.size() - 1].returnHour());
	Friday[Friday.size() - 1].setModuleEndTime_Minute(Friday[Friday.size() - 1].returnModuleStartTime_Minute() + Friday[Friday.size() - 1].returnMinute());
}
ostream & operator<< (ostream & output, vector<CModule> & passIn)
{
	system("cls");

	string hour = "";
	string minute = "";
	string moduleStartTime_Hour = "";
	string moduleStartTime_Minute = "";
	string moduleEndTime_Hour = "";
	string moduleEndTime_Minute = "";

	output << "You have entered" << endl;
	for (unsigned a = 0; a < passIn.size(); ++a)
	{

		//Checking hour
		if (passIn[a].returnHour() < 10 && passIn[a].returnHour() > 0)
		{
			hour = data[passIn[a].returnHour() - 1];
		}
		else if (passIn[a].returnHour() == 0)
		{
			hour = zero;
		}
		else
		{
			hour = to_string((long long)passIn[a].returnHour());
		}

		//Checking minute
		if (passIn[a].returnMinute() < 10 && passIn[a].returnMinute() > 0)
		{
			minute = data[passIn[a].returnMinute() - 1];
		}
		else if (passIn[a].returnMinute() == 0)
		{
			minute = zero;
		}
		else
		{
			minute = to_string((long long)passIn[a].returnMinute());
		}

		//Checking Module start time in hour
		if(passIn[a].returnModuleStartTime_Hour() < 10 && passIn[a].returnModuleStartTime_Hour() > 0)
		{
			moduleStartTime_Hour = data[passIn[a].returnModuleStartTime_Hour() - 1];
		}
		else if (passIn[a].returnModuleStartTime_Hour() == 0)
		{
			moduleStartTime_Hour = zero;
		}
		else
		{
			moduleStartTime_Hour = to_string((long long)passIn[a].returnModuleStartTime_Hour());
		}

		//Chcking Module start time in minute
		if(passIn[a].returnModuleStartTime_Minute() < 10 && passIn[a].returnModuleStartTime_Minute() > 0)
		{
			moduleStartTime_Minute = data[passIn[a].returnModuleStartTime_Minute() - 1];
		}
		else if (passIn[a].returnModuleStartTime_Minute() == 0)
		{
			moduleStartTime_Minute = zero;
		}
		else
		{
			moduleStartTime_Minute = to_string((long long)passIn[a].returnModuleStartTime_Minute());
		}

		//Checking Module end time in hour
		if(passIn[a].returnModuleEndTime_Hour() < 10 && passIn[a].returnModuleEndTime_Hour() > 0)
		{
			moduleEndTime_Hour = data[passIn[a].returnModuleEndTime_Hour() - 1];
		}
		else if (passIn[a].returnModuleEndTime_Hour() == 0)
		{
			moduleEndTime_Hour = zero;
		}
		else
		{
			moduleEndTime_Hour = to_string((long long)passIn[a].returnModuleEndTime_Hour());
		}

		//Chcking Module end time in minute
		if(passIn[a].returnModuleEndTime_Minute() < 10 && passIn[a].returnModuleEndTime_Minute() > 0)
		{
			moduleEndTime_Minute = data[passIn[a].returnModuleEndTime_Minute() - 1];
		}
		else if (passIn[a].returnModuleEndTime_Minute() == 0)
		{
			moduleEndTime_Minute = zero;
		}
		else
		{
			moduleEndTime_Minute = to_string((long long)passIn[a].returnModuleEndTime_Minute());
		}

		//================Output==============//
		output << "Module Code: " <<  passIn[a].returnMCode() << endl;
		output << "Module Name: " << passIn[a].returnMName() << endl;
		output << "Module Duration (Hr:Min): " << hour << ":" << minute << endl;
		output << "Module start at (Hr:Min): " << moduleStartTime_Hour << ":" << moduleStartTime_Minute << endl;
		output << "Module ends at (Hr:Min): " << moduleEndTime_Hour << ":" << moduleEndTime_Minute << endl;
		cout << endl;
	}

	return output;
}
void newData()
{
	cout << "Which day? \n1)Monday \n2)Tuesday \n3)Wednesday \n4)Thursday \n5)Friday" << endl;
	cin >> choice3;
	cin >> mInfo;
	cin >> mTime;
	
	while(choice3 < 1 || choice3 > 5)
	{
		cout << "Error, please enter the correct value" << endl;
		cin >> choice3;
	}

	//=======Monday=========//
	if (choice3 == 1)
	{
		AddNewDataToMonday();
	}
	//=======Tuesday=========//
	else if (choice3 == 2)
	{
		AddNewDataToTuesday();
	}
	//=======Wednesday=========//
	else if (choice3 == 3)
	{
		AddNewDataToWednesday();
	}
	//=======Thursday=========//
	else if (choice3 == 4)
	{
		AddNewDataToThursday();
	}
	//=======Friday=========//
	else
	{
		AddNewDataToFriday();
	}
}
void Choices()
{
	cout << "Please enter your choice\n1)Add \n2)Check Timetable \n3)Exit" << endl;
	cin >> choice;

	while(choice < 1 || choice > 3)
	{
		cout << "Error, please enter the correct value" << endl;
		cin >> choice;
	}
}
void Choices2()
{
	cout << "Which day? \n1)Monday \n2)Tuesday \n3)Wednesday \n4)Thursday \n5)Friday" << endl;
	cin >> choice2;

	while(choice2 < 1 || choice2 > 5)
	{
		cout << "Error, please enter the correct value" << endl;
		cin >> choice2;
	}

	//=======Monday=========//
	if (choice2 == 1)
	{
		if (!Monday.empty())
		{
			cout << Monday;
		}
		else
			cout << "No data entered for Monday" << endl;
	}
	//=======Tuesday=========//
	else if (choice2 == 2)
	{
		if (!Tuesday.empty())
			cout << Tuesday;
		else
			cout << "No data entered for Tuesday" << endl;
	}
	//=======Wednesday=========//
	else if (choice2 == 3)
	{
		if (!Wednesday.empty())
			cout << Wednesday;
		else
			cout << "No data entered fro Wednesday" << endl;
	}
	//=======Thursday=========//
	else if (choice2 == 4)
	{
		if (!Thursday.empty())
			cout << Thursday;
		else
			cout << "No data entered for Thursday" << endl;
	}
	//=======Friday=========//
	else
	{
		if (!Friday.empty())
			cout << Friday;
		else
			cout << "No data entered for Friday" << endl;
	}
}


void main()
{
	do
	{
		choice = -1;//Reset choice input
		choice2 = -1;
		choice3 = -1;

		system("cls");

		Choices();

		if (choice == 1)
		{
			system("cls");

			newData();

		}
		else if (choice == 2)
		{
			system("cls");

			Choices2();
		}
		system("pause");
	}
	while(choice != 3);

}