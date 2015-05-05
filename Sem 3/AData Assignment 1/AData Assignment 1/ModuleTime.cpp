#include "ModuleTime.h"


CModuleTime::CModuleTime(void)
{
}


CModuleTime::~CModuleTime(void)
{
}

istream & operator>> (istream & input, CModuleTime & passIn)
{
	cout << "Please enter the hour for this module" << endl;
	input >> passIn.hour;
	cout << endl;

	cout << "Please enter the minute for the module" << endl;
	input >> passIn.minute;
	cout << endl;

	if (passIn.minute == 60)
	{
		passIn.minute = 0;
		passIn.hour += 1;
	}

	return input;
}

unsigned CModuleTime::returnHour()
{
	return this->hour;
}
unsigned CModuleTime::returnMinute()
{
	return this->minute;
}
