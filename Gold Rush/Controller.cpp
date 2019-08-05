#include "Controller.h"



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

void Controller::Update()
{
	memcpy(mPreviousState, mCurrentState, SDL_NUM_SCANCODES);
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		// If we get an SDL_QUIT event, end loop
		case SDL_QUIT:
			mGame->SetState(-1);
			break;
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

