#include "Lecturer.h"
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

unsigned int CLecturer::countL = 0;

CLecturer::CLecturer(void)
{
	countL ++;
	cout << "Lecturer called" << endl;
}


CLecturer::~CLecturer(void)
{
	countL --;
	cout << "Lecturer fired" << endl;
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
	cout << "Lecturer's name: " << CLecturer::returnName() << endl;
	cout << "Lecturer's age: " << CLecturer::returnAge() << endl;
	cout << "Lecturer's NRIC: " << CLecturer::returnNRIC() << endl;
	cout << "Lecturer's employee id: " << CLecturer::returnEmployeeID() << endl;
	cout << "Lecturer's qualification: " << CLecturer::returnQualification() << endl;
	cout << "Lecturer's department: " << CLecturer::returnDepartment() << endl;
	cout << "Lecturer's designation: " << CLecturer::returnDesignation() << endl;
	cout << endl;
}

unsigned int CLecturer::returnLcount() const
{
	return countL;
}