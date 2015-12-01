#ifndef _APPLICATION_H_
#define _APPLICATION_H_

#include "ship.h"
#include "Asteroid.h"
#include <vector>

class HGE;

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
	HGE* hge_; //!< Instance of the internal graphics engine
	typedef std::vector<Ship*> ShipList;  //!< A list of ships
	typedef std::vector<Asteroid*> AList;  //Asteroid
	ShipList ships_; //!< List of all the ships in the universe
	AList Asteroid_;
	
	bool Init();
	static bool Loop();
	void Shutdown();

public:
	Application();
	~Application() throw();

	void Start();
	bool Update();
	void Render();
};

#endif