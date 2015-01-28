#include "LinkList.h"

void main(void)
{
	CLinkList myLL;

	while (true)
	{
		int insChoice;

		cout << "Please enter an integer to add: ";
		cin >> insChoice;

		//myLL.InsertForward(insChoice);
		myLL.Insert(insChoice);

		myLL.PrintAll();
		cout << endl;
	}	
		
}