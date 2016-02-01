#pragma once
#include <hge.h>
#include <hgerect.h>
#include <memory>
#include <vector>

class hgeSprite;
class hgeRect;
class Ship;
class Laser;

class CAsteroid
{
public:
	enum TYPE
	{
		s_BIG,
		s_SMALL,
	};

	CAsteroid();
	CAsteroid(float x, float y, float w, bool smallAsteroid = false);
	~CAsteroid();

	void Update(float dt);
	bool UpdateShip(std::vector<Ship*> &shipList, float dt);
	bool UpdateLaser(std::vector<Laser*> &laserList);
	bool hasCollided(Ship* ship);
	bool hasCollided(Laser* laser);

	void Render();
	void UpdateLoc(float x, float y, float w)
	{
		x_ = x;
		y_ = y;
		w_ = w;
	}

	float GetX() const
	{
		return x_;
	}

	float GetY() const
	{
		return y_;
	}

	float GetW() const
	{
		return w_;
	}

	float GetVelocityX() { return velocity_x_; }
	float GetVelocityY() { return velocity_y_; }

	void SetVelocityX(float velocity) { velocity_x_ = velocity; }
	void SetVelocityY(float velocity) { velocity_y_ = velocity; }

	void setActive(bool active) { this->active = active; }
	bool getActive() { return active; }

	bool isSmall()
	{
		if (type == s_SMALL)
			return true;
		return false;
	}

private:
	HTEXTURE tex_; //!< Handle to the sprite's texture
	std::auto_ptr<hgeSprite> sprite_; //!< The sprite used to display the ship
	float x_; //!< The x-ordinate of the ship
	float y_; //!< The y-ordinate of the ship
	float w_; //!< The angular position of the ship
	float velocity_x_; //!< The resolved velocity of the ship along the x-axis
	float velocity_y_; //!< The resolved velocity of the ship along the y-axis
	hgeRect collidebox;
	bool active;
	float angular_velocity;
	TYPE type;
};