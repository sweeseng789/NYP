#include "Text.h"

Color CText::OnClick = Color(1, 0, 0);
Color CText::NotOnClick = Color(0.5, 0.5, 0.5);


CText::CText(Vector3 pos)
{
	this->color = NotOnClick;
	this->pos = pos;
}


CText::~CText()
{
}
