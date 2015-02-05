#pragma once
#include <iostream>
using std::cin;
using std::cout;
using std::endl;

class CQueue
{
public:
	CQueue(void);
	~CQueue(void);
	void insert(int);
	void deleteQueue();
	void ShowAll();
private:
	int queue[10];
	int head, tail, max;
};

