/************************************
Computer Engineering
Homework Multithreading
Solution for exercise 4

Author: Kael Ricardo Kill
************************************/

#include <process.h>
#include <windows.h>
#include <iostream>
#include <stdio.h>

void ThreadFunction(void *pParam);
void createThread();
void termThread();

int main(void)				// Primary Thread
{
	int sel;
	while(true) {
		// Print options
		printf("\n- 1 to create a Thread\n"	
			   "- 2 to terminater a specific Thread\n"
			   "- 3 to exit\n");
		scanf_s("%d", &sel);

		switch (sel)
		{
		case 1:
			createThread();
			break;
		case 2:
			termThread();
			break;
		case 3:
			return 0;
			break;
		default:
			printf("-- Invalid option!\n");
			break;
		}
	}
}

void ThreadFunction(void *pParam)	
{
	int TID = (int)*(int*)pParam;
	while (1)
	{
		printf("\nI am Thread %i ...", TID);
		Sleep(2500);
	}
}

void createThread() // Create a new thread
{
	int threadNumber;
	unsigned long ulThreadHandle;

	printf("-- Enter a thread specific number: ");
	scanf_s("%d", &threadNumber);

	ulThreadHandle = _beginthread(ThreadFunction, 0, (void*)&threadNumber);
	printf("Thread handle: %lu\n", ulThreadHandle);
	Sleep(10);
}

void termThread() // Terminate a thread
{
	unsigned long ulThreadHandle;

	printf("-- Enter thread handle to terminate: ");
	scanf_s("%ul", &ulThreadHandle);
	TerminateThread((HANDLE)ulThreadHandle, 0);
}