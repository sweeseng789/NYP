#include "Colour.h"

CColour::CColour(int red, int green, int blue)
{
	this->red = red;
	this->green = green;
	this->blue = blue;
}

CColour::~CColour()
{
}

int CColour::getRed()
{
	return red;
}

int CColour::getGreen()
{
	return green;
}

int CColour::getBlue()
{
	return blue;
}
