#include "Student.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;


CStudent::CStudent(void)
{
	cout << "Student called" << endl;
}


CStudent::~CStudent(void)
{
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
	cout << CStudent::returnName() << endl;
	cout << CStudent::returnAge() << endl;
	cout << CStudent::returnNRIC() << endl;
	cout << CStudent::returnAdminNo() << endl;
}