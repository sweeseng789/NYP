#include "Queue.h"


CQueue::CQueue(void)
{
	head = tail  =-1;
}


CQueue::~CQueue(void)
{
}

void CQueue::insert(int a)
{
	/*if (tail > 9)
	{
		cout << "Error" << endl;
		head = tail = -1;
		return;
	}
	queue[++tail] = a;
	cout << a << " inserted" << endl;*/
	if ( (tail + 1) % 10 == head)
	{
		cout << "Queue is full" << endl;
		return;
	}
	tail = (tail + 1) % 10;
	queue[tail] = a;
	if (head == -1)
	{
		head = 0;
	}
}

void CQueue::deleteQueue()
{
	/*if (tail == head)
	{
		cout << "Queue is empty" << endl;
	}
	cout << queue[++head] << " is deleted" << endl;*/
	int testing = 0;

	if (head == -1)
	{
		cout << "queue is empty" << endl;
	}

	testing = queue[head];
	queue[head] = 0;

	if (head == (tail +1)%10)
	{
		head = tail = -1;
	}
	else
	{
		head = (head + 1)%10;
	}
}

void CQueue::ShowAll()
{
	for (int a = 0; a < (tail +1)%10; a++)
	{
		cout << queue[a] << endl;
	}
}
