#include <iostream>
#include <string>
#include "UI.h"
#include "DataBase.h"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;

void main()
{
	CDataBase database;
	bool stillUsing = true;
	int menuChoice = 0;

	while (stillUsing)
	{
		system("cls");

		CUI::renderMainMenu();
		cin >> menuChoice;

		try {
			if (menuChoice < 1 || menuChoice > 6)
				throw(CUI(CUI::INVALID));
			else
				throw(CUI(CUI::VALID));
		}
		catch (CUI ui)
		{
			if (ui.getType() == CUI::INVALID)
				CUI::renderErrorMessage();
			else
			{
				system("cls");
				switch (menuChoice)
				{
				case(1) :
					database.addData();
					break;

				case(2) :
					database.deleteData();
					break;

				case(3) :
					database.searchData();
					break;

				case(4) :
					database.sortData();
					break;

				case(5) :
					database.printAll();
					break;

				case(6) :
					stillUsing = false;
					break;
				}
			}
			system("pause");
		}
	}
}