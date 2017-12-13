/*
#include <process.h>
#include <windows.h>
#include <conio.h>
#include <stdio.h>

void main(void)
{
	//HANDLE h_File;
	HANDLE h_FileMapping;
	LPVOID lpv_FileMappingPointer;

	h_FileMapping = OpenFileMapping(FILE_MAP_READ,
		FALSE,
		"MyFirstFileMapping");

	lpv_FileMappingPointer = MapViewOfFile(h_FileMapping,
		FILE_MAP_READ,
		0,
		0,
		0);

	while (1)
	{
		if (*(int*)lpv_FileMappingPointer == 1)
			printf("Value is 1!\n");
		else
			printf("Value is 0!\n");

		Sleep(100);

		if (_kbhit())
			break;
	}

	UnmapViewOfFile(lpv_FileMappingPointer);

	CloseHandle(h_FileMapping);
}
*/