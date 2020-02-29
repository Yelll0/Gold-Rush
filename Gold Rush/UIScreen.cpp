#include "stdafx.h"

UIScreen::UIScreen(class Game* game, class Controller* controller) : mGame(game), mController(controller)
{
}

UIScreen::~UIScreen()
{
}

void UIScreen::Update(float deltaTime)
{
	mController->Update();
}

