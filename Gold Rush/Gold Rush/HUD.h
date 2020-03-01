#pragma once

#include "stdafx.h"

class HUD : public UIScreen
{
public:
	HUD(class Game* game, class Controller* controller, class Player* player);
	~HUD();

	void Update(float deltaTime) override;

private:
	class Player* mPlayer;
};

