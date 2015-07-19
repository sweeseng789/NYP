#ifndef ENEMY_H
#define ENEMY_H

#include <iostream>
#include <vector>
#include "Camera3.h"
#include "MyMath.h"
#include "Vector3.h"

using std::cin;
using std::cout;
using std::endl;
using std::vector;

class CEnemy
{
public:
	CEnemy(void);
	~CEnemy(void);

	//Getter
	Vector3 getEnemyPos();
	bool getActive();
	float getScale();
	

	//Setter
	void update(float dt);
	void setPos(Vector3 pos);

	//Bool
	bool active;
	Vector3 vel;
private:
	//Int
	int EnemyHealth;

	//Float
	float scale;

	//Vector3
	Vector3 pos;
};

#endif