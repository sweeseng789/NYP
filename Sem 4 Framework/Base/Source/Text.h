#pragma once
#include "Vector3.h"
#include "Vertex.h"
#include <string>

class Text
{
public:
	enum MENU_TYPE
	{
		MENU_MAINMENU,
		MENU_OPTION
	};

	Text();
	~Text();


	//Setter
	void setPos(Vector3 pos);
	void setScale(Vector3 scale);
	void setText(std::string text);
	void setCB_TopLeft(Vector3 CB_TopLeft);
	void setCB_BottomRight(Vector3 CB_BottomRight);
	void set_TextSelected();
	void set_TextNotSelected();
	void setType(MENU_TYPE type);


	//Getter
	bool getActive();
	Vector3 getPos();
	Vector3 getScale();
	std::string getText();
	Color getColor();
	Vector3 getCB_TopLeft();
	Vector3 getCB_BottomRight();
	MENU_TYPE getType();

private:
	bool active;
	Vector3 pos;
	Vector3 scale;
	Vector3 CB_TopLeft;
	Vector3 CB_BottomRight;
	std::string text;
	Color color;
	MENU_TYPE type;

	static Color defaultColor;
	static Color selectedColor;
};

