#pragma once

#include "stdafx.h"

enum ButtonState 
{
	ENone,
	EPressed,
	EReleased,
	EHeld
};

class Controller
{
public:
	// Constructor and destructor
	Controller(class Game* game);
	~Controller();

	bool Init();
	void Shutdown();

	void Update();

	// Keyboard input system
	bool GetKeyValue(SDL_Scancode keyCode) const { return mCurrentState[keyCode] == 1; };
	
	ButtonState GetKeyState(SDL_Scancode keyCode) const;

	void SetUI(class UIScreen* ui) { mUI = ui; }
	void SetPlayer(class Player* player) { mPlayer = player; }

private:
	class Game* mGame;
	class Player* mPlayer;
	class UIScreen* mUI;
	const Uint8* mCurrentState;
	Uint8 mPreviousState[SDL_NUM_SCANCODES];
};