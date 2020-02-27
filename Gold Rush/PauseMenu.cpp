#include "stdafx.h"

PauseMenu::PauseMenu(class Game* game, class Controller* controller) : mGame(game), mController(controller)
{
	mButtons[0] = (new Button(this, 3, Vector2(-78.f, 0.f), Vector2(72.f, 72.f), [this]() { mGame->SetState(1); }));
	mButtons[1] = (new Button(this, 4, Vector2(0.f, 0.f), Vector2(72.f, 72.f), [this]() { mGame->ToggleSound(); }));
	mButtons[2] = (new Button(this, 6, Vector2(78.f, 0.f), Vector2(72.f, 72.f), [this]() { mGame->SetState(-1); }));
}

PauseMenu::~PauseMenu()
{
}

void PauseMenu::Update(float deltaTime)
{
	mController->Update();

}
