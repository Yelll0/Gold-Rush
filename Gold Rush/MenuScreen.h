#pragma once

#include "stdafx.h"

class MenuScreen
{
public:	
	MenuScreen();
	~MenuScreen();

private:
	std::vector<class Button*> mButtons;
};

