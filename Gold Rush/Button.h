#pragma once

#include "stdafx.h"

class Button
{
public:
	Button(class UIScreen* owningUI);
	~Button();

	void ProcessInput();
	
private:
	bool mIsPressed;
	bool mIsMouseOver;

	class UIScreen* mOwningUI;
};

