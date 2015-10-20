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
	WSADATA     wsaData;                           /// Declare some variables
	SOCKET      ListenSocket = INVALID_SOCKET;  /// The listening socket to be created
	SOCKET      ConnectedSocket = INVALID_SOCKET;  /// The client connection socket to be created
	sockaddr_in ServerAddress;                     /// The socket address to be passed to bind
	sockaddr_in ClientAddress;                     /// Address of connected socket from client.
	char        MessageBuffer[DEFAULT_BUFLEN];     /// Message buffer to recv from socket
	int         MessageBufferlen = DEFAULT_BUFLEN; /// Length of the message buffer
	int         ClientAddressLen;                  /// Length for sockaddr_in.
	int         Result = 0;                        /// used to return function results

	///----------------------
	/// 1. Initialize Winsock
	Result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (NO_ERROR != Result)
	{
		wprintf(L"Error at WSAStartup()\n");
		return 1;
	}
	else
	{
		wprintf(L"WSAStartup success.\n");
	}

	///----------------------
	/// 2. Create a SOCKET for listening for 
	///    incoming connection requests
	ListenSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (INVALID_SOCKET == ListenSocket)
	{
		wprintf(L"socket function failed with error: %u\n", WSAGetLastError());
		WSACleanup();
		return 1;
	}
	else
	{
		wprintf(L"socket creation success.\n");
	}

	///----------------------
	/// 3-1. The sockaddr_in structure specifies the address family,
	///      IP address, and port for the socket that is being bound.
	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_port = htons(DEFAULT_PORT);
	ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);

	///----------------------
	/// 3-2. Bind the socket.
	ConnectedSocket = bind(ListenSocket, (SOCKADDR *)&ServerAddress, sizeof (ServerAddress));
	if (SOCKET_ERROR == ConnectedSocket)
	{
		wprintf(L"bind failed with error %u\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}
	else
	{
		wprintf(L"bind returned success\n");
	}

	///----------------------
	/// 4. Listen for incoming connection requests 
	///    on the created socket
	if (SOCKET_ERROR == listen(ListenSocket, SOMAXCONN))
	{
		wprintf(L"listen function failed with error: %d\n", WSAGetLastError());
	}
	wprintf(L"Listening on socket...\n");

	///----------------------
	/// Create a SOCKET for accepting incoming requests.
	wprintf(L"Waiting for new client to connect...\n");

	ClientAddressLen = sizeof(ClientAddress);
	while (1)
	{
		///----------------------
		/// 5. Accept the connection.
		ConnectedSocket = accept(ListenSocket, (struct sockaddr*)&ClientAddress, &ClientAddressLen);
		if (INVALID_SOCKET == ConnectedSocket)
		{
			wprintf(L"accept failed with error: %ld\n", WSAGetLastError());
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

		///----------------------
		/// 6. Receive and echo the message until the peer closes the connection
		do
		{
			memset(MessageBuffer, '\0', DEFAULT_BUFLEN);
			MessageBufferlen = 100;
			Result = recv(ConnectedSocket, MessageBuffer, MessageBufferlen, 0);
			if (0 < Result)
			{
				printf("Bytes received  : %d\n", Result);
				printf("Buffer received : %s\n", MessageBuffer);
			}
			else if (0 == Result)
			{
				printf("Connection closed\n");
				break;
			}
			else
			{
				printf("recv failed: %d\n", WSAGetLastError());
				break;
			}

			/// Echo same message to client
			Result = send(ConnectedSocket, MessageBuffer, Result, 0);
			if (SOCKET_ERROR == Result)
			{
				printf("send failed: %d\n", WSAGetLastError());
			}
		} while (0 < Result);

		// Close the ConnectedSocket.
		closesocket(ConnectedSocket);
	}

	///----------------------
	/// 7. Closes an existing socket
	closesocket(ListenSocket);
	

	///----------------------
	/// 8. Terminate use of the Winsock 2 DLL (Ws2_32.dll)
	WSACleanup();
	return 0;
}