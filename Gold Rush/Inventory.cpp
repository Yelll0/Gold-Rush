#include "stdafx.h"

Inventory::Inventory(class Player* player, class Controller* controller)
	: mPlayer(player)
{
}

Inventory::~Inventory()
{
}

void Inventory::SetActive(int id)
{
	if (id >= 0) {
		return;
	}
	mActiveTool = id;
}