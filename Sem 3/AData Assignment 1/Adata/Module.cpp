#include "Module.h"

int CModule::mon_hr = 0;
int CModule::tue_hr = 0;
int CModule::wed_hr = 0;
int CModule::thur_hr = 0;
int CModule::fri_hr = 0;
int CModule::mon_min = 0;
int CModule::tue_min = 0;
int CModule::wed_min = 0;
int CModule::thur_min = 0;
int CModule::fri_min = 0;
bool CModule::full = false;

int temp_hr = 0;
int temp_min = 0;
int temp_TTime = 0;
string temp_code;

string DayToPrint[6] = {"", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};

CModule::CModule(void)
{
}


CModule::~CModule(void)
{
}

void CModule::determineDay()
{
	int mon_Time = (mon_hr * 60) + mon_min;
	int tue_Time = (tue_hr * 60) + tue_min;
	int wed_Time = (wed_hr * 60) + wed_min;
	int thur_Time = (thur_hr * 60) + thur_min;
	int fri_Time = (fri_hr * 60) + fri_min;

	if(mon_Time != 540)
	{
		day.dayOfWeek = 1;
	}
	else if(mon_Time == 540 && tue_Time != 540)
	{
		day.dayOfWeek = 2;
	}
	else if(mon_Time == 540 && tue_Time == 540 && wed_Time != 540)
	{
		day.dayOfWeek = 3;
	}
	else if(mon_Time == 540 && tue_Time == 540 && wed_Time == 540 && thur_Time != 540)
	{
		day.dayOfWeek = 4;
	}
	else if(mon_Time == 540 && tue_Time == 540 && wed_Time == 540 && thur_Time == 540 && fri_Time != 540)
	{
		day.dayOfWeek = 5;
	}
}

void CModule::setData(string moduleCode, int start_hour, int start_min, int hour, int min, int dayofWeek)
{
	this->newCode = moduleCode;
	this->day.setTime(start_hour, start_min, hour, min, dayofWeek);
}

bool CModule::getFull()
{
	return this->full;
}

bool CModule::operator!() const
{
	int freeTime;

	if(day.dayOfWeek == 1)
	{
		freeTime = 540 - ((60 * mon_hr) + mon_min);
	}
	else if(day.dayOfWeek == 2)
	{
		freeTime = 540 - ((60 * tue_hr) + tue_min);
	}
	else if(day.dayOfWeek == 3)
	{
		freeTime = 540 - ((60 * wed_hr) + wed_min);
	}
	else if(day.dayOfWeek == 4)
	{
		freeTime = 540 - ((60 * thur_hr) + thur_min);
	}
	else if(day.dayOfWeek == 5)
	{
		freeTime = 540 - ((60 * fri_hr) + fri_min);
	}

	if(temp_TTime <= freeTime) //Within free time
		return true;
	else
		return false;
}

istream& operator>>(istream& input, CModule* passIn)
{
	passIn->determineDay();

	cout << DayToPrint[passIn->day.dayOfWeek] << endl;

	cout << "Please enter your Module Code" << endl;
	cin.ignore();
	getline(input, temp_code);

	cout << "Please enter your Module Duration(Hour)" << endl;
	input >> temp_hr;

	cout << "Please enter your Module Duration(Min)" << endl;
	input >> temp_min;

	//Converting everything to min
	temp_TTime = (temp_hr * 60) + temp_min;

	//Check if time entered is more than 9 hours
	while(temp_TTime > 540)
	{
		cout << "Error, please enter again" << endl;

		cout << "Please enter your Module Duration(Hour)" << endl;
		input >> temp_hr;

		cout << "Please enter your Module Duration(Min)" << endl;
		input >> temp_min;

		temp_TTime = (temp_hr * 60) + temp_min;
	}

	while(temp_min >= 60)
	{
		temp_min -= 60;
		temp_hr += 1;
	}

	int hourToSet = 0;
	int minToSet = 0;

	switch(passIn->day.dayOfWeek)
	{
	case(1):
		if(!*passIn == true)
		{
			passIn->day.dayOfWeek = 1;
			hourToSet = passIn->mon_hr;
			minToSet = passIn->mon_min;
			passIn->mon_hr += temp_hr;
			passIn->mon_min += temp_min;
		}
		else
		{
			passIn->day.dayOfWeek = 2;
			hourToSet = passIn->tue_hr;
			minToSet = passIn->tue_min;
			passIn->tue_hr += temp_hr;
			passIn->tue_min += temp_min;
		}
		break;

	case(2):
		if(!*passIn)
		{
			passIn->day.dayOfWeek = 2;
			hourToSet = passIn->tue_hr;
			minToSet = passIn->tue_min;
			passIn->tue_hr += temp_hr;
			passIn->tue_min += temp_min;
		}
		else
		{
			passIn->day.dayOfWeek = 3;
			hourToSet = passIn->wed_hr;
			minToSet = passIn->wed_min;
			passIn->wed_hr += temp_hr;
			passIn->wed_min += temp_min;
		}
		break;

	case(3):
		if(!*passIn)
		{
			passIn->day.dayOfWeek = 3;
			hourToSet = passIn->wed_hr;
			minToSet = passIn->wed_min;
			passIn->wed_hr += temp_hr;
			passIn->wed_min += temp_min;
		}
		else
		{
			passIn->day.dayOfWeek = 4;
			hourToSet = passIn->thur_hr;
			minToSet = passIn->thur_min;
			passIn->thur_hr += temp_hr;
			passIn->thur_min += temp_min;
		}
		break;

	case(4):
		if(!*passIn)
		{
			passIn->day.dayOfWeek = 4;
			hourToSet = passIn->thur_hr;
			minToSet = passIn->thur_min;
			passIn->thur_hr += temp_hr;
			passIn->thur_min += temp_min;
		}
		else
		{
			passIn->day.dayOfWeek = 5;
			hourToSet = passIn->fri_hr;
			minToSet = passIn->fri_min;
			passIn->fri_hr += temp_hr;
			passIn->fri_min += temp_min;
		}
		break;

	case(5):
		if(!*passIn)
		{
			passIn->day.dayOfWeek = 5;
			hourToSet = passIn->fri_hr;
			minToSet = passIn->fri_min;
			passIn->fri_hr += temp_hr;
			passIn->fri_min += temp_min;
		}
		else
		{
			passIn->day.dayOfWeek = 5;
			cout << "Error, please enter again" << endl << endl;
			cout << "Please enter your Module Duration(Hour)" << endl;
			input >> temp_hr;

			cout << "Please enter your Module Duration(Min)" << endl;
			input >> temp_min;
		}
		break;
	}

	passIn->setData(temp_code, hourToSet, minToSet, temp_hr, temp_min, passIn->day.dayOfWeek);

	if((passIn->mon_hr * 60) + passIn->mon_min == 540 && 
		(passIn->tue_hr * 60) + passIn->tue_min == 540 && 
		(passIn->wed_hr * 60) + passIn->wed_min == 540 && 
		(passIn->thur_hr * 60) + passIn->thur_min == 540 && 
		(passIn->fri_hr * 60) + passIn->fri_min == 540)
	{
		passIn->full = true;
	}

	return input;
}

ostream& operator<<(ostream& output, CModule* passIn)
{
	int mStart_hr = passIn->day.getSHour() + 9;
	int mStart_min = passIn->day.getSMin();
	int mEnd_hr = mStart_hr + passIn->day.getHour();
	int mEnd_min = mStart_min + passIn->day.getMin();

	output << "Day: " << DayToPrint[passIn->day.dayOfWeek] << endl;
	output << "Module Code: " << passIn->newCode << endl;
	output << "Duration(Hr:Min): " << passIn->day.getHour() << ":" << passIn->day.getMin() << endl;
	output << "Timing(Hr:Min): " << mStart_hr << ":" << mStart_min << " - " << mEnd_hr << ":" << mEnd_min << endl;

	return output;
}