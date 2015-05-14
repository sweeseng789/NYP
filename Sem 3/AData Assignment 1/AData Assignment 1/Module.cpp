#include "Module.h"


CModule::CModule(void):
hour					(0),
minute					(0),
moduleStartTime_Hour	(9),
moduleStartTime_Minute	(0),
moduleEndTime_Hour		(9),
moduleEndTime_Minute	(0),
MCode					(""),
MName					(""),
full					(false)
{
}

CModule::CModule(unsigned newHour, unsigned newMinute, string newMCode, string newMName):
hour					(0),
minute					(0),
moduleStartTime_Hour	(9),
moduleStartTime_Minute	(0),
moduleEndTime_Hour		(9),
moduleEndTime_Minute	(0),
MCode					(""),
MName					(""),
full					(false)
{
	this->hour = newHour;
	this->minute = newMinute;
	this->MCode = newMCode;
	this->MName = newMName;
}


CModule::~CModule(void)
{
}

unsigned CModule::returnHour()
{
	return this->hour;
}
unsigned CModule::returnMinute()
{
	return this->minute;
}
unsigned CModule::returnStartTime_Hour()
{
	return this->moduleStartTime_Hour;
}
unsigned CModule::returnEndTime_Minute()
{
	return this->moduleStartTime_Minute;
}
unsigned CModule::returnModuleEndTime_Hour()
{
	return this->moduleEndTime_Hour;
}
unsigned CModule::returnModuleEndTime_Minute()
{
	return this->moduleEndTime_Minute;
}
string CModule::returnMCode()
{
	return this->MCode;
}
string CModule::returnMName()
{
	return this->MName;
}

void CModule::setParameters(unsigned newHour, unsigned newMinute, string newMCode, string newMName)
{
	moduleStartTime_Hour = 9;
	moduleStartTime_Minute = 0;
	moduleEndTime_Hour = 9;
	moduleEndTime_Minute = 0;

	this->hour = newHour;
	this->minute = newMinute;
	this->MCode = newMCode;
	this->MName = newMName;
}

void CModule::setEndTime_Hour(int newValue)
{
	this->moduleEndTime_Hour = newValue;
}
void CModule::setEndTime_Minute(int newValue)
{
	this->moduleEndTime_Minute = newValue;
}
void CModule::setModuleStartTime_Hour(int newValue)
{
	this->moduleStartTime_Hour = newValue;
}
void CModule::setModuleStartTime_Minute(int newValue)
{
	this->moduleStartTime_Minute = newValue;
}
void CModule::setFull()
{
	full = true;
}