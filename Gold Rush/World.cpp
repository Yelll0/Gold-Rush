#include "stdafx.h"

World::World(class Game* game, class Player* player, int seed)
	: mGame(game), 
	mPlayer(player),
	mBlockScale(3.f),
	mSeed(seed)
{
	// Randomly generate seed if no seed
	if (!seed) {}
	// Set all possible gradient vectors
	// TODO: Refactor to make less cluttered
	mGradientVectors[0].x = 10;
	mGradientVectors[0].y = 10;
	mGradientVectors[1].x = 10;
	mGradientVectors[1].y = -10;
	mGradientVectors[2].x = -10;
	mGradientVectors[2].y = -10;
	mGradientVectors[3].x = -10;
	mGradientVectors[3].y = 10;
	Generate();
}

World::~World()
{
}

float World::mPerlNoise(int x, int y)
{
	// Find nearest grid points
		// Divide both coords by 10
		// Round each coordinate to 1, store, and subtract/add 1 to the result depending on whether it is rounded up or down from the original
		// Alt: If possible, floor and ceil the quotient, and combine to determine and store the 4 grid points
	// Determine gradient vectors based on mSeed
	// Find distance vectors
		// 
	// Calculate dot products of each point
	// Bilinearly interpolate value of point
	// Return value
	return 1.f;
}

// 0 = Air
// 1 = Grass/dirt
// 2 = Stone
// 3 = Coal
// 4 = Copper
// 5 = Iron
// 6 = Titanium
// 7 = Mithril
// 8 = Gold
void World::Generate()
{
	// Set checkpoints
	mCheckpoints[0] = 616;
	mCheckpoints[1] = 606;
	int lastCheckpoint;
	int checkpointSize;
	int lastCheckpointSize = 10;
	for (int i = 2; i <= 16; i++)
	{
		lastCheckpoint = mCheckpoints[i - 1];
		checkpointSize = floor(lastCheckpointSize * 1.2);
		mCheckpoints[i] = lastCheckpoint - checkpointSize;
		lastCheckpointSize = checkpointSize;
	}

	// Fill with stone
	for (int i = 0; i <= 621; i++)
	{
		for (int j = 0; j <= 209; j++)
		{
			SetBlock(j, i, 0);
		}
	}

	// TODO: Generate all ores using perlin noise according to seed

	// Set checkpoints
	for (int i = 6; i <= 615; i++)
	{
		if (GetIsCheckpoint(i))
		{
			for (int j = 0; j <= 209; j++)
			{
				SetBlock(j, i, 0);
			}
		}
		else 
		{
			for (int j = 0; j <= 209; j++)
			{
				SetBlock(j, i, 2);
			}
		}
	}
	// Grass layer
	for (int i = 0; i <= 209; i++)
	{
		SetBlock(i, 615, 1);
	}

	// Damage map
	for (int i = 0; i <= 621; i++)
	{
		for (int j = 0; j <= 209; j++)
		{
			mDamageMap[j][i] = 0.f;
		}
	}
}