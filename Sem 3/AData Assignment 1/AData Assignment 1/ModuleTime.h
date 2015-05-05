#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::istream;
using std::ostream;

class CModuleTime
{
public:
	CModuleTime(void);
	~CModuleTime(void);
	friend istream & operator>> (istream & input, CModuleTime & passIn);

	unsigned returnHour();
	unsigned returnMinute();
private:
	unsigned hour;
	unsigned minute;
};

