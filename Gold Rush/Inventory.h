#pragma once

#include "stdafx.h"

class Inventory
{
public:
	Inventory(class Player* player, class Controller* controller, class Game* game);
	~Inventory();

	int GetTool() { return mTool; }
	void UpgradePick();
	void C4Action();
	int GetAmountOfItem(int id) { return mInventory[id]; }
	void AddItem(int id, int amount) { if (id < 10) { mInventory[id] += amount; } }
	void DropItem(int id, int amount) { if (id < 10) { mInventory[id] -= amount; } }

private:
	class Player* mPlayer;
	class Controller* mController;
	class Game* mGame;
	// Inventory map
	std::map<int, int> mInventory;
	int mTool;
	// Pickaxe speed reference 
	std::map<int, int> mPickSpeeds;
};
/*
0. Gold
1. Coal - Default pick : 2
2. Copper - Copper pick : 3
3. Iron - Iron pick : 6
4. Titanium - Titanium pick : 10
5. Mithril - Mithril pick : 20
6. - C4
*/