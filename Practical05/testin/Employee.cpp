#include "Employee.h"

unsigned int CEmployee::count = 0;

CEmployee::CEmployee(void)
{
	count ++;
}

CEmployee::~CEmployee(void)
{
	count --;
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