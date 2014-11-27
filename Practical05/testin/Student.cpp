#include "Student.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

unsigned int CStudent::countS = 0;

CStudent::CStudent(void)
{
	countS ++;
	cout << "Student called" << endl;
}


CStudent::~CStudent(void)
{
	countS --;
	cout << "Student expelled" << endl;
}

void CStudent::setAdminNo(string adminNoM)
{
	adminNo = adminNoM;
}

string CStudent::returnAdminNo() const
{
	return adminNo;
}

void CStudent::printTest()
{
	cout << "Student's name: " << CStudent::returnName() << endl;
	cout << "Student's age: " << CStudent::returnAge() << endl;
	cout << "Student's NRIC: " << CStudent::returnNRIC() << endl;
	cout << "Student's admin no: " << CStudent::returnAdminNo() << endl;
	cout << endl;
}

unsigned int CStudent::returnStudentCount() const
{
	return countS;
}