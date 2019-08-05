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

	// Getters and setters
	int GetState() { return mState; }
	void SetState(int nState) { mState = nState; }

private:
	// Game loop helper functions
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	// Other member variables
	int mState; // (1 = Active, 0 = Paused, -1 = Quit)
	Uint32 mTickCount;
	SDL_Window* mWindow;
	SDL_GLContext mContext;
	class Controller* mController;
	class Player* mPlayer;
	class Renderer* mRenderer;
};