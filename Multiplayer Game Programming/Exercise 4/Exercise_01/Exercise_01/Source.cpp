#include <iostream>
#include <Windows.h>
using std::cin;
using std::cout;
using std::endl;

HANDLE hThread[2];
DWORD IDThread[2];


static int g_n = 0;

UINT ThreadOne(LPVOID lParam)
{
	for (int i = 0; i < 10; i++) {		cout << "Thread 1: " << ++g_n << "\n";
	}
	return 0;
}
UINT ThreadTwo(LPVOID lParam)
{
	for (int i = 0; i < 10; i++) {
		cout << "Thread 2: " << ++g_n << "\n";
	}
	return 0;
}

int main(void)
{
	hThread[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadOne, (LPVOID)NULL, 0, &IDThread[0]);
	hThread[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadTwo, (LPVOID)NULL, 0, &IDThread[1]);
	std::cout << hThread[0] << std::endl;
	std::cout << IDThread[0] << std::endl;
	std::cout << hThread[1] << std::endl;
	std::cout << IDThread[1] << std::endl;
	WaitForMultipleObjects(2, hThread, TRUE, INFINITE);
	return 0;
}