#include "stdafx.h"

UIScreen::UIScreen(class Game* game) : mGame(game), mState(EActive)
{
}

UIScreen::~UIScreen()
{
}

void UIScreen::Update(float deltaTime)
{
}

void UIScreen::ProcessInput(const uint8_t* keys)
{
}

void UIScreen::HandleKeyPress(int key)
{
}
