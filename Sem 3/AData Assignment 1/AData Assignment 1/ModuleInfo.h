#pragma once
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::istream;
using std::ostream;

class CModuleInfo
{
public:
	CModuleInfo(void);
	~CModuleInfo(void);

	friend istream & operator>>(istream & input, CModuleInfo & passIn);

	string returnModuleCode();
	string returnModuleName();
private:
	string moduleCode;
	string moduleName;
};

