#define WIN32_LEAN_AND_MEAN

#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>

#pragma comment(lib,"ws2_32.lib")

#define BUFSIZE 1024
#define DEFAULT_PORT 7890

SOCKET g_SocketArray[WSA_MAXIMUM_WAIT_EVENTS] = { NULL, };
WSAEVENT g_EventArray[WSA_MAXIMUM_WAIT_EVENTS] = { NULL, };

int g_SocketCount = 0;

void accept_new_session(SOCKET ClientSocket);
void close_session(int Index);
void compress_sockets(int OmitIndex);
void compress_events(int OmitIndex);


int main(int argc, char **argv)
{
	WSADATA wsaData;
	SOCKET ServerSocket;
	SOCKADDR_IN ServerAddress;

	SOCKET ClientSocket;
	int ClientLen;
	SOCKADDR_IN ClientAddress;

	WSAEVENT NewEvent;
	WSANETWORKEVENTS NetworkEvents;

	int Index, i;

	char MessageBuffer[BUFSIZE];
	int MessageLen;

	if (0 != WSAStartup(MAKEWORD(2, 2), &wsaData))
	{
		printf("WSAStartup() error!\n");
		return 1;
	}

	ServerSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == ServerSocket)
	{
		printf("socket() error!\n");
		return 1;
	}

	ServerAddress.sin_family = AF_INET;
	ServerAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	ServerAddress.sin_port = htons(DEFAULT_PORT);
	if (SOCKET_ERROR == bind(ServerSocket, (struct sockaddr *)&ServerAddress, sizeof(ServerAddress)))
	{
		printf("bind() error!\n");
		return 1;
	}

	NewEvent = WSACreateEvent();
	if (SOCKET_ERROR == WSAEventSelect(ServerSocket, NewEvent, FD_ACCEPT))
	{
		printf("WSAEventSelect() for Server socket with FD_ACCEPT error!\n");
		return 1;
	}

	if (SOCKET_ERROR == listen(ServerSocket, SOMAXCONN))
	{
		printf("listen() error!\n");
		return 1;
	}

	g_SocketCount = 0;
	g_SocketArray[g_SocketCount] = ServerSocket;
	g_EventArray[g_SocketCount] = NewEvent;
	g_SocketCount++;

	printf("Now the server is ready! listening the port number %d\n", DEFAULT_PORT);

	while (1)
	{
		Index = WSAWaitForMultipleEvents(g_SocketCount, g_EventArray, FALSE, WSA_INFINITE, FALSE);
		Index = Index - WSA_WAIT_EVENT_0;

		for (i = Index; i < g_SocketCount; i++)
		{ //Iterate through all events to see if more than one is signaled
			Index = WSAWaitForMultipleEvents(1, &g_EventArray[i], TRUE, 0, FALSE);
			if ((WSA_WAIT_FAILED == Index) || (WSA_WAIT_TIMEOUT == Index))
			{
				continue;
			}
			else
			{
				Index = i;
				WSAEnumNetworkEvents(g_SocketArray[Index], g_EventArray[Index], &NetworkEvents);
				if (NetworkEvents.lNetworkEvents & FD_ACCEPT)
				{
					if (0 != NetworkEvents.iErrorCode[FD_ACCEPT_BIT])
					{
						printf("Accept event has error!\n");
						break;
					}

					ClientLen = sizeof(ClientAddress);
					ClientSocket = accept(g_SocketArray[Index], (SOCKADDR *)&ClientAddress, &ClientLen);
					if (INVALID_SOCKET == ClientSocket)
					{
						printf("accept() error!\n");
						continue;
					}
					accept_new_session(ClientSocket);
					printf("New client accepted in Index[%d]\n", Index);
				}

				if (NetworkEvents.lNetworkEvents & FD_READ)
				{
					if (0 != NetworkEvents.iErrorCode[FD_READ_BIT])
					{
						printf("Read event has error!\n");
						continue;
					}

					MessageLen = recv(g_SocketArray[Index - WSA_WAIT_EVENT_0], MessageBuffer, BUFSIZE, 0);
					if (0 > MessageLen)
					{
						printf("recv() returned error in Socket handle %d\n", g_SocketArray[Index - WSA_WAIT_EVENT_0]);
						close_session(Index);
						continue;
					}
					else
					{
						printf("Message received %d bytes from Socket handle %d", MessageLen, g_SocketArray[Index - WSA_WAIT_EVENT_0]);
						send(g_SocketArray[Index - WSA_WAIT_EVENT_0], MessageBuffer, MessageLen, 0);

						std::cout << std::endl;
						for (unsigned a = 0; a < MessageLen; a++)
						{
							std::cout << MessageBuffer[a];
						}
						std::cout << std::endl;
					}
				}

				if (NetworkEvents.lNetworkEvents & FD_CLOSE)
				{
					if (0 != NetworkEvents.iErrorCode[FD_CLOSE_BIT])
					{
						printf("Close event has error!\n");
						close_session(Index);
						continue;
					}

					close_session(Index);

				}
			}
		}
	}

	WSACleanup();

	return 0;
}

void accept_new_session(SOCKET ClientSocket)
{
	WSAEVENT NewEvent;

	NewEvent = WSACreateEvent();
	WSAEventSelect(ClientSocket, NewEvent, FD_READ | FD_CLOSE);

	g_EventArray[g_SocketCount] = NewEvent;
	g_SocketArray[g_SocketCount] = ClientSocket;
	g_SocketCount++;
	printf("Net client accepted! Socket handle is %d\n", ClientSocket);
}

void close_session(int Index)
{
	printf("Socket closed. Socket handle is %d\n", g_SocketArray[Index]);

	WSACloseEvent(g_EventArray[Index]);
	closesocket(g_SocketArray[Index]);
	g_SocketCount--;
	compress_sockets(Index);
	compress_events(Index);
}

void compress_sockets(int OmitIndex)
{
	int i;
	for (i = OmitIndex; i < g_SocketCount; i++)
	{
		g_SocketArray[i] = g_SocketArray[i + 1];
	}
	g_SocketArray[i] = 0;
}

void compress_events(int OmitIndex)
{
	int i;
	for (i = OmitIndex; i < g_SocketCount; i++)
	{
		g_EventArray[i] = g_EventArray[i + 1];
	}
	g_EventArray[i] = 0;
}