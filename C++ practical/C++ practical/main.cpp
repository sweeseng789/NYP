#include "Monster.h"
#include "Database.h"
#include <string>
using std::string;

void main(void)
{
	//CDatabase myLL;

	CDatabase linkList;

	while (true)
	{
		int choice1;
		int choice2;
		int choice3;
		int monsterHealth;
		int monsterLevel;
		string monsterName;


		cout << "Enter your choice\n1)Add \n2)Delete" << endl;
		cin >> choice1;

		if (choice1 == 1)
		{
			cout << "Please enter an integer to add: ";
			cin >> choice2;
			linkList.Insert(choice2);
			cout << "Please enter a level" << endl;
			cin >> monsterLevel;
			cout << "Please enter a name" << endl;
			cin.ignore();
			std::getline(cin, monsterName);
			cout << "Please enter health" << endl;
			cin >> monsterHealth;

			linkList.monsterStuff.set(monsterName, monsterLevel, monsterHealth);
		}
		/*else if (choice1 == 2)
		{
			cout << "Please enter a value to delete" << endl;
			cin >> choice3;
			if (linkList.Delete(choice3) == true)
			{
				cout << choice3 << " have been deleted" << endl;
			}
			else
			{
				cout << "Erorr " << choice3 << " cannot be found" << endl;
			}
		}

		linkList.PrintAll();
		linkList.PrintD();*/
		linkList.PrintAll();
	}	
		
}