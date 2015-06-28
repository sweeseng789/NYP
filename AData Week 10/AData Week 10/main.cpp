#include <iostream>
#include <vector>
#include <algorithm>
#include <string>;

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::sort;
using std::string;

int testing[] = { 1 };
vector<int> list(testing, testing + sizeof(testing)/4);
bool loop = true;

bool searchFunction(int valueToFind)
{
	int first = 0;
	int last = list.size() - 1;
	int mid = 0;

	while (first <= last)
	{
		mid = (first + last) / 2;

		if (list[mid] == valueToFind)
		{
			return true;
		}
		else if (list[mid] > valueToFind)
		{
			last = mid - 1;
		}
		else
		{
			first = mid + 1;
		}
	}
	return false;
}

void addToList()
{
	int valueToAdd = 0;

	cout << "Please enter a value: ";
	cin >> valueToAdd;

	if (searchFunction(valueToAdd))
	{
		cout << "Duplication Detected, Error" << endl;
	}
	else
	{
		list.push_back(valueToAdd);
	}
}

void printAll()
{
	if (!list.empty())
	{
		for (vector<int>::iterator it = list.begin(); it != list.end(); ++it)
		{
			int i = *it;

			cout << i << endl;
		}
	}
	else
	{
		cout << "No Data has been entered" << endl;
	}
}

void Search()
{
	int valueToFind = 0;
	cout << "Please enter a value to find: ";
	cin >> valueToFind;

	if (searchFunction(valueToFind))
	{
		cout << valueToFind << " is found" << endl;
	}
	else
	{
		cout << valueToFind << " couldn't be found" << endl;
	}
}

void deleteFrmList()
{
	int valueToDelete = 0;

	cout << "Please enter a value: ";
	cin >> valueToDelete;

	if (searchFunction(valueToDelete))
	{
		cout << valueToDelete << " have been deleted" << endl;
		list.erase(std::remove(list.begin(), list.end(), valueToDelete), list.end());
	}
	else
	{
		cout << valueToDelete << " is not found and nothing have been deleted" << endl;
	}

	if (list.empty())
	{
		cout << "All Data have been erased" << endl;
	}
}

void Choice(int newNum)
{
	try
	{
		if (newNum == 1)
		{
			throw string("Add");
		}
		else if (newNum == 2)
		{
			throw string("Delete");
		}
		else if (newNum == 3)
		{
			throw string("Check");
		}
		else if (newNum == 4)
		{
			throw string("Search");
		}
		else if (newNum == 5)
		{
			throw string("Exit");
		}
		else
		{
			throw string("Error");
		}
	}

	catch (string s)
	{
		system("cls");
		if (s == "Add")
		{
			addToList();
		}
		else if (s == "Check")
		{
			printAll();
		}
		else if (s == "Search")
		{
			Search();
		}
		else if (s == "Exit")
		{
			loop = false;
		}
		else if (s == "Delete")
		{
			deleteFrmList();
		}
		else
		{
			cout << "Please enter again" << endl;
		}
	}
}

void main()
{

	while (loop)
	{
		system("cls");
		int newNum = 0;

		cout << "1)Add New Number \n2)Delete \n3)Check Total Input \n4)Search \n5)Exit" << endl;
		cin >> newNum;

		Choice(newNum);

		//Sort according to Ascending Order
		sort(list.begin(), list.end());

		system("pause");
	}
}