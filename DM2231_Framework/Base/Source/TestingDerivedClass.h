#pragma once
#include <iostream>
#include "TestingBaseClass.h"

using std::cout;
using std::endl;

class TestingDerivedClass : public TestingBaseClass
{
public:
	TestingDerivedClass(void);
	~TestingDerivedClass(void);
};

