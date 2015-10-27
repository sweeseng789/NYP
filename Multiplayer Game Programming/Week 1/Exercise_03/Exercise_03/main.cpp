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
	// Declare and initialize variables.
	WSADATA     wsaData;                             

	// The socket to connect to server
	SOCKET      ConnectSocket = INVALID_SOCKET;     

	// The socket address to connecto to server
	sockaddr_in clientService;                       

	// Message MessageBuffer to recv from socket
	char        MessageBuffer[DEFAULT_BUFLEN]; 

	// Length of the message buffer
	int         BufferLen;               

	// used to return function results
	int         Result;

	int         i;


	//===============Initialize Winsock===============//
	Result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (Result != NO_ERROR)
	{
		std::cout << "WSAStartup failed: " << Result << std::endl;
		return 1;
	}


	//===============Create a socket for connecting to server===============//
	ConnectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (ConnectSocket == INVALID_SOCKET)
	{
		std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 1;
	}

	//===============The sockaddr_in structure specifies the address family, IP address, and port of the server to connect to ===============//
	clientService.sin_family = AF_INET;
	clientService.sin_addr.s_addr = inet_addr("127.0.0.1"); /// Connecting to local machine. "127.0.0.1" is the loopback address.
	clientService.sin_port = htons(DEFAULT_PORT);


	//===============Connect to server===============//
	Result = connect(ConnectSocket, (SOCKADDR*)&clientService, sizeof(clientService));
	if (Result == SOCKET_ERROR)
	{
		std::cout << "Unable to connect to server: " << WSAGetLastError() << std::endl;
		closesocket(ConnectSocket);
		WSACleanup();
		return 1;
	}
	else
	{
		std::cout << "Connection to server successful!" << std::endl;
	}

	//===============Receive until the peer closes the connection===============//
	do
	{
		std::cout << "Enter your message: ";

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
			std::cout << "Send failed: " << WSAGetLastError() << std::endl;
			closesocket(ConnectSocket);
			WSACleanup();
			return 1;
		}

		std::cout << "Bytes sent: " << Result << std::endl;

		for (unsigned a = 0; a < DEFAULT_BUFLEN; ++a)
		{
			MessageBuffer[a] = '\0';
		}
		Result = recv(ConnectSocket, MessageBuffer, DEFAULT_BUFLEN, 0);
		if (Result > 0)
		{
			std::cout << "Bytes received: " << Result << std::endl;
			std::cout << "Message received: " << MessageBuffer << std::endl;
		}
		else if (Result == 0)
		{
			std::cout << "Connection closed" << std::endl;
		}
		else
		{
			std::cout << "recv failed: " << WSAGetLastError() << std::endl;
		}
	} while (Result > 0);

	//===============Close and Cleanup===============//
	closesocket(ConnectSocket);
	WSACleanup();

	return 0;
}