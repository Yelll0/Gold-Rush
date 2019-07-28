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
	int GetState() { return mState; }
	void SetState( int nState ) { mState = nState; }
private:
	// Game loop helper functions
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();
	// Other member variables
	int mState; // (1 = Active, 0 = Paused, -1 = Quit)
	class Player* mPlayer;
	SDL_Window* mWindow;
};