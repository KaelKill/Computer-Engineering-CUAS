/*
#include <process.h>
#include <windows.h>
#include <iostream>

using namespace std;

void ThreadFunction(void *pParam);

void main(void)				// Primary Thread
{
	unsigned long ulThreadHandle = 0;

	ulThreadHandle = _beginthread(ThreadFunction, 0, NULL);
	printf("Thread handle: %x\n", ulThreadHandle);

	Sleep(1000);

	TerminateThread((HANDLE)ulThreadHandle, 0);
	

}

void ThreadFunction(void *pParam)		// Secundary Thread
{

	while (1)
	{
		printf("Sample Text, Thread is running...\n")
		Sleep(10);
	}
}
*/