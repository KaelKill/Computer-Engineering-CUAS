/************************************
Computer Engineering
Homework Synchronization
Solution for exercise 3

Author: Kael Ricardo Kill
************************************/

#include <process.h>
#include <windows.h>
#include <conio.h>
#include <iostream>

void thread1(void *pParam);
void thread2(void *pParam);
void thread3(void *pParam);
void thread4(void *pParam);

HANDLE hSemaphore;
HANDLE hEvent1, hEvent2, hEvent3, hEvent4;

void main() {

	float nums[7]; // {x1,x2,x3,y1,y2,y3,y4}
	char sel = 'y';

	unsigned long ulThreadHandle1, ulThreadHandle2, ulThreadHandle3, ulThreadHandle4;

	// Create events and start threads:
	hEvent1 = CreateEvent(NULL, FALSE, FALSE, NULL);
	hEvent2 = CreateEvent(NULL, FALSE, FALSE, NULL);
	hEvent3 = CreateEvent(NULL, FALSE, FALSE, NULL);
	hEvent4 = CreateEvent(NULL, FALSE, FALSE, NULL);
	hSemaphore = CreateSemaphore(NULL, 0, 3, NULL);

	ulThreadHandle1 = _beginthread(thread1, 0, (void*)nums);
	ulThreadHandle2 = _beginthread(thread2, 0, (void*)nums);
	ulThreadHandle3 = _beginthread(thread3, 0, (void*)nums);
	ulThreadHandle4 = _beginthread(thread4, 0, (void*)nums);

	do {
		// get numbers
		printf("Write the number to compute:\n"
			"X1 = ");
		scanf_s("%f", &nums[0]);
		printf("X2 = ");
		scanf_s("%f", &nums[1]);
		printf("X3 = ");
		scanf_s("%f", &nums[2]);

		ReleaseSemaphore(hSemaphore, 3, NULL);

		WaitForSingleObject(hEvent4, INFINITE);

		// Print results
		printf("Y1 = %f\n", nums[3]);
		printf("Y2 = %f\n", nums[4]);
		printf("Y3 = %f\n", nums[5]);
		printf("Y4 = %f\n", nums[6]);

		do {
			printf("Repeat? y/n\n");
			sel = _getch();
		} while ((sel != 'y') && (sel != 'Y') && (sel != 'n') && (sel != 'N'));
	} while ((sel != 'n') && (sel != 'N'));


	TerminateThread((HANDLE)ulThreadHandle1, 0);
	TerminateThread((HANDLE)ulThreadHandle2, 0);
	TerminateThread((HANDLE)ulThreadHandle3, 0);
	TerminateThread((HANDLE)ulThreadHandle4, 0);

	CloseHandle(hEvent1);
	CloseHandle(hEvent2);
	CloseHandle(hEvent3);
	CloseHandle(hEvent4);
	CloseHandle(hSemaphore);

	printf("Threads and events terminated...\n");
}

void thread1(void *pParam) {
	float *numsThread = (float*)pParam;

	while (true) {
		WaitForSingleObject(hSemaphore, INFINITE);
		numsThread[3] = (numsThread[0] + 2 * numsThread[1] - 3 * numsThread[2]) / numsThread[0];
		SetEvent(hEvent1);
	}
}

void thread2(void *pParam) {
	float *numsThread = (float*)pParam;

	while (true) {
		WaitForSingleObject(hSemaphore, INFINITE);
		numsThread[4] = (2 * numsThread[0] + 4 * numsThread[1]) / numsThread[1];
		SetEvent(hEvent2);
	}
}

void thread3(void *pParam) {
	float *numsThread = (float*)pParam;
	while (1) {
		WaitForSingleObject(hSemaphore, INFINITE);
		numsThread[5] = (numsThread[2] - numsThread[1]) / numsThread[2];
		SetEvent(hEvent3);
	}
}

void thread4(void *pParam) {
	float *numsThread = (float*)pParam;

	HANDLE hArray[3];
	hArray[0] = hEvent1;
	hArray[1] = hEvent2;
	hArray[2] = hEvent3;

	while (true) {
		WaitForMultipleObjects(3, hArray, 1, INFINITE);
		numsThread[6] = numsThread[3] + numsThread[4] + numsThread[5];
		SetEvent(hEvent4);
	}
}