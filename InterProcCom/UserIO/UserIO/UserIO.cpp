/************************************
Computer Engineering
Homework IPC - UserIO
Author: Kael Ricardo Kill
************************************/

#include <process.h>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>

#define FILENAME "mapfile.mf"

struct HANDLES
{
	void* lpv_FileMappingPointer;
	HANDLE	startWork,
		semaphore,
		calcDone,
		file,
		fileMapping;
};

void init_config(HANDLES *h);
void get_numbers(HANDLES *h);
void close_handles(HANDLES *h);

void main()
{
	char sel;
	struct HANDLES h = { 0 };

	init_config(&h);

	do{
		get_numbers(&h);
		ReleaseSemaphore(h.semaphore, 3, NULL);
		WaitForSingleObject(h.calcDone, INFINITE);
		printf("Result = %f\n", *((float*)h.lpv_FileMappingPointer + 6));
		
		do {
			printf("Repeat? y/n\n");
			sel = _getch();
		} while ((sel != 'y') && (sel != 'Y') && (sel != 'n') && (sel != 'N'));
	} while ((sel != 'n') && (sel != 'N'));

	*((float*)h.lpv_FileMappingPointer + 7) = (float)-1;
	close_handles(&h);
	//_getch();
	system("pause");
}

void init_config(HANDLES *h)
{
	printf("Init_config...");
	h->file = CreateFile(FILENAME,
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	h->fileMapping = CreateFileMapping(h->file,
		NULL,
		PAGE_READWRITE,
		0,
		0,
		"myFileMapping");

	h->lpv_FileMappingPointer = MapViewOfFile(h->fileMapping,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		8*sizeof(float));

	*((float*)h->lpv_FileMappingPointer + 7) = (float)1; // Controls the Worker loop, 1 = repeat, -1 = close

	h->startWork = CreateEvent(NULL, FALSE, FALSE, TEXT("startWork"));
	h->semaphore = CreateSemaphore(NULL, 0, 3, "Semaphore");
	Sleep(10);
	while(!(h->calcDone = OpenEvent(EVENT_ALL_ACCESS, FALSE, TEXT("calcDone")))) 
	{
		printf("Waiting for Client...\n");
		Sleep(1000);
	}
	SetEvent(h->startWork);
	Sleep(10);
	printf("Done!\n");
}

void get_numbers(HANDLES *h)
{
	printf("Write the numbers to compute:\n"
		"X1 = ");
	scanf_s("%f", ((float*)h->lpv_FileMappingPointer+0));
	printf("X2 = ");
	scanf_s("%f", ((float*)h->lpv_FileMappingPointer+1));
	printf("X3 = ");
	scanf_s("%f", ((float*)h->lpv_FileMappingPointer+2));
}

void close_handles(HANDLES *h)
{
	printf("Closing Handles...");
	UnmapViewOfFile(h->lpv_FileMappingPointer);
	CloseHandle(h->calcDone);
	CloseHandle(h->file);
	CloseHandle(h->fileMapping);
	CloseHandle(h->startWork);
	printf("Done!\n");
}
