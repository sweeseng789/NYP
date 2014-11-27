#pragma once
#include <string>
#include "Person.h"
using std::string;
class CEmployee :
	public CPerson
{
public:
	CEmployee(void);
	~CEmployee(void);

	void setEmployeeID(string employeeIDM);
	void setQualification(string qualificationM);

	string returnEmployeeID() const;
	string returnQualification() const;
protected:
	string employeeID;
	string qualification;
	static unsigned int count;
};

