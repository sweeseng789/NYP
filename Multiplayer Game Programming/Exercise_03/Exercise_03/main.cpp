#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <winsock2.h>
#include <stdio.h>
#include <iostream>

/// Link with ws2_32.lib
#pragma comment(lib, "Ws2_32.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT   7890

int main(void)
{
	///----------------------
	/// Declare and initialize variables.
	WSADATA     wsaData;                             /// Declare some variables
	SOCKET      ConnectSocket = INVALID_SOCKET;      /// The socket to connect to server
	sockaddr_in clientService;                       /// The socket address to connecto to server
	char        MessageBuffer[DEFAULT_BUFLEN]; /// Message MessageBuffer to recv from socket
	int         BufferLen;                           /// Length of the message buffer
	int         Result;                              /// used to return function results
	int         i;

	///----------------------
	/// 1. Initialize Winsock
	Result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (Result != NO_ERROR)
	{
		printf("WSAStartup failed: %d\n", Result);
		return 1;
	}

	///----------------------
	/// 2. Create a SOCKET for connecting to server
	ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ConnectSocket == INVALID_SOCKET)
	{
		printf("Error at socket(): %ld\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	///----------------------
	/// The sockaddr_in structure specifies the address family,
	/// IP address, and port of the server to be connected to.
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr("127.0.0.1"); /// Connecting to local machine. "127.0.0.1" is the loopback address.
	clientService.sin_port = htons(DEFAULT_PORT);

	///----------------------
	/// 3. Connect to server.
	Result = connect(ConnectSocket, (SOCKADDR*)&clientService, sizeof(clientService));
	if (Result == SOCKET_ERROR)
	{
		closesocket(ConnectSocket);
		printf("Unable to connect to server: %ld\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}

	/// Receive until the peer closes the connection
	do
	{
		printf("enter messages : ");

		for (i = 0; i < (DEFAULT_BUFLEN - 1); i++)
		{
			MessageBuffer[i] = getchar();
			if (MessageBuffer[i] == '\n')
			{
				MessageBuffer[i++] = '\0';
				break;
			}
		}
		BufferLen = i;

		/// 4. Send an MessageBuffer
		Result = send(ConnectSocket, MessageBuffer, BufferLen, 0);
		if (Result == SOCKET_ERROR)
		{
			printf("send failed: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}

		printf("Bytes Sent: %ld\n", Result);

		Result = recv(ConnectSocket, MessageBuffer, DEFAULT_BUFLEN, 0);
		if (Result > 0)
		{
			printf("Bytes received   : %d\n", Result);
			printf("Message received : %s\n", MessageBuffer);
		}
		else if (Result == 0)
		{
			printf("Connection closed\n");
		}
		else
		{
			printf("recv failed: %d\n", WSAGetLastError());
		}
	} while (Result > 0);

	/// 5. close & cleanup
	closesocket(ConnectSocket);
	WSACleanup();

	return 0;
	system("pause");
}