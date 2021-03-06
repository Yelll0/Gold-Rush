#pragma once

#include "stdafx.h"

class MainMenu :
	public UIScreen
{
public:
	MainMenu(class Game* game, class Controller* controller, class Renderer* renderer);
	~MainMenu();

	void Update(float deltaTime) override;

	int GetSeed() const { return mSeed; }

private:
	class Renderer* mRenderer;
	int mSeed;
};

