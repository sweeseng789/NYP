#ifndef RAIN_H
#define RAIN_H

#include <vector>
#include "Mesh.h"
#include "Vector3.h"
#include "Vertex.h"
#include "LoadHmap.h"

using std::vector;

class COBJ
{
public:
	COBJ(Vector3 pos, float speed, int type);
	~COBJ(void);

	void update(double dt);
	void update2(double dt, vector<unsigned char> m_heightMap);

	Vector3 getPos();

	float tempY;

	int type;
	//1 = Rain
	//2 = Tree
private:
	Vector3 pos;
	float speed;
	float defaultY;
};

#endif