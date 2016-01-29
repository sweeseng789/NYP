#include "Application.h"
#include "GameObject.h"
#include "Globals.h"
#include "MyMsgIDs.h"
#include "RakNetworkFactory.h"
#include "RakPeerInterface.h"
#include "Bitstream.h"
#include "GetTime.h"
#include <hge.h>
#include <string>
#include <iostream>
#include <fstream>



// Lab 13 Task 9a : Uncomment the macro NETWORKMISSILE
float GetAbsoluteMag(float num)
{
	if (num < 0)
	{
		return -num;
	}

	return num;
}

Application::Application()
	: hge(hgeCreate(HGE_VERSION))
	, rakpeer(RakNetworkFactory::GetRakPeerInterface())
	, timer(0)
	// Lab 13 Task 2 : add new initializations
{
}

Application::~Application() throw()
{
	Shutdown();
	rakpeer->Shutdown(100);
	RakNetworkFactory::DestroyRakPeerInterface(rakpeer);
}

bool Application::Init()
{
	std::ifstream inData;
	std::string serverip;

	inData.open("serverip.txt");

	inData >> serverip;

	srand(RakNet::GetTime());

	hge->System_SetState(HGE_FRAMEFUNC, Application::Loop);
	hge->System_SetState(HGE_WINDOWED, true);
	hge->System_SetState(HGE_USESOUND, false);
	hge->System_SetState(HGE_TITLE, "Movement");
	hge->System_SetState(HGE_LOGFILE, "movement.log");
	hge->System_SetState(HGE_DONTSUSPEND, true);

	if (hge->System_Initiate())
	{
		/*shipList.push_back(new Ship(rand() % 4 + 1, rand() % 500 + 100, rand() % 400 + 100));
		shipList.at(0)->SetName("My Ship");
		if (rakpeer->Startup(1, 30, &SocketDescriptor(), 1))
		{
			rakpeer->SetOccasionalPing(true);
			return rakpeer->Connect(serverip.c_str(), 1691, 0, 0);
		}*/
		Ship* ship = new Ship(rand() % 4 + 1, rand() % 500 + 100, rand() % 400 + 100);
		ship->SetName("My Ship");
		shipList.push_back(ship);

		if (rakpeer->Startup(1, 30, &SocketDescriptor(), 1))
		{
			rakpeer->SetOccasionalPing(true);
			return rakpeer->Connect(serverip.c_str(), 1691, 0, 0);
		}
	}
	return false;
}

/**
* Update cycle
*
* Checks for keypresses:
*   - Esc - Quits the game
*   - Left - Rotates ship left
*   - Right - Rotates ship right
*   - Up - Accelerates the ship
*   - Down - Deccelerates the ship
*
* Also calls Update() on all the ships in the universe
*/
bool Application::Update()
{
	if (hge->Input_GetKeyState(HGEK_ESCAPE))
		return true;

	float dt = hge->Timer_GetDelta();

	playerControl(dt);

	// Lab 13 Task 4 : Add a key to shoot missiles

	for (std::vector<Ship*>::iterator it = shipList.begin(); it != shipList.end(); ++it)
	{
		/*Ship* ship = static_cast<Ship*>(*it);
		ship->Update(dt);

		if (ship == shipList.at(0))
			checkCollisions(ship);*/
		Ship* ship = static_cast<Ship*>(*it);
		if (ship)
		{
			ship->Update(dt);
		}
	}

	// Lab 13 Task 5 : Updating the missile


	// Lab 13 Task 13 : Update network missiles


	if (Packet* packet = rakpeer->Receive())
	{
		RakNet::BitStream bs(packet->data, packet->length, false);

		unsigned char msgid = 0;
		RakNetTime timestamp = 0;

		bs.Read(msgid);

		if (msgid == ID_TIMESTAMP)
		{
			bs.Read(timestamp);
			bs.Read(msgid);
		}

		switch (msgid)
		{
		case ID_CONNECTION_REQUEST_ACCEPTED:
			std::cout << "Connected to Server" << std::endl;
			break;

		case ID_NO_FREE_INCOMING_CONNECTIONS:
		case ID_CONNECTION_LOST:
		case ID_DISCONNECTION_NOTIFICATION:
			std::cout << "Lost Connection to Server" << std::endl;
			rakpeer->DeallocatePacket(packet);
			return true;

		case ID_WELCOME:
			welcome(bs);
			break;

		case ID_NEWSHIP:
			newPlayer(bs);
			break;

		case ID_LOSTSHIP:
			removePlayer(bs);
			break;

		case ID_INITIALPOS:
			break;

		case ID_MOVEMENT:
			movementUpdate(bs);
			break;

		case ID_COLLIDE:
			collisionUpdate(bs);
			break;
			// Lab 13 Task 10 : new cases to handle missile on application side

		default:
			std::cout << "Unhandled Message Identifier: " << (int)msgid << std::endl;

		}
		rakpeer->DeallocatePacket(packet);
	}

	sendData();
	return false;
}

void Application::Render()
{
	hge->Gfx_BeginScene();
	hge->Gfx_Clear(0);

	/*for (std::vector<Ship*>::iterator it = shipList.begin(); it != shipList.end(); ++it)
	{
		Ship* ship = static_cast<Ship*>(*it);
		ship->Render();
	}*/
	for (std::vector<Ship*>::iterator it = shipList.begin(); it != shipList.end(); ++it)
	{
		Ship* ship = static_cast<Ship*>(*it);
		if (ship)
		{
			ship->Render();
		}
	}

	// Lab 13 Task 6 : Render the missile


	// Lab 13 Task 12 : Render network missiles


	hge->Gfx_EndScene();
}

bool Application::Loop()
{
	Global::application->Render();
	return Global::application->Update();
}

/**
* Shuts down the graphics and network system
*/
void Application::Shutdown()
{
	hge->System_Shutdown();
	hge->Release();
}

/**
* Kick starts the everything, called from main.
*/
void Application::Start()
{
	if (Init())
	{
		hge->System_Start();
	}
}

bool Application::SendInitialPosition()
{
	RakNet::BitStream bs;
	unsigned char msgid = ID_INITIALPOS;
	bs.Write(msgid);
	bs.Write(shipList.at(0)->getPos().x);
	bs.Write(shipList.at(0)->getPos().y);
	bs.Write(shipList.at(0)->GetType());

	std::cout << "Sending pos" << shipList.at(0)->getPos().x << " " << shipList.at(0)->getPos().y << std::endl;

	rakpeer->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true);

	return true;
}

bool Application::checkCollisions(Ship* ship1)
{
	/*for (std::vector<Ship*>::iterator it = shipList.begin(); it != shipList.end(); ++it)
	{
		CGameObject* go2 = static_cast<CGameObject*>(*it);
		if (go1 == go2)
			continue;

		Ship* ship1 = static_cast<Ship*>(go1);
		if (ship1)
		{
			Ship* ship2 = static_cast<Ship*>(go2);
			if (ship1 && ship2)
			{
				Ship_ShipCollision(ship1, ship2);
			}
		}
	}*/
	for (std::vector<Ship*>::iterator it = shipList.begin(); it != shipList.end(); ++it)
	{
		Ship* ship2 = static_cast<Ship*>(*it);
		if (ship1 == ship2)
			continue;
	}

//	for (std::vector<Ship*>::iterator it = shipList.begin(); it != shipList.end(); ++it)
//	{
//		Ship* ship2 = static_cast<Ship*>(*it);
//
//		if (ship2 == ship1) continue;	//skip if it is the same ship
//
//		if (ship1->HasCollided(ship2))
//		{
//			if (ship2->CanCollide(RakNet::GetTime()) && ship1->CanCollide(RakNet::GetTime()))
//			{
//				std::cout << "collide!" << std::endl;
//
//#ifdef INTERPOLATEMOVEMENT
//				if (GetAbsoluteMag(ship1->getVel().y) > GetAbsoluteMag(ship2->getVel().y))
//				{
//					// this transfers vel to thisship
//					ship2->SetVelocityY(ship2->getVel().y + ship1->getVel().y / 3);
//					ship1->SetVelocityY(-ship1->getVel().y);
//
//					ship2->SetServerVelocityY(ship2->getServerVel().y + ship1->getServerVel().y / 3);
//					ship1->SetServerVelocityY(-ship1->getServerVel().y);
//				}
//				else
//				{
//					ship1->SetVelocityY(ship1->getVel().y + ship2->getVel().y / 3);
//					ship2->SetVelocityY(-ship2->getVel().y / 2);
//
//					ship1->SetServerVelocityY(ship1->getServerVel().y + ship2->getServerVel().y / 3);
//					ship2->SetServerVelocityY(-ship2->getServerVel().y / 2);
//				}
//
//				if (GetAbsoluteMag(ship1->getVel().x) > GetAbsoluteMag(ship2->getVel().x))
//				{
//					// this transfers vel to thisship
//					ship2->SetVelocityX(ship2->getVel().x + ship1->getVel().x / 3);
//					ship1->SetVelocityX(-ship1->getVel().x);
//
//					ship2->SetServerVelocityX(ship2->getServerVel().x + ship1->getServerVel().x / 3);
//					ship1->SetServerVelocityX(-ship1->getServerVel().x);
//				}
//				else
//				{
//					// ship transfers vel to asteroid
//					ship1->SetVelocityX(ship1->getVel().x + ship2->getVel().x / 3);
//					ship2->SetVelocityX(-ship2->getVel().x / 2);
//
//					ship1->SetServerVelocityX(ship1->getServerVel().x + ship2->getServerVel().x / 3);
//					ship2->SetServerVelocityX(-ship2->getServerVel().x / 2);
//				}
//
//				ship1->SetPreviousLocation();
//#else
//				if (GetAbsoluteMag(ship->GetVelocityY()) > GetAbsoluteMag((*thisship)->GetVelocityY()))
//				{
//					// this transfers vel to thisship
//					(*thisship)->SetVelocityY((*thisship)->GetVelocityY() + ship->GetVelocityY() / 3);
//					ship->SetVelocityY(-ship->GetVelocityY());
//				}
//				else
//				{
//					ship->SetVelocityY(ship->GetVelocityY() + (*thisship)->GetVelocityY() / 3);
//					(*thisship)->SetVelocityY(-(*thisship)->GetVelocityY() / 2);
//				}
//
//				if (GetAbsoluteMag(ship->GetVelocityX()) > GetAbsoluteMag((*thisship)->GetVelocityX()))
//				{
//					// this transfers vel to thisship
//					(*thisship)->SetVelocityX((*thisship)->GetVelocityX() + ship->GetVelocityX() / 3);
//					ship->SetVelocityX(-ship->GetVelocityX());
//				}
//				else
//				{
//					// ship transfers vel to asteroid
//					ship->SetVelocityX(ship->GetVelocityX() + (*thisship)->GetVelocityX() / 3);
//					(*thisship)->SetVelocityX(-(*thisship)->GetVelocityX() / 2);
//				}
//
//
//				//				ship->SetVelocityY( -ship->GetVelocityY() );
//				//				ship->SetVelocityX( -ship->GetVelocityX() );
//
//				ship->SetPreviousLocation();
//#endif
//				SendCollision(ship2);
//
//				return true;
//			}
//
//		}
//
//	}

	return false;
}

void Application::SendCollision(Ship* ship1)
{
	RakNet::BitStream bs;
	unsigned char msgid = ID_COLLIDE;
	bs.Write(msgid);
	bs.Write(ship1->GetID());
	bs.Write(ship1->getPos().x);
	bs.Write(ship1->getPos().y);
	bs.Write(ship1->getVel().x);
	bs.Write(ship1->getVel().y);
#ifdef INTERPOLATEMOVEMENT
	bs.Write(ship1->getServerVel().x);
	bs.Write(ship1->getServerVel().y);
#endif

	rakpeer->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true);
}

void Application::CreateMissile(float x, float y, float w, int id)
{
#ifdef NETWORKMISSLE
	// Lab 13 Task 9b : Implement networked version of createmissile


#else
	// Lab 13 Task 3 : Implement local version missile creation

#endif
}

void Application::playerControl(const float dt)
{
	shipList.at(0)->SetAngularVelocity(0.0f);

	if (hge->Input_GetKeyState(HGEK_LEFT))
	{
		shipList.at(0)->SetAngularVelocity(shipList.at(0)->GetAngularVelocity() - DEFAULT_ANGULAR_VELOCITY);
	}

	if (hge->Input_GetKeyState(HGEK_RIGHT))
	{
		shipList.at(0)->SetAngularVelocity(shipList.at(0)->GetAngularVelocity() + DEFAULT_ANGULAR_VELOCITY);
	}

	if (hge->Input_GetKeyState(HGEK_UP))
	{
		shipList.at(0)->Accelerate(DEFAULT_ACCELERATION, dt);
	}

	if (hge->Input_GetKeyState(HGEK_DOWN))
	{
		shipList.at(0)->Accelerate(-DEFAULT_ACCELERATION, dt);
	}
}

void Application::welcome(RakNet::BitStream &bs)
{
	unsigned int shipcount, id;
	float x_, y_;
	int type_;
	std::string temp;
	char chartemp[5];

	bs.Read(id);
	shipList.at(0)->setID(id);
	bs.Read(shipcount);

	for (unsigned int i = 0; i < shipcount; ++i)
	{
		bs.Read(id);
		bs.Read(x_);
		bs.Read(y_);
		bs.Read(type_);
		std::cout << "New Ship pos" << x_ << " " << y_ << std::endl;
		Ship* ship = new Ship(type_, x_, y_);
		temp = "Ship ";
		temp += _itoa(id, chartemp, 10);
		ship->SetName(temp.c_str());
		ship->setID(id);
		shipList.push_back(ship);
	}
}

void Application::newPlayer(RakNet::BitStream &bs)
{
	unsigned int id;
	bs.Read(id);

	if (id == shipList.at(0)->GetID())
	{
		// if it is me
		return;
	}
	else
	{
		float x_, y_;
		int type_;
		std::string temp;
		char chartemp[5];

		bs.Read(x_);
		bs.Read(y_);
		bs.Read(type_);
		std::cout << "New Ship pos" << x_ << " " << y_ << std::endl;
		Ship* ship = new Ship(type_, x_, y_);
		temp = "Ship ";
		temp += _itoa(id, chartemp, 10);
		ship->SetName(temp.c_str());
		ship->setID(id);
		shipList.push_back(ship);
	}
}

void Application::removePlayer(RakNet::BitStream &bs)
{
	unsigned int shipid;
	bs.Read(shipid);

	/*for (std::vector<Ship*>::iterator it = shipList.begin(); it != shipList.end(); ++it)
	{
		Ship* ship = static_cast<Ship*>(*it);

		if (ship->GetID() == shipid)
		{
			delete ship;
			shipList.erase(it);
			break;
		}
	}*/
	for (std::vector<Ship*>::iterator it = shipList.begin(); it != shipList.end(); ++it)
	{
		/*Ship* ship = static_cast<Ship*>(*it);

		if (ship->GetID() == shipid)
		{
			delete ship;
			shipList.erase(it);
			break;
		}*/
		Ship* ship = static_cast<Ship*>(*it);
		if (ship)
		{
			if (ship->GetID() == shipid)
			{
				delete *it;
				shipList.erase(it);
				break;
			}
		}
	}
}

void Application::movementUpdate(RakNet::BitStream &bs)
{
	unsigned int shipid;
	float temp;
	float x, y, w;
	bs.Read(shipid);

	for (std::vector<Ship*>::iterator it = shipList.begin(); it != shipList.end(); ++it)
	{
		Ship* ship = static_cast<Ship*>(*it);

		if (ship)
		{
			if (ship->GetID() == shipid)
			{
				// this portion needs to be changed for it to work
#ifdef INTERPOLATEMOVEMENT
				bs.Read(x);
				bs.Read(y);
				bs.Read(w);

				ship->SetServerLocation(x, y, w);

				bs.Read(temp);
				ship->SetServerVelocityX(temp);

				bs.Read(temp);
				ship->SetServerVelocityY(temp);

				bs.Read(temp);
				ship->SetAngularVelocity(temp);

				ship->DoInterpolateUpdate();
#else
				bs.Read(x);
				bs.Read(y);
				bs.Read(w);
				(*itr)->setLocation(x, y, w);

				// Lab 7 Task 1 : Read Extrapolation Data velocity x, velocity y & angular velocity
				bs.Read(temp);
				(*itr)->SetVelocityX(temp);
				bs.Read(temp);
				(*itr)->SetVelocityY(temp);
				bs.Read(temp);
				(*itr)->SetAngularVelocity(temp);
#endif

				break;
			}
		}
	}
}

void Application::collisionUpdate(RakNet::BitStream &bs)
{
	unsigned int shipid;
	float x, y;
	bs.Read(shipid);

	if (shipid == shipList.at(0)->GetID())
	{
		std::cout << "collided with someone!" << std::endl;
		bs.Read(x);
		bs.Read(y);
		shipList.at(0)->setPosX(x);
		shipList.at(0)->setPosY(y);
		bs.Read(x);
		bs.Read(y);
		shipList.at(0)->SetVelocityX(x);
		shipList.at(0)->SetVelocityY(y);
#ifdef INTERPOLATEMOVEMENT
		bs.Read(x);
		bs.Read(y);
		shipList.at(0)->SetServerVelocityX(x);
		shipList.at(0)->SetServerVelocityY(y);
#endif	
	}
}

void Application::sendData()
{
	if (RakNet::GetTime() - timer > 1000)
	{
		timer = RakNet::GetTime();
		RakNet::BitStream bs;
		unsigned char msgid = ID_MOVEMENT;
		bs.Write(msgid);

#ifdef INTERPOLATEMOVEMENT
		bs.Write(shipList.at(0)->GetID());
		bs.Write(shipList.at(0)->getServerPos().x);
		bs.Write(shipList.at(0)->getServerPos().y);
		bs.Write(shipList.at(0)->getServerPos().w);
		bs.Write(shipList.at(0)->getServerVel().x);
		bs.Write(shipList.at(0)->getServerVel().y);
		bs.Write(shipList.at(0)->GetAngularVelocity());

#else
		bs2.Write(shipList.at(0)->GetID());
		bs2.Write(shipList.at(0)->GetX());
		bs2.Write(shipList.at(0)->GetY());
		bs2.Write(shipList.at(0)->GetW());
		// Lab 7 Task 1 : Add Extrapolation Data velocity x, velocity y & angular velocity
		bs2.Write(shipList.at(0)->GetVelocityX());
		bs2.Write(shipList.at(0)->GetVelocityY());
		bs2.Write(shipList.at(0)->GetAngularVelocity());
#endif

		rakpeer->Send(&bs, HIGH_PRIORITY, RELIABLE, 0, UNASSIGNED_SYSTEM_ADDRESS, true);


		// Lab 13 Task 11 : send missile update 


	}
}

void Application::Ship_ShipCollision(Ship* ship1, Ship* ship2)
{
	if (ship1->HasCollided(ship2))
	{
		if (ship1->CanCollide(RakNet::GetTime()) && ship2->CanCollide(RakNet::GetTime()))
		{
			std::cout << "Ship to Ship Collision" << std::endl;

#ifdef INTERPOLATEMOVEMENT
			if (GetAbsoluteMag(ship1->getVel().y) > GetAbsoluteMag(ship2->getVel().y))
			{
				// this transfers vel to thisship
				ship2->SetVelocityY(ship2->getVel().y + ship1->getVel().y / 3);
				ship1->SetVelocityY(-ship1->getVel().y);

				ship2->SetServerVelocityY(ship2->getServerVel().y + ship1->getServerVel().y / 3);
				ship1->SetServerVelocityY(-ship1->getServerVel().y);
			}
			else
			{
				ship1->SetVelocityY(ship1->getVel().y + ship2->getVel().y / 3);
				ship2->SetVelocityY(-ship2->getVel().y / 2);

				ship1->SetServerVelocityY(ship1->getServerVel().y + ship2->getServerVel().y / 3);
				ship2->SetServerVelocityY(-ship2->getServerVel().y / 2);
			}

			if (GetAbsoluteMag(ship1->getVel().x) > GetAbsoluteMag(ship2->getVel().x))
			{
				// this transfers vel to thisship
				ship2->SetVelocityX(ship2->getVel().x + ship1->getVel().x / 3);
				ship1->SetVelocityX(-ship1->getVel().x);

				ship2->SetServerVelocityX(ship2->getServerVel().x + ship1->getServerVel().x / 3);
				ship1->SetServerVelocityX(-ship1->getServerVel().x);
			}
			else
			{
				// ship transfers vel to asteroid
				ship1->SetVelocityX(ship1->getVel().x + ship2->getVel().x / 3);
				ship2->SetVelocityX(-ship2->getVel().x / 2);

				ship1->SetServerVelocityX(ship1->getServerVel().x + ship2->getServerVel().x / 3);
				ship2->SetServerVelocityX(-ship2->getServerVel().x / 2);
			}

			ship1->SetPreviousLocation();
#else
			if (GetAbsoluteMag(ship->GetVelocityY()) > GetAbsoluteMag((*thisship)->GetVelocityY()))
			{
				// this transfers vel to thisship
				(*thisship)->SetVelocityY((*thisship)->GetVelocityY() + ship->GetVelocityY() / 3);
				ship->SetVelocityY(-ship->GetVelocityY());
			}
			else
			{
				ship->SetVelocityY(ship->GetVelocityY() + (*thisship)->GetVelocityY() / 3);
				(*thisship)->SetVelocityY(-(*thisship)->GetVelocityY() / 2);
			}

			if (GetAbsoluteMag(ship->GetVelocityX()) > GetAbsoluteMag((*thisship)->GetVelocityX()))
			{
				// this transfers vel to thisship
				(*thisship)->SetVelocityX((*thisship)->GetVelocityX() + ship->GetVelocityX() / 3);
				ship->SetVelocityX(-ship->GetVelocityX());
			}
			else
			{
				// ship transfers vel to asteroid
				ship->SetVelocityX(ship->GetVelocityX() + (*thisship)->GetVelocityX() / 3);
				(*thisship)->SetVelocityX(-(*thisship)->GetVelocityX() / 2);
			}


			//				ship->SetVelocityY( -ship->GetVelocityY() );
			//				ship->SetVelocityX( -ship->GetVelocityX() );

			ship->SetPreviousLocation();
#endif
			SendCollision(ship2);
		}
	}
}