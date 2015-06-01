#include <iostream>
#include "MyExcept.h"

using std::cin;
using std::cout;
using std::endl;

void main()
{
	while (true) {
		int dividend = 0;
		int divisor = 0;
		int quotient = 0;

		cout << "Enter dividend: ";
		cin >> dividend;

		cout << "Enter divisor: ";
		cin >> divisor;

		try {
			if (divisor == 0)
				throw MyExcept(100);
			else if (divisor < 0)
				throw MyExcept(101);
		}

		catch (MyExcept me) {
			cout << "Error: " << me.getErrorMsg() << endl;
		}

		try {
			if (dividend == 0)
				throw MyExcept(200);
			else if (dividend < 0)
				throw MyExcept(201);
		}
		catch (MyExcept me) {
			cout << "Error: " << me.getErrorMsg() << endl;
		}

		system("pause");
	}
}