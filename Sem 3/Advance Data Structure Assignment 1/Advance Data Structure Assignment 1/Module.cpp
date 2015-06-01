#include "Module.h"

int CModule::mon_hour = 0;
int CModule::mon_min = 0;
int CModule::tue_hour = 0;
int CModule::tue_min = 0;
int CModule::wed_hour = 0;
int CModule::wed_min = 0;
int CModule::thur_hour = 0;
int CModule::thur_min = 0;
int CModule::fri_hour = 0;
int CModule::fri_min = 0;
int CModule::day2 = 1;
int CModule::input_hour = 0;
int CModule::input_min = 0;
int CModule::input_total = 0;
int CModule::freeTime = 0;
int CModule::hourToSet = 0;
int CModule::minToSet = 0;
string CModule::newCode = "";

int oldStart_hour = 0;
int oldStart_min = 0;


string dayForWeek[6] = {"", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
string daysToPrint = "";

CModule::CModule(void)
{
}

CModule::CModule(string moduleCode, int start_hour, int start_min, int d_hour, int d_min, int dayofWeek)
{
	this->moduleCode = moduleCode;
	this->duration.setTime(d_hour, d_min, start_hour, start_min, dayofWeek);
}

CModule::~CModule(void)
{
}

int CModule::getDay()
{
	return this->day;
}

CTimeType CModule::getDuration()
{
	return this->duration;
}

void CModule::DetermineDay()
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

void CModule::updateTiming_Mon(CModule* passIn)
{
	freeTime = 540 - (passIn->mon_hour * 60) + passIn->mon_min;

	//InputTime is more than freeTime
	if (input_total > freeTime)
	{
		cout << "Timing exceeded, it will be moved to the next day" << endl;
		passIn->day = 2;

		passIn->tue_hour += passIn->input_hour;
		passIn->tue_min += passIn->input_min;

		passIn->hourToSet = passIn->tue_hour;
		passIn->minToSet = passIn->tue_min;
	}
	else
	{
		passIn->day = 1;

		passIn->mon_hour += passIn->input_hour;
		passIn->mon_min += passIn->input_min;

		passIn->hourToSet = passIn->mon_hour;
		passIn->minToSet = passIn->mon_min;
	}
}

void CModule::updateTiming_Mon(CModule* passIn)
{
	freeTime = 540 - (passIn->tue_hour * 60) + passIn->tue_min;

	//InputTime is more than freeTime
	if (input_total > freeTime)
	{
		cout << "Timing exceeded, it will be moved to the next day" << endl;
		passIn->day = 3;

		passIn->wed_hour += passIn->input_hour;
		passIn->wed_min += passIn->input_min;

		passIn->hourToSet = passIn->wed_hour;
		passIn->minToSet = passIn->wed_min;
	}
	else
	{
		passIn->day = 2;

		passIn->tue_hour += passIn->input_hour;
		passIn->tue_min += passIn->input_min;

		passIn->hourToSet = passIn->tue_hour;
		passIn->minToSet = passIn->tue_min;
	}
}

//Operator Overload
bool CModule::operator! () const
{
	return true;
}

ostream & operator<<(ostream & output, CModule* & passIn) 
{
	oldStart_hour = (9 + passIn->duration.getStartHour()) - passIn->duration.getHour();
	oldStart_min = passIn->duration.getStartMin() - passIn->duration.getMinute();
	daysToPrint = dayForWeek[passIn->duration.getDOW()];

	output << "Day: " << daysToPrint << endl;
	output << "Module Code: " << passIn->moduleCode << endl;;
	output << "Duration(Hr:Min): " << passIn->duration.getHour() << ":" << passIn->duration.getMinute() << endl;
	output << "Module Duration: " << oldStart_hour << ":" << oldStart_min << " - " << 9 + passIn->duration.getStartHour() << ":" << passIn->duration.getStartMin() << endl;

	return output;
}

istream & operator>>(istream & input, CModule* & passIn)
{
	passIn->DetermineDay();

	cout << "Please enter your Module Code" << endl;
	cin.ignore();
	getline(input, passIn->newCode);

	cout << "Please enter the duration(Hour)" << endl;
	input >> passIn->input_hour;

	cout << "Please enter the duration(Minute)" << endl;
	input >> passIn->input_min;

	//Converting input to min
	static int input_total = (passIn->input_hour * 60) + passIn->input_min;

	//Input time is more than 9 hrs which will not fit into any timetable at all
	while (input_total > 540)
	{
		cout << "Error, please enter again" << endl << endl;
		cout << "Please enter the duration(Hour)" << endl;
		input >> passIn->input_hour;

		cout << "Please enter the duration(Minute)" << endl;
		input >> passIn->input_min;
	}

	//Update new timing
	switch (passIn->day)
	{
	case(1) :
		passIn->updateTiming_Mon(passIn);
		break;
	case(2) :

		break;
	}


	return input;
}
