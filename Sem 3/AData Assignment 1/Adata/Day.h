#pragma once
class CDay
{
public:
	CDay(void);
	~CDay(void);
	
	void setTime(int start_hour, int start_min, int hour, int min, int dayofWeek);

	int getHour();
	int getMin();
	int getSHour();
	int getSMin();

	int dayOfWeek;
private:
	int hour;
	int min;
	int start_hr;
	int start_min;
};

