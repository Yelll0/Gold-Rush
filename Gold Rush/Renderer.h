#pragma once

#include "stdafx.h"

class Renderer
{
public: 
	// Constructor and destructor
	Renderer(class Game* game);
	~Renderer();

private:
	// Owner game
	class Game* mGame;
};