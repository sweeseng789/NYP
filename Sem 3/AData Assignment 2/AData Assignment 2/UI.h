#pragma once
#include <iostream>
class CUI
{
public:
	enum MENU_OPTION
	{
		VALID,
		INVALID,
		MENU_LAST
	};

	CUI();
	CUI(MENU_OPTION type);
	~CUI();

	static void renderMainMenu();
	static void renderErrorMessage();
	static void renderRecordIsFull();
	static void renderRecordIsEmpty();
	static void renderNoDataFound();

	MENU_OPTION getType();
private:
	MENU_OPTION type;
};

