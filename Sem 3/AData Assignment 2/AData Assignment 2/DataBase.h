#pragma once

#include <iostream>
#include "Data.h"
#include "UI.h"

class CDataBase
{
public:
	CDataBase();
	~CDataBase();

	bool binarySearch(string nameToFind, int IDtoFind, bool findByID);
	bool sequentialSearch(string nameToFind, int IDtoFind, bool findByID);

	void addData();
	void deleteData();
	void searchData();
	void sortData();
	void printAll();
private:
	static int count;
	static bool sortByName;
	static bool sortByID;
	static int location;

	CData data[20];
};

