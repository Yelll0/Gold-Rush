#include "stdafx.h"

EndScreen::EndScreen(class Game* game, class Controller* controller, class Player* player) : UIScreen(game, controller),
	mPlayer(player)
{
	mButtons.emplace(mButtons.end(), new Button(this, 6, Vector2(0.f, 0.f), Vector2(72.f, 72.f), [this]() { mGame->SetState(-1); }));
}

EndScreen::~EndScreen()
{
}