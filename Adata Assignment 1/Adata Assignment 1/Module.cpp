#include "Module.h"



CModule::CModule()
{
}


CModule::~CModule()
{
}

void CModule::setData(const string moduleCode, const int hour, const int min, const int dayOfWeek)
{
	this->moduleCode = moduleCode;
	this->time.setTimeData(hour, min, dayOfWeek);
}