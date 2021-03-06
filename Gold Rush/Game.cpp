#include "stdafx.h"

Game::Game() 
	: mState(-1), 
	mTickCount(0), 
	mMute(false),
	mWindow(nullptr), 
	mContext(NULL), 
	mController(new Controller(this)),
	mPlayer(nullptr),
	mWorld(nullptr),
	mRenderer(new Renderer(this, mPlayer)),
	mHUD(nullptr),
	mActiveUI(new MainMenu(this, mController, mRenderer))
{
}

Game::~Game()
{
}

int Game::Init()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL unable to initialize. SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	// Request OpenGL attributes
	// Use core OpenGL profile
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	// Version 3.3
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// 8-bit color buffer
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	// Double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// Hardware acceleration
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	// Create the window
	mWindow = SDL_CreateWindow(
		"Gold Rush",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		576, // Sprites are 24*24 pixels, and are scaled up *3
		576,
		SDL_WINDOW_OPENGL
		);
	if (!mWindow) 
	{
		std::cout << "Unable to create window: "  << SDL_GetError() << std::endl;
		return 1;
	}

	// Initialize controller
	if (!mController->Init())
	{
		SDL_Log("Unable to initialize controller.");
		return 1;
	}

	// Create OpenGL context and initialize GLEW
	mContext = SDL_GL_CreateContext(mWindow);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) 
	{
		SDL_Log("Unable to initialize GLEW.");
		return 1;
	}
	glGetError();

	// Initialize renderer
	if (!mRenderer->Init())
	{
		SDL_Log("Unable to initialize renderer.");
		return 1;
	}

	return 0;
}

void Game::RunMenuLoop()
{
	while (mState == -1)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
		// Update tick count
		mTickCount = SDL_GetTicks();
	}
	// Quit game
	if (mState == -2) { Quit(); }
}

void Game::InitGame(int seed)
{
	// Create everything
	mState = 1;
	mPlayer = new Player(this, mController);
	mRenderer->SetPlayer(mPlayer);
	mController->SetPlayer(mPlayer);
	mWorld = new World(this, mPlayer, seed);
	mRenderer->SetWorld(mWorld);
	delete mActiveUI;
	mHUD = new HUD(this, mController, mPlayer);
	mActiveUI = mHUD;
}

void Game::RunLoop()
{
	while (mState > -2)
	{
		// Main menu
		while (mState == -1)
		{
			RunMenuLoop();
		}
		// Run game
		while (mState > -1)
		{
			ProcessInput();
			UpdateGame();
			GenerateOutput();
			// Update tick count
			mTickCount = SDL_GetTicks();
		}
		// Quit game
		if (mState == -1) { QuitGame(); }
	}
	// Quit application
	if (mState == -2) 
	{ 
		Quit();
		return;
	}
}

void Game::QuitGame()
{
	delete mPlayer;
	delete mWorld;
	mActiveUI = nullptr;
	delete mHUD;
	mActiveUI = new MainMenu(this, mController, mRenderer);
}

void Game::Quit()
{
	// Quit SDL
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
	TTF_Quit();
	return;
}

void Game::ProcessInput()
{
	mController->Update();
}

void Game::UpdateGame()
{
	// Main menu
	if (mState < 0)
	{
		// Limit FPS to 62.5
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + 16));
		// Calculate delta time
		double mDeltaTime = (SDL_GetTicks() - mTickCount) / 1000.0f;
		mController->SetUI(mActiveUI);
		// Limit delta time value
		if (mDeltaTime > 0.05)
		{
			mDeltaTime = 0.05;
		}
		mActiveUI->Update(mDeltaTime);
		return;
	}
	// Create pause menu UI
	if (!mState)
	{
		mActiveUI = new PauseMenu(this, mController);
		mController->SetUI(mActiveUI);
	}
	// Pause game if paused
	while (!mState)
	{
		// Limit FPS to 62.5
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + 16));
		// Calculate delta time
		mDeltaTime = (SDL_GetTicks() - mTickCount) / 1000.0f;
		// Update tick count
		mTickCount = SDL_GetTicks();
		// Limit delta time value
		if (mDeltaTime > 0.05)
		{
			mDeltaTime = 0.05;
		}

		mActiveUI->Update(mDeltaTime);
		GenerateOutput();
		if (mState) 
		{ 
			delete mActiveUI; 
			mController->SetUI(nullptr);
		}
	}

	// Create end screen UI
	if (mState == 2)
	{
		mActiveUI = new EndScreen(this, mController, mPlayer);
		mController->SetUI(mActiveUI);
	}
	// End screen
	while (mState == 2)
	{
		// Limit FPS to 62.5
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + 16));
		// Calculate delta time
		mDeltaTime = (SDL_GetTicks() - mTickCount) / 1000.0f;
		// Update tick count
		mTickCount = SDL_GetTicks();
		// Limit delta time value
		if (mDeltaTime > 0.05)
		{
			mDeltaTime = 0.05;
		}

		mActiveUI->Update(mDeltaTime);
		GenerateOutput();
		if (mState < 2)
		{
			delete mActiveUI;
			mController->SetUI(nullptr);
		}
	}

	mActiveUI = mHUD;
	mController->SetUI(mActiveUI);
	// Limit FPS to 62.5 
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + 16));
	// Calculate delta time
	double mDeltaTime = (SDL_GetTicks() - mTickCount) / 1000.0f;
	// Limit delta time value
	if (mDeltaTime > 0.05)
	{
		mDeltaTime = 0.05;
	}

	mActiveUI->Update(mDeltaTime);
	mPlayer->Update(mDeltaTime);
}

void Game::UpdateGameMenu()
{

}

void Game::GenerateOutput()
{
	// Set clear color to grey
	glClearColor(0.f, 0.f, 0.f, 1.0f);
	// Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	// Recalculate delta time
	mDeltaTime = (SDL_GetTicks() - mTickCount) / 1000.f;
	// Draw scene
	mRenderer->Draw(mDeltaTime);

	// Swap buffers
	SDL_GL_SwapWindow(mWindow);
}