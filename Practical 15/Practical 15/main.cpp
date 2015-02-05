#include <iostream>
#include "Queue.h"
using std::cin;
using std::cout;
using std::endl;

void main()
{
	CQueue queue;
	queue.insert(10);
	queue.insert(20);
	queue.insert(30);
	queue.insert(40);
	queue.ShowAll();

	queue.deleteQueue();
	cout << endl;
	queue.ShowAll();
	system("pause");
}