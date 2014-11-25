#pragma once

class CDate
{
public:
	CDate(void);
	~CDate(void);
	void setDate(int yearM, int monthM, int dayM);
	void calcDateDifference();

	int returnYear(void) const;
	int returnMonth(void) const;
	int returnDay(void) const;
protected:
	int month;
	int year;
	int day;

	int monthD;
	int yearD;
	int dayD;

	int age;
};

