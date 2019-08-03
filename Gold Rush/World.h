#pragma once

#include "stdafx.h"

class World
{
public:
	// Constructor and destructor
	World(class Game* game);
	~World();

private:
	class Game* mGame;

};

