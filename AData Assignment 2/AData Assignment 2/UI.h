#pragma once
class CUI
{
public:
	enum MENU_OPTION
	{
		ADD,
		DELETE,
		SEARCH,
		SORT,
		PRINT,
		EXIT,
		VALID,
		INVALID,
		MENU_LAST
	};

	CUI();
	CUI(MENU_OPTION type);
	~CUI();

	MENU_OPTION getType();

private:
	MENU_OPTION type;
};

