#include <iostream>
#include <vector>
#include "Employee.h"
#include "Lecturer.h"
#include "Person.h"
#include "Student.h"
#include "TechnicalOfficer.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::getline;

int main()
{
	int decision;
	string Continue;
	string goOn;
	cout << "Personal Data Adminstrator" << endl;
	cout << "1. Lecturer \n" << "2. Technical Officer \n" << "3. Student \n" << "4. Print all data \n" << endl; 
	do
	{
		cout << "Please enter number 1-4" << endl;
		cin >> decision;
		while(decision >= 5)
		{
			cout << "Error, please enter again" << endl;
			cin >> decision;
		}
		CPerson * person;
		
		if (decision == 1)
		{
			string nameM;
			int ageM;
			string NRICM;
			string employeeIDM;
			string qualificationM;
			string DepartmentM;
			string DesignationM;
			cout << "Lecturer" << endl;
			person = new CLecturer;

			cout << "Please enter the name" << endl;
			cin.ignore();
			getline(cin, nameM);
			((CLecturer*) person)->setName(nameM);

			cout << "Please enter the age" << endl;
			cin >> ageM;
			((CLecturer*) person)->setAge(ageM);

			cout << "Please enter the NRIC" << endl;
			cin.ignore();
			getline (cin, NRICM);
			((CLecturer*) person) ->setNRIC(NRICM);

			cout << "Please enter Employee ID" << endl;
			///cin.ignore();
			getline (cin, employeeIDM);
			((CLecturer*) person)->setEmployeeID(employeeIDM);

			cout << "Please enter qualification" << endl;
			//cin.ignore();
			getline(cin, qualificationM);
			((CLecturer*) person)->setQualification(qualificationM);

			cout << "Please enter department" << endl;
			getline(cin, DepartmentM);
			((CLecturer*) person)->setDepartment(DepartmentM);

			cout << "Please enter designation" << endl;
			getline(cin, DesignationM);
			((CLecturer*) person) ->setDesignation(DesignationM);
			cout << endl;


			person -> printTest();
		}
		else if (decision == 2)
		{
			string nameM;
			int ageM;
			string NRICM;
			string employeeIDM;
			string qualificationM;

			cout << "Technical Officer" << endl;
			person = new CTechnicalOfficer;
			cout << "Please enter name" << endl;
			cin.ignore();
			getline(cin, nameM);
			((CTechnicalOfficer*) person)->setName(nameM);

			cout << "Please enter age" << endl;
			cin >> ageM;
			((CTechnicalOfficer*) person) ->setAge(ageM);

			cout << "Please enter NRIC" << endl;
			cin.ignore();
			getline(cin, NRICM);
			((CTechnicalOfficer*) person)->setNRIC(NRICM);

			cout << "Please enter Employee ID" << endl;
			getline(cin, employeeIDM);
			((CTechnicalOfficer*) person)->setEmployeeID(employeeIDM);

			cout << "Please enter qualification" << endl;
			getline(cin, qualificationM);
			((CTechnicalOfficer*) person)->setQualification(qualificationM);
			person ->printTest();
		}
		else if (decision == 3)
		{
			cout << "Student" << endl;
			person = new CStudent;

			string nameM;
			int ageM;
			string NRICM;
			string adminNoM;

			cout << "Please enter name" << endl;
			cin.ignore();
			getline(cin, nameM);
			((CStudent*) person) ->setName(nameM);

			cout << "Please enter age" << endl;
			cin >> ageM;
			((CStudent*) person) ->setAge(ageM);

			cout << "Please enter NRIC" << endl;
			cin.ignore();
			getline(cin, NRICM);
			((CStudent*) person) ->setNRIC(NRICM);

			cout << "Please enter admin no" << endl;
			getline(cin , adminNoM);
			((CStudent*) person) ->setAdminNo(adminNoM);

			person ->printTest();
		}
		else if (decision == 4)
		{
			cout << "Print all data" << endl;
		}
		else
		{
			cout << "Error" << endl;
		}
		cout << "Do you want to continue?" << endl;
		cin >> Continue;

	} while(Continue == "Y" || Continue == "y");
}