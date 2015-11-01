#pragma once
#include <string>
#include "Vertex.h"
#include "Vector3.h"

class CText
{
public:
	CText();
	~CText();


	void setPos(Vector3 pos);
	void setScale(Vector3 scale);
	void setGamestate(int gamestate);
	void setText(std::string text);
	void setColorToOnClick();
	void setColorToNotOnClick();

	Vector3 getPos();
	Vector3 getScale();
	int getGameState();
	std::string getText();
	Color getColor();

private:
	Vector3 pos;
	Vector3 scale;
	Color color;
	int gamestate;
	std::string text;

	static Color OnClick;
	static Color NotOnClick;
};