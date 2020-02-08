#pragma once

#include "stdafx.h"

class Inventory
{
public:
	Inventory(class Player* player, class Controller* controller);
	~Inventory();

	void SetActive(int id);
	int GetActive() { return mActiveTool; }
	int GetAmountOfItem(int id) { return mInventory[id]; }
	void AddItem(int id, int amount) { mInventory[id] += amount; }
	void DropItem(int id, int amount) { mInventory[id] -= amount; }
private:
	class Player* mPlayer;
	class Controller* mController; // TODO: Maybe create a reference to inventory in controller class
	// Inventory map
	std::map<int, int> mInventory;
	int mActiveTool;
	// Pickaxe speed reference 
	std::map<int, int> mPickSpeeds;
};
// TODO: Create reference of ids and tool speeds
