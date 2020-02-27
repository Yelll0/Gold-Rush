#pragma once

#include "stdafx.h"

class PauseMenu
{
public:
	PauseMenu(class Game* game, class Controller* controller);
	~PauseMenu();

	void Update(float deltaTime);

	class Button* GetButton(int i) const { return mButtons[i]; }

private:
	class Game* mGame;
	class Controller* mController;
	class Button* mButtons[3];
};