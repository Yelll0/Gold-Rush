#pragma once

#include "Game.h"

Game::Game()
{
	mState = 1;
}

Game::~Game()
{

}

int Game::Init()
{
	// Initialize SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		std::cout << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
		return 1;
	}
	// Create the window
	mWindow = SDL_CreateWindow(
		"Gold Rush",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		576, // Sprites are 16*16 pixels, and are scaled up *4
		576,
		SDL_WINDOW_OPENGL
		);
	if (!mWindow) {
		std::cout << "Could not create window: "  << SDL_GetError() << std::endl;
		return 1;
	}
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
	return;
}

void Game::Quit()
{
	// Quit SDL
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