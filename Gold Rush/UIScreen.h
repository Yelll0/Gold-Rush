#pragma once

#include "stdafx.h"

class UIScreen
{
public:
	UIScreen(class Game* game, class Controller* controller);
	~UIScreen();

	virtual void Update(float deltaTime);

	class Button* GetButton(int i) const { return mButtons[i]; }
	int GetNumButtons() const { return mButtons.size(); }

protected:
	class Game* mGame;
	class Controller* mController;
	std::vector<class Button*> mButtons;
};

