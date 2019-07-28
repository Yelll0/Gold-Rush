#pragma once

#include "Game.h"

Game::Game()
{
	mState = 1;
}

Game::~Game()
{

}
// TODO: Render frames in GenerateOutput()
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

	// Create SDL window
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

	// Create OpenGL context and initialize GLEW
	mContext = SDL_GL_CreateContext(mWindow);
	glewExperimental = true;
	if (glewInit() != GLEW_OK) 
	{
		SDL_Log("Failed to initialize GLEW.");
		return 1;
	}
	glGetError();
	return 0;
}

void Game::RunLoop()
{
	while (mState == 1)
	{
		ProcessInput();
		UpdateGame();
		GenerateOutput();
	}
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

}

void Game::UpdateGame()
{

}

void Game::GenerateOutput()
{

}