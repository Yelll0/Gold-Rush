#include "World.h"

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
	for (int i = 0; i <= 5; i++)
	{
		for (int j = 0; j <= 209; j++)
		{
			SetBlock(j, i, 0);
		}
	}
	for (int i = 6; i <= 536; i++)
	{
		for (int j = 0; j <= 209; j++)
		{
			SetBlock(j, i, 2);
		}
	}
	for (int i = 537; i <= 541; i++)
	{
		for (int j = 0; j <= 209; j++)
		{
			SetBlock(j, i, 0);
		}
	}
}
