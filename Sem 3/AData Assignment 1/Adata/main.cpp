#include "Module.h"
#include <vector>

using std::vector;

void main()
{
	vector<CModule *> timetable;
	CModule* newModule;
	int choice = 0;
	while(true)
	{
		system("cls");

		cout << "Please enter your choice \n1)Enter timetable \n2)Check timetable \n3)Exit" << endl;
		cin >> choice;

		while(choice < 1 || choice > 3)
		{
			system("cls");
			cout << "Error, please enter again" << endl;
			cin >> choice;
		}

		if(choice == 1)
		{
			if(!timetable.empty())
			{
				if(timetable[0]->getFull())
				{
					cout << "Timetable full" << endl;
				}
				else
				{
					newModule = new CModule;
					cin >> newModule;
					timetable.push_back(newModule);
				}
			}
			else
			{
				newModule = new CModule;
				cin >> newModule;
				timetable.push_back(newModule);
			}
		}
		else if(choice == 2)
		{
			if(!timetable.empty())
			{
				for(vector<CModule *>::iterator it = timetable.begin(); it != timetable.end(); it++)
				{
					CModule* tt = *it;
					if(tt->day.dayOfWeek == 1)
						cout << tt << endl;
				}

				for(vector<CModule *>::iterator it = timetable.begin(); it != timetable.end(); it++)
				{
					CModule* tt = *it;
					if(tt->day.dayOfWeek == 2)
						cout << tt << endl;
				}

				for(vector<CModule *>::iterator it = timetable.begin(); it != timetable.end(); it++)
				{
					CModule* tt = *it;
					if(tt->day.dayOfWeek == 3)
						cout << tt << endl;
				}

				for(vector<CModule *>::iterator it = timetable.begin(); it != timetable.end(); it++)
				{
					CModule* tt = *it;
					if(tt->day.dayOfWeek == 4)
						cout << tt << endl;
				}

				for(vector<CModule *>::iterator it = timetable.begin(); it != timetable.end(); it++)
				{
					CModule* tt = *it;
					if(tt->day.dayOfWeek == 5)
						cout << tt << endl;
				}
			}
			else
			{
				cout << "No data entered" << endl;
			}
		}
		else 
		{
			break;
		}

		system("pause");
	}

	while (timetable.size() > 0)
	{
		CModule * tt = timetable.back();
		delete tt;
		timetable.pop_back();
	}
}