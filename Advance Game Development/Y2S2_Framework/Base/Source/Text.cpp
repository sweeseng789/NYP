#include "Text.h"

Color CText::OnClick = Color(1, 0, 0);
Color CText::NotOnClick = Color(1 , 0.6, 0.2);


CText::CText()
{
	this->color = NotOnClick;
}


CText::~CText()
{
}

void CText::setPos(Vector3 pos)
{
	this->pos = pos;
}

void CText::setScale(Vector3 scale)
{
	this->scale = scale;
}

void CText::setGamestate(int gamestate)
{
	this->gamestate = gamestate;
}

void CText::setText(std::string text)
{
	this->text = text;
}

void CText::setColorToOnClick()
{
	this->color = OnClick;
}

void CText::setColorToNotOnClick()
{
	this->color = NotOnClick;
}

Vector3 CText::getPos()
{
	return pos;
}

Vector3 CText::getScale()
{
	return scale;
}

int CText::getGameState()
{
	return gamestate;
}

std::string CText::getText()
{
	return text;
}

Color CText::getColor()
{
	return color;
}
