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
#define NETWORKMISSLE



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
, mymissile(0)
, keydown_enter(false)
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

	if (hge_->System_Initiate())
	{
		//ships_.push_back(new Ship(rand() % 4 + 1, rand() % 500 + 100, rand() % 400 + 100));
		//ships_.at(0)->SetName("My Ship");
		shipList.push_back(new Ship(rand() % 4 + 1, rand() % 500 + 100, rand() % 400 + 400));
		shipList.at(0)->SetName("My Ship");
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

	shipList.at(0)->setAngularVelocity(0.0f);

	if (hge_->Input_GetKeyState(HGEK_LEFT))
	{
		shipList.at(0)->setAngularVelocity(shipList.at(0)->getAngularVelocity() - DEFAULT_ANGULAR_VELOCITY);
	}

	if (hge_->Input_GetKeyState(HGEK_RIGHT))
	{
		shipList.at(0)->setAngularVelocity(shipList.at(0)->getAngularVelocity() + DEFAULT_ANGULAR_VELOCITY);
	}

	if (hge_->Input_GetKeyState(HGEK_UP))
	{
		shipList.at(0)->Acclerate(DEFAULT_ACCELERATION, timedelta);
	}

	if (hge_->Input_GetKeyState(HGEK_DOWN))
	{
		shipList.at(0)->Acclerate(-DEFAULT_ACCELERATION, timedelta);
	}

	// Lab 13 Task 4 : Add a key to shoot missiles
	if (hge_->Input_GetKeyState(HGEK_ENTER))
	{
		if (!keydown_enter)
		{
			CreateMissile(shipList.at(0)->getPos().x, shipList.at(0)->getPos().y, shipList.at(0)->getPos().w, shipList.at(0)->getID());
			keydown_enter = true;
		}
	}
	else
	{
		if (keydown_enter)
		{
			keydown_enter = false;
		}
	}


	//for (ShipList::iterator ship = ships_.begin();
	//	ship != ships_.end(); ship++)
	//{
	//	(*ship)->Update(timedelta);

	//	//collisions
	//	if( (*ship) == ships_.at(0) )
	//		checkCollisions( (*ship) );
	//}
	for (Ship* ship : shipList)
	{
		ship->Update(timedelta);

		//Collision Detection

	}

	// Lab 13 Task 5 : Updating the missile
	if (mymissile)
	{
		if (mymissile->Update(shipList, timedelta))
		{
			//havecollision
			delete mymissile;
			mymissile = 0;
		}
	}


	// Lab 13 Task 13 : Update network missiles

	for (MissileList::iterator missile = missiles_.begin(); missile != missiles_.end(); missile++)
	{
		if ((*missile)->Update(shipList, timedelta))
		{
			//havecollision
			delete*missile;
			missiles_.erase(missile);
			break;
		}
	}

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

						   SendInitialPosition();
		}
			break;

		case ID_NEWSHIP:
		{
						   unsigned int id;
						   bs.Read(id);

						   if (id == shipList.at(0)->GetID())
						   {
							   // if it is me
							   break;
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
			break;

		case ID_LOSTSHIP:
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
							for (std::vector<Ship*>::iterator it = shipList.begin(); it != shipList.end(); ++it)
							{
								Ship* ship = static_cast<Ship*>(*it);
								if (ship->GetID() == shipid)
								{
									delete ship;
									shipList.erase(it);
									break;
								}
							}
		}
			break;

		case ID_INITIALPOS:
			break;

		case ID_MOVEMENT:
		{
							unsigned int shipid;
							float temp;
							float x, y, w;
							bs.Read(shipid);
							//for (ShipList::iterator itr = ships_.begin(); itr != ships_.end(); ++itr)
							for (std::vector<Ship*>::iterator it = shipList.begin(); it != shipList.end(); ++it)
							{
								Ship* ship = static_cast<Ship*>(*it);

								//if ((*itr)->GetID() == shipid)
								if (ship->GetID() == shipid)
								{
									// this portion needs to be changed for it to work
#ifdef INTERPOLATEMOVEMENT
									/*bs.Read(x);
									bs.Read(y);
									bs.Read(w);

									(*itr)->SetServerLocation(x, y, w);

									bs.Read(temp);
									(*itr)->SetServerVelocityX( temp );
									bs.Read(temp);
									(*itr)->SetServerVelocityY( temp );
									bs.Read(temp);
									(*itr)->SetAngularVelocity( temp );

									(*itr)->DoInterpolateUpdate();*/
									bs.Read(x);
									bs.Read(y);
									bs.Read(w);

									ship->setLocation(x, y, w);

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
									(*itr)->setLocation( x, y, w ); 

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
			break;

		case ID_COLLIDE:
		{
						   unsigned int shipid;
						   float x, y;
						   bs.Read(shipid);

						   if (shipid == shipList.at(0)->GetID())
						   {
							   std::cout << "collided with someone!" << std::endl;
							   bs.Read(x);
							   bs.Read(y);
							   shipList.at(0)->SetX(x);
							   shipList.at(0)->SetY(y);
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
			break;


			// Lab 13 Task 10 : new cases to handle missile on application side
		caseID_NEWMISSILE:
			{
				float x, y, w;
				int id;
				bs.Read(id);
				bs.Read(x);
				bs.Read(y);
				bs.Read(w);
				missiles_.push_back(new Missile("missile.png", x, y, w, id)
					);
			}
			break;
		caseID_UPDATEMISSILE:
			{
				float x, y, w;
				int id;
				char deleted;
				bs.Read(id);
				bs.Read(deleted);
				for (MissileList::iterator itr = missiles_.begin(); itr !=
					missiles_.end(); ++itr)
				{
					if ((*itr)->GetOwnerID() == id)
					{
						if (deleted == 1)
						{
							delete*itr;
							missiles_.erase(itr);
						}
						else
						{
							bs.Read(x);
							bs.Read(y);
							bs.Read(w);
							(*itr)->UpdateLoc(x, y, w);
							bs.Read(x);
							(*itr)->SetVelocityX(x);
							bs.Read(y);
							(*itr)->SetVelocityY(y);
						}
						break;
					}
				}
			}
			break;

		default:
			std::cout << "Unhandled Message Identifier: " << (int)msgid << std::endl;

		}
		rakpeer_->DeallocatePacket(packet);
	}

	if (RakNet::GetTime() - timer_ > 1000)
	{
		timer_ = RakNet::GetTime();
		RakNet::BitStream bs2;
		unsigned char msgid = ID_MOVEMENT;
		bs2.Write(msgid);

#ifdef INTERPOLATEMOVEMENT
		bs2.Write(shipList.at(0)->GetID());
		bs2.Write(shipList.at(0)->GetServerX());
		bs2.Write(shipList.at(0)->GetServerY());
		bs2.Write(shipList.at(0)->GetServerW());
		bs2.Write(shipList.at(0)->GetServerVelocityX());
		bs2.Write(shipList.at(0)->GetServerVelocityY());
		bs2.Write(shipList.at(0)->GetAngularVelocity());

#else
		bs2.Write(ships_.at(0)->GetID());
		bs2.Write(ships_.at(0)->GetX());
		bs2.Write(ships_.at(0)->GetY());
		bs2.Write(ships_.at(0)->GetW());
		// Lab 7 Task 1 : Add Extrapolation Data velocity x, velocity y & angular velocity
		bs2.Write(ships_.at(0)->GetVelocityX());
		bs2.Write(ships_.at(0)->GetVelocityY());
		bs2.Write(ships_.at(0)->GetAngularVelocity());
#endif

		rakpeer_->Send(&bs2, HIGH_PRIORITY, RELIABLE, 0, UNASSIGNED_SYSTEM_ADDRESS, true);


		// Lab 13 Task 11 : send missile update 
		if (mymissile)
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
			rakpeer_->Send(&bs3, HIGH_PRIORITY, UNRELIABLE_SEQUENCED, 0,
				UNASSIGNED_SYSTEM_ADDRESS, true);
		}


	}

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
	for (std::vector<Ship*>::iterator it = shipList.begin(); it != shipList.end(); ++it)
	{
		Ship* ship = static_cast<Ship*>(*it);
		ship->Render();
	}

	// Lab 13 Task 6 : Render the missile
	if (mymissile)
	{
		mymissile->Render();
	}

	// Lab 13 Task 12 : Render network missiles
	MissileList::iterator itr2;
	for (itr2 = missiles_.begin(); itr2 != missiles_.end(); itr2++)
	{
		(*itr2)->Render();
	}

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
	bs.Write(shipList.at(0)->GetX());
	bs.Write(shipList.at(0)->GetY());
	bs.Write(shipList.at(0)->GetType());

	std::cout << "Sending pos" << shipList.at(0)->GetX() << " " << shipList.at(0)->GetY() << std::endl;

	rakpeer_->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true);

	return true;
}

bool Application::checkCollisions(Ship* ship)
{
	for (std::vector<Ship*>::iterator thisship = shipList.begin(); thisship != shipList.end(); thisship++)
	{
		Ship* ship2 = static_cast<Ship*>(*thisship);

		if (ship2 == ship) continue;	//skip if it is the same ship

		if (ship->hasCollided((*thisship)))
		{
			if (ship2->canCollide(RakNet::GetTime()) && ship->canCollide(RakNet::GetTime()))
			{
				std::cout << "collide!" << std::endl;

#ifdef INTERPOLATEMOVEMENT
				if (GetAbsoluteMag(ship->getvel().y) > GetAbsoluteMag((*thisship)->getvel().y))
				{
					// this transfers vel to thisship
					ship2->getvel().y = ship2->getvel().y + ship->getvel().y / 3;
					ship->getvel().y *= -ship->getvel().y;


					/*(*thisship)->SetVelocityY((*thisship)->GetVelocityY() + ship->GetVelocityY() / 3);
					ship->SetVelocityY(-ship->GetVelocityY());

					(*thisship)->SetServerVelocityY((*thisship)->GetServerVelocityY() + ship->GetServerVelocityY() / 3);
					ship->SetServerVelocityY(-ship->GetServerVelocityY());*/
				}
				else
				{
					ship->SetVelocityY(ship->GetVelocityY() + (*thisship)->GetVelocityY() / 3);
					(*thisship)->SetVelocityY(-(*thisship)->GetVelocityY() / 2);

					ship->SetServerVelocityY(ship->GetServerVelocityY() + (*thisship)->GetServerVelocityY() / 3);
					(*thisship)->SetServerVelocityY(-(*thisship)->GetServerVelocityY() / 2);
				}

				if (GetAbsoluteMag(ship->GetVelocityX()) > GetAbsoluteMag((*thisship)->GetVelocityX()))
				{
					// this transfers vel to thisship
					(*thisship)->SetVelocityX((*thisship)->GetVelocityX() + ship->GetVelocityX() / 3);
					ship->SetVelocityX(-ship->GetVelocityX());

					(*thisship)->SetServerVelocityX((*thisship)->GetServerVelocityX() + ship->GetServerVelocityX() / 3);
					ship->SetServerVelocityX(-ship->GetServerVelocityX());
				}
				else
				{
					// ship transfers vel to asteroid
					ship->SetVelocityX(ship->GetVelocityX() + (*thisship)->GetVelocityX() / 3);
					(*thisship)->SetVelocityX( -(*thisship)->GetVelocityX()/2 );

					ship->SetServerVelocityX( ship->GetServerVelocityX() + (*thisship)->GetServerVelocityX()/3 ); 
					(*thisship)->SetServerVelocityX( -(*thisship)->GetServerVelocityX()/2 );
				}

				ship->SetPreviousLocation();
#else
				if( GetAbsoluteMag( ship->GetVelocityY() ) > GetAbsoluteMag( (*thisship)->GetVelocityY() ) )
				{
					// this transfers vel to thisship
					(*thisship)->SetVelocityY( (*thisship)->GetVelocityY() + ship->GetVelocityY()/3 );
					ship->SetVelocityY( - ship->GetVelocityY() );
				}
				else
				{
					ship->SetVelocityY( ship->GetVelocityY() + (*thisship)->GetVelocityY()/3 ); 
					(*thisship)->SetVelocityY( -(*thisship)->GetVelocityY()/2 );
				}

				if( GetAbsoluteMag( ship->GetVelocityX() ) > GetAbsoluteMag( (*thisship)->GetVelocityX() ) )
				{
					// this transfers vel to thisship
					(*thisship)->SetVelocityX( (*thisship)->GetVelocityX() + ship->GetVelocityX()/3 );
					ship->SetVelocityX( - ship->GetVelocityX() );
				}
				else
				{
					// ship transfers vel to asteroid
					ship->SetVelocityX( ship->GetVelocityX() + (*thisship)->GetVelocityX()/3 ); 
					(*thisship)->SetVelocityX( -(*thisship)->GetVelocityX()/2 );
				}


				//				ship->SetVelocityY( -ship->GetVelocityY() );
				//				ship->SetVelocityX( -ship->GetVelocityX() );

				ship->SetPreviousLocation();
#endif
				SendCollision((*thisship));

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
	bs.Write(ship->GetX());
	bs.Write(ship->GetY());
	bs.Write(ship->GetVelocityX());
	bs.Write(ship->GetVelocityY());
#ifdef INTERPOLATEMOVEMENT
	bs.Write(ship->GetServerVelocityX());
	bs.Write(ship->GetServerVelocityY());
#endif

	rakpeer_->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true);

}

void Application::CreateMissile(float x, float y, float w, int id)
{
#ifdef NETWORKMISSLE
	// Lab 13 Task 9b : Implement networked version of createmissile
	RakNet::BitStream bs;
	unsigned char msgid;
	unsigned char deleted = 0;
	if (mymissile)
	{
		//sendupdatethroughnetworktodeletethismissile
		deleted = 1;
		msgid = ID_UPDATEMISSILE;
		bs.Write(msgid);
		bs.Write(id);
		bs.Write(deleted);
		bs.Write(x);
		bs.Write(y);
		bs.Write(w);
		rakpeer_->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0,
			UNASSIGNED_SYSTEM_ADDRESS, true);
		//deleteexistingmissile
		delete mymissile;
		mymissile = 0;
	}
	//addanewmissilebasedonthefollowingparametercoordinates
	mymissile = new Missile("missile.png", x, y, w, id);
	//sendnetworkcommandtoaddnewmissile
	bs.Reset();
	msgid = ID_NEWMISSILE;
	bs.Write(msgid);
	bs.Write(id);
	bs.Write(x);
	bs.Write(y);
	bs.Write(w);
	rakpeer_->Send(&bs, HIGH_PRIORITY, RELIABLE_ORDERED, 0,
		UNASSIGNED_SYSTEM_ADDRESS, true);


#else
	// Lab 13 Task 3 : Implement local version missile creation
	if (mymissile)
	{
		//deleteexistingmissile
		delete mymissile;
		mymissile = 0;
	}
	//addanewmissilebasedonthefollowingparametercoordinates
	mymissile = new Missile("missile.png", x, y, w, id);

#endif
}
