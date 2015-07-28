#include <iostream>
#include <string>
#include "Data.h"
#include "UI.h"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;

bool checkForDuplicateID(CData data[], int numToCheck)
{
	for (unsigned a = 0; a < 20; ++a)
	{
		if (data[a].getTaken() == true)
		{
			if (data[a].getID() == numToCheck)
				return true;
			else
				return false;
		}
	}
}
bool checkStringForNumber(string ID)
{
	for (unsigned a = 0; a < ID.size(); ++a)
	{
		if (!isdigit(ID[a]))
			return true;
		else
			return false;
	}
}
void addData(CData data[], int location)
{
	int check = -1;
	string name = "";
	int ID = 0;
	string IDtoCheck = "";
	bool allNum = false;

	cout << "Please enter your name" << endl;
	cin.ignore();
	getline(cin, name);

	//Check if there is more than 32 character, if true then shorten it to 32
	if (name.size() > 32)
		name.resize(32);

	cout << endl;

	cout << "Please enter your ID" << endl;
	getline(cin, IDtoCheck);

	try {
		//Check if ID contain stuff other than numbers or ID size is more than 5 digit
		if (checkStringForNumber(IDtoCheck) || IDtoCheck.size() > 5)
			throw CUI(CUI::INVALID);
		else
			throw CUI(CUI::VALID);
	}
	catch (CUI ui)
	{
		if (ui.getType() == CUI::VALID)
		{
			ID = stoi(IDtoCheck);

			if (checkForDuplicateID(data, ID))
				cout << "There should only be one unique ID at any given time" << endl;
			else
				data[location].setData(true, name, ID);
		}
		else
		{
			cout << "Error, please try again later" << endl;
		}
	}
}
void add(CData data[], int &count, bool &listSorted)
{
	if (count < 20)
	{
		for (unsigned a = 0; a < 20; ++a)
		{
			if (data[a].getTaken() == false)
			{
				addData(data, a);
				break;
			}
		}
	}
	else
		cout << "Record is Full" << endl;
}

void deleteData(CData data[], int &count, bool& listSorted)
{
	if (count == 0)
	{
		cout << "Record is empty" << endl;
	}
	else
	{
		int choice = 0;
		bool deleteByID = false;
		bool deleteByName = false;
		string nameToDelete = "";
		int IDtoDelete = 0;

		cout << "Enter (1) to delete by Patient's name \nEnter (2) to delete by Patient's ID" << endl;
		cin >> choice;

		try {
			if (choice < 1 || choice > 2)
				throw CUI(CUI::INVALID);
			else
				throw CUI(CUI::VALID);
		}
		catch (CUI ui)
		{
			if (ui.getType() == CUI::INVALID)
			{
				cout << "Error, please try again later" << endl;
			}
			else
			{
				if (choice == 1)
				{
					//Delete by name
					deleteByName = true;
					deleteByID = false;
				}
				else
				{
					//Delete by ID
					deleteByName = false;
					deleteByID = true;
				}


				if (deleteByName && !deleteByID)
				{
					cout << "Please enter the name that you want to delete" << endl;
					cin.ignore();
					getline(cin, nameToDelete);
				}
				else
				{
					cout << "Please enter the ID that you want to delete" << endl;
					cin >> IDtoDelete;
				}


				for (unsigned a = 0; a < 20; ++a)
				{
					if (data[a].getTaken())
					{
						//if (deleteByName && !deleteByID)
						{
							if (data[a].getName() == nameToDelete || data[a].getID() == IDtoDelete)
							{
								data[a].resetData();
								count--;
								cout << "Patient's record have been removed" << endl;
								listSorted = false;
								break;
							}
						}
					}
				}
			}
		}
	}
}

void printAll(CData data[], int & count)
{
	if (count == 0)
	{
		cout << "Record is empty" << endl;
	}
	else
	{
		for (unsigned a = 0; a < 20; ++a)
		{
			if (data[a].getTaken() == true)
			{
				cout << data[a] << endl;
			}
		}
	}
}

void binarySearch(CData data[], bool &found, const bool findByID, const bool findByName, const int size, const string nameToSearch, const int IDtoSearch)
{
	int first = 0;
	int last = size - 1;
	int mid = 0;
	if (findByID == false && findByName == true)
	{
		while (first <= last)
		{
			mid = (first + last) / 2;
			if (data[mid].getName() == nameToSearch)
			{
				cout << "Patient's Record Found:" << endl;
				cout << data[mid] << endl;
				found = true;
				break;
			}
			else if (data[mid].getName() > nameToSearch)
			{
				last = mid - 1;
			}
			else
			{
				first = mid + 1;
			}
		}
	}
	else
	{
		while (first <= last)
		{
			mid = (first + last) / 2;
			if (data[mid].getID() == IDtoSearch)
			{
				cout << "Patient's Record Found:" << endl;
				cout << data[mid] << endl;
				found = true;
				break;
			}
			else if (data[mid].getID() > IDtoSearch)
			{
				last = mid - 1;
			}
			else
			{
				first = mid + 1;
			}
		}
	}
}
void sequentialSearch(CData data[], bool &found, const bool findByID, const bool findByName, const int size, const string nameToSearch, const int IDtoSearch)
{
	for (unsigned a = 0; a < 20; a++)
	{
		if (data[a].getTaken())
		{
			if (findByID == false && findByName == true)
			{
				if (data[a].getName() == nameToSearch)
				{
					cout << "Patient's Record Found:" << endl;
					cout << data[a] << endl;
					found = true;
					break;
				}
			}
			else
			{
				if (data[a].getID() == IDtoSearch)
				{
					cout << "Patient's Record Found:" << endl;
					cout << data[a] << endl;
					found = true;
					break;
				}
			}
		}
	}
}
void search(CData data[], int &count, int size, bool &listSorted)
{
	if (count == 0)
	{
		cout << "Record is empty" << endl;
	}
	else
	{
		int choice = 0;
		bool found = false;
		string nameToSearch = "";
		int IDtoSearch = 0;
		bool findByName = false;
		bool findByID = false;

		cout << "Please enter (1) to search by name \nPlease enter(2) to enter by ID" << endl;
		cin >> choice;

		try {
			if (choice < 1 || choice > 2)
				throw CUI(CUI::INVALID);
			else
				throw CUI(CUI::VALID);
		}
		catch (CUI ui)
		{
			if (ui.getType() == CUI::VALID)
			{
				if (choice == 1)
				{
					findByName = true;
					findByID = false;
					cout << "Please enter the name that you want to search" << endl;
					cin.ignore();
					getline(cin, nameToSearch);
				}
				else
				{
					findByName = false;
					findByID = true;
					cout << "Please enter the ID that you want to search" << endl;
					cin >> IDtoSearch;
				}
				if (listSorted)
				{
					binarySearch(data, found, findByID, findByName, size, nameToSearch, IDtoSearch);
				}
				else
				{
					sequentialSearch(data, found, findByID, findByName, size, nameToSearch, IDtoSearch);
				}

				if (found == false)
					cout << "Patient's Record not found" << endl;
			}
			else
			{
				cout << "Error, please try again later" << endl;
			}
		}
	}
}

void merge(CData data[], int first, int middle, int last, bool ascending)
{
	//temp array to hold first list
	CData * temp = new CData[middle - first + 1];

	int i, j, k;
	for (j = first, i = 0; j <= middle; i++, j++)
	{
		temp[i] = data[j];//Duplicate first list
	}

	i = 0; k = first;

	if (ascending)
	{
		while (k < j && j <= last)
		{
			//if element from 1st list < 2nd list
			if (temp[i].getID() <= data[j].getID())
			{
				data[k++] = temp[i++]; //copy first 1st list
			}
			else
				data[k++] = data[j++]; //copy from 2nd list
		}
	}
	else
	{
		while (k < j && j <= last)
		{
			//if element from 1st list < 2nd list
			if (temp[i].getID() > data[j].getID())
			{
				data[k++] = temp[i++]; //copy first 1st list
			}
			else
				data[k++] = data[j++]; //copy from 2nd list
		}
	}

	while (k < j)//copy remaining to temp if any
	{
		data[k++] = temp[i++];
	}

	delete[] temp; // remove temp array
}
void mergeSort(CData data[], int first, int last, bool ascending)
{
	if (first < last)
	{
		int middle = (first + last) / 2;
		mergeSort(data, first, middle, ascending);
		mergeSort(data, middle + 1, last, ascending);
		merge(data, first, middle, last, ascending);
	}
}
void sorting(CData data[], int first, int last, bool &listSorted)
{
	int choice = 0;
	bool ascending = false;

	cout << "Please enter (1) to sort in ascending order \nPlease enter (2) to sort in descending order" << endl;
	cin >> choice;


	try {
		if (choice < 1 || choice > 2)
			throw CUI(CUI::INVALID);
		else
			throw(CUI(CUI::VALID));
	}
	catch (CUI ui)
	{
		if (ui.getType() == CUI::INVALID)
			cout << "Error, please try again later" << endl;
		else
		{
			if (choice == 1)
				ascending = true;
			else
				ascending = false;

			cout << "Sorting now" << endl;
			mergeSort(data, first, last, ascending);

			cout << "Sorting done" << endl;
		}
	}
}

void main()
{
	CData data[20];
	data[0].setData(true, "Abby", 12345);
	data[1].setData(true, "Zebra", 12314);
	data[2].setData(true, "Swee Seng", 31423);
	data[3].setData(true, "Joyce", 14233);
	int count = 4;
	bool stillUsing = true;
	int menuChoice = 0;
	bool listSorted = false;

	while (stillUsing)
	{
		system("cls");
		cout << "Welcome to NTU patient record system! \nEnter (1) to add patient record to the database \nEnter (2) to remove a patient record from the database \nEnter (3) to search patient records \nEnter (4) to sort patient records \nEnter (5) to print existing records \nEnter (6) to exit" << endl << "Please enter your choice: ";
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
			{
				cout << "Error, please try again" << endl;
			}
			else
			{
				system("cls");
				switch (menuChoice)
				{
				case(1) :
					add(data, count, listSorted);
					break;

				case(2) :
					deleteData(data, count, listSorted);
					break;

				case(3) :
					search(data, count, 20, listSorted);
					break;

				case(4) :
					sorting(data, 0, 19, listSorted);
					break;

				case(5) :
					printAll(data, count);
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