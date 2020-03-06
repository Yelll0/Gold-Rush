#include "stdafx.h"

MainMenu::MainMenu(class Game* game, class Controller* controller, class Renderer* renderer) : UIScreen(game, controller),
	mRenderer(renderer), mSeed(50)
{
	mButtons.emplace_back(new Button(this, 3, Vector2(0.f, 0.f), Vector2(72.f, 72.f), NULL));
}

MainMenu::~MainMenu()
{
}

void MainMenu::Update(float deltaTime)
{
	UIScreen::Update(deltaTime);
}