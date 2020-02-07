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

void World::mGenerateGradVectorGrid()
{
	unsigned int B = mSeed;
	for (int i = 0; i <= 61; i++) {
		for (int j = 0; j < 21; j++)
		{
			srand(B);
			int pointVal = floor(rand() % 100 / 25);
			std::cout << pointVal << std::endl;
			mGradVectorGrid[j][i] = mGradientVectors[pointVal];
			if (B < 2887174368)
			{
				B *= 78;
			}
			else
			{
				B /= 13;
			}
		}
	}
}

float World::BilinearInterpolation(float q11, float q12, float q21, float q22, float x1, float x2, float y1, float y2, float x, float y)
{
	float x2x1, y2y1, x2x, y2y, yy1, xx1;
	x2x1 = x2 - x1;
	y2y1 = y2 - y1;
	x2x = x2 - x;
	y2y = y2 - y;
	yy1 = y - y1;
	xx1 = x - x1;
	return 1.0 / (x2x1 * y2y1) * (
		q11 * x2x * y2y +
		q21 * xx1 * y2y +
		q12 * x2x * yy1 +
		q22 * xx1 * yy1
		);
}

float World::mGetPerlNoise(int x, int y)
{
// Get gradient vectors
	Vector2 localGradVectors[4];
	int tempX = x, 
		tempY = y;
	if (!(x % 10)) { tempX += 1; }
	if (!(y % 10)) { tempY += 1; }
	int left = floor(tempX * 0.1),
		right = ceil(tempX * 0.1),
		top = floor(tempY * 0.1),
		bottom = ceil(tempY * 0.1);
	localGradVectors[0] = mGradVectorGrid[left][top];
	localGradVectors[1] = mGradVectorGrid[right][top];
	localGradVectors[2] = mGradVectorGrid[right][bottom];
	localGradVectors[3] = mGradVectorGrid[left][bottom];
// Find distance vectors
	Vector2 distanceVectors[4];
	distanceVectors[0].x = x - left * 10 + 0.5;
	distanceVectors[0].y = y - top * 10 + 0.5;
	distanceVectors[1].x = x - right * 10 - 0.5;
	distanceVectors[1].y = distanceVectors[0].y;
	distanceVectors[2].x = distanceVectors[1].x;
	distanceVectors[2].y = y - bottom * 10 - 0.5;
	distanceVectors[3].x = distanceVectors[0].x;
	distanceVectors[3].y = distanceVectors[2].y;
// Calculate dot products of each point
	float dotProd[4];
	for (int i = 0; i <= 3; i++)
	{
		dotProd[i] = Vector2::Dot(localGradVectors[i], distanceVectors[i]);
	}
// Bilinearly interpolate value of point
	return BilinearInterpolation(dotProd[0], dotProd[3], dotProd[1], dotProd[2], left*10-0.5, right*10-0.5, top*10-0.5, bottom*10-0.5, x, y);
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
	// Generate gradient vectors
	mGenerateGradVectorGrid();
	for (int i = 0; i <= 621; i++)
	{
		for (int j = 0; j <= 209; j++)
		{
			mGenerationMap[j][i] = mGetPerlNoise(j, i);
			std::cout << mGenerationMap[j][i] << ", ";
		}
		std::cout << std::endl;
	}

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