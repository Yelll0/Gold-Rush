#include "stdafx.h"

World::World(class Game* game, class Player* player)
	: mGame(game), 
	mPlayer(player),
	mBlockScale(3.f)
{
	Generate();
}

World::~World()
{
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
	mCheckpoints[0] = 537;
	mCheckpoints[1] = 527;
	int lastCheckpoint;
	int checkpointSize;
	int lastCheckpointSize = 10;
	for (int i = 2; i <= 20; i++)
	{
		lastCheckpoint = mCheckpoints[i - 1];
		checkpointSize = lastCheckpointSize * 1.1;
		mCheckpoints[i] = round(lastCheckpoint - checkpointSize);
		lastCheckpointSize = checkpointSize;
	}
	for (int i = 0; i <= 541; i++)
	{
		for (int j = 0; j <= 209; j++)
		{
			SetBlock(j, i, 0);
		}
	}
	for (int i = 6; i <= 536; i++)
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

	for (int i = 0; i <= 209; i++)
	{
		SetBlock(i, 536, 1);
	}

	for (int i = 0; i <= 541; i++)
	{
		for (int j = 0; j <= 209; j++)
		{
			mDamageMap[j][i] = 0.f;
		}
	}
}