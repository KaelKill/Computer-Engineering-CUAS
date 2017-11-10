/************************************
Computer Engineering
Homework IPC - Worker
Author: Kael Ricardo Kill
************************************/

#include <process.h>
#include <windows.h>
#include <conio.h>
#include <stdio.h>

struct HANDLES
{
	void* lpv_FileMappingPointer;
	unsigned long thread[4];
	HANDLE fileMapping,
		semaphore,
		startWork,
		calcDone,
		threadDone[4];
};

void init_config(HANDLES *h);
void close_handles(HANDLES *h);
void thread1(void *pParam);
void thread2(void *pParam);
void thread3(void *pParam);
void thread4(void *pParam);

void main() 
{
	struct HANDLES h = { 0 };
	init_config(&h);

	// Stay on the loop while the UserIO don't quit
	while (*((float*)h.lpv_FileMappingPointer + 7) != (float)-1) {}
		
	close_handles(&h);
	//_getch();
	system("pause");
 }

void init_config(HANDLES *h)
{
	printf("Init_config...");
	h->fileMapping = OpenFileMapping(FILE_MAP_ALL_ACCESS,
		FALSE,
		"myFileMapping");

	h->lpv_FileMappingPointer = MapViewOfFile(h->fileMapping,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		8*sizeof(float));

	h->calcDone = CreateEvent(NULL, FALSE, FALSE, TEXT("calcDone"));
	Sleep(10);
	while (!(h->startWork = OpenEvent(EVENT_ALL_ACCESS, FALSE, TEXT("startWork"))) )
	{
		printf("Waiting for Server...\n");
		Sleep(1000);
	}
	
	WaitForSingleObject(h->startWork, INFINITE);
	
	h->threadDone[0] = CreateEvent(NULL, FALSE, FALSE, NULL);
	h->threadDone[1] = CreateEvent(NULL, FALSE, FALSE, NULL);
	h->threadDone[2] = CreateEvent(NULL, FALSE, FALSE, NULL);
	h->threadDone[3] = CreateEvent(NULL, FALSE, FALSE, NULL);
	h->semaphore = OpenSemaphore(EVENT_ALL_ACCESS, FALSE, "Semaphore");
	
	h->thread[0] = _beginthread(thread1, 0, h);
	h->thread[1] = _beginthread(thread2, 0, h);
	h->thread[2] = _beginthread(thread3, 0, h);
	h->thread[3] = _beginthread(thread4, 0, h);
	
	Sleep(10);
	printf("Done!\n");
}

void close_handles(HANDLES *h)
{
	printf("Closing Handles...");
	TerminateThread((HANDLE)(h->thread[0]), 0);
	TerminateThread((HANDLE)(h->thread[1]), 0);
	TerminateThread((HANDLE)(h->thread[2]), 0);
	TerminateThread((HANDLE)(h->thread[3]), 0);
	UnmapViewOfFile(h->lpv_FileMappingPointer);
	CloseHandle(h->fileMapping);
	CloseHandle(h->semaphore);
	CloseHandle(h->startWork);
	CloseHandle(h->calcDone);
	CloseHandle(h->threadDone[0]);
	CloseHandle(h->threadDone[1]);
	CloseHandle(h->threadDone[2]);
	printf("Done!\n");
}

void thread1(void *pParam)
{
	HANDLES* h = (HANDLES*)pParam;
	float* numsThread = (float*)(h->lpv_FileMappingPointer);
	while (true) {
		WaitForSingleObject(h->semaphore, INFINITE);
		numsThread[3] = (numsThread[0] + 2 * numsThread[1] - 3 * numsThread[2]) / numsThread[0];
		SetEvent(h->threadDone[0]);
	}
}

void thread2(void *pParam)
{
	HANDLES* h = (HANDLES*)pParam;
	float* numsThread = (float*)h->lpv_FileMappingPointer;
	while (true) {
		WaitForSingleObject(h->semaphore, INFINITE);
		numsThread[4] = (2 * numsThread[0] + 4 * numsThread[1]) / numsThread[1];
		SetEvent(h->threadDone[1]);
	}
}

void thread3(void *pParam)
{
	HANDLES* h = (HANDLES*)pParam;
	float* numsThread = (float*)h->lpv_FileMappingPointer;
	while (true) {
		WaitForSingleObject(h->semaphore, INFINITE);
		numsThread[5] = (numsThread[2] - numsThread[1]) / numsThread[2];
		SetEvent(h->threadDone[2]);
	}
}

void thread4(void *pParam)
{
	HANDLES* h = (HANDLES*)pParam;
	float* numsThread = (float*)h->lpv_FileMappingPointer;
	HANDLE hArray[3];
	hArray[0] = h->threadDone[0];
	hArray[1] = h->threadDone[1];
	hArray[2] = h->threadDone[2];

	while (true) {
		WaitForMultipleObjects(3, hArray, 1, INFINITE);
		numsThread[6] = numsThread[3] + numsThread[4] + numsThread[5];
		SetEvent(h->calcDone);
	}
}