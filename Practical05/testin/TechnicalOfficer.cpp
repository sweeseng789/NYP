#include "TechnicalOfficer.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

unsigned int CTechnicalOfficer::countTO = 0;
CTechnicalOfficer::CTechnicalOfficer(void)
{
	countTO ++;
	cout << "TO called" << endl;
}


CTechnicalOfficer::~CTechnicalOfficer(void)
{
	countTO --;
	cout << "TO fired" << endl;
}


void CTechnicalOfficer::printTest()
{
	cout << "Technical Officer's name: " << CTechnicalOfficer::returnName() << endl;
	cout << "Technical Officer's age: " <<CTechnicalOfficer::returnAge() << endl;
	cout << "Technical Officer's NRIC: " <<CTechnicalOfficer::returnNRIC() << endl;
	cout << "Technical Officer's employee id: " <<CTechnicalOfficer::returnEmployeeID() << endl;
	cout << "Technical Officer's qualification: " << CTechnicalOfficer::returnQualification() << endl;
	cout << endl;

}

unsigned int CTechnicalOfficer::returnTOcount() const
{
	return countTO;
}