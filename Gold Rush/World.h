#pragma once

#include "stdafx.h"

class World
{
public:
	World(class Game* game, class Player* player);
	~World();

	// Generate the world
	void Generate();

	// Getters and setters
	int GetBlock(int x, int y) const { return mMap[x][y]; }
	void SetBlock(int x, int y, int block) { mMap[x][y] = block; }
	int mMap[210][542];

private:
	class Game* mGame;
	class Player* mPlayer;
	float mBlockScale;
};

// TODO: Convert coordinates to blocks instead of pixels