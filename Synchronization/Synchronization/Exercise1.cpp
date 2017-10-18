/*

#include <process.h>
#include <windows.h>
#include <conio.h>
#include <iostream>

using namespace std;

void threadFunction1(void *pParam);
void threadFunction2(void *pParam);

HANDLE h_Event1, h_Event2;

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

ulThreadHandle1 = _beginthread(threadFunction1, 0, 0);
ulThreadHandle2 = _beginthread(threadFunction2, 0, 0);

Sleep(10);

while (true)
{
Sleep(20);
int sel;

printf("\nMenu\n"
"1 - Signal Thread 1\n"
"2 - Signal Thread 2\n"
"3 - Signal Thread 1 and Thread 2\n"
"4 - Terminate\n");

scanf_s("%i", &sel);

switch (sel)
{
default:
printf("Invalid option!\n");
break;
case 1:
SetEvent(h_Event1);
break;
case 2:
SetEvent(h_Event2);
break;
case 3:
SetEvent(h_Event1);
SetEvent(h_Event2);
break;
case 4:
TerminateThread((HANDLE)ulThreadHandle1, 0);
TerminateThread((HANDLE)ulThreadHandle2, 0);
CloseHandle(h_Event1);
CloseHandle(h_Event2);
printf("Threads Terminated\n");
return;
break;
}
}
}

void threadFunction1(void *pParam)
{
while (true)
{
WaitForSingleObject(h_Event1, INFINITE);
printf("\nThread 1 signaled");
}
}

void threadFunction2(void *pParam)
{
while (true)
{
WaitForSingleObject(h_Event2, INFINITE);
printf("\nThread 2 signaled");
}
}

*/