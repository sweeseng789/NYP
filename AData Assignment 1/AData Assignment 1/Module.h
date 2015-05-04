#pragma once
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::istream;
using std::ostream;
using std::vector;
class CModule
{
public:
	CModule(void);
	~CModule(void);
	CModule(unsigned newHour, unsigned newMinute, string newMNumber, string newMName);

	void setParameters(unsigned newHour, unsigned newMinute, string newMNumber, string newMName);

	unsigned returnHour();
	unsigned returnMinute();

	unsigned returnModuleStartTime_Hour();
	unsigned returnModuleStartTime_Minute();
	unsigned returnModuleEndTime_Hour();
	unsigned returnModuleEndTime_Minute();

	string returnMCode();
	string returnMName();

	void setModuleStartTime_Hour(int newValue);
	void setModuleStartTime_Minute(int newValue);
	void setModuleEndTime_Hour(int newValue);
	void setModuleEndTime_Minute(int newValue);

	void setFull();
private:
	unsigned hour, minute;
	unsigned moduleStartTime_Hour, moduleStartTime_Minute, moduleEndTime_Hour, moduleEndTime_Minute;
	string MCode, MName;
	bool full;
	
};

