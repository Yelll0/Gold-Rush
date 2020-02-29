#include "stdafx.h"

UIScreen::UIScreen(class Game* game, class Controller* controller)
{
}

UIScreen::~UIScreen()
{
}

void UIScreen::Update(float deltaTime)
{
	mController->Update();
}

