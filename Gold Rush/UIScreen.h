#pragma once

#include "stdafx.h"

class UIScreen
{
public:
	UIScreen(class Game* game);
	virtual ~UIScreen();

	virtual void Update(float deltaTime);
	virtual void Draw(class Shader* shader);
	virtual void ProcessInput(const uint8_t* keys);

private:
	virtual void HandleKeyPress(int key);
	class Game* mGame;
};

