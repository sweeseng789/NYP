#include <iostream>
using std::cin;
using std::cout;
using std::endl;

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

void main()
{
	int list[] = {34, 45, 12, 2, 456, 78, 103, 423, 67, 4};
	int list2[] = {34, 45, 12, 2, 456, 78, 103, 423, 67, 4 };

	quickSort(list, 0, 9);
	mergeSort(list2, 0, 9);

	for (unsigned a = 0; a < 10; ++a)
	{
		cout << list[a] << endl;
	}

	cout << endl;

	for (unsigned a = 0; a < 10; ++a)
	{
		cout << list2[a] << endl;
	}

	system("pause");
}