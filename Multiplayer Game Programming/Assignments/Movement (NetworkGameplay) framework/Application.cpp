#include "Application.h"
#include "ship.h"
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
#define NETWORKMISSILE


float GetAbsoluteMag(float num)
{
	if (num < 0)
	{
		return -num;
	}

	return num;
}

/**
* Constuctor
*
* Creates an instance of the graphics engine and network engine
*/

Application::Application()
	: hge_(hgeCreate(HGE_VERSION))
	, rakpeer_(RakNetworkFactory::GetRakPeerInterface())
	, timer_(0)
	// Lab 13 Task 2 : add new initializations
	//, mymissile(0)
{
}

/**
* Destructor
*
* Does nothing in particular apart from calling Shutdown
*/

Application::~Application() throw()
{
	Shutdown();
	rakpeer_->Shutdown(100);
	RakNetworkFactory::DestroyRakPeerInterface(rakpeer_);
}

/**
* Initialises the graphics system
* It should also initialise the network system
*/

bool Application::Init()
{
	std::ifstream inData;
	std::string serverip;

	inData.open("serverip.txt");

	inData >> serverip;

	srand(RakNet::GetTime());

	hge_->System_SetState(HGE_FRAMEFUNC, Application::Loop);
	hge_->System_SetState(HGE_WINDOWED, true);
	hge_->System_SetState(HGE_USESOUND, false);
	hge_->System_SetState(HGE_TITLE, "Movement");
	hge_->System_SetState(HGE_LOGFILE, "movement.log");
	hge_->System_SetState(HGE_DONTSUSPEND, true);
	hge_->System_SetState(HGE_SCREENWIDTH, 1280);
	hge_->System_SetState(HGE_SCREENHEIGHT, 720);

	if (hge_->System_Initiate())
	{
		ShipList.push_back(new Ship(Math::RandIntMinMax(1, 4) , rand() % 500 + 100, rand() % 400 + 100));
		ShipList.at(0)->SetName("My Ship");
		if (rakpeer_->Startup(1, 30, &SocketDescriptor(), 1))
		{
			rakpeer_->SetOccasionalPing(true);
			return rakpeer_->Connect(serverip.c_str(), 1691, 0, 0);
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
	if (hge_->Input_GetKeyState(HGEK_ESCAPE))
		return true;

	float timedelta = hge_->Timer_GetDelta();

	playerControl(timedelta);

	// Lab 13 Task 4 : Add a key to shoot missiles


	for (std::vector<Ship*>::iterator it = ShipList.begin(); it != ShipList.end(); ++it)
	{
		Ship* ship = static_cast<Ship*>(*it);
		ship->Update(timedelta);

		if (ship == ShipList.at(0))
		{
			checkCollisions(ship);
		}
	}

	/*if (mymissile)
	{
		if (mymissile->Update(ShipList, timedelta))
		{
			delete mymissile;
			mymissile = NULL;
		}
	}*/

	/*for (std::vector<Missile*>::iterator it = missileList.begin(); it != missileList.end(); ++it)
	{
		Missile* missile = static_cast<Missile*>(*it);
		if (missile->Update(ShipList, timedelta))
		{
			delete *it;
			missileList.erase(it);
			break;
		}
	}*/

	for (std::vector<CProjectile*>::iterator it = projectileList.begin(); it != projectileList.end(); ++it)
	{
		/*Missile* missile = static_cast<Missile*>(*it);
		if (missile->Update(ShipList, timedelta))
		{
			delete *it;
			missileList.erase(it);
			break;
		}*/
		CProjectile* projectile = static_cast<CProjectile*>(*it);
		if (projectile->getActive())
		{
			if (projectile->Update(ShipList, timedelta))
			{
				/*delete *it;
				projectileList.erase(it);*/
				projectile->setActive(false);
				break;
			}
		}
	}

	// Lab 13 Task 5 : Updating the missile


	// Lab 13 Task 13 : Update network missiles
	/*for (std::vector<Missile*>::iterator it = missileList.begin(); it != missileList.end(); ++it)
	{
		Missile* missile = static_cast<Missile*>(*it);
		if (missile->Update(ShipList, timedelta))
		{
			delete *it;
			missileList.erase(it);
			break;
		}
	}*/


	if (Packet* packet = rakpeer_->Receive())
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
			rakpeer_->DeallocatePacket(packet);
			return true;

		case ID_WELCOME:
		{
			welcome(bs);
		}
		break;

		case ID_NEWSHIP:
		{
			newPlayer(bs);
		}
		break;

		case ID_LOSTSHIP:
		{
			removePlayer(bs);
		}
		break;

		case ID_INITIALPOS:
			break;

		case ID_MOVEMENT:
		{
			movementUpdate(bs);
		}
		break;

		case ID_COLLIDE:
		{
			collisionUpdate(bs);
		}
		break;


		// Lab 13 Task 10 : new cases to handle missile on application side
		case ID_NEWMISSILE:
		{
			float x, y, w;
			int id;

			bs.Read(id);
			bs.Read(x);
			bs.Read(y);
			bs.Read(w);

			projectileList.push_back(new Missile("missile.png", x, y, w, id));
		}
		break;

		case ID_UPDATEMISSILE:
		{
			float x, y, w;
			int id;
			char deleted;

			bs.Read(id);
			bs.Read(deleted);

			/*for (std::vector<Missile*>::iterator it = missileList.begin(); it != missileList.end(); ++it)
			{
				Missile* missile = static_cast<Missile*>(*it);
				if(missile->getOwnerID() == id)
				{
					if (deleted == 1)
					{
						delete *it;
						missileList.erase(it);
					}
					else
					{
						bs.Read(x);
						bs.Read(y);
						bs.Read(w);
						missile->UpdateLoc(x, y, w);

						bs.Read(x);
						missile->setVelocityX(x);

						bs.Read(y);
						missile->setVelocityY(y);
					}
					break;
				}
			}*/
			for (std::vector<CProjectile*>::iterator it = projectileList.begin(); it != projectileList.end(); ++it)
			{
				CProjectile* projectile = static_cast<CProjectile*>(*it);
				if (projectile->getOwnerID() == id)
				{
					//if (projectile->getActive())
					{
						if (deleted == 1 || !projectile->getActive())
						{
							/*delete *it;
							projectileList.erase(it);*/
							projectile->setActive(false);
						}
						else
						{
							bs.Read(x);
							bs.Read(y);
							bs.Read(w);
							projectile->UpdateLoc(x, y, w);

							bs.Read(x);
							projectile->setVelocityX(x);

							bs.Read(y);
							projectile->setVelocityY(y);
						}
						break;
					}
				}
			}
		}
		break;

		default:
			std::cout << "Unhandled Message Identifier: " << (int)msgid << std::endl;

		}
		rakpeer_->DeallocatePacket(packet);
	}

	sendData();

	return false;
}


/**
* Render Cycle
*
* Clear the screen and render all the ships
*/
void Application::Render()
{
	hge_->Gfx_BeginScene();
	hge_->Gfx_Clear(0);

	/*ShipList::iterator itr;
	for (itr = ships_.begin(); itr != ships_.end(); itr++)
	{
		(*itr)->Render();
	}*/
	for (std::vector<Ship*>::iterator it = ShipList.begin(); it != ShipList.end(); ++it)
	{
		Ship* ship = static_cast<Ship*>(*it);
		ship->Render();
	}

	/*for (std::vector<Missile*>::iterator it = missileList.begin(); it != missileList.end(); ++it)
	{
		Missile* missile = static_cast<Missile*>(*it);
		missile->Render();
	}*/
	for (std::vector<CProjectile*>::iterator it = projectileList.begin(); it != projectileList.end(); ++it)
	{
		CProjectile* projectile = static_cast<CProjectile*>(*it);
		if(projectile->getActive())
			projectile->Render();
	}

	/*if (mymissile)
	{
		mymissile->Render();
	}*/

	// Lab 13 Task 6 : Render the missile


	// Lab 13 Task 12 : Render network missiles


	hge_->Gfx_EndScene();
}


/**
* Main game loop
*
* Processes user input events
* Supposed to process network events
* Renders the ships
*
* This is a static function that is called by the graphics
* engine every frame, hence the need to loop through the
* global namespace to find itself.
*/
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
	hge_->System_Shutdown();
	hge_->Release();
}

/**
* Kick starts the everything, called from main.
*/
void Application::Start()
{
	if (Init())
	{
		hge_->System_Start();
	}
}

bool Application::SendInitialPosition()
{
	RakNet::BitStream bs;
	unsigned char msgid = ID_INITIALPOS;
	bs.Write(msgid);
	bs.Write(ShipList.at(0)->getPos().x);
	bs.Write(ShipList.at(0)->getPos().y);
	bs.Write(ShipList.at(0)->GetType());

	std::cout << "Sending pos" << ShipList.at(0)->getPos().x << " " << ShipList.at(0)->getPos().y << std::endl;

	rakpeer_->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true);

	return true;
}

bool Application::checkCollisions(Ship* ship)
{
	for (std::vector<Ship*>::iterator it = ShipList.begin(); it != ShipList.end(); ++it)
	{
		Ship* ship2 = static_cast<Ship*>(*it);

		if (ship2 == ship) continue;	//skip if it is the same ship

		if (ship->HasCollided(ship2))
		{
			if (ship2->CanCollide(RakNet::GetTime()) && ship->CanCollide(RakNet::GetTime()))
			{
				std::cout << "collide!" << std::endl;

#ifdef INTERPOLATEMOVEMENT
				if (GetAbsoluteMag(ship->getVel().y) > GetAbsoluteMag(ship2->getVel().y))
				{
					// this transfers vel to thisship
					ship2->SetVelocityY(ship2->getVel().y + ship->getVel().y / 3);
					ship->SetVelocityY(-ship->getVel().y);

					ship2->SetServerVelocityY(ship2->getVel().y + ship->getVel().y / 3);
					ship->SetServerVelocityY(-ship->getVel().y);
				}
				else
				{
					ship->SetVelocityY(ship->getVel().y + ship2->getVel().y / 3);
					ship2->SetVelocityY(-ship2->getVel().y / 2);

					ship->SetServerVelocityY(ship->getServerVel().y + ship2->getServerVel().y / 3);
					ship2->SetServerVelocityY(-ship2->getServerVel().y / 2);
				}

				if (GetAbsoluteMag(ship->getVel().x) > GetAbsoluteMag(ship2->getVel().x))
				{
					// this transfers vel to thisship
					ship2->SetVelocityX(ship2->getVel().x + ship->getVel().x / 3);
					ship->SetVelocityX(-ship->getVel().x);

					ship2->SetServerVelocityX(ship2->getServerVel().x + ship->getServerVel().x / 3);
					ship->SetServerVelocityX(-ship->getServerVel().x);
				}
				else
				{
					// ship transfers vel to asteroid
					ship->SetVelocityX(ship->getVel().x + ship2->getVel().x / 3);
					ship2->SetVelocityX(-ship2->getVel().x / 2);

					ship->SetServerVelocityX(ship->getServerVel().x + ship2->getServerVel().x / 3);
					ship2->SetServerVelocityX(-ship2->getServerVel().x / 2);
				}

				ship->SetPreviousLocation();
#else
				if (GetAbsoluteMag(ship->getVel().y()) > GetAbsoluteMag((*thisship)->getVel().y()))
				{
					// this transfers vel to thisship
					(*thisship)->SetVelocityY((*thisship)->getVel().y() + ship->getVel().y() / 3);
					ship->SetVelocityY(-ship->getVel().y());
				}
				else
				{
					ship->SetVelocityY(ship->getVel().y() + (*thisship)->getVel().y() / 3);
					(*thisship)->SetVelocityY(-(*thisship)->getVel().y() / 2);
				}

				if (GetAbsoluteMag(ship->getVel().x) > GetAbsoluteMag((*thisship)->getVel().x))
				{
					// this transfers vel to thisship
					(*thisship)->SetVelocityX((*thisship)->getVel().x + ship->getVel().x / 3);
					ship->SetVelocityX(-ship->getVel().x);
				}
				else
				{
					// ship transfers vel to asteroid
					ship->SetVelocityX(ship->getVel().x + (*thisship)->getVel().x / 3);
					(*thisship)->SetVelocityX(-(*thisship)->getVel().x / 2);
				}


				//				ship->SetVelocityY( -ship->getVel().y() );
				//				ship->SetVelocityX( -ship->getVel().x );

				ship->SetPreviousLocation();
#endif
				SendCollision(ship2);

				return true;
			}

		}

	}

	return false;
}

void Application::SendCollision(Ship* ship)
{
	RakNet::BitStream bs;
	unsigned char msgid = ID_COLLIDE;
	bs.Write(msgid);
	bs.Write(ship->GetID());
	bs.Write(ship->getPos().x);
	bs.Write(ship->getPos().y);
	bs.Write(ship->getVel().x);
	bs.Write(ship->getVel().y);
#ifdef INTERPOLATEMOVEMENT
	bs.Write(ship->getServerVel().x);
	bs.Write(ship->getServerVel().y);
#endif

	rakpeer_->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true);

}

void Application::CreateMissile(float x, float y, float w, int id)
{
#ifdef NETWORKMISSILE
	// Lab 13 Task 9b : Implement networked version of createmissile
	RakNet::BitStream bs;
	unsigned char msgid;
	unsigned char deleted = 0;
	//if (mymissile)
	//{
	//	//sendupdatethroughnetworktodeletethismissile
	//	deleted = 1;
	//	msgid = ID_UPDATEMISSILE;
	//	bs.Write(msgid);
	//	bs.Write(id);
	//	bs.Write(deleted);
	//	bs.Write(x);
	//	bs.Write(y);
	//	bs.Write(w);
	//	rakpeer_->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true);
	//	//deleteexistingmissile
	//	delete mymissile;
	//	mymissile = 0;
	//}

	////addanewmissilebasedonthefollowingparametercoordinates
	//mymissile = new Missile("missile.png", x, y, w, id);
	////sendnetworkcommandtoaddnewmissile
	//bs.Reset();
	//msgid = ID_NEWMISSILE;
	//bs.Write(msgid);
	//bs.Write(id);
	//bs.Write(x);
	//bs.Write(y);
	//bs.Write(w);
	//rakpeer_->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true);
	Missile* missile = new Missile("missile.png", x, y, w, id);
	//missileList.push_back(missile);
	projectileList.push_back(missile);
	msgid = ID_NEWMISSILE;
	bs.Write(msgid);
	bs.Write(id);
	bs.Write(x);
	bs.Write(y);
	bs.Write(w);
	rakpeer_->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true);
#else
	// Lab 13 Task 3 : Implement local version missile creation
	Missile* missile = new Missile("missile.png", x, y, w, id);
	missileList.push_back(missile);

#endif
}

void Application::playerControl(const float dt)
{
	ShipList.at(0)->SetAngularVelocity(0.0f);

	if (hge_->Input_GetKeyState(HGEK_LEFT))
	{
		ShipList.at(0)->SetAngularVelocity(ShipList.at(0)->GetAngularVelocity() - DEFAULT_ANGULAR_VELOCITY);
	}

	if (hge_->Input_GetKeyState(HGEK_RIGHT))
	{
		ShipList.at(0)->SetAngularVelocity(ShipList.at(0)->GetAngularVelocity() + DEFAULT_ANGULAR_VELOCITY);
	}

	if (hge_->Input_GetKeyState(HGEK_UP))
	{
		ShipList.at(0)->Accelerate(DEFAULT_ACCELERATION, dt);
	}

	if (hge_->Input_GetKeyState(HGEK_DOWN))
	{
		ShipList.at(0)->Accelerate(-DEFAULT_ACCELERATION, dt);
	}

	static bool keyDown_Enter = false;
	if (hge_->Input_GetKeyState(HGEK_ENTER))
	{
		if (!keyDown_Enter)
		{
			CreateMissile(ShipList.at(0)->getPos().x, ShipList.at(0)->getPos().y, ShipList.at(0)->getPos().w, ShipList.at(0)->GetID());
			keyDown_Enter = true;
		}
	}
	else
	{
		if (keyDown_Enter)
		{
			keyDown_Enter = false;
		}
	}
}

void Application::welcome(RakNet::BitStream& bs)
{
	unsigned int shipcount, id;
	float x_, y_;
	int type_;
	std::string temp;
	char chartemp[5];

	bs.Read(id);
	ShipList.at(0)->setID(id);
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
		ShipList.push_back(ship);
	}

	SendInitialPosition();
}

void Application::newPlayer(RakNet::BitStream &bs)
{
	unsigned int id;
	bs.Read(id);

	if (id == ShipList.at(0)->GetID())
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
		ShipList.push_back(ship);
	}
}

void Application::removePlayer(RakNet::BitStream &bs)
{
	unsigned int shipid;
	bs.Read(shipid);
	/*for (ShipList::iterator itr = ships_.begin(); itr != ships_.end(); ++itr)
	{
	if ((*itr)->GetID() == shipid)
	{
	delete *itr;
	ships_.erase(itr);
	break;
	}
	}*/
	for (std::vector<Ship*>::iterator it = ShipList.begin(); it != ShipList.end(); ++it)
	{
		Ship* ship = static_cast<Ship*>(*it);
		if (ship->GetID() == shipid)
		{
			delete *it;
			ShipList.erase(it);
			break;
		}
	}
}

void Application::movementUpdate(RakNet::BitStream &bs)
{
	unsigned int shipid;
	float temp;
	float x, y, w;
	bs.Read(shipid);
	for (std::vector<Ship*>::iterator it = ShipList.begin(); it != ShipList.end(); ++it)
	{
		Ship* ship = static_cast<Ship*>(*it);
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

void Application::collisionUpdate(RakNet::BitStream &bs)
{
	unsigned int shipid;
	float x, y;
	bs.Read(shipid);

	if (shipid == ShipList.at(0)->GetID())
	{
		std::cout << "collided with someone!" << std::endl;
		bs.Read(x);
		bs.Read(y);
		ShipList.at(0)->setPosX(x);
		ShipList.at(0)->setPosY(y);
		bs.Read(x);
		bs.Read(y);
		ShipList.at(0)->SetVelocityX(x);
		ShipList.at(0)->SetVelocityY(y);
#ifdef INTERPOLATEMOVEMENT
		bs.Read(x);
		bs.Read(y);
		ShipList.at(0)->SetServerVelocityX(x);
		ShipList.at(0)->SetServerVelocityY(y);
#endif	
	}
}

void Application::sendData()
{
	if (RakNet::GetTime() - timer_ > 1000)
	{
		timer_ = RakNet::GetTime();
		RakNet::BitStream bs2;
		unsigned char msgid = ID_MOVEMENT;
		bs2.Write(msgid);

#ifdef INTERPOLATEMOVEMENT
		bs2.Write(ShipList.at(0)->GetID());
		bs2.Write(ShipList.at(0)->getServerPos().x);
		bs2.Write(ShipList.at(0)->getServerPos().y);
		bs2.Write(ShipList.at(0)->getServerPos().w);
		bs2.Write(ShipList.at(0)->getServerVel().x);
		bs2.Write(ShipList.at(0)->getServerVel().y);
		bs2.Write(ShipList.at(0)->GetAngularVelocity());

#else
		bs2.Write(ships_.at(0)->GetID());
		bs2.Write(ships_.at(0)->getPos().x);
		bs2.Write(ships_.at(0)->GetY());
		bs2.Write(ships_.at(0)->GetW());
		// Lab 7 Task 1 : Add Extrapolation Data velocity x, velocity y & angular velocity
		bs2.Write(ships_.at(0)->getVel().x);
		bs2.Write(ships_.at(0)->getVel().y());
		bs2.Write(ships_.at(0)->GetAngularVelocity());
#endif

		rakpeer_->Send(&bs2, HIGH_PRIORITY, RELIABLE, 0, UNASSIGNED_SYSTEM_ADDRESS, true);


		// Lab 13 Task 11 : send missile update
		/*if (mymissile)
		{
			RakNet::BitStream bs3;
			unsigned char msgid2 = ID_UPDATEMISSILE;
			unsigned char deleted = 0;
			bs3.Write(msgid2);
			bs3.Write(mymissile->GetOwnerID());
			bs3.Write(deleted);
			bs3.Write(mymissile->GetX());
			bs3.Write(mymissile->GetY());
			bs3.Write(mymissile->GetW());
			bs3.Write(mymissile->GetVelocityX());
			bs3.Write(mymissile->GetVelocityY());
			rakpeer_->Send(&bs3, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, UNASSIGNED_SYSTEM_ADDRESS, true);
		}*/
		for (std::vector<CProjectile*>::iterator it = projectileList.begin(); it != projectileList.end(); ++it)
		{
			CProjectile* projectile = static_cast<CProjectile*>(*it);
			if (projectile->getActive())
			{
				RakNet::BitStream bs3;
				unsigned char msgid2 = ID_UPDATEMISSILE;
				unsigned char deleted = 0;
				bs3.Write(msgid2);
				bs3.Write(projectile->getOwnerID());
				bs3.Write(deleted);
				bs3.Write(projectile->getPos().x);
				bs3.Write(projectile->getPos().y);
				bs3.Write(projectile->getPos().w);
				bs3.Write(projectile->getVel().x);
				bs3.Write(projectile->getVel().y);
				rakpeer_->Send(&bs3, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0, UNASSIGNED_SYSTEM_ADDRESS, true);
			}
		}
	}
}

//Missile* Application::fetchMissile()
//{
//	for (std::vector<CProjectile*>::iterator it = projectileList.begin(); it != projectileList.end(); ++it)
//	{
//		Missile* missile = dynamic_cast<Missile*>(*it);
//		if (missile)
//		{
//			if (!missile->getActive())
//			{
//				return missile;
//			}
//		}
//	}
//
//	for (int a = 0; a < 10; ++a)
//	{
//		Missile* missile = new Missile();
//		projectileList.push_back(missile);
//	}
//
//	Missile* missile = dynamic_cast<Missile*>(projectileList.back());
//	return missile;
//}