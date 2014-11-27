#include <iostream>
#include "Person.h"
#include "Lecturer.h"
using std::cin;
using std::cout;
using std::endl;

CPerson::CPerson(void)
{
}


CPerson::~CPerson(void)
{
}

void CPerson::printTest(void)
{
	cout << &CLecturer::returnName << endl;
}

void CPerson::setNRIC(string NRICM)
{
	NRIC = NRICM;
}

void CPerson::setAge(int ageM)
{
	age = ageM;
}

string CPerson::returnNRIC() const
{
	return NRIC;
}

int CPerson::returnAge() const
{
	return age;
}

void CPerson::setName(string nameM)
{
	name = nameM;
}

string CPerson::returnName() const
{
	return name;
}

int CPerson::returnCount() const
{
	return 0;
}
