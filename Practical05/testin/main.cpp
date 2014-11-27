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
	int totalcount = 0;
	int decision;
	CPerson * studentData[10];
	CPerson * lecturerData[10];
	CPerson * technicalOfficerData[10];
	int studentM = 0;
	int lecturerM = 0;
	int TOM = 0;

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
			getline (cin, employeeIDM);
			((CLecturer*) person)->setEmployeeID(employeeIDM);

			cout << "Please enter qualification" << endl;
			getline(cin, qualificationM);
			((CLecturer*) person)->setQualification(qualificationM);

			cout << "Please enter department" << endl;
			getline(cin, DepartmentM);
			((CLecturer*) person)->setDepartment(DepartmentM);

			cout << "Please enter designation" << endl;
			getline(cin, DesignationM);
			((CLecturer*) person) ->setDesignation(DesignationM);

			lecturerData[((CLecturer *) person) ->returnLcount()] = person;
			lecturerM ++;
			cout << endl;
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

			technicalOfficerData[((CTechnicalOfficer *) person) ->returnTOcount()] = person;
			TOM ++;
			cout << endl;
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

			studentData[((CStudent *) person) ->returnStudentCount()] = person;
			studentM ++;
			cout << endl;
		}
		totalcount = studentM + lecturerM + TOM;

		if (decision == 4 || totalcount == 5)
		{
			cout << "Print all data" << endl;
			if ( studentM >= 1 || lecturerM >= 1 || TOM >= 1)
			{
				for (int a = 1; a <= lecturerM; a++)
				{
					((CLecturer *) lecturerData[a]) ->printTest();
				}

				for (int a = 1; a <= TOM; a++)
				{
					((CTechnicalOfficer *) technicalOfficerData[a]) ->printTest();
				}
				
				for (int a = 1; a <= studentM ; a++)
				{
					((CStudent *) studentData[a]) ->printTest();
				}
			}
		}
	} while(totalcount != 5);	

	//delete
		for (int a = 1; a <= lecturerM; a++)
		{
			delete lecturerData[a];
		}

		for (int a = 1; a <= TOM; a++)
		{
			delete technicalOfficerData[a];
		}
				
		for (int a = 1; a <= studentM ; a++)
		{
			delete studentData[a];
		}
}