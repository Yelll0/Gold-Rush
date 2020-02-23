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
	void SetState(int state) { mState = state; }
	class World* GetWorld() { return mWorld; }

private:
	// Game loop helper functions
	void ProcessInput();
	void UpdateGame();
	void GenerateOutput();

	// Other member variables
	int mState; // (1 = Active, 0 = Paused, -1 = Quit)
	bool mMute;
	Uint32 mTickCount;
	SDL_Window* mWindow;
	SDL_GLContext mContext;
	class Controller* mController;
	class Player* mPlayer;
	class Renderer* mRenderer;
	class World* mWorld;
	class PauseMenu* mPauseMenu;
};