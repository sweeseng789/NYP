#ifndef _SHIP_H_
#define _SHIP_H_

#include <hge.h>
#include <memory>
#include <hgefont.h>
#include <string>

class hgeSprite;

/**
* The Ship class represents a single spaceship floating in space. It obeys
* 2D physics in terms of displacement, velocity and acceleration, as well
* as angular position and displacement. The size of the current art is
* 128*128 pixels
*/

class Ship
{
	HTEXTURE tex_; //!< Handle to the sprite's texture
	std::auto_ptr<hgeSprite> sprite_; //!< The sprite used to display the ship
	float x_; //!< The x-ordinate of the ship
	float y_; //!< The y-ordinate of the ship
	float w_; //!< The angular position of the ship
	float velocity_x_; //!< The resolved velocity of the ship along the x-axis
	float velocity_y_; //!< The resolved velocity of the ship along the y-axis

public:
	float angular_velocity;
	Ship(char* filename, char* Shipname);
	~Ship();
	void Update(float timedelta);
	void Render();
	void Accelerate(float acceleration, float timedelta);
	std::auto_ptr<hgeFont> font_;
	std::string ShipName;
};

#endif