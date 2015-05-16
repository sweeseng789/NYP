#include "Module.h"

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
	return input;
}
