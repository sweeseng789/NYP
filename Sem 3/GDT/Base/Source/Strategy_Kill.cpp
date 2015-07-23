#include "Strategy_Kill.h"
#include <iostream>
using namespace std;
CStrategy_Kill::CStrategy_Kill()
{
}
CStrategy_Kill::~CStrategy_Kill()
{
}
void CStrategy_Kill::Update(void)
{
	theEnemyPosition.x = theEnemyPosition.x + (theDestination.x -
		theEnemyPosition.x > 0 ? 5 : -5);
	//theEnemyPosition.y = theEnemyPosition.y + (theDestination.y - theEnemyPosition.y > 0 ? 5 : -5 );
}
void CStrategy_Kill::SetDestination(const float x, const float y)
{
	theDestination.x = x;
	theDestination.y = y;
}
void CStrategy_Kill::GetEnemyPosition(float& x, float& y)
{
	x = theEnemyPosition.x;
	y = theEnemyPosition.y;
}
void CStrategy_Kill::SetEnemyPosition(const float x, const float y)
{
	theEnemyPosition.x = x;
	theEnemyPosition.y = y;
}