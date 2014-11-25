#pragma once

class CDate
{
public:
	CDate(void);
	~CDate(void);
	void setDate(int yearM, int monthM, int dayM);

	int returnYear(void) const;
	int returnMonth(void) const;
	int returnDay(void) const;
protected:
	int month;
	int year;
	int day;
};

