/*
#include <process.h>
#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

void threadFunction1(void *pParam);
void threadFunction2(void *pParam);
void threadFunction3(void *pParam);

HANDLE h_Event1;
HANDLE h_Event2;
HANDLE hSemaphore = 0;

void main() {

	unsigned long ulThreadHandle1, ulThreadHandle2;

	h_Event1 = CreateEvent(NULL, // Security Attributes
		FALSE,	// Manual Reset: 0 - no; 1 - yeah
		FALSE,	// Initial Stat: not set
		NULL);	// Name: no

	h_Event2 = CreateEvent(NULL, // Security Attributes
		FALSE,	// Manual Reset: 0 - no; 1 - yeah
		FALSE,	// Initial Stat: not set
		NULL);	// Name: no

	hSemaphore = CreateSemaphore(NULL, 0, 2, NULL);

	_beginthread(threadFunction1, 0, 0);
	_beginthread(threadFunction2, 0, 0);
	_beginthread(threadFunction3, 0, 0);

	Sleep(10);

	cout << "Press a key to set event 1" << endl;
	_getch();
	SetEvent(h_Event1);
	cout << "Press a key to set event 2" << endl;
	_getch();
	SetEvent(h_Event2);
	cout << "Press a key to release Semaphore" << endl;
	_getch();
	ReleaseSemaphore(hSemaphore, 2, NULL);

	Sleep(2000);
}

void threadFunction1(void *pParam)
{
	HANDLE h_Array[2];
	h_Array[0] = h_Event1;
	h_Array[1] = h_Event2;

	while (true)
	{
		WaitForMultipleObjects(2, h_Array, TRUE, INFINITE);
		printf("\nThread 1 signaled");
	}

}

void threadFunction2(void *pParam)
{
	while (true)
	{
		WaitForSingleObject(hSemaphore, INFINITE);
		printf("\nThread 2 signaled");
	}

}

void threadFunction3(void *pParam)
{
	while (true)
	{
		WaitForSingleObject(hSemaphore, INFINITE);
		printf("\nThread 3 signaled");
	}
}
*/