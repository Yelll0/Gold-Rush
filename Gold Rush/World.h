#pragma once

#include "stdafx.h"

class World
{
public:
	World(class Game* game, class Player* player, int seed);
	~World();

	// Generate the world
	void Generate();

	// Getters and setters
	int GetBlock(int x, int y) const { return mMap[x][y]; }
	float GetBlockDamage(int x, int y) const { return mDamageMap[x][y]; }
	bool GetIsCheckpoint(int y) const 
	{ 
		for (int i = 0; i <= 20; i++)
		{
			if (mCheckpoints[i] == y)
			{
				return true;
			}
		}
		return false;
	}
	void DamageBlock(int x, int y, float damage) { mDamageMap[x][y] += damage; }
	void SetBlock(int x, int y, int block) { mMap[x][y] = block; }

private:
	// Helper functions
	void mGenerateGradVectorGrid();
	float mGetPerlNoise(int x, int y);

	// Member variables
	int mMap[210][621];
	int mCheckpoints[21];
	float mDamageMap[210][542];
	Vector2 mGradVectorGrid[22][62];
	class Game* mGame;
	class Player* mPlayer;
	float mBlockScale;
	Vector2 mGradientVectors[4];
	int mSeed;
};