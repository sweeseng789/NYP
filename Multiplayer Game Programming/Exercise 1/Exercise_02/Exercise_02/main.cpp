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
	// Declare some variables
	WSADATA     wsaData;

	// The listening socket to be created
	SOCKET      ListenSocket = INVALID_SOCKET;

	/// The client connection socket to be created
	SOCKET      ConnectedSocket = INVALID_SOCKET;

	// The socket address to be passed to bind
	sockaddr_in ServerAddress;

	// Address of connected socket from client.
	sockaddr_in ClientAddress;           

	// Message buffer to recv from socket
	char        MessageBuffer[DEFAULT_BUFLEN];

	// Length of the message buffer
	int         MessageBufferlen = DEFAULT_BUFLEN; 

	// Length for sockaddr_in.
	int         ClientAddressLen;

	// used to return function results
	int         Result = 0;                        


	//===============Initialize Winsock===============//
	Result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (NO_ERROR != Result)
	{
		std::cout << "Error at WSAStartip()" << std::endl;
		return 1;
	}
	else
	{
		std::cout << "WSAStartup success" << std::endl;
	}


	//===============Create a SOCKET for listening for incoming connection requests===============//
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == ListenSocket)
	{
		std::cout << "Socket function failed with error: " << WSAGetLastError() << std::endl;
		WSACleanup();
		return 1;
	}
	else
	{
		std::cout << "Socket creation succesfull" << std::endl;
	}


	//===============The sockaddr_in structure speccifies the address family, IP address and the port for the socket being found===============//
	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_port = htons(DEFAULT_PORT);
	ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);

	//===============Bind the Socket===============//
	ConnectedSocket = bind(ListenSocket, (SOCKADDR *)&ServerAddress, sizeof (ServerAddress));
	if (SOCKET_ERROR == ConnectedSocket)
	{
		std::cout << "Binding failed with error: " << WSAGetLastError() << std::endl;
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	else
	{
		std::cout << "Binding successful" << std::endl;
	}

	//===============Listen for incoming commection request on the created socket===============//
	if (SOCKET_ERROR == listen(ListenSocket, SOMAXCONN))
	{
		std::cout << "Listen function failed with error: " << WSAGetLastError() << std::endl;
	}
	else
	{
		std::cout << "Listening on socket" << std::endl;
	}

	//===============Create a socket for accepting incoming request===============//
	std::cout << "Waiting for new clients to connect" << std::endl;

	ClientAddressLen = sizeof(ClientAddress);
	while (1)
	{
		//===============Accepting the connection===============//
		ConnectedSocket = accept(ListenSocket, (struct sockaddr*)&ClientAddress, &ClientAddressLen);
		if (INVALID_SOCKET == ConnectedSocket)
		{
			std::cout << "Accept failed with error: " << WSAGetLastError() << std::endl;
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
		}
		else
		{
			wprintf(L"Client connected. IP Address : %d.%d.%d.%d, Port Number :%d\n",
				ClientAddress.sin_addr.S_un.S_un_b.s_b1,
				ClientAddress.sin_addr.S_un.S_un_b.s_b2,
				ClientAddress.sin_addr.S_un.S_un_b.s_b3,
				ClientAddress.sin_addr.S_un.S_un_b.s_b4,
				ntohs(ClientAddress.sin_port));

		}

		//===============Receive and cout the message until the peer closes the connection===============//
		do
		{
			memset(MessageBuffer, '\0', DEFAULT_BUFLEN);
			MessageBufferlen = 2;
			Result = recv(ConnectedSocket, MessageBuffer, MessageBufferlen, 0);
			if (0 < Result)
			{
				std::cout << "Bytes received: " << Result << std::endl;
				std::cout << "Buffer received: " << MessageBuffer << std::endl;
			}
			else if (0 == Result)
			{
				std::cout << "connection closed" << std::endl;
				break;
			}
			else
			{
				std::cout << "recv failed: " << WSAGetLastError() << std::endl;
				break;
			}

			/// Echo same message to client
			Result = send(ConnectedSocket, MessageBuffer, Result, 0);
			if (SOCKET_ERROR == Result)
			{
				std::cout << "Send failed: " << WSAGetLastError() << std::endl;
			}
		} while (0 < Result);

		// Close the ConnectedSocket.
		closesocket(ConnectedSocket);
	}

	//===============Close an existing socket===============//
	closesocket(ListenSocket);
	

	//===============Terminate use of the Winsock 2 DLL (Ws2_32.dll)===============//
	WSACleanup();
	return 0;
}