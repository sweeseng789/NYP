#include "UI.h"



CUI::CUI()
{
}

CUI::CUI(MENU_OPTION type)
{
	this->type = type;
}


CUI::~CUI()
{
}

CUI::MENU_OPTION CUI::getType()
{
	return type;
}
