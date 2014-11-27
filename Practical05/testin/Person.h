#pragma once
#include <string>
using std::string;

class CPerson
{
public:
	CPerson(void);
	~CPerson(void);

	
	virtual void printTest(void);
	void setName(string nameM);
	void setNRIC(string NRICM);
	void setAge(int ageM);

	virtual string returnNRIC(void) const;
	string returnName(void) const;
	virtual int returnAge(void) const;
	virtual int returnCount(void) const;
protected:
	string name;
	int age;
	string NRIC;
};

