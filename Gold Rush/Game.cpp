#include "Game.h"

Game::Game() 
	: mState(1), 
	mTickCount(0), 
	mWindow(nullptr), 
	mContext(NULL), 
	mController(new Controller(this)),
	mPlayer(new Player(this, mController)),
	mWorld(new World(this, mPlayer)),
	mRenderer(new Renderer(this, mPlayer, mWorld))
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
		576, // Sprites are 16*16 pixels, and are scaled up *4
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

void Game::RunLoop()
{
	// Run game
	while (mState == 1)
	{
		ProcessInput();
		// Pause game
		while (mState == 0) { ProcessInput(); }
		UpdateGame();
		GenerateOutput();
	}
	// Quit game
	if (mState == -1) { Quit(); }
}

void Game::Quit()
{
	// Quit SDL
	SDL_GL_DeleteContext(mContext);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
	return;
}

void Game::ProcessInput()
{
	mController->Update();
}

void Game::UpdateGame()
{
	// Limit FPS to 60
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTickCount + 16));
	// Calculate delta time
	double deltaTime = (SDL_GetTicks() - mTickCount) / 1000.0f;
	// Update tick count
	mTickCount = SDL_GetTicks();
	// Limit delta time value
	if (deltaTime > 0.05)
	{
		deltaTime = 0.05;
	}

	mPlayer->Update(deltaTime);
}

void Game::GenerateOutput()
{
	// Set clear color to grey
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	// Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);

	// Draw scene
	mRenderer->Draw();

	// Swap buffers
	SDL_GL_SwapWindow(mWindow);
}