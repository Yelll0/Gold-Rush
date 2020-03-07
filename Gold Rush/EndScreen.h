#pragma once

#include "stdafx.h"

class EndScreen : public UIScreen
{
public:
	EndScreen(class Game* game, class Controller* controller, class Player* player);
	~EndScreen();

private:
	class Player* mPlayer;
};
