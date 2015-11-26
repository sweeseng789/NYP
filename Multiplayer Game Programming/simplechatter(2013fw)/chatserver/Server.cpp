#include <winsock2.h>
#include <iostream>
#include <sstream>
#include <vector>

struct user
{
	user(SOCKET sd)// this initalise name to “New User”
	: s(0), name("New User")
	{
		s = sd;
	}


	SOCKET s;
	std::string name; // to hold the name
	bool afk = true;
};

std::vector<user *> socks;

void CheckBuffer(std::string buffer, user* User)
{
	if (buffer == "AFK")
	{
		User->afk = true;
	}
	else
	{
		if (buffer[0] == '/')
		{
			std::string msgToSend;

			for (unsigned a = 1; buffer[a] != ' '; a++)
			{
				msgToSend += buffer[a];
			}
		}
	}
}

int main()
{
	//Startup
	WSADATA w;
	int error = WSAStartup (0x0202, &w);
	if (error) // Something bad happened
	{
		std::cout << "Could not start Winsock" << std::endl;
		return 0;
	}
	if (w.wVersion != 0x0202) // Wrong version, time to update windows
	{
		std::cout << "Winsock is outdated. Update Windows!" << std::endl;
		WSACleanup ();
		return 0;
	}

	//Prepare Socket
	SOCKET s = socket (AF_INET, SOCK_STREAM, 0); // Create socket
	sockaddr_in addr; // the address structure for a TCP socket
	addr.sin_family = AF_INET; // Address family Internet
	addr.sin_port = htons (23456); // Assign port 27888 to this socket
	addr.sin_addr.s_addr = htonl (INADDR_ANY); // No destination

	if (bind(s, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR)
	{ // error in binding
		return false;
	}

	u_long somelong;
	ioctlsocket(s, FIONBIO, &somelong);

	if (listen(s,1)==SOCKET_ERROR)
	{ // error! unable to listen
		return false;
	}
	std::cout << "Chat Server Up! Listening on port 23456..." << std::endl;

	// Loop
	while(true)
	{
		fd_set fset;
		FD_ZERO(&fset);
		FD_SET(s, &fset);

		for (std::vector<user*>::iterator itr = socks.begin(); itr != socks.end(); ++itr)
		{
			FD_SET((*itr)->s, &fset);
		}

		if (select(0, &fset, 0, 0, 0) > 0)
		{
			if (FD_ISSET(s, &fset))
			{
				SOCKET tmpsocket = accept (s, NULL, NULL);
				ioctlsocket(tmpsocket, FIONBIO, &somelong);
				user *tmpuser = new user( tmpsocket );
				socks.push_back( tmpuser );

				std::cout << "New Connection" << std::endl;

				std::string sendbuff = "Enter your name: ";

				send(tmpsocket, sendbuff.c_str(), sendbuff.length()+1, 0);
			}

			for (std::vector<user*>::iterator itr = socks.begin(); itr != socks.end(); ++itr)
			{
				user* User = static_cast<user*>(*itr);

				if (FD_ISSET(User->s, &fset))
				{
					char buffer[80]; // buffer that is 80 characters big
					int length = recv (User->s, buffer, sizeof(buffer), 0);
					if (length == SOCKET_ERROR)
					{
						std::cout << "Client ("<< User->s <<") Disconnected" << std::endl;
						socks.erase(itr);
						
						break;
					}

					std::cout << "Message Received: " << buffer << std::endl;

					CheckBuffer(std::string(buffer), User);

					std::string sendbuff = buffer;

					if(User->name == "New User" )
					{
						std::string newname = sendbuff;
						sendbuff = "You are now known as " + newname;
						User->name = newname;

						send(User->s, sendbuff.c_str(), sendbuff.length()+1, 0);

						sendbuff = "New User has joined chat as " + newname;
					}
					else
					{
						std::ostringstream oss;
						oss << User->name  << ": " << buffer;
						sendbuff = oss.str();
					}

					for (std::vector<user*>::iterator itr2 = socks.begin(); itr2 != socks.end(); ++itr2)
					{
						if(User->s == User->s ) continue;

						send(User->s, sendbuff.c_str(), sendbuff.length()+1, 0);
					}
				}
			}
		}
	}

	//Cleanup
	WSACleanup ();
	return 0;
}