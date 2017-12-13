#include <process.h>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>

void main(void)
{
	HANDLE h_File;
	HANDLE h_FileMapping;
	void* lpv_FileMappingPointer;

	h_File = CreateFile("file.mf",
		GENERIC_READ | GENERIC_WRITE,
		0,
		NULL,
		OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL,
		NULL);

	h_FileMapping = CreateFileMapping(h_File,
		NULL,
		PAGE_READWRITE,
		0,
		0,
		"MyFirstFileMapping");

	lpv_FileMappingPointer = MapViewOfFile(h_FileMapping,
		FILE_MAP_ALL_ACCESS,
		0,
		0,
		0);

	while (1)
	{
		*(int*)lpv_FileMappingPointer = 1;
		printf("Value is 1!\n");
		Sleep(100);

		*(int*)lpv_FileMappingPointer = 0;
		printf("Value is 0!\n");
		Sleep(100);

		if (_kbhit())
			break;
	}

	UnmapViewOfFile(lpv_FileMappingPointer);

	CloseHandle(h_FileMapping);
	CloseHandle(h_File);
}


