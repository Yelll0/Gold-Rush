#pragma once

#include "stdafx.h"

class Inventory
{
public:
	Inventory(class Player* player, class Controller* controller);
	~Inventory();

	int GetTool() { return mTool; }
	void SetTool(int tool) { 
		mTool = tool;
		mPlayer->SetMineSpeed(mPickSpeeds[tool]);
	}
	int GetAmountOfItem(int id) { return mInventory[id]; }
	void AddItem(int id, int amount) { if (id) { mInventory[id] += amount; } }
	void DropItem(int id, int amount) { if (id) { mInventory[id] -= amount; } }

private:
	class Player* mPlayer;
	class Controller* mController; // TODO: Maybe create a reference to inventory in controller class
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
3. Bronze - Bronze pick : 4
4. Iron - Iron pick : 4
5. Steel - Steel pick : 6
6. Titanium - Titanium pick : 10
7. Mithril - Mithril pick : 20
8. - C4
*/