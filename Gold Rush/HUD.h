#pragma once

#include "stdafx.h"

class HUD : public UIScreen
{
public:
	HUD(class Game* game, class Controller* controller, class Player* player);
	~HUD();

private:
	class Player* mPlayer;
};

