#pragma once
class CColour
{
public:
	CColour(int, int, int);
	~CColour();

	int getRed();
	int getGreen();
	int getBlue();

	int number;
private:
	int red, green, blue;
};

