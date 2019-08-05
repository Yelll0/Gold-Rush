#include "World.h"

World::World(class Game* game, class Player* player)
	: mGame(game), 
	mPlayer(player)
{
	Generate();
}

World::~World()
{
}

void World::Generate()
{

}