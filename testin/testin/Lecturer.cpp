#include "Lecturer.h"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

unsigned int CLecturer::count = 0;

CLecturer::CLecturer(void)
{
	cout << "Lecturer called" << endl;
}


CLecturer::~CLecturer(void)
{
}



void CLecturer::setDepartment(string departmentM)
{
	department = departmentM;
}

void CLecturer::setDesignation(string designationM)
{
	designation = designationM;
}


string CLecturer::returnDepartment() const
{
	return department;
}

string CLecturer::returnDesignation() const
{
	return designation;
}

void CLecturer::printTest()
{
	cout << CLecturer::returnName() << endl;
	cout << CLecturer::returnAge() << endl;
	cout << CLecturer::returnNRIC() << endl;
	cout << CLecturer::returnEmployeeID() << endl;
	cout << CLecturer::returnQualification() << endl;
	cout << CLecturer::returnDepartment() << endl;
	cout << CLecturer::returnDesignation() << endl;
}