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
	float GetBlockDamage(int x, int y) const { return mDamageMap[x][y]; }
	void SetBlock(int x, int y, int block) { mMap[x][y] = block; }
	void DamageBlock(int x, int y, float damage) { mDamageMap[x][y] += damage; }

private:
	int mMap[210][542];
	float mDamageMap[210][542];
	class Game* mGame;
	class Player* mPlayer;
	float mBlockScale;
};

// TODO: Convert coordinates to blocks instead of pixels