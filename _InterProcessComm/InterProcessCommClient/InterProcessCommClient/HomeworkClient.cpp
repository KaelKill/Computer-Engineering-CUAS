#include <windows.h>
#include <iostream>
using namespace std;

#define BUFFER_SIZE 512
#define TIMEOUT 20000

void main() {

	char pipe_name[] = "\\\\localhost\\pipe\\my_pipe";
	HANDLE h_pipe;
	unsigned char send_data[25] = "Client is running...";
	unsigned char receive_data[25] = { 0 };
	DWORD sent_data = 0;
	DWORD received_data = 0;

	cout << "Client waiting for server to create pipe..." << endl;
	while (1) {
		if (WaitNamedPipe(pipe_name, NMPWAIT_WAIT_FOREVER) != 0) // wait for server to create pipe
			break;
		Sleep(250);
	}

	h_pipe = CreateFile(pipe_name,
		GENERIC_READ |  // read and write access 
		GENERIC_WRITE,
		0,              // no sharing 
		NULL,           // default security attributes
		OPEN_EXISTING,  // opens existing pipe 
		0,              // default attributes 
		NULL);          // no template file 

	if (h_pipe == INVALID_HANDLE_VALUE)
		return;


	for (int i = 0; i < 100; i++)
	{
		ReadFile(h_pipe, receive_data, sizeof(receive_data), &received_data, NULL);
		cout << "Client read data from server" << endl;
		cout << "Data read: " << receive_data << endl;

		WriteFile(h_pipe, send_data, sizeof(send_data), &sent_data, NULL);
		cout << "Client wrote data to server" << endl;
		cout << "Data written: " << send_data << endl;
	}

	CloseHandle(h_pipe);
}
