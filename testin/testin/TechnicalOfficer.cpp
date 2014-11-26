#include "TechnicalOfficer.h"
#include <iostream>

using std::cin;
using std::cout;
using std::endl;

unsigned int CTechnicalOfficer::count = 0;
CTechnicalOfficer::CTechnicalOfficer(void)
{
	cout << "TO called" << endl;
}


CTechnicalOfficer::~CTechnicalOfficer(void)
{
}


void CTechnicalOfficer::printTest()
{
	cout << CTechnicalOfficer::returnName() << endl;
	cout << CTechnicalOfficer::returnAge() << endl;
	cout << CTechnicalOfficer::returnNRIC() << endl;
	cout << CTechnicalOfficer::returnEmployeeID() << endl;
	cout << CTechnicalOfficer::returnQualification() << endl;

}