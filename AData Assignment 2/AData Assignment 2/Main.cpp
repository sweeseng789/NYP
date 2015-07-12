#include <iostream>
#include <string>
#include "Data.h"
#include "UI.h"

using std::cin;
using std::cout;
using std::endl;
using std::getline;
using std::string;

void add(CData data[], int &count)
{
	if (count < 20)
	{
		for (unsigned a = 0; a < 20; ++a)
		{
			if (!data[a].getTaken())
			{
				cin >> data[a];
				count++;
				break;
			}
		}
	}
	else
		cout << "Record is Full" << endl;
}

void deleteData(CData data[], int &count)
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
		string toDelete = "";
		
		cout << "Enter (1) to delete by Patient's name \nEnter (2) to delete by Patient's ID" << endl;
		cin >> choice;

		while (choice < 1 || choice> 2)
		{
			cout << "Error, please enter again" << endl;
		}

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

		cout << "Please enter the ";
		if (deleteByName && !deleteByID)
			cout << "name ";
		else
			cout << "ID ";
		cout << "that you want to delete" << endl;
		cin.ignore();
		getline(cin, toDelete);

		for (unsigned a = 0; a < 20; ++a)
		{
			if (deleteByName && !deleteByID)
			{
				if (data[a].getName() == toDelete)
				{
					data[a].resetData();
					count--;
					cout << "Patient's record have been removed" << endl;
					break;
				}
			}
			else
			{
				if (data[a].getID() == toDelete)
				{
					data[a].resetData();
					count--;
					cout << "Patient's record have been removed" << endl;
					break;
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

void search(CData data[], int &count, int size)
{
	if (count == 0)
	{
		cout << "Record is empty" << endl;
	}
	else
	{
		int first = 0;
		int last = size - 1;
		int mid = 0;
		int choice = 0;
		bool found = false;
		string valueToSearch = "";

		cout << "Please enter (1) to search by name \nPlease enter(2) to enter by ID" << endl;
		cin >> choice;

		while (choice < 1 || choice > 2)
		{
			cout << "Error, please enter again" << endl;
			cin >> choice;
		}

		cout << "Please enter the ";
		if (choice == 1)
			cout << "name ";
		else
			cout << "ID ";
		cout << "that you want to search" << endl;
		cin.ignore();
		getline(cin, valueToSearch);

		while (first <= last)
		{
			mid = (first + last) / 2;
			if (data[mid].getName() == valueToSearch || data[mid].getID() == valueToSearch)
			{
				cout << "Patient's Record Found:" << endl;
				cout << data[mid] << endl;
				found = true;
				break;
			}
			else if (data[mid].getName() > valueToSearch || data[mid].getID() > valueToSearch)
			{
				last = mid - 1;
			}
			else
			{
				first = mid + 1;
			}
		}

		if (found == false)
			cout << "Patient's Record not found" << endl;
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
			if (temp[i].getName() <= data[j].getName())
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
			if (temp[i].getName() > data[j].getName())
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

void sorting(CData data[], int first, int last)
{
	int choice = 0;
	bool ascending = false;

	cout << "Please enter (1) to sort in ascending order \nPlease enter (2) to sort in descending order" << endl;
	cin >> choice;

	while (choice < 1 || choice > 2)
	{
		cout << "Error, please enter your choice again" << endl;
		cin >> choice;
	}

	if (choice == 1)
		ascending = true;
	else
		ascending = false;

	cout << "Sorting now" << endl;
	mergeSort(data, first, last, ascending);
	cout << "Sorting done" << endl;
}

void main()
{
	CData data[20];
	data[0].setData(true, "Abby", "12345");
	data[1].setData(true, "Zebra", "12314");
	data[2].setData(true, "Swee Seng", "31423");
	data[3].setData(true, "Joyce", "14233");
	int count = 4;
	bool stillUsing = true;
	int menuChoice = 0;

	while (stillUsing)
	{
		system("cls");
		cout << "Welcome to NTU patient record system! \nEnter (1) to add patient record to the database \nEnter (2) to remove a patient record from the database \nEnter (3) to search patient records \nEnter (4) to sort patient records \nEnter (5) to print existing records \nEnter (6) to exit" << endl << "Please enter your choice: ";
		cin >> menuChoice;

		try
		{
			if (menuChoice == 1)
				throw (CUI(CUI::ADD));
			else if(menuChoice == 2)
				throw (CUI(CUI::DELETE));
			else if (menuChoice == 3)
				throw (CUI(CUI::SEARCH));
			else if (menuChoice == 4)
				throw (CUI(CUI::SORT));
			else if (menuChoice == 5)
				throw (CUI(CUI::PRINT));
			else if (menuChoice == 6)
				throw (CUI(CUI::EXIT));
			else
				throw(CUI(CUI::INVALID));
		}
		catch (CUI ui)
		{
			system("cls");
			if (ui.getType() == CUI::ADD)
			{
				add(data, count);
			}
			else if (ui.getType() == CUI::DELETE)
			{
				deleteData(data, count);
			}
			else if (ui.getType() == CUI::SEARCH)
			{
				search(data, count, 20);
			}
			else if (ui.getType() == CUI::SORT)
			{
				sorting(data, 0, 19);
			}
			else if (ui.getType() == CUI::PRINT)
			{
				printAll(data, count);
			}
			else if (ui.getType() == CUI::EXIT)
			{
				stillUsing = false;
			}
			else if(ui.getType() == CUI::INVALID)
			{
				cout << "Error, please start over again" << endl;
			}

			system("pause");
		}
	}
}