#pragma once
#include "Person.h"
#include "Employee.h"
class CStudent :
	public CPerson
{
public:
	CStudent(void);
	~CStudent(void);

	virtual void printTest();

	void setAdminNo(string adminNoM);

	string returnAdminNo() const;
protected:
	string adminNo;
	static unsigned int count;
};

