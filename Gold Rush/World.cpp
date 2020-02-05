#include "stdafx.h"

World::World(class Game* game, class Player* player, int seed)
	: mGame(game), 
	mPlayer(player),
	mBlockScale(3.f),
	mSeed(seed)
{
	// Randomly generate seed if no seed
	if (!seed) { mSeed = rand() % 100000000000; }
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
	Vector2 pA, pB, pC, pD;
	// Left side
	pA.x = floor(x / 10) * 10;
	pC.x = pA.x;
	// Right side
	pB.x = ceil(x / 10) * 10;
	pD.x = pB.x;
	// Top side
	pA.y = floor(y / 10) * 10;
	pB.y = pA.y;
	// Bottom side
	pC.y = ceil(y / 10) * 10;
	pD.y = pC.y;

// Determine gradient vectors based on mSeed
	Vector2 gA, gB, gC, gD;
	L = mSeed / (floor(x / 10) * 10) / (floor(y / 10) * 10);
	for (int i = 0; i <= 3; i++)
	{
		switch (i)
		{
		case 0: 
			L = (O * L + Y) % J;
			round(L / 0.25);
			break;
		default:
			break;
		}
	}
// Find distance vectors
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