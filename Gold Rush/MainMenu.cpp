#include "stdafx.h"

MainMenu::MainMenu(class Game* game, class Controller* controller, class Renderer* renderer) : UIScreen(game, controller),
	mRenderer(renderer)
{
	mButtons.emplace_back(new Button(this, 100, Vector2(0.f, 0.f), Vector2(0.f, 0.f), NULL));
	mButtons.emplace_back(new Button(this, 3, Vector2(0.f, 0.f), Vector2(0.f, 0.f), NULL));
}

MainMenu::~MainMenu()
{
}

void MainMenu::Update(float deltaTime)
{
	UIScreen::Update(deltaTime);

}