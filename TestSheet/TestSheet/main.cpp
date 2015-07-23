#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::vector;

int testing[] = { 1 };
vector<int> list(testing, testing + sizeof(testing) / 4);

bool BinarySearch(int valueToFind)
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

//Merge Sort
void merge(int data[], int first, int middle, int last)
{
	//temp array to hold first list
	int * temp = new int[middle - first + 1];

	int i, j, k;
	for (j = first, i = 0; j <= middle; i++, j++)
	{
		temp[i] = data[j];//Duplicate first list
	}

	i = 0; k = first;

	while (k < j && j <= last)
	{
		//if element from 1st list < 2nd list
		if (temp[i] <= data[j])
			data[k++] = temp[i++]; //copy first 1st list
		else
			data[k++] = data[j++]; //copy from 2nd list
	}

	while (k < j)//copy remaining to temp if any
	{
		data[k++] = temp[i++];
	}

	delete[] temp; // remove temp array
}
void mergeSort(int data[], int first, int last)
{
	if (first < last)
	{
		int middle = (first + last) / 2;
		mergeSort(data, first, middle);
		mergeSort(data, middle + 1, last);
		merge(data, first, middle, last);
	}
}

//Quick Sort
int partition(int data[], int first, int last)
{
	int middle = (first + last) / 2;

	{
		int temp = data[first];
		data[first] = data[last];
		data[last] = temp;
	}

	int pivot = data[first];
	int smallIndex = first;

	for (unsigned i = first + 1; i <= last; i++)
	{
		if (data[i] < pivot)
		{
			smallIndex++;

			int temp = data[smallIndex];
			data[smallIndex] = data[i];
			data[i] = temp;
		}
	}

	int temp = data[first];
	data[first] = data[smallIndex];
	data[smallIndex] = temp;

	return smallIndex;
}
void quickSort(int data[], int first, int last)
{
	if (first < last)
	{
		int pivotLocation = partition(data, first, last);

		quickSort(data, first, pivotLocation - 1);
		quickSort(data, pivotLocation + 1, last);
	}
}

void main()
{
	cout << "HelloWorld" << endl;
}