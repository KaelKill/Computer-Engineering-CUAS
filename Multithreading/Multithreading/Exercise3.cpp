/*
#include <process.h>
#include <windows.h>
#include <iostream>

struct DATA {
	char string[20];
	int  number;
};

void ThreadFunction(void *pParam);

void main(void)				// Primary Thread
{
	DATA data = { 0 };
	printf("Enter a number: ");
	scanf_s("%d", &data.number);
	printf("Enter a string: ");
	scanf_s("%s", &data.string, sizeof(data.string));
	
	
	unsigned long ulThreadHandle = 0;

	ulThreadHandle = _beginthread(ThreadFunction, 0, (void*)&data);
	printf("Thread handle: %x\n", ulThreadHandle);

	Sleep(1000);

	TerminateThread((HANDLE)ulThreadHandle, 0);


}

void ThreadFunction(void *pParam)		// Secundary Thread
{
	DATA dataThread = (DATA)*(DATA*)pParam;

	while (1)
	{
		printf("Thread is running...\n");
		printf("Entered string:%s\n", dataThread.string);
		printf("Entered number %d\n", dataThread.number);
		Sleep(250);
	}
}
*/