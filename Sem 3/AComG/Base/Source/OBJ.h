#ifndef RAIN_H
#define RAIN_H

#include "Mesh.h"
#include "Vector3.h"
#include "Vertex.h"

class COBJ
{
public:
	COBJ(Vector3 pos, float speed, int type);
	~COBJ(void);

	void update(double dt);

	Vector3 getPos();

	int type;
	//1 = Rain
	//2 = Tree
private:
	Vector3 pos;
	float speed;
	float defaultY;
};

#endif