#pragma once

class CDate
{
public:
	CDate(void);
	CDate(int yearM, int monthM, int dayM);
	~CDate(void);
	void setDate(int yearM, int monthM, int dayM);
	void calcDateDifference();
	void printData();

	int returnYear(void) const;
	int returnMonth(void) const;
	int returnDay(void) const;

	int returnDateDiff(void) const;

	//int getYearDiff(CDate& anotherDate);
protected:
	int month;
	int year;
	int day;

	int dateDiff;
};

