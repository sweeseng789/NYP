#include "Employee.h"


CEmployee::CEmployee(void)
{
}


CEmployee::~CEmployee(void)
{
}

void CEmployee::setEmployeeID(string employeeIDM)
{
	employeeID = employeeIDM;
}

void CEmployee::setQualification(string qualificationM)
{
	qualification = qualificationM;
}

string CEmployee::returnEmployeeID() const
{
	return employeeID;
}

string CEmployee::returnQualification() const
{
	return qualification;
}