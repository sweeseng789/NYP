#include "UI.h"



CUI::CUI()
{
}

CUI::CUI(MENU_OPTION type)
{
	this->type = type;
}


CUI::~CUI()
{
}

CUI::MENU_OPTION CUI::getType()
{
	return type;
}

void CUI::renderMainMenu()
{
	std::cout << "Welcome to NTU patient record system! \nEnter (1) to add patient record to the database \nEnter (2) to remove a patient record from the database \nEnter (3) to search patient records \nEnter (4) to sort patient records \nEnter (5) to print existing records \nEnter (6) to exit" << std::endl << "Please enter your choice: ";
}

void CUI::renderErrorMessage()
{
	std::cout << "Error, please try again" << std::endl;
}

void CUI::renderRecordIsFull()
{
	std::cout << "Record is Full" << std::endl;
}

void CUI::renderRecordIsEmpty()
{
	std::cout << "Record is empty" << std::endl;
}

void CUI::renderNoDataFound()
{
	std::cout << "No record is found" << std::endl;
}