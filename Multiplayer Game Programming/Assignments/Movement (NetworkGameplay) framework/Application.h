#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "ship.h"
#include "Projectile.h"
#include "missile.h"
#include "Bitstream.h"
#include <vector>

class HGE;
class RakPeerInterface;

//! The default angular velocity of the ship when it is in motion
static const float DEFAULT_ANGULAR_VELOCITY = 3.0f; 
//! The default acceleration of the ship when powered
static const float DEFAULT_ACCELERATION = 50.0f;

/**
* The application class is the main body of the program. It will
* create an instance of the graphics engine and execute the
* Update/Render cycle.
*
*/

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
	void SendCollision(Ship* ship);
	void ProcessWelcomePackage();
	bool SendInitialPosition();

	//===== GETTER =====//
	void Render();
	bool checkCollisions(Ship* ship);
	void playerControl(const float dt);

	void welcome(RakNet::BitStream &bs);
	void newPlayer(RakNet::BitStream &bs);
	void removePlayer(RakNet::BitStream &bs);
	void movementUpdate(RakNet::BitStream &bs);
	void collisionUpdate(RakNet::BitStream &bs);

	void sendData();

	Missile* fetchMissile();

	// Lab 13 Task 1 : add variables for local missle


	// Lab 13 Task 8 : add variables to handle networked missiles


	// Lab 13
	void CreateMissile(float x, float y, float w, int id);
	bool RemoveMissile(float x, float y, float w, int id);
private:
	//Int
	unsigned timer_;

	//Class Variables Or Vector
	HGE* hge_; //!< Instance of the internal graphics engine
	std::vector<Ship*> ShipList; //!< List of all the ships in the universe
	//std::vector<Missile*> missileList;
	std::vector<CProjectile*> projectileList;
	//Missile* mymissile;
	//bool have_Missile;
	RakPeerInterface* rakpeer_;
};

#endif