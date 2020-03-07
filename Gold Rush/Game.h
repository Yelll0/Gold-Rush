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
	void RunMenuLoop();
	void InitGame(int seed);
	void RunLoop();
	void QuitGame();
	void Quit();

	// Getters and setters
	int GetState() const { return mState; }
	bool GetMute() const { return mMute; }
	void SetState(int state) { mState = state; }
	void ToggleSound() { mMute = !mMute; }
	class World* GetWorld() const { return mWorld; }
	class UIScreen* GetUI() const { return mActiveUI; }
	class HUD* GetHUD() const { return mHUD; }

private:
	// Game loop helper functions
	void ProcessInput();
	void UpdateGame();
	void UpdateGameMenu();
	void GenerateOutput();

	// Other member variables
	int mState; // (2 = Finished, 1 = Active, 0 = Paused, -1 = Main menu, -2 = Quit)
	bool mMute; 
	Uint32 mTickCount;
	SDL_Window* mWindow;
	SDL_GLContext mContext;
	class Controller* mController;
	class Player* mPlayer;
	class Renderer* mRenderer;
	class World* mWorld;
	class HUD* mHUD;
	class UIScreen* mActiveUI;
	double mDeltaTime;
};