#pragma once

#include "stdafx.h"

class Game
{
public:
	// Constructor and destructor
	Game();
	~Game();
	// Game loop functions
	int Init();
	void RunLoop();
	void Quit();
	// Get and set functions
	int GetState() { return mGameState; }
	void SetState( int nState ) { mGameState = nState; }
private:
	// Game loop helper functions
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	// Member variables
	int mGameState; // (1 = Active, 0 = Paused, -1 = Quit)
	SDL_Window* mWindow;
};