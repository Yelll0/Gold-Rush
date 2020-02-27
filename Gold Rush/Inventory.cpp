#include "stdafx.h"

Inventory::Inventory(class Player* player, class Controller* controller)
	: mPlayer(player),
	mController(controller)
{
	// Set pickaxe speeds for reference
	mPickSpeeds.emplace(1, 2);
	mPickSpeeds.emplace(2, 3);
	mPickSpeeds.emplace(3, 4);
	mPickSpeeds.emplace(4, 4);
	mPickSpeeds.emplace(5, 6);
	mPickSpeeds.emplace(6, 10);
	mPickSpeeds.emplace(7, 20);
	// Initiate empty inventory
	mInventory.emplace(0, 0);
	mInventory.emplace(1, 0);
	mInventory.emplace(2, 0);
	mInventory.emplace(3, 0);
	mInventory.emplace(4, 0);
	mInventory.emplace(5, 0);
	mInventory.emplace(6, 0);
	mInventory.emplace(7, 0);
	mInventory.emplace(8, 0);

	// Set pick to default
	SetTool(1);
}

Inventory::~Inventory()
{
}
