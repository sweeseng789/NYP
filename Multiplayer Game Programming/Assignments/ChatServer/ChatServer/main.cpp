#include <winsock2.h>
#include <iostream>
#include <sstream>
#include <vector>
#include <fstream>

struct user
{
	user(SOCKET sd)// this initalise name to “New User”
	: 
		s(0), 
		name("New User"),
		usernameVerified(false),
		passwordVerified(false)
	{
		s = sd;
	}


	SOCKET s;
	std::string name; // to hold the name
	bool afk = true;
	bool logIn = false;
	bool usernameVerified;
	bool passwordVerified;
};

struct ACCOUNT
{
	ACCOUNT(std::string username, std::string password) :
		username(username),
		password(password),
		used(false)
	{
	}

	std::string username;
	std::string password;
	bool used;
};

std::vector<user *> socks;
std::vector<ACCOUNT *> m_cAccount;



void listCommand(user* User)
{
	std::string msgToSend = "";

	for (std::vector<user*>::iterator itr2 = socks.begin(); itr2 != socks.end(); ++itr2)
	{
		user* User2 = static_cast<user*>(*itr2);

		if (User == User2)
		{
			msgToSend += "(You)";
		}
		else
		{
			msgToSend += User2->name;
		}

		if (itr2 + 1 != socks.end())
		{
			msgToSend += ", ";
		}
	}
	send(User->s, msgToSend.c_str(), msgToSend.length() + 1, 0);
}

void msgCommand(user* User, std::string buffer, int lastPos)
{
	std::string userToSendTo = "";
	std::string msgToSendToUser = "(Whisper)" + User->name + ": ";

	//Getting name to send to
	for (unsigned a = lastPos + 1; a < buffer.length(); ++a)
	{
		if (buffer[a] != '-')
		{
			userToSendTo += buffer[a];
		}
		else
		{
			lastPos = a;
			break;
		}
	}

	//Getting msg to send
	for (unsigned a = lastPos + 1; a < buffer.length(); ++a)
	{
		msgToSendToUser += buffer[a];
	}

	//Verify and send msg to user
	for (std::vector<user*>::iterator it = socks.begin(); it != socks.end(); ++it)
	{
		user* User2 = static_cast<user*>(*it);
		if (User == User2)
			continue;

		if (User2->name == userToSendTo)
		{
			send(User2->s, msgToSendToUser.c_str(), msgToSendToUser.length() + 1, 0);
			break;
		}
	}
}

bool bufferCommand(std::string buffer, user* User)
{
	if (buffer == "AFK")
	{
		User->afk = true;
		return true;
	}
	else
	{
		if (buffer[0] == '/')
		{
			std::string command = "";
			int lastPos = 0;

			for (unsigned a = 1; a < buffer.length(); a++)
			{
				if (buffer[a] != ' ')
				{
					command += buffer[a];
				}
				else
				{
					lastPos = a;
					break;
				}
			}

			if (command == "list")
			{
				listCommand(User);
			}
			else if (command == "msg")
			{
				msgCommand(User, buffer, lastPos);
			}

			return true;
		}
	}

	return false;
}

void newConnection(SOCKET s, u_long somelong)
{
	SOCKET tmpsocket = accept(s, NULL, NULL);
	ioctlsocket(tmpsocket, FIONBIO, &somelong);
	user *tmpuser = new user(tmpsocket);
	socks.push_back(tmpuser);

	std::cout << "New Connection Made" << std::endl;

	std::string enterName = "Please enter your username";
	//std::string sendbuff = "Enter your name";

	send(tmpsocket, enterName.c_str(), enterName.length() + 1, 0);
}

void sendMsg(std::string buffer, user* User)
{
	std::string msgToSend = "";

	if (User->name == "New User")
	{
		//Set name
		User->name = buffer;

		//Send msg back to user
		std::string msgToUser = "You are known as " + User->name;
		send(User->s, msgToUser.c_str(), msgToUser.length() + 1, 0);

		msgToSend = "New User have join: " + User->name;
	}
	else
	{
		msgToSend = User->name + ": " + buffer;
		std::cout << User->name << " send: " << buffer << std::endl;
	}

	for (std::vector<user*>::iterator itr2 = socks.begin(); itr2 != socks.end(); ++itr2)
	{
		user* User2 = static_cast<user*>(*itr2);
		if (User->s == User2->s) continue;

		send(User2->s, msgToSend.c_str(), msgToSend.length() + 1, 0);
	}
}

void getAccountSettings()
{
	//Read from text
	std::ifstream account("Text/Accounts.txt");
	if (account.is_open())
	{
		std::string username = "";
		std::string password = "";

		while (!account.eof())
		{
			std::getline(account, username, ',');
			std::getline(account, password);

			//Clear whitespace
			password.erase(0, 1);

			ACCOUNT* newAccount = new ACCOUNT(username, password);
			m_cAccount.push_back(newAccount);
		}
	}
	account.close();
}

bool verifyAccount(user* User, std::string stringToCheck, bool checkUsername = true)
{
	for (std::vector<ACCOUNT*>::iterator it = m_cAccount.begin(); it != m_cAccount.end(); ++it)
	{
		ACCOUNT* account = static_cast<ACCOUNT*>(*it);

		//Check against username
		if (checkUsername)
		{
			if (stringToCheck == account->username)
			{
				User->usernameVerified = true;
				return true;
			}
		}
		//Check against password
		else
		{
			if (stringToCheck == account->password)
			{
				User->passwordVerified = true;
				return true;
			}
		}
	}

	return false;
}

void accountLogIn(user* User, std::string buffer)
{
	std::string enterName = "Please enter your username";
	std::string enterPass = "Please enter your password";

	if (!User->usernameVerified)
	{
		if (!verifyAccount(User, buffer))
		{
			send(User->s, enterName.c_str(), enterName.length() + 1, 0);
		}
		else
		{
			User->usernameVerified = true;
			send(User->s, enterPass.c_str(), enterPass.length() + 1, 0);
		}
	}
	else
	{
		if (!verifyAccount(User, buffer, false))
		{
			send(User->s, enterName.c_str(), enterName.length() + 1, 0);
			User->usernameVerified = false;
		}
		else
		{
			User->passwordVerified = true;
			User->logIn = true;
			std::cout << "Account Verified" << std::endl;

			std::string msgToSend = "Please enter your name";
			send(User->s, msgToSend.c_str(), msgToSend.length() + 1, 0);
		}
	}
}

int main()
{
	//Read from text
	getAccountSettings();

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

	//Prepare Socket
	SOCKET s = socket(AF_INET, SOCK_STREAM, 0); // Create socket
	sockaddr_in addr; // the address structure for a TCP socket
	addr.sin_family = AF_INET; // Address family Internet
	addr.sin_port = htons(23456); // Assign port 27888 to this socket
	addr.sin_addr.s_addr = htonl(INADDR_ANY); // No destination

	if (bind(s, (LPSOCKADDR)&addr, sizeof(addr)) == SOCKET_ERROR)
	{ // error in binding
		return false;
	}

	u_long somelong;
	ioctlsocket(s, FIONBIO, &somelong);

	if (listen(s, 1) == SOCKET_ERROR)
	{ // error! unable to listen
		return false;
	}
	std::cout << "Chat Server Up! Listening on port 23456..." << std::endl;

	// Loop
	while (true)
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
				newConnection(s, somelong);
			}

			for (std::vector<user*>::iterator itr = socks.begin(); itr != socks.end(); ++itr)
			{
				user* User = static_cast<user*>(*itr);

				if (FD_ISSET(User->s, &fset))
				{
					char buffer[80]; // buffer that is 80 characters big
					int length = recv(User->s, buffer, sizeof(buffer), 0);
					if (length == SOCKET_ERROR)
					{
						std::cout << "Client (" << User->s << ") Disconnected" << std::endl;
						socks.erase(itr);

						break;
					}

					//User have not sign in
					if (!User->logIn)
					{
						accountLogIn(User, buffer);
					}
					else
					{
						//Check if user is AFK, set to false
						if (User->afk)
							User->afk = false;

						//If bufferCommand return false, it is a normal message
						if (!bufferCommand(std::string(buffer), User))
						{
							sendMsg(std::string(buffer), User);

							std::string msgToSend = "Please enter your message";
							send(User->s, msgToSend.c_str(), msgToSend.length() + 1, 0);
						}
					}
				}
			}
		}
	}

	//Cleanup
	WSACleanup();
	return 0;
}