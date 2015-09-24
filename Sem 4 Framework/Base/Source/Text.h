#pragma once
#include "Vector3.h"
#include "Vertex.h"
#include <string>

class Text
{
public:
	Text();
	Text(Vector3 pos, Vector3 CB_TopLeft, Vector3 CB_BottomRight, std::string text, Vector3 scale = Vector3(3.5, 3.5, 0), Color color = Color(0, 0, 0));
	~Text();


	//Setter
	void setPos(Vector3 pos);
	void setScale(Vector3 scale);
	void setText(std::string text);
	void setCB_TopLeft(Vector3 CB_TopLeft);
	void setCB_BottomRight(Vector3 CB_BottomRight);
	void set_TextSelected();
	void set_TextNotSelected();


	//Getter
	bool getActive();
	Vector3 getPos();
	Vector3 getScale();
	std::string getText();
	Color getColor();
	Vector3 getCB_TopLeft();
	Vector3 getCB_BottomRight();

private:
	bool active;
	Vector3 pos;
	Vector3 scale;
	Vector3 CB_TopLeft;
	Vector3 CB_BottomRight;
	std::string text;
	Color color;

	static Color defaultColor;
	static Color selectedColor;
};

