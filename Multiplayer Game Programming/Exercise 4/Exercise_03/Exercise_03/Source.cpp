#include <Windows.h>
#include <iostream>
#include <mutex>

using namespace std;
#define EXPECTING_NUMBER 100000000 // 100M
#define THREAD_COUNT 2
#define LOOP_COUNT (EXPECTING_NUMBER / (THREAD_COUNT*2))
int sum = 0;
HANDLE hMutex;

void mutexGuarding()
{
	//std::lock_guard<std::mutex> guard(mu);
	Sleep(1000);
	sum += 2;
}

DWORD WINAPI ThreadFunction(void *arg)
{
	for (int i = 0; i < LOOP_COUNT; ++i) 
	{
		WaitForSingleObject(hMutex, INFINITE);
		sum += 2;
		ReleaseMutex(hMutex);
	}
	return 0;
}
int main()
{
	HANDLE hThread[THREAD_COUNT];
	DWORD dwThreadID[THREAD_COUNT];

	cout << "Calculating expectation result is " << EXPECTING_NUMBER << endl;
	hMutex = CreateMutex(NULL, FALSE, NULL);

	for (int i = 0; i < THREAD_COUNT; i++) 
	{
		hThread[i] = CreateThread(NULL, 0, ThreadFunction, NULL, 0, &dwThreadID[i]);
		if (hThread == 0)
		{
			cout << "CreateThread() error" << endl;
			exit(1);
		}
	}
	WaitForMultipleObjects(THREAD_COUNT, hThread, TRUE, INFINITE);
	CloseHandle(hMutex);

	cout << "Calculation result is with thread is " << sum << endl;
	system("Pause");
}
