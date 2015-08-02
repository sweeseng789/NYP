#include "DataBase.h"

int CDataBase::count = 4;
int CDataBase::location = 0;
bool CDataBase::sortByID = false;
bool CDataBase::sortByName = false;


CDataBase::CDataBase()
{
	data[0].setData(true, "Abby", 12345);
	data[1].setData(true, "Zebra", 12314);
	data[2].setData(true, "Swee Seng", 31423);
	data[3].setData(true, "Joyce", 14233);
}


CDataBase::~CDataBase()
{
}

bool CDataBase::binarySearch(string nameToFind, int IDtoFind, bool findByID)
{
	int first = 0;
	int last = count - 1;
	int mid = 0;

	while (first <= last)
	{
		mid = (first + last) / 2;

		if (findByID == true)
		{
			if (data[mid].getID() == IDtoFind)
			{
				location = mid;
				return true;
			}
			else if (data[mid].getID() > IDtoFind)
				last = mid - 1;
			else
				first = mid + 1;
		}
		else
		{
			if (data[mid].getName() == nameToFind)
			{
				location = mid;
				return true;
			}
			else if (data[mid].getName() > nameToFind)
				last = mid - 1;
			else
				first = mid + 1;
		}
	}
	return false;
}

bool CDataBase::sequentialSearch(string nameToFind, int IDtoFind, bool findByID)
{
	for (int a = 0; a < count - 1; a++)
	{
		if (data[a].getTaken())
		{
			if (findByID == true)
			{
				if (data[a].getID() == IDtoFind)
				{
					location = a;
					return true;
				}
			}
			else
			{
				if (data[a].getName() == nameToFind)
				{
					location = a;
					return true;
				}
			}
		}
	}
	return false;
}

void CDataBase::addData()
{
	if (count == 20)
		CUI::renderRecordIsFull();
	else
	{
		for (unsigned a = 0; a < 20; ++a)
		{
			if (data[a].getTaken() == false)
			{
				//addData(data, a);
				cin >> data[a];
				sortByID = false;
				sortByName = false;
				count++;
				break;
			}
		}
	}
}

void CDataBase::deleteData()
{
	if (count == 0)
		CUI::renderRecordIsEmpty();
	else
	{
		int choice = 0;
		bool deleteByID = false;
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
				CUI::renderErrorMessage();
			else
			{
				if (choice == 1)
					deleteByID = false;
				else
					deleteByID = true;

				if (!deleteByID)
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

				if (deleteByID == true)
				{
					if (sortByID == true)
					{
						if (binarySearch(nameToDelete, IDtoDelete, deleteByID) == true)
						{
							std::cout << "Record Deleted" << std::endl;
							data[location].resetData();
						}
						else
							CUI::renderNoDataFound();
					}
					else
					{
						if (sequentialSearch(nameToDelete, IDtoDelete, deleteByID) == true)
						{
							std::cout << "Record Deleted" << std::endl;
							data[location].resetData();
						}
						else
							CUI::renderNoDataFound();
					}
				}
				else
				{
					if (sortByName == true)
					{
						if (binarySearch(nameToDelete, IDtoDelete, deleteByID) == true)
						{
							std::cout << "Record Deleted" << std::endl;
							data[location].resetData();
						}
						else
							CUI::renderNoDataFound();
					}
					else
					{
						if (sequentialSearch(nameToDelete, IDtoDelete, deleteByID) == true)
						{
							std::cout << "Record Deleted" << std::endl;
							data[location].resetData();
						}
						else
							CUI::renderNoDataFound();
					}
				}
			}
		}
	}
}

void CDataBase::searchData()
{
	if (count == 0)
		CUI::renderRecordIsEmpty();
	else
	{
		int choice = 0;
		bool found = false;
		string nameToSearch = "";
		int IDtoSearch = 0;
		bool findByID = false;

		cout << "Please enter (1) to search by name \nPlease enter (2) to search by ID" << endl;
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
				CUI::renderErrorMessage();
			else
			{
				if (choice == 1)
				{
					findByID = false;
					cout << "Please enter the name that you want to search" << endl;
					cin.ignore();
					getline(cin, nameToSearch);
				}
				else
				{
					findByID = true;
					cout << "Please enter the ID that you want to search" << endl;
					cin >> IDtoSearch;
				}

				if (findByID == true)
				{
					if (sortByID == true)
					{
						if (binarySearch(nameToSearch, IDtoSearch, findByID) == true)
						{
							std::cout << "Record Found: " << std::endl;
							std::cout << data[location] << std::endl;
						}
						else
							CUI::renderNoDataFound();
					}
					else
					{
						if (sequentialSearch(nameToSearch, IDtoSearch, findByID) == true)
						{
							std::cout << "Record Found: " << std::endl;
							std::cout << data[location] << std::endl;
						}
						else
							CUI::renderNoDataFound();
					}
				}
				else
				{
					if (sortByName == true)
					{
						if (binarySearch(nameToSearch, IDtoSearch, findByID) == true)
						{
							std::cout << "Record Found: " << std::endl;
							std::cout << data[location] << std::endl;
						}
						else
							CUI::renderNoDataFound();
					}
					else
					{
						if (sequentialSearch(nameToSearch, IDtoSearch, findByID) == true)
						{
							std::cout << "Record Found: " << std::endl;
							std::cout << data[location] << std::endl;
						}
						else
							CUI::renderNoDataFound();
					}
				}
			}
		}
	}
}

void CDataBase::printAll()
{
	if (count == 0)
		CUI::renderRecordIsEmpty();
	else
	{
		for (int a = 0; a < count; a++)
		{
			if (data[a].getTaken())
			{
				cout << data[a] << endl;
			}
		}
	}
}

void merge(CData data[], int first, int middle, int last, bool ascending, bool sortingByIDorder)
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
			if (sortingByIDorder == true)
			{
				//if element from 1st list < 2nd list
				if (temp[i].getID() <= data[j].getID())
					data[k++] = temp[i++]; //copy first 1st list
				else
					data[k++] = data[j++]; //copy from 2nd list
			}
			else
			{
				//if element from 1st list < 2nd list
				if (temp[i].getName() <= data[j].getName())
					data[k++] = temp[i++]; //copy first 1st list
				else
					data[k++] = data[j++]; //copy from 2nd list
			}
		}
	}
	else
	{
		while (k < j && j <= last)
		{
			if (sortingByIDorder == true)
			{
				//if element from 1st list < 2nd list
				if (temp[i].getID() > data[j].getID())
					data[k++] = temp[i++]; //copy first 1st list
				else
					data[k++] = data[j++]; //copy from 2nd list
			}
			else
			{
				//if element from 1st list < 2nd list
				if (temp[i].getName() > data[j].getName())
					data[k++] = temp[i++]; //copy first 1st list
				else
					data[k++] = data[j++]; //copy from 2nd list
			}

		}
	}

	while (k < j)//copy remaining to temp if any
	{
		data[k++] = temp[i++];
	}

	delete[] temp; // remove temp array
}
void mergeSort(CData data[], int first, int last, bool ascending, bool sortingByIDorder)
{
	if (first < last)
	{
		int middle = (first + last) / 2;
		mergeSort(data, first, middle, ascending, sortingByIDorder);
		mergeSort(data, middle + 1, last, ascending, sortingByIDorder);
		merge(data, first, middle, last, ascending, sortingByIDorder);
	}
}
void CDataBase::sortData()
{
	if (count == 0)
		CUI::renderNoDataFound();
	else
	{
		int first = 0;
		int last = count - 1;
		int choice = 0;
		int choice2 = 0;
		bool ascending = false;
		bool sortingByIDorder = false;

		cout << "Please enter (1) to sort by Name \nPlease enter (2) to sort by ID" << endl;
		cin >> choice;

		cout << endl;

		cout << "Please enter (1) to sort in ascending order \nPlease enter (2) to sort in descending order" << endl;
		cin >> choice2;


		try {
			if (choice < 1 || choice > 2 || choice2 < 1 || choice2 > 2)
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
				{
					sortByName = true;
					sortByID = false;
					sortingByIDorder = false;
				}
				else
				{
					sortByName = false;
					sortByID = true;
					sortingByIDorder = true;
				}

				if (choice2 == 1)
					ascending = true;
				else
					ascending = false;

				cout << "Sorting now" << endl;
				mergeSort(data, first, last, ascending, sortingByIDorder);

				cout << "Sorting done" << endl;
			}
		}
	}
}
