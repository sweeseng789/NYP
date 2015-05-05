#include "ModuleInfo.h"


CModuleInfo::CModuleInfo(void)
{
}


CModuleInfo::~CModuleInfo(void)
{
}

istream & operator>>(istream & input, CModuleInfo & passIn)
{
	cout << "Please enter your module code" << endl;
	cin.ignore();
	getline(input, passIn.moduleCode);
	cout << endl;

	cout << "Please enter your module name" << endl;
	getline(input, passIn.moduleName);
	cout << endl;
	return input;
}

string CModuleInfo::returnModuleCode()
{
	return this->moduleCode;
}
string CModuleInfo::returnModuleName()
{
	return this->moduleName;
}
