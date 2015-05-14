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
vector<CModule> Mon, Tue, Wed, Thurs, Fri;
int choice = -1;
int choice2 = -1;
int choice3 = -1;
unsigned totalTime_min;
string data[9] = {"01", "02", "03", "04", "05", "06", "07", "08", "09"};
string zero = "00";
unsigned minute = 0;
unsigned hour = 0;

void ErrorCheckingForInput()
{
	cout << "Error, timing exceeded!" << endl;
	cout << "Please enter again" << endl;
	cin >> mTime;
}
void AddNewDataToMonday()
{
	if (!Mon.empty())
	{
		hour =  Mon[Mon.size() - 1].returnModuleEndTime_Hour() - 9;
		minute = Mon[Mon.size() - 1].returnModuleEndTime_Minute();
		totalTime_min = (hour * 60) + minute + (mTime.returnHour() * 60) + mTime.returnMinute();
		cout << totalTime_min << endl;
		while (totalTime_min > 1080)
		{
			totalTime_min = (hour * 60) + minute + (mTime.returnHour() * 60) + mTime.returnMinute();
			ErrorCheckingForInput();
		}
	}
	else
	{
		totalTime_min = (mTime.returnHour() * 60) + mTime.returnMinute();//Converting everything to min

		while(totalTime_min > 1080)
		{
			totalTime_min = (mTime.returnHour() * 60) + mTime.returnMinute();
			ErrorCheckingForInput();
		}
	}

	newEntry.setParameters(mTime.returnHour(), mTime.returnMinute(), mInfo.returnModuleCode(), mInfo.returnModuleName());
	Mon.push_back(newEntry);
	if (Mon.size() > 1)
	{
		Mon[Mon.size() - 1].setModuleStartTime_Hour(Mon[Mon.size() - 2].returnModuleEndTime_Hour());
		Mon[Mon.size() - 1].setModuleStartTime_Minute(Mon[Mon.size() - 2].returnModuleEndTime_Minute());
	}

	Mon[Mon.size() - 1].setEndTime_Hour(Mon[Mon.size() - 1].returnStartTime_Hour() + Mon[Mon.size() - 1].returnHour());
	Mon[Mon.size() - 1].setEndTime_Minute(Mon[Mon.size()-1].returnEndTime_Minute() + Mon[Mon.size() - 1].returnMinute());
}
void AddNewDataToTuesday()
{
	if (!Tue.empty())
	{
		hour = 17 - Tue[Tue.size() - 1].returnModuleEndTime_Hour();
		minute = 60 - Tue[Tue.size() - 1].returnModuleEndTime_Minute();
		totalTime_min = (hour * 60) + minute;

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
	Tue.push_back(newEntry);
	if (Tue.size() > 1)
	{
		Tue[Tue.size() - 1].setModuleStartTime_Hour(Tue[Tue.size() - 2].returnModuleEndTime_Hour());
		Tue[Tue.size() - 1].setModuleStartTime_Minute(Tue[Tue.size() - 2].returnModuleEndTime_Minute());
	}

	Tue[Tue.size() - 1].setEndTime_Hour(Tue[Tue.size() - 1].returnStartTime_Hour() + Tue[Tue.size() - 1].returnHour());
	Tue[Tue.size() - 1].setEndTime_Minute(Tue[Tue.size() - 1].returnEndTime_Minute() + Tue[Tue.size() - 1].returnMinute());
}
void AddNewDataToWednesday()
{
	if (!Wed.empty())
	{
		hour = 17 - Wed[Wed.size() - 1].returnModuleEndTime_Hour();
		minute = 60 - Wed[Wed.size() - 1].returnModuleEndTime_Minute();
		totalTime_min = (hour * 60) + minute;

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
	Wed.push_back(newEntry);
	if (Wed.size() > 1)
	{
		Wed[Wed.size() - 1].setModuleStartTime_Hour(Wed[Wed.size() - 2].returnModuleEndTime_Hour());
		Wed[Wed.size() - 1].setModuleStartTime_Minute(Wed[Wed.size() - 2].returnModuleEndTime_Minute());
	}

	Wed[Wed.size() - 1].setEndTime_Hour(Wed[Wed.size() - 1].returnStartTime_Hour() + Wed[Wed.size() - 1].returnHour());
	Wed[Wed.size() - 1].setEndTime_Minute(Wed[Wed.size() - 1].returnEndTime_Minute() + Wed[Wed.size() - 1].returnMinute());
}
void AddNewDataToThursday()
{
	if (!Thurs.empty())
	{
		hour = 17 - Thurs[Wed.size() - 1].returnModuleEndTime_Hour();
		minute = 60 - Thurs[Wed.size() - 1].returnModuleEndTime_Minute();
		totalTime_min = (hour * 60) + minute;

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
	Thurs.push_back(newEntry);
	if (Thurs.size() > 1)
	{
		Thurs[Thurs.size() - 1].setModuleStartTime_Hour(Thurs[Thurs.size() - 2].returnModuleEndTime_Hour());
		Thurs[Thurs.size() - 1].setModuleStartTime_Minute(Thurs[Thurs.size() - 2].returnModuleEndTime_Minute());
	}

	Thurs[Thurs.size() - 1].setEndTime_Hour(Thurs[Tue.size() - 1].returnStartTime_Hour() + Thurs[Thurs.size() - 1].returnHour());
	Thurs[Thurs.size() - 1].setEndTime_Minute(Thurs[Tue.size() - 1].returnEndTime_Minute() + Thurs[Thurs.size() - 1].returnMinute());
}
void AddNewDataToFriday()
{
	if (!Fri.empty())
	{
		hour = 17 - Fri[Fri.size() - 1].returnModuleEndTime_Hour();
		minute = 60 - Fri[Fri.size() - 1].returnModuleEndTime_Minute();
		totalTime_min = (hour * 60) + minute;

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
	Fri.push_back(newEntry);
	if (Fri.size() > 1)
	{
		Fri[Fri.size() - 1].setModuleStartTime_Hour(Fri[Fri.size() - 2].returnModuleEndTime_Hour());
		Fri[Fri.size() - 1].setModuleStartTime_Minute(Fri[Fri.size() - 2].returnModuleEndTime_Minute());
	}

	Fri[Fri.size() - 1].setEndTime_Hour(Fri[Fri.size() - 1].returnStartTime_Hour() + Fri[Fri.size() - 1].returnHour());
	Fri[Fri.size() - 1].setEndTime_Minute(Fri[Fri.size() - 1].returnEndTime_Minute() + Fri[Fri.size() - 1].returnMinute());
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
		if(passIn[a].returnStartTime_Hour() < 10 && passIn[a].returnStartTime_Hour() > 0)
		{
			moduleStartTime_Hour = data[passIn[a].returnStartTime_Hour() - 1];
		}
		else if (passIn[a].returnStartTime_Hour() == 0)
		{
			moduleStartTime_Hour = zero;
		}
		else
		{
			moduleStartTime_Hour = to_string((long long)passIn[a].returnStartTime_Hour());
		}

		//Chcking Module start time in minute
		if(passIn[a].returnEndTime_Minute() < 10 && passIn[a].returnEndTime_Minute() > 0)
		{
			moduleStartTime_Minute = data[passIn[a].returnEndTime_Minute() - 1];
		}
		else if (passIn[a].returnEndTime_Minute() == 0)
		{
			moduleStartTime_Minute = zero;
		}
		else
		{
			moduleStartTime_Minute = to_string((long long)passIn[a].returnEndTime_Minute());
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
	cout << "Which day? \n1)Mon \n2)Tue \n3)Wed \n4)Thurs \n5)Fri" << endl;
	cin >> choice3;
	cin >> mInfo;
	cin >> mTime;
	
	while(choice3 < 1 || choice3 > 5)
	{
		cout << "Error, please enter the correct value" << endl;
		cin >> choice3;
	}

	//=======Mon=========//
	if (choice3 == 1)
	{
		AddNewDataToMonday();
	}
	//=======Tue=========//
	else if (choice3 == 2)
	{
		AddNewDataToTuesday();
	}
	//=======Wed=========//
	else if (choice3 == 3)
	{
		AddNewDataToWednesday();
	}
	//=======Thurs=========//
	else if (choice3 == 4)
	{
		AddNewDataToThursday();
	}
	//=======Fri=========//
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
void Print()
{
	cout << "Which day? \n1)Mon \n2)Tue \n3)Wed \n4)Thurs \n5)Fri" << endl;
	cin >> choice2;

	while(choice2 < 1 || choice2 > 5)
	{
		cout << "Error, please enter the correct value" << endl;
		cin >> choice2;
	}

	//=======Mon=========//
	if (choice2 == 1)
	{
		if (!Mon.empty())
		{
			cout << Mon;
		}
		else
			cout << "No data entered for Mon" << endl;
	}
	//=======Tue=========//
	else if (choice2 == 2)
	{
		if (!Tue.empty())
			cout << Tue;
		else
			cout << "No data entered for Tue" << endl;
	}
	//=======Wed=========//
	else if (choice2 == 3)
	{
		if (!Wed.empty())
			cout << Wed;
		else
			cout << "No data entered for Wed" << endl;
	}
	//=======Thurs=========//
	else if (choice2 == 4)
	{
		if (!Thurs.empty())
			cout << Thurs;
		else
			cout << "No data entered for Thurs" << endl;
	}
	//=======Fri=========//
	else
	{
		if (!Fri.empty())
			cout << Fri;
		else
			cout << "No data entered for Fri" << endl;
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
		
		system("cls");
		if (choice == 1)
		{
			newData();
		}
		else if (choice == 2)
		{
			Print();
		}
		system("pause");
	}
	while(choice != 3);

}