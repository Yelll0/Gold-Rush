#include "stdafx.h"

Controller::Controller(class Game* game)
	: mGame(game)
{
}


Controller::~Controller()
{
}

bool Controller::Init()
{
	mCurrentState = SDL_GetKeyboardState(NULL);
	memset(mPreviousState, 0, SDL_NUM_SCANCODES);
	return true;
}

void Controller::Shutdown()
{
}

void Controller::Update()
{
	memcpy(mPreviousState, mCurrentState, SDL_NUM_SCANCODES);
	SDL_Event event;
	int x, y;
	SDL_GetMouseState(&x, &y);
	// Convert to (0, 0) center coordinates
	Vector2 mousePos(x, y);
	mousePos.x -= 288.f;
	mousePos.y -= 288.f;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		// If we get an SDL_QUIT event, end loop
		case SDL_QUIT:
			mGame->SetState(-1);
			break;
		// On click, get position of mouse
		case SDL_MOUSEBUTTONDOWN:
			for (int j = 0; j < mUI->GetNumButtons(); j++)
			{
				if (mUI->GetButton(j)->ContainsPoint(mousePos))
				{
					if (mUI->GetButton(j)->mFunction) { mUI->GetButton(j)->mFunction(); }
				}
			}
		}
	}
	// Pause/unpause game when escape is pressed
	if (GetKeyState(SDL_SCANCODE_ESCAPE) == EPressed)
	{
		if (mGame->GetState())
		{
			mGame->SetState(0);
		}
		else
		{
			mGame->SetState(1);
		}
	}
}

ButtonState Controller::GetKeyState(SDL_Scancode keyCode) const
{
	if (mPreviousState[keyCode] == 0)
	{
		if (mCurrentState[keyCode] == 0) { return ENone; }
		else { return EPressed; }
	}
	else
	{
		if (mCurrentState[keyCode] == 0) { return EReleased; }
		else { return EHeld; }
	}
}