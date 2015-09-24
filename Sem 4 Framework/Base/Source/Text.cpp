#include "Text.h"

Color Text::defaultColor = Color(0, 0, 0);
Color Text::selectedColor = Color(1, 1, 1);

Text::Text():
	active(true),
	pos(0),
	scale(0),
	text(""),
	color(defaultColor)
{
}

Text::Text(Vector3 pos, Vector3 CB_TopLeft, Vector3 CB_BottomRight, std::string text, Vector3 scale, Color color)
{
	active = true;
	this->pos = pos;
	this->CB_TopLeft = CB_TopLeft;
	this->CB_BottomRight = CB_BottomRight;
	this->text = text;
	this->scale = scale;
	this->color = color;
	this->defaultColor = color;
}


Text::~Text()
{
}

void Text::setPos(Vector3 pos)
{
	this->pos = pos;
}

void Text::setScale(Vector3 scale)
{
	this->scale = scale;
}

void Text::setText(std::string text)
{
	this->text = text;
}

void Text::setCB_TopLeft(Vector3 CB_TopLeft)
{
	this->CB_TopLeft = CB_TopLeft;
}

void Text::setCB_BottomRight(Vector3 CB_BottomRight)
{
	this->CB_BottomRight = CB_BottomRight;
}

void Text::set_TextSelected()
{
	this->color = selectedColor;
}

void Text::set_TextNotSelected()
{
	this->color = defaultColor;
}


bool Text::getActive()
{
	return active;
}

Vector3 Text::getPos()
{
	return pos;
}

Vector3 Text::getScale()
{
	return scale;
}
std::string Text::getText()
{
	return text;
}

Color Text::getColor()
{
	return color;
}

Vector3 Text::getCB_TopLeft()
{
	return CB_TopLeft;
}

Vector3 Text::getCB_BottomRight()
{
	return CB_BottomRight;
}
