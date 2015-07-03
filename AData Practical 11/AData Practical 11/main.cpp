#include <iostream>
#include <vector>
#include "Colour.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

void bubbleSort(vector<int>&initList, int length)
{
	for (int iter = 1; iter < length; iter++)
	{
		for (int index = 0; index < length - iter; index++)
		{
			if (initList[index] > initList[index + 1])
			{
				int temp = initList[index];
				initList[index] = initList[index + 1];
				initList[index + 1] = temp;
			}
		}
	}
}

void bubbleSortColor(vector<CColour *>&initList, int length)
{
	for (int iter = 1; iter < length; iter++)
	{
		for (int index = 0; index < length - iter; index++)
		{
			if (initList[index]->getRed() > initList[index + 1]->getRed())
			{
				CColour* temp = initList[index];
				initList[index] = initList[index + 1];
				initList[index + 1] = temp;
			}
			else if (initList[index]->getRed() == initList[index + 1]->getRed())
			{
				if (initList[index]->getGreen() > initList[index + 1]->getGreen())
				{
					CColour* temp = initList[index];
					initList[index] = initList[index + 1];
					initList[index + 1] = temp;
				}
				else if (initList[index]->getGreen() == initList[index + 1]->getGreen())
				{
					if (initList[index]->getBlue() > initList[index + 1]->getBlue())
					{
						CColour* temp = initList[index];
						initList[index] = initList[index + 1];
						initList[index + 1] = temp;
					}
				}
			}
		}
	}
}

void selectionSort(vector<int>&initList, int length)
{
	int minIndex = 0;

	for (int loc = 0; loc < length; loc++)
	{
		for (int loc2 = loc + 1; loc2 < length; loc2++)
		{
			if (initList[loc2] < initList[loc])
			{
				int temp = initList[loc];
				initList[loc] = initList[loc2];
				initList[loc2] = temp;
			}
		}
	}
}

void InsertionSort(vector<int> &initList, int length)
{
	int location, temp;

	for (int firstOutOfOrder = 1; firstOutOfOrder < length; firstOutOfOrder++)
	{
		//Check against previous element
		if (initList[firstOutOfOrder] < initList[firstOutOfOrder - 1])
		{
			temp = initList[firstOutOfOrder];
			//initialize where to start moving back
			location = firstOutOfOrder;

			do
			{
				initList[location] = initList[location - 1];
				location--;
			} while (location > 0 && initList[location - 1] > temp);
			initList[location] = temp;
		}
	}
}

void main()
{
	vector<CColour*> colourList;

	int initList[] = {34, 45, 12, 2, 456, 78, 103, 423, 67, 4};
	vector<int>list(initList, initList + sizeof(initList)/4);
	int RedList[] = {144, 21, 144, 243, 144, 32, 123, 21};
	int GreenList[] = {33, 134, 234, 123, 33, 123, 21, 231};
	int BlueList[] = {123, 1, 12, 212, 21, 78, 1, 2};

	//Set colour parameters
	for (unsigned a = 0; a < 8; a++)
	{
		CColour * color = new CColour(RedList[a], GreenList[a], BlueList[a]);
		color->number = a;
		colourList.push_back(color);
	}

	for (vector<CColour *>::iterator i = colourList.begin(); i != colourList.end(); i++)
	{
		CColour * color = (CColour*)*i;

		cout << "RGB " << color->number + 1 << ": " << color->getRed() << ", " << color->getGreen() << ", " << color->getBlue() << endl;
	}

	cout << endl;

	//bubbleSort(list, list.size());
	//selectionSort(list, list.size());
	//InsertionSort(list, list.size());
	bubbleSortColor(colourList, colourList.size());

	for (vector<CColour *>::iterator i = colourList.begin(); i != colourList.end(); i++)
	{
		CColour * color = (CColour*)*i;

		cout << "RGB " << color->number + 1 << ": " << color->getRed() << ", " << color->getGreen() << ", " << color->getBlue() << endl;
	}

	system("pause");
}