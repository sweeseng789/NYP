#pragma once
#include "Goodies.h"
#include "TreasureChest.h"

typedef int GoodiesID;
#define TREASURECHEST 0;

class CGoodieFactory
{
public:
	CGoodieFactory();
	~CGoodieFactory();

	CGoodies* Create(GoodiesID);
};

