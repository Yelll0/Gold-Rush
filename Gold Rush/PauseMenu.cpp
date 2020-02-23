#include "stdafx.h"

PauseMenu::PauseMenu(class Game* game, class Controller* controller) : mGame(game), mController(controller)
{
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::Update(float deltaTime)
{
	mController->Update();
}
