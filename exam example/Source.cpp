/*----------------------------------------------------
Solution for computer engineering exam example- CUAS

Author: Kael Kill   
16/03/2018
-----------------------------------------------------*/

#include <stdio.h>
#include <Windows.h>
#include <time.h> // used to create unique random numbers each time the you run the code
#include <omp.h>
#include <process.h>

// define a N number to manipulate N size array:
#define N 35000

void populateArray(int *arr, int size);
void checkArray(int *arr, bool check);
void createRandomNumbers(int *nums, int nNums);
void initThreads(struct data *s);
void showResults(struct data s);

void searchThread1(void *pParam);
void searchThread2(void *pParam);
void searchThread3(void *pParam);

// use a struct to pass data through process and avoid global variables;
struct data{
	int arr[N+1];
    int number[3];
    int index[3];
};

HANDLE hSemaphore;
HANDLE hFound1, hFound2, hFound3, hArray[3];

void main() {
    struct data s = {};
	
	//DWORD start, end; // delete this if you don't need to measure time

    /* initiate handles and threads */
    initThreads(&s);
	
	/* 1 - generate a test set of descending integer numbers: (using openMPI) */
	//start = GetTickCount();
	populateArray(s.arr, N);
	checkArray(s.arr, false); // true to show array index and content, false to skip (just for debug)
	//end = GetTickCount();
	//printf("Elapsed time = %d ms\n", (end - start)); // 812 ms using one core/without openmpi, 200ms with openmpi
	
	/* 2 - create three random numbers: */
    createRandomNumbers(s.number, 3);
	printf("Search for:\n1 = %d\n2 = %d\n3 = %d\n", s.number[0], s.number[1], s.number[2]);

	/* 3-  perform a parallel search for the numbers: (using multithreading e sync) */
    ReleaseSemaphore(hSemaphore, 3, NULL);

    /* 4 - display search results: */
    WaitForMultipleObjects(3, hArray, true, INFINITE);
    showResults(s);

    system("pause");

}

void populateArray(int *arr, int size) {
	// create an array of N descending integer
	int i;

	// comment the '#pragma" line to compare the time to generate the array. 
	// you should notice a decrease in the time based in the number of 
    #pragma omp parallel for  
	for (i = size; i >= 0; i--) {
		arr[i] = size-i;
	}
}

void checkArray(int *arr, bool check) {
	if (check) {
		int i;
		for (i = 0; i <= N; i++) {
			printf("[%d] - %d \n",i, arr[i]);
		}
		system("pause");
	}
}

void createRandomNumbers(int *num, int nNums) {
    int i;
    srand(time(NULL));
    for (i = 0; i < nNums; i++) {
        num[i] = rand() % N;
    }
}

void initThreads(data *s) {
    hSemaphore = CreateSemaphore(NULL, 0, 3, NULL);

    hFound1 = CreateEvent(NULL, FALSE, FALSE, NULL);
    hFound2 = CreateEvent(NULL, FALSE, FALSE, NULL);
    hFound3 = CreateEvent(NULL, FALSE, FALSE, NULL);

    hArray[0] = hFound1;
    hArray[1] = hFound2;
    hArray[2] = hFound3;

    _beginthread(searchThread1, 0, (void*)s);
    _beginthread(searchThread2, 0, (void*)s);
    _beginthread(searchThread3, 0, (void*)s);
}

void showResults(struct data s) {
    printf("Found %d in index %d\n", s.number[0], s.index[0]);
    printf("Found %d in index %d\n", s.number[1], s.index[1]);
    printf("Found %d in index %d\n", s.number[2], s.index[2]);
}

void searchThread1(void *pParam) {
    struct data *s = (data*)pParam;
    int i;
    while (true) {
        WaitForSingleObject(hSemaphore, INFINITE);
        for (i = 0; i < N; i++) {
            if (s->arr[i] == s->number[0]) {
                s->index[0] = i;
                //printf("found %d in %d", s->number[0], s->index[0]);
                SetEvent(hFound1);
            }
        }
    }
}
void searchThread2(void *pParam) {
    struct data *s = (data*)pParam;
    int i;
    while (true) {
        WaitForSingleObject(hSemaphore, INFINITE);
        for (i = 0; i < N; i++) {
            if (s->arr[i] == s->number[1]) {
                s->index[1] = i;
                SetEvent(hFound2);
            }
        }
    }
}
void searchThread3(void *pParam) {
    struct data *s = (data*)pParam;
    int i;
    while (true) {
        WaitForSingleObject(hSemaphore, INFINITE);
        for (i = 0; i < N; i++) {
            if (s->arr[i] == s->number[2]) {
                s->index[2] = i;
                SetEvent(hFound3);
            }
        }
    }
}