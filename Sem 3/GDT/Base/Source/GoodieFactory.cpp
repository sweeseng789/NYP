#include "GoodieFactory.h"
#include <stdlib.h>



CGoodieFactory::CGoodieFactory()
{
}


CGoodieFactory::~CGoodieFactory()
{
}

CGoodies* CGoodieFactory::Create(GoodiesID id)
{
	CGoodies* theNewGoodies = NULL;
	switch (id)
	{
	case TREASURECHEST:
		theNewGoodies = new CTreasureChest;
		break;
	default:
		break;
	}

	return theNewGoodies;
}
