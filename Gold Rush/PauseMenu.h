#pragma once

#include "stdafx.h"

class PauseMenu: public UIScreen
{
public:
	PauseMenu(class Game* game, class Controller* controller);
	~PauseMenu();

	void Update(float deltaTime) override;
};