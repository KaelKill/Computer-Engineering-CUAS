#include <windows.h>
#include <iostream>
using namespace std;

#define BUFFER_SIZE 512
#define TIMEOUT 20000

void main() {

	char pipe_name[] = "\\\\.\\pipe\\my_pipe";
	HANDLE h_pipe;
	unsigned char send_data[25] = "Server is running...";
	unsigned char receive_data[25] = { 0 };
	DWORD sent_data = 0;
	DWORD received_data = 0;

	h_pipe = CreateNamedPipe(pipe_name,	// Name der Pipe
		PIPE_ACCESS_DUPLEX,		// Bidirektionale Kommunikation
		PIPE_TYPE_BYTE |		// Daten werden als Bytes interpretiert
		PIPE_WAIT,				// Blocking Mode enabled
		PIPE_UNLIMITED_INSTANCES,
		BUFFER_SIZE,			// Output Buffer Size in Bytes
		BUFFER_SIZE,			// Input Buffer Size in Bytes
		TIMEOUT,				// Wait Timeout in msec
		NULL);					// Security Attributes	

	if (h_pipe == INVALID_HANDLE_VALUE)
	{
		DWORD dwRet;
		dwRet = GetLastError();
		cout << "Error Code: " << dwRet << endl;
		return;
	}

	cout << "Server waiting for client connection..." << endl;

	if (ConnectNamedPipe(h_pipe, NULL) != 0) // Wait for connection, connection established?
	{
		for (int i = 0; i < 100; i++)
		{
			WriteFile(h_pipe, send_data, sizeof(send_data), &sent_data, NULL);
			cout << "Server wrote data to client" << endl;
			cout << "Data written: " << send_data << endl;

			ReadFile(h_pipe, receive_data, sizeof(receive_data), &received_data, NULL);
			cout << "Server read data from client" << endl;
			cout << "Data read: " << receive_data << endl;
		}

		CloseHandle(h_pipe);
	}

}
