#include "stdafx.h"

PauseMenu::PauseMenu(class Game* game, class Controller* controller) : UIScreen(game, controller)
{
	UIScreen(game, controller);
	mButtons.emplace(mButtons.end(), new Button(this, 3, Vector2(-78.f, 0.f), Vector2(72.f, 72.f), [this]() { mGame->SetState(1); }));
	mButtons.emplace(mButtons.end(), new Button(this, 4, Vector2(0.f, 0.f), Vector2(72.f, 72.f), [this]() { mGame->ToggleSound(); }));
	mButtons.emplace(mButtons.end(), new Button(this, 6, Vector2(78.f, 0.f), Vector2(72.f, 72.f), [this]() { mGame->SetState(-1); }));
}

PauseMenu::~PauseMenu()
{
}
