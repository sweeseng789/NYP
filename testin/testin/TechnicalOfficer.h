#pragma once
#include "Employee.h"
#include "Person.h"
class CTechnicalOfficer :
	public CEmployee
{
public:
	CTechnicalOfficer(void);
	~CTechnicalOfficer(void);

	virtual void printTest();
};

