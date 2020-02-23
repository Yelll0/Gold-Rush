#pragma once

#include "stdafx.h"

class PauseMenu
{
public:
	PauseMenu(class Game* game, class Controller* controller);
	~PauseMenu();

	void Update(float deltaTime);

private:
	class Game* mGame;
	class Controller* mController;
};

