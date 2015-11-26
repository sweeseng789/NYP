#include <winsock2.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <process.h>

bool afkMsgSent = false;
double durationBeforeAfk = 0.0;

int main()
{
	//Startup
	WSADATA w;
	int error = WSAStartup(0x0202, &w);
	if (error) // Something bad happened
	{
		std::cout << "Could not start Winsock" << std::endl;
		return 0;
	}
	if (w.wVersion != 0x0202) // Wrong version, time to update windows
	{
		std::cout << "Winsock is outdated. Update Windows!" << std::endl;
		WSACleanup();
		return 0;
	}

	std::string ipAddress = "";
	std::cout << "Please enter the IP Address to connect to: ";
	std::getline(std::cin, ipAddress);

	SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // Create socket
	sockaddr_in addr; // the address structure for a TCP socket
	addr.sin_family = AF_INET; // Address family Internet
	addr.sin_port = htons(23456); // Assign port 23456 to this socket
	addr.sin_addr.s_addr = inet_addr(ipAddress.c_str()); // To local host

	u_long somelong;
	ioctlsocket(sock, FIONBIO, &somelong);

	// do not check == SOCKET_ERROR here because Async mode will always return SOCKET_ERROR
	connect(sock, (sockaddr*)&addr, sizeof(addr));

	ipAddress = "";
	ipAddress += std::to_string(addr.sin_addr.S_un.S_un_b.s_b1) + '.';
	ipAddress += std::to_string(addr.sin_addr.S_un.S_un_b.s_b2) + '.';
	ipAddress += std::to_string(addr.sin_addr.S_un.S_un_b.s_b3) + '.';
	ipAddress += std::to_string(addr.sin_addr.S_un.S_un_b.s_b4);

	//Loop
	while (true)
	{
		if (_kbhit())
		{
			durationBeforeAfk = 0.0;
			afkMsgSent = false;

			std::string inputstring;
			std::getline(std::cin, inputstring);
			send(sock, inputstring.c_str(), (int)inputstring.length() + 1, 0);
		}
		else
		{
			if (durationBeforeAfk < 10)
			{
				durationBeforeAfk += 0.005;
			}
			else
			{
				if (!afkMsgSent)
				{
					std::string afk = "AFK";
					send(sock, afk.c_str(), (int)afk.length() + 1, 0);
					afkMsgSent = true;
				}
			}
		}

		fd_set fset;
		FD_ZERO(&fset);
		FD_SET(sock, &fset);

		timeval tval;
		tval.tv_sec = 0;
		tval.tv_usec = 10000;

		if (select(0, &fset, 0, 0, &tval) > 0)
		{
			char buffer[80]; // buffer that is 80 characters big
			int length = recv(sock, buffer, sizeof(buffer), 0);
			if (length == SOCKET_ERROR)
			{
				std::cout << "Server went offline" << std::endl;
				break;
			}
			std::cout << buffer << std::endl;
		}

	}

	//Cleanup
	WSACleanup();
	return 0;
}