#include "MyExcept.h"



MyExcept::MyExcept()
{
}

MyExcept::MyExcept(int code)
{
	errorCode = code;
}


MyExcept::~MyExcept()
{
}

std::string MyExcept::getErrorMsg()
{
	std::string temp;

	if (errorCode == 0)
	{
		temp = "Error Code is not defined";
	}
	else if(errorCode== 100)
	{
		temp = "Divisor cannot be zero";
	}
	else if (errorCode == 101)
	{
		temp = "Divisor cannot be negative";
	}
	else if (errorCode == 200)
	{
		temp = "Diviend cannot be zero";
	}
	else if (errorCode == 201)
	{
		temp = "Diviend cannot be nagative";
	}
	else
	{
		temp = "No error";
	}

	return temp;
}