#pragma once
#include "Person.h"
#include "Employee.h"
class CLecturer :
	public CEmployee 
{
public:
	CLecturer(void);
	~CLecturer(void);

	
	void setDepartment(string departmentM);
	void setDesignation(string designmationM);

	
	string returnDepartment() const;
	string returnDesignation() const;
	virtual void printTest(void);

	unsigned int returnLcount () const;
protected:
	string department;
	string designation;
	static unsigned int countL;
};

