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

	ACCOUNT()
	{
		username = password = "";
		used = false;
	}

	std::string username;
	std::string password;
	bool used;
};

std::vector<user *> socks;
std::vector<ACCOUNT *> m_cAccount;
std::vector<std::string> m_TruncateList;
bool creatingAccount;

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

void msgCommand(user* User, int lastPos)
{
	std::string username = "";
	std::string msgToSend = "";

	//Getting name to send to
	for (unsigned a = 0; a < m_TruncateList[2].size(); ++a)
	{
		username += m_TruncateList[2][a];
	}

	msgToSend += User->name + " PM you: ";

	//Getting msg to send
	for (unsigned a = 3; a < m_TruncateList.size(); ++a)
	{
		msgToSend += m_TruncateList[a] + " ";
	}

	//Verifying User
	for (user* User2 : socks)
	{
		if (User2 != User)
		{
			if (User2->name == username)
			{
				send(User2->s, msgToSend.c_str(), msgToSend.size() + 1, 0);
				break;
			}
		}
	}
}

void helpCommand(user* User)
{
	std::string msgCommand = "Enter [/msg - <username> <msg>] to whisper a msg to that user";
	std::string listCommand = "Enter [/list] to get current user";

	std::ostringstream msgToSend;
	msgToSend << msgCommand << std::endl;
	msgToSend << listCommand << std::endl;
	send(User->s, msgToSend.str().c_str(), msgToSend.str().length() + 1, 0);
}

bool truncateBuffer(char buffer[], user* User)
{
	if (std::string(buffer) == "AFK")
	{
		User->afk = true;
		return true;
	}

	//Clear List
	if (!m_TruncateList.empty())
		m_TruncateList.clear();

	char* token = strtok(buffer, " ");
	while (token != NULL)
	{
		m_TruncateList.push_back(token);
		token = strtok(NULL, " ");
	}

	std::string command = "";
	int vecLastLoc = 0;
	if (m_TruncateList[0][0] == '/')
	{
		for (unsigned a = 1; a < m_TruncateList[0].size(); ++a)
		{
			if (m_TruncateList[0][a] != ' ')
			{
				command += m_TruncateList[0][a];
			}
			else
			{
				vecLastLoc = a;
				break;
			}
		}

		if (command == "list")
		{
			listCommand(User);
			return true;
		}
		else if (command == "msg")
		{
			msgCommand(User, vecLastLoc);
			return true;
		}
		else if (command == "help")
		{
			helpCommand(User);
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
	std::string suggestToSignUp = "Enter sign-up' to sign-up for a account";

	std::ostringstream msgToSend;
	msgToSend << suggestToSignUp << std::endl;
	msgToSend << enterName << std::endl;
	send(tmpsocket, msgToSend.str().c_str(), msgToSend.str().length() + 1, 0);
}

void sendMsg(std::string buffer, user* User)
{
	std::string msgToSend = "";
	msgToSend = User->name + " send: " + buffer;
	std::cout << msgToSend << std::endl;

	for (user* User2 : socks)
	{
		if (User != User2)
		{
			send(User2->s, msgToSend.c_str(), msgToSend.length() + 1, 0);
		}
	}

	/*msgToSend = User->name + ": " + buffer;
	std::cout << User->name << " send: " << buffer << std::endl;

	for (std::vector<user*>::iterator itr2 = socks.begin(); itr2 != socks.end(); ++itr2)
	{
		user* User2 = static_cast<user*>(*itr2);
		if (User->s == User2->s) continue;

		send(User2->s, msgToSend.c_str(), msgToSend.length() + 1, 0);
	}*/
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

std::string getUsernameByPass(std::string password)
{
	for (std::vector<ACCOUNT*>::iterator it = m_cAccount.begin(); it != m_cAccount.end(); ++it)
	{
		ACCOUNT* account = static_cast<ACCOUNT*>(*it);
		if (account->password == password)
		{
			return account->username;
		}
	}

	return "";
}

ACCOUNT* getAccountByName(std::string name)
{
	for (ACCOUNT* account : m_cAccount)
	{
		if (account->username == name)
		{
			return account;
		}
	}

	return NULL;
}

bool verifyAccount(user* User, std::string stringToCheck, bool checkUsername = true)
{
	for (std::vector<ACCOUNT*>::iterator it = m_cAccount.begin(); it != m_cAccount.end(); ++it)
	{
		ACCOUNT* account = static_cast<ACCOUNT*>(*it);

		if (account->used != true)
		{
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
					account->used = true;
					return true;
				}
			}
		}
	}

	return false;
}

void accountLogIn(user* User, std::string buffer)
{
	std::string enterName = "Please enter your username";
	std::string enterPass = "Please enter your password";
	std::string loginSuccess = "You have login successfully";
	std::string suggestToSignUp = "Enter 'sign-up' to sign-up for a account";

	//send(User->s, suggestToSignUp.c_str(), suggestToSignUp.length() + 1, 0);
	if (!User->usernameVerified)
	{
		if (!verifyAccount(User, buffer))
		{
			std::ostringstream msgToSend;
			msgToSend << suggestToSignUp << std::endl;
			msgToSend << enterName << std::endl;
			send(User->s, msgToSend.str().c_str(), msgToSend.str().length() + 1, 0);
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
			User->name = getUsernameByPass(buffer);

			std::cout << User->name << " have login sucessfully" << std::endl;

			//Send a announcement to client
			send(User->s, loginSuccess.c_str(), loginSuccess.length() + 1, 0);

			//Send a announcement to all connected client
			std::string msgToSend = User->name + " have joined this server";
			for each (user* User2 in socks)
			{
				if (User2 != User)
				{
					send(User2->s, msgToSend.c_str(), msgToSend.length() + 1, 0);
				}
			}
		}
	}
}

void createAccount(user* User, std::string buffer)
{
	std::string username = "Please enter your desired username";
	std::string password = "Please enter your desired password";
	static bool enteringUsername = true;
	static ACCOUNT* newAccount = NULL;

	if (enteringUsername)
	{
		if (newAccount == NULL)
		{
			newAccount = new ACCOUNT();
			send(User->s, username.c_str(), username.length() + 1, 0);
		}
		else
		{
			newAccount->username = buffer;
			enteringUsername = false;
			send(User->s, password.c_str(), password.length() + 1, 0);
		}
	}
	else
	{
		if (newAccount->password == "")
		{
			newAccount->password = buffer;
			m_cAccount.push_back(newAccount);
			newAccount = NULL;
			enteringUsername = true;
			creatingAccount = false;

			//Write to file
			std::ofstream accountInfo;
			accountInfo.open("Text/Accounts.txt");
			for (ACCOUNT* account : m_cAccount)
			{
				std::string username = account->username;
				std::string password = account->password;

				accountInfo << username << ", " << password << std::endl;
			}
			accountInfo.close();

			std::string enterName = "Please enter your username";
			std::string suggestToSignUp = "Enter 'sign-up' to sign-up for a account";

			std::ostringstream msgToSend;
			msgToSend << suggestToSignUp << std::endl;
			msgToSend << enterName << std::endl;
			send(User->s, msgToSend.str().c_str(), msgToSend.str().length() + 1, 0);
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
					char tempBuffer[80];
					int length = recv(User->s, buffer, sizeof(buffer), 0);
					if (length == SOCKET_ERROR)
					{
						std::cout << "Client (" << User->s << ") Disconnected" << std::endl;
						socks.erase(itr);

						break;
					}

					if (std::string(buffer) == "sign-up")
					{
						creatingAccount = true;
					}

					if (creatingAccount)
					{
						createAccount(User, std::string(buffer));
					}
					else
					{
						//User have not sign in
						if (!User->logIn)
						{
							accountLogIn(User, buffer);
						}
						else
						{
							for (unsigned a = 0; a < 80; ++a)
							{
								tempBuffer[a] = buffer[a];
							}

							//Check if user is AFK, set to false
							if (User->afk)
								User->afk = false;
							if (!truncateBuffer(tempBuffer, User))
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
	}

	//Cleanup
	WSACleanup();

	return 0;
}