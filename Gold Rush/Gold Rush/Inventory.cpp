#include "stdafx.h"

Inventory::Inventory(class Player* player, class Controller* controller, class Game* game)
	: mPlayer(player),
	mController(controller),
	mGame(game),
	mTool(1)
{
	// Set pickaxe speeds for reference
	mPickSpeeds.emplace(1, 2);
	mPickSpeeds.emplace(2, 3);
	mPickSpeeds.emplace(3, 6);
	mPickSpeeds.emplace(4, 10);
	mPickSpeeds.emplace(5, 20);
	// Initiate empty inventory
	mInventory.emplace(0, 0);
	mInventory.emplace(1, 5);
	mInventory.emplace(2, 0);
	mInventory.emplace(3, 0);
	mInventory.emplace(4, 0);
	mInventory.emplace(5, 0);
	mInventory.emplace(6, 5);

	mPlayer->SetMineSpeed(mPickSpeeds[mTool]);
}

Inventory::~Inventory()
{
}

void Inventory::UpgradePick() {
	int mat = mTool + 1;

	if (mInventory[mat] > 0)
	{
		if (mTool < 5)
		{
			mTool += 1;
			mPlayer->SetMineSpeed(mPickSpeeds[mTool]);
			mInventory[mat] -= 1;
			mGame->GetUI()->GetButton(10)->SetTexCode(mTool+20);
		}
	}
}

void Inventory::C4Action()
{
	if (mPlayer->GetIsAtCheckpoint())
	{
		// Craft C4
		if (mInventory[1] > 0)
		{
			mInventory[6] += 1;
			mInventory[1] -= 1;
		}
	}
	else
	{
		// Use C4
		if (mInventory[6] > 0)
		{
			for (int i = mPlayer->GetPos().x - 1; i <= mPlayer->GetPos().x + 1; i++)
			{
				for (int j = mPlayer->GetPos().y - 1; j <= mPlayer->GetPos().y + 1; j++)
				{
					AddItem(mGame->GetWorld()->GetItemForBlock(mGame->GetWorld()->GetBlock(i, j)), 1);
					mGame->GetWorld()->SetBlock(i, j, 0);
				}
			}
			mInventory[6] -= 1;
		}
	}
}