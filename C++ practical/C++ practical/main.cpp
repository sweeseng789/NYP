#include "Database.h"
#include <string>
using std::string;

void main(void)
{
	//CDatabase myLL;

	CDatabase linkList;
	int choice1;
	int choice2;
	int choice3;
	int monsterHealth;
	int monsterLevel;
	string monsterName;
	string searchList;
	string found;

	while (true)
	{
		cout << "Enter your choice\n \n1)Add \n2)Delete \n3)Search record \n4)Edit Record \n5)Print All Record \n6)Exit program" << endl;
		cout << endl;
		cout << "Input: ";
		cin >> choice1;

		while(choice1 < 1 || choice1 > 6)
		{
			cout << "Error, please enter again" << endl;
			cin >> choice1;
		}
		if (choice1 == 1)//add value
		{
			cout << "Please enter an integer to add: ";
			cin >> choice2;
			cin.ignore();
			cout << "Please enter a name: ";
			getline(cin, monsterName);
			cout << "Please enter a level: ";
			cin >> monsterLevel;
			cout << "Please enter health: ";
			cin >> monsterHealth;
			linkList.Insert(choice2, monsterLevel, monsterHealth, monsterName);
		}
		else if (choice1 == 2)//delete value
		{
			if(linkList.detectFirstNode() == true)
			{
				cout << "Linklist is empty" << endl;
			}
			else
			{
				cout << "Please enter a value to delete: ";
				cin >> choice3;
				if (linkList.Delete(choice3) == true)
				{
					cout << choice3 << " have been deleted" << endl;
				}
				else
				{
					cout << "Error " << choice3 << " cannot be found" << endl;
				}
			}
		}
		else if (choice1 == 3)//search record
		{
			if(linkList.detectFirstNode() == true)
			{
				cout << "Linklist is empty" << endl;
			}
			else
			{
				cout << "Please enter what you want to search: ";
				cin.ignore();
				getline(cin, searchList);
				linkList.SearchFunction(searchList);
			}

		}
		else if (choice1 == 4)//edit record
		{
			if (linkList.detectFirstNode() == true)
			{
				cout << "LinkList is empty" << endl;
			}
			else
			{
				linkList.PrintAll();
				cout << "Please enter the record that you want to edit" << endl;
				cin >> choice3;

				if(linkList.RecordValidation(choice3) == true)
				{
					cout << "Please enter what you want to edit \n1)Monster name \n2)Monster Level \n3)Monster Health \n4)All of the above" << endl;
					cin >> choice2;
					while (choice2 < 1 || choice2 > 4)
					{
						cout << "Error, please enter again" <<endl;
						cin >> choice2;
					}

					if (choice2 == 1)
					{
						cin.ignore();
						cout << "Please enter a name: ";
						getline(cin, monsterName);
						linkList.EditMonsterName(choice3, monsterName);
					}
					else if (choice2 == 2)
					{
						cout << "Please enter a level: ";
						cin >> monsterLevel;
						linkList.EditMonsterLevel(choice3, monsterLevel);
					}
					else if(choice2 == 3)
					{
						cout << "Please enter health: ";
						cin >> monsterHealth;
						linkList.EditMonsterHealth(choice3, monsterHealth);
					}
					else if(choice2 == 4)
					{
						cin.ignore();
						cout << "Please enter a name: ";
						getline(cin, monsterName);
						cout << "Please enter a level: ";
						cin >> monsterLevel;
						cout << "Please enter health: ";
						cin >> monsterHealth;
						linkList.EditRecord(choice3, monsterLevel, monsterHealth, monsterName);
					}
				}
				else
				{
					cout << "Data not found" << endl;
				}
			}
		}
		else if (choice1 == 5)//print record
		{
			if(linkList.detectFirstNode() == true)
			{
				cout << "linkList is empty" << endl;
			}
			else
			{
				cout << "1)Front to back \n2)Back to front \n3)Both" << endl;
				cin >> choice3;
				if(choice3 == 1)
				{
					cout << "Ascending Order" << endl;
					linkList.PrintAll();
				}
				else if (choice3 == 2)
				{
					cout << "Descending Order" << endl;
					linkList.PrintD();
				}
				else
				{
					cout << "Ascending Order" << endl;
					linkList.PrintAll();

					cout << "Descending Order" << endl;
					linkList.PrintD();
				}
			}
		}
		else if (choice1 == 6)//exit program
		{
			break;
		}
		system("pause");
		system("cls");
	}	
		
}