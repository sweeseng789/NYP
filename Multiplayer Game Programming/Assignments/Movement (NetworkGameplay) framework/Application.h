#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "GameObject.h"
#include "Ship.h"
#include "missile.h"
#include"BitStream.h"
#include <vector>

class HGE;
class RakPeerInterface;

//! The default angular velocity of the ship when it is in motion
static const float DEFAULT_ANGULAR_VELOCITY = 3.0f; 
//! The default acceleration of the ship when powered
static const float DEFAULT_ACCELERATION = 50.0f;

class Application
{
public:
	//===== CONSTRUCTOR & DESTRUCTOR =====//
	Application();
	~Application() throw();

	//===== SETTER =====//
	void Start();
	bool Init();
	static bool Loop();
	bool Update();
	void Shutdown();
	void SendCollision(Ship* ship1);
	void ProcessWelcomePackage();
	bool SendInitialPosition();

	//===== GETTER  =====//
	void Render();
	bool checkCollisions(Ship* ship1);
	void playerControl(const float dt);

	void welcome(RakNet::BitStream &bs);
	void newPlayer(RakNet::BitStream &bs);
	void removePlayer(RakNet::BitStream &bs);
	void movementUpdate(RakNet::BitStream &bs);
	void collisionUpdate(RakNet::BitStream &bs);

	void sendData();

	void Ship_ShipCollision(Ship* ship1, Ship* ship2);

private:
	// Lab 13 Task 1 : add variables for local missle


	// Lab 13 Task 8 : add variables to handle networked missiles


	// Lab 13
	void CreateMissile(float x, float y, float w, int id);
	bool RemoveMissile(float x, float y, float w, int id);

	//Int
	unsigned timer;

	//Class Variables Or Vector
	HGE* hge; //!< Instance of the internal graphics engine
	RakPeerInterface* rakpeer;
	std::vector<Ship*> shipList; //!< List of all the ships in the universe
};

#endif