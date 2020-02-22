#pragma once

#include "stdafx.h"

class PauseMenu
{
public:
	PauseMenu();
	~PauseMenu();

	void ProcessInput();
	void Update(float deltaTime);

private:
	class Game* mGame;
};

