#pragma once

#include "stdafx.h"

class UIScreen
{
public:
	UIScreen(class Game* game);
	virtual ~UIScreen();

	virtual void Update(float deltaTime);
	virtual void ProcessInput(const uint8_t* keys);
	virtual void HandleKeyPress(int key);
	enum UIState { EActive, EClosing };
	void Close() { mState = EClosing; }
	UIState GetState() const { return mState; }

protected:
	
	class Game* mGame;
	UIState mState;
};