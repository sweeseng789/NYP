#pragma once
class CDay
{
public:
	CDay();
	~CDay();

	void setTimeData(const int hour, const int min, const int dayOfWeek);

	static unsigned Mon_hr;
	static unsigned Mon_min;
	static unsigned Tue_hr;
	static unsigned Tue_min;
	static unsigned Wed_hr;
	static unsigned Wed_min;
	static unsigned Thur_hr;
	static unsigned Thur_min;
	static unsigned Fri_hr;
	static unsigned Fri_min;
private:
	int dayOfWeek;
	int startTime_hr;
	int startTime_min;
	int endTime_hr;
	int endTime_min;
};

