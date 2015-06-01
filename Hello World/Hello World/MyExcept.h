#pragma once
#include <string>

using namespace std;
class MyExcept
{
public:
	MyExcept();
	MyExcept(int code);
	~MyExcept();
	std::string getErrorMsg();
private:
	int errorCode;
};

